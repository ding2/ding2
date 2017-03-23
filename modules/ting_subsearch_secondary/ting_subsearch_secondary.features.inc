<?php
/**
 * @file
 * ting_subsearch_secondary.features.inc
 */

/**
 * Implements hook_field_default_field_instances_alter().
 */
function ting_subsearch_secondary_field_default_field_instances_alter(&$data) {
  if (isset($data['ting_collection-ting_collection-ting_primary_object'])) {
    $data['ting_collection-ting_collection-ting_primary_object']['display']['minimal'] = array(
      'label' => 'hidden',
      'module' => 'ting',
      'settings' => array(
        'view_mode' => 'minimal',
      ),
      'type' => 'ting_primary_object_default',
      'weight' => 0,
    ); /* WAS: '' */
  }
  if (isset($data['ting_object-ting_object-ting_author'])) {
    $data['ting_object-ting_object-ting_author']['display']['minimal'] = array(
      'label' => 'hidden',
      'module' => 'ting_subsearch_secondary',
      'settings' => array(),
      'type' => 'ting_author_minimal',
      'weight' => 2,
    ); /* WAS: '' */
  }
  if (isset($data['ting_object-ting_object-ting_title'])) {
    $data['ting_object-ting_object-ting_title']['display']['minimal'] = array(
      'label' => 'hidden',
      'module' => 'ting_subsearch_secondary',
      'settings' => array(
        'link_type' => 'none',
        'prefix_type' => 'no',
      ),
      'type' => 'ting_title_minimal',
      'weight' => 0,
    ); /* WAS: '' */
  }
  if (isset($data['ting_object-ting_object-ting_type'])) {
    $data['ting_object-ting_object-ting_type']['display']['minimal'] = array(
      'label' => 'hidden',
      'module' => 'ting',
      'settings' => array(),
      'type' => 'ting_type_default',
      'weight' => 1,
    ); /* WAS: '' */
  }
}
