<?php
/**
 * @file
 * This panels content type defines panes that can be used to add reservation
 * lists to the user page.
 */

$plugin = array(
  'title' => t('User reservation list'),
  'description' => t('The current reservations for a user'),
  'single' => TRUE,
  'content_types' => array('list'),
  'required context' => new ctools_context_required(t('User'), 'user'),
  'category' => t('User'),
);

/**
 * Render the block
 */
function ding_reservation_reservations_content_type_render($subtype, $conf, $panel_args, $context) {
  static $preload_reservations = TRUE;
  $account = isset($context->data) ? $context->data : NULL;
  $preload_ids = array();
  $reservation_list = array();

  // Defined the return block.
  $block = new stdClass();
  $block->module = 'ding_reservation';
  $block->delta  = 'reservations';

  // Set title and get the form id base on the list type.
  switch ($conf['reservation_type_list']) {
    case 'ready_for_pickup':
      $block->title = t('Reservations ready for pickup');
      $block->content = t('There are no reservations ready for pickup.');
      $form_id = 'ding_reservation_reservations_ready_form';
      break;

    case 'interlibrary_loans':
      $block->title = t('Interlibrary loans');
      $block->content = t('There are no interlibrary loans.');
      $form_id = 'ding_reservation_reservations_ill';

    default:
      $block->title = t('Reservations');
      $block->content = t('There are no reservations.');
      $form_id = 'ding_reservation_reservations_notready_form';
      break;
  }

  // Get the lists
  $items = ding_provider_invoke_page('reservation', 'list', $account);
  foreach ($items as $item) {
    if (isset($item->ding_entity_id)) {
      $preload_ids[] = $item->ding_entity_id;
    }
    if (isset($conf['reservation_type_list'])) {
      if (($conf['reservation_type_list'] == 'ready_for_pickup' && $item->ready_for_pickup === 1) ||
          ($conf['reservation_type_list'] == 'not_ready_for_pickup' && $item->ready_for_pickup === 0) ||
          ($conf['reservation_type_list'] == 'interlibrary_loans' && isset($item->ill_status))) {
        $reservation_list[] = $item;
      }
    }
  }
  // Preload all ting objects.
  if ($preload_reservations) {
    ding_entity_load_multiple($preload_ids);
    $preload_reservations = FALSE;
  }

  // Change the default block content, if the list is not empty
  if (!empty($reservation_list)) {
    $block->content = ding_provider_get_form($form_id, $reservation_list, $conf['reservation_type_list']);
  }

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
      'ready_for_pickup' => t('Ready for pickup'),
      'interlibrary_loans' => t('Interlibrary loans'),
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
