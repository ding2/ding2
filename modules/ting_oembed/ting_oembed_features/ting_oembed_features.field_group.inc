<?php
/**
 * @file
 * ting_oembed_features.field_group.inc
 */

/**
 * Implements hook_field_group_info().
 */
function ting_oembed_features_field_group_info() {
  $export = array();

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_oembed|ting_object|ting_object|default';
  $field_group->group_name = 'group_oembed';
  $field_group->entity_type = 'ting_object';
  $field_group->bundle = 'ting_object';
  $field_group->mode = 'default';
  $field_group->parent_name = 'group_ting_object_right_column';
  $field_group->data = array(
    'label' => 'Material content',
    'weight' => '6',
    'children' => array(
      0 => 'field_ting_oembed_oembed',
    ),
    'format_type' => 'div',
    'format_settings' => array(
      'label' => 'Material content',
      'instance_settings' => array(
        'classes' => '',
        'description' => '',
        'show_label' => '1',
        'label_element' => 'h2',
        'effect' => 'none',
        'speed' => 'fast',
      ),
      'formatter' => 'collapsible',
    ),
  );
  $export['group_oembed|ting_object|ting_object|default'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_oembed|ting_object|ting_object|form';
  $field_group->group_name = 'group_oembed';
  $field_group->entity_type = 'ting_object';
  $field_group->bundle = 'ting_object';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'oEmbed',
    'weight' => '13',
    'children' => array(
      0 => 'field_ting_oembed_oembed',
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
  $export['group_oembed|ting_object|ting_object|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_ting_object_right_column|ting_object|ting_object|default';
  $field_group->group_name = 'group_ting_object_right_column';
  $field_group->entity_type = 'ting_object';
  $field_group->bundle = 'ting_object';
  $field_group->mode = 'default';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Right column',
    'weight' => '1',
    'children' => array(
      0 => 'ding_entity_buttons',
      1 => 'ting_abstract',
      2 => 'ting_author',
      3 => 'ting_series',
      4 => 'ting_subjects',
      5 => 'ting_title',
      6 => 'ting_type',
      7 => 'group_oembed',
    ),
    'format_type' => 'div',
    'format_settings' => array(
      'label' => 'Right column',
      'instance_settings' => array(
        'classes' => 'ting-object-right',
        'description' => '',
        'show_label' => '0',
        'label_element' => 'h3',
        'effect' => 'none',
        'speed' => 'none',
      ),
      'formatter' => 'open',
    ),
  );
  $export['group_ting_object_right_column|ting_object|ting_object|default'] = $field_group;

  return $export;
}
