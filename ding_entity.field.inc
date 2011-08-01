<?php

/**
 * @file
 * Field hook implementations.
 */

/**
 * Implements hook_field_info().
 */
function ding_entity_field_info() {
  return array(
    'ding_entity_buttons' => array(
      'label' => t('Action buttons.'),
      'description' => t('Action buttons.'),
      'default_widget' => 'hidden',
      'default_formatter' => 'ding_entity_buttons_default',
      'no_ui' => TRUE,
    ),
  );
}

/**
 * Implements hook_field_load().
 */
function ding_entity_field_load($entity_type, $entities, $field, $instances, $langcode, &$items, $age) {
  foreach ($entities as $id => $entity) {
    $items[$id][0] = array(
      'id' => $id,
    );
  }
}

/**
 * Implements hook_widget_info_alter().
 */
function ding_entity_widget_info_alter(&$info) {
  if (isset($info['hidden'])) {
    $info['hidden']['field types'][] = 'ding_entity_buttons';
  }
}

/**
 * Implements hook_field_formatter_info().
 */
function ding_entity_field_formatter_info() {
  return array(
    'ding_entity_buttons_default' => array(
      'label' => t('Default'),
      'field types' => array(
        'ding_entity_buttons',
      ),
    )
  );
}

/**
 * Implements hook_field_formatter_view().
 */
function ding_entity_field_formatter_view($entity_type, $entity, $field, $instance, $langcode, $items, $display) {
  $element = array();
  foreach ($items as $delta => $item) {
    $element[$delta] = module_invoke_all('ding_entity_buttons', 'ding_entity', $entity);
  }
  return $element;
}
