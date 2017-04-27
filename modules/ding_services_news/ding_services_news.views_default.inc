<?php
/**
 * @file
 * ding_services_news.views_default.inc
 */

/**
 * Implements hook_views_default_views().
 */
function ding_services_news_views_default_views() {
  $export = array();

  $view = new view();
  $view->name = 'ding_news_services';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'node';
  $view->human_name = 'Ding news services';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['use_more_text'] = 'mere';
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['exposed_form']['options']['submit_button'] = 'Udfør';
  $handler->display->display_options['exposed_form']['options']['reset_button_label'] = 'Gendan';
  $handler->display->display_options['exposed_form']['options']['exposed_sorts_label'] = 'Sortér efter';
  $handler->display->display_options['exposed_form']['options']['sort_asc_label'] = 'Stigende';
  $handler->display->display_options['exposed_form']['options']['sort_desc_label'] = 'Faldende';
  $handler->display->display_options['pager']['type'] = 'some';
  $handler->display->display_options['pager']['options']['items_per_page'] = '10';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['style_plugin'] = 'default';
  $handler->display->display_options['row_plugin'] = 'fields';
  /* Forbindelse: Entity Reference: Refereret entity */
  $handler->display->display_options['relationships']['og_group_ref_target_id']['id'] = 'og_group_ref_target_id';
  $handler->display->display_options['relationships']['og_group_ref_target_id']['table'] = 'og_membership';
  $handler->display->display_options['relationships']['og_group_ref_target_id']['field'] = 'og_group_ref_target_id';
  /* Felt: Indhold: Titel */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = 'title';
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['title']['alter']['ellipsis'] = FALSE;
  /* Felt: Indhold: Nid */
  $handler->display->display_options['fields']['nid']['id'] = 'nid';
  $handler->display->display_options['fields']['nid']['table'] = 'node';
  $handler->display->display_options['fields']['nid']['field'] = 'nid';
  $handler->display->display_options['fields']['nid']['label'] = 'nid';
  $handler->display->display_options['fields']['nid']['element_label_colon'] = FALSE;
  /* Felt: Indhold: Body */
  $handler->display->display_options['fields']['field_ding_news_body']['id'] = 'field_ding_news_body';
  $handler->display->display_options['fields']['field_ding_news_body']['table'] = 'field_data_field_ding_news_body';
  $handler->display->display_options['fields']['field_ding_news_body']['field'] = 'field_ding_news_body';
  $handler->display->display_options['fields']['field_ding_news_body']['label'] = 'description';
  /* Felt: Indhold: Category */
  $handler->display->display_options['fields']['field_ding_news_category']['id'] = 'field_ding_news_category';
  $handler->display->display_options['fields']['field_ding_news_category']['table'] = 'field_data_field_ding_news_category';
  $handler->display->display_options['fields']['field_ding_news_category']['field'] = 'field_ding_news_category';
  $handler->display->display_options['fields']['field_ding_news_category']['label'] = 'category';
  $handler->display->display_options['fields']['field_ding_news_category']['type'] = 'taxonomy_term_reference_plain';
  /* Felt: Indhold: Files */
  $handler->display->display_options['fields']['field_ding_news_files']['id'] = 'field_ding_news_files';
  $handler->display->display_options['fields']['field_ding_news_files']['table'] = 'field_data_field_ding_news_files';
  $handler->display->display_options['fields']['field_ding_news_files']['field'] = 'field_ding_news_files';
  $handler->display->display_options['fields']['field_ding_news_files']['label'] = 'files';
  $handler->display->display_options['fields']['field_ding_news_files']['click_sort_column'] = 'fid';
  $handler->display->display_options['fields']['field_ding_news_files']['type'] = 'file_url_plain';
  $handler->display->display_options['fields']['field_ding_news_files']['delta_offset'] = '0';
  /* Felt: Indhold: Groups */
  $handler->display->display_options['fields']['ding_news_groups_ref']['id'] = 'ding_news_groups_ref';
  $handler->display->display_options['fields']['ding_news_groups_ref']['table'] = 'og_membership';
  $handler->display->display_options['fields']['ding_news_groups_ref']['field'] = 'ding_news_groups_ref';
  $handler->display->display_options['fields']['ding_news_groups_ref']['label'] = 'groups';
  $handler->display->display_options['fields']['ding_news_groups_ref']['settings'] = array(
    'link' => 0,
  );
  $handler->display->display_options['fields']['ding_news_groups_ref']['delta_offset'] = '0';
  /* Felt: Indhold: Lead */
  $handler->display->display_options['fields']['field_ding_news_lead']['id'] = 'field_ding_news_lead';
  $handler->display->display_options['fields']['field_ding_news_lead']['table'] = 'field_data_field_ding_news_lead';
  $handler->display->display_options['fields']['field_ding_news_lead']['field'] = 'field_ding_news_lead';
  $handler->display->display_options['fields']['field_ding_news_lead']['label'] = 'lead';
  /* Felt: Indhold: List image */
  $handler->display->display_options['fields']['field_ding_news_list_image']['id'] = 'field_ding_news_list_image';
  $handler->display->display_options['fields']['field_ding_news_list_image']['table'] = 'field_data_field_ding_news_list_image';
  $handler->display->display_options['fields']['field_ding_news_list_image']['field'] = 'field_ding_news_list_image';
  $handler->display->display_options['fields']['field_ding_news_list_image']['label'] = 'list image';
  $handler->display->display_options['fields']['field_ding_news_list_image']['click_sort_column'] = 'fid';
  $handler->display->display_options['fields']['field_ding_news_list_image']['settings'] = array(
    'image_style' => '',
    'image_link' => 'file',
  );
  /* Felt: Indhold: Tags */
  $handler->display->display_options['fields']['field_ding_news_tags']['id'] = 'field_ding_news_tags';
  $handler->display->display_options['fields']['field_ding_news_tags']['table'] = 'field_data_field_ding_news_tags';
  $handler->display->display_options['fields']['field_ding_news_tags']['field'] = 'field_ding_news_tags';
  $handler->display->display_options['fields']['field_ding_news_tags']['label'] = 'tags';
  $handler->display->display_options['fields']['field_ding_news_tags']['type'] = 'taxonomy_term_reference_plain';
  $handler->display->display_options['fields']['field_ding_news_tags']['delta_offset'] = '0';
  /* Felt: Indhold: Title image */
  $handler->display->display_options['fields']['field_ding_news_title_image']['id'] = 'field_ding_news_title_image';
  $handler->display->display_options['fields']['field_ding_news_title_image']['table'] = 'field_data_field_ding_news_title_image';
  $handler->display->display_options['fields']['field_ding_news_title_image']['field'] = 'field_ding_news_title_image';
  $handler->display->display_options['fields']['field_ding_news_title_image']['label'] = 'title image';
  $handler->display->display_options['fields']['field_ding_news_title_image']['click_sort_column'] = 'fid';
  $handler->display->display_options['fields']['field_ding_news_title_image']['settings'] = array(
    'image_style' => '',
    'image_link' => 'file',
  );
  /* Felt: Indhold: Titel */
  $handler->display->display_options['fields']['title_1']['id'] = 'title_1';
  $handler->display->display_options['fields']['title_1']['table'] = 'node';
  $handler->display->display_options['fields']['title_1']['field'] = 'title';
  $handler->display->display_options['fields']['title_1']['relationship'] = 'og_group_ref_target_id';
  $handler->display->display_options['fields']['title_1']['label'] = 'library';
  $handler->display->display_options['fields']['title_1']['link_to_node'] = FALSE;
  /* Sorteringskriterie: Indhold: Oprettelsesdato */
  $handler->display->display_options['sorts']['created']['id'] = 'created';
  $handler->display->display_options['sorts']['created']['table'] = 'node';
  $handler->display->display_options['sorts']['created']['field'] = 'created';
  $handler->display->display_options['sorts']['created']['order'] = 'DESC';
  /* Filterkriterie: Indhold: Udgivet */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'node';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = 1;
  $handler->display->display_options['filters']['status']['group'] = 1;
  $handler->display->display_options['filters']['status']['expose']['operator'] = FALSE;
  /* Filterkriterie: Indhold: Type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'node';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'ding_news' => 'ding_news',
  );
  $handler->display->display_options['filters']['type']['group'] = 1;
  /* Filterkriterie: Indhold: Category (field_ding_news_category) */
  $handler->display->display_options['filters']['field_ding_news_category_tid']['id'] = 'field_ding_news_category_tid';
  $handler->display->display_options['filters']['field_ding_news_category_tid']['table'] = 'field_data_field_ding_news_category';
  $handler->display->display_options['filters']['field_ding_news_category_tid']['field'] = 'field_ding_news_category_tid';
  $handler->display->display_options['filters']['field_ding_news_category_tid']['value'] = '';
  $handler->display->display_options['filters']['field_ding_news_category_tid']['exposed'] = TRUE;
  $handler->display->display_options['filters']['field_ding_news_category_tid']['expose']['operator_id'] = 'field_ding_news_category_tid_op';
  $handler->display->display_options['filters']['field_ding_news_category_tid']['expose']['label'] = 'Kategori';
  $handler->display->display_options['filters']['field_ding_news_category_tid']['expose']['operator'] = 'field_ding_news_category_tid_op';
  $handler->display->display_options['filters']['field_ding_news_category_tid']['expose']['identifier'] = 'category';
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
  );
  $handler->display->display_options['filters']['field_ding_news_category_tid']['vocabulary'] = 'news_category';
  /* Filterkriterie: Indhold: Titel */
  $handler->display->display_options['filters']['title']['id'] = 'title';
  $handler->display->display_options['filters']['title']['table'] = 'node';
  $handler->display->display_options['filters']['title']['field'] = 'title';
  $handler->display->display_options['filters']['title']['relationship'] = 'og_group_ref_target_id';
  $handler->display->display_options['filters']['title']['exposed'] = TRUE;
  $handler->display->display_options['filters']['title']['expose']['operator_id'] = 'title_op';
  $handler->display->display_options['filters']['title']['expose']['label'] = 'Bibliotek';
  $handler->display->display_options['filters']['title']['expose']['operator'] = 'title_op';
  $handler->display->display_options['filters']['title']['expose']['identifier'] = 'library';
  $handler->display->display_options['filters']['title']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
    4 => 0,
    5 => 0,
    6 => 0,
    7 => 0,
    8 => 0,
    9 => 0,
  );
  /* Filterkriterie: Indhold: Type */
  $handler->display->display_options['filters']['type_1']['id'] = 'type_1';
  $handler->display->display_options['filters']['type_1']['table'] = 'node';
  $handler->display->display_options['filters']['type_1']['field'] = 'type';
  $handler->display->display_options['filters']['type_1']['relationship'] = 'og_group_ref_target_id';
  $handler->display->display_options['filters']['type_1']['value'] = array(
    'ding_library' => 'ding_library',
  );

  /* Display: Services */
  $handler = $view->new_display('services', 'Services', 'services_news_list');
  $handler->display->display_options['path'] = 'news_list';
  $translatables['ding_news_services'] = array(
    t('Master'),
    t('mere'),
    t('Udfør'),
    t('Gendan'),
    t('Sortér efter'),
    t('Stigende'),
    t('Faldende'),
    t('Indhold entity refereret fra og_group_ref'),
    t('title'),
    t('nid'),
    t('description'),
    t('category'),
    t('files'),
    t('groups'),
    t('lead'),
    t('list image'),
    t('tags'),
    t('title image'),
    t('library'),
    t('Kategori'),
    t('Bibliotek'),
    t('Services'),
  );
  $export['ding_news_services'] = $view;

  return $export;
}
