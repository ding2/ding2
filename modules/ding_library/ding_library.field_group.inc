<?php
/**
 * @file
 * ding_library.field_group.inc
 */

/**
 * Implements hook_field_group_info().
 */
function ding_library_field_group_info() {
  $field_groups = array();

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
    'label' => 'Links',
    'weight' => '5',
    'children' => array(
      0 => 'field_ding_library_geocode',
      1 => 'field_ding_library_links',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'label' => 'Links',
      'instance_settings' => array(
        'required_fields' => 1,
        'classes' => ' group-ding-library-attachments field-group-fieldset',
        'description' => '',
      ),
      'formatter' => 'collapsed',
    ),
  );
  $field_groups['group_ding_library_attachments|node|ding_library|form'] = $field_group;

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
    'weight' => '4',
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
        'classes' => ' group-ding-library-contact field-group-fieldset',
        'description' => '',
      ),
      'formatter' => 'collapsed',
    ),
  );
  $field_groups['group_ding_library_contact|node|ding_library|form'] = $field_group;

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
    'weight' => '3',
    'children' => array(
      0 => 'field_ding_library_body',
      1 => 'field_ding_library_lead',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'label' => 'Content',
      'instance_settings' => array(
        'required_fields' => 1,
        'classes' => ' group-ding-library-content field-group-fieldset',
        'description' => '',
      ),
      'formatter' => 'collapsed',
    ),
  );
  $field_groups['group_ding_library_content|node|ding_library|form'] = $field_group;

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
    'weight' => '2',
    'children' => array(
      0 => 'field_ding_library_list_image',
      1 => 'field_ding_library_title_image',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'label' => 'Images',
      'instance_settings' => array(
        'required_fields' => 1,
        'classes' => ' group-ding-library-images field-group-fieldset',
        'description' => '',
      ),
      'formatter' => 'collapsed',
    ),
  );
  $field_groups['group_ding_library_images|node|ding_library|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_ding_library_left_column|node|ding_library|teaser';
  $field_group->group_name = 'group_ding_library_left_column';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'ding_library';
  $field_group->mode = 'teaser';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Left column',
    'weight' => '0',
    'children' => array(
      0 => 'field_ding_library_list_image',
    ),
    'format_type' => 'div',
    'format_settings' => array(
      'label' => 'Left column',
      'instance_settings' => array(
        'classes' => 'ding-library-left group-ding-library-left-column field-group-div',
        'description' => '',
        'show_label' => '0',
        'label_element' => 'h3',
        'effect' => 'none',
        'speed' => 'none',
        'id' => 'node_ding_library_teaser_group_ding_library_left_column',
      ),
      'formatter' => 'open',
    ),
  );
  $field_groups['group_ding_library_left_column|node|ding_library|teaser'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_ding_library_right_column|node|ding_library|teaser';
  $field_group->group_name = 'group_ding_library_right_column';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'ding_library';
  $field_group->mode = 'teaser';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Right column',
    'weight' => '1',
    'children' => array(
      0 => 'field_ding_library_addresse',
      1 => 'field_ding_library_fax_number',
      2 => 'field_ding_library_links',
      3 => 'field_ding_library_mail',
      4 => 'field_ding_library_phone_number',
    ),
    'format_type' => 'div',
    'format_settings' => array(
      'label' => 'Right column',
      'instance_settings' => array(
        'classes' => 'ding-library-right group-ding-library-right-column field-group-div',
        'description' => '',
        'show_label' => '0',
        'label_element' => 'h3',
        'effect' => 'none',
        'speed' => 'none',
        'id' => 'node_ding_library_teaser_group_ding_library_right_column',
      ),
      'formatter' => 'open',
    ),
  );
  $field_groups['group_ding_library_right_column|node|ding_library|teaser'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_left_col_search|node|ding_library|search_result';
  $field_group->group_name = 'group_left_col_search';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'ding_library';
  $field_group->mode = 'search_result';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Left column',
    'weight' => '0',
    'children' => array(
      0 => 'field_ding_library_list_image',
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
        'speed' => 'none',
        'id' => 'node_ding_library_search_result_group_left_col_search',
      ),
      'formatter' => 'open',
    ),
  );
  $field_groups['group_left_col_search|node|ding_library|search_result'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_right_col_search|node|ding_library|search_result';
  $field_group->group_name = 'group_right_col_search';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'ding_library';
  $field_group->mode = 'search_result';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Right column',
    'weight' => '1',
    'children' => array(
      0 => 'field_ding_library_addresse',
      1 => 'field_ding_library_mail',
      2 => 'field_ding_library_phone_number',
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
        'speed' => 'none',
        'id' => 'node_ding_library_search_result_group_right_col_search',
      ),
      'formatter' => 'open',
    ),
  );
  $field_groups['group_right_col_search|node|ding_library|search_result'] = $field_group;

  // Translatables
  // Included for use with string extractors like potx.
  t('Contact');
  t('Content');
  t('Images');
  t('Left column');
  t('Links');
  t('Right column');

  return $field_groups;
}
