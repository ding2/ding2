<?php

/**
 * @file
 * Field hook implementations.
 */

/**
 * Implements hook_field_info().
 */
function ding_periodical_field_info() {
  return array(
    'ding_periodical_issues' => array(
      'label' => t('Issue list for periodicals.'),
      'description' => t('Issue list for periodicals.'),
      'default_widget' => 'hidden',
      'default_formatter' => 'ding_periodical_issues_default',
      'no_ui' => TRUE,
    ),
  );
}

/**
 * Implements hook_field_load().
 */
function ding_periodical_field_load($entity_type, $entities, $field, $instances, $langcode, &$items, $age) {
  foreach ($entities as $id => $entity) {
    // Only bother with entities that are periodicals. This is cached, but
    // entities are unlikely to change type.
    if ($entity->is('periodical')) {
      $items[$id][0] = array(
        'provider_id' => $entity->localId,
      );
    }
  }
}

/**
 * Implements hook_widget_info_alter().
 */
function ding_periodical_widget_info_alter(&$info) {
  if (isset($info['hidden'])) {
    $info['hidden']['field types'][] = 'ding_periodical_issues';
  }
}

/**
 * Implements hook_field_formatter_info().
 */
function ding_periodical_field_formatter_info() {
  return array(
    'ding_periodical_issues_default' => array(
      'label' => t('Default'),
      'field types' => array(
        'ding_periodical_issues',
      ),
    ),
  );
}

/**
 * Implements hook_field_formatter_view().
 */
function ding_periodical_field_formatter_view($entity_type, $entity, $field, $instance, $langcode, $items, $display) {
  global $user;
  $element = array();
  foreach ($items as $delta => $item) {

    if( !ding_provider_implements('availability','holdings') ) {
      return $element;
    }

    $availability = ding_provider_invoke('availability', 'holdings', array($entity->provider_id));
    if (isset($availability[$entity->provider_id])) {
      $issues = $availability[$entity->provider_id]['issues'];
      // array_walk($issues, 'asort') complains about 'Notice: A non
      // well formed numeric value encountered'.
       foreach ($issues as $k => $v) {
        asort($v);
      }
      ksort($issues);

      if ($issues) {
        $element[$delta] = array(
          '#theme' => 'ding_periodical_issues',
          '#entity' => $entity,
          '#issues' => $issues,
        );
      }
    }
  }
  return $element;
}
