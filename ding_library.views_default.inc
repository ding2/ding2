<?php
/**
 * @file
 * ding_library.views_default.inc
 */

/**
 * Implements hook_views_default_views().
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
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['query']['options']['query_comment'] = FALSE;
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['exposed_form']['options']['reset_button_label'] = 'Gendan';
  $handler->display->display_options['pager']['type'] = 'none';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['style_plugin'] = 'list';
  $handler->display->display_options['style_options']['row_class'] = 'vcard clearfix library-[nid]';
  $handler->display->display_options['style_options']['class'] = 'library-list';
  $handler->display->display_options['style_options']['wrapper_class'] = '';
  $handler->display->display_options['row_plugin'] = 'fields';
  /* Field: Content: Nid */
  $handler->display->display_options['fields']['nid']['id'] = 'nid';
  $handler->display->display_options['fields']['nid']['table'] = 'node';
  $handler->display->display_options['fields']['nid']['field'] = 'nid';
  $handler->display->display_options['fields']['nid']['label'] = '';
  $handler->display->display_options['fields']['nid']['exclude'] = TRUE;
  $handler->display->display_options['fields']['nid']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['nid']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['nid']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['nid']['alter']['external'] = 0;
  $handler->display->display_options['fields']['nid']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['nid']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['nid']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['nid']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['nid']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['nid']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['nid']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['nid']['alter']['html'] = 0;
  $handler->display->display_options['fields']['nid']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['nid']['element_default_classes'] = 0;
  $handler->display->display_options['fields']['nid']['hide_empty'] = 0;
  $handler->display->display_options['fields']['nid']['empty_zero'] = 0;
  $handler->display->display_options['fields']['nid']['hide_alter_empty'] = 0;
  $handler->display->display_options['fields']['nid']['link_to_node'] = 0;
  /* Field: Content: Opening hours */
  $handler->display->display_options['fields']['field_opening_hours']['id'] = 'field_opening_hours';
  $handler->display->display_options['fields']['field_opening_hours']['table'] = 'field_data_field_opening_hours';
  $handler->display->display_options['fields']['field_opening_hours']['field'] = 'field_opening_hours';
  $handler->display->display_options['fields']['field_opening_hours']['label'] = '';
  $handler->display->display_options['fields']['field_opening_hours']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['field_opening_hours']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['field_opening_hours']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['field_opening_hours']['alter']['external'] = 0;
  $handler->display->display_options['fields']['field_opening_hours']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['field_opening_hours']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['field_opening_hours']['alter']['nl2br'] = 1;
  $handler->display->display_options['fields']['field_opening_hours']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['field_opening_hours']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['field_opening_hours']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['field_opening_hours']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['field_opening_hours']['alter']['html'] = 0;
  $handler->display->display_options['fields']['field_opening_hours']['element_type'] = 'div';
  $handler->display->display_options['fields']['field_opening_hours']['element_class'] = 'opening-hours';
  $handler->display->display_options['fields']['field_opening_hours']['element_label_type'] = '0';
  $handler->display->display_options['fields']['field_opening_hours']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_opening_hours']['element_wrapper_type'] = '0';
  $handler->display->display_options['fields']['field_opening_hours']['element_default_classes'] = 0;
  $handler->display->display_options['fields']['field_opening_hours']['hide_empty'] = 0;
  $handler->display->display_options['fields']['field_opening_hours']['empty_zero'] = 0;
  $handler->display->display_options['fields']['field_opening_hours']['hide_alter_empty'] = 0;
  $handler->display->display_options['fields']['field_opening_hours']['type'] = 'text_plain';
  $handler->display->display_options['fields']['field_opening_hours']['field_api_classes'] = 0;
  /* Field: Content: List image */
  $handler->display->display_options['fields']['field_list_image']['id'] = 'field_list_image';
  $handler->display->display_options['fields']['field_list_image']['table'] = 'field_data_field_list_image';
  $handler->display->display_options['fields']['field_list_image']['field'] = 'field_list_image';
  $handler->display->display_options['fields']['field_list_image']['label'] = '';
  $handler->display->display_options['fields']['field_list_image']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['field_list_image']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['field_list_image']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['field_list_image']['alter']['external'] = 0;
  $handler->display->display_options['fields']['field_list_image']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['field_list_image']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['field_list_image']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['field_list_image']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['field_list_image']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['field_list_image']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['field_list_image']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['field_list_image']['alter']['html'] = 0;
  $handler->display->display_options['fields']['field_list_image']['element_type'] = 'div';
  $handler->display->display_options['fields']['field_list_image']['element_class'] = 'list-image';
  $handler->display->display_options['fields']['field_list_image']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_list_image']['element_wrapper_type'] = '0';
  $handler->display->display_options['fields']['field_list_image']['element_default_classes'] = 0;
  $handler->display->display_options['fields']['field_list_image']['hide_empty'] = 0;
  $handler->display->display_options['fields']['field_list_image']['empty_zero'] = 0;
  $handler->display->display_options['fields']['field_list_image']['hide_alter_empty'] = 0;
  $handler->display->display_options['fields']['field_list_image']['click_sort_column'] = 'fid';
  $handler->display->display_options['fields']['field_list_image']['settings'] = array(
    'image_style' => 'ding_library_list',
    'image_link' => 'content',
  );
  $handler->display->display_options['fields']['field_list_image']['field_api_classes'] = 0;
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
  $handler->display->display_options['fields']['title']['element_type'] = 'h2';
  $handler->display->display_options['fields']['title']['element_class'] = 'title fn org middle-col';
  $handler->display->display_options['fields']['title']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['title']['element_wrapper_type'] = '0';
  $handler->display->display_options['fields']['title']['element_default_classes'] = 0;
  $handler->display->display_options['fields']['title']['hide_empty'] = 0;
  $handler->display->display_options['fields']['title']['empty_zero'] = 0;
  $handler->display->display_options['fields']['title']['hide_alter_empty'] = 0;
  $handler->display->display_options['fields']['title']['link_to_node'] = 1;
  /* Field: Content: Address */
  $handler->display->display_options['fields']['field_address']['id'] = 'field_address';
  $handler->display->display_options['fields']['field_address']['table'] = 'field_data_field_address';
  $handler->display->display_options['fields']['field_address']['field'] = 'field_address';
  $handler->display->display_options['fields']['field_address']['label'] = '';
  $handler->display->display_options['fields']['field_address']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['field_address']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['field_address']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['field_address']['alter']['external'] = 0;
  $handler->display->display_options['fields']['field_address']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['field_address']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['field_address']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['field_address']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['field_address']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['field_address']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['field_address']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['field_address']['alter']['html'] = 0;
  $handler->display->display_options['fields']['field_address']['element_type'] = 'div';
  $handler->display->display_options['fields']['field_address']['element_class'] = 'address add middle-col';
  $handler->display->display_options['fields']['field_address']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_address']['element_wrapper_type'] = '0';
  $handler->display->display_options['fields']['field_address']['element_default_classes'] = 0;
  $handler->display->display_options['fields']['field_address']['hide_empty'] = 1;
  $handler->display->display_options['fields']['field_address']['empty_zero'] = 0;
  $handler->display->display_options['fields']['field_address']['hide_alter_empty'] = 0;
  /* Field: Content: Phone number */
  $handler->display->display_options['fields']['field_phone']['id'] = 'field_phone';
  $handler->display->display_options['fields']['field_phone']['table'] = 'field_data_field_phone';
  $handler->display->display_options['fields']['field_phone']['field'] = 'field_phone';
  $handler->display->display_options['fields']['field_phone']['label'] = 'Phone';
  $handler->display->display_options['fields']['field_phone']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['field_phone']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['field_phone']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['field_phone']['alter']['external'] = 0;
  $handler->display->display_options['fields']['field_phone']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['field_phone']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['field_phone']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['field_phone']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['field_phone']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['field_phone']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['field_phone']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['field_phone']['alter']['html'] = 0;
  $handler->display->display_options['fields']['field_phone']['element_type'] = 'span';
  $handler->display->display_options['fields']['field_phone']['element_class'] = 'value';
  $handler->display->display_options['fields']['field_phone']['element_label_type'] = 'span';
  $handler->display->display_options['fields']['field_phone']['element_label_class'] = 'type';
  $handler->display->display_options['fields']['field_phone']['element_label_colon'] = 1;
  $handler->display->display_options['fields']['field_phone']['element_wrapper_type'] = 'div';
  $handler->display->display_options['fields']['field_phone']['element_wrapper_class'] = 'tel phone middle-col';
  $handler->display->display_options['fields']['field_phone']['element_default_classes'] = 0;
  $handler->display->display_options['fields']['field_phone']['hide_empty'] = 1;
  $handler->display->display_options['fields']['field_phone']['empty_zero'] = 0;
  $handler->display->display_options['fields']['field_phone']['hide_alter_empty'] = 0;
  $handler->display->display_options['fields']['field_phone']['field_api_classes'] = 0;
  /* Field: Content: Fax number */
  $handler->display->display_options['fields']['field_fax']['id'] = 'field_fax';
  $handler->display->display_options['fields']['field_fax']['table'] = 'field_data_field_fax';
  $handler->display->display_options['fields']['field_fax']['field'] = 'field_fax';
  $handler->display->display_options['fields']['field_fax']['label'] = 'Fax';
  $handler->display->display_options['fields']['field_fax']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['field_fax']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['field_fax']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['field_fax']['alter']['external'] = 0;
  $handler->display->display_options['fields']['field_fax']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['field_fax']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['field_fax']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['field_fax']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['field_fax']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['field_fax']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['field_fax']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['field_fax']['alter']['html'] = 0;
  $handler->display->display_options['fields']['field_fax']['element_type'] = 'span';
  $handler->display->display_options['fields']['field_fax']['element_class'] = 'value';
  $handler->display->display_options['fields']['field_fax']['element_label_type'] = 'span';
  $handler->display->display_options['fields']['field_fax']['element_label_class'] = 'type';
  $handler->display->display_options['fields']['field_fax']['element_label_colon'] = 1;
  $handler->display->display_options['fields']['field_fax']['element_wrapper_type'] = 'div';
  $handler->display->display_options['fields']['field_fax']['element_wrapper_class'] = 'tel fax middle-col';
  $handler->display->display_options['fields']['field_fax']['element_default_classes'] = 0;
  $handler->display->display_options['fields']['field_fax']['hide_empty'] = 1;
  $handler->display->display_options['fields']['field_fax']['empty_zero'] = 0;
  $handler->display->display_options['fields']['field_fax']['hide_alter_empty'] = 0;
  $handler->display->display_options['fields']['field_fax']['field_api_classes'] = 0;
  /* Field: Content: E-mail address */
  $handler->display->display_options['fields']['field_email']['id'] = 'field_email';
  $handler->display->display_options['fields']['field_email']['table'] = 'field_data_field_email';
  $handler->display->display_options['fields']['field_email']['field'] = 'field_email';
  $handler->display->display_options['fields']['field_email']['label'] = 'E-mail';
  $handler->display->display_options['fields']['field_email']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['field_email']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['field_email']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['field_email']['alter']['external'] = 0;
  $handler->display->display_options['fields']['field_email']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['field_email']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['field_email']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['field_email']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['field_email']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['field_email']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['field_email']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['field_email']['alter']['html'] = 0;
  $handler->display->display_options['fields']['field_email']['element_type'] = 'span';
  $handler->display->display_options['fields']['field_email']['element_class'] = 'value';
  $handler->display->display_options['fields']['field_email']['element_label_type'] = 'span';
  $handler->display->display_options['fields']['field_email']['element_label_class'] = 'type';
  $handler->display->display_options['fields']['field_email']['element_label_colon'] = 1;
  $handler->display->display_options['fields']['field_email']['element_wrapper_type'] = 'div';
  $handler->display->display_options['fields']['field_email']['element_wrapper_class'] = 'email middle-col';
  $handler->display->display_options['fields']['field_email']['element_default_classes'] = 0;
  $handler->display->display_options['fields']['field_email']['hide_empty'] = 1;
  $handler->display->display_options['fields']['field_email']['empty_zero'] = 0;
  $handler->display->display_options['fields']['field_email']['hide_alter_empty'] = 0;
  $handler->display->display_options['fields']['field_email']['field_api_classes'] = 0;
  /* Sort criterion: Content: Title */
  $handler->display->display_options['sorts']['title']['id'] = 'title';
  $handler->display->display_options['sorts']['title']['table'] = 'node';
  $handler->display->display_options['sorts']['title']['field'] = 'title';
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
  /* Filter criterion: Content translation: Language */
  $handler->display->display_options['filters']['language']['id'] = 'language';
  $handler->display->display_options['filters']['language']['table'] = 'node';
  $handler->display->display_options['filters']['language']['field'] = 'language';
  $handler->display->display_options['filters']['language']['value'] = array(
    '***CURRENT_LANGUAGE***' => '***CURRENT_LANGUAGE***',
    'und' => 'und',
  );

  /* Display: Content pane */
  $handler = $view->new_display('panel_pane', 'Content pane', 'panel_pane_1');
  $handler->display->display_options['allow']['use_pager'] = 0;
  $handler->display->display_options['allow']['items_per_page'] = 0;
  $handler->display->display_options['allow']['offset'] = 0;
  $handler->display->display_options['allow']['link_to_view'] = 0;
  $handler->display->display_options['allow']['more_link'] = 0;
  $handler->display->display_options['allow']['path_override'] = 0;
  $handler->display->display_options['allow']['title_override'] = 'title_override';
  $handler->display->display_options['allow']['exposed_form'] = 0;
  $handler->display->display_options['allow']['fields_override'] = 0;

  /* Display: OpenLayers Data Overlay */
  $handler = $view->new_display('openlayers', 'OpenLayers Data Overlay', 'openlayers_1');
  $handler->display->display_options['pager']['type'] = 'none';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['defaults']['style_plugin'] = FALSE;
  $handler->display->display_options['style_plugin'] = 'openlayers_data';
  $handler->display->display_options['style_options']['data_source'] = array(
    'value' => 'wkt',
    'other_lat' => 'field_opening_hours',
    'other_lon' => 'field_opening_hours',
    'wkt' => 'field_geocode',
    'other_top' => 'field_opening_hours',
    'other_right' => 'field_opening_hours',
    'other_bottom' => 'field_opening_hours',
    'other_left' => 'field_opening_hours',
    'name_field' => 'title',
    'description_field' => '#row',
  );
  $handler->display->display_options['defaults']['style_options'] = FALSE;
  $handler->display->display_options['defaults']['row_plugin'] = FALSE;
  $handler->display->display_options['row_plugin'] = 'fields';
  $handler->display->display_options['row_options']['hide_empty'] = 0;
  $handler->display->display_options['row_options']['default_field_elements'] = 0;
  $handler->display->display_options['defaults']['row_options'] = FALSE;
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Field: Content: Nid */
  $handler->display->display_options['fields']['nid']['id'] = 'nid';
  $handler->display->display_options['fields']['nid']['table'] = 'node';
  $handler->display->display_options['fields']['nid']['field'] = 'nid';
  $handler->display->display_options['fields']['nid']['label'] = '';
  $handler->display->display_options['fields']['nid']['exclude'] = TRUE;
  $handler->display->display_options['fields']['nid']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['nid']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['nid']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['nid']['alter']['external'] = 0;
  $handler->display->display_options['fields']['nid']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['nid']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['nid']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['nid']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['nid']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['nid']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['nid']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['nid']['alter']['html'] = 0;
  $handler->display->display_options['fields']['nid']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['nid']['element_default_classes'] = 0;
  $handler->display->display_options['fields']['nid']['hide_empty'] = 0;
  $handler->display->display_options['fields']['nid']['empty_zero'] = 0;
  $handler->display->display_options['fields']['nid']['hide_alter_empty'] = 0;
  $handler->display->display_options['fields']['nid']['link_to_node'] = 0;
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = '';
  $handler->display->display_options['fields']['title']['exclude'] = TRUE;
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
  $handler->display->display_options['fields']['title']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['title']['element_default_classes'] = 0;
  $handler->display->display_options['fields']['title']['hide_empty'] = 0;
  $handler->display->display_options['fields']['title']['empty_zero'] = 0;
  $handler->display->display_options['fields']['title']['hide_alter_empty'] = 0;
  $handler->display->display_options['fields']['title']['link_to_node'] = 0;
  /* Field: Content: Geocode */
  $handler->display->display_options['fields']['field_geocode']['id'] = 'field_geocode';
  $handler->display->display_options['fields']['field_geocode']['table'] = 'field_data_field_geocode';
  $handler->display->display_options['fields']['field_geocode']['field'] = 'field_geocode';
  $handler->display->display_options['fields']['field_geocode']['label'] = '';
  $handler->display->display_options['fields']['field_geocode']['exclude'] = TRUE;
  $handler->display->display_options['fields']['field_geocode']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['field_geocode']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['field_geocode']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['field_geocode']['alter']['external'] = 0;
  $handler->display->display_options['fields']['field_geocode']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['field_geocode']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['field_geocode']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['field_geocode']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['field_geocode']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['field_geocode']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['field_geocode']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['field_geocode']['alter']['html'] = 0;
  $handler->display->display_options['fields']['field_geocode']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_geocode']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['field_geocode']['hide_empty'] = 0;
  $handler->display->display_options['fields']['field_geocode']['empty_zero'] = 0;
  $handler->display->display_options['fields']['field_geocode']['hide_alter_empty'] = 0;
  $handler->display->display_options['fields']['field_geocode']['click_sort_column'] = 'wkt';
  $handler->display->display_options['fields']['field_geocode']['settings'] = array(
    'data' => 'full',
  );
  $handler->display->display_options['fields']['field_geocode']['field_api_classes'] = 0;
  /* Field: Content: Address */
  $handler->display->display_options['fields']['field_address']['id'] = 'field_address';
  $handler->display->display_options['fields']['field_address']['table'] = 'field_data_field_address';
  $handler->display->display_options['fields']['field_address']['field'] = 'field_address';
  $handler->display->display_options['fields']['field_address']['label'] = '';
  $handler->display->display_options['fields']['field_address']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['field_address']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['field_address']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['field_address']['alter']['external'] = 0;
  $handler->display->display_options['fields']['field_address']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['field_address']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['field_address']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['field_address']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['field_address']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['field_address']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['field_address']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['field_address']['alter']['html'] = 0;
  $handler->display->display_options['fields']['field_address']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_address']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['field_address']['hide_empty'] = 0;
  $handler->display->display_options['fields']['field_address']['empty_zero'] = 0;
  $handler->display->display_options['fields']['field_address']['hide_alter_empty'] = 0;
  /* Field: Content: Opening hours */
  $handler->display->display_options['fields']['field_opening_hours']['id'] = 'field_opening_hours';
  $handler->display->display_options['fields']['field_opening_hours']['table'] = 'field_data_field_opening_hours';
  $handler->display->display_options['fields']['field_opening_hours']['field'] = 'field_opening_hours';
  $handler->display->display_options['fields']['field_opening_hours']['label'] = '';
  $handler->display->display_options['fields']['field_opening_hours']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['field_opening_hours']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['field_opening_hours']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['field_opening_hours']['alter']['external'] = 0;
  $handler->display->display_options['fields']['field_opening_hours']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['field_opening_hours']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['field_opening_hours']['alter']['nl2br'] = 1;
  $handler->display->display_options['fields']['field_opening_hours']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['field_opening_hours']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['field_opening_hours']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['field_opening_hours']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['field_opening_hours']['alter']['html'] = 0;
  $handler->display->display_options['fields']['field_opening_hours']['element_type'] = 'div';
  $handler->display->display_options['fields']['field_opening_hours']['element_class'] = 'opening-hours';
  $handler->display->display_options['fields']['field_opening_hours']['element_label_type'] = '0';
  $handler->display->display_options['fields']['field_opening_hours']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_opening_hours']['element_wrapper_type'] = '0';
  $handler->display->display_options['fields']['field_opening_hours']['element_default_classes'] = 0;
  $handler->display->display_options['fields']['field_opening_hours']['hide_empty'] = 0;
  $handler->display->display_options['fields']['field_opening_hours']['empty_zero'] = 0;
  $handler->display->display_options['fields']['field_opening_hours']['hide_alter_empty'] = 0;
  $handler->display->display_options['fields']['field_opening_hours']['type'] = 'text_plain';
  $handler->display->display_options['fields']['field_opening_hours']['field_api_classes'] = 0;
  $translatables['ding_library'] = array(
    t('Master'),
    t('more'),
    t('Apply'),
    t('Gendan'),
    t('Sort by'),
    t('Asc'),
    t('Desc'),
    t('Phone'),
    t('Fax'),
    t('E-mail'),
    t('Content pane'),
    t('View panes'),
    t('OpenLayers Data Overlay'),
  );
  $export['ding_library'] = $view;

  return $export;
}
