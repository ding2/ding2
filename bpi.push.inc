<?php
/**
 * @file
 * Syndication logic here.
 */

/**
 * Start a content push session.
 *
 * @see bpi_menu()
 *
 * @param string $type
 *   Request type, simple http or ajax.
 * @param int $nid
 *   Node id, whose content is to be pushed.
 *
 * @return Array/string
 *   Ajax command set in case of ajax request, push content page
 *   markup otherwise.
 */
function bpi_push_action($type, $nid) {
  $is_ajax = ($type == 'ajax') ? TRUE : FALSE;

  if (empty($nid)) {
    return;
  }

  if (!bpi_push_available($nid)) {
    drupal_access_denied();
    drupal_exit();
  }

  $push_form = drupal_get_form('bpi_push_form', $nid);

  if ($is_ajax) {
    $commands = array();

    $commands[] = ajax_command_ding_popup(
      'bpi-push',
      t('Push to BPI'),
      drupal_render($push_form),
      array('refresh' => TRUE)
    );

    return array('#type' => 'ajax', '#commands' => $commands);
  }
  else {
    return $push_form;
  }
}

/**
 * BPI http action, with no ajax functionality.
 *
 * @param int $nid
 *   The node id, waiting to be pushed.
 *
 * @return array
 *   Form structure.
 */
function bpi_http_push_action($nid) {
  return drupal_get_form('bpi_http_push_action_form', $nid);
}

/**
 * BPI http push form, used in save and push on node/edit page.
 *
 * @param array $form
 *   Form structure.
 * @param array $form_state
 *   Form state values.
 * @param int $nid
 *   The node id, waiting to be pushed.
 *
 * @return array
 *   Form structure.
 *
 * @ingroup forms
 */
function bpi_http_push_action_form($form, &$form_state, $nid) {
  $form = bpi_http_push_action_form_raw($nid);
  return $form;
}

function bpi_http_push_action_form_raw($nid) {
  // Check that a nid was part of the callback.
  if (!empty($nid)) {
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
      '#options' => array_combine($categories, $categories),
    );

    $audiences = array_values($vocabularies['audience']);
    $form['vocabularies']['bpi_push_audience'] = array(
      '#type' => 'select',
      '#title' => t('Audience'),
      '#options' => array_combine($audiences, $audiences),
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

    return $form;
    // Load node to get title
    // @todo there must be another way to do this.
    $node = node_load($nid);

    // Add confirmation button.
    return confirm_form(
      $form,
      t('Push content to BPI?'),
      'admin/content',
      t('Are you sure you want to push content %title to BPI?', array('%title' => $node->title))
    );
  }
  else {
    // Node id was not defined in the callback to display error message.
    drupal_set_message(t('Node id was not found and content can not be pushed to BPI.'), 'error');
    watchdog('bpi', 'Node id was not found in admin page to push content to BPI', array(), WATCHDOG_ERROR);
  }
}

/**
 * Submit handler for the push node form on node/edit page.
 *
 * @see bpi_push_form()
 *
 * @param array $form
 *   Form structure.
 * @param array $form_state
 *   Form state values.
 *
 * @ingroup forms
 */
function bpi_http_push_action_form_submit($form, &$form_state) {
  $nid = $form_state['input']['bpi_push_nid'];
  $category = $form_state['input']['bpi_push_category'];
  $audience = $form_state['input']['bpi_push_audience'];
  $with_images = $form_state['input']['bpi_push_images'];
  $authorship = $form_state['input']['bpi_push_ccl'];
  $editable = $form_state['input']['bpi_push_editable'];
  $with_refs = $form_state['input']['bpi_push_refs'];

  // Extract information from the node.
  $node = node_load($nid);
  $bpi_content = bpi_convert_to_bpi($node, $category, $audience, $with_images, $authorship, $editable, $with_refs);

  try {
    $bpi = bpi_client_instance();
//    $push_result = $bpi->push($bpi_content)->getProperties();

    if (!empty($push_result['id'])) {
      db_merge('bpi_syndicated')
        ->fields(array(
          'nid' => $nid,
          'bid' => $push_result['id'],
          'status' => BPI_PUSHED,
          'timestamp' => time(),
        ))
        ->condition('nid', $nid, '=')
        ->execute();
      drupal_set_message(t('Node %title was successfully pushed to BPI well.', array('%title' => $node->title)));
    }

    if (isset($_GET['prev_destination'])) {
      drupal_goto($_GET['prev_destination']);
    }
    else {
      drupal_goto('admin/bpi');
    }
  }
  catch (Exception $exception) {
    bpi_error_message($exception, 'error');
  }
}

/**
 * BPI push form.
 *
 * @param array $form
 *   Form structure.
 * @param array $form_state
 *   Form state values.
 * @param int $nid
 *   The node id, waiting to be pushed.
 *
 * @return array
 *   Form structure.
 *
 * @ingroup forms
 */
function bpi_push_form($form, $form_state, $nid) {
  $node_title = '';
  if (!empty($nid)) {
    $node = node_load($nid);
    $node_title = $node->title;
  }

  $form['bpi_push_nid'] = array(
    '#type' => 'hidden',
    '#value' => isset($nid) ? $nid : 0,
  );

  $dictionaries = bpi_get_bpi_dictionaries();

  $categories = array_values($dictionaries['category']);
  $form['bpi_push_category'] = array(
    '#type' => 'select',
    '#title' => t('Category'),
    '#options' => array_combine($categories, $categories),
    '#default_value' => ',',
  );

  $audiences = array_values($dictionaries['audience']);
  $form['bpi_push_audience'] = array(
    '#type' => 'select',
    '#title' => t('Audience'),
    '#options' => array_combine($audiences, $audiences),
    '#default_value' => ',',
  );

  $form['bpi_push_images'] = array(
    '#type' => 'checkbox',
    '#title' => t('Push with images'),
  );

  $form['bpi_push_ccl'] = array(
    '#type' => 'checkbox',
    '#title' => t('I want be anonymous'),
    '#default_value' => FALSE,
  );

  $form['bpi_push_refs'] = array(
    '#type' => 'checkbox',
    '#title' => t('Push with references'),
    '#description' => t('Note that posts with the katalog keyword will not be pushed.'),
    '#default_value' => TRUE,
  );

  $form['bpi_push_editable'] = array(
    '#type' => 'checkbox',
    '#title' => t('Editable'),
    '#default_value' => '1',
  );

  return confirm_form(
    $form,
    t(
      'Are you sure u want to push content <strong>%title</strong> to BPI well?',
      array('%title' => $node_title)
    ),
    'admin/content'
  );
}

/**
 * Submit handler for the push node form.
 *
 * @see bpi_push_form()
 *
 * @param array $form
 *   Form structure.
 * @param array $form_state
 *   Form state values.
 *
 * @ingroup forms
 */
function bpi_push_form_submit($form, &$form_state) {
  $nid = $form_state['input']['bpi_push_nid'];
  $category = $form_state['input']['bpi_push_category'];
  $audience = $form_state['input']['bpi_push_audience'];
  $with_images = $form_state['input']['bpi_push_images'];
  $authorship = $form_state['input']['bpi_push_ccl'];
  $editable = $form_state['input']['bpi_push_editable'];
  $with_refs = $form_state['input']['bpi_push_refs'];

  if (empty($nid)) {
    return;
  }

  $node = node_load($nid);
  $bpi_content = bpi_convert_to_bpi($node, $category, $audience, $with_images, $authorship, $editable, $with_refs);

  try {
    $bpi = bpi_client_instance();
//    $push_result = $bpi->push($bpi_content)->getProperties();

    if (!empty($push_result['id'])) {
      db_merge('bpi_syndicated')
        ->fields(array(
          'nid' => $nid,
          'bid' => $push_result['id'],
          'status' => BPI_PUSHED,
          'timestamp' => time(),
        ))
        ->condition('nid', $nid, '=')
        ->execute();

      drupal_set_message(t('Node %title was successuflly pushed to BPI well.', array('%title' => $node->title)));
    }
  }
  catch (Exception $exception) {
    bpi_error_message($exception, 'error');
  }
}

/**
 * AJAX callback for the push button in bpi push node form.
 *
 * @see bpi_push_form()
 *
 * @param array $form
 *   Form structure.
 * @param array $form_state
 *   Form state values.
 *
 * @return array
 *   A set of ajax commands.
 *
 * @ingroup forms
 */
function bpi_push_action_ajax_callback($form, &$form_state) {
  $response = array(
    '#type' => 'ajax',
    '#commands' => array(),
  );

  $html = theme('status_messages');

  $response['#commands'][] = ajax_command_ding_popup(
    'bpi-push',
    t('Push to BPI'),
    $html
  );

  return $response;
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

  // Find the references to the ting date well.
  $materials_drupal = array();
  if ($with_refs) {
    $materials_map = field_view_field('node', $node, variable_get('bpi_field_materials', ''));
    if (isset($materials_map['#items'])) {
      foreach ($materials_map['#items'] as $key => $value) {
        if (!empty($materials_map[$key]['#object'])) {
          $ting_entity = $materials_map[$key]['#object'];
          $id = $ting_entity->ding_entity_id;

          // Filter out id's with "katalog" PID, as they only makes sens on
          // current site.
          if (!preg_match('/katalog/', $id)) {
            $materials_drupal[] = $id;
          }
        }
      }
    }
  }

  if (!empty($body_field) && isset($body_field['#items'][0]['safe_value'])) {
    $body = $body_field['#items'][0]['safe_value'];
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
