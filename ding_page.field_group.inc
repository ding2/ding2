<?php
/**
 * @file
 * ding_page.field_group.inc
 */

/**
 * Implements hook_field_group_info().
 */
function ding_page_field_group_info() {
  $export = array();

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_ding_event_attachments|node|ding_page|form';
  $field_group->group_name = 'group_ding_event_attachments';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'ding_page';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Attachments',
    'weight' => '3',
    'children' => array(
      0 => 'field_ding_page_files',
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
  $export['group_ding_event_attachments|node|ding_page|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_ding_event_content|node|ding_page|form';
  $field_group->group_name = 'group_ding_event_content';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'ding_page';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Content',
    'weight' => '2',
    'children' => array(
      0 => 'field_ding_page_content',
      1 => 'field_ding_page_manchet',
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
  $export['group_ding_event_content|node|ding_page|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_ding_event_images|node|ding_page|form';
  $field_group->group_name = 'group_ding_event_images';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'ding_page';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Images',
    'weight' => '1',
    'children' => array(
      0 => 'field_ding_page_list_image',
      1 => 'field_ding_page_titel_image',
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
  $export['group_ding_event_images|node|ding_page|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_ding_event_tagging|node|ding_page|form';
  $field_group->group_name = 'group_ding_event_tagging';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'ding_page';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Tagging',
    'weight' => '5',
    'children' => array(
      0 => 'field_ding_page_tags',
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
  $export['group_ding_event_tagging|node|ding_page|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_ding_event_ting|node|ding_page|form';
  $field_group->group_name = 'group_ding_event_ting';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'ding_page';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Ting',
    'weight' => '4',
    'children' => array(
      0 => 'field_ding_page_materials',
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
  $export['group_ding_event_ting|node|ding_page|form'] = $field_group;

  return $export;
}
