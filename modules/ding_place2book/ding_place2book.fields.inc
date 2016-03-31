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
  $prices = $item['prices_wrapper']['prices'];
  $prices = array_filter($prices, function ($i) {
    return !empty($i['value']) || !empty($i['name']);
  });
  return empty($item['synchronize']) || empty($prices);
}

/**
 * Implements hook_field_widget_info().
 */
function ding_place2book_field_widget_info() {
  return [
    'ding_p2b_widget_default' => [
      'label' => t('Default'),
      'field types' => ['ding_p2b'],
      'behaviors' => [
        'multiple values' => FIELD_BEHAVIOR_CUSTOM,
        'default value' => FIELD_BEHAVIOR_CUSTOM,
      ],
    ],
  ];
}

/**
 * Implements hook_field_widget_form().
 */
function ding_place2book_field_widget_form(&$form, &$form_state, $field, $instance, $langcode, $items, $delta, $element) {
  $event = $event_id = $event_maker_id = $price_id = NULL;
  $node_id = isset($form_state['node']->nid) ? $form_state['node']->nid : NULL;
  if (!empty($items)) {
    list($event_id, $event_maker_id) = array_values(reset($items));
    try {
      $p2b = P2b\P2b::getInstance();
      $event = $p2b->getEvent($event_maker_id, $event_id);
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
        '#default_value' => variable_get('ding_p2b_default_synchronize', FALSE),
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
        '#default_value' => isset($event->capacity) ? $event->capacity : variable_get('ding_p2b_default_capacity', 0),
        '#description' => t('Capacity of event. 0 - unlimited.'),
        '#element_validate' => ['element_validate_integer'],
      ];

      $element['place2book']['passive'] = [
        '#type' => 'checkbox',
        '#title' => t('Passive event'),
        '#default_value' => isset($event->mute) ? $event->mute : variable_get('ding_p2b_default_passive', FALSE),
        '#description' => t('If checked, event will be marked as passive with no ticket sale.'),
      ];

      $element['place2book']['kultunaut_export'] = [
        '#type' => 'checkbox',
        '#title' => t('Kultunaut export'),
        '#default_value' => isset($event->kultunaut_export) ? $event->kultunaut_export : variable_get('ding_p2b_default_kultunaut_export', FALSE),
        '#description' => t('If checked, Place2book will forward this ding-event to Kultunaut.'),
      ];

      if (isset($event->kultunaut_age_group)) {
        $element['place2book']['kultunaut_age_group'] = [
          '#markup' => "<p><strong>Kultunaut export category</strong> <span>{$event->kultunaut_age_group}</span></p>",
        ];
      }

      if (isset($event->kultunaut_export_category)) {
        $element['place2book']['kultunaut_export_category'] = [
          '#markup' => "<p><strong>Kultunaut export category</strong> <span>{$event->kultunaut_export_category}</span></p>",
        ];
      }

      $element['place2book']['prices_wrapper'] = [
        '#type' => 'fieldset',
        '#title' => t('Prices'),
        '#prefix' => '<div id="ding-place2book-prices-wrapper">',
        '#suffix' => '</div>',
        '#theme' => 'ding_p2b_prices_table',
      ];

      if (!isset($form_state['prices_count'])) {
        $form_state['prices_count'] = empty($items) ? range(0, 0) : range(0, count($items));
      }
      foreach ($form_state['prices_count'] as $key) {
        $price = $price_id = NULL;
        if (isset($items[$key])) {
          list($event_id, $event_maker_id, $price_id) = array_values($items[$key]);
          try {
            $price = $p2b->getPrice($event_maker_id, $event_id, $price_id);
          }
          catch (Exception $ex) {
            watchdog_exception('ding_place2book', $ex);
          }
        }
        $element['place2book']['prices_wrapper']['prices'][$key]['value'] = [
          '#type' => 'textfield',
          '#default_value' => !empty($price) ? $price->value : '',
        ];

        $element['place2book']['prices_wrapper']['prices'][$key]['name'] = [
          '#type' => 'textfield',
          '#default_value' => !empty($price) ? $price->name : '',
        ];

        $element['place2book']['prices_wrapper']['prices'][$key]['id'] = [
          '#type' => 'hidden',
          '#value' => $price_id,
        ];

        $element['place2book']['prices_wrapper']['prices'][$key]['remove'] = [
          '#type' => 'submit',
          '#value' => t('Remove'),
          '#name' => 'prices_remove_' . $key,
          '#price_key' => $key,
          '#node_id' => $node_id,
          '#price_id' => $price_id,
          '#event_id' => $event_id,
          '#event_maker_id' => $event_maker_id,
          '#submit' => ['ding_place2book_prices_remove_submit'],
          '#limit_validation_errors' => [],
          '#ajax' => [
            'wrapper' => 'ding-place2book-prices-wrapper',
            'callback' => 'ding_p2b_prices_remove_ajax_handler',
          ],
        ];
      }

      $element['place2book']['prices_wrapper']['add'] = [
        '#type' => 'submit',
        '#value' => t('Add'),
        '#name' => 'p2b_prices_add_btn',
        '#submit' => ['ding_place2book_prices_add_submit'],
        '#limit_validation_errors' => [],
        '#ajax' => [
          'wrapper' => 'ding-place2book-prices-wrapper',
          'callback' => 'ding_p2b_prices_add_ajax_handler',
        ],
      ];

      $element['place2book']['ids'] = [
        '#type' => 'value',
        '#value' => !empty($items) ? $items : [],
      ];

      break;
  }

  return $element;
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
      $p2b = P2b\P2b::getInstance();
      $p2b->deletePrice($element['#event_maker_id'], $element['#event_id'], $element['#price_id']);
    }
    catch (Exception $ex) {
      watchdog_exception('ding_place2book', $ex);
    }
    if (!empty($element['#node_id'])) {
      $original = $form_state['node'];
      $node = new stdClass();
      $node->nid = $original->nid;
      $node->vid = $original->vid;
      $node->type = $original->type;
      $place2book = field_get_items('node', $original, 'field_place2book');
      $place2book = array_filter($place2book, function ($i) use ($element) {
        return $i['price_id'] != $element['#price_id'];
      });
      $node->field_place2book = [
        LANGUAGE_NONE => $place2book,
      ];
      field_attach_update('node', $node);
      entity_get_controller('node')->resetCache();
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
        $p2b = P2b\P2b::getInstance();
        $settings = reset($items);
        list($event_id, $event_maker_id) = array_values(reset($settings['ids']));
        $items = [];
        if (empty($event_id)) {
          $event_maker_id = _ding_place2book_get_event_maker($entity);
          $date = field_get_items('node', $entity, 'field_ding_event_date');
          $start = strtotime($date[0]['value']);
          if ($event_maker_id && round(abs(time() - $start) / 60, 2) != 0) {
            try {
              // Collect data for creating event.
              $prices = $settings['prices_wrapper']['prices'];
              unset($settings['prices_wrapper']);
              unset($settings['synchronize']);
              unset($settings['ids']);
              $options['event'] = ding_p2b_format_options($entity, $settings);
              $event = $p2b->createEvent($event_maker_id, $options);

              foreach ($prices as $price) {
                $data = [
                  'name' => $price['name'],
                  'value' => $price['value'],
                ];
                $price = $p2b->createPrice($event_maker_id, $event->id, ['price' => $data]);
                $items[] = [
                  'p2b_id' => $event->id,
                  'event_maker' => $event_maker_id,
                  'price_id' => $price->id,
                ];
              }
            }
            catch (Exception $ex) {
              watchdog_exception('ding_place2book', $ex);
              $items = [];
            }
          }
        }
        else {
          $date = field_get_items('node', $entity, 'field_ding_event_date');
          $start = strtotime($date[0]['value']);
          if ($event_maker_id && round(abs(time() - $start) / 60, 2) != 0) {
            try {
              // Collect data for updating event.
              $prices = $settings['prices_wrapper']['prices'];
              $ids = $settings['ids'];
              unset($settings['prices_wrapper']);
              unset($settings['synchronize']);
              unset($settings['ids']);
              $options['event'] = ding_p2b_format_options($entity, $settings);
              $event = $p2b->updateEvent($event_maker_id, $event_id, $options);

              foreach ($prices as $key => $price) {
                if (empty($price['name']) || empty($price['value']))
                  continue;

                $data = [
                  'name' => $price['name'],
                  'value' => $price['value'],
                ];
                if (!empty($price['id'])) {
                  $price = $p2b->updatePrice($event_maker_id, $event->id, $ids[$key]['price_id'], ['price' => $data]);
                }
                else {
                  $price = $p2b->createPrice($event_maker_id, $event->id, ['price' => $data]);
                }
                $items[] = [
                  'p2b_id' => $event->id,
                  'event_maker' => $event_maker_id,
                  'price_id' => $price->id,
                ];
              }
            }
            catch (Exception $ex) {
              watchdog_exception('ding_place2book', $ex);
              $items = [];
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
          $meta_data = $event->meta_data;
          $start = strtotime($event->begin_at);
          if (in_array($meta_data->event_state, ['passive', 'published',]) && time() < $start) {
            $meta_data->sales_status = 'closed';
            switch ($meta_data->sales_status) {
              case 'open':
                if (isset($event->links->sales_location) && ($meta_data->available_tickets > 0 || $meta_data->available_tickets == '∞')) {
                  $data = l(t('Book a ticket'), $event->links->sales_location, ['attributes' => ['_target' => 'blank']]);
                  $class = 'order';
                }
                else {
                  $data = t('Sold out');
                  $class = 'info ticket-info';
                }
                break;
              case 'upcoming':
                $data = t('Ticket sale has not yet started for this event');
                $class = 'info ticket-info';
                break;
              case 'closed':
                $data = t('The event is closed for admission');
                $class = 'info ticket-info';
                break;
            }
          }
          else {
            $data = t('The event has already taken place');
            $class = 'info ticket-info';
          }

          $element[0] = [
            '#markup' => "<div class='place2book {$class}'>{$data}</div>",
            '#attached' => [
              'css' => [
                drupal_get_path('module', 'ding_place2book') . '/css/ding_place2book.css',
              ],
            ],
          ];
        }
        catch (Exception $ex) {
          watchdog_exception('ding_place2book', $ex, t('Error appeared on getting date form p2b.'));
        }
      }
      break;
  }
  return $element;
}
