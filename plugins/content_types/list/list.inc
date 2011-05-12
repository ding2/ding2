<?php

/**
 * Plugins are described by creating a $plugin array which will be used
 * by the system that includes this file.
 */
$plugin = array(
  'title' => t('Reservation List'),
  'description' => t('Users reservation list'),
  'single' => TRUE,
  'content_types' => array('list'),
  'render callback' => 'list_content_type_render',
  'required context' => new ctools_context_required(t('User'), 'user'),
  'category' => t('User'),
);

/**
 * Render the block
 */
function list_content_type_render($subtype, $conf, $panel_args, $context) {
  $account = isset($context->data) ? $context->data : NULL;
  $items = array();

  $block = new stdClass();
  $block->module = 'ding_reservation';
  $block->delta = 'list';
  $block->title = t('Reservation list');

  $list = ding_provider_invoke('reservation', 'list', $account);
  foreach ($list as $item) {
    $items[$item->id] = ting_object_load(variable_get('ting_agency', 0) . ':' . $item->ding_entity_id);
  }
  $block->content = count($items) == TRUE ? drupal_get_form('ding_reservation_list_form', $items) : t('No reservations');
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
  foreach ($items as $entity_id => $item) {
    $title = t('@title by @author', array('@title' => $item->getTitle(), '@author' => implode(', ', $item->getCreators())));
    $checkboxes[$entity_id] = l($title, 'ting/object/' . $item->getId());
  }
  $form['reservations'] = array(
    '#type' => 'checkboxes',
    '#options' => $checkboxes,
    '#default_value' => FALSE,
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
  drupal_goto('user');
}
