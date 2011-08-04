<?php

/**
 * @file
 * Field hook implementations.
 */

/**
 * Implements hook_field_info().
 */
function ting_relation_field_info() {
  return array(
    'ting_relations' => array(
      'label' => t('Ting relations.'),
      'description' => t('Ting relations.'),
      'default_widget' => 'hidden',
      'default_formatter' => 'ting_relations_default',
      'no_ui' => TRUE,
    ),
  );
}

/**
 * Implements hook_field_load().
 */
function ting_relation_field_load($entity_type, $entities, $field, $instances, $langcode, &$items, $age) {
  foreach ($entities as $id => $entity) {
    // We could create relations as multiple values here, but it's
    // cached after this hook, so we don't.
    $items[$id][0] = array(
      'id' => $id,
    );
  }
}

/**
 * Implements hook_widget_info_alter().
 */
function ting_relation_widget_info_alter(&$info) {
  if (isset($info['hidden'])) {
    $info['hidden']['field types'][] = 'ding_entity_buttons';
  }
}

/**
 * Implements hook_field_formatter_info().
 */
function ting_relation_field_formatter_info() {
  return array(
    'ting_relations_default' => array(
      'label' => t('Default'),
      'field types' => array(
        'ting_relations',
      ),
    )
  );
}

/**
 * Implements hook_field_formatter_view().
 */
function ting_relation_field_formatter_view($entity_type, $entity, $field, $instance, $langcode, $items, $display) {
  $element = array();
  $relation_types = ting_relation_inline();
  foreach ($items as $delta => $item) {
    foreach ($entity->relations as $relation) {
      if (isset($relation_types[$relation->relationType])) {
        $element[$delta][] = array(
          '#theme' => 'ting_relation',
          '#object' => $relation,
          '#title' => $relation_types[$relation->relationType],
          '#attached' => array(
            'css' => array(drupal_get_path('module', 'ting_relation') . '/ting_relation.css'),
          ),
        );
      }
    }
  }
  return $element;
}
