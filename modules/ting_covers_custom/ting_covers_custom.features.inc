<?php
/**
 * @file
 * ting_covers_custom.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function ting_covers_custom_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "relation" && $api == "relation_type_default") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_views_api().
 */
function ting_covers_custom_views_api($module = NULL, $api = NULL) {
  return array("api" => "3.0");
}

/**
 * Implements hook_eck_bundle_info().
 */
function ting_covers_custom_eck_bundle_info() {
  $items = array(
    'ting_covers_custom_cover' => array(
      'machine_name' => 'ting_covers_custom_cover',
      'entity_type' => 'ting_covers_custom',
      'name' => 'cover',
      'label' => 'Cover',
    ),
  );
  return $items;
}

/**
 * Implements hook_eck_entity_type_info().
 */
function ting_covers_custom_eck_entity_type_info() {
  $items = array(
    'ting_covers_custom' => array(
      'name' => 'ting_covers_custom',
      'label' => 'Ting custom cover',
      'properties' => array(
        'uid' => array(
          'label' => 'Author',
          'type' => 'integer',
          'behavior' => 'author',
        ),
        'created' => array(
          'label' => 'Created',
          'type' => 'integer',
          'behavior' => 'created',
        ),
        'changed' => array(
          'label' => 'Changed',
          'type' => 'integer',
          'behavior' => 'changed',
        ),
      ),
    ),
  );
  return $items;
}
