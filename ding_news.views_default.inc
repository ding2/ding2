<?php
/**
 * @file
 * ding_news.views_default.inc
 */

/**
 * Implementation of hook_views_default_views().
 */
function ding_news_views_default_views() {
  $export = array();

  $view = new view;
  $view->name = 'ding_news';
  $view->description = '';
  $view->tag = 'ding_news';
  $view->base_table = 'node';
  $view->human_name = 'Ding news';
  $view->core = 7;
  $view->api_version = '3.0-alpha1';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['use_more'] = TRUE;
  $handler->display->display_options['use_more_text'] = 'Read more';
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['query']['options']['query_comment'] = FALSE;
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'some';
  $handler->display->display_options['pager']['options']['items_per_page'] = '10';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['style_plugin'] = 'default';
  $handler->display->display_options['row_plugin'] = 'fields';
  /* Field: Content: Title */
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
  /* Field: Content: Body */
  $handler->display->display_options['fields']['ding_news_body']['id'] = 'ding_news_body';
  $handler->display->display_options['fields']['ding_news_body']['table'] = 'field_data_ding_news_body';
  $handler->display->display_options['fields']['ding_news_body']['field'] = 'ding_news_body';
  $handler->display->display_options['fields']['ding_news_body']['label'] = '';
  $handler->display->display_options['fields']['ding_news_body']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['ding_news_body']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['ding_news_body']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['ding_news_body']['alter']['external'] = 0;
  $handler->display->display_options['fields']['ding_news_body']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['ding_news_body']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['ding_news_body']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['ding_news_body']['alter']['max_length'] = '300';
  $handler->display->display_options['fields']['ding_news_body']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['ding_news_body']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['ding_news_body']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['ding_news_body']['alter']['trim'] = 1;
  $handler->display->display_options['fields']['ding_news_body']['alter']['html'] = 0;
  $handler->display->display_options['fields']['ding_news_body']['element_type'] = 'p';
  $handler->display->display_options['fields']['ding_news_body']['element_class'] = 'teaser';
  $handler->display->display_options['fields']['ding_news_body']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['ding_news_body']['element_wrapper_type'] = '0';
  $handler->display->display_options['fields']['ding_news_body']['element_default_classes'] = 0;
  $handler->display->display_options['fields']['ding_news_body']['hide_empty'] = 0;
  $handler->display->display_options['fields']['ding_news_body']['empty_zero'] = 0;
  $handler->display->display_options['fields']['ding_news_body']['hide_alter_empty'] = 0;
  $handler->display->display_options['fields']['ding_news_body']['field_api_classes'] = 0;
  /* Sort criterion: Content: Post date */
  $handler->display->display_options['sorts']['created']['id'] = 'created';
  $handler->display->display_options['sorts']['created']['table'] = 'node';
  $handler->display->display_options['sorts']['created']['field'] = 'created';
  $handler->display->display_options['sorts']['created']['order'] = 'DESC';
  /* Contextual filter: Content: Category (ding_news_category) */
  $handler->display->display_options['arguments']['ding_news_category_tid']['id'] = 'ding_news_category_tid';
  $handler->display->display_options['arguments']['ding_news_category_tid']['table'] = 'field_data_ding_news_category';
  $handler->display->display_options['arguments']['ding_news_category_tid']['field'] = 'ding_news_category_tid';
  $handler->display->display_options['arguments']['ding_news_category_tid']['default_argument_type'] = 'fixed';
  $handler->display->display_options['arguments']['ding_news_category_tid']['default_argument_skip_url'] = 0;
  $handler->display->display_options['arguments']['ding_news_category_tid']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['ding_news_category_tid']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['ding_news_category_tid']['summary_options']['items_per_page'] = '25';
  $handler->display->display_options['arguments']['ding_news_category_tid']['break_phrase'] = 0;
  $handler->display->display_options['arguments']['ding_news_category_tid']['not'] = 0;
  /* Filter criterion: Content: Published */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'node';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = 1;
  $handler->display->display_options['filters']['status']['group'] = 0;
  $handler->display->display_options['filters']['status']['expose']['operator'] = FALSE;
  /* Filter criterion: Content: Type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'node';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'ding_news' => 'ding_news',
  );

  /* Display: Master */
  $handler = $view->new_display('ctools_context', 'Master', 'ctools_context_master');
  $handler->display->display_options['defaults']['pager'] = FALSE;
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = '10';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['pager']['options']['id'] = '0';
  $handler->display->display_options['pager']['options']['expose']['items_per_page_options_all'] = 0;
  $handler->display->display_options['style_plugin'] = 'ctools_context';
  $handler->display->display_options['row_plugin'] = 'fields';

  /* Display: Front page teaser list */
  $handler = $view->new_display('ctools_context', 'Front page teaser list', 'ctools_context_teaser_list');
  $handler->display->display_options['defaults']['pager'] = FALSE;
  $handler->display->display_options['pager']['type'] = 'some';
  $handler->display->display_options['pager']['options']['items_per_page'] = '4';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['style_plugin'] = 'ctools_context';
  $handler->display->display_options['row_plugin'] = 'fields';
  $handler->display->display_options['row_options']['hide_empty'] = 0;
  $handler->display->display_options['row_options']['default_field_elements'] = 0;
  $handler->display->display_options['defaults']['arguments'] = FALSE;
  $handler->display->display_options['defaults']['filters'] = FALSE;
  /* Filter criterion: Content: Published */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'node';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = 1;
  $handler->display->display_options['filters']['status']['group'] = 0;
  $handler->display->display_options['filters']['status']['expose']['operator'] = FALSE;
  /* Filter criterion: Content: Type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'node';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'ding_news' => 'ding_news',
  );
  /* Filter criterion: Content: Promoted to front page */
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
  $handler->display->display_options['path'] = 'news/feed';
  $handler->display->display_options['displays'] = array(
    'default' => 'default',
    'ctools_context_teaser_list' => 'ctools_context_teaser_list',
    'ctools_context_1' => 0,
  );
  $handler->display->display_options['sitename_title'] = 1;

  /* Display: Library teaser list */
  $handler = $view->new_display('ctools_context', 'Library teaser list', 'ctools_context_library_list');
  $handler->display->display_options['defaults']['pager'] = FALSE;
  $handler->display->display_options['pager']['type'] = 'some';
  $handler->display->display_options['pager']['options']['items_per_page'] = '4';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['style_plugin'] = 'ctools_context';
  $handler->display->display_options['row_plugin'] = 'fields';
  $handler->display->display_options['row_options']['hide_empty'] = 0;
  $handler->display->display_options['row_options']['default_field_elements'] = 0;
  $handler->display->display_options['defaults']['arguments'] = FALSE;
  /* Contextual filter: Content: Library (ding_news_library:gid) */
  $handler->display->display_options['arguments']['ding_news_library_gid']['id'] = 'ding_news_library_gid';
  $handler->display->display_options['arguments']['ding_news_library_gid']['table'] = 'field_data_ding_news_library';
  $handler->display->display_options['arguments']['ding_news_library_gid']['field'] = 'ding_news_library_gid';
  $handler->display->display_options['arguments']['ding_news_library_gid']['default_argument_type'] = 'fixed';
  $handler->display->display_options['arguments']['ding_news_library_gid']['default_argument_skip_url'] = 0;
  $handler->display->display_options['arguments']['ding_news_library_gid']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['ding_news_library_gid']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['ding_news_library_gid']['summary_options']['items_per_page'] = '25';
  $handler->display->display_options['arguments']['ding_news_library_gid']['break_phrase'] = 0;
  $handler->display->display_options['arguments']['ding_news_library_gid']['not'] = 0;
  $handler->display->display_options['defaults']['filters'] = FALSE;
  /* Filter criterion: Content: Published */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'node';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = 1;
  $handler->display->display_options['filters']['status']['group'] = 0;
  $handler->display->display_options['filters']['status']['expose']['operator'] = FALSE;
  /* Filter criterion: Content: Type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'node';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'ding_news' => 'ding_news',
  );
  $translatables['ding_news'] = array(
    t('Master'),
    t('Read more'),
    t('Apply'),
    t('Reset'),
    t('Sort by'),
    t('Asc'),
    t('Desc'),
    t('All'),
    t('more'),
    t('Items per page'),
    t('- All -'),
    t('Offset'),
    t('Front page teaser list'),
    t('Feed'),
    t('Library teaser list'),
  );
  $export['ding_news'] = $view;

  return $export;
}
