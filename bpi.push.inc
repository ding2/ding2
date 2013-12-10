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
 * @return Array/string
 *   Ajax command set in case of ajax request, push content page
 *   markup otherwise.
 */
function bpi_push_action($type, $nid) {
  $is_ajax = ($type == 'ajax') ? TRUE : FALSE;

  if (empty($nid)) {
    return;
  }

  // TODO There are access checks here and in the hook_menu() definition. Why not keep it all in hook_menu or here?
  if (!bpi_ability($nid, 'push')) {
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
 * @return array
 *   Form structure.
 *
 */
//TODO Please prefix all function names with the module name to avoid name clashes.
function http_bpi_push_action($nid) {
  return drupal_get_form('http_bpi_push_action_form', $nid);
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
 * @return array
 *   Form structure.
 *
 * @ingroup forms
 */
//TODO Please prefix all function names with the module name to avoid name clashes.
function http_bpi_push_action_form($form, &$form_state, $nid) {
  $node_title = '';
  // TODO If $nid is empty this seems like a poor fix.
  if (!empty($nid)) {
    $node = node_load($nid);
    $node_title = $node->title;
  }

  $form['bpi_push_nid'] = array(
    // TODO Why not use value here?
    '#type' => 'hidden',
    '#value' => isset($nid) ? $nid : 0,
  );

  $dictionaries = bpi_get_bpi_dictionaries();

  $categories = array_values($dictionaries['category']);
  $form['bpi_push_category'] = array(
    '#type' => 'select',
    '#title' => t('Category'),
    '#options' => array_combine($categories, $categories),
    // TODO: There is no #descroption here. Is this intentional?
    '#default_value' => ','
  );

  $audiences = array_values($dictionaries['audience']);
  $form['bpi_push_audience'] = array(
    '#type' => 'select',
    '#title' => t('Audience'),
    '#options' => array_combine($audiences, $audiences),
    // TODO: There is no #descroption here. Is this intentional?
    '#default_value' => ','
  );

  $form['bpi_push_images'] = array(
    '#type' => 'checkbox',
    '#title' => t('Push with images'),
    // TODO: There is no #descroption here. Is this intentional?
  );

  $form['bpi_push_ccl'] = array(
    '#type' => 'checkbox',
    '#title' => t('I want be anonymous'),
    // TODO: There is no #descroption here. Is this intentional?
    '#default_value' => FALSE,
  );

  $form['bpi_push_editable'] = array(
    '#type' => 'checkbox',
    '#title' => t('Editable'),
    // TODO: There is no #descroption here. Is this intentional?
    '#default_value' => '1',
  );

  return confirm_form(
    $form,
    // TODO Why include strong tag? %title should already add <em>.
    t('Are you sure u want to push content <strong>%title</strong> to BPI well?', array('%title' => $node_title)),
    'admin/content'
  );
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
//TODO Please prefix all function names with the module name to avoid name clashes.
function http_bpi_push_action_form_submit($form, &$form_state) {
  $nid = $form_state['input']['bpi_push_nid'];
  $category = $form_state['input']['bpi_push_category'];
  $audience = $form_state['input']['bpi_push_audience'];
  $with_images = $form_state['input']['bpi_push_images'];
  $authorship = $form_state['input']['bpi_push_ccl'];
  $editable = $form_state['input']['bpi_push_editable'];
  if (empty($nid)) {
    return;
  }
  $node = node_load($nid);
  $bpi_content = bpi_convert_to_bpi($node, $category, $audience, $with_images, $authorship, $editable);

  try {
    $bpi = bpi_client_instance();
    $push_result = $bpi->push($bpi_content)->getProperties();

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
    // TODO Using $base_url should not be necessary here.
    global $base_url;
    drupal_goto($base_url . '/admin/bpi');
  }
  catch (Exception $e) {
    watchdog_exception('bpi', $e);
    $msg = t('Error occurred when pushing %title to BPI well. Check reports for more information.', array('%title' => $node->title));
    drupal_set_message($msg, 'error');
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
 * @return array
 *   Form structure.
 *
 * @ingroup forms
 */
// TODO There seems to be a lot of duplicated code between this function and http_bpi_push_action_form().
// Can this be refactored?
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
    '#default_value' => ','
  );

  $audiences = array_values($dictionaries['audience']);
  $form['bpi_push_audience'] = array(
    '#type' => 'select',
    '#title' => t('Audience'),
    '#options' => array_combine($audiences, $audiences),
    '#default_value' => ','
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
// TODO There seems to be a lot of duplicated code between this function and http_bpi_push_action_form_submit().
// Can this be refactored?
function bpi_push_form_submit($form, &$form_state) {
  $nid = $form_state['input']['bpi_push_nid'];
  $category = $form_state['input']['bpi_push_category'];
  $audience = $form_state['input']['bpi_push_audience'];
  $with_images = $form_state['input']['bpi_push_images'];
  $authorship = $form_state['input']['bpi_push_ccl'];
  $editable = $form_state['input']['bpi_push_editable'];

  if (empty($nid)) {
    return;
  }

  $node = node_load($nid);
  $bpi_content = bpi_convert_to_bpi($node, $category, $audience, $with_images, $authorship, $editable);

  try {
    $bpi = bpi_client_instance();
    $push_result = $bpi->push($bpi_content)->getProperties();

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
  catch (Exception $e) {
    watchdog_exception('bpi', $e);
    $msg = t('Error occured when pushing %title to BPI well. Check reports for more information.', array('%title' => $node->title));
    drupal_set_message($msg, 'error');
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
 * @return array
 *   A set of ajax commands.
 *
 * @ingroup forms
 */
function bpi_push_action_ajax_callback($form, &$form_state) {
  $response = array(
    '#type' => 'ajax',
    '#commands' => array()
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
 * Convert node object to bpi-related array structure,
 * suitable for pushing to the well.
 *
 * @param stdClass $node
 *   Node object being processed.
 * @param string $category
 *   Selected category at the BPI side.
 * @param string $audience
 *   Selected audience at the BPI side.
 *
 * @return array
 *   An array of node values, used by the BPI ws.
 */
function bpi_convert_to_bpi($node, $category, $audience, $with_images = FALSE, $authorship = FALSE, $editable = 1) {
  $bpi_content = array();

  // TODO Why would node not be a standard class this deep down?
  if ($node instanceof stdClass) {
    // TODO This code seems messy to me. The structure is set some simple values to BPI object , set some user values,
    // extract a lot of variables and field information, extract values for most fields, assign more values to BPI,
    // extract images and assign images to BPI. It would make more sense to me if the code dealt with one aspect all
    // the way from variable retrieval to BPI object value setting one at a time.
    $bpi_content['agency_id'] = variable_get('bpi_agency_id', '');
    $bpi_content['local_id'] = $node->nid;
    $bpi_content['bpi_id'] = isset($node->bpi_id) ? $node->bpi_id : NULL;
    $user = user_load($node->uid);
    // TODO Setting the name field for the user to the firstname of the BPI object is a start but seems a bit naive
    // If we have the persons full name, nickname etc. from a profile this is not added. How about adding an alter hook
    // allowing other modules to change the values before they are sent to BPI?
    $bpi_content['firstname'] = $user->name;
    $bpi_content['lastname'] = '';
    $bpi_content['title'] = $node->title;

    $teaser_map = variable_get('bpi_field_teaser', '');
    $body_map = variable_get('bpi_field_body', '');
    $materials_map = variable_get('bpi_field_materials', '');
    $materials_map = field_view_field('node', $node, $materials_map);
    $teaser_field = field_view_field('node', $node, $teaser_map);
    $body_field = field_view_field('node', $node, $body_map);
    $teaser = '';
    $body = '';

    // Whether the field is a textarea with summary, fetch the summary, if not -
    // fetch it's safe value.
    if (!empty($teaser_field) && isset($teaser_field['#items'][0]['safe_summary'])) {
      $teaser = $teaser_field['#items'][0]['safe_summary'];
    }
    elseif (isset($teaser_field['#items'][0]['safe_value'])) {
      $teaser = $teaser_field['#items'][0]['safe_value'];
    }

    $materials_drupal = array();
    foreach ($materials_map as $key => $value) {
      if (is_numeric($key)) {
        $record = $value['#object']->getRecord();
        $ac_identifier_array = array_shift(array_values($record['ac:identifier']));
        $parts = explode('|', $ac_identifier_array[0]);
        $materials_drupal[] = $parts[1] . ':' . $parts[0];
      }
    }

    if (!empty($body_field) && isset($body_field['#items'][0]['safe_value'])) {
      $body = $body_field['#items'][0]['safe_value'];
    }

    // Empty the teaser, if body and teaser are mapped to same fields, and the values
    // are identical.
    if ($teaser_map == $body_map && md5($teaser) == md5($body)) {
      $teaser  = '';
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
      $bpi_content['body'] = preg_replace('~(<p>)?<img.+?/>(</p>)?~is', '', $bpi_content['body']);
    }
  }

  // TODO No content has actually been pushed here. The watchdog statement seems misleading?
  watchdog(
    'bpi',
    'Pushed to server !content',
    array('!content' => '<pre>' . htmlspecialchars(print_r($bpi_content, TRUE)) . '</pre>'),
    WATCHDOG_DEBUG
  );

  return $bpi_content;
}

/**
 * Fetch image field types.
 *
 * @param string $bundle
 *   Node type.
 * @return array
 *   Array of field names which are actually image fields.
 */
function bpi_fetch_image_fields($bundle) {
  $potential_image_fields = array('image_image', 'media_generic');
  $field_instances = field_info_instances('node', (string)$bundle);

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
    watchdog('bpi', $e);
  }

  return $dictionaries;
}
