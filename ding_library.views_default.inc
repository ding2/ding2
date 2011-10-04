<?php
/**
 * @file
 * ding_library.views_default.inc
 */

/**
 * Implementation of hook_views_default_views().
 */
function ding_library_views_default_views() {
  $export = array();

  $view = new view;
  $view->name = 'ding_library';
  $view->description = '';
  $view->tag = 'ding_library';
  $view->base_table = 'node';
  $view->human_name = 'Ding library';
  $view->core = 7;
  $view->api_version = '3.0-alpha1';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Libraries';
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['query']['options']['query_comment'] = FALSE;
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'none';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['style_plugin'] = 'list';
  $handler->display->display_options['style_options']['row_class'] = 'library';
  $handler->display->display_options['style_options']['class'] = 'library-list';
  $handler->display->display_options['style_options']['wrapper_class'] = '';
  $handler->display->display_options['row_plugin'] = 'fields';
  /* Relationship: Group: Node group */
  $handler->display->display_options['relationships']['og_rel']['id'] = 'og_rel';
  $handler->display->display_options['relationships']['og_rel']['table'] = 'node';
  $handler->display->display_options['relationships']['og_rel']['field'] = 'og_rel';
  $handler->display->display_options['relationships']['og_rel']['required'] = 0;
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
  $handler->display->display_options['fields']['title']['element_type'] = '0';
  $handler->display->display_options['fields']['title']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['title']['element_wrapper_type'] = '0';
  $handler->display->display_options['fields']['title']['element_default_classes'] = 0;
  $handler->display->display_options['fields']['title']['hide_empty'] = 0;
  $handler->display->display_options['fields']['title']['empty_zero'] = 0;
  $handler->display->display_options['fields']['title']['hide_alter_empty'] = 0;
  $handler->display->display_options['fields']['title']['link_to_node'] = 1;
  /* Field: Content: Address */
  $handler->display->display_options['fields']['field_library_address']['id'] = 'field_library_address';
  $handler->display->display_options['fields']['field_library_address']['table'] = 'field_data_field_library_address';
  $handler->display->display_options['fields']['field_library_address']['field'] = 'field_library_address';
  $handler->display->display_options['fields']['field_library_address']['label'] = '';
  $handler->display->display_options['fields']['field_library_address']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['field_library_address']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['field_library_address']['alter']['path'] = 'mailto:';
  $handler->display->display_options['fields']['field_library_address']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['field_library_address']['alter']['external'] = 0;
  $handler->display->display_options['fields']['field_library_address']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['field_library_address']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['field_library_address']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['field_library_address']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['field_library_address']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['field_library_address']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['field_library_address']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['field_library_address']['alter']['html'] = 0;
  $handler->display->display_options['fields']['field_library_address']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_library_address']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['field_library_address']['hide_empty'] = 0;
  $handler->display->display_options['fields']['field_library_address']['empty_zero'] = 0;
  $handler->display->display_options['fields']['field_library_address']['hide_alter_empty'] = 0;
  $handler->display->display_options['fields']['field_library_address']['click_sort_column'] = 'country';
  $handler->display->display_options['fields']['field_library_address']['settings'] = array(
    'use_widget_handlers' => 1,
    'format_handlers' => array(
      'address' => 'address',
    ),
  );
  $handler->display->display_options['fields']['field_library_address']['field_api_classes'] = 0;
  /* Field: Content: E-mail address */
  $handler->display->display_options['fields']['field_library_email']['id'] = 'field_library_email';
  $handler->display->display_options['fields']['field_library_email']['table'] = 'field_data_field_library_email';
  $handler->display->display_options['fields']['field_library_email']['field'] = 'field_library_email';
  $handler->display->display_options['fields']['field_library_email']['label'] = '';
  $handler->display->display_options['fields']['field_library_email']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['field_library_email']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['field_library_email']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['field_library_email']['alter']['external'] = 0;
  $handler->display->display_options['fields']['field_library_email']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['field_library_email']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['field_library_email']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['field_library_email']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['field_library_email']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['field_library_email']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['field_library_email']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['field_library_email']['alter']['html'] = 0;
  $handler->display->display_options['fields']['field_library_email']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_library_email']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['field_library_email']['empty'] = 'Ingen e-mail';
  $handler->display->display_options['fields']['field_library_email']['hide_empty'] = 0;
  $handler->display->display_options['fields']['field_library_email']['empty_zero'] = 0;
  $handler->display->display_options['fields']['field_library_email']['hide_alter_empty'] = 0;
  $handler->display->display_options['fields']['field_library_email']['field_api_classes'] = 0;
  /* Sort criterion: Content: Title */
  $handler->display->display_options['sorts']['title']['id'] = 'title';
  $handler->display->display_options['sorts']['title']['table'] = 'node';
  $handler->display->display_options['sorts']['title']['field'] = 'title';
  $handler->display->display_options['sorts']['title']['order'] = 'DESC';
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
    'ding_library' => 'ding_library',
  );

  /* Display: Content pane */
  $handler = $view->new_display('panel_pane', 'Content pane', 'panel_pane_1');
  $translatables['ding_library'] = array(
    t('Master'),
    t('Libraries'),
    t('more'),
    t('Apply'),
    t('Reset'),
    t('Sort by'),
    t('Asc'),
    t('Desc'),
    t('group'),
    t('mailto:'),
    t('Ingen e-mail'),
    t('Content pane'),
    t('View panes'),
  );
  $export['ding_library'] = $view;

  return $export;
}
