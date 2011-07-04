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
  'required context' => new ctools_context_required(t('User'), 'user'),
  'category' => t('User'),
);

/*
 * Additional dateformat, used by format_date().
 */
variable_set('date_format_ding_reservation_short', 'd.m.Y');

/**
 * Render the block
 */
function ding_reservation_reservations_content_type_render($subtype, $conf, $panel_args, $context) {
  $preload_reservations = &drupal_static('ids');
  $account              = isset($context->data) ? $context->data : NULL;
  $preload_ids          = array();
  $items                = array();
  $reservation_list     = array();

  $block         = new stdClass();
  $block->module = 'ding_reservation';
  $block->delta  = 'reservations';
  $block->title  = t('Reservation list');

  $list = ding_provider_invoke_page('reservation', 'list', $account);

  foreach ($list as $item) {
    $preload_ids[] = $item->ding_entity_id;
    if (isset($conf['reservation_type_list'])) {
      if ($conf['reservation_type_list'] == 'ready_for_pickup' && $item->ready_for_pickup == TRUE || $conf['reservation_type_list'] == 'not_ready_for_pickup' && $item->ready_for_pickup == FALSE) {
        $reservation_list[] = $item;
      }
    }
  }
  // Preload all ting objects.
  if ($preload_reservations['ids'] == FALSE) {
    ding_entity_load_multiple($preload_ids);
    $preload_reservations['ids'] = TRUE;
  }

  $block->content = count($reservation_list) == TRUE ? ding_provider_get_form('ding_reservation_reservations_form', $reservation_list, $conf['reservation_type_list']) : t('No reservations');
  return $block;
}

/**
 * Adding the admin form, to be able to control the required context
 */
function ding_reservation_reservations_content_type_edit_form($form, &$form_state) {
  $conf = $form_state['conf'];
  $form['reservation_type_list'] = array(
    '#type'    => 'radios',
    '#title'   => t('Reservation list type'),
    '#options' => array(
      'not_ready_for_pickup' => t('Not ready for pickup'),
      'ready_for_pickup'     => t('Ready for pickup'),
    ),
    '#default_value' => !empty($conf['reservation_type_list']) ? $conf['reservation_type_list'] : NULL,
  );
  return $form;
}

/**
 * Submit handler for the admin form
 */
function ding_reservation_reservations_content_type_edit_form_submit(&$form, &$form_state) {
  foreach (element_children($form) as $key) {
    if (!empty($form_state['values'][$key])) {
      $form_state['conf'][$key] = $form_state['values'][$key];
    }
  }
}

/**
 * Implements a drupal form, which show a list of reservations
 */
function ding_reservation_reservations_form($form, &$form_state, $items = array(), $type = 'not_ready_for_pickup') {
  $options = array();
  $destination = drupal_get_destination();
  switch ($type) {
  case 'ready_for_pickup':
    $header = array(
      'title' => t('Title'),
      'created' => t('Created date'),
      'pickup_date' => t('Pickup date'),
      'pickup_branch_id' => t('Pickup branch'),
      'operations' => '',
    );
    uasort($items, 'ding_reservation_sort_queue_by_pickup_date');
    break;
  case 'not_ready_for_pickup':
    $header = array(
      'title' => t('Title'),
      'created' => t('Created date'),
      'expiry' => t('Expiry date'),
      'pickup_branch_id' => t('Pickup branch'),
      'queue_number' => t('Queue number'),
      'operations' => '',
    );
    uasort($items, 'ding_reservation_sort_queue_by_queue_number');
    break;
  }


  foreach ($items as $id => $item) {
    $entity = $item->entity;
    switch ($type) {
    case 'ready_for_pickup':
      $options[$item->id] = array(
        'title' => array(
          'data' => array(
            isset($entity) ? ting_object_view($entity, 'user_list') : array('#markup' => $item->display_name),
            array(
              '#type' => 'markup',
              '#prefix' => '<p class="order-id">',
              '#markup' => t('(Material no. @mat_no)', array('@mat_no' => check_plain($item->order_id))),
              '#suffix' => '</p>',
            ),
          ),
          'class' => 'title',
        ),
        'created' => array(
          'data' => format_date(strtotime(check_plain($item->created)), 'ding_reservation_short'),
          'class' => 'created-date',
        ),
        'pickup_date' => array(
          'data' => format_date(strtotime(check_plain($item->pickup_date)), 'ding_reservation_short' ),
          'class' => 'pickup-date',
        ),
        'pickup_branch_id' => array(
          'data' => check_plain($item->pickup_branch_id),
          'class' => 'pickup-branch',
        ),
        'operations' => array(
          'data' =>  array(
            '#type' => 'button',
            '#value' => t('Delete'),
            '#options' => array('query' => $destination),
          ),
          'class' => 'operations',
        ),
      );
      break;
    case 'not_ready_for_pickup':
      $options[$item->id] = array(
        'title' => array(
          'data' => isset($entity) ? ting_object_view($entity, 'user_list') : array('#markup' => $item->display_name),
          'class' => 'title',
        ),
        'created' => array(
          'data' => format_date(strtotime(check_plain($item->created)), 'ding_reservation_short'),
          'class' => 'created-date',
        ),
        'expiry' => array(
          'data' => format_date(strtotime(check_plain($item->expiry)), 'ding_reservation_short'),
          'class' => 'expire-date',
        ),
        'pickup_branch_id' => array(
          'data' => check_plain($item->pickup_branch_id),
          'class' => 'pickup-branch',
        ),
        'queue_number' => array(
          'data' => check_plain($item->queue_number),
          'class' => 'queue-number',
        ),
        'operations' => array(
          'data' =>  array(
            '#type' => 'button',
            '#value' => t('Delete'),
            '#options' => array('query' => $destination),
          ),
          'class' => 'operations',
        ),
      );
      break;
    }
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

  if ($type == 'not_ready_for_pickup') {
    $form['update'] = array(
      '#type' => 'submit',
      '#submit' => array('ding_reservation_update_reservation_form'),
      '#value' => t('Update reservations'),
      '#ajax' => array(
        'callback' => 'ding_reservation_update_reservation_callback',
        'wrapper' => 'ding-reservation-reservations-form',
      ),
    );
  }

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
