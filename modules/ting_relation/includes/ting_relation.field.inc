<?php

/**
 * @file
 * Field hook implementations.
 */

use Ting\TingObjectInterface;

/**
 * Implements hook_field_info().
 *
 * Defines a field type to display relations on ting_entites.
 */
function ting_relation_field_info() {
  return array(
    'ting_relations' => array(
      'label' => t('Ting relations.'),
      'description' => t('Ting relations.'),
      'default_widget' => 'hidden',
      'default_formatter' => 'ting_relations_default',
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
function ting_relation_field_load($entity_type, $entities, $field, $instances, $langcode, &$items, $age) {
  foreach ($entities as $id => $entity) {
    // We could create relations as multiple values here, but it's
    // cached after this hook, so we don't. If you try to load relations here
    // it will load the relations as ting_object, which will call this function
    // which will result in recursive behaviour.
    $items[$id][0] = array(
      'id' => $id,
    );
  }
}

/**
 * Implements hook_widget_info_alter().
 *
 * @todo: what dose this do ?
 */
function ting_relation_widget_info_alter(&$info) {
  if (isset($info['hidden'])) {
    $info['hidden']['field types'][] = 'ting_relations';
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
    ),
  );
}

/**
 * Implements hook_field_formatter_view().
 */
function ting_relation_field_formatter_view($entity_type, $entity, $field, $instance, $langcode, $items, $display) {
  $groups = array();
  // Get relations, default to empty array.
  $relations = $entity->getRelations() ?: [];

  // Get the relation-types and their titles.
  $relation_types = ding_provider_invoke('search', 'supported_relations');

  if (count($relations) > 0) {
    $relations = ding_provider_invoke('search', 'filter_relations', $relations);
  }

  foreach ($relations as $relation) {
    // If basic information about a relation group have not been set yet then
    // add it.
    if (!isset($groups[$relation->type])) {
      $groups[$relation->type] = array(
        '#theme' => 'ting_relations',
        '#title' => $relation_types[$relation->type],
        '#source' => $relation->ac_source,
        '#attributes' => array(
          'class' => array(
            drupal_html_class(preg_replace('/(\B[A-Z]|:)/', '_$1', $relation->type)),
            'ting-relations',
          ),
        ),
        '#relations' => array(),
      );
    }
    // Group relations based on types, so they can be show under the same
    // headline on the page.
    $relation_ra = ding_provider_invoke('search', 'render_inline_relation', $relation);
    $relation_ra['#attributes']['class'][] = 'ting-object-related-item';
    $groups[$relation->type]['#relations'][] = $relation_ra;
  }

  // Add "last" class to last relation in group.
  foreach ($groups as &$group) {
    $group['#relations'][count($group['#relations']) - 1]['#attributes']['class'][] = 'last';
  }

  // Wrap the whole render array into array with an element render theme
  // function. So we have three layers in the render array.
  $element = array(
    '#theme' => 'ting_relation_groups',
    '#groups' => $groups,
  );

  return $element;
}
