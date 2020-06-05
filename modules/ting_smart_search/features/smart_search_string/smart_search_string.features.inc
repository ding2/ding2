<?php
/**
 * @file
 * smart_search_string.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function smart_search_string_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "field_group" && $api == "field_group") {
    return array("version" => "1");
  }
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_views_api().
 */
function smart_search_string_views_api($module = NULL, $api = NULL) {
  return array("api" => "3.0");
}

/**
 * Implements hook_eck_bundle_info().
 */
function smart_search_string_eck_bundle_info() {
  $items = array(
    'ting_type_smart_search_string' => array(
      'machine_name' => 'ting_type_smart_search_string',
      'entity_type' => 'ting_type',
      'name' => 'smart_search_string',
      'label' => 'smart_search_string',
      'config' => array(
        'managed_properties' => array(
          'title' => 'title',
          'uid' => 0,
          'created' => 0,
          'changed' => 0,
          'uuid' => 0,
        ),
      ),
    ),
  );
  return $items;
}

/**
 * Implements hook_eck_entity_type_info().
 */
function smart_search_string_eck_entity_type_info() {
  $items = array(
    'ting_type' => array(
      'name' => 'ting_type',
      'label' => 'ting_type',
      'properties' => array(
        'title' => array(
          'label' => 'Title',
          'type' => 'text',
          'behavior' => 'title',
        ),
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
        'uuid' => array(
          'label' => 'UUID',
          'type' => 'text',
          'behavior' => 'uuid',
        ),
      ),
    ),
  );
  return $items;
}

/**
 * Implements hook_paragraphs_info().
 */
function smart_search_string_paragraphs_info() {
  $items = array(
    'custom_boost_values' => array(
      'name' => 'Custom boost values',
      'bundle' => 'custom_boost_values',
      'locked' => '1',
    ),
  );
  return $items;
}
