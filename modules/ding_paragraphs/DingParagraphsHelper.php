<?php

/**
 * Helper for paragraphs content in bpi.
 */
class DingParagraphsHelper {
  const BPI_FILE_URL = 'bpi_file_url';
  const DING_ENTITY_ID = 'ding_entity_id';

  /**
   * Process all files references from paragraphs.
   *
   * Stores the full file url in the data for later retrieval when syndicating
   * paragraphs.
   */
  public function replaceFilesWithUrls(array &$data) {
    $files = [];

    $this->traverse($data, function ($key, &$value, &$data) use (&$files) {
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
   */
  public function processMaterials(array &$paragraphs_data, $include_materials) {
    $materials = [];

    if ($include_materials) {
      $this->traverse($paragraphs_data, function ($key, &$item) use (&$materials) {
        if (is_array($item) && !empty($item['ting_object_id'])) {
          $ding_entity_id = null;
          $id = $item['ting_object_id'];
          // Filter out id's with "katalog" PID, as they only makes sens on
          // current site.
          if (!preg_match('/katalog/', $id)) {
            $ding_entity_id = $id;
            $materials[] = $id;
          }
          $item = array(self::DING_ENTITY_ID => $ding_entity_id);
        } elseif (isset($item->endpoints)) {
          $ding_entity_id = null;
          $endpoints = $item->endpoints;
          $data = array_filter($endpoints[LANGUAGE_NONE], function ($i) {
            return $i['entity_type'] == 'ting_object';
          });
          if (!empty($data)) {
            $ting_data = current($data);
            $ting_object = entity_load_single('ting_object', $ting_data['entity_id']);
            if ($ting_object) {
              if (!preg_match('/katalog/', $ting_object->ding_entity_id)) {
                $ding_entity_id = $ting_object->ding_entity_id;
                $materials[] = $ting_object->ding_entity_id;
              }
            }
          }
          $item = (object)array(self::DING_ENTITY_ID => $ding_entity_id);
        }
      });
    }

    return $materials;
  }

  /**
   * Convert a list of files (used in paragraphs) to bpi assets.
   */
  private function getBpiAssets(array $files) {
    $assets = [];

    foreach ($files as $file) {
      $assets[] = array(
        'path' => file_create_url($file->uri),
        'alt' => $file->alt ?: $file->filename,
        'title' => $file->title ?: $file->filename,
        'type' => 'paragraphs_image',
        'name' => $file->filename,
        'extension' => pathinfo($file->uri, PATHINFO_EXTENSION),
      );
    }

    return $assets;
  }

  /**
   * Add bpi paragraphs to node form.
   *
   * This is heavily inspired by paragraphs_defaults_form_alter
   * (cf. http://cgit.drupalcode.org/paragraphs_defaults/tree/paragraphs_defaults.module#n96)
   */
  public function addBpiParagraphs(array &$form, array &$form_state, $bpi_node, $syndicated_images) {
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
                foreach ($paragraphs as $paragraphs_item) {
                  $items[]['entity'] = $paragraphs_item;
                }
                $paragraphs_field_form = field_default_form($entity_type, $entity, $field, $instance, LANGUAGE_NONE, $items, $form, $form_state);

                // Place ding entity ids into default values.
                $this->traverse($paragraphs_field_form, function ($key, &$value, &$data) use ($field_name) {
                  if (is_array($value) && isset($value['value']['#value']['ding_entity_id'], $value['ting_object_id'])) {
                    $field = &$value['ting_object_id'];
                    $material_number = $value['value']['#value']['ding_entity_id'];
                    preg_match('/[^\:]+\:\s?(.*)/', $material_number, $matches);
                    $id = bpi_validate_material($matches[1]);
                    if (!$id) {
                      $id = $material_number;
                      $field['#attributes'] = array('class' => array('error'));
                      drupal_set_message(t('These materials doesn\'t exists.'), 'error', FALSE);
                    }
                    $field['#default_value'] = $id;
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
   *
   */
  private function getBpiParagraphsItems($entity_type, $entity, $bpi_node, $syndicated_images) {
    if (empty($bpi_node)) {
      return NULL;
    }

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
      $this->traverse($bpi_data, function ($key, &$value, &$data) use (&$paragraphs_assets) {
        if (is_array($value) && isset($value[self::BPI_FILE_URL])) {
          $url = $value[self::BPI_FILE_URL];
          if (isset($paragraphs_assets[$url], $paragraphs_assets[$url]['@managed_file'])) {
            // Inject the file object (as an array).
            $value = (array)$paragraphs_assets[$url]['@managed_file'];
          } else {
            // No syndicated file found. Remove the data entry.
            unset($data[$key]);
          }
        }
      });

      foreach ($paragraphs_fields as $paragraphs_field_name => $paragraphs_field) {
        if (isset($bpi_data[$paragraphs_field_name]) && is_array($bpi_data[$paragraphs_field_name])) {
          foreach ($bpi_data[$paragraphs_field_name] as $item) {
            $paragraphs_items[] = new ParagraphsItemEntity($item);
          }
        }
      }
    }

    if (empty($paragraphs_items)) {
      // Put bpi body into default paragraph item.
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
   * Depth-first descend into array with callback (by reference).
   */
  private function traverse(array &$data, $callback) {
    foreach ($data as $key => &$value) {
      if (is_array($value)) {
        $this->traverse($value, $callback);
      }
      $callback($key, $value, $data);
    }
  }

}
