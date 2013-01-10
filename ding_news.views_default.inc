<?php
/**
 * @file
 * ding_news.views_default.inc
 */

/**
 * Implements hook_views_default_views().
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
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['use_more'] = TRUE;
  $handler->display->display_options['use_more_text'] = 'Read more';
  $handler->display->display_options['link_display'] = 'custom_url';
  $handler->display->display_options['link_url'] = 'news-category/all';
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
  $handler->display->display_options['style_options']['row_class'] = 'list-item';
  $handler->display->display_options['row_plugin'] = 'fields';
  $handler->display->display_options['row_options']['hide_empty'] = 0;
  $handler->display->display_options['row_options']['default_field_elements'] = 0;
  /* Relationship: Content: Author */
  $handler->display->display_options['relationships']['uid']['id'] = 'uid';
  $handler->display->display_options['relationships']['uid']['table'] = 'node';
  $handler->display->display_options['relationships']['uid']['field'] = 'uid';
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
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['title']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['title']['alter']['more_link'] = 0;
  $handler->display->display_options['fields']['title']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['title']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['title']['alter']['html'] = 0;
  $handler->display->display_options['fields']['title']['element_type'] = 'h3';
  $handler->display->display_options['fields']['title']['element_class'] = 'heading';
  $handler->display->display_options['fields']['title']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['title']['element_default_classes'] = 0;
  $handler->display->display_options['fields']['title']['hide_empty'] = 0;
  $handler->display->display_options['fields']['title']['empty_zero'] = 0;
  $handler->display->display_options['fields']['title']['hide_alter_empty'] = 1;
  $handler->display->display_options['fields']['title']['link_to_node'] = 1;
  /* Field: Category (excluded) */
  $handler->display->display_options['fields']['field_ding_news_category']['id'] = 'field_ding_news_category';
  $handler->display->display_options['fields']['field_ding_news_category']['table'] = 'field_data_field_ding_news_category';
  $handler->display->display_options['fields']['field_ding_news_category']['field'] = 'field_ding_news_category';
  $handler->display->display_options['fields']['field_ding_news_category']['ui_name'] = 'Category (excluded)';
  $handler->display->display_options['fields']['field_ding_news_category']['label'] = '';
  $handler->display->display_options['fields']['field_ding_news_category']['exclude'] = TRUE;
  $handler->display->display_options['fields']['field_ding_news_category']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['field_ding_news_category']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['field_ding_news_category']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['field_ding_news_category']['alter']['external'] = 0;
  $handler->display->display_options['fields']['field_ding_news_category']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['field_ding_news_category']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['field_ding_news_category']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['field_ding_news_category']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['field_ding_news_category']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['field_ding_news_category']['alter']['more_link'] = 0;
  $handler->display->display_options['fields']['field_ding_news_category']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['field_ding_news_category']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['field_ding_news_category']['alter']['html'] = 0;
  $handler->display->display_options['fields']['field_ding_news_category']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_ding_news_category']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['field_ding_news_category']['hide_empty'] = 0;
  $handler->display->display_options['fields']['field_ding_news_category']['empty_zero'] = 0;
  $handler->display->display_options['fields']['field_ding_news_category']['hide_alter_empty'] = 1;
  $handler->display->display_options['fields']['field_ding_news_category']['field_api_classes'] = 0;
  /* Field: Date (excluded) */
  $handler->display->display_options['fields']['created']['id'] = 'created';
  $handler->display->display_options['fields']['created']['table'] = 'node';
  $handler->display->display_options['fields']['created']['field'] = 'created';
  $handler->display->display_options['fields']['created']['ui_name'] = 'Date (excluded)';
  $handler->display->display_options['fields']['created']['label'] = '';
  $handler->display->display_options['fields']['created']['exclude'] = TRUE;
  $handler->display->display_options['fields']['created']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['created']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['created']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['created']['alter']['external'] = 0;
  $handler->display->display_options['fields']['created']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['created']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['created']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['created']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['created']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['created']['alter']['more_link'] = 0;
  $handler->display->display_options['fields']['created']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['created']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['created']['alter']['html'] = 0;
  $handler->display->display_options['fields']['created']['element_type'] = 'span';
  $handler->display->display_options['fields']['created']['element_class'] = 'date';
  $handler->display->display_options['fields']['created']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['created']['element_default_classes'] = 0;
  $handler->display->display_options['fields']['created']['hide_empty'] = 0;
  $handler->display->display_options['fields']['created']['empty_zero'] = 0;
  $handler->display->display_options['fields']['created']['hide_alter_empty'] = 1;
  $handler->display->display_options['fields']['created']['date_format'] = 'long_date_only';
  /* Field: Author (excluded) */
  $handler->display->display_options['fields']['name']['id'] = 'name';
  $handler->display->display_options['fields']['name']['table'] = 'users';
  $handler->display->display_options['fields']['name']['field'] = 'name';
  $handler->display->display_options['fields']['name']['relationship'] = 'uid';
  $handler->display->display_options['fields']['name']['ui_name'] = 'Author (excluded)';
  $handler->display->display_options['fields']['name']['label'] = '';
  $handler->display->display_options['fields']['name']['exclude'] = TRUE;
  $handler->display->display_options['fields']['name']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['name']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['name']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['name']['alter']['external'] = 0;
  $handler->display->display_options['fields']['name']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['name']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['name']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['name']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['name']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['name']['alter']['more_link'] = 0;
  $handler->display->display_options['fields']['name']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['name']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['name']['alter']['html'] = 0;
  $handler->display->display_options['fields']['name']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['name']['element_default_classes'] = 0;
  $handler->display->display_options['fields']['name']['hide_empty'] = 0;
  $handler->display->display_options['fields']['name']['empty_zero'] = 0;
  $handler->display->display_options['fields']['name']['hide_alter_empty'] = 1;
  $handler->display->display_options['fields']['name']['link_to_user'] = 1;
  $handler->display->display_options['fields']['name']['overwrite_anonymous'] = 0;
  $handler->display->display_options['fields']['name']['format_username'] = 1;
  /* Field: Category, date and author */
  $handler->display->display_options['fields']['nothing']['id'] = 'nothing';
  $handler->display->display_options['fields']['nothing']['table'] = 'views';
  $handler->display->display_options['fields']['nothing']['field'] = 'nothing';
  $handler->display->display_options['fields']['nothing']['ui_name'] = 'Category, date and author';
  $handler->display->display_options['fields']['nothing']['label'] = '';
  $handler->display->display_options['fields']['nothing']['alter']['text'] = '<span class="label label-info">[field_ding_news_category]</span> <span class="date">[created]</span> <span class="author">by [name]</span>';
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
  /* Field: Image (list image) */
  $handler->display->display_options['fields']['field_ding_news_list_image']['id'] = 'field_ding_news_list_image';
  $handler->display->display_options['fields']['field_ding_news_list_image']['table'] = 'field_data_field_ding_news_list_image';
  $handler->display->display_options['fields']['field_ding_news_list_image']['field'] = 'field_ding_news_list_image';
  $handler->display->display_options['fields']['field_ding_news_list_image']['ui_name'] = 'Image (list image)';
  $handler->display->display_options['fields']['field_ding_news_list_image']['label'] = '';
  $handler->display->display_options['fields']['field_ding_news_list_image']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['field_ding_news_list_image']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['field_ding_news_list_image']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['field_ding_news_list_image']['alter']['external'] = 0;
  $handler->display->display_options['fields']['field_ding_news_list_image']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['field_ding_news_list_image']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['field_ding_news_list_image']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['field_ding_news_list_image']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['field_ding_news_list_image']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['field_ding_news_list_image']['alter']['more_link'] = 0;
  $handler->display->display_options['fields']['field_ding_news_list_image']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['field_ding_news_list_image']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['field_ding_news_list_image']['alter']['html'] = 0;
  $handler->display->display_options['fields']['field_ding_news_list_image']['element_type'] = 'div';
  $handler->display->display_options['fields']['field_ding_news_list_image']['element_class'] = 'image-container';
  $handler->display->display_options['fields']['field_ding_news_list_image']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_ding_news_list_image']['element_default_classes'] = 0;
  $handler->display->display_options['fields']['field_ding_news_list_image']['hide_empty'] = 0;
  $handler->display->display_options['fields']['field_ding_news_list_image']['empty_zero'] = 0;
  $handler->display->display_options['fields']['field_ding_news_list_image']['hide_alter_empty'] = 1;
  $handler->display->display_options['fields']['field_ding_news_list_image']['click_sort_column'] = 'fid';
  $handler->display->display_options['fields']['field_ding_news_list_image']['settings'] = array(
    'image_style' => 'ding_large',
    'image_link' => '',
  );
  $handler->display->display_options['fields']['field_ding_news_list_image']['field_api_classes'] = 0;
  /* Field: Lead (content) */
  $handler->display->display_options['fields']['field_ding_news_lead']['id'] = 'field_ding_news_lead';
  $handler->display->display_options['fields']['field_ding_news_lead']['table'] = 'field_data_field_ding_news_lead';
  $handler->display->display_options['fields']['field_ding_news_lead']['field'] = 'field_ding_news_lead';
  $handler->display->display_options['fields']['field_ding_news_lead']['ui_name'] = 'Lead (content)';
  $handler->display->display_options['fields']['field_ding_news_lead']['label'] = '';
  $handler->display->display_options['fields']['field_ding_news_lead']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['field_ding_news_lead']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['field_ding_news_lead']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['field_ding_news_lead']['alter']['external'] = 0;
  $handler->display->display_options['fields']['field_ding_news_lead']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['field_ding_news_lead']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['field_ding_news_lead']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['field_ding_news_lead']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['field_ding_news_lead']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['field_ding_news_lead']['alter']['more_link'] = 0;
  $handler->display->display_options['fields']['field_ding_news_lead']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['field_ding_news_lead']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['field_ding_news_lead']['alter']['html'] = 0;
  $handler->display->display_options['fields']['field_ding_news_lead']['element_type'] = 'p';
  $handler->display->display_options['fields']['field_ding_news_lead']['element_class'] = 'content';
  $handler->display->display_options['fields']['field_ding_news_lead']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_ding_news_lead']['element_default_classes'] = 0;
  $handler->display->display_options['fields']['field_ding_news_lead']['hide_empty'] = 0;
  $handler->display->display_options['fields']['field_ding_news_lead']['empty_zero'] = 0;
  $handler->display->display_options['fields']['field_ding_news_lead']['hide_alter_empty'] = 1;
  $handler->display->display_options['fields']['field_ding_news_lead']['field_api_classes'] = 0;
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
  $handler->display->display_options['fields']['view_node']['element_default_classes'] = 0;
  $handler->display->display_options['fields']['view_node']['hide_empty'] = 0;
  $handler->display->display_options['fields']['view_node']['empty_zero'] = 0;
  $handler->display->display_options['fields']['view_node']['hide_alter_empty'] = 1;
  $handler->display->display_options['fields']['view_node']['text'] = 'Read more';
  /* Sort criterion: Content: Post date */
  $handler->display->display_options['sorts']['created']['id'] = 'created';
  $handler->display->display_options['sorts']['created']['table'] = 'node';
  $handler->display->display_options['sorts']['created']['field'] = 'created';
  $handler->display->display_options['sorts']['created']['order'] = 'DESC';
  /* Contextual filter: Content: Library (field_ding_news_library:nid) */
  $handler->display->display_options['arguments']['ding_library_nid_1']['id'] = 'ding_library_nid_1';
  $handler->display->display_options['arguments']['ding_library_nid_1']['table'] = 'field_data_field_ding_news_library';
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
    'ding_news' => 'ding_news',
  );
  /* Filter criterion: Content translation: Language */
  $handler->display->display_options['filters']['language']['id'] = 'language';
  $handler->display->display_options['filters']['language']['table'] = 'node';
  $handler->display->display_options['filters']['language']['field'] = 'language';
  $handler->display->display_options['filters']['language']['value'] = array(
    '***CURRENT_LANGUAGE***' => '***CURRENT_LANGUAGE***',
    'und' => 'und',
  );

  /* Display: Default news list */
  $handler = $view->new_display('panel_pane', 'Default news list', 'ding_news_default_list');
  $handler->display->display_options['display_description'] = 'This is the default news list used for displaying news';
  $handler->display->display_options['defaults']['link_display'] = FALSE;
  $handler->display->display_options['link_display'] = 'custom_url';
  $handler->display->display_options['link_url'] = 'news-category/all';

  /* Display: Default news list (promoted) */
  $handler = $view->new_display('panel_pane', 'Default news list (promoted)', 'panel_pane_1');
  $handler->display->display_options['display_description'] = 'This is the default news list used for displaying news with promoted content ';
  $handler->display->display_options['defaults']['pager'] = FALSE;
  $handler->display->display_options['pager']['type'] = 'some';
  $handler->display->display_options['pager']['options']['items_per_page'] = '4';
  $handler->display->display_options['pager']['options']['offset'] = '1';

  /* Display: Default news list (promoted attachment) */
  $handler = $view->new_display('attachment', 'Default news list (promoted attachment)', 'ding_news_default_list_highlight_attach');
  $handler->display->display_options['defaults']['css_class'] = FALSE;
  $handler->display->display_options['css_class'] = 'promoted';
  $handler->display->display_options['display_description'] = 'Promoted news that are used to attach on news lists';
  $handler->display->display_options['defaults']['use_more'] = FALSE;
  $handler->display->display_options['pager']['type'] = 'some';
  $handler->display->display_options['pager']['options']['items_per_page'] = '1';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['defaults']['style_plugin'] = FALSE;
  $handler->display->display_options['style_plugin'] = 'default';
  $handler->display->display_options['style_options']['row_class'] = 'list-item';
  $handler->display->display_options['defaults']['style_options'] = FALSE;
  $handler->display->display_options['defaults']['row_plugin'] = FALSE;
  $handler->display->display_options['row_plugin'] = 'fields';
  $handler->display->display_options['row_options']['hide_empty'] = 0;
  $handler->display->display_options['row_options']['default_field_elements'] = 0;
  $handler->display->display_options['defaults']['row_options'] = FALSE;
  $handler->display->display_options['defaults']['sorts'] = FALSE;
  /* Sort criterion: Content: Sticky */
  $handler->display->display_options['sorts']['sticky']['id'] = 'sticky';
  $handler->display->display_options['sorts']['sticky']['table'] = 'node';
  $handler->display->display_options['sorts']['sticky']['field'] = 'sticky';
  $handler->display->display_options['sorts']['sticky']['order'] = 'DESC';
  /* Sort criterion: Content: Post date */
  $handler->display->display_options['sorts']['created']['id'] = 'created';
  $handler->display->display_options['sorts']['created']['table'] = 'node';
  $handler->display->display_options['sorts']['created']['field'] = 'created';
  $handler->display->display_options['sorts']['created']['order'] = 'DESC';
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
  /* Filter criterion: Content translation: Language */
  $handler->display->display_options['filters']['language']['id'] = 'language';
  $handler->display->display_options['filters']['language']['table'] = 'node';
  $handler->display->display_options['filters']['language']['field'] = 'language';
  $handler->display->display_options['filters']['language']['value'] = array(
    '***CURRENT_LANGUAGE***' => '***CURRENT_LANGUAGE***',
    'und' => 'und',
  );
  $handler->display->display_options['displays'] = array(
    'panel_pane_1' => 'panel_pane_1',
    'panel_pane_4' => 'panel_pane_4',
    'default' => 0,
    'ding_news_default_list' => 0,
    'ding_news_full_list_panel_pane' => 0,
    'ding_news_library_teaser_list' => 0,
    'panel_pane_2' => 0,
    'panel_pane_3' => 0,
  );

  /* Display: Full list */
  $handler = $view->new_display('panel_pane', 'Full list', 'ding_news_full_list_panel_pane');
  $handler->display->display_options['defaults']['use_more'] = FALSE;
  $handler->display->display_options['defaults']['pager'] = FALSE;
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = '10';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['pager']['options']['id'] = '0';
  $handler->display->display_options['pager']['options']['expose']['items_per_page_options_all'] = 0;
  $handler->display->display_options['pane_category']['name'] = 'News panes';
  $handler->display->display_options['pane_category']['weight'] = '0';
  $handler->display->display_options['argument_input'] = array(
    'ding_library_nid_1' => array(
      'type' => 'context',
      'context' => 'entity:node.nid',
      'context_optional' => 1,
      'panel' => '0',
      'fixed' => '',
      'label' => 'Content: Library (field_ding_news_library:nid)',
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

  /* Display: Library teaser highlight */
  $handler = $view->new_display('attachment', 'Library teaser highlight', 'ding_news_library_teaser_highlight');
  $handler->display->display_options['defaults']['css_class'] = FALSE;
  $handler->display->display_options['css_class'] = 'ding-news-highlight';
  $handler->display->display_options['pager']['type'] = 'some';
  $handler->display->display_options['pager']['options']['items_per_page'] = '1';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['defaults']['style_plugin'] = FALSE;
  $handler->display->display_options['style_plugin'] = 'default';
  $handler->display->display_options['defaults']['style_options'] = FALSE;
  $handler->display->display_options['defaults']['row_plugin'] = FALSE;
  $handler->display->display_options['row_plugin'] = 'node';
  $handler->display->display_options['row_options']['view_mode'] = 'teaser_highlight';
  $handler->display->display_options['row_options']['links'] = 0;
  $handler->display->display_options['row_options']['comments'] = 0;
  $handler->display->display_options['defaults']['row_options'] = FALSE;
  $handler->display->display_options['defaults']['sorts'] = FALSE;
  /* Sort criterion: Content: Sticky */
  $handler->display->display_options['sorts']['sticky']['id'] = 'sticky';
  $handler->display->display_options['sorts']['sticky']['table'] = 'node';
  $handler->display->display_options['sorts']['sticky']['field'] = 'sticky';
  $handler->display->display_options['sorts']['sticky']['order'] = 'DESC';
  /* Sort criterion: Content: Post date */
  $handler->display->display_options['sorts']['created']['id'] = 'created';
  $handler->display->display_options['sorts']['created']['table'] = 'node';
  $handler->display->display_options['sorts']['created']['field'] = 'created';
  $handler->display->display_options['sorts']['created']['order'] = 'DESC';
  $handler->display->display_options['defaults']['arguments'] = FALSE;
  /* Contextual filter: Content: Library (field_ding_news_library:nid) */
  $handler->display->display_options['arguments']['ding_library_nid_1']['id'] = 'ding_library_nid_1';
  $handler->display->display_options['arguments']['ding_library_nid_1']['table'] = 'field_data_field_ding_news_library';
  $handler->display->display_options['arguments']['ding_library_nid_1']['field'] = 'ding_library_nid';
  $handler->display->display_options['arguments']['ding_library_nid_1']['default_argument_type'] = 'fixed';
  $handler->display->display_options['arguments']['ding_library_nid_1']['default_argument_skip_url'] = 0;
  $handler->display->display_options['arguments']['ding_library_nid_1']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['ding_library_nid_1']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['ding_library_nid_1']['summary_options']['items_per_page'] = '25';
  $handler->display->display_options['arguments']['ding_library_nid_1']['break_phrase'] = 0;
  $handler->display->display_options['arguments']['ding_library_nid_1']['not'] = 0;
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
  /* Filter criterion: Content translation: Language */
  $handler->display->display_options['filters']['language']['id'] = 'language';
  $handler->display->display_options['filters']['language']['table'] = 'node';
  $handler->display->display_options['filters']['language']['field'] = 'language';
  $handler->display->display_options['filters']['language']['value'] = array(
    '***CURRENT_LANGUAGE***' => '***CURRENT_LANGUAGE***',
    'und' => 'und',
  );
  $handler->display->display_options['displays'] = array(
    'ctools_context_library_list' => 'ctools_context_library_list',
    'default' => 0,
    'ctools_context_master' => 0,
    'ctools_context_teaser_list' => 0,
    'ctools_context_2' => 0,
  );
  $handler->display->display_options['inherit_arguments'] = 1;

  /* Display: Feed */
  $handler = $view->new_display('feed', 'Feed', 'ding_news_feed');
  $handler->display->display_options['pager']['type'] = 'some';
  $handler->display->display_options['pager']['options']['items_per_page'] = '20';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['style_plugin'] = 'rss';
  $handler->display->display_options['row_plugin'] = 'node_rss';
  $handler->display->display_options['path'] = 'news/feed';
  $handler->display->display_options['displays'] = array(
    'default' => 'default',
    'ctools_context_teaser_list' => 'ctools_context_teaser_list',
    'panel_pane_1' => 'panel_pane_1',
    'ctools_context_library_list' => 0,
  );
  $handler->display->display_options['sitename_title'] = 1;

  /* Display: Library teaser list */
  $handler = $view->new_display('ctools_context', 'Library teaser list', 'ding_news_library_teaser_list');
  $handler->display->display_options['defaults']['pager'] = FALSE;
  $handler->display->display_options['pager']['type'] = 'some';
  $handler->display->display_options['pager']['options']['items_per_page'] = '4';
  $handler->display->display_options['pager']['options']['offset'] = '1';
  $handler->display->display_options['style_plugin'] = 'ctools_context';
  $handler->display->display_options['row_plugin'] = 'fields';
  $handler->display->display_options['row_options']['hide_empty'] = 0;
  $handler->display->display_options['row_options']['default_field_elements'] = 0;
  $handler->display->display_options['defaults']['empty'] = FALSE;
  /* No results behavior: Global: Text area */
  $handler->display->display_options['empty']['area']['id'] = 'area';
  $handler->display->display_options['empty']['area']['table'] = 'views';
  $handler->display->display_options['empty']['area']['field'] = 'area';
  $handler->display->display_options['empty']['area']['label'] = 'Dummy text if no result';
  $handler->display->display_options['empty']['area']['empty'] = FALSE;
  $handler->display->display_options['empty']['area']['format'] = 'ding_wysiwyg';
  $handler->display->display_options['empty']['area']['tokenize'] = 0;
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Field: Content: Library */
  $handler->display->display_options['fields']['field_ding_news_library']['id'] = 'field_ding_news_library';
  $handler->display->display_options['fields']['field_ding_news_library']['table'] = 'field_data_field_ding_news_library';
  $handler->display->display_options['fields']['field_ding_news_library']['field'] = 'field_ding_news_library';
  $handler->display->display_options['fields']['field_ding_news_library']['label'] = '';
  $handler->display->display_options['fields']['field_ding_news_library']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['field_ding_news_library']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['field_ding_news_library']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['field_ding_news_library']['alter']['external'] = 0;
  $handler->display->display_options['fields']['field_ding_news_library']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['field_ding_news_library']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['field_ding_news_library']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['field_ding_news_library']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['field_ding_news_library']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['field_ding_news_library']['alter']['more_link'] = 0;
  $handler->display->display_options['fields']['field_ding_news_library']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['field_ding_news_library']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['field_ding_news_library']['alter']['html'] = 0;
  $handler->display->display_options['fields']['field_ding_news_library']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_ding_news_library']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['field_ding_news_library']['hide_empty'] = 0;
  $handler->display->display_options['fields']['field_ding_news_library']['empty_zero'] = 0;
  $handler->display->display_options['fields']['field_ding_news_library']['hide_alter_empty'] = 1;
  $handler->display->display_options['fields']['field_ding_news_library']['click_sort_column'] = 'gid';
  $handler->display->display_options['fields']['field_ding_news_library']['field_api_classes'] = 0;
  /* Field: Content: Post date */
  $handler->display->display_options['fields']['created']['id'] = 'created';
  $handler->display->display_options['fields']['created']['table'] = 'node';
  $handler->display->display_options['fields']['created']['field'] = 'created';
  $handler->display->display_options['fields']['created']['label'] = '';
  $handler->display->display_options['fields']['created']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['created']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['created']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['created']['alter']['external'] = 0;
  $handler->display->display_options['fields']['created']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['created']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['created']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['created']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['created']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['created']['alter']['more_link'] = 0;
  $handler->display->display_options['fields']['created']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['created']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['created']['alter']['html'] = 0;
  $handler->display->display_options['fields']['created']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['created']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['created']['hide_empty'] = 0;
  $handler->display->display_options['fields']['created']['empty_zero'] = 0;
  $handler->display->display_options['fields']['created']['hide_alter_empty'] = 1;
  $handler->display->display_options['fields']['created']['date_format'] = 'medium';
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
  $handler->display->display_options['defaults']['sorts'] = FALSE;
  /* Sort criterion: Content: Sticky */
  $handler->display->display_options['sorts']['sticky']['id'] = 'sticky';
  $handler->display->display_options['sorts']['sticky']['table'] = 'node';
  $handler->display->display_options['sorts']['sticky']['field'] = 'sticky';
  $handler->display->display_options['sorts']['sticky']['order'] = 'DESC';
  /* Sort criterion: Content: Post date */
  $handler->display->display_options['sorts']['created']['id'] = 'created';
  $handler->display->display_options['sorts']['created']['table'] = 'node';
  $handler->display->display_options['sorts']['created']['field'] = 'created';
  $handler->display->display_options['sorts']['created']['order'] = 'DESC';
  $handler->display->display_options['defaults']['arguments'] = FALSE;
  /* Contextual filter: Content: Library (field_ding_news_library:nid) */
  $handler->display->display_options['arguments']['ding_library_nid_1']['id'] = 'ding_library_nid_1';
  $handler->display->display_options['arguments']['ding_library_nid_1']['table'] = 'field_data_field_ding_news_library';
  $handler->display->display_options['arguments']['ding_library_nid_1']['field'] = 'ding_library_nid';
  $handler->display->display_options['arguments']['ding_library_nid_1']['default_action'] = 'not found';
  $handler->display->display_options['arguments']['ding_library_nid_1']['default_argument_type'] = 'fixed';
  $handler->display->display_options['arguments']['ding_library_nid_1']['default_argument_skip_url'] = 0;
  $handler->display->display_options['arguments']['ding_library_nid_1']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['ding_library_nid_1']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['ding_library_nid_1']['summary_options']['items_per_page'] = '25';
  $handler->display->display_options['arguments']['ding_library_nid_1']['break_phrase'] = 0;
  $handler->display->display_options['arguments']['ding_library_nid_1']['not'] = 0;
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
  /* Filter criterion: Content translation: Language */
  $handler->display->display_options['filters']['language']['id'] = 'language';
  $handler->display->display_options['filters']['language']['table'] = 'node';
  $handler->display->display_options['filters']['language']['field'] = 'language';
  $handler->display->display_options['filters']['language']['value'] = array(
    '***CURRENT_LANGUAGE***' => '***CURRENT_LANGUAGE***',
    'und' => 'und',
  );
  $handler->display->display_options['inherit_panels_path'] = '1';
  $handler->display->display_options['argument_input'] = array(
    'ding_library_nid_1' => array(
      'type' => 'context',
      'context' => 'entity:node.nid',
      'context_optional' => 1,
    ),
  );

  /* Display: Library Feed */
  $handler = $view->new_display('feed', 'Library Feed', 'ding_news_library_feed');
  $handler->display->display_options['pager']['type'] = 'some';
  $handler->display->display_options['pager']['options']['items_per_page'] = '20';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['style_plugin'] = 'rss';
  $handler->display->display_options['row_plugin'] = 'node_rss';
  $handler->display->display_options['defaults']['arguments'] = FALSE;
  /* Contextual filter: Content: Library (field_ding_news_library:nid) */
  $handler->display->display_options['arguments']['ding_library_nid_1']['id'] = 'ding_library_nid_1';
  $handler->display->display_options['arguments']['ding_library_nid_1']['table'] = 'field_data_field_ding_news_library';
  $handler->display->display_options['arguments']['ding_library_nid_1']['field'] = 'ding_library_nid';
  $handler->display->display_options['arguments']['ding_library_nid_1']['default_action'] = 'not found';
  $handler->display->display_options['arguments']['ding_library_nid_1']['default_argument_type'] = 'fixed';
  $handler->display->display_options['arguments']['ding_library_nid_1']['default_argument_skip_url'] = 0;
  $handler->display->display_options['arguments']['ding_library_nid_1']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['ding_library_nid_1']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['ding_library_nid_1']['summary_options']['items_per_page'] = '25';
  $handler->display->display_options['arguments']['ding_library_nid_1']['break_phrase'] = 0;
  $handler->display->display_options['arguments']['ding_library_nid_1']['not'] = 0;
  $handler->display->display_options['path'] = 'node/%/news/feed';
  $handler->display->display_options['displays'] = array(
    'ctools_context_library_list' => 'ctools_context_library_list',
    'ctools_context_2' => 'ctools_context_2',
    'default' => 0,
    'ctools_context_master' => 0,
    'ctools_context_teaser_list' => 0,
  );
  $handler->display->display_options['sitename_title'] = 1;

  /* Display: Simple news list */
  $handler = $view->new_display('panel_pane', 'Simple news list', 'panel_pane_2');
  $handler->display->display_options['defaults']['css_class'] = FALSE;
  $handler->display->display_options['css_class'] = 'simple';
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Field: Date (excluded) */
  $handler->display->display_options['fields']['created']['id'] = 'created';
  $handler->display->display_options['fields']['created']['table'] = 'node';
  $handler->display->display_options['fields']['created']['field'] = 'created';
  $handler->display->display_options['fields']['created']['ui_name'] = 'Date (excluded)';
  $handler->display->display_options['fields']['created']['label'] = '';
  $handler->display->display_options['fields']['created']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['created']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['created']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['created']['alter']['external'] = 0;
  $handler->display->display_options['fields']['created']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['created']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['created']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['created']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['created']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['created']['alter']['more_link'] = 0;
  $handler->display->display_options['fields']['created']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['created']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['created']['alter']['html'] = 0;
  $handler->display->display_options['fields']['created']['element_type'] = 'span';
  $handler->display->display_options['fields']['created']['element_class'] = 'date';
  $handler->display->display_options['fields']['created']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['created']['element_default_classes'] = 0;
  $handler->display->display_options['fields']['created']['hide_empty'] = 0;
  $handler->display->display_options['fields']['created']['empty_zero'] = 0;
  $handler->display->display_options['fields']['created']['hide_alter_empty'] = 1;
  $handler->display->display_options['fields']['created']['date_format'] = 'custom';
  $handler->display->display_options['fields']['created']['custom_date_format'] = 'j. M';
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
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['title']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['title']['alter']['more_link'] = 0;
  $handler->display->display_options['fields']['title']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['title']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['title']['alter']['html'] = 0;
  $handler->display->display_options['fields']['title']['element_type'] = 'h3';
  $handler->display->display_options['fields']['title']['element_class'] = 'heading';
  $handler->display->display_options['fields']['title']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['title']['element_default_classes'] = 0;
  $handler->display->display_options['fields']['title']['hide_empty'] = 0;
  $handler->display->display_options['fields']['title']['empty_zero'] = 0;
  $handler->display->display_options['fields']['title']['hide_alter_empty'] = 1;
  $handler->display->display_options['fields']['title']['link_to_node'] = 1;

  /* Display: Floated news list */
  $handler = $view->new_display('panel_pane', 'Floated news list', 'panel_pane_3');
  $handler->display->display_options['defaults']['css_class'] = FALSE;
  $handler->display->display_options['css_class'] = 'floated';
  $handler->display->display_options['defaults']['arguments'] = FALSE;
  /* Contextual filter: Indhold: Has taxonomy term ID */
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
  $handler->display->display_options['argument_input'] = array(
    'tid' => array(
      'type' => 'panel',
      'context' => 'entity:user.cancel-url',
      'context_optional' => 0,
      'panel' => '0',
      'fixed' => '',
      'label' => 'Indhold: Has taxonomy term ID',
    ),
  );

  /* Display: Floated news list (highlight) */
  $handler = $view->new_display('panel_pane', 'Floated news list (highlight)', 'panel_pane_4');
  $handler->display->display_options['defaults']['css_class'] = FALSE;
  $handler->display->display_options['css_class'] = 'floated highlighted';
  $handler->display->display_options['defaults']['pager'] = FALSE;
  $handler->display->display_options['pager']['type'] = 'some';
  $handler->display->display_options['pager']['options']['items_per_page'] = '4';
  $handler->display->display_options['pager']['options']['offset'] = '1';
  $handler->display->display_options['defaults']['fields'] = FALSE;
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
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['title']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['title']['alter']['more_link'] = 0;
  $handler->display->display_options['fields']['title']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['title']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['title']['alter']['html'] = 0;
  $handler->display->display_options['fields']['title']['element_type'] = 'h3';
  $handler->display->display_options['fields']['title']['element_class'] = 'heading';
  $handler->display->display_options['fields']['title']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['title']['element_default_classes'] = 0;
  $handler->display->display_options['fields']['title']['hide_empty'] = 0;
  $handler->display->display_options['fields']['title']['empty_zero'] = 0;
  $handler->display->display_options['fields']['title']['hide_alter_empty'] = 1;
  $handler->display->display_options['fields']['title']['link_to_node'] = 1;
  /* Field: Category (excluded) */
  $handler->display->display_options['fields']['field_ding_news_category']['id'] = 'field_ding_news_category';
  $handler->display->display_options['fields']['field_ding_news_category']['table'] = 'field_data_field_ding_news_category';
  $handler->display->display_options['fields']['field_ding_news_category']['field'] = 'field_ding_news_category';
  $handler->display->display_options['fields']['field_ding_news_category']['ui_name'] = 'Category (excluded)';
  $handler->display->display_options['fields']['field_ding_news_category']['label'] = '';
  $handler->display->display_options['fields']['field_ding_news_category']['exclude'] = TRUE;
  $handler->display->display_options['fields']['field_ding_news_category']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['field_ding_news_category']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['field_ding_news_category']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['field_ding_news_category']['alter']['external'] = 0;
  $handler->display->display_options['fields']['field_ding_news_category']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['field_ding_news_category']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['field_ding_news_category']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['field_ding_news_category']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['field_ding_news_category']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['field_ding_news_category']['alter']['more_link'] = 0;
  $handler->display->display_options['fields']['field_ding_news_category']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['field_ding_news_category']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['field_ding_news_category']['alter']['html'] = 0;
  $handler->display->display_options['fields']['field_ding_news_category']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_ding_news_category']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['field_ding_news_category']['hide_empty'] = 0;
  $handler->display->display_options['fields']['field_ding_news_category']['empty_zero'] = 0;
  $handler->display->display_options['fields']['field_ding_news_category']['hide_alter_empty'] = 1;
  $handler->display->display_options['fields']['field_ding_news_category']['field_api_classes'] = 0;
  /* Field: Date (excluded) */
  $handler->display->display_options['fields']['created']['id'] = 'created';
  $handler->display->display_options['fields']['created']['table'] = 'node';
  $handler->display->display_options['fields']['created']['field'] = 'created';
  $handler->display->display_options['fields']['created']['ui_name'] = 'Date (excluded)';
  $handler->display->display_options['fields']['created']['label'] = '';
  $handler->display->display_options['fields']['created']['exclude'] = TRUE;
  $handler->display->display_options['fields']['created']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['created']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['created']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['created']['alter']['external'] = 0;
  $handler->display->display_options['fields']['created']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['created']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['created']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['created']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['created']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['created']['alter']['more_link'] = 0;
  $handler->display->display_options['fields']['created']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['created']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['created']['alter']['html'] = 0;
  $handler->display->display_options['fields']['created']['element_type'] = 'span';
  $handler->display->display_options['fields']['created']['element_class'] = 'date';
  $handler->display->display_options['fields']['created']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['created']['element_default_classes'] = 0;
  $handler->display->display_options['fields']['created']['hide_empty'] = 0;
  $handler->display->display_options['fields']['created']['empty_zero'] = 0;
  $handler->display->display_options['fields']['created']['hide_alter_empty'] = 1;
  $handler->display->display_options['fields']['created']['date_format'] = 'long_date_only';
  /* Field: Author (excluded) */
  $handler->display->display_options['fields']['name']['id'] = 'name';
  $handler->display->display_options['fields']['name']['table'] = 'users';
  $handler->display->display_options['fields']['name']['field'] = 'name';
  $handler->display->display_options['fields']['name']['relationship'] = 'uid';
  $handler->display->display_options['fields']['name']['ui_name'] = 'Author (excluded)';
  $handler->display->display_options['fields']['name']['label'] = '';
  $handler->display->display_options['fields']['name']['exclude'] = TRUE;
  $handler->display->display_options['fields']['name']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['name']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['name']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['name']['alter']['external'] = 0;
  $handler->display->display_options['fields']['name']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['name']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['name']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['name']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['name']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['name']['alter']['more_link'] = 0;
  $handler->display->display_options['fields']['name']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['name']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['name']['alter']['html'] = 0;
  $handler->display->display_options['fields']['name']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['name']['element_default_classes'] = 0;
  $handler->display->display_options['fields']['name']['hide_empty'] = 0;
  $handler->display->display_options['fields']['name']['empty_zero'] = 0;
  $handler->display->display_options['fields']['name']['hide_alter_empty'] = 1;
  $handler->display->display_options['fields']['name']['link_to_user'] = 1;
  $handler->display->display_options['fields']['name']['overwrite_anonymous'] = 0;
  $handler->display->display_options['fields']['name']['format_username'] = 1;
  /* Field: Category, date and author */
  $handler->display->display_options['fields']['nothing']['id'] = 'nothing';
  $handler->display->display_options['fields']['nothing']['table'] = 'views';
  $handler->display->display_options['fields']['nothing']['field'] = 'nothing';
  $handler->display->display_options['fields']['nothing']['ui_name'] = 'Category, date and author';
  $handler->display->display_options['fields']['nothing']['label'] = '';
  $handler->display->display_options['fields']['nothing']['alter']['text'] = '<span class="label label-info">[field_ding_news_category]</span> <span class="date">[created]</span> <span class="author">by [name]</span>';
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
  /* Field: Image (list image) */
  $handler->display->display_options['fields']['field_ding_news_list_image']['id'] = 'field_ding_news_list_image';
  $handler->display->display_options['fields']['field_ding_news_list_image']['table'] = 'field_data_field_ding_news_list_image';
  $handler->display->display_options['fields']['field_ding_news_list_image']['field'] = 'field_ding_news_list_image';
  $handler->display->display_options['fields']['field_ding_news_list_image']['ui_name'] = 'Image (list image)';
  $handler->display->display_options['fields']['field_ding_news_list_image']['label'] = '';
  $handler->display->display_options['fields']['field_ding_news_list_image']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['field_ding_news_list_image']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['field_ding_news_list_image']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['field_ding_news_list_image']['alter']['external'] = 0;
  $handler->display->display_options['fields']['field_ding_news_list_image']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['field_ding_news_list_image']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['field_ding_news_list_image']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['field_ding_news_list_image']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['field_ding_news_list_image']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['field_ding_news_list_image']['alter']['more_link'] = 0;
  $handler->display->display_options['fields']['field_ding_news_list_image']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['field_ding_news_list_image']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['field_ding_news_list_image']['alter']['html'] = 0;
  $handler->display->display_options['fields']['field_ding_news_list_image']['element_type'] = 'div';
  $handler->display->display_options['fields']['field_ding_news_list_image']['element_class'] = 'image-container';
  $handler->display->display_options['fields']['field_ding_news_list_image']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_ding_news_list_image']['element_default_classes'] = 0;
  $handler->display->display_options['fields']['field_ding_news_list_image']['hide_empty'] = 0;
  $handler->display->display_options['fields']['field_ding_news_list_image']['empty_zero'] = 0;
  $handler->display->display_options['fields']['field_ding_news_list_image']['hide_alter_empty'] = 1;
  $handler->display->display_options['fields']['field_ding_news_list_image']['click_sort_column'] = 'fid';
  $handler->display->display_options['fields']['field_ding_news_list_image']['settings'] = array(
    'image_style' => 'ding_large',
    'image_link' => '',
  );
  $handler->display->display_options['fields']['field_ding_news_list_image']['field_api_classes'] = 0;
  /* Field: Lead (excluded) */
  $handler->display->display_options['fields']['field_ding_news_lead']['id'] = 'field_ding_news_lead';
  $handler->display->display_options['fields']['field_ding_news_lead']['table'] = 'field_data_field_ding_news_lead';
  $handler->display->display_options['fields']['field_ding_news_lead']['field'] = 'field_ding_news_lead';
  $handler->display->display_options['fields']['field_ding_news_lead']['ui_name'] = 'Lead (excluded)';
  $handler->display->display_options['fields']['field_ding_news_lead']['label'] = '';
  $handler->display->display_options['fields']['field_ding_news_lead']['exclude'] = TRUE;
  $handler->display->display_options['fields']['field_ding_news_lead']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['field_ding_news_lead']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['field_ding_news_lead']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['field_ding_news_lead']['alter']['external'] = 0;
  $handler->display->display_options['fields']['field_ding_news_lead']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['field_ding_news_lead']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['field_ding_news_lead']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['field_ding_news_lead']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['field_ding_news_lead']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['field_ding_news_lead']['alter']['more_link'] = 0;
  $handler->display->display_options['fields']['field_ding_news_lead']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['field_ding_news_lead']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['field_ding_news_lead']['alter']['html'] = 0;
  $handler->display->display_options['fields']['field_ding_news_lead']['element_type'] = 'p';
  $handler->display->display_options['fields']['field_ding_news_lead']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_ding_news_lead']['element_default_classes'] = 0;
  $handler->display->display_options['fields']['field_ding_news_lead']['hide_empty'] = 0;
  $handler->display->display_options['fields']['field_ding_news_lead']['empty_zero'] = 0;
  $handler->display->display_options['fields']['field_ding_news_lead']['hide_alter_empty'] = 1;
  $handler->display->display_options['fields']['field_ding_news_lead']['field_api_classes'] = 0;
  /* Field: Link (excluded) */
  $handler->display->display_options['fields']['view_node']['id'] = 'view_node';
  $handler->display->display_options['fields']['view_node']['table'] = 'views_entity_node';
  $handler->display->display_options['fields']['view_node']['field'] = 'view_node';
  $handler->display->display_options['fields']['view_node']['ui_name'] = 'Link (excluded)';
  $handler->display->display_options['fields']['view_node']['label'] = '';
  $handler->display->display_options['fields']['view_node']['exclude'] = TRUE;
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
  $handler->display->display_options['fields']['view_node']['element_default_classes'] = 0;
  $handler->display->display_options['fields']['view_node']['hide_empty'] = 0;
  $handler->display->display_options['fields']['view_node']['empty_zero'] = 0;
  $handler->display->display_options['fields']['view_node']['hide_alter_empty'] = 1;
  $handler->display->display_options['fields']['view_node']['text'] = 'Read more';
  /* Field: Lead and read more */
  $handler->display->display_options['fields']['nothing_1']['id'] = 'nothing_1';
  $handler->display->display_options['fields']['nothing_1']['table'] = 'views';
  $handler->display->display_options['fields']['nothing_1']['field'] = 'nothing';
  $handler->display->display_options['fields']['nothing_1']['ui_name'] = 'Lead and read more';
  $handler->display->display_options['fields']['nothing_1']['label'] = '';
  $handler->display->display_options['fields']['nothing_1']['alter']['text'] = '[field_ding_news_lead][view_node]';
  $handler->display->display_options['fields']['nothing_1']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['nothing_1']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['nothing_1']['alter']['external'] = 0;
  $handler->display->display_options['fields']['nothing_1']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['nothing_1']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['nothing_1']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['nothing_1']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['nothing_1']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['nothing_1']['alter']['more_link'] = 0;
  $handler->display->display_options['fields']['nothing_1']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['nothing_1']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['nothing_1']['alter']['html'] = 0;
  $handler->display->display_options['fields']['nothing_1']['element_type'] = 'div';
  $handler->display->display_options['fields']['nothing_1']['element_class'] = 'content';
  $handler->display->display_options['fields']['nothing_1']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['nothing_1']['element_default_classes'] = 0;
  $handler->display->display_options['fields']['nothing_1']['hide_empty'] = 0;
  $handler->display->display_options['fields']['nothing_1']['empty_zero'] = 0;
  $handler->display->display_options['fields']['nothing_1']['hide_alter_empty'] = 0;

  /* Display: Floated news list (library) */
  $handler = $view->new_display('panel_pane', 'Floated news list (library)', 'panel_pane_5');
  $handler->display->display_options['defaults']['css_class'] = FALSE;
  $handler->display->display_options['css_class'] = 'floated';
  $handler->display->display_options['defaults']['pager'] = FALSE;
  $handler->display->display_options['pager']['type'] = 'none';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['argument_input'] = array(
    'ding_library_nid_1' => array(
      'type' => 'panel',
      'context' => 'entity:user.cancel-url',
      'context_optional' => 0,
      'panel' => '0',
      'fixed' => '',
      'label' => 'Indhold: Library (field_ding_news_library:nid)',
    ),
    'tid' => array(
      'type' => 'panel',
      'context' => 'entity:user.cancel-url',
      'context_optional' => 0,
      'panel' => '1',
      'fixed' => '',
      'label' => 'Indhold: Has taxonomy term ID',
    ),
  );
  $translatables['ding_news'] = array(
    t('Master'),
    t('Read more'),
    t('Apply'),
    t('Gendan'),
    t('Sort by'),
    t('Asc'),
    t('Desc'),
    t('author'),
    t('<span class="label label-info">[field_ding_news_category]</span> <span class="date">[created]</span> <span class="author">by [name]</span>'),
    t('All'),
    t('Default news list'),
    t('This is the default news list used for displaying news'),
    t('more'),
    t('View panes'),
    t('Default news list (promoted)'),
    t('This is the default news list used for displaying news with promoted content '),
    t('Default news list (promoted attachment)'),
    t('Promoted news that are used to attach on news lists'),
    t('Full list'),
    t('Items per page'),
    t('- All -'),
    t('Offset'),
    t('News panes'),
    t('Library teaser highlight'),
    t('Feed'),
    t('Library teaser list'),
    t('Dummy text if no result'),
    t('Library Feed'),
    t('Simple news list'),
    t('Floated news list'),
    t('Floated news list (highlight)'),
    t('[field_ding_news_lead][view_node]'),
    t('Floated news list (library)'),
  );
  $export['ding_news'] = $view;

  return $export;
}
