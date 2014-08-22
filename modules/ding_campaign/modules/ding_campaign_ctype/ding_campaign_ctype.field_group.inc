<?php
/**
 * @file
 * ding_campaign_ctype.field_group.inc
 */

/**
 * Implements hook_field_group_info().
 */
function ding_campaign_ctype_field_group_info() {
  $export = array();

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_ding_campaign_content|node|ding_campaign|form';
  $field_group->group_name = 'group_ding_campaign_content';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'ding_campaign';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Content',
    'weight' => '3',
    'children' => array(
      0 => 'field_camp_link',
      1 => 'field_camp_text_full',
      2 => 'field_camp_text_plain',
      3 => 'field_camp_behavior',
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
  $export['group_ding_campaign_content|node|ding_campaign|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_ding_campaign_images|node|ding_campaign|form';
  $field_group->group_name = 'group_ding_campaign_images';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'ding_campaign';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Images',
    'weight' => '2',
    'children' => array(
      0 => 'field_camp_image',
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
  $export['group_ding_campaign_images|node|ding_campaign|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_ding_campaign_settings|node|ding_campaign|form';
  $field_group->group_name = 'group_ding_campaign_settings';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'ding_campaign';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Settings',
    'weight' => '1',
    'children' => array(
      0 => 'ding_campaign_group_ref',
      1 => 'field_camp_settings',
      2 => 'field_camp_weight',
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
  $export['group_ding_campaign_settings|node|ding_campaign|form'] = $field_group;

  return $export;
}
