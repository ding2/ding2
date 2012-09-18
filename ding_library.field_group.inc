<?php
/**
 * @file
 * ding_library.field_group.inc
 */

/**
 * Implements hook_field_group_info().
 */
function ding_library_field_group_info() {
  $export = array();

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_ding_library_attachments|node|ding_library|form';
  $field_group->group_name = 'group_ding_library_attachments';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'ding_library';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Attachments',
    'weight' => '6',
    'children' => array(
      0 => 'field_ding_library_geocode',
      1 => 'field_ding_library_links',
      2 => 'field_ding_library_opening_hours',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'label' => 'Attachments',
      'instance_settings' => array(
        'required_fields' => 1,
        'classes' => '',
        'description' => '',
      ),
      'formatter' => 'collapsed',
    ),
  );
  $export['group_ding_library_attachments|node|ding_library|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_ding_library_contact|node|ding_library|form';
  $field_group->group_name = 'group_ding_library_contact';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'ding_library';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Contact',
    'weight' => '3',
    'children' => array(
      0 => 'field_ding_library_addresse',
      1 => 'field_ding_library_fax_number',
      2 => 'field_ding_library_mail',
      3 => 'field_ding_library_phone_number',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'label' => 'Contact',
      'instance_settings' => array(
        'required_fields' => 1,
        'classes' => '',
        'description' => '',
      ),
      'formatter' => 'collapsed',
    ),
  );
  $export['group_ding_library_contact|node|ding_library|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_ding_library_content|node|ding_library|form';
  $field_group->group_name = 'group_ding_library_content';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'ding_library';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Content',
    'weight' => '5',
    'children' => array(
      0 => 'field_ding_library_body',
      1 => 'field_ding_library_lead',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'label' => 'Content',
      'instance_settings' => array(
        'required_fields' => 1,
        'classes' => '',
        'description' => '',
      ),
      'formatter' => 'collapsed',
    ),
  );
  $export['group_ding_library_content|node|ding_library|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_ding_library_images|node|ding_library|form';
  $field_group->group_name = 'group_ding_library_images';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'ding_library';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Images',
    'weight' => '4',
    'children' => array(
      0 => 'field_ding_library_list_image',
      1 => 'field_ding_library_title_image',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'label' => 'Images',
      'instance_settings' => array(
        'required_fields' => 1,
        'classes' => '',
        'description' => '',
      ),
      'formatter' => 'collapsed',
    ),
  );
  $export['group_ding_library_images|node|ding_library|form'] = $field_group;

  return $export;
}
