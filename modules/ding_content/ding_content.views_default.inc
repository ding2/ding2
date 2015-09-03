<?php
/**
 * @file
 * ding_content.views_default.inc
 */

/**
 * Implements hook_views_default_views().
 */
function ding_content_views_default_views() {
  $export = array();

  $view = new view();
  $view->name = 'ding_content_workbench';
  $view->description = 'Content lists for Workbench';
  $view->tag = 'Ding content';
  $view->base_table = 'node';
  $view->human_name = 'Ding Content: Workbench';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Defaults */
  $handler = $view->new_display('default', 'Defaults', 'default');
  $handler->display->display_options['title'] = 'All Recent Content';
  $handler->display->display_options['use_ajax'] = TRUE;
  $handler->display->display_options['use_more'] = TRUE;
  $handler->display->display_options['use_more_always'] = TRUE;
  $handler->display->display_options['use_more_text'] = 'view all';
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['access']['perm'] = 'access workbench';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['query']['options']['query_comment'] = FALSE;
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = '25';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['pager']['options']['id'] = '0';
  $handler->display->display_options['pager']['options']['expose']['items_per_page'] = TRUE;
  $handler->display->display_options['pager']['options']['expose']['items_per_page_options'] = '10, 25, 50, 100, 200';
  $handler->display->display_options['style_plugin'] = 'table';
  $handler->display->display_options['style_options']['columns'] = array(
    'title' => 'title',
    'type' => 'type',
    'status' => 'status',
    'name' => 'name',
    'changed' => 'changed',
    'edit_node' => 'edit_node',
    'field_ding_staff_forename' => 'field_ding_staff_forename',
    'field_ding_staff_surname' => 'field_ding_staff_surname',
    'title_1' => 'title_1',
    'uid' => 'uid',
  );
  $handler->display->display_options['style_options']['default'] = 'changed';
  $handler->display->display_options['style_options']['info'] = array(
    'title' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'type' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'status' => array(
      'sortable' => 1,
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
    'changed' => array(
      'sortable' => 1,
      'default_sort_order' => 'desc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'edit_node' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_ding_staff_forename' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_ding_staff_surname' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'title_1' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'uid' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
  );
  /* No results behavior: Global: Text area */
  $handler->display->display_options['empty']['area']['id'] = 'area';
  $handler->display->display_options['empty']['area']['table'] = 'views';
  $handler->display->display_options['empty']['area']['field'] = 'area';
  $handler->display->display_options['empty']['area']['content'] = 'There is no content available for you to edit.';
  $handler->display->display_options['empty']['area']['format'] = 'plain_text';
  /* Relationship: Content: Author */
  $handler->display->display_options['relationships']['uid']['id'] = 'uid';
  $handler->display->display_options['relationships']['uid']['table'] = 'node';
  $handler->display->display_options['relationships']['uid']['field'] = 'uid';
  /* Relationship: Entity Reference: Referenced Entity */
  $handler->display->display_options['relationships']['og_group_ref_target_id']['id'] = 'og_group_ref_target_id';
  $handler->display->display_options['relationships']['og_group_ref_target_id']['table'] = 'og_membership';
  $handler->display->display_options['relationships']['og_group_ref_target_id']['field'] = 'og_group_ref_target_id';
  $handler->display->display_options['relationships']['og_group_ref_target_id']['label'] = 'Library';
  /* Relationship: User: Profile */
  $handler->display->display_options['relationships']['profile']['id'] = 'profile';
  $handler->display->display_options['relationships']['profile']['table'] = 'users';
  $handler->display->display_options['relationships']['profile']['field'] = 'profile';
  $handler->display->display_options['relationships']['profile']['relationship'] = 'uid';
  $handler->display->display_options['relationships']['profile']['bundle_types'] = array(
    'ding_staff_profile' => 'ding_staff_profile',
  );
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['title']['alter']['ellipsis'] = FALSE;
  /* Field: Content: Type */
  $handler->display->display_options['fields']['type']['id'] = 'type';
  $handler->display->display_options['fields']['type']['table'] = 'node';
  $handler->display->display_options['fields']['type']['field'] = 'type';
  $handler->display->display_options['fields']['type']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['type']['alter']['ellipsis'] = FALSE;
  /* Field: Content: Date */
  $handler->display->display_options['fields']['field_ding_event_date']['id'] = 'field_ding_event_date';
  $handler->display->display_options['fields']['field_ding_event_date']['table'] = 'field_data_field_ding_event_date';
  $handler->display->display_options['fields']['field_ding_event_date']['field'] = 'field_ding_event_date';
  $handler->display->display_options['fields']['field_ding_event_date']['label'] = 'Event date';
  $handler->display->display_options['fields']['field_ding_event_date']['settings'] = array(
    'format_type' => 'short',
    'fromto' => 'both',
    'multiple_number' => '',
    'multiple_from' => '',
    'multiple_to' => '',
  );
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title_1']['id'] = 'title_1';
  $handler->display->display_options['fields']['title_1']['table'] = 'node';
  $handler->display->display_options['fields']['title_1']['field'] = 'title';
  $handler->display->display_options['fields']['title_1']['relationship'] = 'og_group_ref_target_id';
  $handler->display->display_options['fields']['title_1']['label'] = 'Library';
  /* Field: User: Name */
  $handler->display->display_options['fields']['name']['id'] = 'name';
  $handler->display->display_options['fields']['name']['table'] = 'users';
  $handler->display->display_options['fields']['name']['field'] = 'name';
  $handler->display->display_options['fields']['name']['relationship'] = 'uid';
  $handler->display->display_options['fields']['name']['label'] = '';
  $handler->display->display_options['fields']['name']['exclude'] = TRUE;
  $handler->display->display_options['fields']['name']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['name']['hide_alter_empty'] = FALSE;
  /* Field: User: Uid */
  $handler->display->display_options['fields']['uid']['id'] = 'uid';
  $handler->display->display_options['fields']['uid']['table'] = 'users';
  $handler->display->display_options['fields']['uid']['field'] = 'uid';
  $handler->display->display_options['fields']['uid']['relationship'] = 'uid';
  $handler->display->display_options['fields']['uid']['label'] = '';
  $handler->display->display_options['fields']['uid']['exclude'] = TRUE;
  $handler->display->display_options['fields']['uid']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['uid']['link_to_user'] = FALSE;
  /* Field: Profile: Forename */
  $handler->display->display_options['fields']['field_ding_staff_forename']['id'] = 'field_ding_staff_forename';
  $handler->display->display_options['fields']['field_ding_staff_forename']['table'] = 'field_data_field_ding_staff_forename';
  $handler->display->display_options['fields']['field_ding_staff_forename']['field'] = 'field_ding_staff_forename';
  $handler->display->display_options['fields']['field_ding_staff_forename']['relationship'] = 'profile';
  $handler->display->display_options['fields']['field_ding_staff_forename']['label'] = '';
  $handler->display->display_options['fields']['field_ding_staff_forename']['exclude'] = TRUE;
  $handler->display->display_options['fields']['field_ding_staff_forename']['element_label_colon'] = FALSE;
  /* Field: Profile: Surname */
  $handler->display->display_options['fields']['field_ding_staff_surname']['id'] = 'field_ding_staff_surname';
  $handler->display->display_options['fields']['field_ding_staff_surname']['table'] = 'field_data_field_ding_staff_surname';
  $handler->display->display_options['fields']['field_ding_staff_surname']['field'] = 'field_ding_staff_surname';
  $handler->display->display_options['fields']['field_ding_staff_surname']['relationship'] = 'profile';
  $handler->display->display_options['fields']['field_ding_staff_surname']['label'] = 'Author';
  $handler->display->display_options['fields']['field_ding_staff_surname']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['field_ding_staff_surname']['alter']['text'] = '[field_ding_staff_forename] [field_ding_staff_surname]';
  $handler->display->display_options['fields']['field_ding_staff_surname']['alter']['make_link'] = TRUE;
  $handler->display->display_options['fields']['field_ding_staff_surname']['alter']['path'] = 'user/[uid]';
  $handler->display->display_options['fields']['field_ding_staff_surname']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_ding_staff_surname']['empty'] = '[name]';
  /* Field: Content: Published */
  $handler->display->display_options['fields']['status']['id'] = 'status';
  $handler->display->display_options['fields']['status']['table'] = 'node';
  $handler->display->display_options['fields']['status']['field'] = 'status';
  $handler->display->display_options['fields']['status']['label'] = 'Udgivet';
  $handler->display->display_options['fields']['status']['not'] = 0;
  /* Field: Content: Updated date */
  $handler->display->display_options['fields']['changed']['id'] = 'changed';
  $handler->display->display_options['fields']['changed']['table'] = 'node';
  $handler->display->display_options['fields']['changed']['field'] = 'changed';
  $handler->display->display_options['fields']['changed']['label'] = 'Last updated';
  $handler->display->display_options['fields']['changed']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['changed']['alter']['ellipsis'] = FALSE;
  $handler->display->display_options['fields']['changed']['date_format'] = 'short';
  $handler->display->display_options['fields']['changed']['second_date_format'] = 'ding_date_only';
  /* Field: Content: Language */
  $handler->display->display_options['fields']['language']['id'] = 'language';
  $handler->display->display_options['fields']['language']['table'] = 'node';
  $handler->display->display_options['fields']['language']['field'] = 'language';
  /* Field: Content: Edit link */
  $handler->display->display_options['fields']['edit_node']['id'] = 'edit_node';
  $handler->display->display_options['fields']['edit_node']['table'] = 'views_entity_node';
  $handler->display->display_options['fields']['edit_node']['field'] = 'edit_node';
  $handler->display->display_options['fields']['edit_node']['label'] = 'Actions';
  $handler->display->display_options['fields']['edit_node']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['edit_node']['alter']['ellipsis'] = FALSE;
  $handler->display->display_options['fields']['edit_node']['text'] = 'edit';
  /* Sort criterion: Content: Updated date */
  $handler->display->display_options['sorts']['changed']['id'] = 'changed';
  $handler->display->display_options['sorts']['changed']['table'] = 'node';
  $handler->display->display_options['sorts']['changed']['field'] = 'changed';
  $handler->display->display_options['sorts']['changed']['order'] = 'DESC';
  $handler->display->display_options['filter_groups']['groups'] = array(
    1 => 'AND',
    3 => 'AND',
    2 => 'OR',
  );
  /* Filter criterion: Content: Title */
  $handler->display->display_options['filters']['title']['id'] = 'title';
  $handler->display->display_options['filters']['title']['table'] = 'node';
  $handler->display->display_options['filters']['title']['field'] = 'title';
  $handler->display->display_options['filters']['title']['operator'] = 'contains';
  $handler->display->display_options['filters']['title']['group'] = 1;
  $handler->display->display_options['filters']['title']['exposed'] = TRUE;
  $handler->display->display_options['filters']['title']['expose']['label'] = 'Title';
  $handler->display->display_options['filters']['title']['expose']['identifier'] = 'title';
  $handler->display->display_options['filters']['title']['expose']['remember'] = TRUE;
  /* Filter criterion: Content: Type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'node';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['group'] = 1;
  $handler->display->display_options['filters']['type']['exposed'] = TRUE;
  $handler->display->display_options['filters']['type']['expose']['label'] = 'Type';
  $handler->display->display_options['filters']['type']['expose']['identifier'] = 'type';
  $handler->display->display_options['filters']['type']['expose']['remember'] = TRUE;
  /* Filter criterion: Content: Published */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'node';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = '1';
  $handler->display->display_options['filters']['status']['group'] = 1;
  $handler->display->display_options['filters']['status']['exposed'] = TRUE;
  $handler->display->display_options['filters']['status']['expose']['operator_id'] = '';
  $handler->display->display_options['filters']['status']['expose']['label'] = 'Published';
  $handler->display->display_options['filters']['status']['expose']['identifier'] = 'published';
  /* Filter criterion: Content: Published or admin */
  $handler->display->display_options['filters']['status_extra']['id'] = 'status_extra';
  $handler->display->display_options['filters']['status_extra']['table'] = 'node';
  $handler->display->display_options['filters']['status_extra']['field'] = 'status_extra';
  $handler->display->display_options['filters']['status_extra']['group'] = 1;
  /* Filter criterion: Content: Title */
  $handler->display->display_options['filters']['title_1']['id'] = 'title_1';
  $handler->display->display_options['filters']['title_1']['table'] = 'node';
  $handler->display->display_options['filters']['title_1']['field'] = 'title';
  $handler->display->display_options['filters']['title_1']['relationship'] = 'og_group_ref_target_id';
  $handler->display->display_options['filters']['title_1']['operator'] = 'contains';
  $handler->display->display_options['filters']['title_1']['group'] = 1;
  $handler->display->display_options['filters']['title_1']['exposed'] = TRUE;
  $handler->display->display_options['filters']['title_1']['expose']['operator_id'] = 'title_1_op';
  $handler->display->display_options['filters']['title_1']['expose']['label'] = 'Library';
  $handler->display->display_options['filters']['title_1']['expose']['operator'] = 'title_1_op';
  $handler->display->display_options['filters']['title_1']['expose']['identifier'] = 'title_1';
  $handler->display->display_options['filters']['title_1']['expose']['remember'] = TRUE;
  $handler->display->display_options['filters']['title_1']['expose']['remember_roles'] = array(
    2 => 2,
    1 => 0,
    3 => 0,
    4 => 0,
    5 => 0,
    6 => 0,
    7 => 0,
    8 => 0,
    9 => 0,
  );
  /* Filter criterion: Field: Library (og_group_ref) */
  $handler->display->display_options['filters']['og_group_ref_target_id']['id'] = 'og_group_ref_target_id';
  $handler->display->display_options['filters']['og_group_ref_target_id']['table'] = 'og_membership';
  $handler->display->display_options['filters']['og_group_ref_target_id']['field'] = 'og_group_ref_target_id';
  $handler->display->display_options['filters']['og_group_ref_target_id']['operator'] = 'empty';
  $handler->display->display_options['filters']['og_group_ref_target_id']['group'] = 2;
  /* Filter criterion: Content: Type */
  $handler->display->display_options['filters']['type_1']['id'] = 'type_1';
  $handler->display->display_options['filters']['type_1']['table'] = 'node';
  $handler->display->display_options['filters']['type_1']['field'] = 'type';
  $handler->display->display_options['filters']['type_1']['relationship'] = 'og_group_ref_target_id';
  $handler->display->display_options['filters']['type_1']['value'] = array(
    'ding_library' => 'ding_library',
  );
  $handler->display->display_options['filters']['type_1']['group'] = 2;
  /* Filter criterion: Profile: Forename (field_ding_staff_forename) */
  $handler->display->display_options['filters']['field_ding_staff_forename_value']['id'] = 'field_ding_staff_forename_value';
  $handler->display->display_options['filters']['field_ding_staff_forename_value']['table'] = 'field_data_field_ding_staff_forename';
  $handler->display->display_options['filters']['field_ding_staff_forename_value']['field'] = 'field_ding_staff_forename_value';
  $handler->display->display_options['filters']['field_ding_staff_forename_value']['relationship'] = 'profile';
  $handler->display->display_options['filters']['field_ding_staff_forename_value']['operator'] = 'contains';
  $handler->display->display_options['filters']['field_ding_staff_forename_value']['group'] = 3;
  $handler->display->display_options['filters']['field_ding_staff_forename_value']['exposed'] = TRUE;
  $handler->display->display_options['filters']['field_ding_staff_forename_value']['expose']['operator_id'] = 'field_ding_staff_forename_value_op';
  $handler->display->display_options['filters']['field_ding_staff_forename_value']['expose']['label'] = 'Author: Forename';
  $handler->display->display_options['filters']['field_ding_staff_forename_value']['expose']['operator'] = 'field_ding_staff_forename_value_op';
  $handler->display->display_options['filters']['field_ding_staff_forename_value']['expose']['identifier'] = 'field_ding_staff_forename_value';
  $handler->display->display_options['filters']['field_ding_staff_forename_value']['expose']['remember'] = TRUE;
  $handler->display->display_options['filters']['field_ding_staff_forename_value']['expose']['remember_roles'] = array(
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
  $handler->display->display_options['filters']['field_ding_staff_forename_value']['group_info']['label'] = 'Forename (field_ding_staff_forename)';
  $handler->display->display_options['filters']['field_ding_staff_forename_value']['group_info']['identifier'] = 'field_ding_staff_forename_value';
  $handler->display->display_options['filters']['field_ding_staff_forename_value']['group_info']['remember'] = FALSE;
  $handler->display->display_options['filters']['field_ding_staff_forename_value']['group_info']['group_items'] = array(
    1 => array(),
    2 => array(),
    3 => array(),
  );
  /* Filter criterion: Profile: Surname (field_ding_staff_surname) */
  $handler->display->display_options['filters']['field_ding_staff_surname_value']['id'] = 'field_ding_staff_surname_value';
  $handler->display->display_options['filters']['field_ding_staff_surname_value']['table'] = 'field_data_field_ding_staff_surname';
  $handler->display->display_options['filters']['field_ding_staff_surname_value']['field'] = 'field_ding_staff_surname_value';
  $handler->display->display_options['filters']['field_ding_staff_surname_value']['relationship'] = 'profile';
  $handler->display->display_options['filters']['field_ding_staff_surname_value']['operator'] = 'contains';
  $handler->display->display_options['filters']['field_ding_staff_surname_value']['group'] = 3;
  $handler->display->display_options['filters']['field_ding_staff_surname_value']['exposed'] = TRUE;
  $handler->display->display_options['filters']['field_ding_staff_surname_value']['expose']['operator_id'] = 'field_ding_staff_surname_value_op';
  $handler->display->display_options['filters']['field_ding_staff_surname_value']['expose']['label'] = 'Author: Surname';
  $handler->display->display_options['filters']['field_ding_staff_surname_value']['expose']['operator'] = 'field_ding_staff_surname_value_op';
  $handler->display->display_options['filters']['field_ding_staff_surname_value']['expose']['identifier'] = 'field_ding_staff_surname_value';
  $handler->display->display_options['filters']['field_ding_staff_surname_value']['expose']['remember'] = TRUE;
  $handler->display->display_options['filters']['field_ding_staff_surname_value']['expose']['remember_roles'] = array(
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

  /* Display: Content list */
  $handler = $view->new_display('panel_pane', 'Content list', 'content_list');
  $handler->display->display_options['pane_category']['name'] = 'Ding!';
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
  $handler->display->display_options['inherit_panels_path'] = '1';

  /* Display: Summary */
  $handler = $view->new_display('panel_pane', 'Summary', 'summary');
  $handler->display->display_options['defaults']['link_display'] = FALSE;
  $handler->display->display_options['link_display'] = 'custom_url';
  $handler->display->display_options['link_url'] = 'admin/workbench/content/all';
  $handler->display->display_options['defaults']['pager'] = FALSE;
  $handler->display->display_options['pager']['type'] = 'some';
  $handler->display->display_options['pager']['options']['items_per_page'] = '10';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['title']['alter']['ellipsis'] = FALSE;
  /* Field: Content: Date */
  $handler->display->display_options['fields']['field_ding_event_date']['id'] = 'field_ding_event_date';
  $handler->display->display_options['fields']['field_ding_event_date']['table'] = 'field_data_field_ding_event_date';
  $handler->display->display_options['fields']['field_ding_event_date']['field'] = 'field_ding_event_date';
  $handler->display->display_options['fields']['field_ding_event_date']['label'] = 'Event date';
  $handler->display->display_options['fields']['field_ding_event_date']['settings'] = array(
    'format_type' => 'short',
    'fromto' => 'both',
    'multiple_number' => '',
    'multiple_from' => '',
    'multiple_to' => '',
  );
  /* Field: Content: Type */
  $handler->display->display_options['fields']['type']['id'] = 'type';
  $handler->display->display_options['fields']['type']['table'] = 'node';
  $handler->display->display_options['fields']['type']['field'] = 'type';
  $handler->display->display_options['fields']['type']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['type']['alter']['ellipsis'] = FALSE;
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title_1']['id'] = 'title_1';
  $handler->display->display_options['fields']['title_1']['table'] = 'node';
  $handler->display->display_options['fields']['title_1']['field'] = 'title';
  $handler->display->display_options['fields']['title_1']['relationship'] = 'og_group_ref_target_id';
  $handler->display->display_options['fields']['title_1']['label'] = 'Library';
  /* Field: User: Name */
  $handler->display->display_options['fields']['name']['id'] = 'name';
  $handler->display->display_options['fields']['name']['table'] = 'users';
  $handler->display->display_options['fields']['name']['field'] = 'name';
  $handler->display->display_options['fields']['name']['relationship'] = 'uid';
  $handler->display->display_options['fields']['name']['label'] = '';
  $handler->display->display_options['fields']['name']['exclude'] = TRUE;
  $handler->display->display_options['fields']['name']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['name']['hide_alter_empty'] = FALSE;
  /* Field: User: Uid */
  $handler->display->display_options['fields']['uid']['id'] = 'uid';
  $handler->display->display_options['fields']['uid']['table'] = 'users';
  $handler->display->display_options['fields']['uid']['field'] = 'uid';
  $handler->display->display_options['fields']['uid']['relationship'] = 'uid';
  $handler->display->display_options['fields']['uid']['label'] = '';
  $handler->display->display_options['fields']['uid']['exclude'] = TRUE;
  $handler->display->display_options['fields']['uid']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['uid']['link_to_user'] = FALSE;
  /* Field: Profile: Forename */
  $handler->display->display_options['fields']['field_ding_staff_forename']['id'] = 'field_ding_staff_forename';
  $handler->display->display_options['fields']['field_ding_staff_forename']['table'] = 'field_data_field_ding_staff_forename';
  $handler->display->display_options['fields']['field_ding_staff_forename']['field'] = 'field_ding_staff_forename';
  $handler->display->display_options['fields']['field_ding_staff_forename']['relationship'] = 'profile';
  $handler->display->display_options['fields']['field_ding_staff_forename']['label'] = '';
  $handler->display->display_options['fields']['field_ding_staff_forename']['exclude'] = TRUE;
  $handler->display->display_options['fields']['field_ding_staff_forename']['element_label_colon'] = FALSE;
  /* Field: Profile: Surname */
  $handler->display->display_options['fields']['field_ding_staff_surname']['id'] = 'field_ding_staff_surname';
  $handler->display->display_options['fields']['field_ding_staff_surname']['table'] = 'field_data_field_ding_staff_surname';
  $handler->display->display_options['fields']['field_ding_staff_surname']['field'] = 'field_ding_staff_surname';
  $handler->display->display_options['fields']['field_ding_staff_surname']['relationship'] = 'profile';
  $handler->display->display_options['fields']['field_ding_staff_surname']['label'] = 'Author';
  $handler->display->display_options['fields']['field_ding_staff_surname']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['field_ding_staff_surname']['alter']['text'] = '[field_ding_staff_forename] [field_ding_staff_surname]';
  $handler->display->display_options['fields']['field_ding_staff_surname']['alter']['make_link'] = TRUE;
  $handler->display->display_options['fields']['field_ding_staff_surname']['alter']['path'] = 'user/[uid]';
  $handler->display->display_options['fields']['field_ding_staff_surname']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_ding_staff_surname']['empty'] = '[name]';
  /* Field: Content: Updated date */
  $handler->display->display_options['fields']['changed']['id'] = 'changed';
  $handler->display->display_options['fields']['changed']['table'] = 'node';
  $handler->display->display_options['fields']['changed']['field'] = 'changed';
  $handler->display->display_options['fields']['changed']['label'] = 'Last updated';
  $handler->display->display_options['fields']['changed']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['changed']['alter']['ellipsis'] = FALSE;
  $handler->display->display_options['fields']['changed']['date_format'] = 'time ago';
  $handler->display->display_options['fields']['changed']['second_date_format'] = 'ding_date_only';
  /* Field: Content: Edit link */
  $handler->display->display_options['fields']['edit_node']['id'] = 'edit_node';
  $handler->display->display_options['fields']['edit_node']['table'] = 'views_entity_node';
  $handler->display->display_options['fields']['edit_node']['field'] = 'edit_node';
  $handler->display->display_options['fields']['edit_node']['label'] = 'Actions';
  $handler->display->display_options['fields']['edit_node']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['edit_node']['alter']['ellipsis'] = FALSE;
  $handler->display->display_options['fields']['edit_node']['text'] = 'edit';
  $handler->display->display_options['defaults']['filter_groups'] = FALSE;
  $handler->display->display_options['filter_groups']['groups'] = array(
    1 => 'AND',
    2 => 'OR',
  );
  $handler->display->display_options['defaults']['filters'] = FALSE;
  /* Filter criterion: Content: Published or admin */
  $handler->display->display_options['filters']['status_extra']['id'] = 'status_extra';
  $handler->display->display_options['filters']['status_extra']['table'] = 'node';
  $handler->display->display_options['filters']['status_extra']['field'] = 'status_extra';
  $handler->display->display_options['filters']['status_extra']['group'] = 1;
  $handler->display->display_options['pane_category']['name'] = 'Ding!';
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
  $translatables['ding_content_workbench'] = array(
    t('Defaults'),
    t('All Recent Content'),
    t('view all'),
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
    t('There is no content available for you to edit.'),
    t('author'),
    t('Library'),
    t('Profile'),
    t('Title'),
    t('Type'),
    t('Event date'),
    t('Author'),
    t('[field_ding_staff_forename] [field_ding_staff_surname]'),
    t('[name]'),
    t('Udgivet'),
    t('Last updated'),
    t('Language'),
    t('Actions'),
    t('edit'),
    t('Published'),
    t('Author: Forename'),
    t('Forename (field_ding_staff_forename)'),
    t('Author: Surname'),
    t('Content list'),
    t('more'),
    t('Ding!'),
    t('Summary'),
  );
  $export['ding_content_workbench'] = $view;

  $view = new view();
  $view->name = 'tags_list';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'node';
  $view->human_name = 'Tags list';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['css_class'] = 'view-node-search-result';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['style_plugin'] = 'list';
  $handler->display->display_options['style_options']['row_class'] = 'list-item search-result';
  $handler->display->display_options['style_options']['default_row_class'] = FALSE;
  $handler->display->display_options['style_options']['row_class_special'] = FALSE;
  $handler->display->display_options['style_options']['class'] = 'list floated';
  $handler->display->display_options['style_options']['wrapper_class'] = 'search-results';
  $handler->display->display_options['row_plugin'] = 'entity';
  $handler->display->display_options['row_options']['view_mode'] = 'search_result';
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
  /* Contextual filter: Content: Has taxonomy term ID */
  $handler->display->display_options['arguments']['tid']['id'] = 'tid';
  $handler->display->display_options['arguments']['tid']['table'] = 'taxonomy_index';
  $handler->display->display_options['arguments']['tid']['field'] = 'tid';
  $handler->display->display_options['arguments']['tid']['default_action'] = 'empty';
  $handler->display->display_options['arguments']['tid']['default_argument_type'] = 'fixed';
  $handler->display->display_options['arguments']['tid']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['tid']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['tid']['summary_options']['items_per_page'] = '25';
  /* Filter criterion: Content: Published */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'node';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = 1;
  $handler->display->display_options['filters']['status']['group'] = 1;
  $handler->display->display_options['filters']['status']['expose']['operator'] = FALSE;

  /* Display: Tags */
  $handler = $view->new_display('panel_pane', 'Tags', 'ding_content_tags');
  $handler->display->display_options['pane_title'] = 'Nodes based on tag';
  $handler->display->display_options['pane_category']['name'] = 'Taxonomy term';
  $handler->display->display_options['pane_category']['weight'] = '0';
  $handler->display->display_options['argument_input'] = array(
    'tid' => array(
      'type' => 'context',
      'context' => 'entity:taxonomy_term.tid',
      'context_optional' => 0,
      'panel' => '0',
      'fixed' => '',
      'label' => 'Content: Has taxonomy term ID',
    ),
  );
  $translatables['tags_list'] = array(
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
    t('All'),
    t('Tags'),
    t('Nodes based on tag'),
    t('Taxonomy term'),
  );
  $export['tags_list'] = $view;

  return $export;
}
