<?php
/**
 * @file
 * Field hook implementations.
 */

/**
 * Implements hook_field_info().
 */
function ding_place2book_field_info() {
  return array(
    'ding_p2b' => array(
      'label' => t('Place2book field'),
      'description' => t('Information about place2book ticket.'),
      'default_widget' => 'ding_p2b_widget_default',
      'default_formatter' => 'ding_p2b_formatter_default',
      'settings' => array(),
    ),
  );
}

/**
 * Implements hook_field_is_empty().
 */
function ding_place2book_field_is_empty($item, $field) {
  return FALSE;
}

/**
 * Implements hook_field_widget_info().
 */
function ding_place2book_field_widget_info() {
  return array(
    'ding_p2b_widget_default' => array(
      'label' => t('Default'),
      'field types' => array('ding_p2b'),
      'behaviors' => array(
        'multiple values' => FIELD_BEHAVIOR_CUSTOM,
        'default value' => FIELD_BEHAVIOR_CUSTOM,
      ),
    ),
  );
}

/**
 * Implements hook_field_widget_form().
 */
function ding_place2book_field_widget_form(&$form, &$form_state, $field, $instance, $langcode, $items, $delta, $element) {
  $event = $event_id = $event_maker_id = $synchronize = $prices = $meta_data = NULL;
  if (!empty($items)) {
    // If items is non-empty we might be on a node clone form.
    // See: ding_place2book_clone_node_alter()
    if (!empty($items[$delta]['do_clone'])) {
      $event = $items[$delta]['event_clone'];
      $meta_data = isset($event->meta_data) ? $event->meta_data : NULL;
      $prices = $items[$delta]['prices_clone'];
      $synchronize = $items[$delta]['synchronize'];
    }
    // Otherwise this an existing p2b-synced entity; try to fetch the event.
    else {
      list($event_id, $event_maker_id, $synchronize) = array_values(reset($items));
      if ($event = ding_place2book_get_event($event_maker_id, $event_id)) {
        $meta_data = isset($event->meta_data) ? $event->meta_data : NULL;
        $prices = $event->prices;
      }
    }
  }

  switch ($instance['widget']['type']) {
    case 'ding_p2b_widget_default':
      $element['place2book'] = array(
        '#type' => 'fieldset',
        '#title' => t('Place2Book'),
        '#description' => t('Information about event on Place2book service.'),
        '#collapsible' => TRUE,
        '#collapsed' => TRUE,
        '#tree' => TRUE,
      );

      // This setting determines whether the event should be synchronized with
      // p2b every time an administrator updates the entity from an entity form.
      $element['place2book']['synchronize'] = array(
        '#type' => 'checkbox',
        '#title' => t('Synchronize event with Place2book service'),
        '#description' => t('If checked, then event on Place2book will be updated with data from local event.'),
        '#default_value' => $synchronize !== NULL ? $synchronize : variable_get('ding_p2b_default_synchronize', FALSE),
      );

      // The value/presence of this element is what actually determines whether
      // an update will be performed if 'synchronize' above is selected. This is
      // to protect against unwanted/needed request against p2b API, when nodes
      // are updated programmatically or in a bulk operation from the UI. In
      // these cases it's almost never the intention to sync with p2b and it
      // will also result in potentially lots of un-needed separated requests
      // against p2b API. These requests would also generate errors since
      // required values like 'capacity' or 'address' is missing.
      // If the intention IS to update to events also, the caller would have to
      // supply the 'do_sync' setting itself on the p2b field on the entity
      // (together with the required fields).
      // From this field widget form, the event should be synchronized with p2b
      // every time (if synchronize is selected), so to ensure this we attach
      // the 'do_sync' setting here manually as an internal form value.
      $element['place2book']['do_sync'] = array(
        '#type' => 'value',
        '#value' => TRUE,
      );

      $element['place2book']['original_event'] = array(
        '#type' => 'value',
        '#value' => $event,
      );

      if (!empty($event)) {
        $begin_at = date('d/m/Y H:i:s', strtotime($event->begin_at));
        $end_at = date('d/m/Y H:i:s', strtotime($event->end_at));
        $element['place2book']['event_data'] = array(
          '#type' => 'container',
          '#states' => array(
            'visible' => array(
              ':input[name="field_place2book[und][place2book][synchronize]"]' => array('checked' => TRUE),
            ),
          ),
        );

        $short = check_plain($event->description_short);
        $long = check_plain($event->description_long);
        $element['place2book']['event_data'] += array(
          'name' => array('#markup' => "<p><strong>" . t('Name') . ":</strong> <span>{$event->name}</span></p>"),
          'description_short' => array('#markup' => "<p><strong>" . t('Short description') . ":</strong> <span>{$short}</span></p>"),
          'description_long' => array('#markup' => "<p><strong>" . t('Long description') . ":</strong> <span>{$long}</span></p>"),
          'begin_at' => array('#markup' => "<p><strong>" . t('Begin at') . ":</strong> <span>{$begin_at}</span></p>"),
          'end_at' => array('#markup' => "<p><strong>" . t('End at') . ":</strong> <span>{$end_at}</span></p>"),
        );

        if (!empty($price)) {
          $element['place2book']['event_data']['price']['#markup'] = "<p><strong>" . t('Event price') . ":</strong> <span>{$price->value}</span></p>";
        }

        if (!empty($event->address)) {
          $address = implode(', ', (array) $event->address);
          $element['place2book']['event_data']['address']['#markup'] = "<p><strong>" . t('Location') . ":</strong> <span>{$address}</span></p>";
        }

        if (!empty($event->sale_open_at)) {
          $sale_open_at = date('d/m/Y H:i:s', strtotime($event->sale_open_at));
          $element['place2book']['event_data']['sale_open_at']['#markup'] = "<p><strong>" . t('Sale open at') . ":</strong> <span>{$sale_open_at}</span></p>";
        }

        if (!empty($event->sale_close_at)) {
          $sale_close_at = date('d/m/Y H:i:s', strtotime($event->sale_close_at));
          $element['place2book']['event_data']['sale_close_at']['#markup'] = "<p><strong>" . t('Sale end at') . ":</strong> <span>{$sale_close_at}</span></p>";
        }

        if (isset($event->kultunaut_age_group)) {
          $element['place2book']['event_data']['kultunaut_age_group'] = array(
            '#markup' => "<p><strong>" . t('Kultunaut export category') . "</strong> <span>{$event->kultunaut_age_group}</span></p>",
          );
        }

        if (isset($event->kultunaut_export_category)) {
          $element['place2book']['event_data']['kultunaut_export_category'] = array(
            '#markup' => "<p><strong>" . t('Kultunaut export category') . "</strong> <span>{$event->kultunaut_export_category}</span></p>",
          );
        }
      }

      if (!isset($event->capacity)) {
        $capacity = variable_get('ding_p2b_default_capacity', 0);
      }
      elseif ($event->capacity == '∞') {
        $capacity = 0;
      }
      else {
        $capacity = $event->capacity;
      }
      $element['place2book']['capacity'] = array(
        '#type' => 'textfield',
        '#title' => t('Event capacity'),
        '#size' => 6,
        '#maxlength' => 6,
        '#default_value' => $capacity,
        '#description' => t('Capacity of event. 0 - unlimited.'),
        '#element_validate' => array('element_validate_integer'),
        '#states' => array(
          'visible' => array(
            ':input[name="field_place2book[und][place2book][synchronize]"]' => array('checked' => TRUE),
          ),
        ),
      );

      $passive = 0;
      if (!isset($meta_data->event_state)) {
        $passive = variable_get('ding_p2b_default_passive', FALSE);
      }
      elseif ($meta_data->event_state == 'passive') {
        $passive = 1;
      }
      $element['place2book']['passive'] = array(
        '#type' => 'checkbox',
        '#title' => t('Passive event'),
        '#default_value' => $passive,
        '#description' => t('If checked, event will be marked as passive with no ticket sale.'),
        '#states' => array(
          'visible' => array(
            ':input[name="field_place2book[und][place2book][synchronize]"]' => array('checked' => TRUE),
          ),
        ),
      );

      $element['place2book']['kultunaut_export'] = array(
        '#type' => 'checkbox',
        '#title' => t('Kultunaut export'),
        '#default_value' => isset($event->kultunaut_export) ? $event->kultunaut_export : variable_get('ding_p2b_default_kultunaut_export', FALSE),
        '#description' => t('If checked, Place2book will forward this ding-event to Kultunaut.'),
        '#states' => array(
          'visible' => array(
            ':input[name="field_place2book[und][place2book][synchronize]"]' => array('checked' => TRUE),
          ),
        ),
      );

      $element['place2book']['prices_wrapper'] = array(
        '#type' => 'fieldset',
        '#title' => t('Prices'),
        '#prefix' => '<div id="ding-place2book-prices-wrapper">',
        '#suffix' => '</div>',
        '#theme' => 'ding_p2b_prices_table',
        '#states' => array(
          'visible' => array(
            ':input[name="field_place2book[und][place2book][synchronize]"]' => array('checked' => TRUE),
          ),
        ),
        '#attached' => array(
          'css' => array(
            drupal_get_path('module', 'ding_place2book') . '/css/ding_place2book_fields.css',
          ),
        ),
      );

      // Initialize prices count first time the form is rendered.
      if (!isset($form_state['prices_count'])) {
        if (!empty($prices)) {
          $form_state['prices_count'] = range(0, count($prices) - 1);
        }
        else {
          $form_state['prices_count'] = [];
        }
      }

      $price_name = variable_get('ding_p2b_default_price_name', '');

      // We have elements that are required depending on other fields. This
      // doesn't goes well with the states API, so we theme our own required
      // marker, use states API and do the validation ourselves.
      // See: https://www.drupal.org/project/drupal/issues/2855139#comment-12472554
      $required_marker = array('#theme' => 'form_required_marker');
      $required_marker = drupal_render($required_marker);
      $required_state = array(
        'required' => array(
          ':input[name="field_place2book[und][place2book][passive]"]' => array(
            'checked' => FALSE,
          ),
        ),
      );
      foreach ($form_state['prices_count'] as $key) {
        $price = isset($prices[$key]) ? $prices[$key] : NULL;

        $element['place2book']['prices_wrapper']['prices'][$key]['name'] = array(
          '#type' => 'textfield',
          '#title' => t('Name'),
          '#default_value' => !empty($price) ? $price->name : $price_name,
        );

        if (isset($price->id) && empty($price->meta_data->deletable)) {
          $element['place2book']['prices_wrapper']['prices'][$key]['name']['#description'] = t('NB: This ticket type can not be deleted (most likely because of sold tickets).');
        }

        $element['place2book']['prices_wrapper']['prices'][$key]['value'] = array(
          '#type' => 'textfield',
          '#title' => t('Price'),
          '#default_value' => !empty($price) ? $price->value : '',
        );

        // Only show required marker and add required state for existing prices
        // unless no prices exists in p2b, since we need at least one price.
        if (isset($price->id) || empty($prices)) {
          foreach (array('name', 'value') as $field) {
            $element['place2book']['prices_wrapper']['prices'][$key][$field]['#title'] .= ' ' . $required_marker;
            $element['place2book']['prices_wrapper']['prices'][$key][$field]['#states'] = $required_state;
          }
        }

        $sale_begin_at = !empty($price->sale_begin_at) ? date('Y-m-d H:i:s', strtotime($price->sale_begin_at)) : '';
        $element['place2book']['prices_wrapper']['prices'][$key]['sale_begin_at'] = array(
          '#type' => 'date_popup',
          '#default_value' => $sale_begin_at,
        );

        $sale_end_at = !empty($price->sale_end_at) ? date('Y-m-d H:i:s', strtotime($price->sale_end_at)) : '';
        $element['place2book']['prices_wrapper']['prices'][$key]['sale_end_at'] = array(
          '#type' => 'date_popup',
          '#default_value' => $sale_end_at,
        );

        // If existing price: store the original on an internal form value for
        // later use in submission.
        if (isset($price->id)) {
          $element['place2book']['prices_wrapper']['prices'][$key]['original_price'] = array(
            '#type' => 'value',
            '#value' => $price,
          );
        }

        $element['place2book']['prices_wrapper']['prices'][$key]['remove'] = array(
          '#type' => 'submit',
          '#value' => t('Remove'),
          '#name' => 'prices_remove_' . $key,
          '#price_key' => $key,
          '#price_id' => isset($price->id) ? $price->id : NULL,
          '#event_id' => $event_id,
          '#event_maker_id' => $event_maker_id,
          '#submit' => array('ding_place2book_prices_remove_submit'),
          '#limit_validation_errors' => array(),
          '#disabled' => isset($price->id) && empty($price->meta_data->deletable),
          '#ajax' => array(
            'wrapper' => 'ding-place2book-prices-wrapper',
            'callback' => 'ding_p2b_prices_remove_ajax_handler',
          ),
        );
      }

      $element['place2book']['prices_wrapper']['add'] = array(
        '#type' => 'submit',
        '#value' => t('Add'),
        '#name' => 'p2b_prices_add_btn',
        '#submit' => array('ding_place2book_prices_add_submit'),
        '#limit_validation_errors' => array(),
        '#ajax' => array(
          'wrapper' => 'ding-place2book-prices-wrapper',
          'callback' => 'ding_p2b_prices_add_ajax_handler',
        ),
      );

      $element['place2book']['event_id'] = array(
        '#type' => 'value',
        '#value' => $event_id,
      );

      $element['place2book']['event_maker_id'] = array(
        '#type' => 'value',
        '#value' => $event_maker_id,
      );

      $element['#element_validate'] = array('ding_place2book_widget_validate');

      break;
  }

  return $element;
}

/**
 * Validate handler for place2book widget.
 */
function ding_place2book_widget_validate($form, &$form_state) {
  $values = $form_state['values'];
  $place2book = $values['field_place2book'][LANGUAGE_NONE]['place2book'];
  if ($place2book['synchronize']) {
    $library = array_filter($values['og_group_ref'][LANGUAGE_NONE], function ($i) {
      return !empty($i['target_id']);
    });
    if (empty($library)) {
      $address = $values['field_ding_event_location'][LANGUAGE_NONE];
      if (empty($address[0]['name_line'])) {
        form_set_error('field_ding_event_location][und][0][name_line', t('Name is required for creating event on P2b.'));
      }

      if (empty($address[0]['thoroughfare'])) {
        form_set_error('field_ding_event_location][und][0][thoroughfare', t('Address is required for creating event on P2b.'));
      }

      if (empty($address[0]['postal_code'])) {
        form_set_error('field_ding_event_location][und][0][postal_code', t('Postal code is required for creating event on P2b.'));
      }

      if (empty($address[0]['locality'])) {
        form_set_error('field_ding_event_location][und][0][locality', t('City is required for creating event on P2b.'));
      }
    }

    if (!$place2book['passive'] && isset($place2book['prices_wrapper']['prices'])) {
      $prices = $place2book['prices_wrapper']['prices'];
      $prices = array_filter($prices, function ($price, $key) {
        $has_values = !empty($price['name']) && (!empty($price['value']) || $price['value'] === '0');
        // For existing prices we need both name and value, so flag an error if
        // this is not the case. If price ID is not set it's not an existing
        // price and just "the add one" more price, which admin can fill out if
        // they want to add another price. We require at least one price to
        // exist though (see below).
        if (isset($price['id']) && !$has_values) {
          form_set_error("field_place2book][und][place2book][prices_wrapper][prices][$key][name", t('Both Name and price value is required for prices'));
          form_set_error("field_place2book][und][place2book][prices_wrapper][prices][$key][value");
        }
        return $has_values;
      }, ARRAY_FILTER_USE_BOTH);

      if (empty($prices)) {
        form_set_error('field_place2book][und][place2book][prices_wrapper][prices][0][name', t('At least one price should exist and both name and price value is required.'));
        form_set_error('field_place2book][und][place2book][prices_wrapper][prices][0][value');
      }
    }

    $start = $values['field_ding_event_date'][LANGUAGE_NONE][0]['value'];
    $start = strtotime($start);
    if (round(abs(time() - $start) / 60, 2) == 0) {
      form_set_error('field_ding_event_date][und][0][value][date', t("Event date can't be in the past."));
    }
  }
}

/**
 * Ajax handler for add button.
 */
function ding_p2b_prices_add_ajax_handler($form, $form_state) {
  $element = $form_state['triggering_element'];
  $parents = $element['#parents'];
  array_pop($parents);
  return drupal_array_get_nested_value($form, $parents);
}

/**
 * Submit handler for adding price.
 */
function ding_place2book_prices_add_submit($form, &$form_state) {
  $form_state['rebuild'] = TRUE;
  $id = !empty($form_state['prices_count']) ? max($form_state['prices_count']) + 1 : 1;
  $form_state['prices_count'][$id] = $id;
}

/**
 * Ajax handler for remove button.
 */
function ding_p2b_prices_remove_ajax_handler($form, &$form_state) {
  $element = $form_state['triggering_element'];
  $parents = $element['#parents'];
  $parents = array_slice($parents, 0, count($parents) - 3);
  return drupal_array_get_nested_value($form, $parents);
}

/**
 * Submit handler for removing price.
 */
function ding_place2book_prices_remove_submit($form, &$form_state) {
  $element = $form_state['triggering_element'];
  if (!empty($element['#price_id']) && !empty($element['#event_id']) && !empty($element['#event_maker_id'])) {
    try {
      $p2b = ding_place2book_instance();
      $p2b->deletePrice($element['#event_maker_id'], $element['#event_id'], $element['#price_id']);
    }
    catch (Exception $ex) {
      watchdog_exception('ding_place2book', $ex);
      drupal_set_message($ex->getMessage(), 'error');
    }
  }

  unset($form_state['prices_count'][$element['#price_key']]);
  $form_state['rebuild'] = TRUE;
}

/**
 * Implements hook_field_presave().
 */
function ding_place2book_field_presave($entity_type, $entity, $field, $instance, $langcode, &$items) {
  switch ($field['type']) {
    case 'ding_p2b':
      if (!empty($items)) {
        $settings = reset($items);
        $synchronized_items = [];
        // Ensure that both 'synchronize' and 'do_sync' is set and TRUE, before
        // making any requests to p2b API. This is to ensure we don't make lots
        // of unneeded requests when nodes are saved programmatically or updated
        // in bulk via the UI.
        // See ding_place2book_field_widget_form() for more info.
        if ($settings['synchronize'] && !empty($settings['do_sync'])) {
          $synchronized_items = _ding_place2book_sync_p2b_entities($entity, $settings);
        }

        // Only update field data if synchronizationn was successful.
        if (!empty($synchronized_items)) {
          $items = $synchronized_items;
        }
        else {
          $items = array(
            array(
              'event_id' => $settings['event_id'],
              'event_maker_id' => $settings['event_maker_id'],
              'synchronize' => $settings['synchronize'],
            ),
          );
        }
      }
      break;
  }
}

/**
 * Implements hook_field_delete().
 */
function ding_place2book_field_delete($entity_type, $entity, $field, $instance, $langcode, &$items) {
  switch ($field['type']) {
    case 'ding_p2b':
      if (!empty($items)) {
        $settings = reset($items);
        if ($settings['synchronize'] && !empty($settings['event_id'])) {
          $event_id = $settings['event_id'];
          $event_maker_id = $settings['event_maker_id'];
          try {
            $p2b = ding_place2book_instance();
            $prices = $p2b->getPrices($event_maker_id, $event_id);
            foreach ($prices as $price) {
              $p2b->deletePrice($event_maker_id, $event_id, $price->id);
            }
            $p2b->deleteEvent($event_maker_id, $event_id);
          }
          catch (Exception $ex) {
            watchdog_exception('ding_place2book', $ex, t('Error appeared on deleting node: nid - :nid, title - :title.', array(
              ':nid' => $node->nid,
              ':title' => $node->title,
            )));
          }
        }
      }
      break;
  }
}

/**
 * Implements hook_field_formatter_info().
 */
function ding_place2book_field_formatter_info() {
  return array(
    'ding_p2b_formatter_default' => array(
      'label' => t('Default'),
      'field types' => array(
        'ding_p2b',
      ),
      'settings' => array(),
    ),
  );
}

/**
 * Implements hook_field_formatter_view().
 */
function ding_place2book_field_formatter_view($entity_type, $entity, $field, $instance, $langcode, $items, $display) {
  $element = array();
  switch ($field['field_name']) {
    case 'field_place2book':
      if ($display['type'] == 'ding_p2b_formatter_default' && !empty($items)) {
        list($event_id, $event_maker_id) = array_values(reset($items));

        $element[0] = array(
          '#markup' => "<div data-event-id='{$event_id}' data-event-maker-id='{$event_maker_id}' class='place2book'></div>",
          '#attached' => array(
            'css' => array(
              drupal_get_path('module', 'ding_place2book') . '/css/ding_place2book.css',
            ),
            'js' => array(
              drupal_get_path('module', 'ding_place2book') . '/js/ding_place2book.js',
            ),
          ),
        );
      }
  }
  return $element;
}

/**
 * Helper function for synchronizing p2b entities.
 *
 * @param object $entity
 *   Entity with p2b field.
 * @param array $settings
 *   Represents array of data and settings.
 *
 * @return array
 *   Array of items for field_place2book.
 */
function _ding_place2book_sync_p2b_entities($entity, array $settings) {
  $items = [];

  $event_id = !empty($settings['event_id']) ? $settings['event_id'] : FALSE;
  $event_maker_id = FALSE;
  // For clarity.
  $is_new = !$event_id;

  if ($is_new) {
    $event_maker_id = _ding_place2book_get_event_maker($entity);
  }
  elseif (isset($settings['event_maker_id'])) {
    $event_maker_id = $settings['event_maker_id'];
  }

  if ($event_maker_id) {
    $p2b = ding_place2book_instance();
    // Collect data for synchronizing event.
    $prices = $settings['prices_wrapper']['prices'];
    $original_event = $settings['original_event'];
    unset($settings['prices_wrapper']);
    unset($settings['original_event']);
    unset($settings['synchronize']);
    unset($settings['event_id']);
    unset($settings['event_maker_id']);
    $options['event'] = ding_p2b_format_options($entity, $settings);

    try {
      if ($is_new) {
        $event = $p2b->createEvent($event_maker_id, $options);
      }
      else {
        // Ensure that we are not missing data on the event by merging the
        // original event with the data we send p2b API. If something is
        // missing it may remove data or give other unexpected behavior.
        $options['event'] = array_merge((array) $original_event, $options['event']);
        $event = $p2b->updateEvent($event_maker_id, $event_id, $options);
      }

      $items = array(
        array(
          'event_id' => $event->id,
          'event_maker_id' => $event_maker_id,
          'synchronize' => 1,
        ),
      );
    }
    catch (Exception $ex) {
      watchdog_exception('ding_place2book', $ex);
      drupal_set_message($ex->getMessage(), 'error');
      return $items;
    }

    foreach ($prices as $price) {
      if (empty($price['name']) || !isset($price['value'])) {
        continue;
      }

      $sale_begin = NULL;
      if ($price['sale_begin_at']) {
        $sale_begin = format_date(strtotime($price['sale_begin_at']), 'custom', 'Y-m-d\TH:i:sO', date_default_timezone());
      }
      else {
        // If sale begin was left empty use current time.
        $sale_begin = date('Y-m-d\TH:i:sO');
      }
      $sale_end = NULL;
      if ($price['sale_end_at']) {
        $sale_end = format_date(strtotime($price['sale_end_at']), 'custom', 'Y-m-d\TH:i:sO', date_default_timezone());
      }
      else {
        // If sale end was left empty use events start date.
        $sale_end = $event->begin_at;
      }

      $data = array(
        'name' => $price['name'],
        'value' => $price['value'],
        'sale_begin_at' => $sale_begin,
        'sale_end_at' => $sale_end,
      );

      try {
        if (isset($price['original_price'])) {
          $original_price = (array) $price['original_price'];
          $price_id = $original_price['id'];
          unset($original_price['id']);
          // Ensure that we are not missing data on the price by merging the
          // original price with the data we send p2b API. If somethins is
          // missing it may remove data or give other unexpected behavior.
          $data = array_merge($original_price, $data);
          $p2b->updatePrice($event_maker_id, $event->id, $price_id, array('price' => $data));
        }
        else {
          $p2b->createPrice($event_maker_id, $event->id, array('price' => $data));
        }
      }
      catch (Exception $ex) {
        watchdog_exception('ding_place2book', $ex);
        drupal_set_message($ex->getMessage(), 'error');
        return $items;
      }
    }

    if ($is_new) {
      drupal_set_message(t('Event was successfully created.'));
    }
    else {
      drupal_set_message(t('Event was successfully updated.'));
    }
  }
  return $items;
}
