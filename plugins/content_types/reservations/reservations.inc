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
 * Render the block.
 */
function ding_reservation_reservations_content_type_render($subtype, $conf, $panel_args, $context) {
  $account = isset($context->data) ? $context->data : NULL;

  // Defined the return block.
  $block = new stdClass();
  $block->title = t('My reservations');
  $block->module = 'ding_reservation';
  $block->delta  = 'reservations';

  // Get configuration for this pane and set empty text.
  $types = array_filter($conf['reservation_type_list']);
  $block->content = t($conf['reservation_empty_text']);
  $form_id = $conf['reservation_form_id'];

  $content = array();
  if (module_exists('ding_session_cache')) {
    $content = ding_session_cache_get('ding_reservation', 'reservations');
  }

  if (empty($content) || !isset($content[$form_id])) {
    // Get the reservations lists.
    $reservations = ding_provider_invoke_page('reservation', 'list', $account);

    // Filter items base on configuration and pre-load ting entities.
    $preloaded_reservations = &drupal_static(__FUNCTION__, array());
    $items = array();
    foreach ($types as $type) {
      // Try to pre-load ting entities, if not already loaded.
      if (!isset($preloaded_reservations[$type])) {
        $preload_ids = array();
        foreach ($reservations[$type] as $item) {
          if (isset($item->ding_entity_id)) {
            $preload_ids[] = $item->ding_entity_id;
          }
        }

        // Pre-load all ting entities.
        if (!empty($preload_ids)) {
          ding_entity_load_multiple($preload_ids);
        }

        // Set this list type as preloaded.
        $preloaded_reservations[$type] = TRUE;
      }

      // Sort the reservations based on type.
      $sorted = array();
      switch ($type) {
        case DING_RESERVATION_READY:
          $sorted = $reservations[$type];
          uasort($sorted, 'ding_reservation_sort_queue_by_pickup_date');
          break;

        case DING_RESERVATION_NOT_READY:
          $sorted = $reservations[$type];
          uasort($sorted, 'ding_reservation_sort_queue_by_queue_number');
          break;

        case DING_RESERVATION_INTERLIBRARY_LOANS:
          $sorted = $reservations[$type];
          break;
      }

      // Add the current type to the items we want.
      $items += $sorted;
    }

    // Add the pre-load entity to each loan (side effect of getting the entity).
    foreach ($items as $id => &$item) {
      $item->entity;
    }

    $content[$form_id] = $items;

    if (module_exists('ding_session_cache')) {
      ding_session_cache_set('ding_reservation', 'reservations', $content);
    }
  }

  // Build block content.
  if (!empty($content[$form_id])) {
    if (count($types) > 1) {
      // If more than one type is selected we will fallback to the most generic
      // form type.
      $block->content = ding_provider_get_form($form_id, $content[$form_id], DING_RESERVATION_NOT_READY, $conf);
    }
    else {
      $block->content = ding_provider_get_form($form_id, $content[$form_id], array_shift($types), $conf);
    }
  }

  return $block;
}

/**
 * Adding the admin form, to be able to control the required context.
 */
function ding_reservation_reservations_content_type_edit_form($form, &$form_state) {
  $conf = $form_state['conf'];
  $form['reservation_type_list'] = array(
    '#type' => 'checkboxes',
    '#title' => t('Reservation list type(s)'),
    '#options' => array(
      DING_RESERVATION_NOT_READY => t('Not ready for pickup'),
      DING_RESERVATION_READY => t('Ready for pickup'),
      DING_RESERVATION_INTERLIBRARY_LOANS => t('Interlibrary loans'),
    ),
    '#default_value' => !empty($conf['reservation_type_list']) ? $conf['reservation_type_list'] : NULL,
  );

  $form['reservation_title'] = array(
    '#type' => 'textfield',
    '#title' => t('List title'),
    '#default_value' => !empty($conf['reservation_title']) ? $conf['reservation_title'] : 'Reservations',
  );

  $form['reservation_empty_text'] = array(
    '#type' => 'textfield',
    '#title' => t('Empty text'),
    '#default_value' => !empty($conf['reservation_empty_text']) ? $conf['reservation_empty_text'] : 'There are no reservations.',
  );

  $form['reservation_form_id'] = array(
    '#type' => 'select',
    '#title' => t('Form to user for reservations'),
    '#options' => array(
      'ding_reservation_reservations_notready_form' => t('Reservation form'),
      'ding_reservation_reservations_ready_form' => t('Reservations ready form'),
      'ding_reservation_reservations_ill' => t('Interlibrary reservation form'),
    ),
    '#default_value' => !empty($conf['reservation_form_id']) ? $conf['reservation_form_id'] : 'ding_reservation_reservations_notready_form',
  );
  return $form;
}

/**
 * Submit handler for the admin form.
 */
function ding_reservation_reservations_content_type_edit_form_submit(&$form, &$form_state) {
  foreach (element_children($form) as $key) {
    if (!empty($form_state['values'][$key])) {
      $form_state['conf'][$key] = $form_state['values'][$key];
    }
  }
}

/**
 * Returns the administrative title.
 */
function ding_reservation_reservations_content_type_admin_title($subtype, $conf) {
  $types = implode(', ', array_filter($conf['reservation_type_list']));
  return 'Reservations (' . $types . ')';
}

/**
 * Callback function to sort array by pickup date.
 */
function ding_reservation_sort_queue_by_pickup_date($a, $b) {
  if ($a->pickup_date == $b->pickup_date) {
    return 0;
  }
  return ($a->pickup_date < $b->pickup_date) ? -1 : 1;
}

/**
 * Callback function for sorting loans by queue_number.
 */
function ding_reservation_sort_queue_by_queue_number($a, $b) {
  if ($a->queue_number == $b->queue_number) {
    return 0;
  }
  return ($a->queue_number < $b->queue_number) ? -1 : 1;
}
