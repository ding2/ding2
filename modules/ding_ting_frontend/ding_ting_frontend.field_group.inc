<?php
/**
 * @file
 * ding_ting_frontend.field_group.inc
 */

/**
 * Implements hook_field_group_info().
 */
function ding_ting_frontend_field_group_info() {
  $field_groups = array();

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_holdings_available|ting_object|ting_object|default';
  $field_group->group_name = 'group_holdings_available';
  $field_group->entity_type = 'ting_object';
  $field_group->bundle = 'ting_object';
  $field_group->mode = 'default';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Holdings available on the shelf',
    'weight' => '3',
    'children' => array(
      0 => 'ding_availability_holdings',
    ),
    'format_type' => 'div',
    'format_settings' => array(
      'label' => 'Holdings available on the shelf',
      'instance_settings' => array(
        'classes' => ' group-holdings-available field-group-div',
        'description' => '',
        'show_label' => '0',
        'label_element' => 'h2',
        'effect' => 'none',
        'speed' => 'fast',
        'id' => 'ting_object_ting_object_full_group_holdings_available',
      ),
      'formatter' => 'collapsed',
    ),
  );
  $field_groups['group_holdings_available|ting_object|ting_object|default'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_on_this_site|ting_object|ting_object|default';
  $field_group->group_name = 'group_on_this_site';
  $field_group->entity_type = 'ting_object';
  $field_group->bundle = 'ting_object';
  $field_group->mode = 'default';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'On this site',
    'weight' => '4',
    'children' => array(
      0 => 'ting_reference_reverse',
    ),
    'format_type' => 'div',
    'format_settings' => array(
      'label' => 'On this site',
      'instance_settings' => array(
        'classes' => ' group-on-this-site field-group-div',
        'description' => '',
        'show_label' => '1',
        'label_element' => 'h2',
        'effect' => 'none',
        'speed' => 'fast',
        'id' => 'ting_object_ting_object_full_group_on_this_site',
      ),
      'formatter' => 'collapsed',
    ),
  );
  $field_groups['group_on_this_site|ting_object|ting_object|default'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_overlay|ting_object|ting_object|compact';
  $field_group->group_name = 'group_overlay';
  $field_group->entity_type = 'ting_object';
  $field_group->bundle = 'ting_object';
  $field_group->mode = 'compact';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Group overlay',
    'weight' => '1',
    'children' => array(
      0 => 'ting_author',
      1 => 'ting_title',
    ),
    'format_type' => 'div',
    'format_settings' => array(
      'label' => 'Group overlay',
      'instance_settings' => array(
        'classes' => ' group-overlay field-group-div',
        'description' => '',
        'show_label' => '0',
        'label_element' => 'h3',
        'effect' => 'none',
        'speed' => 'fast',
        'id' => 'ting_object_ting_object_compact_group_overlay',
      ),
      'formatter' => 'open',
    ),
  );
  $field_groups['group_overlay|ting_object|ting_object|compact'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_periodical_issues|ting_object|ting_object|default';
  $field_group->group_name = 'group_periodical_issues';
  $field_group->entity_type = 'ting_object';
  $field_group->bundle = 'ting_object';
  $field_group->mode = 'default';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Issues',
    'weight' => '5',
    'children' => array(
      0 => 'ding_periodical_issues',
    ),
    'format_type' => 'div',
    'format_settings' => array(
      'label' => 'Issues',
      'instance_settings' => array(
        'classes' => ' group-periodical-issues field-group-div',
        'description' => '',
        'show_label' => '1',
        'label_element' => 'h2',
        'effect' => 'none',
        'speed' => 'fast',
        'id' => 'ting_object_ting_object_full_group_periodical_issues',
      ),
      'formatter' => 'collapsed',
    ),
  );
  $field_groups['group_periodical_issues|ting_object|ting_object|default'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_ting_left_col_collection|ting_object|ting_object|collection_list';
  $field_group->group_name = 'group_ting_left_col_collection';
  $field_group->entity_type = 'ting_object';
  $field_group->bundle = 'ting_object';
  $field_group->mode = 'collection_list';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Left column',
    'weight' => '0',
    'children' => array(
      0 => 'ting_cover',
    ),
    'format_type' => 'div',
    'format_settings' => array(
      'label' => 'Left column',
      'instance_settings' => array(
        'classes' => 'ting-object-left group-ting-left-col-collection field-group-div',
        'description' => '',
        'show_label' => '0',
        'label_element' => 'h3',
        'effect' => 'none',
        'speed' => 'none',
        'id' => 'ting_object_ting_object_collection_list_group_ting_left_col_collection',
      ),
      'formatter' => 'open',
    ),
  );
  $field_groups['group_ting_left_col_collection|ting_object|ting_object|collection_list'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_ting_left_col_primary|ting_object|ting_object|collection_primary';
  $field_group->group_name = 'group_ting_left_col_primary';
  $field_group->entity_type = 'ting_object';
  $field_group->bundle = 'ting_object';
  $field_group->mode = 'collection_primary';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Left column',
    'weight' => '0',
    'children' => array(
      0 => 'ting_cover',
    ),
    'format_type' => 'div',
    'format_settings' => array(
      'label' => 'Left column',
      'instance_settings' => array(
        'classes' => 'ting-object-left group-ting-left-col-primary field-group-div',
        'description' => '',
        'show_label' => '0',
        'label_element' => 'h3',
        'effect' => 'none',
        'speed' => 'none',
        'id' => 'ting_object_ting_object_collection_primary_group_ting_left_col_primary',
      ),
      'formatter' => 'open',
    ),
  );
  $field_groups['group_ting_left_col_primary|ting_object|ting_object|collection_primary'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_ting_left_col_search|ting_object|ting_object|search_result';
  $field_group->group_name = 'group_ting_left_col_search';
  $field_group->entity_type = 'ting_object';
  $field_group->bundle = 'ting_object';
  $field_group->mode = 'search_result';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Left column',
    'weight' => '0',
    'children' => array(
      0 => 'ting_cover',
    ),
    'format_type' => 'div',
    'format_settings' => array(
      'label' => 'Left column',
      'instance_settings' => array(
        'classes' => 'ting-object-left group-ting-left-col-search field-group-div',
        'description' => '',
        'show_label' => '0',
        'label_element' => 'h3',
        'effect' => 'none',
        'speed' => 'none',
        'id' => 'ting_object_ting_object_search_result_group_ting_left_col_search',
      ),
      'formatter' => 'open',
    ),
  );
  $field_groups['group_ting_left_col_search|ting_object|ting_object|search_result'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_ting_object_left_column|ting_object|ting_object|default';
  $field_group->group_name = 'group_ting_object_left_column';
  $field_group->entity_type = 'ting_object';
  $field_group->bundle = 'ting_object';
  $field_group->mode = 'default';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Left column',
    'weight' => '0',
    'children' => array(
      0 => 'ting_cover',
    ),
    'format_type' => 'div',
    'format_settings' => array(
      'label' => 'Left column',
      'instance_settings' => array(
        'classes' => 'ting-object-left group-ting-object-left-column field-group-div',
        'description' => '',
        'show_label' => '0',
        'label_element' => 'h3',
        'effect' => 'none',
        'speed' => 'none',
        'id' => 'ting_object_ting_object_full_group_ting_object_left_column',
      ),
      'formatter' => 'open',
    ),
  );
  $field_groups['group_ting_object_left_column|ting_object|ting_object|default'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_ting_object_right_column|ting_object|ting_object|default';
  $field_group->group_name = 'group_ting_object_right_column';
  $field_group->entity_type = 'ting_object';
  $field_group->bundle = 'ting_object';
  $field_group->mode = 'default';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Right column',
    'weight' => '1',
    'children' => array(
      0 => 'ting_title',
      1 => 'ting_type',
      2 => 'ting_series',
      3 => 'ting_abstract',
      4 => 'ting_author',
      5 => 'ting_subjects',
      6 => 'ding_entity_buttons',
      7 => 'ding_serendipity_info',
      8 => 'ding_entity_rating_action',
      9 => 'ding_entity_rating_result',
    ),
    'format_type' => 'div',
    'format_settings' => array(
      'label' => 'Right column',
      'instance_settings' => array(
        'classes' => 'ting-object-right group-ting-object-right-column field-group-div',
        'description' => '',
        'show_label' => '0',
        'label_element' => 'h3',
        'effect' => 'none',
        'speed' => 'none',
        'id' => 'ting_object_ting_object_full_group_ting_object_right_column',
      ),
      'formatter' => 'open',
    ),
  );
  $field_groups['group_ting_object_right_column|ting_object|ting_object|default'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_ting_object_teaser_left|ting_object|ting_object|teaser';
  $field_group->group_name = 'group_ting_object_teaser_left';
  $field_group->entity_type = 'ting_object';
  $field_group->bundle = 'ting_object';
  $field_group->mode = 'teaser';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Left column',
    'weight' => '0',
    'children' => array(
      0 => 'ting_cover',
    ),
    'format_type' => 'div',
    'format_settings' => array(
      'label' => 'Left column',
      'instance_settings' => array(
        'classes' => 'ting-object-left group-ting-object-teaser-left field-group-div',
        'description' => '',
        'show_label' => '0',
        'label_element' => 'h3',
        'effect' => 'none',
        'speed' => 'none',
        'id' => 'ting_object_ting_object_teaser_group_ting_object_teaser_left',
      ),
      'formatter' => 'open',
    ),
  );
  $field_groups['group_ting_object_teaser_left|ting_object|ting_object|teaser'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_ting_object_teaser_right|ting_object|ting_object|teaser';
  $field_group->group_name = 'group_ting_object_teaser_right';
  $field_group->entity_type = 'ting_object';
  $field_group->bundle = 'ting_object';
  $field_group->mode = 'teaser';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Right column',
    'weight' => '1',
    'children' => array(
      0 => 'ting_title',
      1 => 'ting_series',
      2 => 'ting_abstract',
      3 => 'ting_author',
      4 => 'ting_subjects',
      5 => 'ding_serendipity_info',
      6 => 'ding_entity_rating_action',
      7 => 'ding_entity_rating_result',
    ),
    'format_type' => 'div',
    'format_settings' => array(
      'label' => 'Right column',
      'instance_settings' => array(
        'classes' => 'ting-object-right group-ting-object-teaser-right field-group-div',
        'description' => '',
        'show_label' => '0',
        'label_element' => 'h3',
        'effect' => 'none',
        'speed' => 'none',
        'id' => 'ting_object_ting_object_teaser_group_ting_object_teaser_right',
      ),
      'formatter' => 'open',
    ),
  );
  $field_groups['group_ting_object_teaser_right|ting_object|ting_object|teaser'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_ting_right_col_collection|ting_object|ting_object|collection_list';
  $field_group->group_name = 'group_ting_right_col_collection';
  $field_group->entity_type = 'ting_object';
  $field_group->bundle = 'ting_object';
  $field_group->mode = 'collection_list';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Right column',
    'weight' => '1',
    'children' => array(
      0 => 'ting_title',
      1 => 'ting_type',
      2 => 'ting_series',
      3 => 'ting_abstract',
      4 => 'ting_author',
      5 => 'ting_subjects',
      6 => 'ding_entity_buttons',
    ),
    'format_type' => 'div',
    'format_settings' => array(
      'label' => 'Right column',
      'instance_settings' => array(
        'classes' => 'ting-object-right group-ting-right-col-collection field-group-div',
        'description' => '',
        'show_label' => '0',
        'label_element' => 'h3',
        'effect' => 'none',
        'speed' => 'none',
        'id' => 'ting_object_ting_object_collection_list_group_ting_right_col_collection',
      ),
      'formatter' => 'open',
    ),
  );
  $field_groups['group_ting_right_col_collection|ting_object|ting_object|collection_list'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_ting_right_col_primary|ting_object|ting_object|collection_primary';
  $field_group->group_name = 'group_ting_right_col_primary';
  $field_group->entity_type = 'ting_object';
  $field_group->bundle = 'ting_object';
  $field_group->mode = 'collection_primary';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Right column',
    'weight' => '1',
    'children' => array(
      0 => 'ting_title',
      1 => 'ting_type',
      2 => 'ting_series',
      3 => 'ting_abstract',
      4 => 'ting_author',
      5 => 'ting_subjects',
    ),
    'format_type' => 'div',
    'format_settings' => array(
      'label' => 'Right column',
      'instance_settings' => array(
        'classes' => 'ting-object-right group-ting-right-col-primary field-group-div',
        'description' => '',
        'show_label' => '0',
        'label_element' => 'h3',
        'effect' => 'none',
        'speed' => 'none',
        'id' => 'ting_object_ting_object_collection_primary_group_ting_right_col_primary',
      ),
      'formatter' => 'open',
    ),
  );
  $field_groups['group_ting_right_col_primary|ting_object|ting_object|collection_primary'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_ting_right_col_search|ting_object|ting_object|search_result';
  $field_group->group_name = 'group_ting_right_col_search';
  $field_group->entity_type = 'ting_object';
  $field_group->bundle = 'ting_object';
  $field_group->mode = 'search_result';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Right column',
    'weight' => '1',
    'children' => array(
      0 => 'ting_title',
      1 => 'ting_series',
      2 => 'ting_abstract',
      3 => 'ting_author',
      4 => 'ding_entity_rating_action',
      5 => 'ding_entity_rating_result',
    ),
    'format_type' => 'div',
    'format_settings' => array(
      'label' => 'Right column',
      'instance_settings' => array(
        'classes' => 'ting-object-right group-ting-right-col-search field-group-div',
        'description' => '',
        'show_label' => '0',
        'label_element' => 'h3',
        'effect' => 'none',
        'speed' => 'none',
        'id' => 'ting_object_ting_object_search_result_group_ting_right_col_search',
      ),
      'formatter' => 'open',
    ),
  );
  $field_groups['group_ting_right_col_search|ting_object|ting_object|search_result'] = $field_group;

  // Translatables
  // Included for use with string extractors like potx.
  t('Group overlay');
  t('Holdings available on the shelf');
  t('Issues');
  t('Left column');
  t('On this site');
  t('Right column');

  return $field_groups;
}
