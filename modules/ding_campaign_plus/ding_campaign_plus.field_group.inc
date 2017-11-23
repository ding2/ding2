<?php
/**
 * @file
 * ding_campaign_plus.field_group.inc
 */

/**
 * Implements hook_field_group_info().
 */
function ding_campaign_plus_field_group_info() {
  $field_groups = array();

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_ding_campaign_plus_content|node|ding_campaign_plus|form';
  $field_group->group_name = 'group_ding_campaign_plus_content';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'ding_campaign_plus';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Content',
    'weight' => '1',
    'children' => array(
      0 => 'field_ding_campaign_plus_image',
      1 => 'field_ding_campaign_plus_link',
      2 => 'field_ding_campaign_plus_text',
      3 => 'field_ding_campaign_plus_type',
      4 => 'field_ding_campaign_plus_style',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'formatter' => 'collapsible',
      'instance_settings' => array(
        'description' => '',
        'classes' => 'group-ding-campaign-plus-content field-group-fieldset',
        'required_fields' => 1,
        'id' => '',
      ),
    ),
  );
  $field_groups['group_ding_campaign_plus_content|node|ding_campaign_plus|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_ding_campaign_plus_trig|node|ding_campaign_plus|form';
  $field_group->group_name = 'group_ding_campaign_plus_trig';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'ding_campaign_plus';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Campaign triggers',
    'weight' => '1',
    'children' => array(),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'formatter' => 'collapsible',
      'instance_settings' => array(
        'description' => '',
        'classes' => 'group-ding-campaign-plus-trig field-group-fieldset',
        'required_fields' => 1,
        'id' => '',
      ),
    ),
  );
  $field_groups['group_ding_campaign_plus_trig|node|ding_campaign_plus|form'] = $field_group;

  // Translatables
  // Included for use with string extractors like potx.
  t('Campaign triggers');
  t('Content');

  return $field_groups;
}
