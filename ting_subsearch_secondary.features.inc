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
    $data['ting_collection-ting_collection-ting_primary_object']['display']['minimal'] = [
      'label' => 'hidden',
      'module' => 'ting',
      'settings' => [
        'view_mode' => 'minimal',
      ],
      'type' => 'ting_primary_object_default',
      'weight' => 0,
    ]; /* WAS: '' */
  }
  if (isset($data['ting_object-ting_object-ting_author'])) {
    $data['ting_object-ting_object-ting_author']['display']['minimal'] = [
      'label' => 'hidden',
      'module' => 'ting_subsearch_secondary',
      'settings' => [],
      'type' => 'ting_author_minimal',
      'weight' => 2,
    ]; /* WAS: '' */
  }
  if (isset($data['ting_object-ting_object-ting_title'])) {
    $data['ting_object-ting_object-ting_title']['display']['minimal'] = [
      'label' => 'hidden',
      'module' => 'ting_subsearch_secondary',
      'settings' => [
        'link_type' => 'none',
        'prefix_type' => 'no',
      ],
      'type' => 'ting_title_minimal',
      'weight' => 0,
    ]; /* WAS: '' */
  }
  if (isset($data['ting_object-ting_object-ting_type'])) {
    $data['ting_object-ting_object-ting_type']['display']['minimal'] = [
      'label' => 'hidden',
      'module' => 'ting',
      'settings' => [],
      'type' => 'ting_type_default',
      'weight' => 1,
    ]; /* WAS: '' */
  }
}
