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
    'weight' => '8',
    'children' => array(
      0 => 'field_ding_staff_image',
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
        'speed' => 'fast',
      ),
      'formatter' => 'open',
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
    'weight' => '11',
    'children' => array(
      0 => 'field_ding_staff_description',
      1 => 'field_ding_staff_forename',
      2 => 'field_ding_staff_position',
      3 => 'field_ding_staff_surname',
      4 => 'group_contactinfo',
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
        'speed' => 'fast',
      ),
      'formatter' => 'open',
    ),
  );
  $export['group_right_col_search|profile2|ding_staff_profile|default'] = $field_group;

  return $export;
}
