<?php
/**
 * @file
 * ding_news.field_group.inc
 */

/**
 * Implements hook_field_group_info().
 */
function ding_news_field_group_info() {
  $export = array();

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_ding_news_attachments|node|ding_news|form';
  $field_group->group_name = 'group_ding_news_attachments';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'ding_news';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Attachments',
    'weight' => '5',
    'children' => array(
      0 => 'field_ding_news_files',
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
  $export['group_ding_news_attachments|node|ding_news|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_ding_news_categorization|node|ding_news|form';
  $field_group->group_name = 'group_ding_news_categorization';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'ding_news';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Categorization',
    'weight' => '3',
    'children' => array(
      0 => 'field_ding_news_category',
      1 => 'field_ding_news_tags',
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
  $export['group_ding_news_categorization|node|ding_news|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_ding_news_content|node|ding_news|form';
  $field_group->group_name = 'group_ding_news_content';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'ding_news';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Content',
    'weight' => '2',
    'children' => array(
      0 => 'field_ding_news_body',
      1 => 'field_ding_news_lead',
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
  $export['group_ding_news_content|node|ding_news|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_ding_news_data_well|node|ding_news|form';
  $field_group->group_name = 'group_ding_news_data_well';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'ding_news';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Data well',
    'weight' => '4',
    'children' => array(
      0 => 'field_ding_news_materials',
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
  $export['group_ding_news_data_well|node|ding_news|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_ding_news_images|node|ding_news|form';
  $field_group->group_name = 'group_ding_news_images';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'ding_news';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Images',
    'weight' => '1',
    'children' => array(
      0 => 'field_ding_news_list_image',
      1 => 'field_ding_news_title_image',
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
  $export['group_ding_news_images|node|ding_news|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_ding_news_relations|node|ding_news|form';
  $field_group->group_name = 'group_ding_news_relations';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'ding_news';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Relations',
    'weight' => '6',
    'children' => array(
      0 => 'ding_news_groups_ref',
      1 => 'og_group_ref',
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
  $export['group_ding_news_relations|node|ding_news|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_left_col_search|node|ding_news|search_result';
  $field_group->group_name = 'group_left_col_search';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'ding_news';
  $field_group->mode = 'search_result';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Left column',
    'weight' => '0',
    'children' => array(
      0 => 'field_ding_news_list_image',
    ),
    'format_type' => 'div',
    'format_settings' => array(
      'label' => 'Left column',
      'instance_settings' => array(
        'classes' => 'search-left',
        'description' => '',
        'show_label' => '0',
        'label_element' => 'h3',
        'effect' => 'none',
        'speed' => 'none',
      ),
      'formatter' => 'open',
    ),
  );
  $export['group_left_col_search|node|ding_news|search_result'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_left|node|ding_news|alternative_layout_full';
  $field_group->group_name = 'group_left';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'ding_news';
  $field_group->mode = 'alternative_layout_full';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Left',
    'weight' => '13',
    'children' => array(
      0 => 'field_ding_news_files',
      1 => 'field_ding_news_tags',
      2 => 'field_ding_news_title_image',
    ),
    'format_type' => 'div',
    'format_settings' => array(
      'label' => 'Left',
      'instance_settings' => array(
        'classes' => '',
        'description' => '',
        'show_label' => '0',
        'label_element' => 'h3',
        'effect' => 'none',
        'speed' => 'fast',
      ),
      'formatter' => 'open',
    ),
  );
  $export['group_left|node|ding_news|alternative_layout_full'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_left|node|ding_news|default';
  $field_group->group_name = 'group_left';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'ding_news';
  $field_group->mode = 'default';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Left',
    'weight' => '0',
    'children' => array(
      0 => 'field_ding_news_title_image',
    ),
    'format_type' => 'div',
    'format_settings' => array(
      'label' => 'Left',
      'instance_settings' => array(
        'classes' => '',
        'description' => '',
        'show_label' => '0',
        'label_element' => 'h3',
        'effect' => 'none',
        'speed' => 'none',
      ),
      'formatter' => 'open',
    ),
  );
  $export['group_left|node|ding_news|default'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_right_col_search|node|ding_news|search_result';
  $field_group->group_name = 'group_right_col_search';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'ding_news';
  $field_group->mode = 'search_result';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Right column',
    'weight' => '1',
    'children' => array(
      0 => 'field_ding_news_category',
      1 => 'field_ding_news_lead',
      2 => 'field_ding_news_tags',
    ),
    'format_type' => 'div',
    'format_settings' => array(
      'label' => 'Right column',
      'instance_settings' => array(
        'classes' => 'search-right',
        'description' => '',
        'show_label' => '0',
        'label_element' => 'h3',
        'effect' => 'none',
        'speed' => 'none',
      ),
      'formatter' => 'open',
    ),
  );
  $export['group_right_col_search|node|ding_news|search_result'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_right|node|ding_news|alternative_layout_full';
  $field_group->group_name = 'group_right';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'ding_news';
  $field_group->mode = 'alternative_layout_full';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Right',
    'weight' => '16',
    'children' => array(
      0 => 'field_ding_news_body',
      1 => 'field_ding_news_category',
      2 => 'field_ding_news_lead',
      3 => 'field_ding_news_materials',
      4 => 'og_group_ref',
    ),
    'format_type' => 'div',
    'format_settings' => array(
      'label' => 'Right',
      'instance_settings' => array(
        'classes' => '',
        'description' => '',
        'show_label' => '0',
        'label_element' => 'h3',
        'effect' => 'none',
        'speed' => 'fast',
      ),
      'formatter' => 'open',
    ),
  );
  $export['group_right|node|ding_news|alternative_layout_full'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_right|node|ding_news|default';
  $field_group->group_name = 'group_right';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'ding_news';
  $field_group->mode = 'default';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Right',
    'weight' => '1',
    'children' => array(
      0 => 'field_ding_news_body',
      1 => 'field_ding_news_category',
      2 => 'field_ding_news_files',
      3 => 'field_ding_news_lead',
      4 => 'field_ding_news_tags',
      5 => 'og_group_ref',
      6 => 'webform',
    ),
    'format_type' => 'div',
    'format_settings' => array(
      'label' => 'Right',
      'instance_settings' => array(
        'classes' => '',
        'description' => '',
        'show_label' => '0',
        'label_element' => 'h3',
        'effect' => 'none',
        'speed' => 'none',
      ),
      'formatter' => 'open',
    ),
  );
  $export['group_right|node|ding_news|default'] = $field_group;

  return $export;
}
