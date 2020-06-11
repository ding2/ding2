<?php
/**
 * @file
 * ting_field_search.strongarm.inc
 */

/**
 * Implements hook_strongarm().
 */
function ting_field_search_strongarm() {
  $export = array();

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_anonymous_ting_field_search_search_guide';
  $strongarm->value = 0;
  $export['comment_anonymous_ting_field_search_search_guide'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_default_mode_ting_field_search_search_guide';
  $strongarm->value = 1;
  $export['comment_default_mode_ting_field_search_search_guide'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_default_per_page_ting_field_search_search_guide';
  $strongarm->value = '50';
  $export['comment_default_per_page_ting_field_search_search_guide'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_form_location_ting_field_search_search_guide';
  $strongarm->value = 1;
  $export['comment_form_location_ting_field_search_search_guide'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_preview_ting_field_search_search_guide';
  $strongarm->value = '0';
  $export['comment_preview_ting_field_search_search_guide'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_subject_field_ting_field_search_search_guide';
  $strongarm->value = 1;
  $export['comment_subject_field_ting_field_search_search_guide'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_ting_field_search_search_guide';
  $strongarm->value = '1';
  $export['comment_ting_field_search_search_guide'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'field_bundle_settings_node__ting_field_search_search_guide';
  $strongarm->value = array(
    'view_modes' => array(),
    'extra_fields' => array(
      'form' => array(
        'metatags' => array(
          'weight' => '4',
        ),
        'title' => array(
          'weight' => '0',
        ),
        'path' => array(
          'weight' => '1',
        ),
        'redirect' => array(
          'weight' => '2',
        ),
      ),
      'display' => array(),
    ),
  );
  $export['field_bundle_settings_node__ting_field_search_search_guide'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'language_content_type_ting_field_search_search_guide';
  $strongarm->value = '0';
  $export['language_content_type_ting_field_search_search_guide'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'menu_options_ting_field_search_search_guide';
  $strongarm->value = array();
  $export['menu_options_ting_field_search_search_guide'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'menu_parent_ting_field_search_search_guide';
  $strongarm->value = 'main-menu:0';
  $export['menu_parent_ting_field_search_search_guide'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'node_options_ting_field_search_search_guide';
  $strongarm->value = array(
    0 => 'status',
  );
  $export['node_options_ting_field_search_search_guide'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'node_preview_ting_field_search_search_guide';
  $strongarm->value = 0;
  $export['node_preview_ting_field_search_search_guide'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'node_submitted_ting_field_search_search_guide';
  $strongarm->value = 0;
  $export['node_submitted_ting_field_search_search_guide'] = $strongarm;

  return $export;
}
