<?php
/**
 * @file
 * ting_field_search.field_group.inc
 */

/**
 * Implements hook_field_group_info().
 */
function ting_field_search_field_group_info() {
  $field_groups = array();

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_profile_placements|node|ting_field_search_search_guide|form';
  $field_group->group_name = 'group_profile_placements';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'ting_field_search_search_guide';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Add this search guide to profile pages',
    'weight' => '12',
    'children' => array(
      0 => 'field_profile_page_placment',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'label' => 'Add this search guide to profile pages',
      'instance_settings' => array(
        'required_fields' => 1,
        'id' => '',
        'classes' => 'group-profile-placements field-group-fieldset',
        'description' => '',
      ),
      'formatter' => 'open',
    ),
  );
  $field_groups['group_profile_placements|node|ting_field_search_search_guide|form'] = $field_group;

  // Translatables
  // Included for use with string extractors like potx.
  t('Add this search guide to profile pages');

  return $field_groups;
}
