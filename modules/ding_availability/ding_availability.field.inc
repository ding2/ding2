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
      'virtual_field' => array(
        'entity_types' => array('ting_object'),
        'add_widget' => TRUE,
      ),
    ),
    'ding_availability_holdings' => array(
      'label' => t('Holdings information.'),
      'description' => t('Holdings information.'),
      'default_widget' => 'hidden',
      'default_formatter' => 'ding_availability_default',
      'virtual_field' => array(
        'entity_types' => array('ting_object'),
        'add_widget' => TRUE,
      ),
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
        'ding_availability_holdings',
      ),
    ),
    'ding_availability_type' => array(
      'label' => t('With availability information'),
      'field types' => array(
        'ting_type',
      ),
    ),
    'ding_availability_with_labels' => array(
      'label' => t('Availability information with labels'),
      'field types' => array(
        'ting_collection_types',
      ),
    ),
  );
}

/**
 * Implements hook_field_formatter_view().
 */
function ding_availability_field_formatter_view($entity_type, $entity, $field, $instance, $langcode, $items, $display) {
  $element = array();
  $online_types = array_filter(variable_get('ting_online_types', _ting_default_online_types()));
  $reservable_sources = array_filter(variable_get('ting_reservable_sources', _ting_default_reservable_sources()));

  // Attach front-end style and JS to the element.
  foreach ($items as $delta => $item) {
    $attached = array(
      'css' => array(
        drupal_get_path('module', 'ding_availability') . '/css/ding_availability.css',
      ),
    );

    // Extract records' source.
    if ($field['type'] != 'ting_collection_types') {
      /* @var \TingEntity $entity */
      $ac_source = $entity->getAc_source();
    }

    switch ($display['type']) {
      case 'ding_availability_default':
        // Generate an unique id.
        $id = drupal_html_id('holdings-' . $entity->id);

        // Add javascript.
        $attached['js'] = array(
          drupal_get_path('module', 'ding_availability') . '/js/ding_availability.js',
        );

        // If item is of type 'library materials' (where we can lookup holding
        // data), prepare to check holding on the item.
        $holding_types = variable_get('ding_availability_holdings_types', _ding_availability_holdings_default_types());
        if (in_array(drupal_strtolower($ac_source), $reservable_sources) && in_array(drupal_strtolower($entity->type), $holding_types)) {
          $attached['js'][] = array(
            'data' => array(
              'ding_availability_mode' => 'holdings',
              'ding_availability' => array(
                $id => array($entity->localId),
              ),
            ),
            'type' => 'setting',
          );

          $element[$delta] = array(
            // @todo: move this into tpl file.
            '#markup' => '<div id="' . $id . '" class="holdings holdings-' . $entity->localId . '"><div class="loader"><i class="icon icon-spinner icon-spin"></i><p class="loader-text">' . t('Fetching holdings information.') . '<p></div></div>',
            '#attached' => $attached,
          );
        }

        break;

      case 'ding_availability_item':
        // Add javascript.
        $attached['js'] = array(
          drupal_get_path('module', 'ding_availability') . '/js/ding_availability.js',
        );

        $element[$delta] = array(
          '#markup' => '<div class="availability availability-' . $item['provider_id'] . '"></div>',
          '#attached' => $attached,
        );
        break;

      case 'ding_availability_type':
        // Generate an unique id.
        $id = drupal_html_id('availability-' . $entity->id);

        // Mark as available if it is an online resource,
        $available_online = (in_array(drupal_strtolower($entity->type), $online_types)) ? 'available' : 'not-available-online';

        // Add javascript.
        $attached['js'] = array(
          drupal_get_path('module', 'ding_availability') . '/js/ding_availability.js',
        );

        // If item is of type 'library materials' (where we can lookup holding
        // data), prepare to check holding on the item.
        if (in_array(strtolower($ac_source), $reservable_sources)) {
          $attached['js'][1] = array(
            'data' => array(
              'ding_availability' => array(
                $id => array($entity->localId),
              ),
            ),
            'type' => 'setting',
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
                'pending',
              ),
            ),
          ),
        );
        break;

      case 'ding_availability_with_labels':
        /* @var \TingCollection $entity */
        $element[$delta] = array(
          '#theme' => 'ding_availability_collection_labels',
          '#collection' => $entity->getTingObjectCollection()
        );
        break;
    }
  }

  return $element;
}
