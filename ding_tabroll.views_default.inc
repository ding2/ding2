<?php
/**
 * @file
 * tabroll.views_default.inc
 */

/**
 * Implements hook_views_default_views().
 */
function ding_tabroll_views_default_views() {
  $export = array();

  $view = new view;
  $view->name = 'libraries_tabroll';
  $view->description = 'Display a list of all nodes in queue \'libraries\'';
  $view->tag = 'nodequeue';
  $view->base_table = 'node';
  $view->human_name = 'libraries tabroll';
  $view->core = 0;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Defaults */
  $handler = $view->new_display('default', 'Defaults', 'default');
  $handler->display->display_options['use_more_text'] = 'Se flere';
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['query']['options']['query_comment'] = FALSE;
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['exposed_form']['options']['reset_button_label'] = 'Gendan';
  $handler->display->display_options['exposed_form']['options']['exposed_sorts_label'] = 'Sortér efter';
  $handler->display->display_options['pager']['type'] = 'some';
  $handler->display->display_options['pager']['options']['items_per_page'] = '5';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['style_plugin'] = 'default';
  $handler->display->display_options['row_plugin'] = 'fields';
  $handler->display->display_options['row_options']['hide_empty'] = 0;
  $handler->display->display_options['row_options']['default_field_elements'] = 0;
  /* Relationship: Nodequeue: Queue */
  $handler->display->display_options['relationships']['nodequeue_rel']['id'] = 'nodequeue_rel';
  $handler->display->display_options['relationships']['nodequeue_rel']['table'] = 'node';
  $handler->display->display_options['relationships']['nodequeue_rel']['field'] = 'nodequeue_rel';
  $handler->display->display_options['relationships']['nodequeue_rel']['required'] = 1;
  $handler->display->display_options['relationships']['nodequeue_rel']['limit'] = TRUE;
  $handler->display->display_options['relationships']['nodequeue_rel']['names'] = array(
    'ding_tabroll_for_libraries' => 'ding_tabroll_for_libraries',
  );
  /* Relationship: Entity Reference: Referenced Entity */
  $handler->display->display_options['relationships']['field_ding_tabroll_link_target_id']['id'] = 'field_ding_tabroll_link_target_id';
  $handler->display->display_options['relationships']['field_ding_tabroll_link_target_id']['table'] = 'field_data_field_ding_tabroll_link';
  $handler->display->display_options['relationships']['field_ding_tabroll_link_target_id']['field'] = 'field_ding_tabroll_link_target_id';
  $handler->display->display_options['relationships']['field_ding_tabroll_link_target_id']['required'] = 0;
  /* Felt: Indhold: Titel */
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
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['title']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['title']['alter']['more_link'] = 0;
  $handler->display->display_options['fields']['title']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['title']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['title']['alter']['html'] = 0;
  $handler->display->display_options['fields']['title']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['title']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['title']['hide_empty'] = 0;
  $handler->display->display_options['fields']['title']['empty_zero'] = 0;
  $handler->display->display_options['fields']['title']['hide_alter_empty'] = 1;
  $handler->display->display_options['fields']['title']['link_to_node'] = 0;
  /* Felt: Indhold: image */
  $handler->display->display_options['fields']['field_ding_tabroll_image']['id'] = 'field_ding_tabroll_image';
  $handler->display->display_options['fields']['field_ding_tabroll_image']['table'] = 'field_data_field_ding_tabroll_image';
  $handler->display->display_options['fields']['field_ding_tabroll_image']['field'] = 'field_ding_tabroll_image';
  $handler->display->display_options['fields']['field_ding_tabroll_image']['label'] = '';
  $handler->display->display_options['fields']['field_ding_tabroll_image']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['field_ding_tabroll_image']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['field_ding_tabroll_image']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['field_ding_tabroll_image']['alter']['external'] = 0;
  $handler->display->display_options['fields']['field_ding_tabroll_image']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['field_ding_tabroll_image']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['field_ding_tabroll_image']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['field_ding_tabroll_image']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['field_ding_tabroll_image']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['field_ding_tabroll_image']['alter']['more_link'] = 0;
  $handler->display->display_options['fields']['field_ding_tabroll_image']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['field_ding_tabroll_image']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['field_ding_tabroll_image']['alter']['html'] = 0;
  $handler->display->display_options['fields']['field_ding_tabroll_image']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_ding_tabroll_image']['element_default_classes'] = 0;
  $handler->display->display_options['fields']['field_ding_tabroll_image']['hide_empty'] = 0;
  $handler->display->display_options['fields']['field_ding_tabroll_image']['empty_zero'] = 0;
  $handler->display->display_options['fields']['field_ding_tabroll_image']['hide_alter_empty'] = 1;
  $handler->display->display_options['fields']['field_ding_tabroll_image']['click_sort_column'] = 'fid';
  $handler->display->display_options['fields']['field_ding_tabroll_image']['settings'] = array(
    'image_style' => 'ding_tabroll',
    'image_link' => '',
  );
  $handler->display->display_options['fields']['field_ding_tabroll_image']['field_api_classes'] = 0;
  /* Felt: Indhold: ding_tabroll_lead */
  $handler->display->display_options['fields']['field_ding_tabroll_lead']['id'] = 'field_ding_tabroll_lead';
  $handler->display->display_options['fields']['field_ding_tabroll_lead']['table'] = 'field_data_field_ding_tabroll_lead';
  $handler->display->display_options['fields']['field_ding_tabroll_lead']['field'] = 'field_ding_tabroll_lead';
  $handler->display->display_options['fields']['field_ding_tabroll_lead']['label'] = '';
  $handler->display->display_options['fields']['field_ding_tabroll_lead']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['field_ding_tabroll_lead']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['field_ding_tabroll_lead']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['field_ding_tabroll_lead']['alter']['external'] = 0;
  $handler->display->display_options['fields']['field_ding_tabroll_lead']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['field_ding_tabroll_lead']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['field_ding_tabroll_lead']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['field_ding_tabroll_lead']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['field_ding_tabroll_lead']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['field_ding_tabroll_lead']['alter']['more_link'] = 0;
  $handler->display->display_options['fields']['field_ding_tabroll_lead']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['field_ding_tabroll_lead']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['field_ding_tabroll_lead']['alter']['html'] = 0;
  $handler->display->display_options['fields']['field_ding_tabroll_lead']['element_type'] = 'p';
  $handler->display->display_options['fields']['field_ding_tabroll_lead']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_ding_tabroll_lead']['element_default_classes'] = 0;
  $handler->display->display_options['fields']['field_ding_tabroll_lead']['hide_empty'] = 0;
  $handler->display->display_options['fields']['field_ding_tabroll_lead']['empty_zero'] = 0;
  $handler->display->display_options['fields']['field_ding_tabroll_lead']['hide_alter_empty'] = 1;
  $handler->display->display_options['fields']['field_ding_tabroll_lead']['field_api_classes'] = 0;
  /* Felt: Indhold: ding_tabroll_link */
  $handler->display->display_options['fields']['field_ding_tabroll_link']['id'] = 'field_ding_tabroll_link';
  $handler->display->display_options['fields']['field_ding_tabroll_link']['table'] = 'field_data_field_ding_tabroll_link';
  $handler->display->display_options['fields']['field_ding_tabroll_link']['field'] = 'field_ding_tabroll_link';
  $handler->display->display_options['fields']['field_ding_tabroll_link']['relationship'] = 'field_ding_tabroll_link_target_id';
  $handler->display->display_options['fields']['field_ding_tabroll_link']['label'] = '';
  $handler->display->display_options['fields']['field_ding_tabroll_link']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['field_ding_tabroll_link']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['field_ding_tabroll_link']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['field_ding_tabroll_link']['alter']['external'] = 0;
  $handler->display->display_options['fields']['field_ding_tabroll_link']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['field_ding_tabroll_link']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['field_ding_tabroll_link']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['field_ding_tabroll_link']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['field_ding_tabroll_link']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['field_ding_tabroll_link']['alter']['more_link'] = 0;
  $handler->display->display_options['fields']['field_ding_tabroll_link']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['field_ding_tabroll_link']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['field_ding_tabroll_link']['alter']['html'] = 0;
  $handler->display->display_options['fields']['field_ding_tabroll_link']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_ding_tabroll_link']['element_default_classes'] = 0;
  $handler->display->display_options['fields']['field_ding_tabroll_link']['hide_empty'] = 0;
  $handler->display->display_options['fields']['field_ding_tabroll_link']['empty_zero'] = 0;
  $handler->display->display_options['fields']['field_ding_tabroll_link']['hide_alter_empty'] = 1;
  $handler->display->display_options['fields']['field_ding_tabroll_link']['type'] = 'entityreference_entity_id';
  $handler->display->display_options['fields']['field_ding_tabroll_link']['settings'] = array(
    'link' => 0,
  );
  $handler->display->display_options['fields']['field_ding_tabroll_link']['field_api_classes'] = 0;
  /* Sort criterion: Nodequeue: Position */
  $handler->display->display_options['sorts']['position']['id'] = 'position';
  $handler->display->display_options['sorts']['position']['table'] = 'nodequeue_nodes';
  $handler->display->display_options['sorts']['position']['field'] = 'position';
  $handler->display->display_options['sorts']['position']['relationship'] = 'nodequeue_rel';
  /* Contextual filter: Nodequeue: Subqueue reference */
  $handler->display->display_options['arguments']['reference']['id'] = 'reference';
  $handler->display->display_options['arguments']['reference']['table'] = 'nodequeue_subqueue';
  $handler->display->display_options['arguments']['reference']['field'] = 'reference';
  $handler->display->display_options['arguments']['reference']['relationship'] = 'nodequeue_rel';
  $handler->display->display_options['arguments']['reference']['default_action'] = 'default';
  $handler->display->display_options['arguments']['reference']['default_argument_type'] = 'node';
  $handler->display->display_options['arguments']['reference']['default_argument_skip_url'] = 0;
  $handler->display->display_options['arguments']['reference']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['reference']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['reference']['summary_options']['items_per_page'] = '25';
  $handler->display->display_options['arguments']['reference']['glossary'] = 0;
  $handler->display->display_options['arguments']['reference']['limit'] = '0';
  $handler->display->display_options['arguments']['reference']['transform_dash'] = 0;
  $handler->display->display_options['arguments']['reference']['break_phrase'] = 0;
  /* Filter criterion: Indhold: Type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'node';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'ding_tabroll' => 'ding_tabroll',
  );
  /* Filter criterion: Indhold: Udgivet */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'node';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = '1';

  /* Display: Content pane */
  $handler = $view->new_display('panel_pane', 'Content pane', 'panel_pane_1');
  $translatables['libraries_tabroll'] = array(
    t('Defaults'),
    t('Se flere'),
    t('Send'),
    t('Gendan'),
    t('Sortér efter'),
    t('Asc'),
    t('Desc'),
    t('queue'),
    t('Indhold entity referenced from field_ding_tabroll_link'),
    t('Alle'),
    t('Content pane'),
    t('View panes'),
  );
  $export['libraries_tabroll'] = $view;

  $view = new view;
  $view->name = 'ding_tabroll';
  $view->description = 'Display a list of all nodes in queue \'frontpage tabroll\'';
  $view->tag = 'nodequeue';
  $view->base_table = 'node';
  $view->human_name = 'frontpage tabroll';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['use_more_text'] = 'Se flere';
  $handler->display->display_options['access']['type'] = 'none';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['query']['options']['query_comment'] = FALSE;
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['exposed_form']['options']['reset_button_label'] = 'Gendan';
  $handler->display->display_options['exposed_form']['options']['exposed_sorts_label'] = 'Sortér efter';
  $handler->display->display_options['pager']['type'] = 'some';
  $handler->display->display_options['pager']['options']['items_per_page'] = '5';
  $handler->display->display_options['style_plugin'] = 'default';
  $handler->display->display_options['row_plugin'] = 'fields';
  $handler->display->display_options['row_options']['hide_empty'] = 0;
  $handler->display->display_options['row_options']['default_field_elements'] = 0;
  /* Relationship: Nodequeue: Queue */
  $handler->display->display_options['relationships']['nodequeue_rel']['id'] = 'nodequeue_rel';
  $handler->display->display_options['relationships']['nodequeue_rel']['table'] = 'node';
  $handler->display->display_options['relationships']['nodequeue_rel']['field'] = 'nodequeue_rel';
  $handler->display->display_options['relationships']['nodequeue_rel']['label'] = 'frontpage tabroll';
  $handler->display->display_options['relationships']['nodequeue_rel']['required'] = 1;
  $handler->display->display_options['relationships']['nodequeue_rel']['limit'] = 1;
  $handler->display->display_options['relationships']['nodequeue_rel']['names'] = array(
    'ding_tabroll' => 'ding_tabroll',
    'ding_tabroll_for_libraries' => 0,
  );
  /* Relationship: Entity Reference: Referenced Entity */
  $handler->display->display_options['relationships']['field_ding_tabroll_link_target_id']['id'] = 'field_ding_tabroll_link_target_id';
  $handler->display->display_options['relationships']['field_ding_tabroll_link_target_id']['table'] = 'field_data_field_ding_tabroll_link';
  $handler->display->display_options['relationships']['field_ding_tabroll_link_target_id']['field'] = 'field_ding_tabroll_link_target_id';
  $handler->display->display_options['relationships']['field_ding_tabroll_link_target_id']['required'] = 0;
  /* Felt: Indhold: Titel */
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
  $handler->display->display_options['fields']['title']['alter']['more_link'] = 0;
  $handler->display->display_options['fields']['title']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['title']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['title']['alter']['html'] = 0;
  $handler->display->display_options['fields']['title']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['title']['element_default_classes'] = 0;
  $handler->display->display_options['fields']['title']['hide_empty'] = 0;
  $handler->display->display_options['fields']['title']['empty_zero'] = 0;
  $handler->display->display_options['fields']['title']['hide_alter_empty'] = 1;
  $handler->display->display_options['fields']['title']['link_to_node'] = 0;
  /* Felt: Indhold: image */
  $handler->display->display_options['fields']['field_ding_tabroll_image']['id'] = 'field_ding_tabroll_image';
  $handler->display->display_options['fields']['field_ding_tabroll_image']['table'] = 'field_data_field_ding_tabroll_image';
  $handler->display->display_options['fields']['field_ding_tabroll_image']['field'] = 'field_ding_tabroll_image';
  $handler->display->display_options['fields']['field_ding_tabroll_image']['label'] = '';
  $handler->display->display_options['fields']['field_ding_tabroll_image']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['field_ding_tabroll_image']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['field_ding_tabroll_image']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['field_ding_tabroll_image']['alter']['external'] = 0;
  $handler->display->display_options['fields']['field_ding_tabroll_image']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['field_ding_tabroll_image']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['field_ding_tabroll_image']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['field_ding_tabroll_image']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['field_ding_tabroll_image']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['field_ding_tabroll_image']['alter']['more_link'] = 0;
  $handler->display->display_options['fields']['field_ding_tabroll_image']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['field_ding_tabroll_image']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['field_ding_tabroll_image']['alter']['html'] = 0;
  $handler->display->display_options['fields']['field_ding_tabroll_image']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_ding_tabroll_image']['element_default_classes'] = 0;
  $handler->display->display_options['fields']['field_ding_tabroll_image']['hide_empty'] = 0;
  $handler->display->display_options['fields']['field_ding_tabroll_image']['empty_zero'] = 0;
  $handler->display->display_options['fields']['field_ding_tabroll_image']['hide_alter_empty'] = 1;
  $handler->display->display_options['fields']['field_ding_tabroll_image']['click_sort_column'] = 'fid';
  $handler->display->display_options['fields']['field_ding_tabroll_image']['settings'] = array(
    'image_style' => 'ding_tabroll',
    'image_link' => '',
  );
  $handler->display->display_options['fields']['field_ding_tabroll_image']['field_api_classes'] = 0;
  /* Felt: Indhold: ding_tabroll_lead */
  $handler->display->display_options['fields']['field_ding_tabroll_lead']['id'] = 'field_ding_tabroll_lead';
  $handler->display->display_options['fields']['field_ding_tabroll_lead']['table'] = 'field_data_field_ding_tabroll_lead';
  $handler->display->display_options['fields']['field_ding_tabroll_lead']['field'] = 'field_ding_tabroll_lead';
  $handler->display->display_options['fields']['field_ding_tabroll_lead']['label'] = '';
  $handler->display->display_options['fields']['field_ding_tabroll_lead']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['field_ding_tabroll_lead']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['field_ding_tabroll_lead']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['field_ding_tabroll_lead']['alter']['external'] = 0;
  $handler->display->display_options['fields']['field_ding_tabroll_lead']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['field_ding_tabroll_lead']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['field_ding_tabroll_lead']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['field_ding_tabroll_lead']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['field_ding_tabroll_lead']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['field_ding_tabroll_lead']['alter']['more_link'] = 0;
  $handler->display->display_options['fields']['field_ding_tabroll_lead']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['field_ding_tabroll_lead']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['field_ding_tabroll_lead']['alter']['html'] = 0;
  $handler->display->display_options['fields']['field_ding_tabroll_lead']['element_type'] = 'p';
  $handler->display->display_options['fields']['field_ding_tabroll_lead']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_ding_tabroll_lead']['element_default_classes'] = 0;
  $handler->display->display_options['fields']['field_ding_tabroll_lead']['hide_empty'] = 0;
  $handler->display->display_options['fields']['field_ding_tabroll_lead']['empty_zero'] = 0;
  $handler->display->display_options['fields']['field_ding_tabroll_lead']['hide_alter_empty'] = 1;
  $handler->display->display_options['fields']['field_ding_tabroll_lead']['field_api_classes'] = 0;
  /* Felt: Indhold: ding_tabroll_link */
  $handler->display->display_options['fields']['field_ding_tabroll_link']['id'] = 'field_ding_tabroll_link';
  $handler->display->display_options['fields']['field_ding_tabroll_link']['table'] = 'field_data_field_ding_tabroll_link';
  $handler->display->display_options['fields']['field_ding_tabroll_link']['field'] = 'field_ding_tabroll_link';
  $handler->display->display_options['fields']['field_ding_tabroll_link']['relationship'] = 'field_ding_tabroll_link_target_id';
  $handler->display->display_options['fields']['field_ding_tabroll_link']['label'] = '';
  $handler->display->display_options['fields']['field_ding_tabroll_link']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['field_ding_tabroll_link']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['field_ding_tabroll_link']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['field_ding_tabroll_link']['alter']['external'] = 0;
  $handler->display->display_options['fields']['field_ding_tabroll_link']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['field_ding_tabroll_link']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['field_ding_tabroll_link']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['field_ding_tabroll_link']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['field_ding_tabroll_link']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['field_ding_tabroll_link']['alter']['more_link'] = 0;
  $handler->display->display_options['fields']['field_ding_tabroll_link']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['field_ding_tabroll_link']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['field_ding_tabroll_link']['alter']['html'] = 0;
  $handler->display->display_options['fields']['field_ding_tabroll_link']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_ding_tabroll_link']['element_default_classes'] = 0;
  $handler->display->display_options['fields']['field_ding_tabroll_link']['hide_empty'] = 0;
  $handler->display->display_options['fields']['field_ding_tabroll_link']['empty_zero'] = 0;
  $handler->display->display_options['fields']['field_ding_tabroll_link']['hide_alter_empty'] = 1;
  $handler->display->display_options['fields']['field_ding_tabroll_link']['type'] = 'entityreference_entity_id';
  $handler->display->display_options['fields']['field_ding_tabroll_link']['settings'] = array(
    'link' => 0,
  );
  $handler->display->display_options['fields']['field_ding_tabroll_link']['field_api_classes'] = 0;
  /* Sort criterion: Nodequeue: Position */
  $handler->display->display_options['sorts']['position']['id'] = 'position';
  $handler->display->display_options['sorts']['position']['table'] = 'nodequeue_nodes';
  $handler->display->display_options['sorts']['position']['field'] = 'position';
  $handler->display->display_options['sorts']['position']['relationship'] = 'nodequeue_rel';
  /* Filter criterion: Indhold: Udgivet */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'node';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = 1;
  $handler->display->display_options['filters']['status']['group'] = 1;
  $handler->display->display_options['filters']['status']['expose']['operator'] = FALSE;

  /* Display: Content pane */
  $handler = $view->new_display('panel_pane', 'Content pane', 'panel_pane_1');
  $translatables['ding_tabroll'] = array(
    t('Master'),
    t('Se flere'),
    t('Send'),
    t('Gendan'),
    t('Sortér efter'),
    t('Asc'),
    t('Desc'),
    t('frontpage tabroll'),
    t('Indhold entity referenced from field_ding_tabroll_link'),
    t('Content pane'),
    t('View panes'),
  );
  $export['ding_tabroll'] = $view;

  return $export;
}
