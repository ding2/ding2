<?php
/**
 * @file
 * An example field using the Field API.
 *
 * This is updated from Barry Jaspan's presentation at Drupalcon Paris,
 * @link http://acquia.com/community/resources/acquia-tv/intro-field-api-module-developers Video Presentation @endlink
 *
 * Providing a field requires:
 * - Defining a field
 *   - hook_field_info()
 *   - hook_field_schema()
 *   - hook_field_validate()
 *   - hook_field_is_empty()
 *
 * - Defining a formatter for the field (the portion that outputs the field for
 *   display)
 *   - hook_field_formatter_info()
 *   - hook_field_formatter_view()
 *
 * - Defining a widget for the edit form
 *   - hook_field_widget_info()
 *   - hook_field_widget_form()
 *
 * *

 /**
  * Implements hook_field_info()

  * description of field
 */

/**
 * @TODO: Missing description.
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
      'no_ui' => TRUE,
    ),
  );
  return $ret;
}

/**
 * Implements hook_field_formatter_info
 *
 * Notes; 'field types' are passed on to hook_field_formatter_view
 */
function ting_infomedia_field_formatter_info() {
  return array(
    'ting_infomedia_default' => array(
      'label' => t('Default'),
      'field types' => array(
        'ting_infomedia',
      ),
    )
  );
}

/**
 * Implements hook_field_formatter_view()
 */
function ting_infomedia_field_formatter_view($entity_type, $entity, $field, $instance, $langcode, $items, $display) {
  $element = array();
  $id = $entity->ding_entity_id;

  $relation_types = ting_infomedia_get_ting_relations();
  switch($display['type']) {
  case 'ting_infomedia_default' :
    foreach($items as $delta => $items) {
      foreach ($entity->relations as $relation) {
        if(isset($relation_types[$relation->type]) && $entity->ac_source == 'Artikler' ) {
          $element[$delta] = array(
            '#markup' => l(t('Read article'), ting_infomedia_get_article_link($id), array('attributes' => array('class' => 'infomedia_group', 'name'=>$relation->type))),
		      );
        }
      }
    }
    break;
  }

  return $element;
}

/**
 * Parse the entityid and return an url
 *
 * @param String $entityid
 * @return String
 */
function ting_infomedia_get_article_link($entityid) {
  $ids = explode(':', $entityid);
  return 'ting/infomedia/' . $ids[1];
}

/**
 * Implements hook_field_validate
 *
 * @TODO is some kind of validation needed?
 */
function ting_infomedia_field_validate($entity_type, $entity, $field, $instance, $langcode, $items, &$errors) {
  // do nothing
}

/**
 * Implements hook_field_is_empty
 *
 * @TODO: check
 */
function ting_infomedia_is_empty($item, $field) {
  return false;
}

/**
 * Implements hook_field_load().
 * Notes: Define custom load behavior for this module's field types.
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
 * Implements hook_field_formatter_prepare_view
 * Notes; add the field to given item(s)
 * we could also use hook_field_load or hook_field_prepare_view
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

