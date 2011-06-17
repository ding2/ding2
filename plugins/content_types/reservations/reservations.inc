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
function ding_reservation_reservations_content_type_render($subtype, $conf, $panel_args, $context) {
  $account = isset($context->data) ? $context->data : NULL;
  $items = array();

  $block = new stdClass();
  $block->module = 'ding_reservation';
  $block->delta = 'reservations';
  $block->title = t('Reservation list');

  $list = ding_provider_invoke_page('reservation', 'list', $account);

  $ids = array();
  foreach ($list as $item) {
    $ids[] = $item->ding_entity_id;
  }
  // Preload all ting objects.
  // @todo: this should really be ding_entity_load_multiple()
  ting_object_load_multiple($ids);

  $block->content = count($list) == TRUE ? ding_provider_get_form('ding_reservation_reservations_form', $list) : t('No reservations');
  return $block;
}

/**
 * Adding the admin form, to be able to control the required context
 */
function ding_reservation_reservations_content_type_edit_form($form, &$form_state) {
  return $form;
}

/**
 * Implements a drupal form, which show a list of reservations
 */
function ding_reservation_reservations_form($form, &$form_state, $items = array()) {
  $options = array();
  $destination = drupal_get_destination();
  $header = array(
    'title' => t('Title'),
    'created' => t('Created date'),
    'expiry' => t('Expiry date'),
    'pickup_branch_id' => t('Pickup branch'),
    'queue_number' => t('Queue number'),
    'operations' => '',
  );

  uasort($items, 'ding_reservation_sort_queue');

  foreach ($items as $id => $item) {
    $options[$item->id] = array(
      'title' => array(
        'data' => isset($entity) ? ting_object_view($item->entity, 'user_list') : array('#markup' => $item->display_name),
      ),
      'created' => check_plain($item->created),
      'expiry' => check_plain($item->expiry),
      'pickup_branch_id' => check_plain($item->pickup_branch_id),
      'queue_number' => check_plain($item->queue_number),
      'operations' => array(
        'data' =>  array(
          '#type' => 'button',
          '#value' => t('Delete'),
          '#options' => array('query' => $destination),
        ),
      ),
    );
  }

  $form['reservations'] = array(
    '#type' => 'tableselect',
    '#header' => $header,
    '#options' => $options,
    '#empty' => t('No Reservations'),
  );

   $form['submit'] = array(
     '#type' => 'submit',
     '#value' => t('Delete reservations'),
   );

  $form['update'] = array(
    '#type' => 'submit',
    '#submit' => array('ding_reservation_update_reservation_form'),
    '#value' => t('Update reservations'),
    '#ajax' => array(
      'callback' => 'ding_reservation_update_reservation_callback',
      'wrapper' => 'ding-reservation-reservations-form',
    ),
  );

  return $form;
}


/**
 * Submit handler for the form.
 */
function ding_reservation_reservations_form_submit($form, &$form_state) {
  global $user;
  foreach ($form_state['values']['reservations'] as $key => $entity_id) {
    if ($key == $entity_id) {
      ding_provider_invoke('reservation', 'delete', $user, $entity_id);
    }
  }
}
