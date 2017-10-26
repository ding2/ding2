<?php
/**
 * @file
 * ding_paragraphs.field_group.inc
 */

/**
 * Implements hook_field_group_info().
 */
function ding_paragraphs_field_group_info() {
  $field_groups = array();

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_ding_news_paragraphs|node|ding_news|form';
  $field_group->group_name = 'group_ding_news_paragraphs';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'ding_news';
  $field_group->mode = 'form';
  $field_group->parent_name = 'group_ding_news_content';
  $field_group->data = array(
    'label' => 'Paragraphs',
    'weight' => '7',
    'children' => array(
      0 => 'field_ding_news_paragraphs',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'label' => 'Paragraphs',
      'instance_settings' => array(
        'required_fields' => 0,
        'id' => '',
        'classes' => '',
        'description' => '',
      ),
      'formatter' => 'collapsed',
    ),
  );
  $field_groups['group_ding_news_paragraphs|node|ding_news|form'] = $field_group;

  // Translatables
  // Included for use with string extractors like potx.
  t('Paragraphs');

  return $field_groups;
}
