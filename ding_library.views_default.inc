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
  /* Field: Content: Teaser image */
  $handler->display->display_options['fields']['ding_library_teaser_image']['id'] = 'ding_library_teaser_image';
  $handler->display->display_options['fields']['ding_library_teaser_image']['table'] = 'field_data_ding_library_teaser_image';
  $handler->display->display_options['fields']['ding_library_teaser_image']['field'] = 'ding_library_teaser_image';
  $handler->display->display_options['fields']['ding_library_teaser_image']['label'] = '';
  $handler->display->display_options['fields']['ding_library_teaser_image']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['ding_library_teaser_image']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['ding_library_teaser_image']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['ding_library_teaser_image']['alter']['external'] = 0;
  $handler->display->display_options['fields']['ding_library_teaser_image']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['ding_library_teaser_image']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['ding_library_teaser_image']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['ding_library_teaser_image']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['ding_library_teaser_image']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['ding_library_teaser_image']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['ding_library_teaser_image']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['ding_library_teaser_image']['alter']['html'] = 0;
  $handler->display->display_options['fields']['ding_library_teaser_image']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['ding_library_teaser_image']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['ding_library_teaser_image']['hide_empty'] = 0;
  $handler->display->display_options['fields']['ding_library_teaser_image']['empty_zero'] = 0;
  $handler->display->display_options['fields']['ding_library_teaser_image']['hide_alter_empty'] = 0;
  $handler->display->display_options['fields']['ding_library_teaser_image']['click_sort_column'] = 'fid';
  $handler->display->display_options['fields']['ding_library_teaser_image']['settings'] = array(
    'image_style' => 'ding_small',
    'image_link' => '',
  );
  $handler->display->display_options['fields']['ding_library_teaser_image']['field_api_classes'] = 0;
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
  $handler->display->display_options['fields']['ding_library_address']['id'] = 'ding_library_address';
  $handler->display->display_options['fields']['ding_library_address']['table'] = 'field_data_ding_library_address';
  $handler->display->display_options['fields']['ding_library_address']['field'] = 'ding_library_address';
  $handler->display->display_options['fields']['ding_library_address']['label'] = '';
  $handler->display->display_options['fields']['ding_library_address']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['ding_library_address']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['ding_library_address']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['ding_library_address']['alter']['external'] = 0;
  $handler->display->display_options['fields']['ding_library_address']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['ding_library_address']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['ding_library_address']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['ding_library_address']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['ding_library_address']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['ding_library_address']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['ding_library_address']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['ding_library_address']['alter']['html'] = 0;
  $handler->display->display_options['fields']['ding_library_address']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['ding_library_address']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['ding_library_address']['hide_empty'] = 0;
  $handler->display->display_options['fields']['ding_library_address']['empty_zero'] = 0;
  $handler->display->display_options['fields']['ding_library_address']['hide_alter_empty'] = 0;
  $handler->display->display_options['fields']['ding_library_address']['click_sort_column'] = 'country';
  $handler->display->display_options['fields']['ding_library_address']['settings'] = array(
    'use_widget_handlers' => 1,
    'format_handlers' => array(
      'address' => 'address',
    ),
  );
  $handler->display->display_options['fields']['ding_library_address']['field_api_classes'] = 0;
  /* Field: Content: Phone number */
  $handler->display->display_options['fields']['ding_library_phone']['id'] = 'ding_library_phone';
  $handler->display->display_options['fields']['ding_library_phone']['table'] = 'field_data_ding_library_phone';
  $handler->display->display_options['fields']['ding_library_phone']['field'] = 'ding_library_phone';
  $handler->display->display_options['fields']['ding_library_phone']['label'] = 'Phone';
  $handler->display->display_options['fields']['ding_library_phone']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['ding_library_phone']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['ding_library_phone']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['ding_library_phone']['alter']['external'] = 0;
  $handler->display->display_options['fields']['ding_library_phone']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['ding_library_phone']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['ding_library_phone']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['ding_library_phone']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['ding_library_phone']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['ding_library_phone']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['ding_library_phone']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['ding_library_phone']['alter']['html'] = 0;
  $handler->display->display_options['fields']['ding_library_phone']['element_label_colon'] = 1;
  $handler->display->display_options['fields']['ding_library_phone']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['ding_library_phone']['hide_empty'] = 0;
  $handler->display->display_options['fields']['ding_library_phone']['empty_zero'] = 0;
  $handler->display->display_options['fields']['ding_library_phone']['hide_alter_empty'] = 0;
  $handler->display->display_options['fields']['ding_library_phone']['field_api_classes'] = 0;
  /* Field: Content: Fax number */
  $handler->display->display_options['fields']['ding_library_fax']['id'] = 'ding_library_fax';
  $handler->display->display_options['fields']['ding_library_fax']['table'] = 'field_data_ding_library_fax';
  $handler->display->display_options['fields']['ding_library_fax']['field'] = 'ding_library_fax';
  $handler->display->display_options['fields']['ding_library_fax']['label'] = 'Fax';
  $handler->display->display_options['fields']['ding_library_fax']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['ding_library_fax']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['ding_library_fax']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['ding_library_fax']['alter']['external'] = 0;
  $handler->display->display_options['fields']['ding_library_fax']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['ding_library_fax']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['ding_library_fax']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['ding_library_fax']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['ding_library_fax']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['ding_library_fax']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['ding_library_fax']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['ding_library_fax']['alter']['html'] = 0;
  $handler->display->display_options['fields']['ding_library_fax']['element_label_colon'] = 1;
  $handler->display->display_options['fields']['ding_library_fax']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['ding_library_fax']['hide_empty'] = 0;
  $handler->display->display_options['fields']['ding_library_fax']['empty_zero'] = 0;
  $handler->display->display_options['fields']['ding_library_fax']['hide_alter_empty'] = 0;
  $handler->display->display_options['fields']['ding_library_fax']['field_api_classes'] = 0;
  /* Field: Content: E-mail address */
  $handler->display->display_options['fields']['ding_library_email']['id'] = 'ding_library_email';
  $handler->display->display_options['fields']['ding_library_email']['table'] = 'field_data_ding_library_email';
  $handler->display->display_options['fields']['ding_library_email']['field'] = 'ding_library_email';
  $handler->display->display_options['fields']['ding_library_email']['label'] = 'E-mail';
  $handler->display->display_options['fields']['ding_library_email']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['ding_library_email']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['ding_library_email']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['ding_library_email']['alter']['external'] = 0;
  $handler->display->display_options['fields']['ding_library_email']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['ding_library_email']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['ding_library_email']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['ding_library_email']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['ding_library_email']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['ding_library_email']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['ding_library_email']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['ding_library_email']['alter']['html'] = 0;
  $handler->display->display_options['fields']['ding_library_email']['element_label_colon'] = 1;
  $handler->display->display_options['fields']['ding_library_email']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['ding_library_email']['hide_empty'] = 0;
  $handler->display->display_options['fields']['ding_library_email']['empty_zero'] = 0;
  $handler->display->display_options['fields']['ding_library_email']['hide_alter_empty'] = 0;
  $handler->display->display_options['fields']['ding_library_email']['field_api_classes'] = 0;
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
    t('Phone'),
    t('Fax'),
    t('E-mail'),
    t('Content pane'),
    t('View panes'),
  );
  $export['ding_library'] = $view;

  return $export;
}
