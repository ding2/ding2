<?php
/**
 * @file
 * ding_event.views_default.inc
 */

/**
 * Implementation of hook_views_default_views().
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
  $handler->display->display_options['fields']['ding_event_body']['id'] = 'ding_event_body';
  $handler->display->display_options['fields']['ding_event_body']['table'] = 'field_data_ding_event_body';
  $handler->display->display_options['fields']['ding_event_body']['field'] = 'ding_event_body';
  $handler->display->display_options['fields']['ding_event_body']['label'] = '';
  $handler->display->display_options['fields']['ding_event_body']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['ding_event_body']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['ding_event_body']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['ding_event_body']['alter']['external'] = 0;
  $handler->display->display_options['fields']['ding_event_body']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['ding_event_body']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['ding_event_body']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['ding_event_body']['alter']['max_length'] = '300';
  $handler->display->display_options['fields']['ding_event_body']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['ding_event_body']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['ding_event_body']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['ding_event_body']['alter']['trim'] = 1;
  $handler->display->display_options['fields']['ding_event_body']['alter']['html'] = 0;
  $handler->display->display_options['fields']['ding_event_body']['element_type'] = 'p';
  $handler->display->display_options['fields']['ding_event_body']['element_class'] = 'teaser';
  $handler->display->display_options['fields']['ding_event_body']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['ding_event_body']['element_wrapper_type'] = '0';
  $handler->display->display_options['fields']['ding_event_body']['element_default_classes'] = 0;
  $handler->display->display_options['fields']['ding_event_body']['hide_empty'] = 0;
  $handler->display->display_options['fields']['ding_event_body']['empty_zero'] = 0;
  $handler->display->display_options['fields']['ding_event_body']['hide_alter_empty'] = 0;
  $handler->display->display_options['fields']['ding_event_body']['field_api_classes'] = 0;
  /* Field: Content: Date and time */
  $handler->display->display_options['fields']['ding_event_date']['id'] = 'ding_event_date';
  $handler->display->display_options['fields']['ding_event_date']['table'] = 'field_data_ding_event_date';
  $handler->display->display_options['fields']['ding_event_date']['field'] = 'ding_event_date';
  /* Sort criterion: Content: Date and time (ding_event_date) */
  $handler->display->display_options['sorts']['ding_event_date_value']['id'] = 'ding_event_date_value';
  $handler->display->display_options['sorts']['ding_event_date_value']['table'] = 'field_data_ding_event_date';
  $handler->display->display_options['sorts']['ding_event_date_value']['field'] = 'ding_event_date_value';
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
    'ding_event' => 'ding_event',
  );

  /* Display: Teaser list */
  $handler = $view->new_display('ctools_context', 'Teaser list', 'ctools_context_teaser_list');
  $handler->display->display_options['defaults']['pager'] = FALSE;
  $handler->display->display_options['pager']['type'] = 'some';
  $handler->display->display_options['pager']['options']['items_per_page'] = '6';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['style_plugin'] = 'ctools_context';
  $handler->display->display_options['row_plugin'] = 'fields';
  $handler->display->display_options['row_options']['hide_empty'] = 0;
  $handler->display->display_options['row_options']['default_field_elements'] = 0;
  $handler->display->display_options['defaults']['fields'] = FALSE;
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
  $handler->display->display_options['fields']['ding_event_body']['id'] = 'ding_event_body';
  $handler->display->display_options['fields']['ding_event_body']['table'] = 'field_data_ding_event_body';
  $handler->display->display_options['fields']['ding_event_body']['field'] = 'ding_event_body';
  $handler->display->display_options['fields']['ding_event_body']['label'] = '';
  $handler->display->display_options['fields']['ding_event_body']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['ding_event_body']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['ding_event_body']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['ding_event_body']['alter']['external'] = 0;
  $handler->display->display_options['fields']['ding_event_body']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['ding_event_body']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['ding_event_body']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['ding_event_body']['alter']['max_length'] = '300';
  $handler->display->display_options['fields']['ding_event_body']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['ding_event_body']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['ding_event_body']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['ding_event_body']['alter']['trim'] = 1;
  $handler->display->display_options['fields']['ding_event_body']['alter']['html'] = 0;
  $handler->display->display_options['fields']['ding_event_body']['element_type'] = 'p';
  $handler->display->display_options['fields']['ding_event_body']['element_class'] = 'teaser';
  $handler->display->display_options['fields']['ding_event_body']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['ding_event_body']['element_wrapper_type'] = '0';
  $handler->display->display_options['fields']['ding_event_body']['element_default_classes'] = 0;
  $handler->display->display_options['fields']['ding_event_body']['hide_empty'] = 0;
  $handler->display->display_options['fields']['ding_event_body']['empty_zero'] = 0;
  $handler->display->display_options['fields']['ding_event_body']['hide_alter_empty'] = 0;
  $handler->display->display_options['fields']['ding_event_body']['field_api_classes'] = 0;
  /* Field: Content: Date and time */
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
    'format_type' => 'short',
    'fromto' => 'both',
    'multiple_number' => '',
    'multiple_from' => '',
    'multiple_to' => '',
    'show_repeat_rule' => 'show',
  );
  $handler->display->display_options['fields']['ding_event_date']['field_api_classes'] = 0;
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
    'ding_event' => 'ding_event',
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
  $handler->display->display_options['path'] = 'event/feed';
  $handler->display->display_options['displays'] = array(
    'default' => 'default',
    'ctools_context_teaser_list' => 'ctools_context_teaser_list',
  );
  $handler->display->display_options['sitename_title'] = 1;
  $translatables['ding_event'] = array(
    t('Master'),
    t('more'),
    t('Apply'),
    t('Reset'),
    t('Sort by'),
    t('Asc'),
    t('Desc'),
    t('Date and time'),
    t('Teaser list'),
    t('Feed'),
  );
  $export['ding_event'] = $view;

  return $export;
}
