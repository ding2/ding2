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

  switch ($conf['reservation_type_list']) {
    case 'ready_for_pickup':
      $block->title = t('Reservations ready for pickup');
    break;
    default:
    case 'not_ready_for_pickup':
      $block->title = t('Reservations');
    break;
  }
  
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
        'pickup_branch' => t('Pickup branch'),
        'operations' => '',
      );
      uasort($items, 'ding_reservation_sort_queue_by_pickup_date');
    break;
    case 'not_ready_for_pickup':
      $header = array(
        'title' => t('Title'),
        'created' => t('Created date'),
        'expiry' => t('Expiry date'),
        'pickup_branch' => t('Pickup branch'),
        'queue_number' => t('Queue number'),
        'operations' => '',
      );
      uasort($items, 'ding_reservation_sort_queue_by_queue_number');
    break;
  }
  foreach ($items as $id => $item) {
    $entity = $item->entity;
    $pickup_branch = ding_provider_invoke('reservation', 'branch_name', $item->pickup_branch_id);
    switch ($type) {
    case 'ready_for_pickup':
      $options[$item->id] = array(
        'title' => array(
          'data' => array($entity ? ting_object_view($entity, 'user_list') : array('#markup' => $item->display_name)),
          'class' => 'title',
        ),
        'created' => array(
          'data' => $item->created ? format_date(strtotime(check_plain($item->created)), 'date_only') : '',
          'class' => 'created-date',
        ),
        'pickup_date' => array(
          'data' => $item->pickup_date ? format_date(strtotime(check_plain($item->pickup_date)), 'date_only' ) : '',
          'class' => 'pickup-date',
        ),
        'pickup_branch' => array(
          'data' => $pickup_branch ? check_plain($pickup_branch) : '',
          'class' => 'pickup-branch',
        ),
        'operations' => array(
          'data' =>  array(
            '#type' => 'submit',
            '#submit' => array('ding_reservation_reservations_delete_submit'),
            '#reservation_id' => $item->id,
            '#name' => 'delete-' . $item->id, // Need this for formAPI can tell buttons apart
            '#value' => t('Delete'),
            '#options' => array('query' => $destination),
          ),
          'class' => 'operations',
        ),
      );
      if ($item->order_id) {
        $options[$item->id]['title']['data'][] = array(
          '#type' => 'markup',
          '#prefix' => '<p class="order-id">',
          '#markup' => t('(Material no. @mat_no)', array('@mat_no' => check_plain($item->order_id))),
          '#suffix' => '</p>',
        );
      }
      $form['reservations'] = array(
        '#type' => 'tableselect_form',
        '#header' => $header,
        '#options' => $options,
        '#empty' => t('No reservations ready for pickup'),
      );
      break;
    case 'not_ready_for_pickup':
      $options[$item->id] = array(
        'title' => array(
          'data' => $entity ? ting_object_view($entity, 'user_list') : array('#markup' => $item->display_name),
          'class' => 'title',
        ),
        'created' => array(
          'data' => $item->created ? format_date(strtotime(check_plain($item->created)), 'date_only') : '',
          'class' => 'created-date',
        ),
        'expiry' => array(
          'data' => $item->created ? format_date(strtotime(check_plain($item->expiry)), 'date_only') : '',
          'class' => 'expire-date',
        ),
        'pickup_branch' => array(
          'data' => $pickup_branch ? check_plain($pickup_branch) : '',
          'class' => 'pickup-branch',
        ),
        'queue_number' => array(
          'data' => $item->queue_number ? check_plain($item->queue_number) : '',
          'class' => 'queue-number',
        ),
        'operations' => array(
          'data' =>  array(
            '#type' => 'submit',
            '#submit' => array('ding_reservation_reservations_delete_submit'),
            '#reservation_id' => $item->id,
            '#name' => 'delete-' . $item->id, // Need this for formAPI can tell buttons apart
            '#value' => t('Delete'),
            '#options' => array('query' => $destination),
          ),
          'class' => 'operations',
        ),
      );
      $form['reservations'] = array(
        '#type' => 'tableselect_form',
        '#header' => $header,
        '#options' => $options,
        '#empty' => t('No Reservations'),
      );
      break;
    }
  }

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

function ding_reservation_reservations_delete_submit($form, &$form_state) {
  form_set_value($form['reservations'], array($form_state['triggering_element']['#reservation_id'] => $form_state['triggering_element']['#reservation_id']), $form_state);
  ding_reservation_reservations_form_submit($form, $form_state);
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
