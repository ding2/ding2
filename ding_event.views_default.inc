<?php
/**
 * @file
 * ding_event.views_default.inc
 */

/**
 * Implements hook_views_default_views().
 */
function ding_event_views_default_views() {
  $export = array();

  $view = new view;
  $view->name = 'ding_event';
  $view->description = '';
  $view->tag = 'ding_event';
  $view->base_table = 'node';
  $view->human_name = 'Ding event';
  $view->core = 7;
  $view->api_version = '3.0-alpha1';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['query']['options']['query_comment'] = FALSE;
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['exposed_form']['options']['reset_button_label'] = 'Gendan';
  $handler->display->display_options['pager']['type'] = 'some';
  $handler->display->display_options['pager']['options']['items_per_page'] = '10';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['style_plugin'] = 'default';
  $handler->display->display_options['row_plugin'] = 'fields';
  /* Overskrift: Global: Text area */
  $handler->display->display_options['header']['area']['id'] = 'area';
  $handler->display->display_options['header']['area']['table'] = 'views';
  $handler->display->display_options['header']['area']['field'] = 'area';
  $handler->display->display_options['header']['area']['empty'] = FALSE;
  /* Felt: Indhold: Image */
  $handler->display->display_options['fields']['ding_event_image']['id'] = 'ding_event_image';
  $handler->display->display_options['fields']['ding_event_image']['table'] = 'field_data_ding_event_image';
  $handler->display->display_options['fields']['ding_event_image']['field'] = 'ding_event_image';
  $handler->display->display_options['fields']['ding_event_image']['label'] = '';
  $handler->display->display_options['fields']['ding_event_image']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['ding_event_image']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['ding_event_image']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['ding_event_image']['alter']['external'] = 0;
  $handler->display->display_options['fields']['ding_event_image']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['ding_event_image']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['ding_event_image']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['ding_event_image']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['ding_event_image']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['ding_event_image']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['ding_event_image']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['ding_event_image']['alter']['html'] = 0;
  $handler->display->display_options['fields']['ding_event_image']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['ding_event_image']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['ding_event_image']['hide_empty'] = 0;
  $handler->display->display_options['fields']['ding_event_image']['empty_zero'] = 0;
  $handler->display->display_options['fields']['ding_event_image']['hide_alter_empty'] = 0;
  $handler->display->display_options['fields']['ding_event_image']['click_sort_column'] = 'fid';
  $handler->display->display_options['fields']['ding_event_image']['settings'] = array(
    'image_style' => 'ding_large',
    'image_link' => 'content',
  );
  $handler->display->display_options['fields']['ding_event_image']['field_api_classes'] = 0;
  /* Felt: Indhold: Library */
  $handler->display->display_options['fields']['ding_event_library']['id'] = 'ding_event_library';
  $handler->display->display_options['fields']['ding_event_library']['table'] = 'field_data_ding_event_library';
  $handler->display->display_options['fields']['ding_event_library']['field'] = 'ding_event_library';
  $handler->display->display_options['fields']['ding_event_library']['label'] = '';
  $handler->display->display_options['fields']['ding_event_library']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['ding_event_library']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['ding_event_library']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['ding_event_library']['alter']['external'] = 0;
  $handler->display->display_options['fields']['ding_event_library']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['ding_event_library']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['ding_event_library']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['ding_event_library']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['ding_event_library']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['ding_event_library']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['ding_event_library']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['ding_event_library']['alter']['html'] = 0;
  $handler->display->display_options['fields']['ding_event_library']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['ding_event_library']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['ding_event_library']['hide_empty'] = 0;
  $handler->display->display_options['fields']['ding_event_library']['empty_zero'] = 0;
  $handler->display->display_options['fields']['ding_event_library']['hide_alter_empty'] = 0;
  $handler->display->display_options['fields']['ding_event_library']['click_sort_column'] = 'gid';
  $handler->display->display_options['fields']['ding_event_library']['field_api_classes'] = 0;
  /* Felt: Indhold: Date and time */
  $handler->display->display_options['fields']['ding_event_date']['id'] = 'ding_event_date';
  $handler->display->display_options['fields']['ding_event_date']['table'] = 'field_data_ding_event_date';
  $handler->display->display_options['fields']['ding_event_date']['field'] = 'ding_event_date';
  $handler->display->display_options['fields']['ding_event_date']['label'] = '';
  $handler->display->display_options['fields']['ding_event_date']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['ding_event_date']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['ding_event_date']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['ding_event_date']['alter']['external'] = 0;
  $handler->display->display_options['fields']['ding_event_date']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['ding_event_date']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['ding_event_date']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['ding_event_date']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['ding_event_date']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['ding_event_date']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['ding_event_date']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['ding_event_date']['alter']['html'] = 0;
  $handler->display->display_options['fields']['ding_event_date']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['ding_event_date']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['ding_event_date']['hide_empty'] = 0;
  $handler->display->display_options['fields']['ding_event_date']['empty_zero'] = 0;
  $handler->display->display_options['fields']['ding_event_date']['hide_alter_empty'] = 0;
  $handler->display->display_options['fields']['ding_event_date']['settings'] = array(
    'format_type' => 'long_date_only',
    'fromto' => 'both',
    'multiple_number' => '',
    'multiple_from' => '',
    'multiple_to' => '',
    'show_repeat_rule' => 'show',
  );
  $handler->display->display_options['fields']['ding_event_date']['field_api_classes'] = 0;
  /* Felt: Indhold: Titel */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = '';
  $handler->display->display_options['fields']['title']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['title']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['title']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['title']['alter']['external'] = 0;
  $handler->display->display_options['fields']['title']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['title']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['title']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = 0;
  $handler->display->display_options['fields']['title']['alter']['ellipsis'] = 0;
  $handler->display->display_options['fields']['title']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['title']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['title']['alter']['html'] = 0;
  $handler->display->display_options['fields']['title']['element_type'] = 'h3';
  $handler->display->display_options['fields']['title']['element_class'] = 'title';
  $handler->display->display_options['fields']['title']['element_label_type'] = '0';
  $handler->display->display_options['fields']['title']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['title']['element_wrapper_type'] = '0';
  $handler->display->display_options['fields']['title']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['title']['hide_empty'] = 0;
  $handler->display->display_options['fields']['title']['empty_zero'] = 0;
  $handler->display->display_options['fields']['title']['hide_alter_empty'] = 0;
  $handler->display->display_options['fields']['title']['link_to_node'] = 1;
  /* Sort criterion: Indhold: Date and time (ding_event_date) */
  $handler->display->display_options['sorts']['ding_event_date_value']['id'] = 'ding_event_date_value';
  $handler->display->display_options['sorts']['ding_event_date_value']['table'] = 'field_data_ding_event_date';
  $handler->display->display_options['sorts']['ding_event_date_value']['field'] = 'ding_event_date_value';
  /* Contextual filter: Indhold: Library (ding_event_library:gid) */
  $handler->display->display_options['arguments']['ding_event_library_gid']['id'] = 'ding_event_library_gid';
  $handler->display->display_options['arguments']['ding_event_library_gid']['table'] = 'field_data_ding_event_library';
  $handler->display->display_options['arguments']['ding_event_library_gid']['field'] = 'ding_event_library_gid';
  $handler->display->display_options['arguments']['ding_event_library_gid']['default_argument_type'] = 'fixed';
  $handler->display->display_options['arguments']['ding_event_library_gid']['summary']['format'] = 'default_summary';
  /* Filter criterion: Indhold: Udgivet */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'node';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = 1;
  $handler->display->display_options['filters']['status']['group'] = 0;
  $handler->display->display_options['filters']['status']['expose']['operator'] = FALSE;
  /* Filter criterion: Indhold: Type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'node';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'ding_event' => 'ding_event',
  );

  /* Display: Full list */
  $handler = $view->new_display('ctools_context', 'Full list', 'ctools_context_master');
  $handler->display->display_options['style_plugin'] = 'ctools_context';
  $handler->display->display_options['row_plugin'] = 'fields';
  $handler->display->display_options['defaults']['arguments'] = FALSE;
  /* Contextual filter: Indhold: Category (ding_event_category) */
  $handler->display->display_options['arguments']['ding_event_category_tid']['id'] = 'ding_event_category_tid';
  $handler->display->display_options['arguments']['ding_event_category_tid']['table'] = 'field_data_ding_event_category';
  $handler->display->display_options['arguments']['ding_event_category_tid']['field'] = 'ding_event_category_tid';
  $handler->display->display_options['arguments']['ding_event_category_tid']['default_argument_type'] = 'fixed';
  $handler->display->display_options['arguments']['ding_event_category_tid']['default_argument_skip_url'] = 0;
  $handler->display->display_options['arguments']['ding_event_category_tid']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['ding_event_category_tid']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['ding_event_category_tid']['summary_options']['items_per_page'] = '25';
  $handler->display->display_options['arguments']['ding_event_category_tid']['break_phrase'] = 0;
  $handler->display->display_options['arguments']['ding_event_category_tid']['not'] = 0;

  /* Display: Front page teaser list */
  $handler = $view->new_display('ctools_context', 'Front page teaser list', 'ctools_context_teaser_list');
  $handler->display->display_options['defaults']['pager'] = FALSE;
  $handler->display->display_options['pager']['type'] = 'some';
  $handler->display->display_options['pager']['options']['items_per_page'] = '6';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['style_plugin'] = 'ctools_context';
  $handler->display->display_options['row_plugin'] = 'fields';
  $handler->display->display_options['row_options']['hide_empty'] = 0;
  $handler->display->display_options['row_options']['default_field_elements'] = 0;
  $handler->display->display_options['defaults']['header'] = FALSE;
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Felt: Indhold: Date and time */
  $handler->display->display_options['fields']['ding_event_date']['id'] = 'ding_event_date';
  $handler->display->display_options['fields']['ding_event_date']['table'] = 'field_data_ding_event_date';
  $handler->display->display_options['fields']['ding_event_date']['field'] = 'ding_event_date';
  $handler->display->display_options['fields']['ding_event_date']['label'] = '';
  $handler->display->display_options['fields']['ding_event_date']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['ding_event_date']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['ding_event_date']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['ding_event_date']['alter']['external'] = 0;
  $handler->display->display_options['fields']['ding_event_date']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['ding_event_date']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['ding_event_date']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['ding_event_date']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['ding_event_date']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['ding_event_date']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['ding_event_date']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['ding_event_date']['alter']['html'] = 0;
  $handler->display->display_options['fields']['ding_event_date']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['ding_event_date']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['ding_event_date']['hide_empty'] = 0;
  $handler->display->display_options['fields']['ding_event_date']['empty_zero'] = 0;
  $handler->display->display_options['fields']['ding_event_date']['hide_alter_empty'] = 0;
  $handler->display->display_options['fields']['ding_event_date']['type'] = 'calendar_page';
  $handler->display->display_options['fields']['ding_event_date']['settings'] = array(
    'format_type' => 'short',
    'fromto' => 'both',
    'multiple_number' => '',
    'multiple_from' => '',
    'multiple_to' => '',
    'show_repeat_rule' => 'show',
  );
  $handler->display->display_options['fields']['ding_event_date']['field_api_classes'] = 0;
  /* Felt: Indhold: Library */
  $handler->display->display_options['fields']['ding_event_library']['id'] = 'ding_event_library';
  $handler->display->display_options['fields']['ding_event_library']['table'] = 'field_data_ding_event_library';
  $handler->display->display_options['fields']['ding_event_library']['field'] = 'ding_event_library';
  $handler->display->display_options['fields']['ding_event_library']['label'] = '';
  $handler->display->display_options['fields']['ding_event_library']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['ding_event_library']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['ding_event_library']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['ding_event_library']['alter']['external'] = 0;
  $handler->display->display_options['fields']['ding_event_library']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['ding_event_library']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['ding_event_library']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['ding_event_library']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['ding_event_library']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['ding_event_library']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['ding_event_library']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['ding_event_library']['alter']['html'] = 0;
  $handler->display->display_options['fields']['ding_event_library']['element_type'] = 'div';
  $handler->display->display_options['fields']['ding_event_library']['element_class'] = 'ding-event-library';
  $handler->display->display_options['fields']['ding_event_library']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['ding_event_library']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['ding_event_library']['hide_empty'] = 0;
  $handler->display->display_options['fields']['ding_event_library']['empty_zero'] = 0;
  $handler->display->display_options['fields']['ding_event_library']['hide_alter_empty'] = 0;
  $handler->display->display_options['fields']['ding_event_library']['click_sort_column'] = 'gid';
  $handler->display->display_options['fields']['ding_event_library']['field_api_classes'] = 0;
  /* Felt: Indhold: Titel */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = '';
  $handler->display->display_options['fields']['title']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['title']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['title']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['title']['alter']['external'] = 0;
  $handler->display->display_options['fields']['title']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['title']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['title']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = 0;
  $handler->display->display_options['fields']['title']['alter']['ellipsis'] = 0;
  $handler->display->display_options['fields']['title']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['title']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['title']['alter']['html'] = 0;
  $handler->display->display_options['fields']['title']['element_type'] = 'h3';
  $handler->display->display_options['fields']['title']['element_class'] = 'title';
  $handler->display->display_options['fields']['title']['element_label_type'] = '0';
  $handler->display->display_options['fields']['title']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['title']['element_wrapper_type'] = '0';
  $handler->display->display_options['fields']['title']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['title']['hide_empty'] = 0;
  $handler->display->display_options['fields']['title']['empty_zero'] = 0;
  $handler->display->display_options['fields']['title']['hide_alter_empty'] = 0;
  $handler->display->display_options['fields']['title']['link_to_node'] = 1;
  /* Felt: Indhold: Date and time */
  $handler->display->display_options['fields']['ding_event_date_1']['id'] = 'ding_event_date_1';
  $handler->display->display_options['fields']['ding_event_date_1']['table'] = 'field_data_ding_event_date';
  $handler->display->display_options['fields']['ding_event_date_1']['field'] = 'ding_event_date';
  $handler->display->display_options['fields']['ding_event_date_1']['label'] = '';
  $handler->display->display_options['fields']['ding_event_date_1']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['ding_event_date_1']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['ding_event_date_1']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['ding_event_date_1']['alter']['external'] = 0;
  $handler->display->display_options['fields']['ding_event_date_1']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['ding_event_date_1']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['ding_event_date_1']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['ding_event_date_1']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['ding_event_date_1']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['ding_event_date_1']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['ding_event_date_1']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['ding_event_date_1']['alter']['html'] = 0;
  $handler->display->display_options['fields']['ding_event_date_1']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['ding_event_date_1']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['ding_event_date_1']['hide_empty'] = 0;
  $handler->display->display_options['fields']['ding_event_date_1']['empty_zero'] = 0;
  $handler->display->display_options['fields']['ding_event_date_1']['hide_alter_empty'] = 0;
  $handler->display->display_options['fields']['ding_event_date_1']['settings'] = array(
    'format_type' => 'time_only',
    'fromto' => 'both',
    'multiple_number' => '',
    'multiple_from' => '',
    'multiple_to' => '',
    'show_repeat_rule' => 'show',
  );
  $handler->display->display_options['fields']['ding_event_date_1']['field_api_classes'] = 0;
  $handler->display->display_options['defaults']['filters'] = FALSE;
  /* Filter criterion: Indhold: Udgivet */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'node';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = 1;
  $handler->display->display_options['filters']['status']['group'] = 0;
  $handler->display->display_options['filters']['status']['expose']['operator'] = FALSE;
  /* Filter criterion: Indhold: Type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'node';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'ding_event' => 'ding_event',
  );
  /* Filter criterion: Indhold: Forfremmet til forside */
  $handler->display->display_options['filters']['promote']['id'] = 'promote';
  $handler->display->display_options['filters']['promote']['table'] = 'node';
  $handler->display->display_options['filters']['promote']['field'] = 'promote';
  $handler->display->display_options['filters']['promote']['value'] = '1';

  /* Display: Feed */
  $handler = $view->new_display('feed', 'Feed', 'feed_1');
  $handler->display->display_options['pager']['type'] = 'some';
  $handler->display->display_options['pager']['options']['items_per_page'] = '20';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['style_plugin'] = 'rss';
  $handler->display->display_options['row_plugin'] = 'node_rss';
  $handler->display->display_options['path'] = 'event/feed';
  $handler->display->display_options['displays'] = array(
    'ctools_context_master' => 'ctools_context_master',
    'ctools_context_teaser_list' => 'ctools_context_teaser_list',
    'default' => 0,
  );
  $handler->display->display_options['sitename_title'] = 1;

  /* Display: Library teaser list */
  $handler = $view->new_display('ctools_context', 'Library teaser list', 'ctools_context_library_teaser');
  $handler->display->display_options['defaults']['pager'] = FALSE;
  $handler->display->display_options['pager']['type'] = 'some';
  $handler->display->display_options['pager']['options']['items_per_page'] = '6';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['style_plugin'] = 'ctools_context';
  $handler->display->display_options['row_plugin'] = 'fields';
  $handler->display->display_options['row_options']['hide_empty'] = 0;
  $handler->display->display_options['row_options']['default_field_elements'] = 0;
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Felt: Indhold: Date and time */
  $handler->display->display_options['fields']['ding_event_date']['id'] = 'ding_event_date';
  $handler->display->display_options['fields']['ding_event_date']['table'] = 'field_data_ding_event_date';
  $handler->display->display_options['fields']['ding_event_date']['field'] = 'ding_event_date';
  $handler->display->display_options['fields']['ding_event_date']['label'] = '';
  $handler->display->display_options['fields']['ding_event_date']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['ding_event_date']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['ding_event_date']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['ding_event_date']['alter']['external'] = 0;
  $handler->display->display_options['fields']['ding_event_date']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['ding_event_date']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['ding_event_date']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['ding_event_date']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['ding_event_date']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['ding_event_date']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['ding_event_date']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['ding_event_date']['alter']['html'] = 0;
  $handler->display->display_options['fields']['ding_event_date']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['ding_event_date']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['ding_event_date']['hide_empty'] = 0;
  $handler->display->display_options['fields']['ding_event_date']['empty_zero'] = 0;
  $handler->display->display_options['fields']['ding_event_date']['hide_alter_empty'] = 0;
  $handler->display->display_options['fields']['ding_event_date']['settings'] = array(
    'format_type' => 'date_only',
    'fromto' => 'both',
    'multiple_number' => '',
    'multiple_from' => '',
    'multiple_to' => '',
    'show_repeat_rule' => 'show',
  );
  $handler->display->display_options['fields']['ding_event_date']['field_api_classes'] = 0;
  /* Felt: Indhold: Titel */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = '';
  $handler->display->display_options['fields']['title']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['title']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['title']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['title']['alter']['external'] = 0;
  $handler->display->display_options['fields']['title']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['title']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['title']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = 0;
  $handler->display->display_options['fields']['title']['alter']['ellipsis'] = 0;
  $handler->display->display_options['fields']['title']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['title']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['title']['alter']['html'] = 0;
  $handler->display->display_options['fields']['title']['element_type'] = 'h3';
  $handler->display->display_options['fields']['title']['element_class'] = 'title';
  $handler->display->display_options['fields']['title']['element_label_type'] = '0';
  $handler->display->display_options['fields']['title']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['title']['element_wrapper_type'] = '0';
  $handler->display->display_options['fields']['title']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['title']['hide_empty'] = 0;
  $handler->display->display_options['fields']['title']['empty_zero'] = 0;
  $handler->display->display_options['fields']['title']['hide_alter_empty'] = 0;
  $handler->display->display_options['fields']['title']['link_to_node'] = 1;
  /* Felt: Indhold: Body */
  $handler->display->display_options['fields']['field_ding_body']['id'] = 'field_ding_body';
  $handler->display->display_options['fields']['field_ding_body']['table'] = 'field_data_field_ding_body';
  $handler->display->display_options['fields']['field_ding_body']['field'] = 'field_ding_body';
  $handler->display->display_options['fields']['field_ding_body']['label'] = '';
  $handler->display->display_options['fields']['field_ding_body']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['field_ding_body']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['field_ding_body']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['field_ding_body']['alter']['external'] = 0;
  $handler->display->display_options['fields']['field_ding_body']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['field_ding_body']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['field_ding_body']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['field_ding_body']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['field_ding_body']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['field_ding_body']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['field_ding_body']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['field_ding_body']['alter']['html'] = 0;
  $handler->display->display_options['fields']['field_ding_body']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_ding_body']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['field_ding_body']['hide_empty'] = 0;
  $handler->display->display_options['fields']['field_ding_body']['empty_zero'] = 0;
  $handler->display->display_options['fields']['field_ding_body']['hide_alter_empty'] = 0;
  $handler->display->display_options['fields']['field_ding_body']['type'] = 'text_summary_or_trimmed';
  $handler->display->display_options['fields']['field_ding_body']['settings'] = array(
    'trim_length' => '600',
  );
  $handler->display->display_options['fields']['field_ding_body']['field_api_classes'] = 0;
  /* Felt: Indhold: Date and time */
  $handler->display->display_options['fields']['ding_event_date_1']['id'] = 'ding_event_date_1';
  $handler->display->display_options['fields']['ding_event_date_1']['table'] = 'field_data_ding_event_date';
  $handler->display->display_options['fields']['ding_event_date_1']['field'] = 'ding_event_date';
  $handler->display->display_options['fields']['ding_event_date_1']['label'] = '';
  $handler->display->display_options['fields']['ding_event_date_1']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['ding_event_date_1']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['ding_event_date_1']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['ding_event_date_1']['alter']['external'] = 0;
  $handler->display->display_options['fields']['ding_event_date_1']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['ding_event_date_1']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['ding_event_date_1']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['ding_event_date_1']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['ding_event_date_1']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['ding_event_date_1']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['ding_event_date_1']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['ding_event_date_1']['alter']['html'] = 0;
  $handler->display->display_options['fields']['ding_event_date_1']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['ding_event_date_1']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['ding_event_date_1']['hide_empty'] = 0;
  $handler->display->display_options['fields']['ding_event_date_1']['empty_zero'] = 0;
  $handler->display->display_options['fields']['ding_event_date_1']['hide_alter_empty'] = 0;
  $handler->display->display_options['fields']['ding_event_date_1']['settings'] = array(
    'format_type' => 'time_only',
    'fromto' => 'both',
    'multiple_number' => '',
    'multiple_from' => '',
    'multiple_to' => '',
    'show_repeat_rule' => 'show',
  );
  $handler->display->display_options['fields']['ding_event_date_1']['field_api_classes'] = 0;
  $handler->display->display_options['defaults']['arguments'] = FALSE;
  /* Contextual filter: Indhold: Library (ding_event_library:gid) */
  $handler->display->display_options['arguments']['ding_event_library_gid']['id'] = 'ding_event_library_gid';
  $handler->display->display_options['arguments']['ding_event_library_gid']['table'] = 'field_data_ding_event_library';
  $handler->display->display_options['arguments']['ding_event_library_gid']['field'] = 'ding_event_library_gid';
  $handler->display->display_options['arguments']['ding_event_library_gid']['default_argument_type'] = 'fixed';
  $handler->display->display_options['arguments']['ding_event_library_gid']['default_argument_skip_url'] = 0;
  $handler->display->display_options['arguments']['ding_event_library_gid']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['ding_event_library_gid']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['ding_event_library_gid']['summary_options']['items_per_page'] = '25';
  $handler->display->display_options['arguments']['ding_event_library_gid']['break_phrase'] = 0;
  $handler->display->display_options['arguments']['ding_event_library_gid']['not'] = 0;
  $handler->display->display_options['defaults']['filters'] = FALSE;
  /* Filter criterion: Indhold: Udgivet */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'node';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = 1;
  $handler->display->display_options['filters']['status']['group'] = 0;
  $handler->display->display_options['filters']['status']['expose']['operator'] = FALSE;
  /* Filter criterion: Indhold: Type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'node';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'ding_event' => 'ding_event',
  );

  /* Display: Library full list */
  $handler = $view->new_display('ctools_context', 'Library full list', 'ctools_context_library_master');
  $handler->display->display_options['style_plugin'] = 'ctools_context';
  $handler->display->display_options['row_plugin'] = 'fields';
  $handler->display->display_options['defaults']['arguments'] = FALSE;
  /* Contextual filter: Indhold: Library (ding_event_library:gid) */
  $handler->display->display_options['arguments']['ding_event_library_gid']['id'] = 'ding_event_library_gid';
  $handler->display->display_options['arguments']['ding_event_library_gid']['table'] = 'field_data_ding_event_library';
  $handler->display->display_options['arguments']['ding_event_library_gid']['field'] = 'ding_event_library_gid';
  $handler->display->display_options['arguments']['ding_event_library_gid']['default_argument_type'] = 'fixed';
  $handler->display->display_options['arguments']['ding_event_library_gid']['default_argument_skip_url'] = 0;
  $handler->display->display_options['arguments']['ding_event_library_gid']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['ding_event_library_gid']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['ding_event_library_gid']['summary_options']['items_per_page'] = '25';
  $handler->display->display_options['arguments']['ding_event_library_gid']['break_phrase'] = 0;
  $handler->display->display_options['arguments']['ding_event_library_gid']['not'] = 0;
  /* Contextual filter: Indhold: Category (ding_event_category) */
  $handler->display->display_options['arguments']['ding_event_category_tid']['id'] = 'ding_event_category_tid';
  $handler->display->display_options['arguments']['ding_event_category_tid']['table'] = 'field_data_ding_event_category';
  $handler->display->display_options['arguments']['ding_event_category_tid']['field'] = 'ding_event_category_tid';
  $handler->display->display_options['arguments']['ding_event_category_tid']['default_argument_type'] = 'fixed';
  $handler->display->display_options['arguments']['ding_event_category_tid']['default_argument_skip_url'] = 0;
  $handler->display->display_options['arguments']['ding_event_category_tid']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['ding_event_category_tid']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['ding_event_category_tid']['summary_options']['items_per_page'] = '25';
  $handler->display->display_options['arguments']['ding_event_category_tid']['break_phrase'] = 0;
  $handler->display->display_options['arguments']['ding_event_category_tid']['not'] = 0;

  /* Display: Library Feed */
  $handler = $view->new_display('feed', 'Library Feed', 'feed_library');
  $handler->display->display_options['pager']['type'] = 'some';
  $handler->display->display_options['pager']['options']['items_per_page'] = '20';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['style_plugin'] = 'rss';
  $handler->display->display_options['row_plugin'] = 'node_rss';
  $handler->display->display_options['defaults']['arguments'] = FALSE;
  /* Contextual filter: Indhold: Library (ding_event_library:nid) */
  $handler->display->display_options['arguments']['ding_library_nid']['id'] = 'ding_library_nid';
  $handler->display->display_options['arguments']['ding_library_nid']['table'] = 'field_data_ding_event_library';
  $handler->display->display_options['arguments']['ding_library_nid']['field'] = 'ding_library_nid';
  $handler->display->display_options['arguments']['ding_library_nid']['default_action'] = 'not found';
  $handler->display->display_options['arguments']['ding_library_nid']['default_argument_type'] = 'fixed';
  $handler->display->display_options['arguments']['ding_library_nid']['default_argument_skip_url'] = 0;
  $handler->display->display_options['arguments']['ding_library_nid']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['ding_library_nid']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['ding_library_nid']['summary_options']['items_per_page'] = '25';
  $handler->display->display_options['arguments']['ding_library_nid']['break_phrase'] = 0;
  $handler->display->display_options['arguments']['ding_library_nid']['not'] = 0;
  $handler->display->display_options['path'] = 'node/%/events/feed';
  $handler->display->display_options['displays'] = array(
    'ctools_context_library_teaser' => 'ctools_context_library_teaser',
    'ctools_context_library_master' => 'ctools_context_library_master',
    'default' => 0,
    'ctools_context_master' => 0,
    'ctools_context_teaser_list' => 0,
  );
  $handler->display->display_options['sitename_title'] = 1;
  $translatables['ding_event'] = array(
    t('Master'),
    t('more'),
    t('Apply'),
    t('Gendan'),
    t('Sort by'),
    t('Asc'),
    t('Desc'),
    t('Alle'),
    t('Full list'),
    t('Front page teaser list'),
    t('Feed'),
    t('Library teaser list'),
    t('Library full list'),
    t('Library Feed'),
  );
  $export['ding_event'] = $view;

  return $export;
}
