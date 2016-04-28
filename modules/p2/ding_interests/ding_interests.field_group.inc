<?php

/**
 * @file
 * ding_interests.field_group.inc
 */

/**
 * Implements hook_field_group_info().
 */
function ding_interests_field_group_info() {
  $export = array();

  $field_group = new stdClass();
  /* Edit this to true to make a default field_group disabled initially */

  $field_group->disabled = FALSE;
  $field_group->api_version = 1;
  $field_group->identifier = 'group_ding_interests|taxonomy_term|ding_content_tags|form';
  $field_group->group_name = 'group_ding_interests';
  $field_group->entity_type = 'taxonomy_term';
  $field_group->bundle = 'ding_content_tags';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Interesser',
    'weight' => '2',
    'children' => array(
      0 => 'field_search_string',
      1 => 'field_list_image',
      2 => 'field_title_image',
      3 => 'field_status',
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
  $export['group_ding_interests|taxonomy_term|ding_content_tags|form'] = $field_group;

  return $export;
}
