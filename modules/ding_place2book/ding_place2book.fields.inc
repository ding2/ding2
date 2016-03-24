<?php
/**
 * @file
 * Field hook implementations.
 */

/**
 * Implements hook_field_info().
 */
function ding_place2book_field_info() {
  return [
    'ding_p2b' => [
      'label' => t('Place2book field'),
      'description' => t('Information about place2book ticket.'),
      'default_widget' => 'ding_p2b_widget_default',
      'default_formatter' => 'ding_p2b_formatter_default',
      'settings' => [],
    ],
  ];
}

/**
 * Implements hook_field_is_empty().
 */
function ding_place2book_field_is_empty($item, $field) {
  return empty($item['place2book']['synchronize']);
}

/**
 * Implements hook_field_widget_info().
 */
function ding_place2book_field_widget_info() {
  return [
    'ding_p2b_widget_default' => [
      'label' => t('Default'),
      'field types' => ['ding_p2b'],
    ],
  ];
}

/**
 * Implements hook_field_widget_form().
 */
function ding_place2book_field_widget_form(&$form, &$form_state, $field, $instance, $langcode, $items, $delta, $element) {
  $event = $event_id = $event_maker_id = $price_id = NULL;
  if (!empty($items)) {
    list($event_id, $event_maker_id, $price_id) = array_values(reset($items));
    try {
      $p2b = P2b\P2b::getInstance();
      $event = $p2b->getEvent($event_maker_id, $event_id);
      $price = $p2b->getPrice($event_maker_id, $event_id, $price_id);
    }
    catch (Exception $ex) {
      watchdog_exception('ding_place2book', $ex, t('Error appeared on getting data from p2b.'));
    }
  }
  switch ($instance['widget']['type']) {
    case 'ding_p2b_widget_default':
      $element['place2book'] = [
        '#type' => 'fieldset',
        '#title' => t('Place2Book'),
        '#description' => t('Information about event on Place2book service.'),
        '#collapsible' => TRUE,
        '#collapsed' => TRUE,
        '#tree' => TRUE,
      ];

      $element['place2book']['synchronize'] = [
        '#type' => 'checkbox',
        '#title' => t('Synchronize event with Place2book service'),
        '#description' => t('If checked, then event on Place2book will be updated with data from local event.'),
        '#default_value' => variable_get('p2b_default_syncronize', FALSE),
      ];

      if (!empty($event)) {
        $begin_at = date('d/m/Y H:i:s', strtotime($event->begin_at));
        $end_at = date('d/m/Y H:i:s', strtotime($event->end_at));
        $element['place2book'] += [
          'name' => ['#markup' => "<p><strong>Name:</strong> <span>{$event->name}</span></p>"],
          'description_short' => ['#markup' => "<p><strong>Short description:</strong> <span>{$event->description_short}</span></p>"],
          'description_long' => ['#markup' => "<p><strong>Long description:</strong> <span>{$event->description_long}</span></p>"],
          'begin_at' => ['#markup' => "<p><strong>Begin at:</strong> <span>{$begin_at}</span></p>"],
          'end_at' => ['#markup' => "<p><strong>End at:</strong> <span>{$end_at}</span></p>"],
          'price' => ['#markup' => "<p><strong>End at:</strong> <span>{$price->value}</span></p>"],
        ];

        if (!empty($price)) {
          $element['place2book']['price']['#markup'] = "<p><strong>Event price:</strong> <span>{$price->value}</span></p>";
        }

        if (!empty($event->address)) {
          $address = implode(', ', (array) $event->address);
          $element['place2book']['address']['#markup'] = "<p><strong>Sale open at:</strong> <span>{$address}</span></p>";
        }

        if (!empty($event->sale_open_at)) {
          $sale_open_at = date('d/m/Y H:i:s', strtotime($event->sale_open_at));
          $element['place2book']['sale_open_at']['#markup'] = "<p><strong>Sale open at:</strong> <span>{$sale_open_at}</span></p>";
        }

        if (!empty($event->sale_close_at)) {
          $sale_close_at = date('d/m/Y H:i:s', strtotime($event->sale_close_at));
          $element['place2book']['sale_close_at']['#markup'] = "<p><strong>Sale end at:</strong> <span>{$sale_close_at}</span></p>";
        }
      }

      $element['place2book']['capacity'] = [
        '#type' => 'textfield',
        '#title' => t('Event capacity'),
        '#size' => 5,
        '#maxlength' => 5,
        '#default_value' => isset($event->capacity) ? $event->capacity : 0,
        '#description' => t('Capacity of event. 0 - unlimited.'),
        '#element_validate' => ['element_validate_integer'],
      ];

      $element['place2book']['passive'] = [
        '#type' => 'checkbox',
        '#title' => t('Passive event'),
        '#default_value' => isset($event->mute) ? $event->mute : 0,
        '#description' => t('If checked, event will be marked as passive with no ticket sale.'),
      ];

      $element['place2book']['kultunaut_export'] = [
        '#type' => 'checkbox',
        '#title' => t('Kultunaut export'),
        '#default_value' => isset($event->kultunaut_export) ? $event->kultunaut_export : FALSE,
        '#description' => t('If checked, Place2book will forward this ding-event to Kultunaut.'),
      ];

      $options = variable_get('p2b_kultunaut_age_group', []);
      $element['place2book']['kultunaut_age_group'] = [
        '#type' => 'select',
        '#title' => t('Kultunaut age group'),
        '#options' => $options,
        '#default_value' => isset($event->kultunaut_age_group) ? $event->kultunaut_age_group : '',
        '#states' => [
          'visible' => [
            ':input[name="field_place2book[und][0][place2book][kultunaut_export]"]' => ['checked' => TRUE],
          ],
        ],
        '#empty_option' => t('- None -'),
      ];

      if (isset($event->kultunaut_export_category)) {
        $element['place2book']['kultunaut_export_category'] = [
          '#markup' => "<p><strong>Kultunaut export category</strong> <span>{$event->kultunaut_export_category}</span></p>",
        ];
      }

      $element['ids']['event_id'] = [
        '#type' => 'value',
        '#value' => $event_id,
      ];

      $element['ids']['event_maker_id'] = [
        '#type' => 'value',
        '#value' => $event_maker_id,
      ];

      $element['ids']['price_id'] = [
        '#type' => 'value',
        '#value' => $price_id,
      ];
      break;
  }

  return $element;
}

/**
 * Implements hook_field_presave().
 */
function ding_place2book_field_presave($entity_type, $entity, $field, $instance, $langcode, &$items) {
  switch ($field['type']) {
    case 'ding_p2b':
      if (!empty($items)) {
        $p2b = P2b\P2b::getInstance();
        $settings = reset($items);
        list($event_id, $event_maker_id, $price_id) = array_values($settings['ids']);
        if (empty($event_id)) {
          $event_maker_id = _ding_place2book_get_event_maker($entity);
          $date = field_get_items('node', $entity, 'field_ding_event_date');
          $start = strtotime($date[0]['value']);
          if ($event_maker_id && round(abs(time() - $start) / 60, 2) != 0) {
            try {
              // Collect data for creating event.
              $options['event'] = ding_p2b_format_options($entity, $settings['place2book']);
              $event = $p2b->createEvent($event_maker_id, $options);
              // Collect data for creating price.
              $price = field_get_items('node', $entity, 'field_ding_event_price');
              $data = [
                'name' => $event->name,
                'description' => $event->description_short,
                'value' => $price[0]['value'],
                'sale_begin_at' => $event->sale_open_at,
                'sale_end_at' => $event->sale_close_at,
              ];
              $price = $p2b->createPrice($event_maker_id, $event->id, ['price' => $data]);

              // Save ids in DB.
              $items = [
                [
                  'p2b_id' => $event->id,
                  'event_maker' => $event_maker_id,
                  'price_id' => $price->id,
                ],
              ];
            }
            catch (Exception $ex) {
              watchdog_exception('ding_place2book', $ex, t('Error appeared on creating event.'));
            }
          }
        }
        else {
          $date = field_get_items('node', $entity, 'field_ding_event_date');
          $start = strtotime($date[0]['value']);
          if ($event_maker_id && round(abs(time() - $start) / 60, 2) != 0) {
            try {
              // Collect data for updating event.
              $options['event'] = ding_p2b_format_options($entity, $settings['place2book']);
              $event = $p2b->updateEvent($event_maker_id, $event_id, $options);
              // Collect data for updating price.
              $price = field_get_items('node', $entity, 'field_ding_event_price');
              $data = [
                'name' => $event->name,
                'description' => $event->description_short,
                'value' => $price[0]['value'],
                'sale_begin_at' => $event->sale_open_at,
                'sale_end_at' => $event->sale_close_at,
              ];
              $price = $p2b->updatePrice($event_maker_id, $event_id, $price_id, ['price' => $data]);
              // Save ids in DB.
              $items = [
                [
                  'p2b_id' => $event->id,
                  'event_maker' => $event_maker_id,
                  'price_id' => $price->id,
                ],
              ];
            }
            catch (Exception $ex) {
              watchdog_exception('ding_place2book', $ex, t('Error appeared on updating.'));
            }
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
  return [
    'ding_p2b_formatter_default' => [
      'label' => t('Default'),
      'field types' => [
        'ding_p2b',
      ],
      'settings' => [],
    ],
  ];
}

/**
 * Implements hook_field_formatter_view().
 */
function ding_place2book_field_formatter_view($entity_type, $entity, $field, $instance, $langcode, $items, $display) {
  $element = [];
  switch ($field['field_name']) {
    case 'field_place2book':
      if ($display['type'] == 'ding_p2b_formatter_default' && !empty($items)) {
        list($event_id, $event_maker_id, $price_id) = array_values(reset($items));
        try {
          $p2b = P2b\P2b::getInstance();
          $event = $p2b->getEvent($event_maker_id, $event_id);
          if (isset($event->links->sales_location)) {
            $link = l(t('Book a ticket'), $event->links->sales_location, ['attributes' => ['_target' => 'blank']]);
            $element[0] = [
              '#markup' => "<div class='place2book order'>{$link}</div>>",
              '#attached' => [
                'css' => [
                  drupal_get_path('module', 'ding_place2book') . '/css/ding_place2book.css',
                ],
              ],
            ];
          }
        }
        catch (Exception $ex) {
          watchdog_exception('ding_place2book', $ex, t('Error appeared on getting date form p2b.'));
        }
      }
      break;
  }
  return $element;
}
