<?php
/**
 * @file
 * ding_christmas_calendar.views_default.inc
 */

/**
 * Implements hook_views_default_views().
 */
function ding_christmas_calendar_views_default_views() {
  $export = array();

  $view = new view();
  $view->name = 'export_xmas_calendar_results';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'node';
  $view->human_name = 'Export XMAS calendar results';
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
  /* Sort criterion: Content: Post date */
  $handler->display->display_options['sorts']['created']['id'] = 'created';
  $handler->display->display_options['sorts']['created']['table'] = 'node';
  $handler->display->display_options['sorts']['created']['field'] = 'created';
  $handler->display->display_options['sorts']['created']['order'] = 'DESC';
  /* Filter criterion: Content: Published */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'node';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = 1;
  $handler->display->display_options['filters']['status']['group'] = 1;
  $handler->display->display_options['filters']['status']['expose']['operator'] = FALSE;

  /* Display: Data export */
  $handler = $view->new_display('views_data_export', 'Data export', 'views_data_export_1');
  $handler->display->display_options['pager']['type'] = 'none';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['style_plugin'] = 'views_data_export_csv';
  $handler->display->display_options['style_options']['provide_file'] = 0;
  $handler->display->display_options['style_options']['parent_sort'] = 0;
  $handler->display->display_options['style_options']['quote'] = 1;
  $handler->display->display_options['style_options']['trim'] = 1;
  $handler->display->display_options['style_options']['replace_newlines'] = 0;
  $handler->display->display_options['style_options']['newline_token'] = '1';
  $handler->display->display_options['style_options']['header'] = 1;
  $handler->display->display_options['style_options']['keep_html'] = 0;
  $handler->display->display_options['defaults']['relationships'] = FALSE;
  /* Relationship: Quiz result: Uid */
  $handler->display->display_options['relationships']['uid']['id'] = 'uid';
  $handler->display->display_options['relationships']['uid']['table'] = 'quiz_node_results';
  $handler->display->display_options['relationships']['uid']['field'] = 'uid';
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['title']['alter']['ellipsis'] = FALSE;
  /* Field: User: Name */
  $handler->display->display_options['fields']['name']['id'] = 'name';
  $handler->display->display_options['fields']['name']['table'] = 'users';
  $handler->display->display_options['fields']['name']['field'] = 'name';
  $handler->display->display_options['fields']['name']['relationship'] = 'uid';
  $handler->display->display_options['fields']['name']['label'] = 'User name';
  /* Field: Quiz result: Nid */
  $handler->display->display_options['fields']['nid']['id'] = 'nid';
  $handler->display->display_options['fields']['nid']['table'] = 'quiz_node_results';
  $handler->display->display_options['fields']['nid']['field'] = 'nid';
  /* Field: Quiz result: Score */
  $handler->display->display_options['fields']['score']['id'] = 'score';
  $handler->display->display_options['fields']['score']['table'] = 'quiz_node_results';
  $handler->display->display_options['fields']['score']['field'] = 'score';
  /* Field: Quiz result: Evaluated */
  $handler->display->display_options['fields']['is_evaluated']['id'] = 'is_evaluated';
  $handler->display->display_options['fields']['is_evaluated']['table'] = 'quiz_node_results';
  $handler->display->display_options['fields']['is_evaluated']['field'] = 'is_evaluated';
  $handler->display->display_options['fields']['is_evaluated']['not'] = 0;
  /* Field: Quiz result: Date started */
  $handler->display->display_options['fields']['time_start']['id'] = 'time_start';
  $handler->display->display_options['fields']['time_start']['table'] = 'quiz_node_results';
  $handler->display->display_options['fields']['time_start']['field'] = 'time_start';
  $handler->display->display_options['fields']['time_start']['date_format'] = 'short';
  $handler->display->display_options['fields']['time_start']['second_date_format'] = 'ding_date_only';
  /* Field: Quiz result: Date finished */
  $handler->display->display_options['fields']['time_end']['id'] = 'time_end';
  $handler->display->display_options['fields']['time_end']['table'] = 'quiz_node_results';
  $handler->display->display_options['fields']['time_end']['field'] = 'time_end';
  $handler->display->display_options['fields']['time_end']['date_format'] = 'short';
  $handler->display->display_options['fields']['time_end']['second_date_format'] = 'ding_date_only';
  $handler->display->display_options['defaults']['sorts'] = FALSE;
  $handler->display->display_options['defaults']['filter_groups'] = FALSE;
  $handler->display->display_options['defaults']['filters'] = FALSE;
  /* Filter criterion: Content: Type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'node';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'multichoice' => 'multichoice',
    'quiz' => 'quiz',
  );
  /* Filter criterion: Quiz result: Uid */
  $handler->display->display_options['filters']['uid']['id'] = 'uid';
  $handler->display->display_options['filters']['uid']['table'] = 'quiz_node_results';
  $handler->display->display_options['filters']['uid']['field'] = 'uid';
  $handler->display->display_options['filters']['uid']['operator'] = '!=';
  $handler->display->display_options['filters']['uid']['value']['value'] = '0';
  $handler->display->display_options['path'] = 'ding-christmas-calendar-export.csv';
  $translatables['export_xmas_calendar_results'] = array(
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
    t('Data export'),
    t('User'),
    t('Title'),
    t('User name'),
    t('Nid'),
    t('.'),
    t(','),
    t('Score'),
    t('Evaluated'),
    t('Date started'),
    t('Date finished'),
  );
  $export['export_xmas_calendar_results'] = $view;

  return $export;
}
