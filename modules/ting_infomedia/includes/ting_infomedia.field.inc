<?php

/**
 * @file
 * Infomedia field for ting objects.
 */

/**
 * Implements hook_field_info().
 */
function ting_infomedia_field_info() {
  $ret = array(
    'ting_infomedia' => array(
      'label' => t('A link to infomedia articles'),
      'description' => t('This field links to infomedia articles'),
      'settings' => array(
        'max_length' => 255,
      ),
      'default_widget' => 'hidden',
      'default_formatter' => 'ting_infomedia_default',
      'virtual_field' => array(
        'entity_types' => array('ting_object'),
        'add_widget' => TRUE,
      ),
    ),
  );
  return $ret;
}

/**
 * Implements hook_field_formatter_info().
 */
function ting_infomedia_field_formatter_info() {
  return array(
    'ting_infomedia_default' => array(
      'label' => t('Default'),
      'field types' => array(
        'ting_infomedia',
      ),
    ),
  );
}

/**
 * Implements hook_field_formatter_view().
 */
function ting_infomedia_field_formatter_view($entity_type, $entity, $field, $instance, $langcode, $items, $display) {
  $element = array();
  $id = $entity->ding_entity_id;

  $relation_types = ting_infomedia_get_ting_relations();
  switch ($display['type']) {
    case 'ting_infomedia_default':
      foreach ($items as $delta => $items) {
        foreach ($entity->relations as $relation) {
          if (isset($relation_types[$relation->type]) && $entity->ac_source == 'Artikler') {
            $element[$delta] = array(
              '#markup' => l(t('Read article'),
                         ting_infomedia_get_article_link($id),
                         array(
                           'attributes' => array(
                             'class' => 'infomedia_group',
                             'name' => $relation->type,
                           ),
                         )),
            );
          }
        }
      }
      break;
  }

  return $element;
}

/**
 * Parse the entityid and return an url for it.
 *
 * @param string $entityid
 *   Id of entity to link to.
 *
 * @return string
 *   Internal link.
 */
function ting_infomedia_get_article_link($entityid) {
  $ids = explode(':', $entityid);
  return 'ting/infomedia/' . $ids[1];
}

/**
 * Implements hook_field_validate().
 */
function ting_infomedia_field_validate($entity_type, $entity, $field, $instance, $langcode, $items, &$errors) {
  // Do nothing.
}

/**
 * Implements hook_field_is_empty().
 */
function ting_infomedia_is_empty($item, $field) {
  return FALSE;
}

/**
 * Implements hook_field_load().
 */
function ting_infomedia_field_load($entity_type, $entities, $field, $instances, $langcode, &$items, $age) {
  foreach ($entities as $id => $entity) {
    // We could create relations as multiple values here, but it's
    // cached after this hook, so we don't.
    $items[$id][0] = array(
      'id' => $id,
    );
  }
}

/**
 * Implements hook_field_formatter_prepare_view().
 */
function ting_infomedia_field_formatter_prepare_view($entity_type, $entities, $field, $instances, $langcode, &$items, $displays) {
  foreach ($entities as $id => $entity) {
    // We could create relations as multiple values here, but it's
    // cached after this hook, so we don't.
    $items[$id][0] = array(
      'id' => $id,
    );
  }
}
