<?php

/**
 * @file
 * Field hook implementations.
 */

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
  $relation_types = ting_relation_inline();
  foreach ($entity->relations as $relation) {
    if (isset($relation_types[$relation->type])) {
      // The isPartOfManifestion relation has all relation to other libraries
      // copies of the relation, so we filter the ones that do not belong to
      // current library.
      $owner_id = is_object($relation->object) ? $relation->object->getOwnerId : NULL;
      if ($relation->type == 'isPartOfManifestation' && variable_get('ting_agency', -1) != $owner_id) {
        continue;
      }

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
      $groups[$relation->type]['#relations'][] = array(
        '#theme' => 'ting_relation',
        '#title' => $relation->object->title,
        '#abstract' => ting_relation_get_abstract($relation),
        '#online' => ting_relation_get_online_url($relation),
        '#relation' => $relation,
      );
    }
  }

  // Wrap the whole render array into array with an element render theme
  // function. So we have three layers in the render array.
  $element = array(
    '#theme' => 'ting_relation_groups',
    '#groups' => $groups,
    '#attached' => array(
      'css' => array(drupal_get_path('module', 'ting_relation') . '/ting_relation.css'),
    ),
  );

  return $element;
}

function ting_relation_get_abstract($relation) {
  $abstract = FALSE;
  switch ($relation->type) {
    case 'dbcaddi:hasReview':
      $abstract = $relation->object->getDescription();
      if (empty($abstract)) {
        $abstract = $relation->object->getAbstract();
      }
      $abstract = empty($abstract) ? FALSE : $abstract;
      break;

    case 'dbcaddi:hasSubjectDescription':
//      $variables['content'][$ns] = ting_relation_subjects($relations);
      break;

    case 'dbcaddi:hasCreatorDescription':
//      $variables['content'][$ns] = ting_relation_creator_description($relations);
      break;

    case 'isPartOfManifestation':
//      $variables['content'][$ns] = ting_relation_is_part_of_manifestation($relations);
      break;

    default:
      break;
  }

  return $abstract;
}

function ting_relation_get_online_url($relation) {
  $url = FALSE;
  $title = '';
  switch ($relation->type) {
    case 'dbcaddi:hasReview':
      $title = $relation->object->getAc_source();
      $url = $relation->object->getOnline_url();
      if (empty($url)) {
        $url = $relation->object->getOnline_url();
      }
      $url = empty($url) ? FALSE : $url;

      // Try to make a better link text.
      $is_part_of = $relation->object->getIsPartOf();
      if (!empty($is_part_of)) {
        $title = reset($is_part_of);
      }

      break;

    case 'dbcaddi:hasSubjectDescription':
//      $variables['content'][$ns] = ting_relation_subjects($relations);
      break;

    case 'dbcaddi:hasCreatorDescription':
//      $variables['content'][$ns] = ting_relation_creator_description($relations);
      break;

    case 'isPartOfManifestation':
//      $variables['content'][$ns] = ting_relation_is_part_of_manifestation($relations);
      break;

    default:
      break;
  }

  if ($url) {
    return array(
      'url' => $url,
      'title' => $title,
    );
  }

  return FALSE;
}
