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

  $view = new view();
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
  $handler->display->display_options['title'] = 'Library news';
  $handler->display->display_options['css_class'] = 'news-list';
  $handler->display->display_options['use_more'] = TRUE;
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['use_more_text'] = 'See all news';
  $handler->display->display_options['link_display'] = 'custom_url';
  $handler->display->display_options['link_url'] = 'nyheder';
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['query']['options']['query_comment'] = FALSE;
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'some';
  $handler->display->display_options['pager']['options']['items_per_page'] = '5';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['style_plugin'] = 'default';
  $handler->display->display_options['style_options']['row_class'] = 'news-list-item';
  $handler->display->display_options['row_plugin'] = 'node';
  $handler->display->display_options['row_options']['links'] = FALSE;
  /* No results behavior: Global: Text area */
  $handler->display->display_options['empty']['area']['id'] = 'area';
  $handler->display->display_options['empty']['area']['table'] = 'views';
  $handler->display->display_options['empty']['area']['field'] = 'area';
  $handler->display->display_options['empty']['area']['label'] = 'Empty text';
  $handler->display->display_options['empty']['area']['empty'] = TRUE;
  $handler->display->display_options['empty']['area']['content'] = 'No news were found.';
  $handler->display->display_options['empty']['area']['format'] = 'ding_wysiwyg';
  /* Relationship: Content: Author */
  $handler->display->display_options['relationships']['uid']['id'] = 'uid';
  $handler->display->display_options['relationships']['uid']['table'] = 'node';
  $handler->display->display_options['relationships']['uid']['field'] = 'uid';
  /* Field: Category (excluded) */
  $handler->display->display_options['fields']['field_ding_news_category']['id'] = 'field_ding_news_category';
  $handler->display->display_options['fields']['field_ding_news_category']['table'] = 'field_data_field_ding_news_category';
  $handler->display->display_options['fields']['field_ding_news_category']['field'] = 'field_ding_news_category';
  $handler->display->display_options['fields']['field_ding_news_category']['ui_name'] = 'Category (excluded)';
  $handler->display->display_options['fields']['field_ding_news_category']['label'] = '';
  $handler->display->display_options['fields']['field_ding_news_category']['exclude'] = TRUE;
  $handler->display->display_options['fields']['field_ding_news_category']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_ding_news_category']['element_default_classes'] = FALSE;
  /* Field: Date (excluded) */
  $handler->display->display_options['fields']['created']['id'] = 'created';
  $handler->display->display_options['fields']['created']['table'] = 'node';
  $handler->display->display_options['fields']['created']['field'] = 'created';
  $handler->display->display_options['fields']['created']['ui_name'] = 'Date (excluded)';
  $handler->display->display_options['fields']['created']['label'] = '';
  $handler->display->display_options['fields']['created']['exclude'] = TRUE;
  $handler->display->display_options['fields']['created']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['created']['element_default_classes'] = FALSE;
  $handler->display->display_options['fields']['created']['date_format'] = 'ding_long_date_only';
  /* Field: Author (excluded) */
  $handler->display->display_options['fields']['name']['id'] = 'name';
  $handler->display->display_options['fields']['name']['table'] = 'users';
  $handler->display->display_options['fields']['name']['field'] = 'name';
  $handler->display->display_options['fields']['name']['relationship'] = 'uid';
  $handler->display->display_options['fields']['name']['ui_name'] = 'Author (excluded)';
  $handler->display->display_options['fields']['name']['label'] = '';
  $handler->display->display_options['fields']['name']['exclude'] = TRUE;
  $handler->display->display_options['fields']['name']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['name']['element_default_classes'] = FALSE;
  /* Field: News title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['ui_name'] = 'News title';
  $handler->display->display_options['fields']['title']['label'] = '';
  $handler->display->display_options['fields']['title']['element_type'] = 'h3';
  $handler->display->display_options['fields']['title']['element_class'] = 'news-heading';
  $handler->display->display_options['fields']['title']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['title']['element_default_classes'] = FALSE;
  /* Field: Category, date and author */
  $handler->display->display_options['fields']['nothing']['id'] = 'nothing';
  $handler->display->display_options['fields']['nothing']['table'] = 'views';
  $handler->display->display_options['fields']['nothing']['field'] = 'nothing';
  $handler->display->display_options['fields']['nothing']['ui_name'] = 'Category, date and author';
  $handler->display->display_options['fields']['nothing']['label'] = '';
  $handler->display->display_options['fields']['nothing']['alter']['text'] = '<span class="news-label">[field_ding_news_category]</span> <span class="news-date">[created]</span>  |  <span class="news-author">af [name]</span>';
  $handler->display->display_options['fields']['nothing']['element_type'] = 'div';
  $handler->display->display_options['fields']['nothing']['element_class'] = 'news-sub-heading';
  $handler->display->display_options['fields']['nothing']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['nothing']['element_default_classes'] = FALSE;
  /* Field: Image (list image) */
  $handler->display->display_options['fields']['field_ding_news_list_image']['id'] = 'field_ding_news_list_image';
  $handler->display->display_options['fields']['field_ding_news_list_image']['table'] = 'field_data_field_ding_news_list_image';
  $handler->display->display_options['fields']['field_ding_news_list_image']['field'] = 'field_ding_news_list_image';
  $handler->display->display_options['fields']['field_ding_news_list_image']['ui_name'] = 'Image (list image)';
  $handler->display->display_options['fields']['field_ding_news_list_image']['label'] = '';
  $handler->display->display_options['fields']['field_ding_news_list_image']['element_type'] = 'div';
  $handler->display->display_options['fields']['field_ding_news_list_image']['element_class'] = 'news-image-wrapper';
  $handler->display->display_options['fields']['field_ding_news_list_image']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_ding_news_list_image']['element_default_classes'] = FALSE;
  $handler->display->display_options['fields']['field_ding_news_list_image']['click_sort_column'] = 'fid';
  $handler->display->display_options['fields']['field_ding_news_list_image']['type'] = 'cs_adaptive_image';
  $handler->display->display_options['fields']['field_ding_news_list_image']['settings'] = array(
    'relationship' => 'none',
    'ui_name' => 'Image (list image)',
    'custom_label' => 0,
    'label' => '',
    'element_label_colon' => 0,
    'exclude' => 0,
    'element_type_enable' => 1,
    'element_type' => 'div',
    'element_class_enable' => 1,
    'element_class' => 'image-container',
    'element_label_type_enable' => 0,
    'element_label_type' => '',
    'element_label_class_enable' => 0,
    'element_label_class' => '',
    'element_wrapper_type_enable' => 0,
    'element_wrapper_type' => '',
    'element_wrapper_class_enable' => 0,
    'element_wrapper_class' => '',
    'element_default_classes' => 0,
    'alter' => array(
      'alter_text' => 0,
      'text' => '',
      'make_link' => 0,
      'path' => '',
      'absolute' => 0,
      'replace_spaces' => 0,
      'external' => 0,
      'path_case' => 'none',
      'link_class' => '',
      'alt' => '',
      'rel' => '',
      'prefix' => '',
      'suffix' => '',
      'target' => '',
      'trim' => 0,
      'max_length' => '',
      'word_boundary' => 1,
      'ellipsis' => 1,
      'more_link' => 0,
      'more_link_text' => '',
      'more_link_path' => '',
      'html' => 0,
      'strip_tags' => 0,
      'preserve_tags' => '',
      'trim_whitespace' => 0,
      'nl2br' => 0,
    ),
    'empty' => '',
    'empty_zero' => 0,
    'hide_empty' => 0,
    'hide_alter_empty' => 1,
    'click_sort_column' => 'fid',
    'type' => 'cs_adaptive_image',
    'field_api_classes' => 0,
    'image_link' => 'content',
    'styles' => array(
      'breakpoint_1' => '768',
      'style_1' => 'ding_list_medium',
      'breakpoint_2' => '500',
      'style_2' => 'ding_list_small',
      'max_style' => 'ding_list_large',
      'fallback_style' => 'ding_list_large',
    ),
  );
  /* Field: Lead (content) */
  $handler->display->display_options['fields']['field_ding_news_lead']['id'] = 'field_ding_news_lead';
  $handler->display->display_options['fields']['field_ding_news_lead']['table'] = 'field_data_field_ding_news_lead';
  $handler->display->display_options['fields']['field_ding_news_lead']['field'] = 'field_ding_news_lead';
  $handler->display->display_options['fields']['field_ding_news_lead']['ui_name'] = 'Lead (content)';
  $handler->display->display_options['fields']['field_ding_news_lead']['label'] = '';
  $handler->display->display_options['fields']['field_ding_news_lead']['element_type'] = 'p';
  $handler->display->display_options['fields']['field_ding_news_lead']['element_class'] = 'news-list-content';
  $handler->display->display_options['fields']['field_ding_news_lead']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_ding_news_lead']['element_default_classes'] = FALSE;
  /* Field: Link (read more) */
  $handler->display->display_options['fields']['view_node']['id'] = 'view_node';
  $handler->display->display_options['fields']['view_node']['table'] = 'views_entity_node';
  $handler->display->display_options['fields']['view_node']['field'] = 'view_node';
  $handler->display->display_options['fields']['view_node']['ui_name'] = 'Link (read more)';
  $handler->display->display_options['fields']['view_node']['label'] = '';
  $handler->display->display_options['fields']['view_node']['element_type'] = 'span';
  $handler->display->display_options['fields']['view_node']['element_class'] = 'news-link';
  $handler->display->display_options['fields']['view_node']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['view_node']['element_default_classes'] = FALSE;
  $handler->display->display_options['fields']['view_node']['text'] = 'Read more';
  /* Sort criterion: Content: Post date */
  $handler->display->display_options['sorts']['created']['id'] = 'created';
  $handler->display->display_options['sorts']['created']['table'] = 'node';
  $handler->display->display_options['sorts']['created']['field'] = 'created';
  $handler->display->display_options['sorts']['created']['order'] = 'DESC';
  /* Contextual filter: Content: Has taxonomy term ID */
  $handler->display->display_options['arguments']['tid']['id'] = 'tid';
  $handler->display->display_options['arguments']['tid']['table'] = 'taxonomy_index';
  $handler->display->display_options['arguments']['tid']['field'] = 'tid';
  $handler->display->display_options['arguments']['tid']['default_argument_type'] = 'fixed';
  $handler->display->display_options['arguments']['tid']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['tid']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['tid']['summary_options']['items_per_page'] = '25';
  $handler->display->display_options['arguments']['tid']['validate']['type'] = 'taxonomy_term';
  $handler->display->display_options['arguments']['tid']['validate_options']['vocabularies'] = array(
    'news_category' => 'news_category',
  );
  $handler->display->display_options['arguments']['tid']['validate_options']['type'] = 'convert';
  $handler->display->display_options['filter_groups']['groups'] = array(
    1 => 'AND',
    2 => 'OR',
  );
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
    'ding_news' => 'ding_news',
  );
  $handler->display->display_options['filters']['type']['group'] = 1;

  /* Display: News list (frontpage) */
  $handler = $view->new_display('panel_pane', 'News list (frontpage)', 'ding_news_frontpage_list');
  $handler->display->display_options['defaults']['css_class'] = FALSE;
  $handler->display->display_options['css_class'] = 'grid-medium';
  $handler->display->display_options['defaults']['use_more'] = FALSE;
  $handler->display->display_options['use_more'] = TRUE;
  $handler->display->display_options['defaults']['use_more_always'] = FALSE;
  $handler->display->display_options['defaults']['use_more_always'] = FALSE;
  $handler->display->display_options['use_more_always'] = TRUE;
  $handler->display->display_options['defaults']['use_more_text'] = FALSE;
  $handler->display->display_options['use_more_text'] = 'See all news';
  $handler->display->display_options['defaults']['link_display'] = FALSE;
  $handler->display->display_options['link_display'] = 'custom_url';
  $handler->display->display_options['link_url'] = 'nyheder';
  $handler->display->display_options['defaults']['pager'] = FALSE;
  $handler->display->display_options['pager']['type'] = 'some';
  $handler->display->display_options['pager']['options']['items_per_page'] = '5';
  $handler->display->display_options['pager']['options']['offset'] = '';
  $handler->display->display_options['defaults']['style_plugin'] = FALSE;
  $handler->display->display_options['style_plugin'] = 'default';
  $handler->display->display_options['defaults']['style_options'] = FALSE;
  $handler->display->display_options['defaults']['row_plugin'] = FALSE;
  $handler->display->display_options['row_plugin'] = 'node';
  $handler->display->display_options['row_options']['links'] = FALSE;
  $handler->display->display_options['defaults']['row_options'] = FALSE;
  $handler->display->display_options['defaults']['relationships'] = FALSE;
  /* Relationship: Content: Author */
  $handler->display->display_options['relationships']['uid']['id'] = 'uid';
  $handler->display->display_options['relationships']['uid']['table'] = 'node';
  $handler->display->display_options['relationships']['uid']['field'] = 'uid';
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Field: Image (list image) */
  $handler->display->display_options['fields']['field_ding_news_list_image']['id'] = 'field_ding_news_list_image';
  $handler->display->display_options['fields']['field_ding_news_list_image']['table'] = 'field_data_field_ding_news_list_image';
  $handler->display->display_options['fields']['field_ding_news_list_image']['field'] = 'field_ding_news_list_image';
  $handler->display->display_options['fields']['field_ding_news_list_image']['ui_name'] = 'Image (list image)';
  $handler->display->display_options['fields']['field_ding_news_list_image']['label'] = '';
  $handler->display->display_options['fields']['field_ding_news_list_image']['element_type'] = 'div';
  $handler->display->display_options['fields']['field_ding_news_list_image']['element_class'] = 'news-image-wrapper';
  $handler->display->display_options['fields']['field_ding_news_list_image']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_ding_news_list_image']['element_default_classes'] = FALSE;
  $handler->display->display_options['fields']['field_ding_news_list_image']['click_sort_column'] = 'fid';
  $handler->display->display_options['fields']['field_ding_news_list_image']['type'] = 'cs_adaptive_image';
  $handler->display->display_options['fields']['field_ding_news_list_image']['settings'] = array(
    'image_link' => 'content',
    'styles' => array(
      'breakpoint_1' => '768',
      'style_1' => 'ding_list_medium',
      'breakpoint_2' => '500',
      'style_2' => 'ding_list_small',
      'max_style' => 'ding_list_large',
      'fallback_style' => 'ding_list_large',
    ),
  );
  /* Field: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['ui_name'] = 'Title';
  $handler->display->display_options['fields']['title']['label'] = '';
  $handler->display->display_options['fields']['title']['element_type'] = 'h3';
  $handler->display->display_options['fields']['title']['element_class'] = 'news-heading';
  $handler->display->display_options['fields']['title']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['title']['element_default_classes'] = FALSE;
  /* Field: Category */
  $handler->display->display_options['fields']['field_ding_news_category']['id'] = 'field_ding_news_category';
  $handler->display->display_options['fields']['field_ding_news_category']['table'] = 'field_data_field_ding_news_category';
  $handler->display->display_options['fields']['field_ding_news_category']['field'] = 'field_ding_news_category';
  $handler->display->display_options['fields']['field_ding_news_category']['ui_name'] = 'Category';
  $handler->display->display_options['fields']['field_ding_news_category']['label'] = '';
  $handler->display->display_options['fields']['field_ding_news_category']['element_type'] = 'span';
  $handler->display->display_options['fields']['field_ding_news_category']['element_class'] = 'news-label';
  $handler->display->display_options['fields']['field_ding_news_category']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_ding_news_category']['element_wrapper_type'] = '0';
  $handler->display->display_options['fields']['field_ding_news_category']['element_default_classes'] = FALSE;
  /* Field: Date */
  $handler->display->display_options['fields']['created']['id'] = 'created';
  $handler->display->display_options['fields']['created']['table'] = 'node';
  $handler->display->display_options['fields']['created']['field'] = 'created';
  $handler->display->display_options['fields']['created']['ui_name'] = 'Date';
  $handler->display->display_options['fields']['created']['label'] = '';
  $handler->display->display_options['fields']['created']['element_type'] = 'span';
  $handler->display->display_options['fields']['created']['element_class'] = 'news-date';
  $handler->display->display_options['fields']['created']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['created']['element_wrapper_type'] = '0';
  $handler->display->display_options['fields']['created']['element_default_classes'] = FALSE;
  $handler->display->display_options['fields']['created']['date_format'] = 'ding_long_date_only';
  /* Field: Author */
  $handler->display->display_options['fields']['name']['id'] = 'name';
  $handler->display->display_options['fields']['name']['table'] = 'users';
  $handler->display->display_options['fields']['name']['field'] = 'name';
  $handler->display->display_options['fields']['name']['relationship'] = 'uid';
  $handler->display->display_options['fields']['name']['ui_name'] = 'Author';
  $handler->display->display_options['fields']['name']['label'] = '';
  $handler->display->display_options['fields']['name']['element_type'] = 'span';
  $handler->display->display_options['fields']['name']['element_class'] = 'news-author';
  $handler->display->display_options['fields']['name']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['name']['element_wrapper_type'] = '0';
  $handler->display->display_options['fields']['name']['element_default_classes'] = FALSE;
  /* Field: Lead */
  $handler->display->display_options['fields']['field_ding_news_lead']['id'] = 'field_ding_news_lead';
  $handler->display->display_options['fields']['field_ding_news_lead']['table'] = 'field_data_field_ding_news_lead';
  $handler->display->display_options['fields']['field_ding_news_lead']['field'] = 'field_ding_news_lead';
  $handler->display->display_options['fields']['field_ding_news_lead']['ui_name'] = 'Lead';
  $handler->display->display_options['fields']['field_ding_news_lead']['label'] = '';
  $handler->display->display_options['fields']['field_ding_news_lead']['element_type'] = 'p';
  $handler->display->display_options['fields']['field_ding_news_lead']['element_class'] = 'news-list-content';
  $handler->display->display_options['fields']['field_ding_news_lead']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_ding_news_lead']['element_wrapper_type'] = '0';
  $handler->display->display_options['fields']['field_ding_news_lead']['element_default_classes'] = FALSE;
  /* Field: Link (read more) */
  $handler->display->display_options['fields']['view_node']['id'] = 'view_node';
  $handler->display->display_options['fields']['view_node']['table'] = 'views_entity_node';
  $handler->display->display_options['fields']['view_node']['field'] = 'view_node';
  $handler->display->display_options['fields']['view_node']['ui_name'] = 'Link (read more)';
  $handler->display->display_options['fields']['view_node']['label'] = '';
  $handler->display->display_options['fields']['view_node']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['view_node']['element_wrapper_type'] = 'span';
  $handler->display->display_options['fields']['view_node']['element_wrapper_class'] = 'news-link';
  $handler->display->display_options['fields']['view_node']['element_default_classes'] = FALSE;
  $handler->display->display_options['fields']['view_node']['text'] = 'Read more';
  /* Field: Content: Link */
  $handler->display->display_options['fields']['view_node_1']['id'] = 'view_node_1';
  $handler->display->display_options['fields']['view_node_1']['table'] = 'views_entity_node';
  $handler->display->display_options['fields']['view_node_1']['field'] = 'view_node';
  $handler->display->display_options['fields']['view_node_1']['label'] = '';
  $handler->display->display_options['fields']['view_node_1']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['view_node_1']['alter']['text'] = '<i class="icon-chevron-right"></i>';
  $handler->display->display_options['fields']['view_node_1']['element_type'] = 'div';
  $handler->display->display_options['fields']['view_node_1']['element_class'] = 'news-arrow-link';
  $handler->display->display_options['fields']['view_node_1']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['view_node_1']['element_default_classes'] = FALSE;
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
  $handler->display->display_options['defaults']['filter_groups'] = FALSE;
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
  $handler->display->display_options['pane_category']['name'] = 'News panes';
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

  /* Display: Library news list */
  $handler = $view->new_display('panel_pane', 'Library news list', 'ding_news_library_list');
  $handler->display->display_options['defaults']['css_class'] = FALSE;
  $handler->display->display_options['defaults']['use_more'] = FALSE;
  $handler->display->display_options['use_more'] = TRUE;
  $handler->display->display_options['defaults']['use_more_always'] = FALSE;
  $handler->display->display_options['defaults']['use_more_always'] = FALSE;
  $handler->display->display_options['use_more_always'] = TRUE;
  $handler->display->display_options['defaults']['use_more_text'] = FALSE;
  $handler->display->display_options['use_more_text'] = 'See all news';
  $handler->display->display_options['defaults']['link_display'] = FALSE;
  $handler->display->display_options['link_display'] = 'custom_url';
  $handler->display->display_options['link_url'] = 'nyheder';
  $handler->display->display_options['defaults']['pager'] = FALSE;
  $handler->display->display_options['pager']['type'] = 'some';
  $handler->display->display_options['pager']['options']['items_per_page'] = '6';
  $handler->display->display_options['pager']['options']['offset'] = '';
  $handler->display->display_options['defaults']['style_plugin'] = FALSE;
  $handler->display->display_options['style_plugin'] = 'default';
  $handler->display->display_options['defaults']['style_options'] = FALSE;
  $handler->display->display_options['defaults']['row_plugin'] = FALSE;
  $handler->display->display_options['row_plugin'] = 'node';
  $handler->display->display_options['row_options']['links'] = FALSE;
  $handler->display->display_options['defaults']['row_options'] = FALSE;
  $handler->display->display_options['defaults']['empty'] = FALSE;
  $handler->display->display_options['defaults']['relationships'] = FALSE;
  /* Relationship: OG membership: OG membership from Node */
  $handler->display->display_options['relationships']['og_membership_rel']['id'] = 'og_membership_rel';
  $handler->display->display_options['relationships']['og_membership_rel']['table'] = 'node';
  $handler->display->display_options['relationships']['og_membership_rel']['field'] = 'og_membership_rel';
  /* Relationship: OG membership: Group Node from OG membership */
  $handler->display->display_options['relationships']['og_membership_related_node_group']['id'] = 'og_membership_related_node_group';
  $handler->display->display_options['relationships']['og_membership_related_node_group']['table'] = 'og_membership';
  $handler->display->display_options['relationships']['og_membership_related_node_group']['field'] = 'og_membership_related_node_group';
  $handler->display->display_options['relationships']['og_membership_related_node_group']['relationship'] = 'og_membership_rel';
  $handler->display->display_options['relationships']['og_membership_related_node_group']['label'] = 'OG node group';
  /* Relationship: Content: Author */
  $handler->display->display_options['relationships']['uid']['id'] = 'uid';
  $handler->display->display_options['relationships']['uid']['table'] = 'node';
  $handler->display->display_options['relationships']['uid']['field'] = 'uid';
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Field: Image (list image) */
  $handler->display->display_options['fields']['field_ding_news_list_image']['id'] = 'field_ding_news_list_image';
  $handler->display->display_options['fields']['field_ding_news_list_image']['table'] = 'field_data_field_ding_news_list_image';
  $handler->display->display_options['fields']['field_ding_news_list_image']['field'] = 'field_ding_news_list_image';
  $handler->display->display_options['fields']['field_ding_news_list_image']['ui_name'] = 'Image (list image)';
  $handler->display->display_options['fields']['field_ding_news_list_image']['label'] = '';
  $handler->display->display_options['fields']['field_ding_news_list_image']['element_type'] = 'div';
  $handler->display->display_options['fields']['field_ding_news_list_image']['element_class'] = 'news-image-wrapper';
  $handler->display->display_options['fields']['field_ding_news_list_image']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_ding_news_list_image']['element_default_classes'] = FALSE;
  $handler->display->display_options['fields']['field_ding_news_list_image']['click_sort_column'] = 'fid';
  $handler->display->display_options['fields']['field_ding_news_list_image']['type'] = 'cs_adaptive_image';
  $handler->display->display_options['fields']['field_ding_news_list_image']['settings'] = array(
    'image_link' => 'content',
    'styles' => array(
      'breakpoint_1' => '768',
      'style_1' => 'ding_list_medium',
      'breakpoint_2' => '500',
      'style_2' => 'ding_list_small',
      'max_style' => 'ding_list_large',
      'fallback_style' => 'ding_list_large',
    ),
  );
  /* Field: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['ui_name'] = 'Title';
  $handler->display->display_options['fields']['title']['label'] = '';
  $handler->display->display_options['fields']['title']['element_type'] = 'h3';
  $handler->display->display_options['fields']['title']['element_class'] = 'news-heading';
  $handler->display->display_options['fields']['title']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['title']['element_default_classes'] = FALSE;
  /* Field: Category */
  $handler->display->display_options['fields']['field_ding_news_category']['id'] = 'field_ding_news_category';
  $handler->display->display_options['fields']['field_ding_news_category']['table'] = 'field_data_field_ding_news_category';
  $handler->display->display_options['fields']['field_ding_news_category']['field'] = 'field_ding_news_category';
  $handler->display->display_options['fields']['field_ding_news_category']['ui_name'] = 'Category';
  $handler->display->display_options['fields']['field_ding_news_category']['label'] = '';
  $handler->display->display_options['fields']['field_ding_news_category']['element_type'] = 'span';
  $handler->display->display_options['fields']['field_ding_news_category']['element_class'] = 'news-label';
  $handler->display->display_options['fields']['field_ding_news_category']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_ding_news_category']['element_wrapper_type'] = '0';
  $handler->display->display_options['fields']['field_ding_news_category']['element_default_classes'] = FALSE;
  /* Field: Date */
  $handler->display->display_options['fields']['created']['id'] = 'created';
  $handler->display->display_options['fields']['created']['table'] = 'node';
  $handler->display->display_options['fields']['created']['field'] = 'created';
  $handler->display->display_options['fields']['created']['ui_name'] = 'Date';
  $handler->display->display_options['fields']['created']['label'] = '';
  $handler->display->display_options['fields']['created']['element_type'] = 'span';
  $handler->display->display_options['fields']['created']['element_class'] = 'news-date';
  $handler->display->display_options['fields']['created']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['created']['element_wrapper_type'] = '0';
  $handler->display->display_options['fields']['created']['element_default_classes'] = FALSE;
  $handler->display->display_options['fields']['created']['date_format'] = 'ding_long_date_only';
  /* Field: Author */
  $handler->display->display_options['fields']['name']['id'] = 'name';
  $handler->display->display_options['fields']['name']['table'] = 'users';
  $handler->display->display_options['fields']['name']['field'] = 'name';
  $handler->display->display_options['fields']['name']['relationship'] = 'uid';
  $handler->display->display_options['fields']['name']['ui_name'] = 'Author';
  $handler->display->display_options['fields']['name']['label'] = '';
  $handler->display->display_options['fields']['name']['element_type'] = 'span';
  $handler->display->display_options['fields']['name']['element_class'] = 'news-author';
  $handler->display->display_options['fields']['name']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['name']['element_wrapper_type'] = '0';
  $handler->display->display_options['fields']['name']['element_default_classes'] = FALSE;
  /* Field: Lead */
  $handler->display->display_options['fields']['field_ding_news_lead']['id'] = 'field_ding_news_lead';
  $handler->display->display_options['fields']['field_ding_news_lead']['table'] = 'field_data_field_ding_news_lead';
  $handler->display->display_options['fields']['field_ding_news_lead']['field'] = 'field_ding_news_lead';
  $handler->display->display_options['fields']['field_ding_news_lead']['ui_name'] = 'Lead';
  $handler->display->display_options['fields']['field_ding_news_lead']['label'] = '';
  $handler->display->display_options['fields']['field_ding_news_lead']['element_type'] = 'p';
  $handler->display->display_options['fields']['field_ding_news_lead']['element_class'] = 'news-list-content';
  $handler->display->display_options['fields']['field_ding_news_lead']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_ding_news_lead']['element_wrapper_type'] = '0';
  $handler->display->display_options['fields']['field_ding_news_lead']['element_default_classes'] = FALSE;
  /* Field: Link (read more) */
  $handler->display->display_options['fields']['view_node']['id'] = 'view_node';
  $handler->display->display_options['fields']['view_node']['table'] = 'views_entity_node';
  $handler->display->display_options['fields']['view_node']['field'] = 'view_node';
  $handler->display->display_options['fields']['view_node']['ui_name'] = 'Link (read more)';
  $handler->display->display_options['fields']['view_node']['label'] = '';
  $handler->display->display_options['fields']['view_node']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['view_node']['element_wrapper_type'] = 'span';
  $handler->display->display_options['fields']['view_node']['element_wrapper_class'] = 'news-link';
  $handler->display->display_options['fields']['view_node']['element_default_classes'] = FALSE;
  $handler->display->display_options['fields']['view_node']['text'] = 'Read more';
  /* Field: Content: Link */
  $handler->display->display_options['fields']['view_node_1']['id'] = 'view_node_1';
  $handler->display->display_options['fields']['view_node_1']['table'] = 'views_entity_node';
  $handler->display->display_options['fields']['view_node_1']['field'] = 'view_node';
  $handler->display->display_options['fields']['view_node_1']['label'] = '';
  $handler->display->display_options['fields']['view_node_1']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['view_node_1']['alter']['text'] = '<i class="icon-chevron-right"></i>';
  $handler->display->display_options['fields']['view_node_1']['element_type'] = 'div';
  $handler->display->display_options['fields']['view_node_1']['element_class'] = 'news-arrow-link';
  $handler->display->display_options['fields']['view_node_1']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['view_node_1']['element_default_classes'] = FALSE;
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
  /* Contextual filter: OG membership: Group ID */
  $handler->display->display_options['arguments']['gid']['id'] = 'gid';
  $handler->display->display_options['arguments']['gid']['table'] = 'og_membership';
  $handler->display->display_options['arguments']['gid']['field'] = 'gid';
  $handler->display->display_options['arguments']['gid']['relationship'] = 'og_membership_rel';
  $handler->display->display_options['arguments']['gid']['default_action'] = 'empty';
  $handler->display->display_options['arguments']['gid']['default_argument_type'] = 'fixed';
  $handler->display->display_options['arguments']['gid']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['gid']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['gid']['summary_options']['items_per_page'] = '25';
  $handler->display->display_options['pane_category']['name'] = 'Library panes';
  $handler->display->display_options['pane_category']['weight'] = '0';
  $handler->display->display_options['allow']['use_pager'] = 0;
  $handler->display->display_options['allow']['items_per_page'] = 0;
  $handler->display->display_options['allow']['offset'] = 0;
  $handler->display->display_options['allow']['link_to_view'] = 0;
  $handler->display->display_options['allow']['more_link'] = 0;
  $handler->display->display_options['allow']['path_override'] = 0;
  $handler->display->display_options['allow']['title_override'] = 'title_override';
  $handler->display->display_options['allow']['exposed_form'] = 'exposed_form';
  $handler->display->display_options['allow']['fields_override'] = 0;
  $handler->display->display_options['argument_input'] = array(
    'gid' => array(
      'type' => 'context',
      'context' => 'entity:node.nid',
      'context_optional' => 0,
      'panel' => '0',
      'fixed' => '',
      'label' => 'OG membership: Group ID',
    ),
  );

  /* Display: News list */
  $handler = $view->new_display('panel_pane', 'News list', 'ding_news_list');
  $handler->display->display_options['defaults']['css_class'] = FALSE;
  $handler->display->display_options['defaults']['use_ajax'] = FALSE;
  $handler->display->display_options['use_ajax'] = TRUE;
  $handler->display->display_options['defaults']['use_more'] = FALSE;
  $handler->display->display_options['defaults']['link_display'] = FALSE;
  $handler->display->display_options['link_display'] = 'custom_url';
  $handler->display->display_options['link_url'] = 'nyheder';
  $handler->display->display_options['defaults']['group_by'] = FALSE;
  $handler->display->display_options['group_by'] = TRUE;
  $handler->display->display_options['defaults']['exposed_form'] = FALSE;
  $handler->display->display_options['exposed_form']['type'] = 'better_exposed_filters';
  $handler->display->display_options['exposed_form']['options']['expose_sort_order'] = FALSE;
  $handler->display->display_options['exposed_form']['options']['autosubmit'] = TRUE;
  $handler->display->display_options['exposed_form']['options']['bef'] = array(
    'general' => array(
      'input_required' => 0,
      'text_input_required' => array(
        'text_input_required' => array(
          'value' => 'Select any filter and click on Apply to see results',
          'format' => 'ding_wysiwyg',
        ),
      ),
      'allow_secondary' => 0,
      'secondary_label' => 'Advanced options',
      'secondary_collapse_override' => '0',
    ),
    'field_ding_news_category_tid' => array(
      'bef_format' => 'bef',
      'more_options' => array(
        'bef_select_all_none' => 0,
        'bef_collapsible' => 0,
        'autosubmit' => 0,
        'is_secondary' => 0,
        'any_label' => '',
        'bef_filter_description' => '',
        'tokens' => array(
          'available' => array(
            0 => 'global_types',
            1 => 'vocabulary',
          ),
        ),
        'rewrite' => array(
          'filter_rewrite_values' => '',
        ),
      ),
    ),
    'og_group_ref_target_id_entityreference_filter' => array(
      'bef_format' => 'bef',
      'more_options' => array(
        'bef_select_all_none' => 0,
        'bef_collapsible' => 0,
        'autosubmit' => 0,
        'is_secondary' => 0,
        'any_label' => '',
        'bef_filter_description' => '',
        'tokens' => array(
          'available' => array(
            0 => 'global_types',
          ),
        ),
        'rewrite' => array(
          'filter_rewrite_values' => '',
        ),
      ),
    ),
  );
  $handler->display->display_options['defaults']['pager'] = FALSE;
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = '10';
  $handler->display->display_options['pager']['options']['offset'] = '';
  $handler->display->display_options['pager']['options']['id'] = '0';
  $handler->display->display_options['defaults']['style_plugin'] = FALSE;
  $handler->display->display_options['style_plugin'] = 'default';
  $handler->display->display_options['defaults']['style_options'] = FALSE;
  $handler->display->display_options['defaults']['row_plugin'] = FALSE;
  $handler->display->display_options['row_plugin'] = 'node';
  $handler->display->display_options['row_options']['links'] = FALSE;
  $handler->display->display_options['defaults']['row_options'] = FALSE;
  $handler->display->display_options['exposed_block'] = TRUE;
  $handler->display->display_options['defaults']['relationships'] = FALSE;
  /* Relationship: OG membership: OG membership from Node */
  $handler->display->display_options['relationships']['og_membership_rel']['id'] = 'og_membership_rel';
  $handler->display->display_options['relationships']['og_membership_rel']['table'] = 'node';
  $handler->display->display_options['relationships']['og_membership_rel']['field'] = 'og_membership_rel';
  /* Relationship: OG membership: Group Node from OG membership */
  $handler->display->display_options['relationships']['og_membership_related_node_group']['id'] = 'og_membership_related_node_group';
  $handler->display->display_options['relationships']['og_membership_related_node_group']['table'] = 'og_membership';
  $handler->display->display_options['relationships']['og_membership_related_node_group']['field'] = 'og_membership_related_node_group';
  $handler->display->display_options['relationships']['og_membership_related_node_group']['relationship'] = 'og_membership_rel';
  $handler->display->display_options['relationships']['og_membership_related_node_group']['label'] = 'OG node group';
  /* Relationship: Content: Category (field_ding_news_category) */
  $handler->display->display_options['relationships']['field_ding_news_category_tid']['id'] = 'field_ding_news_category_tid';
  $handler->display->display_options['relationships']['field_ding_news_category_tid']['table'] = 'field_data_field_ding_news_category';
  $handler->display->display_options['relationships']['field_ding_news_category_tid']['field'] = 'field_ding_news_category_tid';
  /* Relationship: Content: Author */
  $handler->display->display_options['relationships']['uid']['id'] = 'uid';
  $handler->display->display_options['relationships']['uid']['table'] = 'node';
  $handler->display->display_options['relationships']['uid']['field'] = 'uid';
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Field: Image (list image) */
  $handler->display->display_options['fields']['field_ding_news_list_image']['id'] = 'field_ding_news_list_image';
  $handler->display->display_options['fields']['field_ding_news_list_image']['table'] = 'field_data_field_ding_news_list_image';
  $handler->display->display_options['fields']['field_ding_news_list_image']['field'] = 'field_ding_news_list_image';
  $handler->display->display_options['fields']['field_ding_news_list_image']['ui_name'] = 'Image (list image)';
  $handler->display->display_options['fields']['field_ding_news_list_image']['label'] = '';
  $handler->display->display_options['fields']['field_ding_news_list_image']['element_type'] = 'div';
  $handler->display->display_options['fields']['field_ding_news_list_image']['element_class'] = 'news-image-wrapper';
  $handler->display->display_options['fields']['field_ding_news_list_image']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_ding_news_list_image']['element_default_classes'] = FALSE;
  $handler->display->display_options['fields']['field_ding_news_list_image']['click_sort_column'] = 'fid';
  $handler->display->display_options['fields']['field_ding_news_list_image']['type'] = 'cs_adaptive_image';
  $handler->display->display_options['fields']['field_ding_news_list_image']['settings'] = array(
    'relationship' => 'none',
    'ui_name' => 'Image (list image)',
    'custom_label' => 0,
    'label' => '',
    'element_label_colon' => 0,
    'exclude' => 0,
    'element_type_enable' => 1,
    'element_type' => 'div',
    'element_class_enable' => 1,
    'element_class' => 'news-image-wrapper',
    'element_label_type_enable' => 0,
    'element_label_type' => '',
    'element_label_class_enable' => 0,
    'element_label_class' => '',
    'element_wrapper_type_enable' => 0,
    'element_wrapper_type' => '',
    'element_wrapper_class_enable' => 0,
    'element_wrapper_class' => '',
    'element_default_classes' => 0,
    'alter' => array(
      'alter_text' => 0,
      'text' => '',
      'make_link' => 0,
      'path' => '',
      'absolute' => 0,
      'replace_spaces' => 0,
      'external' => 0,
      'path_case' => 'none',
      'link_class' => '',
      'alt' => '',
      'rel' => '',
      'prefix' => '',
      'suffix' => '',
      'target' => '',
      'trim' => 0,
      'max_length' => '',
      'word_boundary' => 1,
      'ellipsis' => 1,
      'more_link' => 0,
      'more_link_text' => '',
      'more_link_path' => '',
      'html' => 0,
      'strip_tags' => 0,
      'preserve_tags' => '',
      'trim_whitespace' => 0,
      'nl2br' => 0,
    ),
    'empty' => '',
    'empty_zero' => 0,
    'hide_empty' => 0,
    'hide_alter_empty' => 1,
    'click_sort_column' => 'fid',
    'type' => 'cs_adaptive_image',
    'field_api_classes' => 0,
    'image_link' => 'content',
    'styles' => array(
      'breakpoint_1' => '768',
      'style_1' => 'ding_list_medium',
      'breakpoint_2' => '500',
      'style_2' => 'ding_list_small',
      'max_style' => 'ding_list_large',
      'fallback_style' => 'ding_list_large',
    ),
  );
  /* Field: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['ui_name'] = 'Title';
  $handler->display->display_options['fields']['title']['label'] = '';
  $handler->display->display_options['fields']['title']['element_type'] = 'h3';
  $handler->display->display_options['fields']['title']['element_class'] = 'news-heading';
  $handler->display->display_options['fields']['title']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['title']['element_default_classes'] = FALSE;
  /* Field: Category */
  $handler->display->display_options['fields']['field_ding_news_category']['id'] = 'field_ding_news_category';
  $handler->display->display_options['fields']['field_ding_news_category']['table'] = 'field_data_field_ding_news_category';
  $handler->display->display_options['fields']['field_ding_news_category']['field'] = 'field_ding_news_category';
  $handler->display->display_options['fields']['field_ding_news_category']['ui_name'] = 'Category';
  $handler->display->display_options['fields']['field_ding_news_category']['label'] = '';
  $handler->display->display_options['fields']['field_ding_news_category']['element_type'] = 'span';
  $handler->display->display_options['fields']['field_ding_news_category']['element_class'] = 'news-label';
  $handler->display->display_options['fields']['field_ding_news_category']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_ding_news_category']['element_wrapper_type'] = '0';
  $handler->display->display_options['fields']['field_ding_news_category']['element_default_classes'] = FALSE;
  /* Field: Date */
  $handler->display->display_options['fields']['created']['id'] = 'created';
  $handler->display->display_options['fields']['created']['table'] = 'node';
  $handler->display->display_options['fields']['created']['field'] = 'created';
  $handler->display->display_options['fields']['created']['ui_name'] = 'Date';
  $handler->display->display_options['fields']['created']['label'] = '';
  $handler->display->display_options['fields']['created']['element_type'] = 'span';
  $handler->display->display_options['fields']['created']['element_class'] = 'news-date';
  $handler->display->display_options['fields']['created']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['created']['element_wrapper_type'] = '0';
  $handler->display->display_options['fields']['created']['element_default_classes'] = FALSE;
  $handler->display->display_options['fields']['created']['date_format'] = 'ding_long_date_only';
  /* Field: Author */
  $handler->display->display_options['fields']['name']['id'] = 'name';
  $handler->display->display_options['fields']['name']['table'] = 'users';
  $handler->display->display_options['fields']['name']['field'] = 'name';
  $handler->display->display_options['fields']['name']['relationship'] = 'uid';
  $handler->display->display_options['fields']['name']['ui_name'] = 'Author';
  $handler->display->display_options['fields']['name']['label'] = '';
  $handler->display->display_options['fields']['name']['element_type'] = 'span';
  $handler->display->display_options['fields']['name']['element_class'] = 'news-author';
  $handler->display->display_options['fields']['name']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['name']['element_wrapper_type'] = '0';
  $handler->display->display_options['fields']['name']['element_default_classes'] = FALSE;
  /* Field: Lead */
  $handler->display->display_options['fields']['field_ding_news_lead']['id'] = 'field_ding_news_lead';
  $handler->display->display_options['fields']['field_ding_news_lead']['table'] = 'field_data_field_ding_news_lead';
  $handler->display->display_options['fields']['field_ding_news_lead']['field'] = 'field_ding_news_lead';
  $handler->display->display_options['fields']['field_ding_news_lead']['ui_name'] = 'Lead';
  $handler->display->display_options['fields']['field_ding_news_lead']['label'] = '';
  $handler->display->display_options['fields']['field_ding_news_lead']['element_type'] = 'p';
  $handler->display->display_options['fields']['field_ding_news_lead']['element_class'] = 'news-list-content';
  $handler->display->display_options['fields']['field_ding_news_lead']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_ding_news_lead']['element_wrapper_type'] = '0';
  $handler->display->display_options['fields']['field_ding_news_lead']['element_default_classes'] = FALSE;
  /* Field: Link (read more) */
  $handler->display->display_options['fields']['view_node']['id'] = 'view_node';
  $handler->display->display_options['fields']['view_node']['table'] = 'views_entity_node';
  $handler->display->display_options['fields']['view_node']['field'] = 'view_node';
  $handler->display->display_options['fields']['view_node']['ui_name'] = 'Link (read more)';
  $handler->display->display_options['fields']['view_node']['label'] = '';
  $handler->display->display_options['fields']['view_node']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['view_node']['element_wrapper_type'] = 'span';
  $handler->display->display_options['fields']['view_node']['element_wrapper_class'] = 'news-link';
  $handler->display->display_options['fields']['view_node']['element_default_classes'] = FALSE;
  $handler->display->display_options['fields']['view_node']['text'] = 'Read more';
  /* Field: Content: Link */
  $handler->display->display_options['fields']['view_node_1']['id'] = 'view_node_1';
  $handler->display->display_options['fields']['view_node_1']['table'] = 'views_entity_node';
  $handler->display->display_options['fields']['view_node_1']['field'] = 'view_node';
  $handler->display->display_options['fields']['view_node_1']['label'] = '';
  $handler->display->display_options['fields']['view_node_1']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['view_node_1']['alter']['text'] = '<i class="icon-chevron-right"></i>';
  $handler->display->display_options['fields']['view_node_1']['element_type'] = 'div';
  $handler->display->display_options['fields']['view_node_1']['element_class'] = 'news-arrow-link';
  $handler->display->display_options['fields']['view_node_1']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['view_node_1']['element_default_classes'] = FALSE;
  $handler->display->display_options['defaults']['arguments'] = FALSE;
  /* Contextual filter: Content: Has taxonomy term ID */
  $handler->display->display_options['arguments']['tid']['id'] = 'tid';
  $handler->display->display_options['arguments']['tid']['table'] = 'taxonomy_index';
  $handler->display->display_options['arguments']['tid']['field'] = 'tid';
  $handler->display->display_options['arguments']['tid']['default_argument_type'] = 'fixed';
  $handler->display->display_options['arguments']['tid']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['tid']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['tid']['summary_options']['items_per_page'] = '25';
  $handler->display->display_options['arguments']['tid']['specify_validation'] = TRUE;
  $handler->display->display_options['arguments']['tid']['validate']['type'] = 'taxonomy_term';
  $handler->display->display_options['arguments']['tid']['validate_options']['vocabularies'] = array(
    'news_category' => 'news_category',
  );
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
    'ding_news' => 'ding_news',
  );
  $handler->display->display_options['filters']['type']['group'] = 1;
  /* Filter criterion: Content: Category (field_ding_news_category) */
  $handler->display->display_options['filters']['field_ding_news_category_tid']['id'] = 'field_ding_news_category_tid';
  $handler->display->display_options['filters']['field_ding_news_category_tid']['table'] = 'field_data_field_ding_news_category';
  $handler->display->display_options['filters']['field_ding_news_category_tid']['field'] = 'field_ding_news_category_tid';
  $handler->display->display_options['filters']['field_ding_news_category_tid']['group'] = 1;
  $handler->display->display_options['filters']['field_ding_news_category_tid']['exposed'] = TRUE;
  $handler->display->display_options['filters']['field_ding_news_category_tid']['expose']['operator_id'] = 'field_ding_news_category_tid_op';
  $handler->display->display_options['filters']['field_ding_news_category_tid']['expose']['label'] = 'News category';
  $handler->display->display_options['filters']['field_ding_news_category_tid']['expose']['operator'] = 'field_ding_news_category_tid_op';
  $handler->display->display_options['filters']['field_ding_news_category_tid']['expose']['identifier'] = 'field_ding_news_category_tid';
  $handler->display->display_options['filters']['field_ding_news_category_tid']['expose']['multiple'] = TRUE;
  $handler->display->display_options['filters']['field_ding_news_category_tid']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
    4 => 0,
    5 => 0,
    6 => 0,
    7 => 0,
    8 => 0,
    9 => 0,
    10 => 0,
  );
  $handler->display->display_options['filters']['field_ding_news_category_tid']['type'] = 'select';
  $handler->display->display_options['filters']['field_ding_news_category_tid']['vocabulary'] = 'news_category';
  /* Filter criterion: Field: Library (og_group_ref) (reference filter) */
  $handler->display->display_options['filters']['og_group_ref_target_id_entityreference_filter']['id'] = 'og_group_ref_target_id_entityreference_filter';
  $handler->display->display_options['filters']['og_group_ref_target_id_entityreference_filter']['table'] = 'og_membership';
  $handler->display->display_options['filters']['og_group_ref_target_id_entityreference_filter']['field'] = 'og_group_ref_target_id_entityreference_filter';
  $handler->display->display_options['filters']['og_group_ref_target_id_entityreference_filter']['group'] = 1;
  $handler->display->display_options['filters']['og_group_ref_target_id_entityreference_filter']['exposed'] = TRUE;
  $handler->display->display_options['filters']['og_group_ref_target_id_entityreference_filter']['expose']['operator_id'] = 'og_group_ref_target_id_entityreference_filter_op';
  $handler->display->display_options['filters']['og_group_ref_target_id_entityreference_filter']['expose']['label'] = 'Select library';
  $handler->display->display_options['filters']['og_group_ref_target_id_entityreference_filter']['expose']['operator'] = 'og_group_ref_target_id_entityreference_filter_op';
  $handler->display->display_options['filters']['og_group_ref_target_id_entityreference_filter']['expose']['identifier'] = 'og_group_ref_target_id_entityreference_filter';
  $handler->display->display_options['filters']['og_group_ref_target_id_entityreference_filter']['expose']['multiple'] = TRUE;
  $handler->display->display_options['filters']['og_group_ref_target_id_entityreference_filter']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
    4 => 0,
    5 => 0,
    6 => 0,
    7 => 0,
    8 => 0,
    9 => 0,
    10 => 0,
  );
  $handler->display->display_options['filters']['og_group_ref_target_id_entityreference_filter']['reference_display'] = 'ding_news:news_libraries_list';
  $handler->display->display_options['pane_category']['name'] = 'News panes';
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
    'tid' => array(
      'type' => 'panel',
      'context' => 'entity:user.uid',
      'context_optional' => 0,
      'panel' => '0',
      'fixed' => '',
      'label' => 'Indhold: Har taksonomiterm ID',
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
  $handler->display->display_options['path'] = 'node/%/news/feed';
  $handler->display->display_options['displays'] = array(
    'default' => 0,
    'ding_news_frontpage_list' => 0,
    'ding_news_library_list' => 0,
    'ding_news_list' => 0,
    'ding_news_list_library' => 0,
    'panel_pane_2' => 0,
  );
  $handler->display->display_options['sitename_title'] = 1;

  /* Display: Feed */
  $handler = $view->new_display('feed', 'Feed', 'ding_news_feed');
  $handler->display->display_options['pager']['type'] = 'some';
  $handler->display->display_options['pager']['options']['items_per_page'] = '20';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['style_plugin'] = 'rss';
  $handler->display->display_options['row_plugin'] = 'node_rss';
  $handler->display->display_options['path'] = 'news/feed';
  $handler->display->display_options['displays'] = array(
    'default' => 0,
    'ding_news_frontpage_list' => 0,
    'ding_news_library_list' => 0,
    'ding_news_list' => 0,
    'ding_news_list_library' => 0,
    'panel_pane_2' => 0,
  );
  $handler->display->display_options['sitename_title'] = 1;

  /* Display: Simple news list */
  $handler = $view->new_display('panel_pane', 'Simple news list', 'panel_pane_2');
  $handler->display->display_options['defaults']['css_class'] = FALSE;
  $handler->display->display_options['css_class'] = 'news-list';
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Field: Date (excluded) */
  $handler->display->display_options['fields']['created']['id'] = 'created';
  $handler->display->display_options['fields']['created']['table'] = 'node';
  $handler->display->display_options['fields']['created']['field'] = 'created';
  $handler->display->display_options['fields']['created']['ui_name'] = 'Date (excluded)';
  $handler->display->display_options['fields']['created']['label'] = '';
  $handler->display->display_options['fields']['created']['element_type'] = 'span';
  $handler->display->display_options['fields']['created']['element_class'] = 'date';
  $handler->display->display_options['fields']['created']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['created']['element_default_classes'] = FALSE;
  $handler->display->display_options['fields']['created']['date_format'] = 'custom';
  $handler->display->display_options['fields']['created']['custom_date_format'] = 'j. M';
  /* Field: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['ui_name'] = 'Title';
  $handler->display->display_options['fields']['title']['label'] = '';
  $handler->display->display_options['fields']['title']['element_type'] = 'h3';
  $handler->display->display_options['fields']['title']['element_class'] = 'heading';
  $handler->display->display_options['fields']['title']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['title']['element_default_classes'] = FALSE;
  $handler->display->display_options['pane_category']['name'] = 'News panes';
  $handler->display->display_options['pane_category']['weight'] = '0';

  /* Display: News list (library) */
  $handler = $view->new_display('panel_pane', 'News list (library)', 'ding_news_list_library');
  $handler->display->display_options['defaults']['css_class'] = FALSE;
  $handler->display->display_options['defaults']['use_more'] = FALSE;
  $handler->display->display_options['defaults']['link_display'] = FALSE;
  $handler->display->display_options['link_display'] = 'custom_url';
  $handler->display->display_options['link_url'] = 'nyheder';
  $handler->display->display_options['defaults']['pager'] = FALSE;
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = '10';
  $handler->display->display_options['pager']['options']['offset'] = '';
  $handler->display->display_options['pager']['options']['id'] = '0';
  $handler->display->display_options['defaults']['style_plugin'] = FALSE;
  $handler->display->display_options['style_plugin'] = 'default';
  $handler->display->display_options['defaults']['style_options'] = FALSE;
  $handler->display->display_options['defaults']['row_plugin'] = FALSE;
  $handler->display->display_options['row_plugin'] = 'node';
  $handler->display->display_options['row_options']['links'] = FALSE;
  $handler->display->display_options['defaults']['row_options'] = FALSE;
  $handler->display->display_options['defaults']['relationships'] = FALSE;
  /* Relationship: OG membership: OG membership from Node */
  $handler->display->display_options['relationships']['og_membership_rel']['id'] = 'og_membership_rel';
  $handler->display->display_options['relationships']['og_membership_rel']['table'] = 'node';
  $handler->display->display_options['relationships']['og_membership_rel']['field'] = 'og_membership_rel';
  /* Relationship: OG membership: Group Node from OG membership */
  $handler->display->display_options['relationships']['og_membership_related_node_group']['id'] = 'og_membership_related_node_group';
  $handler->display->display_options['relationships']['og_membership_related_node_group']['table'] = 'og_membership';
  $handler->display->display_options['relationships']['og_membership_related_node_group']['field'] = 'og_membership_related_node_group';
  $handler->display->display_options['relationships']['og_membership_related_node_group']['relationship'] = 'og_membership_rel';
  $handler->display->display_options['relationships']['og_membership_related_node_group']['label'] = 'OG node group';
  /* Relationship: Content: Author */
  $handler->display->display_options['relationships']['uid']['id'] = 'uid';
  $handler->display->display_options['relationships']['uid']['table'] = 'node';
  $handler->display->display_options['relationships']['uid']['field'] = 'uid';
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Field: Image (list image) */
  $handler->display->display_options['fields']['field_ding_news_list_image']['id'] = 'field_ding_news_list_image';
  $handler->display->display_options['fields']['field_ding_news_list_image']['table'] = 'field_data_field_ding_news_list_image';
  $handler->display->display_options['fields']['field_ding_news_list_image']['field'] = 'field_ding_news_list_image';
  $handler->display->display_options['fields']['field_ding_news_list_image']['ui_name'] = 'Image (list image)';
  $handler->display->display_options['fields']['field_ding_news_list_image']['label'] = '';
  $handler->display->display_options['fields']['field_ding_news_list_image']['element_type'] = 'div';
  $handler->display->display_options['fields']['field_ding_news_list_image']['element_class'] = 'news-image-wrapper';
  $handler->display->display_options['fields']['field_ding_news_list_image']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_ding_news_list_image']['element_default_classes'] = FALSE;
  $handler->display->display_options['fields']['field_ding_news_list_image']['click_sort_column'] = 'fid';
  $handler->display->display_options['fields']['field_ding_news_list_image']['type'] = 'cs_adaptive_image';
  $handler->display->display_options['fields']['field_ding_news_list_image']['settings'] = array(
    'relationship' => 'none',
    'ui_name' => 'Image (list image)',
    'custom_label' => 0,
    'label' => '',
    'element_label_colon' => 0,
    'exclude' => 0,
    'element_type_enable' => 1,
    'element_type' => 'div',
    'element_class_enable' => 1,
    'element_class' => 'news-image-wrapper',
    'element_label_type_enable' => 0,
    'element_label_type' => '',
    'element_label_class_enable' => 0,
    'element_label_class' => '',
    'element_wrapper_type_enable' => 0,
    'element_wrapper_type' => '',
    'element_wrapper_class_enable' => 0,
    'element_wrapper_class' => '',
    'element_default_classes' => 0,
    'alter' => array(
      'alter_text' => 0,
      'text' => '',
      'make_link' => 0,
      'path' => '',
      'absolute' => 0,
      'replace_spaces' => 0,
      'external' => 0,
      'path_case' => 'none',
      'link_class' => '',
      'alt' => '',
      'rel' => '',
      'prefix' => '',
      'suffix' => '',
      'target' => '',
      'trim' => 0,
      'max_length' => '',
      'word_boundary' => 1,
      'ellipsis' => 1,
      'more_link' => 0,
      'more_link_text' => '',
      'more_link_path' => '',
      'html' => 0,
      'strip_tags' => 0,
      'preserve_tags' => '',
      'trim_whitespace' => 0,
      'nl2br' => 0,
    ),
    'empty' => '',
    'empty_zero' => 0,
    'hide_empty' => 0,
    'hide_alter_empty' => 1,
    'click_sort_column' => 'fid',
    'type' => 'cs_adaptive_image',
    'field_api_classes' => 0,
    'image_link' => 'content',
    'styles' => array(
      'breakpoint_1' => '768',
      'style_1' => 'ding_list_medium',
      'breakpoint_2' => '500',
      'style_2' => 'ding_list_small',
      'max_style' => 'ding_list_large',
      'fallback_style' => 'ding_list_large',
    ),
  );
  /* Field: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['ui_name'] = 'Title';
  $handler->display->display_options['fields']['title']['label'] = '';
  $handler->display->display_options['fields']['title']['element_type'] = 'h3';
  $handler->display->display_options['fields']['title']['element_class'] = 'news-heading';
  $handler->display->display_options['fields']['title']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['title']['element_default_classes'] = FALSE;
  /* Field: Category */
  $handler->display->display_options['fields']['field_ding_news_category']['id'] = 'field_ding_news_category';
  $handler->display->display_options['fields']['field_ding_news_category']['table'] = 'field_data_field_ding_news_category';
  $handler->display->display_options['fields']['field_ding_news_category']['field'] = 'field_ding_news_category';
  $handler->display->display_options['fields']['field_ding_news_category']['ui_name'] = 'Category';
  $handler->display->display_options['fields']['field_ding_news_category']['label'] = '';
  $handler->display->display_options['fields']['field_ding_news_category']['element_type'] = 'span';
  $handler->display->display_options['fields']['field_ding_news_category']['element_class'] = 'news-label';
  $handler->display->display_options['fields']['field_ding_news_category']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_ding_news_category']['element_wrapper_type'] = '0';
  $handler->display->display_options['fields']['field_ding_news_category']['element_default_classes'] = FALSE;
  /* Field: Date */
  $handler->display->display_options['fields']['created']['id'] = 'created';
  $handler->display->display_options['fields']['created']['table'] = 'node';
  $handler->display->display_options['fields']['created']['field'] = 'created';
  $handler->display->display_options['fields']['created']['ui_name'] = 'Date';
  $handler->display->display_options['fields']['created']['label'] = '';
  $handler->display->display_options['fields']['created']['element_type'] = 'span';
  $handler->display->display_options['fields']['created']['element_class'] = 'news-date';
  $handler->display->display_options['fields']['created']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['created']['element_wrapper_type'] = '0';
  $handler->display->display_options['fields']['created']['element_default_classes'] = FALSE;
  $handler->display->display_options['fields']['created']['date_format'] = 'ding_long_date_only';
  /* Field: Author */
  $handler->display->display_options['fields']['name']['id'] = 'name';
  $handler->display->display_options['fields']['name']['table'] = 'users';
  $handler->display->display_options['fields']['name']['field'] = 'name';
  $handler->display->display_options['fields']['name']['relationship'] = 'uid';
  $handler->display->display_options['fields']['name']['ui_name'] = 'Author';
  $handler->display->display_options['fields']['name']['label'] = '';
  $handler->display->display_options['fields']['name']['element_type'] = 'span';
  $handler->display->display_options['fields']['name']['element_class'] = 'news-author';
  $handler->display->display_options['fields']['name']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['name']['element_wrapper_type'] = '0';
  $handler->display->display_options['fields']['name']['element_default_classes'] = FALSE;
  /* Field: Lead */
  $handler->display->display_options['fields']['field_ding_news_lead']['id'] = 'field_ding_news_lead';
  $handler->display->display_options['fields']['field_ding_news_lead']['table'] = 'field_data_field_ding_news_lead';
  $handler->display->display_options['fields']['field_ding_news_lead']['field'] = 'field_ding_news_lead';
  $handler->display->display_options['fields']['field_ding_news_lead']['ui_name'] = 'Lead';
  $handler->display->display_options['fields']['field_ding_news_lead']['label'] = '';
  $handler->display->display_options['fields']['field_ding_news_lead']['element_type'] = 'p';
  $handler->display->display_options['fields']['field_ding_news_lead']['element_class'] = 'news-list-content';
  $handler->display->display_options['fields']['field_ding_news_lead']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_ding_news_lead']['element_wrapper_type'] = '0';
  $handler->display->display_options['fields']['field_ding_news_lead']['element_default_classes'] = FALSE;
  /* Field: Link (read more) */
  $handler->display->display_options['fields']['view_node']['id'] = 'view_node';
  $handler->display->display_options['fields']['view_node']['table'] = 'views_entity_node';
  $handler->display->display_options['fields']['view_node']['field'] = 'view_node';
  $handler->display->display_options['fields']['view_node']['ui_name'] = 'Link (read more)';
  $handler->display->display_options['fields']['view_node']['label'] = '';
  $handler->display->display_options['fields']['view_node']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['view_node']['element_wrapper_type'] = 'span';
  $handler->display->display_options['fields']['view_node']['element_wrapper_class'] = 'news-link';
  $handler->display->display_options['fields']['view_node']['element_default_classes'] = FALSE;
  $handler->display->display_options['fields']['view_node']['text'] = 'Read more';
  /* Field: Content: Link */
  $handler->display->display_options['fields']['view_node_1']['id'] = 'view_node_1';
  $handler->display->display_options['fields']['view_node_1']['table'] = 'views_entity_node';
  $handler->display->display_options['fields']['view_node_1']['field'] = 'view_node';
  $handler->display->display_options['fields']['view_node_1']['label'] = '';
  $handler->display->display_options['fields']['view_node_1']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['view_node_1']['alter']['text'] = '<i class="icon-chevron-right"></i>';
  $handler->display->display_options['fields']['view_node_1']['element_type'] = 'div';
  $handler->display->display_options['fields']['view_node_1']['element_class'] = 'news-arrow-link';
  $handler->display->display_options['fields']['view_node_1']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['view_node_1']['element_default_classes'] = FALSE;
  $handler->display->display_options['defaults']['arguments'] = FALSE;
  /* Contextual filter: OG membership: Group ID */
  $handler->display->display_options['arguments']['gid']['id'] = 'gid';
  $handler->display->display_options['arguments']['gid']['table'] = 'og_membership';
  $handler->display->display_options['arguments']['gid']['field'] = 'gid';
  $handler->display->display_options['arguments']['gid']['relationship'] = 'og_membership_rel';
  $handler->display->display_options['arguments']['gid']['default_action'] = 'empty';
  $handler->display->display_options['arguments']['gid']['default_argument_type'] = 'fixed';
  $handler->display->display_options['arguments']['gid']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['gid']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['gid']['summary_options']['items_per_page'] = '25';
  /* Contextual filter: Content: Has taxonomy term ID */
  $handler->display->display_options['arguments']['tid']['id'] = 'tid';
  $handler->display->display_options['arguments']['tid']['table'] = 'taxonomy_index';
  $handler->display->display_options['arguments']['tid']['field'] = 'tid';
  $handler->display->display_options['arguments']['tid']['default_argument_type'] = 'fixed';
  $handler->display->display_options['arguments']['tid']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['tid']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['tid']['summary_options']['items_per_page'] = '25';
  $handler->display->display_options['arguments']['tid']['specify_validation'] = TRUE;
  $handler->display->display_options['arguments']['tid']['validate']['type'] = 'taxonomy_term';
  $handler->display->display_options['arguments']['tid']['validate_options']['vocabularies'] = array(
    'news_category' => 'news_category',
  );
  $handler->display->display_options['pane_category']['name'] = 'Library panes';
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
    'gid' => array(
      'type' => 'context',
      'context' => 'entity:node.nid',
      'context_optional' => 0,
      'panel' => '0',
      'fixed' => '',
      'label' => 'OG membership: Group ID',
    ),
    'tid' => array(
      'type' => 'context',
      'context' => 'entity:taxonomy_term.tid',
      'context_optional' => 0,
      'panel' => '1',
      'fixed' => '',
      'label' => 'Indhold: Har taksonomiterm ID',
    ),
  );

  /* Display: User news simple list */
  $handler = $view->new_display('panel_pane', 'User news simple list', 'ding_news_simple_list_user');
  $handler->display->display_options['defaults']['title'] = FALSE;
  $handler->display->display_options['title'] = 'Latest news posts';
  $handler->display->display_options['defaults']['css_class'] = FALSE;
  $handler->display->display_options['css_class'] = 'news-list';
  $handler->display->display_options['display_description'] = 'simple news list by user';
  $handler->display->display_options['defaults']['pager'] = FALSE;
  $handler->display->display_options['pager']['type'] = 'mini';
  $handler->display->display_options['pager']['options']['items_per_page'] = '8';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['pager']['options']['id'] = '0';
  $handler->display->display_options['defaults']['style_plugin'] = FALSE;
  $handler->display->display_options['style_plugin'] = 'default';
  $handler->display->display_options['style_options']['row_class'] = 'simple-list-item';
  $handler->display->display_options['style_options']['default_row_class'] = FALSE;
  $handler->display->display_options['defaults']['style_options'] = FALSE;
  $handler->display->display_options['defaults']['row_plugin'] = FALSE;
  $handler->display->display_options['row_plugin'] = 'fields';
  $handler->display->display_options['row_options']['default_field_elements'] = FALSE;
  $handler->display->display_options['defaults']['row_options'] = FALSE;
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Field: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['ui_name'] = 'Title';
  $handler->display->display_options['fields']['title']['label'] = '';
  $handler->display->display_options['fields']['title']['element_type'] = '0';
  $handler->display->display_options['fields']['title']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['title']['element_default_classes'] = FALSE;
  $handler->display->display_options['defaults']['arguments'] = FALSE;
  /* Contextual filter: User: Uid */
  $handler->display->display_options['arguments']['uid']['id'] = 'uid';
  $handler->display->display_options['arguments']['uid']['table'] = 'users';
  $handler->display->display_options['arguments']['uid']['field'] = 'uid';
  $handler->display->display_options['arguments']['uid']['relationship'] = 'uid';
  $handler->display->display_options['arguments']['uid']['default_action'] = 'not found';
  $handler->display->display_options['arguments']['uid']['default_argument_type'] = 'fixed';
  $handler->display->display_options['arguments']['uid']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['uid']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['uid']['summary_options']['items_per_page'] = '25';
  $handler->display->display_options['pane_category']['name'] = 'News panes';
  $handler->display->display_options['pane_category']['weight'] = '0';
  $handler->display->display_options['argument_input'] = array(
    'uid' => array(
      'type' => 'context',
      'context' => 'entity:user.uid',
      'context_optional' => 0,
      'panel' => '0',
      'fixed' => '',
      'label' => 'Bruger: Uid',
    ),
  );

  /* Display: User news list */
  $handler = $view->new_display('panel_pane', 'User news list', 'ding_news_list_user');
  $handler->display->display_options['defaults']['title'] = FALSE;
  $handler->display->display_options['title'] = 'Latest news posts';
  $handler->display->display_options['defaults']['css_class'] = FALSE;
  $handler->display->display_options['display_description'] = 'news list by user';
  $handler->display->display_options['defaults']['use_more'] = FALSE;
  $handler->display->display_options['defaults']['use_more_always'] = FALSE;
  $handler->display->display_options['defaults']['use_more_always'] = FALSE;
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['defaults']['use_more_text'] = FALSE;
  $handler->display->display_options['use_more_text'] = 'See all news';
  $handler->display->display_options['defaults']['link_display'] = FALSE;
  $handler->display->display_options['link_display'] = 'custom_url';
  $handler->display->display_options['link_url'] = 'nyheder';
  $handler->display->display_options['defaults']['pager'] = FALSE;
  $handler->display->display_options['pager']['type'] = 'mini';
  $handler->display->display_options['pager']['options']['items_per_page'] = '8';
  $handler->display->display_options['pager']['options']['offset'] = '';
  $handler->display->display_options['pager']['options']['id'] = '0';
  $handler->display->display_options['defaults']['style_plugin'] = FALSE;
  $handler->display->display_options['style_plugin'] = 'default';
  $handler->display->display_options['defaults']['style_options'] = FALSE;
  $handler->display->display_options['defaults']['row_plugin'] = FALSE;
  $handler->display->display_options['row_plugin'] = 'node';
  $handler->display->display_options['defaults']['row_options'] = FALSE;
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Field: Image (list image) */
  $handler->display->display_options['fields']['field_ding_news_list_image']['id'] = 'field_ding_news_list_image';
  $handler->display->display_options['fields']['field_ding_news_list_image']['table'] = 'field_data_field_ding_news_list_image';
  $handler->display->display_options['fields']['field_ding_news_list_image']['field'] = 'field_ding_news_list_image';
  $handler->display->display_options['fields']['field_ding_news_list_image']['ui_name'] = 'Image (list image)';
  $handler->display->display_options['fields']['field_ding_news_list_image']['label'] = '';
  $handler->display->display_options['fields']['field_ding_news_list_image']['element_type'] = 'div';
  $handler->display->display_options['fields']['field_ding_news_list_image']['element_class'] = 'news-image-wrapper';
  $handler->display->display_options['fields']['field_ding_news_list_image']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_ding_news_list_image']['element_default_classes'] = FALSE;
  $handler->display->display_options['fields']['field_ding_news_list_image']['click_sort_column'] = 'fid';
  $handler->display->display_options['fields']['field_ding_news_list_image']['type'] = 'cs_adaptive_image';
  $handler->display->display_options['fields']['field_ding_news_list_image']['settings'] = array(
    'image_link' => 'content',
    'styles' => array(
      'breakpoint_1' => '768',
      'style_1' => 'ding_list_medium',
      'breakpoint_2' => '500',
      'style_2' => 'ding_list_small',
      'max_style' => 'ding_list_large',
      'fallback_style' => 'ding_list_large',
    ),
  );
  /* Field: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['ui_name'] = 'Title';
  $handler->display->display_options['fields']['title']['label'] = '';
  $handler->display->display_options['fields']['title']['element_type'] = 'h3';
  $handler->display->display_options['fields']['title']['element_class'] = 'news-heading';
  $handler->display->display_options['fields']['title']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['title']['element_default_classes'] = FALSE;
  /* Field: Category */
  $handler->display->display_options['fields']['field_ding_news_category']['id'] = 'field_ding_news_category';
  $handler->display->display_options['fields']['field_ding_news_category']['table'] = 'field_data_field_ding_news_category';
  $handler->display->display_options['fields']['field_ding_news_category']['field'] = 'field_ding_news_category';
  $handler->display->display_options['fields']['field_ding_news_category']['ui_name'] = 'Category';
  $handler->display->display_options['fields']['field_ding_news_category']['label'] = '';
  $handler->display->display_options['fields']['field_ding_news_category']['element_type'] = 'span';
  $handler->display->display_options['fields']['field_ding_news_category']['element_class'] = 'news-label';
  $handler->display->display_options['fields']['field_ding_news_category']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_ding_news_category']['element_wrapper_type'] = '0';
  $handler->display->display_options['fields']['field_ding_news_category']['element_default_classes'] = FALSE;
  /* Field: Date */
  $handler->display->display_options['fields']['created']['id'] = 'created';
  $handler->display->display_options['fields']['created']['table'] = 'node';
  $handler->display->display_options['fields']['created']['field'] = 'created';
  $handler->display->display_options['fields']['created']['ui_name'] = 'Date';
  $handler->display->display_options['fields']['created']['label'] = '';
  $handler->display->display_options['fields']['created']['element_type'] = 'span';
  $handler->display->display_options['fields']['created']['element_class'] = 'news-date';
  $handler->display->display_options['fields']['created']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['created']['element_wrapper_type'] = '0';
  $handler->display->display_options['fields']['created']['element_default_classes'] = FALSE;
  $handler->display->display_options['fields']['created']['date_format'] = 'ding_long_date_only';
  /* Field: Author */
  $handler->display->display_options['fields']['name']['id'] = 'name';
  $handler->display->display_options['fields']['name']['table'] = 'users';
  $handler->display->display_options['fields']['name']['field'] = 'name';
  $handler->display->display_options['fields']['name']['relationship'] = 'uid';
  $handler->display->display_options['fields']['name']['ui_name'] = 'Author';
  $handler->display->display_options['fields']['name']['label'] = '';
  $handler->display->display_options['fields']['name']['element_type'] = 'span';
  $handler->display->display_options['fields']['name']['element_class'] = 'news-author';
  $handler->display->display_options['fields']['name']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['name']['element_wrapper_type'] = '0';
  $handler->display->display_options['fields']['name']['element_default_classes'] = FALSE;
  /* Field: Lead */
  $handler->display->display_options['fields']['field_ding_news_lead']['id'] = 'field_ding_news_lead';
  $handler->display->display_options['fields']['field_ding_news_lead']['table'] = 'field_data_field_ding_news_lead';
  $handler->display->display_options['fields']['field_ding_news_lead']['field'] = 'field_ding_news_lead';
  $handler->display->display_options['fields']['field_ding_news_lead']['ui_name'] = 'Lead';
  $handler->display->display_options['fields']['field_ding_news_lead']['label'] = '';
  $handler->display->display_options['fields']['field_ding_news_lead']['element_type'] = 'p';
  $handler->display->display_options['fields']['field_ding_news_lead']['element_class'] = 'news-list-content';
  $handler->display->display_options['fields']['field_ding_news_lead']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_ding_news_lead']['element_wrapper_type'] = '0';
  $handler->display->display_options['fields']['field_ding_news_lead']['element_default_classes'] = FALSE;
  /* Field: Link (read more) */
  $handler->display->display_options['fields']['view_node']['id'] = 'view_node';
  $handler->display->display_options['fields']['view_node']['table'] = 'views_entity_node';
  $handler->display->display_options['fields']['view_node']['field'] = 'view_node';
  $handler->display->display_options['fields']['view_node']['ui_name'] = 'Link (read more)';
  $handler->display->display_options['fields']['view_node']['label'] = '';
  $handler->display->display_options['fields']['view_node']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['view_node']['element_wrapper_type'] = 'span';
  $handler->display->display_options['fields']['view_node']['element_wrapper_class'] = 'news-link';
  $handler->display->display_options['fields']['view_node']['element_default_classes'] = FALSE;
  $handler->display->display_options['fields']['view_node']['text'] = 'Read more';
  /* Field: Content: Link */
  $handler->display->display_options['fields']['view_node_1']['id'] = 'view_node_1';
  $handler->display->display_options['fields']['view_node_1']['table'] = 'views_entity_node';
  $handler->display->display_options['fields']['view_node_1']['field'] = 'view_node';
  $handler->display->display_options['fields']['view_node_1']['label'] = '';
  $handler->display->display_options['fields']['view_node_1']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['view_node_1']['alter']['text'] = '<i class="icon-chevron-right"></i>';
  $handler->display->display_options['fields']['view_node_1']['element_type'] = 'div';
  $handler->display->display_options['fields']['view_node_1']['element_class'] = 'news-arrow-link';
  $handler->display->display_options['fields']['view_node_1']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['view_node_1']['element_default_classes'] = FALSE;
  $handler->display->display_options['defaults']['arguments'] = FALSE;
  /* Contextual filter: User: Uid */
  $handler->display->display_options['arguments']['uid']['id'] = 'uid';
  $handler->display->display_options['arguments']['uid']['table'] = 'users';
  $handler->display->display_options['arguments']['uid']['field'] = 'uid';
  $handler->display->display_options['arguments']['uid']['relationship'] = 'uid';
  $handler->display->display_options['arguments']['uid']['default_action'] = 'not found';
  $handler->display->display_options['arguments']['uid']['default_argument_type'] = 'fixed';
  $handler->display->display_options['arguments']['uid']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['uid']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['uid']['summary_options']['items_per_page'] = '25';
  $handler->display->display_options['pane_category']['name'] = 'News panes';
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
    'uid' => array(
      'type' => 'context',
      'context' => 'entity:user.uid',
      'context_optional' => 0,
      'panel' => '0',
      'fixed' => '',
      'label' => 'Bruger: Uid',
    ),
  );

  /* Display: Groups news list */
  $handler = $view->new_display('panel_pane', 'Groups news list', 'ding_news_groups_list');
  $handler->display->display_options['defaults']['title'] = FALSE;
  $handler->display->display_options['title'] = 'Group news';
  $handler->display->display_options['defaults']['css_class'] = FALSE;
  $handler->display->display_options['defaults']['use_more'] = FALSE;
  $handler->display->display_options['use_more'] = TRUE;
  $handler->display->display_options['defaults']['use_more_always'] = FALSE;
  $handler->display->display_options['defaults']['use_more_always'] = FALSE;
  $handler->display->display_options['use_more_always'] = TRUE;
  $handler->display->display_options['defaults']['use_more_text'] = FALSE;
  $handler->display->display_options['use_more_text'] = 'See all news';
  $handler->display->display_options['defaults']['link_display'] = FALSE;
  $handler->display->display_options['link_display'] = 'custom_url';
  $handler->display->display_options['link_url'] = 'temaer/!1/nyheder';
  $handler->display->display_options['defaults']['pager'] = FALSE;
  $handler->display->display_options['pager']['type'] = 'some';
  $handler->display->display_options['pager']['options']['items_per_page'] = '6';
  $handler->display->display_options['pager']['options']['offset'] = '';
  $handler->display->display_options['defaults']['empty'] = FALSE;
  $handler->display->display_options['defaults']['relationships'] = FALSE;
  /* Relationship: OG membership: OG membership from Node */
  $handler->display->display_options['relationships']['og_membership_rel']['id'] = 'og_membership_rel';
  $handler->display->display_options['relationships']['og_membership_rel']['table'] = 'node';
  $handler->display->display_options['relationships']['og_membership_rel']['field'] = 'og_membership_rel';
  /* Relationship: OG membership: Group Node from OG membership */
  $handler->display->display_options['relationships']['og_membership_related_node_group']['id'] = 'og_membership_related_node_group';
  $handler->display->display_options['relationships']['og_membership_related_node_group']['table'] = 'og_membership';
  $handler->display->display_options['relationships']['og_membership_related_node_group']['field'] = 'og_membership_related_node_group';
  $handler->display->display_options['relationships']['og_membership_related_node_group']['relationship'] = 'og_membership_rel';
  $handler->display->display_options['relationships']['og_membership_related_node_group']['label'] = 'OG node group';
  /* Relationship: Content: Author */
  $handler->display->display_options['relationships']['uid']['id'] = 'uid';
  $handler->display->display_options['relationships']['uid']['table'] = 'node';
  $handler->display->display_options['relationships']['uid']['field'] = 'uid';
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Field: Image (list image) */
  $handler->display->display_options['fields']['field_ding_news_list_image']['id'] = 'field_ding_news_list_image';
  $handler->display->display_options['fields']['field_ding_news_list_image']['table'] = 'field_data_field_ding_news_list_image';
  $handler->display->display_options['fields']['field_ding_news_list_image']['field'] = 'field_ding_news_list_image';
  $handler->display->display_options['fields']['field_ding_news_list_image']['ui_name'] = 'Image (list image)';
  $handler->display->display_options['fields']['field_ding_news_list_image']['label'] = '';
  $handler->display->display_options['fields']['field_ding_news_list_image']['element_type'] = 'div';
  $handler->display->display_options['fields']['field_ding_news_list_image']['element_class'] = 'news-image-wrapper';
  $handler->display->display_options['fields']['field_ding_news_list_image']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_ding_news_list_image']['element_default_classes'] = FALSE;
  $handler->display->display_options['fields']['field_ding_news_list_image']['click_sort_column'] = 'fid';
  $handler->display->display_options['fields']['field_ding_news_list_image']['type'] = 'cs_adaptive_image';
  $handler->display->display_options['fields']['field_ding_news_list_image']['settings'] = array(
    'image_link' => 'content',
    'styles' => array(
      'breakpoint_1' => '768',
      'style_1' => 'ding_list_medium',
      'breakpoint_2' => '500',
      'style_2' => 'ding_list_small',
      'max_style' => 'ding_list_large',
      'fallback_style' => 'ding_list_large',
    ),
  );
  /* Field: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['ui_name'] = 'Title';
  $handler->display->display_options['fields']['title']['label'] = '';
  $handler->display->display_options['fields']['title']['element_type'] = 'h3';
  $handler->display->display_options['fields']['title']['element_class'] = 'news-heading';
  $handler->display->display_options['fields']['title']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['title']['element_default_classes'] = FALSE;
  /* Field: Category */
  $handler->display->display_options['fields']['field_ding_news_category']['id'] = 'field_ding_news_category';
  $handler->display->display_options['fields']['field_ding_news_category']['table'] = 'field_data_field_ding_news_category';
  $handler->display->display_options['fields']['field_ding_news_category']['field'] = 'field_ding_news_category';
  $handler->display->display_options['fields']['field_ding_news_category']['ui_name'] = 'Category';
  $handler->display->display_options['fields']['field_ding_news_category']['label'] = '';
  $handler->display->display_options['fields']['field_ding_news_category']['element_type'] = 'span';
  $handler->display->display_options['fields']['field_ding_news_category']['element_class'] = 'news-label';
  $handler->display->display_options['fields']['field_ding_news_category']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_ding_news_category']['element_wrapper_type'] = '0';
  $handler->display->display_options['fields']['field_ding_news_category']['element_default_classes'] = FALSE;
  /* Field: Date */
  $handler->display->display_options['fields']['created']['id'] = 'created';
  $handler->display->display_options['fields']['created']['table'] = 'node';
  $handler->display->display_options['fields']['created']['field'] = 'created';
  $handler->display->display_options['fields']['created']['ui_name'] = 'Date';
  $handler->display->display_options['fields']['created']['label'] = '';
  $handler->display->display_options['fields']['created']['element_type'] = 'span';
  $handler->display->display_options['fields']['created']['element_class'] = 'news-date';
  $handler->display->display_options['fields']['created']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['created']['element_wrapper_type'] = '0';
  $handler->display->display_options['fields']['created']['element_default_classes'] = FALSE;
  $handler->display->display_options['fields']['created']['date_format'] = 'ding_long_date_only';
  /* Field: Author */
  $handler->display->display_options['fields']['name']['id'] = 'name';
  $handler->display->display_options['fields']['name']['table'] = 'users';
  $handler->display->display_options['fields']['name']['field'] = 'name';
  $handler->display->display_options['fields']['name']['relationship'] = 'uid';
  $handler->display->display_options['fields']['name']['ui_name'] = 'Author';
  $handler->display->display_options['fields']['name']['label'] = '';
  $handler->display->display_options['fields']['name']['element_type'] = 'span';
  $handler->display->display_options['fields']['name']['element_class'] = 'news-author';
  $handler->display->display_options['fields']['name']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['name']['element_wrapper_type'] = '0';
  $handler->display->display_options['fields']['name']['element_default_classes'] = FALSE;
  /* Field: Lead */
  $handler->display->display_options['fields']['field_ding_news_lead']['id'] = 'field_ding_news_lead';
  $handler->display->display_options['fields']['field_ding_news_lead']['table'] = 'field_data_field_ding_news_lead';
  $handler->display->display_options['fields']['field_ding_news_lead']['field'] = 'field_ding_news_lead';
  $handler->display->display_options['fields']['field_ding_news_lead']['ui_name'] = 'Lead';
  $handler->display->display_options['fields']['field_ding_news_lead']['label'] = '';
  $handler->display->display_options['fields']['field_ding_news_lead']['element_type'] = 'p';
  $handler->display->display_options['fields']['field_ding_news_lead']['element_class'] = 'news-list-content';
  $handler->display->display_options['fields']['field_ding_news_lead']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_ding_news_lead']['element_wrapper_type'] = '0';
  $handler->display->display_options['fields']['field_ding_news_lead']['element_default_classes'] = FALSE;
  /* Field: Link (read more) */
  $handler->display->display_options['fields']['view_node']['id'] = 'view_node';
  $handler->display->display_options['fields']['view_node']['table'] = 'views_entity_node';
  $handler->display->display_options['fields']['view_node']['field'] = 'view_node';
  $handler->display->display_options['fields']['view_node']['ui_name'] = 'Link (read more)';
  $handler->display->display_options['fields']['view_node']['label'] = '';
  $handler->display->display_options['fields']['view_node']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['view_node']['element_wrapper_type'] = 'span';
  $handler->display->display_options['fields']['view_node']['element_wrapper_class'] = 'news-link';
  $handler->display->display_options['fields']['view_node']['element_default_classes'] = FALSE;
  $handler->display->display_options['fields']['view_node']['text'] = 'Read more';
  /* Field: Content: Link */
  $handler->display->display_options['fields']['view_node_1']['id'] = 'view_node_1';
  $handler->display->display_options['fields']['view_node_1']['table'] = 'views_entity_node';
  $handler->display->display_options['fields']['view_node_1']['field'] = 'view_node';
  $handler->display->display_options['fields']['view_node_1']['label'] = '';
  $handler->display->display_options['fields']['view_node_1']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['view_node_1']['alter']['text'] = '<i class="icon-chevron-right"></i>';
  $handler->display->display_options['fields']['view_node_1']['element_type'] = 'div';
  $handler->display->display_options['fields']['view_node_1']['element_class'] = 'news-arrow-link';
  $handler->display->display_options['fields']['view_node_1']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['view_node_1']['element_default_classes'] = FALSE;
  /* Field: OG membership: Group ID */
  $handler->display->display_options['fields']['gid']['id'] = 'gid';
  $handler->display->display_options['fields']['gid']['table'] = 'og_membership';
  $handler->display->display_options['fields']['gid']['field'] = 'gid';
  $handler->display->display_options['fields']['gid']['relationship'] = 'og_membership_rel';
  $handler->display->display_options['fields']['gid']['label'] = '';
  $handler->display->display_options['fields']['gid']['exclude'] = TRUE;
  $handler->display->display_options['fields']['gid']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['gid']['separator'] = '';
  $handler->display->display_options['defaults']['arguments'] = FALSE;
  /* Contextual filter: OG membership: Group ID */
  $handler->display->display_options['arguments']['gid']['id'] = 'gid';
  $handler->display->display_options['arguments']['gid']['table'] = 'og_membership';
  $handler->display->display_options['arguments']['gid']['field'] = 'gid';
  $handler->display->display_options['arguments']['gid']['relationship'] = 'og_membership_rel';
  $handler->display->display_options['arguments']['gid']['default_action'] = 'empty';
  $handler->display->display_options['arguments']['gid']['default_argument_type'] = 'fixed';
  $handler->display->display_options['arguments']['gid']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['gid']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['gid']['summary_options']['items_per_page'] = '25';
  $handler->display->display_options['pane_category']['name'] = 'Groups panes';
  $handler->display->display_options['pane_category']['weight'] = '0';
  $handler->display->display_options['allow']['use_pager'] = 0;
  $handler->display->display_options['allow']['items_per_page'] = 0;
  $handler->display->display_options['allow']['offset'] = 0;
  $handler->display->display_options['allow']['link_to_view'] = 0;
  $handler->display->display_options['allow']['more_link'] = 0;
  $handler->display->display_options['allow']['path_override'] = 0;
  $handler->display->display_options['allow']['title_override'] = 'title_override';
  $handler->display->display_options['allow']['exposed_form'] = 'exposed_form';
  $handler->display->display_options['allow']['fields_override'] = 0;
  $handler->display->display_options['argument_input'] = array(
    'gid' => array(
      'type' => 'context',
      'context' => 'entity:node.nid',
      'context_optional' => 0,
      'panel' => '0',
      'fixed' => '',
      'label' => 'OG membership: Group ID',
    ),
  );

  /* Display: News list (groups) */
  $handler = $view->new_display('panel_pane', 'News list (groups)', 'panel_pane_1');
  $handler->display->display_options['defaults']['title'] = FALSE;
  $handler->display->display_options['title'] = 'Group news';
  $handler->display->display_options['defaults']['css_class'] = FALSE;
  $handler->display->display_options['defaults']['use_more'] = FALSE;
  $handler->display->display_options['defaults']['link_display'] = FALSE;
  $handler->display->display_options['link_display'] = 'custom_url';
  $handler->display->display_options['link_url'] = 'nyheder';
  $handler->display->display_options['defaults']['pager'] = FALSE;
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = '10';
  $handler->display->display_options['pager']['options']['offset'] = '';
  $handler->display->display_options['pager']['options']['id'] = '0';
  $handler->display->display_options['defaults']['style_plugin'] = FALSE;
  $handler->display->display_options['style_plugin'] = 'default';
  $handler->display->display_options['defaults']['style_options'] = FALSE;
  $handler->display->display_options['defaults']['row_plugin'] = FALSE;
  $handler->display->display_options['row_plugin'] = 'node';
  $handler->display->display_options['row_options']['links'] = FALSE;
  $handler->display->display_options['defaults']['row_options'] = FALSE;
  $handler->display->display_options['defaults']['relationships'] = FALSE;
  /* Relationship: OG membership: OG membership from Node */
  $handler->display->display_options['relationships']['og_membership_rel']['id'] = 'og_membership_rel';
  $handler->display->display_options['relationships']['og_membership_rel']['table'] = 'node';
  $handler->display->display_options['relationships']['og_membership_rel']['field'] = 'og_membership_rel';
  /* Relationship: OG membership: Group Node from OG membership */
  $handler->display->display_options['relationships']['og_membership_related_node_group']['id'] = 'og_membership_related_node_group';
  $handler->display->display_options['relationships']['og_membership_related_node_group']['table'] = 'og_membership';
  $handler->display->display_options['relationships']['og_membership_related_node_group']['field'] = 'og_membership_related_node_group';
  $handler->display->display_options['relationships']['og_membership_related_node_group']['relationship'] = 'og_membership_rel';
  $handler->display->display_options['relationships']['og_membership_related_node_group']['label'] = 'OG node group';
  /* Relationship: Content: Author */
  $handler->display->display_options['relationships']['uid']['id'] = 'uid';
  $handler->display->display_options['relationships']['uid']['table'] = 'node';
  $handler->display->display_options['relationships']['uid']['field'] = 'uid';
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Field: Image (list image) */
  $handler->display->display_options['fields']['field_ding_news_list_image']['id'] = 'field_ding_news_list_image';
  $handler->display->display_options['fields']['field_ding_news_list_image']['table'] = 'field_data_field_ding_news_list_image';
  $handler->display->display_options['fields']['field_ding_news_list_image']['field'] = 'field_ding_news_list_image';
  $handler->display->display_options['fields']['field_ding_news_list_image']['ui_name'] = 'Image (list image)';
  $handler->display->display_options['fields']['field_ding_news_list_image']['label'] = '';
  $handler->display->display_options['fields']['field_ding_news_list_image']['element_type'] = 'div';
  $handler->display->display_options['fields']['field_ding_news_list_image']['element_class'] = 'news-image-wrapper';
  $handler->display->display_options['fields']['field_ding_news_list_image']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_ding_news_list_image']['element_default_classes'] = FALSE;
  $handler->display->display_options['fields']['field_ding_news_list_image']['click_sort_column'] = 'fid';
  $handler->display->display_options['fields']['field_ding_news_list_image']['type'] = 'cs_adaptive_image';
  $handler->display->display_options['fields']['field_ding_news_list_image']['settings'] = array(
    'relationship' => 'none',
    'ui_name' => 'Image (list image)',
    'custom_label' => 0,
    'label' => '',
    'element_label_colon' => 0,
    'exclude' => 0,
    'element_type_enable' => 1,
    'element_type' => 'div',
    'element_class_enable' => 1,
    'element_class' => 'news-image-wrapper',
    'element_label_type_enable' => 0,
    'element_label_type' => '',
    'element_label_class_enable' => 0,
    'element_label_class' => '',
    'element_wrapper_type_enable' => 0,
    'element_wrapper_type' => '',
    'element_wrapper_class_enable' => 0,
    'element_wrapper_class' => '',
    'element_default_classes' => 0,
    'alter' => array(
      'alter_text' => 0,
      'text' => '',
      'make_link' => 0,
      'path' => '',
      'absolute' => 0,
      'replace_spaces' => 0,
      'external' => 0,
      'path_case' => 'none',
      'link_class' => '',
      'alt' => '',
      'rel' => '',
      'prefix' => '',
      'suffix' => '',
      'target' => '',
      'trim' => 0,
      'max_length' => '',
      'word_boundary' => 1,
      'ellipsis' => 1,
      'more_link' => 0,
      'more_link_text' => '',
      'more_link_path' => '',
      'html' => 0,
      'strip_tags' => 0,
      'preserve_tags' => '',
      'trim_whitespace' => 0,
      'nl2br' => 0,
    ),
    'empty' => '',
    'empty_zero' => 0,
    'hide_empty' => 0,
    'hide_alter_empty' => 1,
    'click_sort_column' => 'fid',
    'type' => 'cs_adaptive_image',
    'field_api_classes' => 0,
    'image_link' => 'content',
    'styles' => array(
      'breakpoint_1' => '768',
      'style_1' => 'ding_list_medium',
      'breakpoint_2' => '500',
      'style_2' => 'ding_list_small',
      'max_style' => 'ding_list_large',
      'fallback_style' => 'ding_list_large',
    ),
  );
  /* Field: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['ui_name'] = 'Title';
  $handler->display->display_options['fields']['title']['label'] = '';
  $handler->display->display_options['fields']['title']['element_type'] = 'h3';
  $handler->display->display_options['fields']['title']['element_class'] = 'news-heading';
  $handler->display->display_options['fields']['title']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['title']['element_default_classes'] = FALSE;
  /* Field: Category */
  $handler->display->display_options['fields']['field_ding_news_category']['id'] = 'field_ding_news_category';
  $handler->display->display_options['fields']['field_ding_news_category']['table'] = 'field_data_field_ding_news_category';
  $handler->display->display_options['fields']['field_ding_news_category']['field'] = 'field_ding_news_category';
  $handler->display->display_options['fields']['field_ding_news_category']['ui_name'] = 'Category';
  $handler->display->display_options['fields']['field_ding_news_category']['label'] = '';
  $handler->display->display_options['fields']['field_ding_news_category']['element_type'] = 'span';
  $handler->display->display_options['fields']['field_ding_news_category']['element_class'] = 'news-label';
  $handler->display->display_options['fields']['field_ding_news_category']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_ding_news_category']['element_wrapper_type'] = '0';
  $handler->display->display_options['fields']['field_ding_news_category']['element_default_classes'] = FALSE;
  /* Field: Date */
  $handler->display->display_options['fields']['created']['id'] = 'created';
  $handler->display->display_options['fields']['created']['table'] = 'node';
  $handler->display->display_options['fields']['created']['field'] = 'created';
  $handler->display->display_options['fields']['created']['ui_name'] = 'Date';
  $handler->display->display_options['fields']['created']['label'] = '';
  $handler->display->display_options['fields']['created']['element_type'] = 'span';
  $handler->display->display_options['fields']['created']['element_class'] = 'news-date';
  $handler->display->display_options['fields']['created']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['created']['element_wrapper_type'] = '0';
  $handler->display->display_options['fields']['created']['element_default_classes'] = FALSE;
  $handler->display->display_options['fields']['created']['date_format'] = 'ding_long_date_only';
  /* Field: Author */
  $handler->display->display_options['fields']['name']['id'] = 'name';
  $handler->display->display_options['fields']['name']['table'] = 'users';
  $handler->display->display_options['fields']['name']['field'] = 'name';
  $handler->display->display_options['fields']['name']['relationship'] = 'uid';
  $handler->display->display_options['fields']['name']['ui_name'] = 'Author';
  $handler->display->display_options['fields']['name']['label'] = '';
  $handler->display->display_options['fields']['name']['element_type'] = 'span';
  $handler->display->display_options['fields']['name']['element_class'] = 'news-author';
  $handler->display->display_options['fields']['name']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['name']['element_wrapper_type'] = '0';
  $handler->display->display_options['fields']['name']['element_default_classes'] = FALSE;
  /* Field: Lead */
  $handler->display->display_options['fields']['field_ding_news_lead']['id'] = 'field_ding_news_lead';
  $handler->display->display_options['fields']['field_ding_news_lead']['table'] = 'field_data_field_ding_news_lead';
  $handler->display->display_options['fields']['field_ding_news_lead']['field'] = 'field_ding_news_lead';
  $handler->display->display_options['fields']['field_ding_news_lead']['ui_name'] = 'Lead';
  $handler->display->display_options['fields']['field_ding_news_lead']['label'] = '';
  $handler->display->display_options['fields']['field_ding_news_lead']['element_type'] = 'p';
  $handler->display->display_options['fields']['field_ding_news_lead']['element_class'] = 'news-list-content';
  $handler->display->display_options['fields']['field_ding_news_lead']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_ding_news_lead']['element_wrapper_type'] = '0';
  $handler->display->display_options['fields']['field_ding_news_lead']['element_default_classes'] = FALSE;
  /* Field: Link (read more) */
  $handler->display->display_options['fields']['view_node']['id'] = 'view_node';
  $handler->display->display_options['fields']['view_node']['table'] = 'views_entity_node';
  $handler->display->display_options['fields']['view_node']['field'] = 'view_node';
  $handler->display->display_options['fields']['view_node']['ui_name'] = 'Link (read more)';
  $handler->display->display_options['fields']['view_node']['label'] = '';
  $handler->display->display_options['fields']['view_node']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['view_node']['element_wrapper_type'] = 'span';
  $handler->display->display_options['fields']['view_node']['element_wrapper_class'] = 'news-link';
  $handler->display->display_options['fields']['view_node']['element_default_classes'] = FALSE;
  $handler->display->display_options['fields']['view_node']['text'] = 'Read more';
  /* Field: Content: Link */
  $handler->display->display_options['fields']['view_node_1']['id'] = 'view_node_1';
  $handler->display->display_options['fields']['view_node_1']['table'] = 'views_entity_node';
  $handler->display->display_options['fields']['view_node_1']['field'] = 'view_node';
  $handler->display->display_options['fields']['view_node_1']['label'] = '';
  $handler->display->display_options['fields']['view_node_1']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['view_node_1']['alter']['text'] = '<i class="icon-chevron-right"></i>';
  $handler->display->display_options['fields']['view_node_1']['element_type'] = 'div';
  $handler->display->display_options['fields']['view_node_1']['element_class'] = 'news-arrow-link';
  $handler->display->display_options['fields']['view_node_1']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['view_node_1']['element_default_classes'] = FALSE;
  $handler->display->display_options['defaults']['arguments'] = FALSE;
  /* Contextual filter: OG membership: Group ID */
  $handler->display->display_options['arguments']['gid']['id'] = 'gid';
  $handler->display->display_options['arguments']['gid']['table'] = 'og_membership';
  $handler->display->display_options['arguments']['gid']['field'] = 'gid';
  $handler->display->display_options['arguments']['gid']['relationship'] = 'og_membership_rel';
  $handler->display->display_options['arguments']['gid']['default_action'] = 'empty';
  $handler->display->display_options['arguments']['gid']['default_argument_type'] = 'fixed';
  $handler->display->display_options['arguments']['gid']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['gid']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['gid']['summary_options']['items_per_page'] = '25';
  /* Contextual filter: Content: Has taxonomy term ID */
  $handler->display->display_options['arguments']['tid']['id'] = 'tid';
  $handler->display->display_options['arguments']['tid']['table'] = 'taxonomy_index';
  $handler->display->display_options['arguments']['tid']['field'] = 'tid';
  $handler->display->display_options['arguments']['tid']['default_argument_type'] = 'taxonomy_tid';
  $handler->display->display_options['arguments']['tid']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['tid']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['tid']['summary_options']['items_per_page'] = '25';
  $handler->display->display_options['pane_category']['name'] = 'Groups panes';
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
    'gid' => array(
      'type' => 'context',
      'context' => 'entity:node.nid',
      'context_optional' => 0,
      'panel' => '0',
      'fixed' => '',
      'label' => 'OG membership: Group ID',
    ),
    'tid' => array(
      'type' => 'context',
      'context' => 'entity:taxonomy_term.tid',
      'context_optional' => 0,
      'panel' => '1',
      'fixed' => '',
      'label' => 'Indhold: Har taksonomiterm ID',
    ),
  );

  /* Display: News Image Crop list */
  $handler = $view->new_display('page', 'News Image Crop list', 'ding_news_imagecrop_list');
  $handler->display->display_options['defaults']['title'] = FALSE;
  $handler->display->display_options['title'] = 'News Image Crop Overview';
  $handler->display->display_options['defaults']['css_class'] = FALSE;
  $handler->display->display_options['css_class'] = 'news-list imagecrop-list';
  $handler->display->display_options['defaults']['access'] = FALSE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['access']['perm'] = 'edit any ding_news content';
  $handler->display->display_options['defaults']['pager'] = FALSE;
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = '30';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['pager']['options']['id'] = '0';
  $handler->display->display_options['pager']['options']['quantity'] = '9';
  $handler->display->display_options['defaults']['style_plugin'] = FALSE;
  $handler->display->display_options['style_plugin'] = 'table';
  $handler->display->display_options['style_options']['columns'] = array(
    'field_ding_news_category' => 'field_ding_news_category',
    'created' => 'created',
    'name' => 'name',
    'title' => 'title',
    'nothing' => 'nothing',
    'field_ding_news_list_image' => 'field_ding_news_list_image',
    'field_ding_news_lead' => 'field_ding_news_lead',
    'view_node' => 'view_node',
  );
  $handler->display->display_options['style_options']['default'] = '-1';
  $handler->display->display_options['style_options']['info'] = array(
    'field_ding_news_category' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'created' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'name' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'title' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'nothing' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_ding_news_list_image' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_ding_news_lead' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'view_node' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
  );
  $handler->display->display_options['defaults']['style_options'] = FALSE;
  $handler->display->display_options['defaults']['row_plugin'] = FALSE;
  $handler->display->display_options['defaults']['row_options'] = FALSE;
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Field: News title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['ui_name'] = 'News title';
  $handler->display->display_options['fields']['title']['label'] = '';
  $handler->display->display_options['fields']['title']['element_type'] = 'h3';
  $handler->display->display_options['fields']['title']['element_class'] = 'news-heading';
  $handler->display->display_options['fields']['title']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['title']['element_default_classes'] = FALSE;
  /* Field: Content: Edit link */
  $handler->display->display_options['fields']['edit_node']['id'] = 'edit_node';
  $handler->display->display_options['fields']['edit_node']['table'] = 'views_entity_node';
  $handler->display->display_options['fields']['edit_node']['field'] = 'edit_node';
  $handler->display->display_options['fields']['edit_node']['label'] = 'Edit';
  $handler->display->display_options['fields']['edit_node']['element_label_colon'] = FALSE;
  /* Field: Content: List image */
  $handler->display->display_options['fields']['field_ding_news_list_image']['id'] = 'field_ding_news_list_image';
  $handler->display->display_options['fields']['field_ding_news_list_image']['table'] = 'field_data_field_ding_news_list_image';
  $handler->display->display_options['fields']['field_ding_news_list_image']['field'] = 'field_ding_news_list_image';
  $handler->display->display_options['fields']['field_ding_news_list_image']['label'] = 'Original Image';
  $handler->display->display_options['fields']['field_ding_news_list_image']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_ding_news_list_image']['click_sort_column'] = 'fid';
  $handler->display->display_options['fields']['field_ding_news_list_image']['settings'] = array(
    'image_style' => '',
    'image_link' => '',
  );
  /* Field: Content: List image */
  $handler->display->display_options['fields']['field_ding_news_list_image_1']['id'] = 'field_ding_news_list_image_1';
  $handler->display->display_options['fields']['field_ding_news_list_image_1']['table'] = 'field_data_field_ding_news_list_image';
  $handler->display->display_options['fields']['field_ding_news_list_image_1']['field'] = 'field_ding_news_list_image';
  $handler->display->display_options['fields']['field_ding_news_list_image_1']['label'] = 'Cropped image';
  $handler->display->display_options['fields']['field_ding_news_list_image_1']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_ding_news_list_image_1']['click_sort_column'] = 'fid';
  $handler->display->display_options['fields']['field_ding_news_list_image_1']['settings'] = array(
    'image_style' => 'ding_panorama_list_large',
    'image_link' => '',
  );
  $handler->display->display_options['path'] = 'news-imagecrop';

  /* Display: News: Libraries list */
  $handler = $view->new_display('entityreference', 'News: Libraries list', 'news_libraries_list');
  $handler->display->display_options['defaults']['title'] = FALSE;
  $handler->display->display_options['defaults']['css_class'] = FALSE;
  $handler->display->display_options['pager']['type'] = 'some';
  $handler->display->display_options['defaults']['style_plugin'] = FALSE;
  $handler->display->display_options['style_plugin'] = 'entityreference_style';
  $handler->display->display_options['style_options']['search_fields'] = array(
    'title' => 'title',
    'field_ding_news_category' => 0,
    'created' => 0,
    'name' => 0,
    'nothing' => 0,
    'field_ding_news_list_image' => 0,
    'field_ding_news_lead' => 0,
    'view_node' => 0,
  );
  $handler->display->display_options['defaults']['style_options'] = FALSE;
  $handler->display->display_options['defaults']['row_plugin'] = FALSE;
  $handler->display->display_options['row_plugin'] = 'entityreference_fields';
  $handler->display->display_options['defaults']['row_options'] = FALSE;
  $handler->display->display_options['defaults']['relationships'] = FALSE;
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Field: News title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['ui_name'] = 'News title';
  $handler->display->display_options['fields']['title']['label'] = '';
  $handler->display->display_options['fields']['title']['element_type'] = 'h3';
  $handler->display->display_options['fields']['title']['element_class'] = 'news-heading';
  $handler->display->display_options['fields']['title']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['title']['element_default_classes'] = FALSE;
  $handler->display->display_options['defaults']['sorts'] = FALSE;
  $handler->display->display_options['defaults']['arguments'] = FALSE;
  $handler->display->display_options['defaults']['filter_groups'] = FALSE;
  $handler->display->display_options['filter_groups']['groups'] = array(
    1 => 'AND',
    2 => 'OR',
  );
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
    'ding_library' => 'ding_library',
  );
  $handler->display->display_options['filters']['type']['group'] = 1;
  $translatables['ding_news'] = array(
    t('Master'),
    t('Library news'),
    t('See all news'),
    t('Apply'),
    t('Reset'),
    t('Sort by'),
    t('Asc'),
    t('Desc'),
    t('Empty text'),
    t('No news were found.'),
    t('author'),
    t('<span class="news-label">[field_ding_news_category]</span> <span class="news-date">[created]</span>  |  <span class="news-author">af [name]</span>'),
    t('Read more'),
    t('All'),
    t('News list (frontpage)'),
    t('<i class="icon-chevron-right"></i>'),
    t('News panes'),
    t('Library news list'),
    t('OG membership from node'),
    t('OG node group'),
    t('Library panes'),
    t('News list'),
    t('more'),
    t('Select any filter and click on Apply to see results'),
    t('Advanced options'),
    t('Items per page'),
    t('- All -'),
    t('Offset'),
    t('« first'),
    t('‹ previous'),
    t('next ›'),
    t('last »'),
    t('term from field_ding_news_category'),
    t('News category'),
    t('Select library'),
    t('Library Feed'),
    t('Feed'),
    t('Simple news list'),
    t('News list (library)'),
    t('User news simple list'),
    t('Latest news posts'),
    t('simple news list by user'),
    t('User news list'),
    t('news list by user'),
    t('Groups news list'),
    t('Group news'),
    t('.'),
    t('Groups panes'),
    t('News list (groups)'),
    t('News Image Crop list'),
    t('News Image Crop Overview'),
    t('Edit'),
    t('Original Image'),
    t('Cropped image'),
    t('News: Libraries list'),
  );
  $export['ding_news'] = $view;

  $view = new view();
  $view->name = 'ding_node';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'node';
  $view->human_name = 'Ding node';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'News and events';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'some';
  $handler->display->display_options['pager']['options']['items_per_page'] = '6';
  $handler->display->display_options['style_plugin'] = 'default';
  $handler->display->display_options['row_plugin'] = 'node';
  $handler->display->display_options['row_options']['links'] = FALSE;
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
  /* Filter criterion: Content: Type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'node';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'ding_event' => 'ding_event',
    'ding_news' => 'ding_news',
  );
  /* Filter criterion: Content: Promoted to front page */
  $handler->display->display_options['filters']['promote']['id'] = 'promote';
  $handler->display->display_options['filters']['promote']['table'] = 'node';
  $handler->display->display_options['filters']['promote']['field'] = 'promote';
  $handler->display->display_options['filters']['promote']['value'] = '1';

  /* Display: Content pane */
  $handler = $view->new_display('panel_pane', 'Content pane', 'panel_pane_ding_node');
  $handler->display->display_options['allow']['use_pager'] = 0;
  $handler->display->display_options['allow']['items_per_page'] = 0;
  $handler->display->display_options['allow']['offset'] = 0;
  $handler->display->display_options['allow']['link_to_view'] = 0;
  $handler->display->display_options['allow']['more_link'] = 0;
  $handler->display->display_options['allow']['path_override'] = 0;
  $handler->display->display_options['allow']['title_override'] = 'title_override';
  $handler->display->display_options['allow']['exposed_form'] = 0;
  $handler->display->display_options['allow']['fields_override'] = 0;
  $translatables['ding_node'] = array(
    t('Master'),
    t('News and events'),
    t('more'),
    t('Apply'),
    t('Reset'),
    t('Sort by'),
    t('Asc'),
    t('Desc'),
    t('Content pane'),
    t('View panes'),
  );
  $export['ding_node'] = $view;

  return $export;
}
