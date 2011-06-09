<?php

/**
 * Plugins are described by creating a $plugin array which will be used
 * by the system that includes this file.
 */
$plugin = array(
  'title' => t('User reservation list'),
  'description' => t('The current reservations for a user'),
  'single' => TRUE,
  'content_types' => array('list'),
  // 'render callback' => 'ding_reservation_list_content_type_render',
  'required context' => new ctools_context_required(t('User'), 'user'),
  'category' => t('User'),
);

/**
 * Render the block
 */
function ding_reservation_list_content_type_render($subtype, $conf, $panel_args, $context) {
  $account = isset($context->data) ? $context->data : NULL;
  $items = array();

  $block = new stdClass();
  $block->module = 'ding_reservation';
  $block->delta = 'list';
  $block->title = t('Reservation list');

  $list = ding_provider_invoke_page('reservation', 'list', $account);

  $ids = array();
  foreach ($list as $item) {
    $ids[] = $item->ding_entity_id;
  }
  // Preload all ting objects.
  ting_object_load_multiple($ids);

  $block->content = count($list) == TRUE ? ding_provider_get_form('ding_reservation_list_form', $list) : t('No reservations');
  return $block;
}

/**
 * Adding the admin form, to be able to control the required context
 */
function ding_reservation_list_content_type_edit_form($form, &$form_state) {
  return $form;
}

/**
 * Implements a drupal form, which show a list of reservations
 */
function ding_reservation_list_form($form, &$form_state, $items = array()) {
  foreach ($items as $id => $item) {
    $title = t('@title by @author', array('@title' => $item->title, '@author' => $item->creator));
    $checkboxes[$item->id] = l($title, 'ting/object/' . $item->ding_entity_id);
  }
  $form['reservations'] = array(
    '#type' => 'checkboxes',
    '#options' => $checkboxes,
  );
  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Submit reservations'),
  );
  return $form;
}

/**
 * Validate function for the form.
 */
function ding_reservation_list_form_validate($form, &$form_state) { }

/**
 * Submit handler for the form.
 */
function ding_reservation_list_form_submit($form, &$form_state) {
  global $user;
  foreach ($form_state['values']['reservations'] as $key => $entity_id) {
    if ($key == $entity_id) {
      ding_provider_invoke('reservation', 'delete', $user, $entity_id);
    }
  }
}
