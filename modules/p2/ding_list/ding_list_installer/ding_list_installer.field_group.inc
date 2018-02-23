<?php
/**
 * @file
 * ding_list_installer.field_group.inc
 */

/**
 * Implements hook_field_group_info().
 */
function ding_list_installer_field_group_info() {
  $field_groups = array();

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_material_in_public_lists|ting_object|ting_object|default';
  $field_group->group_name = 'group_material_in_public_lists';
  $field_group->entity_type = 'ting_object';
  $field_group->bundle = 'ting_object';
  $field_group->mode = 'default';
  $field_group->parent_name = 'group_ting_object_right_column';
  $field_group->data = array(
    'label' => 'Lists that include this title',
    'weight' => '6',
    'children' => array(
      0 => 'ding_list_in_public_lists',
    ),
    'format_type' => 'div',
    'format_settings' => array(
      'label' => 'Lists that include this title',
      'instance_settings' => array(
        'id' => '',
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
  $field_groups['group_material_in_public_lists|ting_object|ting_object|default'] = $field_group;

  // Translatables
  // Included for use with string extractors like potx.
  t('Lists that include this title');

  return $field_groups;
}
