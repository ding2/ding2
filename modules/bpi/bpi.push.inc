<?php
/**
 * @file
 * Syndication logic here.
 */

/**
 * BPI http push form, used in save and push on node/edit page.
 *
 * @param int $nid
 *   Node id.
 *
 * @return array
 *   Form structure.
 *
 * @ingroup forms
 */
function bpi_http_push_action_form($nid) {
  $form = array();
  $form['#tree'] = FALSE;
  $form['bpi_push_nid'] = array(
    '#type' => 'hidden',
    '#value' => isset($nid) ? $nid : 0,
  );

  // Get BPI vocabularies (category and audience).
  $vocabularies = bpi_get_bpi_dictionaries();

  $form['vocabularies'] = array(
    '#type' => 'fieldset',
    '#title' => t('BPI vocabularies'),
    '#description' => t('BPI vocabularies is used to categories the pushed content, so searching for content later is easier and related content can be found.'),
  );

  $categories = array_values($vocabularies['category']);
  $form['vocabularies']['bpi_push_category'] = array(
    '#type' => 'select',
    '#title' => t('Category'),
    '#options' => array_merge(array('' => t('- choose -')), array_combine($categories, $categories)),
  );

  $audiences = array_values($vocabularies['audience']);
  $form['vocabularies']['bpi_push_audience'] = array(
    '#type' => 'select',
    '#title' => t('Audience'),
    '#options' => array_merge(array('' => t('- choose -')), array_combine($audiences, $audiences)),
  );

  $form['configurations'] = array(
    '#type' => 'fieldset',
    '#title' => t('BPI options'),
  );

  $form['configurations']['bpi_push_images'] = array(
    '#type' => 'checkbox',
    '#title' => t('Push with images'),
    '#description' => t('You should have permission to publish the images before selecting this option.'),
    '#default_value' => FALSE,
  );

  $form['configurations']['bpi_push_ccl'] = array(
    '#type' => 'checkbox',
    '#title' => t('I want to be anonymous'),
    '#description' => t('If checked the content will be pushed as anonymous to BPI.'),
    '#default_value' => FALSE,
  );

  $form['configurations']['bpi_push_refs'] = array(
    '#type' => 'checkbox',
    '#title' => t('Push with references'),
    '#description' => t('If checked the content will be pushed with material reference to the data well. Note that posts with the katalog keyword will not be pushed.'),
    '#default_value' => TRUE,
  );

  $form['configurations']['bpi_push_editable'] = array(
    '#type' => 'checkbox',
    '#title' => t('Editable'),
    '#description' => t('If checked the content will be marked as not editable (It is not enforced but only recommanded that the content is not changed after syndication).'),
    '#default_value' => '1',
  );

  if ($nid) {
    $bpi_node = bpi_get_bpi_nodes($nid);

    if (!empty($bpi_node[$nid])) {
      $data = unserialize($bpi_node[$nid]->data);
      $form['vocabularies']['bpi_push_category']['#default_value'] = $data['category'];
      $form['vocabularies']['bpi_push_audience']['#default_value'] = $data['audience'];
      $form['configurations']['bpi_push_images']['#default_value'] = $data['with_images'];
      $form['configurations']['bpi_push_ccl']['#default_value'] = !$data['authorship'];
      $form['configurations']['bpi_push_refs']['#default_value'] = $data['with_refs'];
      $form['configurations']['bpi_push_editable']['#default_value'] = $data['editable'];
    }
  }

  return $form;
}

/**
 * Convert node object to array structure, suitable for pushing to the well.
 *
 * @param stdClass $node
 *   Node object being processed.
 * @param string $category
 *   Selected category at the BPI side.
 * @param string $audience
 *   Selected audience at the BPI side.
 * @param bool $with_images
 *   Include images or not.
 * @param bool $authorship
 *   Include author name or not.
 * @param int $editable
 *   1 - to mark as editable, 0 - not editable.
 * @param bool $with_refs
 *   If TRUE ting material reference are extracted.
 *
 * @return array
 *   An array of node values, used by the BPI web service.
 *
 * @todo Add a hook allowing changing the values before they are sent to BPI.
 * @todo Split this function into smaller parts (ex: images, texts).
 */
function bpi_convert_to_bpi($node, $category, $audience, $with_images = FALSE, $authorship = FALSE, $editable = 1, $with_refs = FALSE) {
  $bpi_content = array();

  $bpi_content['agency_id'] = variable_get('bpi_agency_id', '');
  $bpi_content['local_id'] = $node->nid;
  $bpi_content['bpi_id'] = isset($node->bpi_id) ? $node->bpi_id : NULL;

  $user = user_load($node->uid);
  $bpi_content['firstname'] = $user->name;
  $bpi_content['lastname'] = '';

  $bpi_content['title'] = $node->title;


  $teaser_field = field_view_field('node', $node, variable_get('bpi_field_teaser', ''));
  $body_field = field_view_field('node', $node, variable_get('bpi_field_body', ''));
  $teaser = '';
  $body = '';

  // Whether the field is a text area with summary, fetch the summary, if not -
  // fetch it's safe value.
  if (!empty($teaser_field) && isset($teaser_field['#items'][0]['safe_summary'])) {
    $teaser = $teaser_field['#items'][0]['safe_summary'];
  }
  elseif (isset($teaser_field['#items'][0]['safe_value'])) {
    $teaser = $teaser_field['#items'][0]['safe_value'];
  }
  elseif (isset($teaser_field[0]['#markup'])) {
    $teaser = $teaser_field[0]['#markup'];
  }

  // Find the references to the ting date well.
  $materials_drupal = array();
  if ($with_refs) {
    // Function field_get_items returns data with 2 different structure, depending from stage when it was called.
    $items = field_get_items('node', $node, variable_get('bpi_field_materials', ''));
    foreach ($items as $item) {
      // First case, we have completly saved node, when it returns ding_object_id.
      if (!empty($item['ting_object_id'])) {
        $id = $item['ting_object_id'];
        // Filter out id's with "katalog" PID, as they only makes sens on
        // current site.
        if (!preg_match('/katalog/', $id)) {
          $materials_drupal[] = $id;
        }
      }
      // Second case, we used "Save and push" button and node wasn't completly saved
      // In this case, we have object of class Relation.
      elseif (isset($item['value']->endpoints)) {
        $endpoints = $item['value']->endpoints;
        $data = array_filter($endpoints[LANGUAGE_NONE], function ($i) {
          return $i['entity_type'] == 'ting_object';
        });
        if (!empty($data)) {
          $ting_data = current($data);
          $ting_object = entity_load_single('ting_object', $ting_data['entity_id']);
          if ($ting_object) {
            if (!preg_match('/katalog/', $ting_object->ding_entity_id)) {
              $materials_drupal[] = $ting_object->ding_entity_id;
            }
          }
        }
      }
    }
  }

  if (!empty($body_field) && isset($body_field['#items'][0]['safe_value'])) {
    $body = $body_field['#items'][0]['safe_value'];
  }
  elseif (isset($body_field[0]['#markup'])) {
    $body = $body_field[0]['#markup'];
  }

  // Empty the teaser, if body and teaser are mapped to same fields
  // and the values are identical.
  if ($teaser === $body) {
    $teaser = '';
  }

  $bpi_content['body'] = html_entity_decode($body);
  $bpi_content['teaser'] = html_entity_decode($teaser);
  $dt = new DateTime();
  $dt->setTimestamp($node->changed);
  $bpi_content['creation'] = $dt->format(DateTime::W3C);
  $bpi_content['type'] = $node->type;
  $bpi_content['category'] = $category;
  $bpi_content['audience'] = $audience;
  $bpi_content['related_materials'] = $materials_drupal;
  $bpi_content['editable'] = (int) $editable;
  $bpi_content['authorship'] = ($authorship) ? FALSE : TRUE;
  $bpi_content['images'] = array();

  if ($with_images) {
    $image_fields = bpi_fetch_image_fields($node->type);

    if (!empty($image_fields)) {
      foreach ($image_fields as $field_name) {
        $field_value = field_view_field('node', $node, $field_name);

        if (!empty($field_value['#items'][0]['uri'])) {
          $file_url = file_create_url($field_value['#items'][0]['uri']);
          // Image pseudo-check.
          if (@getimagesize($file_url)) {
            $bpi_content['images'][] = array(
              'path' => $file_url,
              'alt' => '',
              'title' => '',
            );
          }
        }
      }
    }
  }
  else {
    $bpi_content['body'] = preg_replace(
      '~(<p>)?<img.+?/>(</p>)?~is',
      '',
      $bpi_content['body']
    );
  }

  return $bpi_content;
}

/**
 * Fetch image field types.
 *
 * @param string $bundle
 *   Node type.
 *
 * @return array
 *   Array of field names which are actually image fields.
 */
function bpi_fetch_image_fields($bundle) {
  $potential_image_fields = array('image_image', 'media_generic');
  $field_instances = field_info_instances('node', (string) $bundle);

  $image_fields = array();

  if (is_array($field_instances)) {
    foreach ($field_instances as $key => $instance) {
      if (in_array($instance['widget']['type'], $potential_image_fields)) {
        $image_fields[] = $key;
      }
    }
  }

  return $image_fields;
}

/**
 * Fetch dictionaries from BPI ws.
 *
 * @return array
 *   Nested array of dictionaries, keyed by dictionary
 *   type.
 */
function bpi_get_bpi_dictionaries() {
  $dictionaries = array('category' => array(), 'audience' => array());

  try {
    $bpi = bpi_client_instance();
    $dictionaries = $bpi->getDictionaries();
  }
  catch (Exception $e) {
    watchdog_exception('bpi', $e);
  }

  return $dictionaries;
}
