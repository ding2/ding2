<?php
/**
 * @file
 * ding_frontend.views_default.inc
 */

/**
 * Implements hook_views_default_views().
 */
function ding_frontend_views_default_views() {
  $export = array();

  $view = new view();
  $view->name = 'ding_node_search';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'node';
  $view->human_name = 'Ding node search';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Ding node search';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['use_more_text'] = 'mere';
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['query']['options']['query_comment'] = FALSE;
  $handler->display->display_options['exposed_form']['type'] = 'input_required';
  $handler->display->display_options['exposed_form']['options']['submit_button'] = 'Udfør';
  $handler->display->display_options['exposed_form']['options']['reset_button_label'] = 'Gendan';
  $handler->display->display_options['exposed_form']['options']['exposed_sorts_label'] = 'Sortér efter';
  $handler->display->display_options['exposed_form']['options']['sort_asc_label'] = 'Stigende';
  $handler->display->display_options['exposed_form']['options']['sort_desc_label'] = 'Faldende';
  $handler->display->display_options['exposed_form']['options']['text_input_required'] = 'No results found';
  $handler->display->display_options['exposed_form']['options']['text_input_required_format'] = 'ding_wysiwyg';
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = '10';
  $handler->display->display_options['pager']['options']['expose']['items_per_page_label'] = 'Antal elementer';
  $handler->display->display_options['pager']['options']['expose']['items_per_page_options_all_label'] = '- Alle -';
  $handler->display->display_options['pager']['options']['expose']['offset_label'] = 'Forskydning';
  $handler->display->display_options['pager']['options']['tags']['first'] = '« første';
  $handler->display->display_options['pager']['options']['tags']['previous'] = '‹ forrige';
  $handler->display->display_options['pager']['options']['tags']['next'] = 'næste ›';
  $handler->display->display_options['pager']['options']['tags']['last'] = 'sidste »';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['pager']['options']['id'] = '0';
  $handler->display->display_options['pager']['options']['quantity'] = '9';
  $handler->display->display_options['style_plugin'] = 'list';
  $handler->display->display_options['style_options']['row_class'] = 'list-item search-result';
  $handler->display->display_options['style_options']['default_row_class'] = FALSE;
  $handler->display->display_options['style_options']['row_class_special'] = FALSE;
  $handler->display->display_options['style_options']['class'] = 'list floated';
  $handler->display->display_options['style_options']['wrapper_class'] = 'search-results';
  $handler->display->display_options['row_plugin'] = 'node';
  $handler->display->display_options['row_options']['view_mode'] = 'search_result';
  $handler->display->display_options['row_options']['links'] = FALSE;
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = '';
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['title']['alter']['ellipsis'] = FALSE;
  /* Sort criterion: Content: Updated date */
  $handler->display->display_options['sorts']['changed']['id'] = 'changed';
  $handler->display->display_options['sorts']['changed']['table'] = 'node';
  $handler->display->display_options['sorts']['changed']['field'] = 'changed';
  $handler->display->display_options['sorts']['changed']['order'] = 'DESC';
  /* Contextual filter: Search: Search Terms */
  $handler->display->display_options['arguments']['keys']['id'] = 'keys';
  $handler->display->display_options['arguments']['keys']['table'] = 'search_index';
  $handler->display->display_options['arguments']['keys']['field'] = 'keys';
  $handler->display->display_options['arguments']['keys']['default_action'] = 'empty';
  $handler->display->display_options['arguments']['keys']['exception']['title'] = 'Alle';
  $handler->display->display_options['arguments']['keys']['default_argument_type'] = 'fixed';
  $handler->display->display_options['arguments']['keys']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['keys']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['keys']['summary_options']['items_per_page'] = '25';
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
  $handler->display->display_options['filters']['type']['operator'] = 'not in';
  $handler->display->display_options['filters']['type']['value'] = array(
    'ding_campaign' => 'ding_campaign',
    'new_materials' => 'new_materials',
    'panel' => 'panel',
    'ding_rolltab' => 'ding_rolltab',
  );

  /* Display: Content pane */
  $handler = $view->new_display('panel_pane', 'Content pane', 'panel_pane_1');
  $translatables['ding_node_search'] = array(
    t('Master'),
    t('Ding node search'),
    t('mere'),
    t('Udfør'),
    t('Gendan'),
    t('Sortér efter'),
    t('Stigende'),
    t('Faldende'),
    t('No results found'),
    t('Antal elementer'),
    t('- Alle -'),
    t('Forskydning'),
    t('« første'),
    t('‹ forrige'),
    t('næste ›'),
    t('sidste »'),
    t('Alle'),
    t('Content pane'),
    t('more'),
    t('View panes'),
  );
  $export['ding_node_search'] = $view;

  $view = new view();
  $view->name = 'ding_node_search_solr';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'search_api_index_default_node_index';
  $view->human_name = 'Ding node search (solr)';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Ding node search';
  $handler->display->display_options['css_class'] = 'view-node-search-result';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'input_required';
  $handler->display->display_options['exposed_form']['options']['text_input_required_format'] = 'ding_wysiwyg';
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['style_plugin'] = 'list';
  $handler->display->display_options['style_options']['row_class'] = 'list-item search-result';
  $handler->display->display_options['style_options']['class'] = 'list';
  $handler->display->display_options['style_options']['wrapper_class'] = 'search-results';
  $handler->display->display_options['row_plugin'] = 'entity';
  $handler->display->display_options['row_options']['view_mode'] = 'search_result';
  /* Field: Indexed Node: Node ID */
  $handler->display->display_options['fields']['nid']['id'] = 'nid';
  $handler->display->display_options['fields']['nid']['table'] = 'search_api_index_default_node_index';
  $handler->display->display_options['fields']['nid']['field'] = 'nid';
  /* Sort criterion: Indexed Node: Date changed */
  $handler->display->display_options['sorts']['changed']['id'] = 'changed';
  $handler->display->display_options['sorts']['changed']['table'] = 'search_api_index_default_node_index';
  $handler->display->display_options['sorts']['changed']['field'] = 'changed';
  $handler->display->display_options['sorts']['changed']['order'] = 'DESC';
  /* Contextual filter: Search: Fulltext search */
  $handler->display->display_options['arguments']['search_api_views_fulltext']['id'] = 'search_api_views_fulltext';
  $handler->display->display_options['arguments']['search_api_views_fulltext']['table'] = 'search_api_index_default_node_index';
  $handler->display->display_options['arguments']['search_api_views_fulltext']['field'] = 'search_api_views_fulltext';
  $handler->display->display_options['arguments']['search_api_views_fulltext']['default_argument_type'] = 'fixed';
  $handler->display->display_options['arguments']['search_api_views_fulltext']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['search_api_views_fulltext']['break_phrase'] = 0;
  $handler->display->display_options['arguments']['search_api_views_fulltext']['not'] = 0;
  $handler->display->display_options['arguments']['search_api_views_fulltext']['conjunction'] = 'OR';
  /* Filter criterion: Indexed Node: Status */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'search_api_index_default_node_index';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = array(
    1 => '1',
  );
  /* Filter criterion: Indexed Node: Content type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'search_api_index_default_node_index';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['operator'] = '<>';
  $handler->display->display_options['filters']['type']['value'] = array(
    'panel' => 'panel',
    'ding_rolltab' => 'ding_rolltab',
  );

  /* Display: Content pane */
  $handler = $view->new_display('panel_pane', 'Content pane', 'panel_pane_1');
  $handler->display->display_options['allow']['use_pager'] = 0;
  $handler->display->display_options['allow']['items_per_page'] = 0;
  $handler->display->display_options['allow']['offset'] = 0;
  $handler->display->display_options['allow']['link_to_view'] = 0;
  $handler->display->display_options['allow']['more_link'] = 0;
  $handler->display->display_options['allow']['path_override'] = 0;
  $handler->display->display_options['allow']['title_override'] = 0;
  $handler->display->display_options['allow']['exposed_form'] = 0;
  $handler->display->display_options['allow']['fields_override'] = 0;
  $handler->display->display_options['argument_input'] = array(
    'search_api_views_fulltext' => array(
      'type' => 'panel',
      'context' => 'entity:comment.author',
      'context_optional' => 0,
      'panel' => '2',
      'fixed' => '',
      'label' => 'Search: Fulltext search',
    ),
  );
  $translatables['ding_node_search_solr'] = array(
    t('Master'),
    t('Ding node search'),
    t('more'),
    t('Apply'),
    t('Reset'),
    t('Sort by'),
    t('Asc'),
    t('Desc'),
    t('Select any filter and click on Apply to see results'),
    t('Items per page'),
    t('- All -'),
    t('Offset'),
    t('« first'),
    t('‹ previous'),
    t('next ›'),
    t('last »'),
    t('Node ID'),
    t('.'),
    t(','),
    t('All'),
    t('Content pane'),
    t('View panes'),
  );
  $export['ding_node_search_solr'] = $view;

  $view = new view();
  $view->name = 'ding_user_search_solr_0';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'search_api_index_default_user_index_0';
  $view->human_name = 'Ding user search (solr)';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['css_class'] = 'view-node-search-result';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'none';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['style_plugin'] = 'list';
  $handler->display->display_options['style_options']['row_class'] = 'list-item search-result';
  $handler->display->display_options['style_options']['class'] = 'list';
  $handler->display->display_options['style_options']['wrapper_class'] = 'search-results';
  $handler->display->display_options['row_plugin'] = 'entity';
  /* Relationship: Staff profile: User (indexed) */
  $handler->display->display_options['relationships']['profile_ding_staff_profile_user']['id'] = 'profile_ding_staff_profile_user';
  $handler->display->display_options['relationships']['profile_ding_staff_profile_user']['table'] = 'search_api_index_default_user_index_0';
  $handler->display->display_options['relationships']['profile_ding_staff_profile_user']['field'] = 'profile_ding_staff_profile_user';
  /* Field: Indexed User: User ID */
  $handler->display->display_options['fields']['uid']['id'] = 'uid';
  $handler->display->display_options['fields']['uid']['table'] = 'search_api_index_default_user_index_0';
  $handler->display->display_options['fields']['uid']['field'] = 'uid';
  $handler->display->display_options['fields']['uid']['exclude'] = TRUE;
  $handler->display->display_options['fields']['uid']['link_to_entity'] = 0;
  /* Field: User: Rendered User */
  $handler->display->display_options['fields']['rendered_entity']['id'] = 'rendered_entity';
  $handler->display->display_options['fields']['rendered_entity']['table'] = 'views_entity_user';
  $handler->display->display_options['fields']['rendered_entity']['field'] = 'rendered_entity';
  $handler->display->display_options['fields']['rendered_entity']['label'] = '';
  $handler->display->display_options['fields']['rendered_entity']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['rendered_entity']['link_to_entity'] = 1;
  $handler->display->display_options['fields']['rendered_entity']['view_mode'] = 'full';
  $handler->display->display_options['fields']['rendered_entity']['bypass_access'] = 0;
  /* Field: Staff profile: Active OG memberships from field Library (indexed) */
  $handler->display->display_options['fields']['profile_ding_staff_profile_og_group_ref_og_membership_1']['id'] = 'profile_ding_staff_profile_og_group_ref_og_membership_1';
  $handler->display->display_options['fields']['profile_ding_staff_profile_og_group_ref_og_membership_1']['table'] = 'search_api_index_default_user_index_0';
  $handler->display->display_options['fields']['profile_ding_staff_profile_og_group_ref_og_membership_1']['field'] = 'profile_ding_staff_profile_og_group_ref_og_membership_1';
  $handler->display->display_options['fields']['profile_ding_staff_profile_og_group_ref_og_membership_1']['label'] = 'Library';
  $handler->display->display_options['fields']['profile_ding_staff_profile_og_group_ref_og_membership_1']['link_to_entity'] = 1;
  $handler->display->display_options['fields']['profile_ding_staff_profile_og_group_ref_og_membership_1']['bypass_access'] = 0;
  /* Field: Staff profile: Department (indexed) */
  $handler->display->display_options['fields']['profile_ding_staff_profile_field_ding_staff_department_1']['id'] = 'profile_ding_staff_profile_field_ding_staff_department_1';
  $handler->display->display_options['fields']['profile_ding_staff_profile_field_ding_staff_department_1']['table'] = 'search_api_index_default_user_index_0';
  $handler->display->display_options['fields']['profile_ding_staff_profile_field_ding_staff_department_1']['field'] = 'profile_ding_staff_profile_field_ding_staff_department';
  $handler->display->display_options['fields']['profile_ding_staff_profile_field_ding_staff_department_1']['label'] = 'Department';
  $handler->display->display_options['fields']['profile_ding_staff_profile_field_ding_staff_department_1']['link_to_entity'] = 1;
  $handler->display->display_options['fields']['profile_ding_staff_profile_field_ding_staff_department_1']['view_mode'] = 'full';
  $handler->display->display_options['fields']['profile_ding_staff_profile_field_ding_staff_department_1']['bypass_access'] = 0;
  /* Field: Staff profile: Position (indexed) */
  $handler->display->display_options['fields']['profile_ding_staff_profile_field_ding_staff_position']['id'] = 'profile_ding_staff_profile_field_ding_staff_position';
  $handler->display->display_options['fields']['profile_ding_staff_profile_field_ding_staff_position']['table'] = 'search_api_index_default_user_index_0';
  $handler->display->display_options['fields']['profile_ding_staff_profile_field_ding_staff_position']['field'] = 'profile_ding_staff_profile_field_ding_staff_position';
  $handler->display->display_options['fields']['profile_ding_staff_profile_field_ding_staff_position']['label'] = 'Position';
  /* Field: Staff profile: Work areas (indexed) */
  $handler->display->display_options['fields']['profile_ding_staff_profile_field_ding_staff_work_areas']['id'] = 'profile_ding_staff_profile_field_ding_staff_work_areas';
  $handler->display->display_options['fields']['profile_ding_staff_profile_field_ding_staff_work_areas']['table'] = 'search_api_index_default_user_index_0';
  $handler->display->display_options['fields']['profile_ding_staff_profile_field_ding_staff_work_areas']['field'] = 'profile_ding_staff_profile_field_ding_staff_work_areas';
  $handler->display->display_options['fields']['profile_ding_staff_profile_field_ding_staff_work_areas']['label'] = 'Work areas';
  /* Field: Staff profile: Email (indexed) */
  $handler->display->display_options['fields']['profile_ding_staff_profile_field_ding_staff_email']['id'] = 'profile_ding_staff_profile_field_ding_staff_email';
  $handler->display->display_options['fields']['profile_ding_staff_profile_field_ding_staff_email']['table'] = 'search_api_index_default_user_index_0';
  $handler->display->display_options['fields']['profile_ding_staff_profile_field_ding_staff_email']['field'] = 'profile_ding_staff_profile_field_ding_staff_email';
  $handler->display->display_options['fields']['profile_ding_staff_profile_field_ding_staff_email']['label'] = 'Email';
  /* Contextual filter: Search: Fulltext search */
  $handler->display->display_options['arguments']['search_api_views_fulltext']['id'] = 'search_api_views_fulltext';
  $handler->display->display_options['arguments']['search_api_views_fulltext']['table'] = 'search_api_index_default_user_index_0';
  $handler->display->display_options['arguments']['search_api_views_fulltext']['field'] = 'search_api_views_fulltext';
  $handler->display->display_options['arguments']['search_api_views_fulltext']['default_argument_type'] = 'fixed';
  $handler->display->display_options['arguments']['search_api_views_fulltext']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['search_api_views_fulltext']['break_phrase'] = 0;
  $handler->display->display_options['arguments']['search_api_views_fulltext']['not'] = 0;
  /* Filter criterion: Indexed User: User roles */
  $handler->display->display_options['filters']['roles']['id'] = 'roles';
  $handler->display->display_options['filters']['roles']['table'] = 'search_api_index_default_user_index_0';
  $handler->display->display_options['filters']['roles']['field'] = 'roles';
  $handler->display->display_options['filters']['roles']['value'] = array(
    9 => '9',
  );

  /* Display: Content pane */
  $handler = $view->new_display('panel_pane', 'Content pane', 'panel_pane_1');
  $translatables['ding_user_search_solr_0'] = array(
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
    t('User'),
    t('User ID'),
    t('.'),
    t(','),
    t('Library'),
    t('Department'),
    t('Position'),
    t('Work areas'),
    t('Email'),
    t('All'),
    t('Content pane'),
    t('View panes'),
  );
  $export['ding_user_search_solr_0'] = $view;

  return $export;
}
