<?php
/**
 * @file
 * ting_material_details.field_group.inc
 */

/**
 * Implements hook_field_group_info().
 */
function ting_material_details_field_group_info() {
  $export = array();

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_material_details|ting_object|ting_object|default';
  $field_group->group_name = 'group_material_details';
  $field_group->entity_type = 'ting_object';
  $field_group->bundle = 'ting_object';
  $field_group->mode = 'default';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Material details',
    'weight' => '2',
    'children' => array(
      0 => 'ting_details_type',
      1 => 'ting_details_format',
      2 => 'ting_details_ispartof',
      3 => 'ting_details_language',
      4 => 'ting_details_spoken',
      5 => 'ting_details_subtitles',
      6 => 'ting_details_genre',
      7 => 'ting_details_subjects',
      8 => 'ting_details_classification',
      9 => 'ting_details_spatial',
      10 => 'ting_details_contributor',
      11 => 'ting_details_musician',
      12 => 'ting_details_tracks',
      13 => 'ting_details_referenced',
      14 => 'ting_details_description',
      15 => 'ting_details_seriesdescription',
      16 => 'ting_details_source',
      17 => 'ting_details_replaces',
      18 => 'ting_details_replaced_by',
      19 => 'ting_details_isbn',
      20 => 'ting_details_version',
      21 => 'ting_details_extent',
      22 => 'ting_details_publisher',
      23 => 'ting_details_rights',
      24 => 'ting_details_audience',
      25 => 'ting_details_age',
      26 => 'ting_details_pegi',
    ),
    'format_type' => 'div',
    'format_settings' => array(
      'label' => 'Material details',
      'instance_settings' => array(
        'classes' => '',
        'description' => '',
        'show_label' => '1',
        'label_element' => 'h2',
        'effect' => 'none',
        'speed' => 'fast',
      ),
      'formatter' => 'collapsed',
    ),
  );
  $export['group_material_details|ting_object|ting_object|default'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_material_details|ting_object|ting_object|form';
  $field_group->group_name = 'group_material_details';
  $field_group->entity_type = 'ting_object';
  $field_group->bundle = 'ting_object';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Material details',
    'weight' => '12',
    'children' => array(
      0 => 'ting_details_age',
      1 => 'ting_details_audience',
      2 => 'ting_details_classification',
      3 => 'ting_details_contributor',
      4 => 'ting_details_description',
      5 => 'ting_details_extent',
      6 => 'ting_details_format',
      7 => 'ting_details_genre',
      8 => 'ting_details_isbn',
      9 => 'ting_details_ispartof',
      10 => 'ting_details_language',
      11 => 'ting_details_musician',
      12 => 'ting_details_pegi',
      13 => 'ting_details_publisher',
      14 => 'ting_details_referenced',
      15 => 'ting_details_replaced_by',
      16 => 'ting_details_replaces',
      17 => 'ting_details_rights',
      18 => 'ting_details_source',
      19 => 'ting_details_spatial',
      20 => 'ting_details_spoken',
      21 => 'ting_details_subjects',
      22 => 'ting_details_subtitles',
      23 => 'ting_details_tracks',
      24 => 'ting_details_type',
      25 => 'ting_details_uri',
      26 => 'ting_details_version',
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
  $export['group_material_details|ting_object|ting_object|form'] = $field_group;

  return $export;
}
