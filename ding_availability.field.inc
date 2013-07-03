<?php

/**
 * @file
 * Field hook implementations.
 */

/**
 * Implements hook_field_info().
 */
function ding_availability_field_info() {
  return array(
    'ding_availability_item' => array(
      'label' => t('Availability information.'),
      'description' => t('Availability information.'),
      'default_widget' => 'hidden',
      'default_formatter' => 'ding_availability_default',
      'no_ui' => TRUE,
    ),
    'ding_availability_holdings' => array(
      'label' => t('Holdings information.'),
      'description' => t('Holdings information.'),
      'default_widget' => 'hidden',
      'default_formatter' => 'ding_availability_default',
      'no_ui' => TRUE,
    ),
  );
}

/**
 * Implements hook_field_load().
 */
function ding_availability_field_load($entity_type, $entities, $field, $instances, $langcode, &$items, $age) {
  foreach ($entities as $id => $entity) {
    $items[$id][0] = array(
      'provider_id' => $entity->localId,
    );
  }
}

/**
 * Implements hook_widget_info_alter().
 */
function ding_availability_widget_info_alter(&$info) {
  if (isset($info['hidden'])) {
    $info['hidden']['field types'][] = 'ding_availability_item';
    $info['hidden']['field types'][] = 'ding_availability_holdings';
  }
}

/**
 * Implements hook_field_formatter_info().
 */
function ding_availability_field_formatter_info() {
  return array(
    'ding_availability_default' => array(
      'label' => t('Default'),
      'field types' => array(
        'ding_availability_item',
        'ding_availability_holdings'
      ),
    ),
    'ding_availability_type' => array(
      'label' => t('With availability information'),
      'field types' => array(
        'ting_type',
      ),
    ),
    'ding_availability_types' => array(
      'label' => t('With availability information'),
      'field types' => array(
        'ting_collection_types',
      ),
      'settings'  => array(
        'link' => FALSE,
      ),
    ),
  );
}



/**
 * Implements hook_field_formatter_settings_form().
 */
function ding_availability_field_formatter_settings_form($field, $instance, $view_mode, $form, &$form_state) {
  // Get display and current (or default) settings.
  $display = $instance['display'][$view_mode];
  $settings = $display['settings'];

  // Initialize the return element (settings form).
  $element = array();

  switch ($field['type']) {
    case 'ting_collection_types':
      $element['link'] = array(
        '#type' => 'checkbox',
        '#title' => t('Links'),
        '#description' => t('Convert the availability texts into links.'),
        '#default_value' => $settings['link'],
      );
      break;
  }

  return $element;
}



/**
 * Implements hook_field_formatter_settings_summary().
 */
function ding_availability_field_formatter_settings_summary($field, $instance, $view_mode) {
  // Get settings information for the field instance.
  $display = $instance['display'][$view_mode];
  $settings = $display['settings'];
  $summary = NULL;

  if ($field['type'] == 'ting_collection_types') {
    $linking = t('false');
    if ($settings['link']) {
      $linking = t('true');
    }

    // Check if linking to the object have been selected
    $summary = t('Link to ting objects: @link', array(
      '@link' => $linking,
    ));
  }

  return $summary;
}

/**
 * Implements hook_field_formatter_view().
 */
function ding_availability_field_formatter_view($entity_type, $entity, $field, $instance, $langcode, $items, $display) {
  $element = array();
  $online_types = variable_get('ting_online_types', _ting_default_online_types());
  $lib_materials_types = array('Bibliotekets materialer', 'Bibliotekskatalog');

  // Attach front-end syle and JS to the element.
  foreach ($items as $delta => $item) {
    $attached = array(
      'js' => array(
        drupal_get_path('module', 'ding_availability') . '/js/ding_availability.js',
      ),
      'css' => array(
        drupal_get_path('module', 'ding_availability') . '/css/ding_availability.css'
      ),
    );

    // Extract records' source
    if ($field['type'] != 'ting_collection_types') {
      $ac_source = $entity->reply->record['ac:source'][''][0];
    }

    switch ($field['type']) {
      case 'ding_availability_holdings':
        // Generate an unique id.
        $id = drupal_html_id('holdings-' . $entity->id);

        // If item is of type 'library materials' (where we can lookup holding data), prepare to check holding on the item
        $holding_types = variable_get('ding_availability_holdings_types', _ding_availability_holdings_default_types());
        if (in_array($ac_source, $lib_materials_types) && in_array(strtolower($entity->type), $holding_types)) {
          $attached['js'][] = array(
            'data' => array(
              'ding_availability_mode' => 'holdings',
              'ding_availability' => array(
                $id => array($entity->localId),
              ),
            ),
            'type' => 'setting'
          );

          $element[$delta] = array(
            '#markup' => '<div id="' . $id . '" class="holdings holdings-' . $entity->localId . '"></div>',
            '#attached' => $attached,
          );
        }

        break;

      case 'ding_availability_item':
        $element[$delta] = array(
          '#markup' => '<div class="availability availability-' . $item['provider_id'] . '"></div>',
          '#attached' => $attached,
        );
        break;

      case 'ting_type':
        // Generate an unique id.
        $id = drupal_html_id('availability-' . $entity->id);

        // Mark as available if it is an online resource
        $available_online = (in_array(drupal_strtolower($entity->type), $online_types)) ? 'available' : 'not-available-online';

        // If item is of type 'library materials' (where we can lookup holding data), prepare to check holding on the item
        if (in_array($ac_source, $lib_materials_types)) {
          $attached['js'][1] = array(
            'data' => array(
              'ding_availability' => array(
                $id => array($entity->localId),
              ),
            ),
            'type' => 'setting'
          );
        }

        $element[$delta] = array(
          '#theme' => 'item_list',
          '#attached' => $attached,
          '#items' => array(
            array(
              'data' => $entity->type,
              'id' => $id,
              'class' => array(
                'availability',
                drupal_html_class($entity->type),
                $available_online,
                'pending'
              ),
            )
          ),
        );
        break;

      case 'ting_collection_types':
        $id_mapping = array();
        $typed_entities = array();
        // Sort entities into type -> ids.
        foreach ($entity->entities as $ent) {
          $typed_entities[$ent->type][] = $ent;
        }

        foreach ($typed_entities as $type => $entities) {
          // Generate an unique id.
          $id = drupal_html_id('availability-' . $entities[0]->id . '-' . $type);

          // Extract records' source
          $ac_source = $entities[0]->reply->record['ac:source'][''][0];

          // Mark as available if it is an online resource
          $available_online = (in_array(drupal_strtolower($type), $online_types)) ? 'available' : '';
          $available_online_label = ($available_online) ? '<span class="availability-status">' . t('online') . '</span>' : '';

          // Convert type into link.
          if ($display['settings']['link']) {
            // If there is only 1 object there is a direct link
            // else there is a link to the collection.
            if (count($entities) == 1) {
              $url = entity_uri('ting_object', $entities[0]);
            }
            else {
              $url = entity_uri('ting_collection', $entities[0]);
            }
            $url['options']['html'] = TRUE;
            $typelink = l(check_plain($type) . $available_online_label, $url['path'], $url['options']);

          }

          // Create a list element for each type.
          $types[] = array(
            'data' => $typelink,
            'id' => $id,
            'class' => array('availability', drupal_html_class($type), $available_online, 'pending'),
          );

          $ids = array();
          foreach ($entities as $object_entity) {
             $ids[] = $object_entity->localId;
          }

          // If item is of type 'library materials' (where we can lookup holding data), map the HTML id to the list of entity ids.
          if (in_array($ac_source, $lib_materials_types) && !$available_online) {
            $id_mapping[$id] = $ids;
          }
        }

        // Prepare to check holding on the item.
        // It's importants that this is attached even if empty, else javascript will fail beacuse it gets an empty object.
        $attached['js'][1] = array(
          'data' => array(
            'ding_availability' => $id_mapping,
            'ding_availability_link' => $display['settings']['link'],
          ), 'type' => 'setting'
        );

        $element[$delta] = array(
          '#theme' => 'item_list',
          '#attached' => $attached,
          '#items' => $types,
        );
        break;
    }
  }

  return $element;
}
