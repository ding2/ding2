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
  foreach ($items as $delta => $item) {
    $attached = array(
      'js' => array(
        drupal_get_path('module', 'ding_availability') . '/js/ding_availability.js' => array(
          'type' => 'file',
        ),
      ),
      'css' => array(
        drupal_get_path('module', 'ding_availability') . '/css/ding_availability.css'
      ),
    );

    switch ($field['type']) {
      case 'ding_availability_holdings':
        // Generate an unique id.
        $id = drupal_html_id('holdings-' . $entity->id);
        $attached['js'][1] = array(
          'data' => array(
            'ding_availability_mode' => 'holdings',
            'ding_availability' => array(
              $id => array($entity->localId),
            ),
          ), 'type' => 'setting');

        $element[$delta] = array(
          '#markup' => '<div id="' . $id . '" class="holdings holdings-' . $entity->localId . '"></div>',
          '#attached' => $attached,
        );
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
        $attached['js'][1] = array(
          'data' => array(
            'ding_availability' => array(
              $id => array($entity->localId),
            ),
          ), 'type' => 'setting');

        $element[$delta] = array(
          '#theme' => 'item_list',
          '#attached' => $attached,
          '#items' => array(
            array(
              'data' => $entity->type,
              'id' => $id,
              'class' => array('availability', drupal_html_class($entity->type)),
            )
          ),
        );
        break;

      case 'ting_collection_types':
        $id_mapping = array();
        $typed_entities = array();
        // Sort entities into type -> ids.
        foreach ($entity->entities as $ent) {
          $typed_entities[$ent->type][] = $ent->localId;
        }

        foreach ($typed_entities as $type => $entities) {
          // Generate an unique id.
          $id = drupal_html_id('availability-' . $entity->id . '-' . $type);

          // Convert type into link.
          if ($display['settings']['link']) {
            $url = entity_uri('ting_object', $entity);
            $type = l($type, $url['path'], $url['options']);
          }

          // Create a list element for each type.
          $types[] = array(
            'data' => $type,
            'id' => $id,
            'class' => array('availability', drupal_html_class($type)),
          );

          // Map the HTML id to the list of entity ids.
          $id_mapping[$id] = $entities;
        }

        $attached['js'][1] = array(
          'data' => array(
            'ding_availability' => $id_mapping,
            'ding_availability_link' => $display['settings']['link'],
          ), 'type' => 'setting');

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
