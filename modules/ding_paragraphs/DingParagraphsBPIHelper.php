<?php

/**
 * @file
 * Code for the Ding paragraphs helper class.
 */

use Bpi\Sdk\Item\Node;

/**
 * Helper for paragraphs content in bpi.
 *
 * The public methods are called from BPI api hooks (cf. implementation of
 * bpi.api.php in ding_paragraphs.module).
 *
 * The code looks complex in some places, but it is basically just runs
 * through paragraphs structures to collect and serialize data to send to BPI,
 * or runs through serialized data for rebuilding paragraphs when syndicating from BPI.
 *
 * Most of the code * inside the loops are similar to the code in the bpi
 * module when pushing and syndicating content.
 */
class DingParagraphsBPIHelper {
  const BPI_FILE_URL = 'bpi_file_url';
  const DING_ENTITY_ID = 'ding_entity_id';

  /**
   * Process all files references from paragraphs.
   *
   * Stores the full file url in the data for later retrieval when syndicating
   * paragraphs. The files themselves are returned for further processing.
   *
   * @param array $paragraphs_data
   *   The paragraphs data.
   *
   * @return array
   *   The BPI assets.
   */
  public function replaceFilesWithUrls(array &$paragraphs_data) {
    $files = [];

    // Run through the paragraps structure and replace file references with
    // file urls. As a side effect we collect the actual files in array.
    $this->traverse($paragraphs_data, function ($key, &$value, &$data) use (&$files) {
      if (is_array($value) && isset($value['fid'], $value['uri'])) {
        $file = file_load($value['fid']);
        if ($file) {
          $files[] = $file;
          $value += array(self::BPI_FILE_URL => file_create_url($file->uri));
        }
      }
    });

    return $this->getBpiAssets($files);
  }

  /**
   * Process material references in paragraphs data.
   *
   * Stores the actual ding entity id in the data.
   *
   * @param array $paragraphs_data
   *   The paragraphs data.
   */
  public function processMaterials(array &$paragraphs_data) {
    $this->traverse($paragraphs_data, function ($key, &$item) {
      if (is_array($item) && !empty($item['ting_object_id'])) {
        $ding_entity_id = NULL;
        $id = $item['ting_object_id'];
        if (bpi_material_is_sharable($id)) {
          $ding_entity_id = $id;
        }
        $item = array(self::DING_ENTITY_ID => $ding_entity_id);
      }
      elseif (isset($item->endpoints)) {
        $ding_entity_id = NULL;
        $endpoints = $item->endpoints;
        $data = array_filter($endpoints[LANGUAGE_NONE], function ($i) {
          return $i['entity_type'] == 'ting_object';
        });

        if (!empty($data)) {
          $ting_data = current($data);
          $ting_object = entity_load_single('ting_object', $ting_data['entity_id']);
          if ($ting_object) {
            if (bpi_material_is_sharable($ting_object->ding_entity_id)) {
              $ding_entity_id = $ting_object->ding_entity_id;
            }
          }
        }
        $item = (object) array(self::DING_ENTITY_ID => $ding_entity_id);
      }
    });
  }

  /**
   * Convert a list of files (used in paragraphs) to bpi assets.
   *
   * @param array $files
   *   The files.
   *
   * @return array
   *   The BPI assets.
   */
  private function getBpiAssets(array $files) {
    $assets = [];

    foreach ($files as $file) {
      $asset = array(
        'path' => file_create_url($file->uri),
        'type' => 'paragraphs_image',
        'name' => $file->filename,
        'extension' => pathinfo($file->uri, PATHINFO_EXTENSION),
      );
      if (!empty($file->alt)) {
        $asset['alt'] = $file->alt;
      }
      if (!empty($file->title)) {
        $asset['title'] = $file->title;
      }

      $assets[] = $asset;
    }

    return $assets;
  }

  /**
   * Add bpi paragraphs to node form.
   *
   * This is heavily inspired by paragraphs_defaults_form_alter
   * (cf. http://cgit.drupalcode.org/paragraphs_defaults/tree/paragraphs_defaults.module#n96)
   *
   * @param array $form
   *   The form.
   * @param array $form_state
   *   The form state.
   * @param \Bpi\Sdk\Item\Node $bpi_node
   *   The BPI node.
   * @param array|bool|null $syndicated_images
   *   The syndicated images if any.
   */
  public function addBpiParagraphs(array &$form, array &$form_state, Node $bpi_node, $syndicated_images) {
    // We don't want to alter the form after an ajax call.
    if (empty($form_state['input'])) {
      // There's also no use if the form doesn't have these properties.
      if (isset($form['#entity']) && isset($form['#entity_type'])) {

        $entity = $form['#entity'];
        $entity_type = $form['#entity_type'];
        list($id, , $bundle_name) = entity_extract_ids($entity_type, $entity);

        if (!isset($id)) {
          $paragraphs_fields = field_read_fields(array(
            'type' => 'paragraphs',
            'entity_type' => $entity_type,
            'bundle' => $bundle_name,
          ));

          foreach ($paragraphs_fields as $paragraphs_field) {
            $field_name = $paragraphs_field['field_name'];
            if (isset($form[$field_name]) && $form[$field_name]['#access']) {
              // Add the paragraphs field defaults.
              $field = field_info_field($field_name);
              $instance = field_info_instance($entity_type, $field_name, $bundle_name);
              $paragraphs = $this->getBpiParagraphsItems($entity_type, $entity, $bpi_node, $syndicated_images);
              if ($paragraphs !== NULL) {
                // Unset the paragraph field.
                unset($form[$field_name]);
                unset($form_state['field'][$field_name]);

                // Order any existing paragraphs in a form we can use to set
                // the default value.
                $items = array_map(function ($item) {
                  return ['entity' => $item];
                }, $paragraphs);

                $paragraphs_field_form = field_default_form($entity_type, $entity, $field, $instance, LANGUAGE_NONE, $items, $form, $form_state);

                // Place ding entity ids into default values.
                $this->traverse($paragraphs_field_form, function ($key, &$value, &$data) {
                  if (is_array($value) && isset($value['#entity'], $value['ting_object_id'], $value['#bundle'])) {
                    $entity = $value['#entity'];
                    $delta = $value['#delta'];
                    $field = &$value['ting_object_id'];

                    switch ($value['#bundle']) {
                      case 'ding_paragraphs_single_material':
                        // Apparently, fields of type "Ting reference" do not
                        // work with entity_metadata_wrapper so we get the
                        // data in the old fashioned way.
                        $material_id = $entity->field_ding_paragraphs_single_mat[LANGUAGE_NONE][0]['value']['ding_entity_id'];
                        $this->setMaterialId($field, $material_id);
                        break;

                      case 'ding_paragraphs_material_list':
                      case 'ding_paragraphs_carousel':
                        $material_ids = array_map(
                          function ($item) {
                            return $item['value']['ding_entity_id'];
                          },
                          $entity->field_ding_paragraphs_material[LANGUAGE_NONE]
                        );

                        if (isset($material_ids[$delta])) {
                          $material_id = $material_ids[$delta];
                          $this->setMaterialId($field, $material_id);
                        }
                        break;
                    }
                  }
                });

                $form += (array) $paragraphs_field_form;
              }
            }
          }
        }
      }
    }
  }

  /**
   * Validate and set material id (as default value) in a form field.
   *
   * @param array $field
   *   The field.
   * @param string $material_id
   *   The material id.
   */
  private function setMaterialId(array &$field, $material_id) {
    $id = $this->validateMaterialId($material_id);
    if (!$id) {
      // We cannot use `form_set_error` (or similar means) to inform the user
      // of invalid materials, so we add a message in the field value itself.
      $id = t('Invalid material id: @id', ['@id' => $material_id]);
      // Add a global error message informing the user that a material is
      // invalid.
      drupal_set_message(t('The material %id does not exist.', ['%id' => $material_id]), 'error', FALSE);
    }
    $field['#default_value'] = $id;
  }

  /**
   * Validate a material id.
   *
   * @param string $material_id
   *   The material id.
   *
   * @return bool|int
   *   Id of validated material or FALSE on invalid material.
   */
  private function validateMaterialId($material_id) {
    preg_match('/[^\:]+\:\s?(?P<id>.*)/', $material_id, $matches);
    if (!isset($matches['id'])) {
      return FALSE;
    }
    return bpi_validate_material($matches['id']);
  }

  /**
   * Get BPI paragraphs items from a BPI node.
   *
   * @param string $entity_type
   *   The entity type.
   * @param object $entity
   *   The entity.
   * @param \Bpi\Sdk\Item\Node $bpi_node
   *   The BPI node.
   * @param array|bool|null $syndicated_images
   *   The syndicated images.
   *
   * @return ParagraphsItemEntity[]
   *   The paragraph items.
   */
  private function getBpiParagraphsItems($entity_type, $entity, Node $bpi_node, $syndicated_images) {
    $bpi_properties = $bpi_node->getProperties();
    $bpi_data = json_decode($bpi_properties['data'], TRUE);

    $paragraphs_items = [];
    if (!empty($bpi_data)) {
      list($id, , $bundle_name) = entity_extract_ids($entity_type, $entity);
      $paragraphs_fields = field_read_fields(array(
        'type' => 'paragraphs',
        'entity_type' => $entity_type,
        'bundle' => $bundle_name,
      ));

      $lang = $entity->language;

      // Get paragraphs assets indexed by original url.
      $paragraphs_assets = [];
      if (isset($syndicated_images['paragraphs_image'])) {
        foreach ($syndicated_images['paragraphs_image'] as $asset) {
          $paragraphs_assets[$asset['external']] = $asset;
        }
      }

      // Replace file urls with references to syndicated files.
      $this->traverse($bpi_data, function ($key, &$value, &$data) use ($paragraphs_assets) {
        if (is_array($value) && isset($value[self::BPI_FILE_URL])) {
          $url = $value[self::BPI_FILE_URL];
          if (isset($paragraphs_assets[$url]['@managed_file'])) {
            // Inject the file object (as an array).
            $value = (array) $paragraphs_assets[$url]['@managed_file'];
          }
          else {
            // No syndicated file found. Remove the data entry.
            unset($data[$key]);
          }
        }
      });

      // Build the final list of paragraphs.
      foreach ($paragraphs_fields as $paragraphs_field_name => $paragraphs_field) {
        if (isset($bpi_data[$paragraphs_field_name]) && is_array($bpi_data[$paragraphs_field_name])) {
          foreach ($bpi_data[$paragraphs_field_name] as $item) {
            $paragraphs_items[] = new ParagraphsItemEntity($item);
          }
        }
      }
    }

    if (empty($paragraphs_items)) {
      // If we don't have any paragraphs items, we create a single paragraph
      // and set its body to the full body content from the BPI node.
      // This should only happen in the unlikely event that we're syndicating
      // paragraphs that do not exists on the target site.
      $paragraphs_items[] = new ParagraphsItemEntity(array(
        'field_name' => 'field_ding_news_paragraphs',
        'bundle' => 'ding_paragraphs_text',
        'field_ding_paragraphs_text' => array(
          'und' => array(
            array(
              'value' => $bpi_properties['body'],
              'format' => 'ding_wysiwyg',
            ),
          ),
        ),
      ));
    }

    return $paragraphs_items;
  }

  /**
   * Descend (depth-first) into array with callback (by reference).
   *
   * This is basically a usable version of `array_walk_recursive` which visits
   * all nodes (`array_walk_recursive` only visits leafs!)
   *
   * @param array $data
   *   The data.
   * @param callable $callback
   *   The callback acception three parameters:
   *   - $key: the current key.
   *   - $value: the current value.
   *   - $data: the full data object being traversed.
   *
   * @see https://www.php.net/manual/en/function.array-walk-recursive.php
   */
  private function traverse(array &$data, callable $callback) {
    foreach ($data as $key => &$value) {
      if (is_array($value)) {
        $this->traverse($value, $callback);
      }
      $callback($key, $value, $data);
    }
  }

}
