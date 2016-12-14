<?php

/**
 * @file
 * Ding Serendipity CTools plugin file.
 */

$plugin = array(
  'title' => t('Ding Entity Rating: Popular'),
  'description' => t('Popular objects, from openlist data.'),
  'single' => TRUE,
  'category' => t('Ding!'),
);

/**
 * Implements hook_content_type_render().
 */
function ding_entity_rating_popular_content_type_render($subtype, $conf, $panel_args, $context) {
  // Only show on front if serendipity is enabled for the frontpage.
  // See ding_frontpage config at /admin/config/ding/frontend.
  if (drupal_is_front_page() && !variable_get('ding_entity_rating_popular_on_frontpage', TRUE)) {
    return;
  }

  $block = new stdClass();

  $month = $conf['month'];
  if (empty($month)) {
    $month = date('Ym');
  }
  else {
    $month = str_replace('-', '', $month);
  }

  $libcode = $conf['libcode'];
  if ($libcode !== FALSE) {
    $libcode = variable_get('ting_library_code', '');
  }

  $openlist_items = array();
  try {
    $openlist_items = ding_provider_invoke('openlist', 'call_module', 'TingObjectRating', 'getPopular', array(
      $month,
      $libcode,
      10,
    ));
  }
  catch (Exception $e) {
    watchdog_exception('ding_entity_rating', $e);
  }

  if (empty($openlist_items)) {
    return FALSE;
  }

  $keys = array();
  foreach ($openlist_items as $openlist_item) {
    $id = ding_list_convert_cql($openlist_item['object_id']);
    $keys[] = $id;
  }

  $keys = ding_serendipity_validate_materials($keys);
  
  $result = array();
  foreach ($keys as $key) {
    $obj = ding_entity_load($key, 'ting_object');

    $result[] = ting_object_view($obj, 'compact');
  }

  $block->content = theme('ting_carousel', array('objects' => $result));

  return $block;
}

/**
 * Implements hook_content_type_edit_form().
 */
function ding_entity_rating_popular_content_type_edit_form($form, &$form_state) {
  $form['libcode'] = array(
    '#type' => 'checkbox',
    '#title' => t('Use library code'),
    '#default_value' => $form_state['conf']['libcode'],
  );

  $form['month'] = array(
    '#type' => 'textfield',
    '#title' => t('Month'),
    '#description' => t('It is important to use YYYY-MM as format, like @example. If not filled out the system will use current month.', array('@example' => date('Y-m'))),
    '#default_value' => $form_state['conf']['month'],
  );

  return $form;
}

/**
 * Implements hook_content_type_edit_form_validate().
 *
 * Validates the entered date to correct format.
 */
function ding_entity_rating_popular_content_type_edit_form_validate($form, &$form_state) {
  if (empty($form_state['values']['month'])) {
    return;
  }

  $date = DateTime::createFromFormat('Y-m', $form_state['values']['month']);
  $error = !$date || $date->format('Y-m') != $form_state['values']['month'];

  if ($error) {
    form_error($form['month'], t('Please make sure you used the correct date format.'));
  }
}

/**
 * Implements hook_content_type_edit_form_submit().
 */
function ding_entity_rating_popular_content_type_edit_form_submit($form, &$form_state) {
  $form_state['conf']['month'] = $form_state['values']['month'];
  $form_state['conf']['libcode'] = $form_state['values']['libcode'];
}
