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
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['use_more'] = TRUE;
  $handler->display->display_options['use_more_text'] = 'more..';
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['query']['options']['query_comment'] = FALSE;
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['exposed_form']['options']['reset_button_label'] = 'Gendan';
  $handler->display->display_options['pager']['type'] = 'some';
  $handler->display->display_options['pager']['options']['items_per_page'] = '5';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['style_plugin'] = 'default';
  $handler->display->display_options['row_plugin'] = 'fields';
  /* Header: Global: Text area */
  $handler->display->display_options['header']['area']['id'] = 'area';
  $handler->display->display_options['header']['area']['table'] = 'views';
  $handler->display->display_options['header']['area']['field'] = 'area';
  $handler->display->display_options['header']['area']['empty'] = FALSE;
  /* Field: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['ui_name'] = 'Title';
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
  $handler->display->display_options['fields']['title']['alter']['more_link'] = 0;
  $handler->display->display_options['fields']['title']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['title']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['title']['alter']['html'] = 0;
  $handler->display->display_options['fields']['title']['element_type'] = 'h3';
  $handler->display->display_options['fields']['title']['element_class'] = 'heading';
  $handler->display->display_options['fields']['title']['element_label_type'] = '0';
  $handler->display->display_options['fields']['title']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['title']['element_wrapper_type'] = '0';
  $handler->display->display_options['fields']['title']['element_default_classes'] = 0;
  $handler->display->display_options['fields']['title']['hide_empty'] = 0;
  $handler->display->display_options['fields']['title']['empty_zero'] = 0;
  $handler->display->display_options['fields']['title']['hide_alter_empty'] = 0;
  $handler->display->display_options['fields']['title']['link_to_node'] = 1;
  /* Field: Event category (excluded) */
  $handler->display->display_options['fields']['field_ding_event_category']['id'] = 'field_ding_event_category';
  $handler->display->display_options['fields']['field_ding_event_category']['table'] = 'field_data_field_ding_event_category';
  $handler->display->display_options['fields']['field_ding_event_category']['field'] = 'field_ding_event_category';
  $handler->display->display_options['fields']['field_ding_event_category']['ui_name'] = 'Event category (excluded)';
  $handler->display->display_options['fields']['field_ding_event_category']['label'] = '';
  $handler->display->display_options['fields']['field_ding_event_category']['exclude'] = TRUE;
  $handler->display->display_options['fields']['field_ding_event_category']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['field_ding_event_category']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['field_ding_event_category']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['field_ding_event_category']['alter']['external'] = 0;
  $handler->display->display_options['fields']['field_ding_event_category']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['field_ding_event_category']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['field_ding_event_category']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['field_ding_event_category']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['field_ding_event_category']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['field_ding_event_category']['alter']['more_link'] = 0;
  $handler->display->display_options['fields']['field_ding_event_category']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['field_ding_event_category']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['field_ding_event_category']['alter']['html'] = 0;
  $handler->display->display_options['fields']['field_ding_event_category']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_ding_event_category']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['field_ding_event_category']['hide_empty'] = 0;
  $handler->display->display_options['fields']['field_ding_event_category']['empty_zero'] = 0;
  $handler->display->display_options['fields']['field_ding_event_category']['hide_alter_empty'] = 1;
  $handler->display->display_options['fields']['field_ding_event_category']['field_api_classes'] = 0;
  /* Field: Date (excluded) */
  $handler->display->display_options['fields']['field_ding_event_date']['id'] = 'field_ding_event_date';
  $handler->display->display_options['fields']['field_ding_event_date']['table'] = 'field_data_field_ding_event_date';
  $handler->display->display_options['fields']['field_ding_event_date']['field'] = 'field_ding_event_date';
  $handler->display->display_options['fields']['field_ding_event_date']['ui_name'] = 'Date (excluded)';
  $handler->display->display_options['fields']['field_ding_event_date']['label'] = '';
  $handler->display->display_options['fields']['field_ding_event_date']['exclude'] = TRUE;
  $handler->display->display_options['fields']['field_ding_event_date']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['field_ding_event_date']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['field_ding_event_date']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['field_ding_event_date']['alter']['external'] = 0;
  $handler->display->display_options['fields']['field_ding_event_date']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['field_ding_event_date']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['field_ding_event_date']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['field_ding_event_date']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['field_ding_event_date']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['field_ding_event_date']['alter']['more_link'] = 0;
  $handler->display->display_options['fields']['field_ding_event_date']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['field_ding_event_date']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['field_ding_event_date']['alter']['html'] = 0;
  $handler->display->display_options['fields']['field_ding_event_date']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_ding_event_date']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['field_ding_event_date']['hide_empty'] = 0;
  $handler->display->display_options['fields']['field_ding_event_date']['empty_zero'] = 0;
  $handler->display->display_options['fields']['field_ding_event_date']['hide_alter_empty'] = 1;
  $handler->display->display_options['fields']['field_ding_event_date']['settings'] = array(
    'format_type' => 'long_date_only',
    'fromto' => 'value',
    'multiple_number' => '',
    'multiple_from' => '',
    'multiple_to' => '',
  );
  $handler->display->display_options['fields']['field_ding_event_date']['field_api_classes'] = 0;
  /* Field: Library (excluded) */
  $handler->display->display_options['fields']['field_ding_event_library']['id'] = 'field_ding_event_library';
  $handler->display->display_options['fields']['field_ding_event_library']['table'] = 'field_data_field_ding_event_library';
  $handler->display->display_options['fields']['field_ding_event_library']['field'] = 'field_ding_event_library';
  $handler->display->display_options['fields']['field_ding_event_library']['ui_name'] = 'Library (excluded)';
  $handler->display->display_options['fields']['field_ding_event_library']['label'] = '';
  $handler->display->display_options['fields']['field_ding_event_library']['exclude'] = TRUE;
  $handler->display->display_options['fields']['field_ding_event_library']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['field_ding_event_library']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['field_ding_event_library']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['field_ding_event_library']['alter']['external'] = 0;
  $handler->display->display_options['fields']['field_ding_event_library']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['field_ding_event_library']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['field_ding_event_library']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['field_ding_event_library']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['field_ding_event_library']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['field_ding_event_library']['alter']['more_link'] = 0;
  $handler->display->display_options['fields']['field_ding_event_library']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['field_ding_event_library']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['field_ding_event_library']['alter']['html'] = 0;
  $handler->display->display_options['fields']['field_ding_event_library']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_ding_event_library']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['field_ding_event_library']['hide_empty'] = 0;
  $handler->display->display_options['fields']['field_ding_event_library']['empty_zero'] = 0;
  $handler->display->display_options['fields']['field_ding_event_library']['hide_alter_empty'] = 1;
  $handler->display->display_options['fields']['field_ding_event_library']['click_sort_column'] = 'gid';
  $handler->display->display_options['fields']['field_ding_event_library']['field_api_classes'] = 0;
  /* Field: Location (excluded) */
  $handler->display->display_options['fields']['field_ding_event_location']['id'] = 'field_ding_event_location';
  $handler->display->display_options['fields']['field_ding_event_location']['table'] = 'field_data_field_ding_event_location';
  $handler->display->display_options['fields']['field_ding_event_location']['field'] = 'field_ding_event_location';
  $handler->display->display_options['fields']['field_ding_event_location']['ui_name'] = 'Location (excluded)';
  $handler->display->display_options['fields']['field_ding_event_location']['label'] = '';
  $handler->display->display_options['fields']['field_ding_event_location']['exclude'] = TRUE;
  $handler->display->display_options['fields']['field_ding_event_location']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['field_ding_event_location']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['field_ding_event_location']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['field_ding_event_location']['alter']['external'] = 0;
  $handler->display->display_options['fields']['field_ding_event_location']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['field_ding_event_location']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['field_ding_event_location']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['field_ding_event_location']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['field_ding_event_location']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['field_ding_event_location']['alter']['more_link'] = 0;
  $handler->display->display_options['fields']['field_ding_event_location']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['field_ding_event_location']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['field_ding_event_location']['alter']['html'] = 0;
  $handler->display->display_options['fields']['field_ding_event_location']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_ding_event_location']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['field_ding_event_location']['hide_empty'] = 0;
  $handler->display->display_options['fields']['field_ding_event_location']['empty_zero'] = 0;
  $handler->display->display_options['fields']['field_ding_event_location']['hide_alter_empty'] = 1;
  $handler->display->display_options['fields']['field_ding_event_location']['click_sort_column'] = 'name_line';
  $handler->display->display_options['fields']['field_ding_event_location']['settings'] = array(
    'use_widget_handlers' => 0,
    'format_handlers' => array(
      'name-oneline' => 'name-oneline',
    ),
  );
  $handler->display->display_options['fields']['field_ding_event_location']['field_api_classes'] = 0;
  /* Field: Price (excluded) */
  $handler->display->display_options['fields']['field_ding_event_price']['id'] = 'field_ding_event_price';
  $handler->display->display_options['fields']['field_ding_event_price']['table'] = 'field_data_field_ding_event_price';
  $handler->display->display_options['fields']['field_ding_event_price']['field'] = 'field_ding_event_price';
  $handler->display->display_options['fields']['field_ding_event_price']['ui_name'] = 'Price (excluded)';
  $handler->display->display_options['fields']['field_ding_event_price']['label'] = '';
  $handler->display->display_options['fields']['field_ding_event_price']['exclude'] = TRUE;
  $handler->display->display_options['fields']['field_ding_event_price']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['field_ding_event_price']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['field_ding_event_price']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['field_ding_event_price']['alter']['external'] = 0;
  $handler->display->display_options['fields']['field_ding_event_price']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['field_ding_event_price']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['field_ding_event_price']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['field_ding_event_price']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['field_ding_event_price']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['field_ding_event_price']['alter']['more_link'] = 0;
  $handler->display->display_options['fields']['field_ding_event_price']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['field_ding_event_price']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['field_ding_event_price']['alter']['html'] = 0;
  $handler->display->display_options['fields']['field_ding_event_price']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_ding_event_price']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['field_ding_event_price']['hide_empty'] = 0;
  $handler->display->display_options['fields']['field_ding_event_price']['empty_zero'] = 0;
  $handler->display->display_options['fields']['field_ding_event_price']['hide_alter_empty'] = 1;
  $handler->display->display_options['fields']['field_ding_event_price']['settings'] = array(
    'thousand_separator' => ' ',
    'prefix_suffix' => 1,
  );
  $handler->display->display_options['fields']['field_ding_event_price']['field_api_classes'] = 0;
  /* Field: Category, date, location and price */
  $handler->display->display_options['fields']['nothing']['id'] = 'nothing';
  $handler->display->display_options['fields']['nothing']['table'] = 'views';
  $handler->display->display_options['fields']['nothing']['field'] = 'nothing';
  $handler->display->display_options['fields']['nothing']['ui_name'] = 'Category, date, location and price';
  $handler->display->display_options['fields']['nothing']['label'] = '';
  $handler->display->display_options['fields']['nothing']['alter']['text'] = '<span class="label label-info">[field_ding_event_category]</span> <span class="date">[field_ding_event_date]</span> <span class="location">[field_ding_event_library]</span><span class="location">[field_ding_event_location]</span><span class="price">[field_ding_event_price]</span>';
  $handler->display->display_options['fields']['nothing']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['nothing']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['nothing']['alter']['external'] = 0;
  $handler->display->display_options['fields']['nothing']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['nothing']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['nothing']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['nothing']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['nothing']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['nothing']['alter']['more_link'] = 0;
  $handler->display->display_options['fields']['nothing']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['nothing']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['nothing']['alter']['html'] = 0;
  $handler->display->display_options['fields']['nothing']['element_type'] = 'div';
  $handler->display->display_options['fields']['nothing']['element_class'] = 'subheading';
  $handler->display->display_options['fields']['nothing']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['nothing']['element_default_classes'] = 0;
  $handler->display->display_options['fields']['nothing']['hide_empty'] = 0;
  $handler->display->display_options['fields']['nothing']['empty_zero'] = 0;
  $handler->display->display_options['fields']['nothing']['hide_alter_empty'] = 0;
  /* Field: Title image (event image default) */
  $handler->display->display_options['fields']['field_ding_event_title_image']['id'] = 'field_ding_event_title_image';
  $handler->display->display_options['fields']['field_ding_event_title_image']['table'] = 'field_data_field_ding_event_title_image';
  $handler->display->display_options['fields']['field_ding_event_title_image']['field'] = 'field_ding_event_title_image';
  $handler->display->display_options['fields']['field_ding_event_title_image']['ui_name'] = 'Title image (event image default)';
  $handler->display->display_options['fields']['field_ding_event_title_image']['label'] = '';
  $handler->display->display_options['fields']['field_ding_event_title_image']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['field_ding_event_title_image']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['field_ding_event_title_image']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['field_ding_event_title_image']['alter']['external'] = 0;
  $handler->display->display_options['fields']['field_ding_event_title_image']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['field_ding_event_title_image']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['field_ding_event_title_image']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['field_ding_event_title_image']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['field_ding_event_title_image']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['field_ding_event_title_image']['alter']['more_link'] = 0;
  $handler->display->display_options['fields']['field_ding_event_title_image']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['field_ding_event_title_image']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['field_ding_event_title_image']['alter']['html'] = 0;
  $handler->display->display_options['fields']['field_ding_event_title_image']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_ding_event_title_image']['element_default_classes'] = 0;
  $handler->display->display_options['fields']['field_ding_event_title_image']['hide_empty'] = 0;
  $handler->display->display_options['fields']['field_ding_event_title_image']['empty_zero'] = 0;
  $handler->display->display_options['fields']['field_ding_event_title_image']['hide_alter_empty'] = 1;
  $handler->display->display_options['fields']['field_ding_event_title_image']['click_sort_column'] = 'fid';
  $handler->display->display_options['fields']['field_ding_event_title_image']['settings'] = array(
    'image_style' => 'ding_event_image_default',
    'image_link' => 'content',
  );
  $handler->display->display_options['fields']['field_ding_event_title_image']['field_api_classes'] = 0;
  /* Field: Lead (content) */
  $handler->display->display_options['fields']['field_ding_event_lead']['id'] = 'field_ding_event_lead';
  $handler->display->display_options['fields']['field_ding_event_lead']['table'] = 'field_data_field_ding_event_lead';
  $handler->display->display_options['fields']['field_ding_event_lead']['field'] = 'field_ding_event_lead';
  $handler->display->display_options['fields']['field_ding_event_lead']['ui_name'] = 'Lead (content)';
  $handler->display->display_options['fields']['field_ding_event_lead']['label'] = '';
  $handler->display->display_options['fields']['field_ding_event_lead']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['field_ding_event_lead']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['field_ding_event_lead']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['field_ding_event_lead']['alter']['external'] = 0;
  $handler->display->display_options['fields']['field_ding_event_lead']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['field_ding_event_lead']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['field_ding_event_lead']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['field_ding_event_lead']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['field_ding_event_lead']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['field_ding_event_lead']['alter']['more_link'] = 0;
  $handler->display->display_options['fields']['field_ding_event_lead']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['field_ding_event_lead']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['field_ding_event_lead']['alter']['html'] = 0;
  $handler->display->display_options['fields']['field_ding_event_lead']['element_type'] = 'p';
  $handler->display->display_options['fields']['field_ding_event_lead']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_ding_event_lead']['element_default_classes'] = 0;
  $handler->display->display_options['fields']['field_ding_event_lead']['hide_empty'] = 0;
  $handler->display->display_options['fields']['field_ding_event_lead']['empty_zero'] = 0;
  $handler->display->display_options['fields']['field_ding_event_lead']['hide_alter_empty'] = 1;
  $handler->display->display_options['fields']['field_ding_event_lead']['field_api_classes'] = 0;
  /* Field: Link (read more) */
  $handler->display->display_options['fields']['view_node']['id'] = 'view_node';
  $handler->display->display_options['fields']['view_node']['table'] = 'views_entity_node';
  $handler->display->display_options['fields']['view_node']['field'] = 'view_node';
  $handler->display->display_options['fields']['view_node']['ui_name'] = 'Link (read more)';
  $handler->display->display_options['fields']['view_node']['label'] = '';
  $handler->display->display_options['fields']['view_node']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['view_node']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['view_node']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['view_node']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['view_node']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['view_node']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['view_node']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['view_node']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['view_node']['alter']['more_link'] = 0;
  $handler->display->display_options['fields']['view_node']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['view_node']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['view_node']['alter']['html'] = 0;
  $handler->display->display_options['fields']['view_node']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['view_node']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['view_node']['hide_empty'] = 0;
  $handler->display->display_options['fields']['view_node']['empty_zero'] = 0;
  $handler->display->display_options['fields']['view_node']['hide_alter_empty'] = 1;
  $handler->display->display_options['fields']['view_node']['text'] = 'Read more';
  /* Sort criterion: Content: Date -  start date (field_ding_event_date) */
  $handler->display->display_options['sorts']['field_ding_event_date_value']['id'] = 'field_ding_event_date_value';
  $handler->display->display_options['sorts']['field_ding_event_date_value']['table'] = 'field_data_field_ding_event_date';
  $handler->display->display_options['sorts']['field_ding_event_date_value']['field'] = 'field_ding_event_date_value';
  /* Contextual filter: Content: Library (field_ding_event_library:nid) */
  $handler->display->display_options['arguments']['ding_library_nid_1']['id'] = 'ding_library_nid_1';
  $handler->display->display_options['arguments']['ding_library_nid_1']['table'] = 'field_data_field_ding_event_library';
  $handler->display->display_options['arguments']['ding_library_nid_1']['field'] = 'ding_library_nid';
  $handler->display->display_options['arguments']['ding_library_nid_1']['default_action'] = 'default';
  $handler->display->display_options['arguments']['ding_library_nid_1']['default_argument_type'] = 'fixed';
  $handler->display->display_options['arguments']['ding_library_nid_1']['default_argument_options']['argument'] = 'all';
  $handler->display->display_options['arguments']['ding_library_nid_1']['default_argument_skip_url'] = 0;
  $handler->display->display_options['arguments']['ding_library_nid_1']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['ding_library_nid_1']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['ding_library_nid_1']['summary_options']['items_per_page'] = '25';
  $handler->display->display_options['arguments']['ding_library_nid_1']['break_phrase'] = 0;
  $handler->display->display_options['arguments']['ding_library_nid_1']['not'] = 0;
  /* Contextual filter: Content: Has taxonomy term ID */
  $handler->display->display_options['arguments']['tid']['id'] = 'tid';
  $handler->display->display_options['arguments']['tid']['table'] = 'taxonomy_index';
  $handler->display->display_options['arguments']['tid']['field'] = 'tid';
  $handler->display->display_options['arguments']['tid']['default_argument_type'] = 'fixed';
  $handler->display->display_options['arguments']['tid']['default_argument_skip_url'] = 0;
  $handler->display->display_options['arguments']['tid']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['tid']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['tid']['summary_options']['items_per_page'] = '25';
  $handler->display->display_options['arguments']['tid']['break_phrase'] = 0;
  $handler->display->display_options['arguments']['tid']['add_table'] = 0;
  $handler->display->display_options['arguments']['tid']['require_value'] = 0;
  $handler->display->display_options['arguments']['tid']['reduce_duplicates'] = 0;
  $handler->display->display_options['arguments']['tid']['set_breadcrumb'] = 0;
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
  /* Filter criterion: Date: Date (node) */
  $handler->display->display_options['filters']['date_filter']['id'] = 'date_filter';
  $handler->display->display_options['filters']['date_filter']['table'] = 'node';
  $handler->display->display_options['filters']['date_filter']['field'] = 'date_filter';
  $handler->display->display_options['filters']['date_filter']['operator'] = '>=';
  $handler->display->display_options['filters']['date_filter']['default_date'] = 'now';
  $handler->display->display_options['filters']['date_filter']['date_fields'] = array(
    'field_data_field_ding_event_date.field_ding_event_date_value' => 'field_data_field_ding_event_date.field_ding_event_date_value',
    'field_data_field_ding_event_date.field_ding_event_date_value2' => 'field_data_field_ding_event_date.field_ding_event_date_value2',
  );
  /* Filter criterion: Content translation: Language */
  $handler->display->display_options['filters']['language']['id'] = 'language';
  $handler->display->display_options['filters']['language']['table'] = 'node';
  $handler->display->display_options['filters']['language']['field'] = 'language';
  $handler->display->display_options['filters']['language']['value'] = array(
    '***CURRENT_LANGUAGE***' => '***CURRENT_LANGUAGE***',
    'und' => 'und',
  );

  /* Display: Default event list */
  $handler = $view->new_display('panel_pane', 'Default event list', 'ding_event_default_list');

  /* Display: Simple event list */
  $handler = $view->new_display('panel_pane', 'Simple event list', 'ding_event_simple_list');
  $handler->display->display_options['defaults']['pager'] = FALSE;
  $handler->display->display_options['pager']['type'] = 'some';
  $handler->display->display_options['pager']['options']['items_per_page'] = '5';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['defaults']['style_plugin'] = FALSE;
  $handler->display->display_options['style_plugin'] = 'list';
  $handler->display->display_options['style_options']['class'] = 'item-list';
  $handler->display->display_options['style_options']['wrapper_class'] = '';
  $handler->display->display_options['defaults']['style_options'] = FALSE;
  $handler->display->display_options['defaults']['row_plugin'] = FALSE;
  $handler->display->display_options['row_plugin'] = 'fields';
  $handler->display->display_options['row_options']['hide_empty'] = 1;
  $handler->display->display_options['row_options']['default_field_elements'] = 0;
  $handler->display->display_options['defaults']['row_options'] = FALSE;
  $handler->display->display_options['defaults']['relationships'] = FALSE;
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Field: Date */
  $handler->display->display_options['fields']['field_ding_event_date']['id'] = 'field_ding_event_date';
  $handler->display->display_options['fields']['field_ding_event_date']['table'] = 'field_data_field_ding_event_date';
  $handler->display->display_options['fields']['field_ding_event_date']['field'] = 'field_ding_event_date';
  $handler->display->display_options['fields']['field_ding_event_date']['ui_name'] = 'Date';
  $handler->display->display_options['fields']['field_ding_event_date']['label'] = '';
  $handler->display->display_options['fields']['field_ding_event_date']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['field_ding_event_date']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['field_ding_event_date']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['field_ding_event_date']['alter']['external'] = 0;
  $handler->display->display_options['fields']['field_ding_event_date']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['field_ding_event_date']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['field_ding_event_date']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['field_ding_event_date']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['field_ding_event_date']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['field_ding_event_date']['alter']['more_link'] = 0;
  $handler->display->display_options['fields']['field_ding_event_date']['alter']['strip_tags'] = 1;
  $handler->display->display_options['fields']['field_ding_event_date']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['field_ding_event_date']['alter']['html'] = 0;
  $handler->display->display_options['fields']['field_ding_event_date']['element_type'] = 'span';
  $handler->display->display_options['fields']['field_ding_event_date']['element_class'] = 'date';
  $handler->display->display_options['fields']['field_ding_event_date']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_ding_event_date']['element_wrapper_type'] = '0';
  $handler->display->display_options['fields']['field_ding_event_date']['element_default_classes'] = 0;
  $handler->display->display_options['fields']['field_ding_event_date']['hide_empty'] = 0;
  $handler->display->display_options['fields']['field_ding_event_date']['empty_zero'] = 0;
  $handler->display->display_options['fields']['field_ding_event_date']['hide_alter_empty'] = 1;
  $handler->display->display_options['fields']['field_ding_event_date']['settings'] = array(
    'format_type' => 'date_only',
    'fromto' => 'value',
    'multiple_number' => '',
    'multiple_from' => '',
    'multiple_to' => '',
  );
  $handler->display->display_options['fields']['field_ding_event_date']['field_api_classes'] = 0;
  /* Field: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['ui_name'] = 'Title';
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
  $handler->display->display_options['fields']['title']['alter']['more_link'] = 0;
  $handler->display->display_options['fields']['title']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['title']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['title']['alter']['html'] = 0;
  $handler->display->display_options['fields']['title']['element_type'] = 'h3';
  $handler->display->display_options['fields']['title']['element_class'] = 'heading';
  $handler->display->display_options['fields']['title']['element_label_type'] = '0';
  $handler->display->display_options['fields']['title']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['title']['element_wrapper_type'] = '0';
  $handler->display->display_options['fields']['title']['element_default_classes'] = 0;
  $handler->display->display_options['fields']['title']['hide_empty'] = 0;
  $handler->display->display_options['fields']['title']['empty_zero'] = 0;
  $handler->display->display_options['fields']['title']['hide_alter_empty'] = 0;
  $handler->display->display_options['fields']['title']['link_to_node'] = 1;
  $handler->display->display_options['pane_category']['name'] = 'Ding events';
  $handler->display->display_options['pane_category']['weight'] = '0';
  $handler->display->display_options['allow']['use_pager'] = 0;
  $handler->display->display_options['allow']['items_per_page'] = 0;
  $handler->display->display_options['allow']['offset'] = 0;
  $handler->display->display_options['allow']['link_to_view'] = 0;
  $handler->display->display_options['allow']['more_link'] = 0;
  $handler->display->display_options['allow']['path_override'] = 0;
  $handler->display->display_options['allow']['title_override'] = 'title_override';
  $handler->display->display_options['allow']['exposed_form'] = 0;
  $handler->display->display_options['allow']['fields_override'] = 0;
  $handler->display->display_options['argument_input'] = array(
    'ding_library_nid_1' => array(
      'type' => 'context',
      'context' => 'entity:node.nid',
      'context_optional' => 1,
      'panel' => '0',
      'fixed' => '',
      'label' => 'Content: Library (field_ding_event_library:nid)',
    ),
    'tid' => array(
      'type' => 'context',
      'context' => 'entity:taxonomy_term.tid',
      'context_optional' => 1,
      'panel' => '0',
      'fixed' => '',
      'label' => 'Content: Has taxonomy term ID',
    ),
  );

  /* Display: RSS event list */
  $handler = $view->new_display('feed', 'RSS event list', 'ding_event_rss_event_list');
  $handler->display->display_options['pager']['type'] = 'some';
  $handler->display->display_options['pager']['options']['items_per_page'] = '20';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['style_plugin'] = 'rss';
  $handler->display->display_options['row_plugin'] = 'node_rss';
  $handler->display->display_options['path'] = 'event/feed';
  $handler->display->display_options['displays'] = array(
    'ctools_context_master' => 'ctools_context_master',
    'ctools_context_teaser_list' => 'ctools_context_teaser_list',
    'panel_pane_1' => 'panel_pane_1',
    'default' => 0,
    'ctools_context_library_teaser' => 0,
    'ctools_context_library_master' => 0,
  );
  $handler->display->display_options['sitename_title'] = 1;

  /* Display: RSS library event list */
  $handler = $view->new_display('feed', 'RSS library event list', 'ding_event_rss_library_event_list');
  $handler->display->display_options['pager']['type'] = 'some';
  $handler->display->display_options['pager']['options']['items_per_page'] = '20';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['style_plugin'] = 'rss';
  $handler->display->display_options['row_plugin'] = 'node_rss';
  $handler->display->display_options['defaults']['arguments'] = FALSE;
  /* Contextual filter: Content: Library (field_ding_event_library:nid) */
  $handler->display->display_options['arguments']['ding_library_nid_1']['id'] = 'ding_library_nid_1';
  $handler->display->display_options['arguments']['ding_library_nid_1']['table'] = 'field_data_field_ding_event_library';
  $handler->display->display_options['arguments']['ding_library_nid_1']['field'] = 'ding_library_nid';
  $handler->display->display_options['arguments']['ding_library_nid_1']['default_action'] = 'not found';
  $handler->display->display_options['arguments']['ding_library_nid_1']['default_argument_type'] = 'fixed';
  $handler->display->display_options['arguments']['ding_library_nid_1']['default_argument_skip_url'] = 0;
  $handler->display->display_options['arguments']['ding_library_nid_1']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['ding_library_nid_1']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['ding_library_nid_1']['summary_options']['items_per_page'] = '25';
  $handler->display->display_options['arguments']['ding_library_nid_1']['break_phrase'] = 0;
  $handler->display->display_options['arguments']['ding_library_nid_1']['not'] = 0;
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
    t('more..'),
    t('Apply'),
    t('Gendan'),
    t('Sort by'),
    t('Asc'),
    t('Desc'),
    t('<span class="label label-info">[field_ding_event_category]</span> <span class="date">[field_ding_event_date]</span> <span class="location">[field_ding_event_library]</span><span class="location">[field_ding_event_location]</span><span class="price">[field_ding_event_price]</span>'),
    t('Read more'),
    t('All'),
    t('Default event list'),
    t('more'),
    t('View panes'),
    t('Simple event list'),
    t('Ding events'),
    t('RSS event list'),
    t('RSS library event list'),
  );
  $export['ding_event'] = $view;

  return $export;
}
