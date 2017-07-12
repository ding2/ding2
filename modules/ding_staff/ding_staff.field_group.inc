<?php
/**
 * @file
 * ding_staff.field_group.inc
 */

/**
 * Implements hook_field_group_info().
 */
function ding_staff_field_group_info() {
  $field_groups = array();

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_contactinfo|profile2|ding_staff_profile|default';
  $field_group->group_name = 'group_contactinfo';
  $field_group->entity_type = 'profile2';
  $field_group->bundle = 'ding_staff_profile';
  $field_group->mode = 'default';
  $field_group->parent_name = 'group_right_col_search';
  $field_group->data = array(
    'label' => 'contact info',
    'weight' => '4',
    'children' => array(
      0 => 'field_ding_staff_department',
      1 => 'field_ding_staff_email',
      2 => 'field_ding_staff_phone',
      3 => 'field_ding_staff_work_areas',
      4 => 'og_group_ref',
    ),
    'format_type' => 'div',
    'format_settings' => array(
      'label' => 'contact info',
      'instance_settings' => array(
        'classes' => ' group-contactinfo field-group-div',
        'description' => '',
        'show_label' => '0',
        'label_element' => 'h3',
        'effect' => 'none',
        'speed' => 'fast',
        'id' => 'profile2_ding_staff_profile_full_group_contactinfo',
      ),
      'formatter' => 'open',
    ),
  );
  $field_groups['group_contactinfo|profile2|ding_staff_profile|default'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_ding_staff_contact|profile2|staff|form';
  $field_group->group_name = 'group_ding_staff_contact';
  $field_group->entity_type = 'profile2';
  $field_group->bundle = 'ding_staff_profile';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Contact',
    'weight' => '3',
    'children' => array(
      0 => 'field_ding_staff_email',
      1 => 'field_ding_staff_phone',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'formatter' => 'collapsible',
      'instance_settings' => array(
        'description' => '',
        'classes' => ' group-ding-staff-contact field-group-fieldset',
        'required_fields' => 1,
      ),
    ),
  );
  $field_groups['group_ding_staff_contact|profile2|staff|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_ding_staff_name|profile2|staff|form';
  $field_group->group_name = 'group_ding_staff_name';
  $field_group->entity_type = 'profile2';
  $field_group->bundle = 'ding_staff_profile';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Name',
    'weight' => '0',
    'children' => array(
      0 => 'field_ding_staff_forename',
      1 => 'field_ding_staff_surname',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'formatter' => 'collapsible',
      'instance_settings' => array(
        'description' => '',
        'classes' => ' group-ding-staff-name field-group-fieldset',
        'required_fields' => 1,
      ),
    ),
  );
  $field_groups['group_ding_staff_name|profile2|staff|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_ding_staff_organisation|profile2|staff|form';
  $field_group->group_name = 'group_ding_staff_organisation';
  $field_group->entity_type = 'profile2';
  $field_group->bundle = 'ding_staff_profile';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Organisation',
    'weight' => '2',
    'children' => array(
      0 => 'field_ding_staff_department',
      1 => 'field_ding_staff_position',
      2 => 'og_group_ref',
      3 => 'field_ding_staff_work_areas',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'formatter' => 'collapsible',
      'instance_settings' => array(
        'description' => '',
        'classes' => ' group-ding-staff-organisation field-group-fieldset',
        'required_fields' => 1,
      ),
    ),
  );
  $field_groups['group_ding_staff_organisation|profile2|staff|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_right_col_search|profile2|ding_staff_profile|default';
  $field_group->group_name = 'group_right_col_search';
  $field_group->entity_type = 'profile2';
  $field_group->bundle = 'ding_staff_profile';
  $field_group->mode = 'default';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Right column',
    'weight' => '1',
    'children' => array(
      0 => 'field_ding_staff_description',
      1 => 'field_ding_staff_position',
      2 => 'group_contactinfo',
    ),
    'format_type' => 'div',
    'format_settings' => array(
      'label' => 'Right column',
      'instance_settings' => array(
        'classes' => 'search-right group-right-col-search field-group-div',
        'description' => '',
        'show_label' => '0',
        'label_element' => 'h3',
        'effect' => 'none',
        'speed' => 'fast',
        'id' => 'profile2_ding_staff_profile_full_group_right_col_search',
      ),
      'formatter' => 'open',
    ),
  );
  $field_groups['group_right_col_search|profile2|ding_staff_profile|default'] = $field_group;

  // Translatables
  // Included for use with string extractors like potx.
  t('Contact');
  t('Name');
  t('Organisation');
  t('Right column');
  t('contact info');

  return $field_groups;
}
