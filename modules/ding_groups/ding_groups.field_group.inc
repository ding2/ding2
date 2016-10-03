<?php
/**
 * @file
 * ding_groups.field_group.inc
 */

/**
 * Implements hook_field_group_info().
 */
function ding_groups_field_group_info() {
  $export = array();

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_ding_group_content|node|ding_group|form';
  $field_group->group_name = 'group_ding_group_content';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'ding_group';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = '';
  $export['group_ding_group_content|node|ding_group|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_ding_group_images|node|ding_group|form';
  $field_group->group_name = 'group_ding_group_images';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'ding_group';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = '';
  $export['group_ding_group_images|node|ding_group|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_ding_group_tagging|node|ding_group|form';
  $field_group->group_name = 'group_ding_group_tagging';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'ding_group';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = '';
  $export['group_ding_group_tagging|node|ding_group|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_left_col_search|node|ding_group|search_result';
  $field_group->group_name = 'group_left_col_search';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'ding_group';
  $field_group->mode = 'search_result';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Left column',
    'weight' => '0',
    'children' => array(
      0 => 'field_ding_group_list_image',
    ),
    'format_type' => 'div',
    'format_settings' => array(
      'label' => 'Left column',
      'instance_settings' => array(
        'classes' => 'search-left',
        'description' => '',
        'show_label' => '0',
        'label_element' => 'h3',
        'effect' => 'none',
        'speed' => 'none',
      ),
      'formatter' => 'open',
    ),
  );
  $export['group_left_col_search|node|ding_group|search_result'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_right_col_search|node|ding_group|search_result';
  $field_group->group_name = 'group_right_col_search';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'ding_group';
  $field_group->mode = 'search_result';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Right column',
    'weight' => '1',
    'children' => array(
      0 => 'field_ding_group_category',
      1 => 'field_ding_group_lead',
    ),
    'format_type' => 'div',
    'format_settings' => array(
      'label' => 'Right column',
      'instance_settings' => array(
        'classes' => 'search-right',
        'description' => '',
        'show_label' => '0',
        'label_element' => 'h3',
        'effect' => 'none',
        'speed' => 'none',
      ),
      'formatter' => 'open',
    ),
  );
  $export['group_right_col_search|node|ding_group|search_result'] = $field_group;

  return $export;
}
