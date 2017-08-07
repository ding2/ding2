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
  $field_group->data = array(
    'label' => 'Content',
    'weight' => '2',
    'children' => array(
      0 => 'field_ding_group_lead',
      1 => 'field_ding_group_body',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'formatter' => 'collapsible',
      'instance_settings' => array(
        'description' => '',
        'classes' => '',
        'required_fields' => 1,
      ),
    ),
  );
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
  $field_group->data = array(
    'label' => 'Images',
    'weight' => '1',
    'children' => array(
      0 => 'field_ding_group_title_image',
      1 => 'field_ding_group_list_image',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'label' => 'Images',
      'instance_settings' => array(
        'required_fields' => 1,
        'classes' => '',
        'description' => '',
      ),
      'formatter' => 'collapsed',
    ),
  );
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
  $field_group->data = array(
    'label' => 'Tagging',
    'weight' => '3',
    'children' => array(
      0 => 'field_ding_group_category',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'formatter' => 'collapsible',
      'instance_settings' => array(
        'description' => '',
        'classes' => '',
        'required_fields' => 1,
      ),
    ),
  );
  $export['group_ding_group_tagging|node|ding_group|form'] = $field_group;

  return $export;
}
