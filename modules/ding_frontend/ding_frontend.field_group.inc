<?php
/**
 * @file
 * ding_frontend.field_group.inc
 */

/**
 * Implements hook_field_group_info().
 */
function ding_frontend_field_group_info() {
  $export = array();

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_left_col_search|profile2|ding_staff_profile|default';
  $field_group->group_name = 'group_left_col_search';
  $field_group->entity_type = 'profile2';
  $field_group->bundle = 'ding_staff_profile';
  $field_group->mode = 'default';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Left column',
    'weight' => '2',
    'children' => array(),
    'format_type' => 'hidden',
    'format_settings' => array(
      'formatter' => '',
      'instance_settings' => array(),
    ),
  );
  $export['group_left_col_search|profile2|ding_staff_profile|default'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_right_col_search|profile2|ding_staff_profile|default';
  $field_group->group_name = 'group_right_col_search';
  $field_group->entity_type = 'profile2';
  $field_group->bundle = 'ding_staff_profile';
  $field_group->mode = 'default';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Right column',
    'weight' => '3',
    'children' => array(),
    'format_type' => 'hidden',
    'format_settings' => array(
      'formatter' => '',
      'instance_settings' => array(),
    ),
  );
  $export['group_right_col_search|profile2|ding_staff_profile|default'] = $field_group;

  return $export;
}
