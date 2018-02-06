<?php
/**
 * @file
 * ting_field_search.views_default.inc
 */

/**
 * Implements hook_views_default_views().
 */
function ting_field_search_views_default_views() {
  $export = array();

  $view = new view();
  $view->name = 'ting_field_search_search_guide';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'node';
  $view->human_name = 'Search guide';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['style_plugin'] = 'default';
  $handler->display->display_options['row_plugin'] = 'fields';
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = '';
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['title']['alter']['ellipsis'] = FALSE;
  /* Sort criterion: Content: Weight (field_search_guide_weight) */
  $handler->display->display_options['sorts']['field_search_guide_weight_value']['id'] = 'field_search_guide_weight_value';
  $handler->display->display_options['sorts']['field_search_guide_weight_value']['table'] = 'field_data_field_search_guide_weight';
  $handler->display->display_options['sorts']['field_search_guide_weight_value']['field'] = 'field_search_guide_weight_value';
  /* Filter criterion: Content: Published */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'node';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = 1;
  $handler->display->display_options['filters']['status']['group'] = 1;
  $handler->display->display_options['filters']['status']['expose']['operator'] = FALSE;
  /* Filter criterion: Content: Type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'node';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'ting_field_search_search_guide' => 'ting_field_search_search_guide',
  );

  /* Display: Profile search guides */
  $handler = $view->new_display('panel_pane', 'Profile search guides', 'panel_pane_1');
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = '';
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['title']['alter']['ellipsis'] = FALSE;
  $handler->display->display_options['fields']['title']['element_type'] = 'h1';
  $handler->display->display_options['fields']['title']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['title']['link_to_node'] = FALSE;
  /* Field: Content: Body */
  $handler->display->display_options['fields']['body']['id'] = 'body';
  $handler->display->display_options['fields']['body']['table'] = 'field_data_body';
  $handler->display->display_options['fields']['body']['field'] = 'body';
  $handler->display->display_options['fields']['body']['label'] = '';
  $handler->display->display_options['fields']['body']['element_label_colon'] = FALSE;
  /* Field: Content: Files */
  $handler->display->display_options['fields']['field_search_guide_files']['id'] = 'field_search_guide_files';
  $handler->display->display_options['fields']['field_search_guide_files']['table'] = 'field_data_field_search_guide_files';
  $handler->display->display_options['fields']['field_search_guide_files']['field'] = 'field_search_guide_files';
  $handler->display->display_options['fields']['field_search_guide_files']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_search_guide_files']['hide_empty'] = TRUE;
  $handler->display->display_options['fields']['field_search_guide_files']['click_sort_column'] = 'fid';
  $handler->display->display_options['fields']['field_search_guide_files']['type'] = 'file_rendered';
  $handler->display->display_options['fields']['field_search_guide_files']['settings'] = array(
    'file_view_mode' => 'default',
  );
  $handler->display->display_options['fields']['field_search_guide_files']['delta_offset'] = '0';
  $handler->display->display_options['fields']['field_search_guide_files']['multi_type'] = 'ul';
  /* Field: Content: Links */
  $handler->display->display_options['fields']['field_search_guide_links']['id'] = 'field_search_guide_links';
  $handler->display->display_options['fields']['field_search_guide_links']['table'] = 'field_data_field_search_guide_links';
  $handler->display->display_options['fields']['field_search_guide_links']['field'] = 'field_search_guide_links';
  $handler->display->display_options['fields']['field_search_guide_links']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_search_guide_links']['hide_empty'] = TRUE;
  $handler->display->display_options['fields']['field_search_guide_links']['click_sort_column'] = 'url';
  $handler->display->display_options['fields']['field_search_guide_links']['delta_offset'] = '0';
  $handler->display->display_options['fields']['field_search_guide_links']['multi_type'] = 'ul';
  $handler->display->display_options['defaults']['sorts'] = FALSE;
  /* Sort criterion: Content: Weight (field_search_guide_weight) */
  $handler->display->display_options['sorts']['field_search_guide_weight_value']['id'] = 'field_search_guide_weight_value';
  $handler->display->display_options['sorts']['field_search_guide_weight_value']['table'] = 'field_data_field_search_guide_weight';
  $handler->display->display_options['sorts']['field_search_guide_weight_value']['field'] = 'field_search_guide_weight_value';
  $handler->display->display_options['defaults']['arguments'] = FALSE;
  /* Contextual filter: Content: Position (field_search_guide_position) */
  $handler->display->display_options['arguments']['field_search_guide_position_value']['id'] = 'field_search_guide_position_value';
  $handler->display->display_options['arguments']['field_search_guide_position_value']['table'] = 'field_data_field_search_guide_position';
  $handler->display->display_options['arguments']['field_search_guide_position_value']['field'] = 'field_search_guide_position_value';
  $handler->display->display_options['arguments']['field_search_guide_position_value']['default_argument_type'] = 'fixed';
  $handler->display->display_options['arguments']['field_search_guide_position_value']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['field_search_guide_position_value']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['field_search_guide_position_value']['summary_options']['items_per_page'] = '25';
  $handler->display->display_options['arguments']['field_search_guide_position_value']['limit'] = '0';
  $handler->display->display_options['defaults']['filter_groups'] = FALSE;
  $handler->display->display_options['defaults']['filters'] = FALSE;
  /* Filter criterion: Content: Published */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'node';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = 1;
  $handler->display->display_options['filters']['status']['group'] = 1;
  $handler->display->display_options['filters']['status']['expose']['operator'] = FALSE;
  /* Filter criterion: Content: Type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'node';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'ting_field_search_search_guide' => 'ting_field_search_search_guide',
  );
  $handler->display->display_options['argument_input'] = array(
    'field_search_guide_position_value' => array(
      'type' => 'user',
      'context' => 'entity:comment.author',
      'context_optional' => 0,
      'panel' => '0',
      'fixed' => '',
      'label' => 'Content: Position (field_search_guide_position)',
    ),
  );
  $translatables['ting_field_search_search_guide'] = array(
    t('Master'),
    t('more'),
    t('Apply'),
    t('Reset'),
    t('Sort by'),
    t('Asc'),
    t('Desc'),
    t('Items per page'),
    t('- All -'),
    t('Offset'),
    t('« first'),
    t('‹ previous'),
    t('next ›'),
    t('last »'),
    t('Profile search guides'),
    t('Files'),
    t('Links'),
    t('All'),
    t('View panes'),
  );
  $export['ting_field_search_search_guide'] = $view;

  return $export;
}
