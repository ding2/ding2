<?php
/**
 * @file
 * ding_event.field_group.inc
 */

/**
 * Implements hook_field_group_info().
 */
function ding_event_field_group_info() {
  $export = array();

  $field_group = new stdClass;
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_date_place|node|ding_event|default';
  $field_group->group_name = 'group_date_place';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'ding_event';
  $field_group->mode = 'default';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Date',
    'weight' => '2',
    'children' => array(
      0 => 'ding_event_address',
      1 => 'ding_event_date',
      2 => 'ding_event_library',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'label' => 'Date',
      'instance_settings' => array(
        'classes' => 'date-place',
        'description' => '',
      ),
      'formatter' => 'open',
    ),
  );
  $export['group_date_place|node|ding_event|default'] = $field_group;

  return $export;
}
