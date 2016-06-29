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
  $relation_types = ting_relation_inline();
  $entity->getRelations();
  foreach ($entity->relations as $rid => $relation) {
    if (isset($relation_types[$relation->type])) {
      // The isPartOfManifestion relation has all relation to other libraries
      // copies of the relation, so we filter the ones that do not belong to
      // current library.
      $owner_id = is_object($relation->object) ? $relation->object->getOwnerId() : NULL;
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
        '#title' => ting_relation_get_title($relation),
        '#abstract' => ting_relation_get_abstract($relation),
        '#online' => ting_relation_get_online_url($relation),
        '#target' => ting_relation_get_target($relation),
        '#relation' => $relation,
        '#attributes' => array(
          'class' => array(
            'ting-object-related-item',
          ),
        ),
      );
    }
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

/**
 * Some relations are requested NOT to load a new window.
 * @see http://platform.dandigbib.org/issues/378.
 *
 *
 * @param $relation
 * @return string _blank | _self
 *  Target attribute for link.
 */
function ting_relation_get_target($relation) {
  $target = '_blank';
  $data = isset($relation->getObject()->reply->relationsData) ?
    $relation->getObject()->reply->relationsData : NULL;
  if (isset($data)) {
    if (strpos($data[0]->relationUri, '[useraccessinfomedia]') === 0) {
      $target = '_self';
    }
  }
  return $target;
}



/**
 * Finds the best title for a relation based on the relation type.
 *
 * @param TingRelation $relation
 *   The relation entity to get title from.
 *
 * @return string|bool
 *   The title found in the object or FALSE if non found.
 */
function ting_relation_get_title($relation) {
  // Set default fallback title.
  $title = isset($relation->object->title) ? $relation->object->title : FALSE;

  // Find better title based on relation type.
  switch ($relation->type) {
    case 'dbcaddi:hasReview':
      // If the relation has "isPartOf" it's always a better title than the one
      // in  object title as it is always "Anmeldelse".
      $is_part_of = $relation->object->getIsPartOf();
      if (!empty($is_part_of)) {
        $title = reset($is_part_of);
      }
      break;
  }

  return $title;
}

/**
 * Get the abstract from a TingRelation entity based on its type.
 *
 * @param TingRelation $relation
 *   The relation entity to get abstract from.
 *
 * @return string|bool
 *   The abstract found or FALSE if non found.
 */
function ting_relation_get_abstract($relation) {
  $abstract = FALSE;
  switch ($relation->type) {
    case 'dbcaddi:hasReview':
    case 'dbcaddi:hasSubjectDescription':
    case 'dbcaddi:hasCreatorDescription':
    case 'dbcaddi:hasDescriptionFromPublisher':

      $abstract = $relation->object->getDescription();
      if (empty($abstract)) {
        $abstract = $relation->object->getAbstract();
      }
      break;

    case 'dbcaddi:hasCreatorHomePage':
      // This type of relation is basically a link without an object in the
      // data well.
      $abstract = t('You can find more information about the material on the creators homapge.');
      break;

    case 'dbcbib:isPartOfManifestation':
      $abstract = $relation->object->getSerieDescription();
      break;
  }

  return empty($abstract) ? FALSE : $abstract;
}

/**
 * Get the online url from a TingRelation entity based on its type.
 *
 * @param TingRelation $relation
 *   The relation entity to get abstract from.
 *
 * @return array|bool
 *   The online url found or FALSE if non found.
 */
function ting_relation_get_online_url($relation) {
  $url = FALSE;
  $title = '';
  switch ($relation->type) {
    case 'dbcaddi:hasReview':
    case 'dbcaddi:hasSubjectDescription':
    case 'dbcaddi:hasCreatorDescription':
      // Reservable sources is library material.
      $reservable_sources = variable_get('ting_reservable_sources', _ting_default_reservable_sources());
      if (in_array(strtolower($relation->object->getAc_source()), $reservable_sources)) {
        $title = t('Read more about the material');
        $url = '/ting/object/' . $relation->object->id;
      }
      else {
        $title = t('Read more at %source', array('%source' => $relation->object->getAc_source()));
        $url = $relation->object->getOnline_url();
        $url = empty($url) ? FALSE : $url;

        // Try to make a better link text as part of can contain series
        // information etc.
        $is_part_of = $relation->object->getIsPartOf();
        if (!empty($is_part_of)) {
          $title = reset($is_part_of);
        }
      }
      break;

    case 'dbcaddi:hasDescriptionFromPublisher':
      // This type have a doc-book "read more" link, which is handled by
      // ting_fulltext.
      break;

    case 'dbcaddi:hasCreatorHomePage':
      // This type of relation is basically a link without an object in the
      // data well.
      $url = $relation->uri;
      $title = $relation->uri;
      break;

    case 'dbcbib:isPartOfManifestation':
      $uri = entity_uri('ting_object', $relation->getObject());
      $url = '/' . $uri['path'];
      $title = $relation->object->getTitle();
      break;
  }

  // If url was found return an array with the url and title.
  if ($url) {
    return array(
      'url' => $url,
      'title' => $title,
    );
  }

  // No url found so return FALSE;
  return $url;
}
