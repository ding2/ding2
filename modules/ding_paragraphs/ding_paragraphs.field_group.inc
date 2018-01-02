<?php
/**
 * @file
 * ding_paragraphs.field_group.inc
 */

/**
 * Implements hook_field_group_info().
 */
function ding_paragraphs_field_group_info() {
  $field_groups = array();

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_ting_left_col_collection|ting_object|ting_object|paragraphs_teaser';
  $field_group->group_name = 'group_ting_left_col_collection';
  $field_group->entity_type = 'ting_object';
  $field_group->bundle = 'ting_object';
  $field_group->mode = 'paragraphs_teaser';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Left column',
    'weight' => '1',
    'children' => array(
      0 => 'ting_cover',
    ),
    'format_type' => 'div',
    'format_settings' => array(
      'label' => 'Left column',
      'instance_settings' => array(
        'id' => '',
        'classes' => 'ting-object-left',
        'description' => '',
        'show_label' => '0',
        'label_element' => 'h3',
        'effect' => 'none',
        'speed' => 'none',
      ),
      'formatter' => 'open',
    ),
  );
  $field_groups['group_ting_left_col_collection|ting_object|ting_object|paragraphs_teaser'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_ting_right_col_collection|ting_object|ting_object|paragraphs_teaser';
  $field_group->group_name = 'group_ting_right_col_collection';
  $field_group->entity_type = 'ting_object';
  $field_group->bundle = 'ting_object';
  $field_group->mode = 'paragraphs_teaser';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Right column',
    'weight' => '2',
    'children' => array(
      0 => 'ting_abstract',
      1 => 'ting_author',
      2 => 'ting_title',
      3 => 'ting_type',
    ),
    'format_type' => 'div',
    'format_settings' => array(
      'label' => 'Right column',
      'instance_settings' => array(
        'id' => '',
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
  $field_groups['group_ting_right_col_collection|ting_object|ting_object|paragraphs_teaser'] = $field_group;

  // Translatables
  // Included for use with string extractors like potx.
  t('Left column');
  t('Right column');

  return $field_groups;
}
