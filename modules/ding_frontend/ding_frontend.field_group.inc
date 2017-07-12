<?php
/**
 * @file
 * ding_frontend.field_group.inc
 */

/**
 * Implements hook_field_group_info().
 */
function ding_frontend_field_group_info() {
  $field_groups = array();

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
        'classes' => 'search-left group-left-col-search field-group-div',
        'description' => '',
        'show_label' => '0',
        'label_element' => 'h3',
        'effect' => 'none',
        'speed' => 'fast',
        'id' => 'profile2_ding_staff_profile_full_group_left_col_search',
      ),
      'formatter' => 'open',
    ),
  );
  $field_groups['group_left_col_search|profile2|ding_staff_profile|default'] = $field_group;

  // Translatables
  // Included for use with string extractors like potx.
  t('Left column');

  return $field_groups;
}
