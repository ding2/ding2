<?php
/**
 * @file
 * bpi_features.field_group.inc
 */

/**
 * Implements hook_field_group_info().
 */
function bpi_features_field_group_info() {
  $field_groups = array();

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_workflow|node|ding_news|form';
  $field_group->group_name = 'group_workflow';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'ding_news';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'BPI',
    'weight' => '36',
    'children' => array(
      0 => 'field_bpi_workflow',
    ),
    'format_type' => 'tab',
    'format_settings' => array(
      'label' => 'BPI',
      'instance_settings' => array(
        'required_fields' => 0,
        'classes' => ' group-workflow field-group-tab',
        'description' => 'Data in this group will only be saved when "Save and push" is used.',
      ),
      'formatter' => 'closed',
    ),
  );
  $field_groups['group_workflow|node|ding_news|form'] = $field_group;

  // Translatables
  // Included for use with string extractors like potx.
  t('BPI');

  return $field_groups;
}
