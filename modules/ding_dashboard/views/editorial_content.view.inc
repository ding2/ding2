<?php
/**
 * @file
 * Editorial content view export.
 */

$view = new view();
$view->name = 'workbench_new_editorial_content';
$view->description = 'Editorial content overview';
$view->tag = 'Workbench';
$view->base_table = 'node';
$view->human_name = 'Workbench: Editorial Content';
$view->core = 7;
$view->api_version = '3.0';
$view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

/* Display: Defaults */
$handler = $view->new_display('default', 'Defaults', 'default');
$handler->display->display_options['title'] = 'Editorial content';
$handler->display->display_options['use_more_always'] = TRUE;
$handler->display->display_options['use_more_text'] = 'view all';
$handler->display->display_options['access']['type'] = 'perm';
$handler->display->display_options['access']['perm'] = 'access workbench';
$handler->display->display_options['cache']['type'] = 'none';
$handler->display->display_options['query']['type'] = 'views_query';
$handler->display->display_options['query']['options']['query_tags'] = array(
  0 => 'editorial_content',
);
$handler->display->display_options['exposed_form']['type'] = 'basic';
$handler->display->display_options['exposed_form']['options']['reset_button'] = TRUE;
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
  'field_editorial_status' => 'field_editorial_status',
  'status' => 'status',
  'name' => 'name',
  'changed' => 'changed',
  'edit_node' => 'edit_node',
  'ed_push_node' => 'ed_push_node',
  'ed_approve_node' => 'ed_approve_node',
  'ed_reject_node' => 'ed_reject_node',
  'ed_restore_node' => 'ed_restore_node',
  'ed_delete_node' => 'ed_delete_node',
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
  'field_editorial_status' => array(
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
    'sortable' => 1,
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
  'ed_push_node' => array(
    'align' => '',
    'separator' => '',
    'empty_column' => 1,
  ),
  'ed_approve_node' => array(
    'align' => '',
    'separator' => '',
    'empty_column' => 1,
  ),
  'ed_reject_node' => array(
    'align' => '',
    'separator' => '',
    'empty_column' => 1,
  ),
  'ed_restore_node' => array(
    'align' => '',
    'separator' => '',
    'empty_column' => 1,
  ),
  'ed_delete_node' => array(
    'align' => '',
    'separator' => '',
    'empty_column' => 1,
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
/* Field: User: Name */
$handler->display->display_options['fields']['name']['id'] = 'name';
$handler->display->display_options['fields']['name']['table'] = 'users';
$handler->display->display_options['fields']['name']['field'] = 'name';
$handler->display->display_options['fields']['name']['relationship'] = 'uid';
$handler->display->display_options['fields']['name']['label'] = 'Author';
$handler->display->display_options['fields']['name']['element_label_colon'] = FALSE;
$handler->display->display_options['fields']['name']['hide_alter_empty'] = FALSE;
/* Field: Content: Updated date */
$handler->display->display_options['fields']['changed']['id'] = 'changed';
$handler->display->display_options['fields']['changed']['table'] = 'node';
$handler->display->display_options['fields']['changed']['field'] = 'changed';
$handler->display->display_options['fields']['changed']['label'] = 'Last updated';
$handler->display->display_options['fields']['changed']['alter']['word_boundary'] = FALSE;
$handler->display->display_options['fields']['changed']['alter']['ellipsis'] = FALSE;
$handler->display->display_options['fields']['changed']['date_format'] = 'time ago';
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
$handler->display->display_options['filters']['type']['expose']['operator_id'] = 'type_op';
$handler->display->display_options['filters']['type']['expose']['label'] = 'Type';
$handler->display->display_options['filters']['type']['expose']['operator'] = 'type_op';
$handler->display->display_options['filters']['type']['expose']['identifier'] = 'type';
$handler->display->display_options['filters']['type']['expose']['remember_roles'] = array(
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
/* Filter criterion: Content: Published */
$handler->display->display_options['filters']['status']['id'] = 'status';
$handler->display->display_options['filters']['status']['table'] = 'node';
$handler->display->display_options['filters']['status']['field'] = 'status';
$handler->display->display_options['filters']['status']['value'] = 'All';
$handler->display->display_options['filters']['status']['group'] = 1;
$handler->display->display_options['filters']['status']['exposed'] = TRUE;
$handler->display->display_options['filters']['status']['expose']['operator_id'] = '';
$handler->display->display_options['filters']['status']['expose']['label'] = 'Published';
$handler->display->display_options['filters']['status']['expose']['identifier'] = 'published';
$handler->display->display_options['filters']['status']['expose']['remember_roles'] = array(
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
/* Filter criterion: Content: Editorial status (field_editorial_status) */
$handler->display->display_options['filters']['field_editorial_status_value']['id'] = 'field_editorial_status_value';
$handler->display->display_options['filters']['field_editorial_status_value']['table'] = 'field_data_field_editorial_status';
$handler->display->display_options['filters']['field_editorial_status_value']['field'] = 'field_editorial_status_value';
$handler->display->display_options['filters']['field_editorial_status_value']['group'] = 1;
$handler->display->display_options['filters']['field_editorial_status_value']['exposed'] = TRUE;
$handler->display->display_options['filters']['field_editorial_status_value']['expose']['operator_id'] = 'field_editorial_status_value_op';
$handler->display->display_options['filters']['field_editorial_status_value']['expose']['label'] = 'Editorial status';
$handler->display->display_options['filters']['field_editorial_status_value']['expose']['operator'] = 'field_editorial_status_value_op';
$handler->display->display_options['filters']['field_editorial_status_value']['expose']['identifier'] = 'field_editorial_status_value';
$handler->display->display_options['filters']['field_editorial_status_value']['expose']['remember_roles'] = array(
  2 => '2',
  1 => 0,
  4 => 0,
  5 => 0,
  6 => 0,
  3 => 0,
  7 => 0,
  8 => 0,
  9 => 0,
);
/* Filter criterion: User: Current */
$handler->display->display_options['filters']['uid_current']['id'] = 'uid_current';
$handler->display->display_options['filters']['uid_current']['table'] = 'users';
$handler->display->display_options['filters']['uid_current']['field'] = 'uid_current';
$handler->display->display_options['filters']['uid_current']['relationship'] = 'uid';
$handler->display->display_options['filters']['uid_current']['value'] = 'All';
$handler->display->display_options['filters']['uid_current']['exposed'] = TRUE;
$handler->display->display_options['filters']['uid_current']['expose']['operator_id'] = '';
$handler->display->display_options['filters']['uid_current']['expose']['label'] = 'My content';
$handler->display->display_options['filters']['uid_current']['expose']['operator'] = 'uid_current_op';
$handler->display->display_options['filters']['uid_current']['expose']['identifier'] = 'uid_current';
$handler->display->display_options['filters']['uid_current']['expose']['remember_roles'] = array(
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

/* Display: Page */
$handler = $view->new_display('page', 'Page', 'page_1');
$handler->display->display_options['defaults']['hide_admin_links'] = FALSE;
$handler->display->display_options['defaults']['fields'] = FALSE;
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
/* Field: Content: Editorial status */
$handler->display->display_options['fields']['field_editorial_status']['id'] = 'field_editorial_status';
$handler->display->display_options['fields']['field_editorial_status']['table'] = 'field_data_field_editorial_status';
$handler->display->display_options['fields']['field_editorial_status']['field'] = 'field_editorial_status';
$handler->display->display_options['fields']['field_editorial_status']['label'] = 'Status';
/* Field: Content: Published */
$handler->display->display_options['fields']['status']['id'] = 'status';
$handler->display->display_options['fields']['status']['table'] = 'node';
$handler->display->display_options['fields']['status']['field'] = 'status';
$handler->display->display_options['fields']['status']['alter']['word_boundary'] = FALSE;
$handler->display->display_options['fields']['status']['alter']['ellipsis'] = FALSE;
$handler->display->display_options['fields']['status']['not'] = 0;
/* Field: User: Name */
$handler->display->display_options['fields']['name']['id'] = 'name';
$handler->display->display_options['fields']['name']['table'] = 'users';
$handler->display->display_options['fields']['name']['field'] = 'name';
$handler->display->display_options['fields']['name']['relationship'] = 'uid';
$handler->display->display_options['fields']['name']['label'] = 'Author';
$handler->display->display_options['fields']['name']['element_label_colon'] = FALSE;
/* Field: Content: Updated date */
$handler->display->display_options['fields']['changed']['id'] = 'changed';
$handler->display->display_options['fields']['changed']['table'] = 'node';
$handler->display->display_options['fields']['changed']['field'] = 'changed';
$handler->display->display_options['fields']['changed']['label'] = 'Last updated';
$handler->display->display_options['fields']['changed']['alter']['word_boundary'] = FALSE;
$handler->display->display_options['fields']['changed']['alter']['ellipsis'] = FALSE;
$handler->display->display_options['fields']['changed']['date_format'] = 'time ago';
/* Field: Content: Edit link */
$handler->display->display_options['fields']['edit_node']['id'] = 'edit_node';
$handler->display->display_options['fields']['edit_node']['table'] = 'views_entity_node';
$handler->display->display_options['fields']['edit_node']['field'] = 'edit_node';
$handler->display->display_options['fields']['edit_node']['label'] = 'Actions';
$handler->display->display_options['fields']['edit_node']['alter']['word_boundary'] = FALSE;
$handler->display->display_options['fields']['edit_node']['alter']['ellipsis'] = FALSE;
$handler->display->display_options['fields']['edit_node']['text'] = 'edit';
/* Field: Content: Editorial Push link */
$handler->display->display_options['fields']['ed_push_node']['id'] = 'ed_push_node';
$handler->display->display_options['fields']['ed_push_node']['table'] = 'views_entity_node';
$handler->display->display_options['fields']['ed_push_node']['field'] = 'ed_push_node';
$handler->display->display_options['fields']['ed_push_node']['label'] = '';
$handler->display->display_options['fields']['ed_push_node']['element_label_colon'] = FALSE;
$handler->display->display_options['fields']['ed_push_node']['hide_empty'] = TRUE;
$handler->display->display_options['fields']['ed_push_node']['text'] = 'push for approval';
/* Field: Content: Editorial Approve link */
$handler->display->display_options['fields']['ed_approve_node']['id'] = 'ed_approve_node';
$handler->display->display_options['fields']['ed_approve_node']['table'] = 'views_entity_node';
$handler->display->display_options['fields']['ed_approve_node']['field'] = 'ed_approve_node';
$handler->display->display_options['fields']['ed_approve_node']['label'] = '';
$handler->display->display_options['fields']['ed_approve_node']['element_label_colon'] = FALSE;
$handler->display->display_options['fields']['ed_approve_node']['text'] = 'approve';
/* Field: Content: Editorial Reject link */
$handler->display->display_options['fields']['ed_reject_node']['id'] = 'ed_reject_node';
$handler->display->display_options['fields']['ed_reject_node']['table'] = 'views_entity_node';
$handler->display->display_options['fields']['ed_reject_node']['field'] = 'ed_reject_node';
$handler->display->display_options['fields']['ed_reject_node']['label'] = '';
$handler->display->display_options['fields']['ed_reject_node']['element_label_colon'] = FALSE;
$handler->display->display_options['fields']['ed_reject_node']['hide_empty'] = TRUE;
$handler->display->display_options['fields']['ed_reject_node']['text'] = 'reject';
/* Field: Content: Editorial Delete link */
$handler->display->display_options['fields']['ed_delete_node']['id'] = 'ed_delete_node';
$handler->display->display_options['fields']['ed_delete_node']['table'] = 'views_entity_node';
$handler->display->display_options['fields']['ed_delete_node']['field'] = 'ed_delete_node';
$handler->display->display_options['fields']['ed_delete_node']['label'] = '';
$handler->display->display_options['fields']['ed_delete_node']['element_label_colon'] = FALSE;
$handler->display->display_options['fields']['ed_delete_node']['hide_empty'] = TRUE;
$handler->display->display_options['fields']['ed_delete_node']['text'] = 'delete';
/* Field: BPI: BPI status field and action */
$handler->display->display_options['fields']['status_1']['id'] = 'status_1';
$handler->display->display_options['fields']['status_1']['table'] = 'bpi_syndicated';
$handler->display->display_options['fields']['status_1']['field'] = 'status';
/* Field: BPI: BPI syndicated */
$handler->display->display_options['fields']['time']['id'] = 'time';
$handler->display->display_options['fields']['time']['table'] = 'bpi_syndicated';
$handler->display->display_options['fields']['time']['field'] = 'time';
$handler->display->display_options['path'] = 'admin/workbench/content/editorial';
$handler->display->display_options['menu']['type'] = 'tab';
$handler->display->display_options['menu']['title'] = 'Editorial content';
$handler->display->display_options['menu']['weight'] = '2';
$handler->display->display_options['menu']['context'] = 0;
$handler->display->display_options['menu']['context_only_inline'] = 0;
$translatables['workbench_new_editorial_content'] = array(
  t('Defaults'),
  t('Editorial content'),
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
  t('Title'),
  t('Type'),
  t('Author'),
  t('Last updated'),
  t('Actions'),
  t('edit'),
  t('Published'),
  t('Editorial status'),
  t('My content'),
  t('Page'),
  t('more'),
  t('Status'),
  t('push for approval'),
  t('approve'),
  t('reject'),
  t('delete'),
  t('BPI status field and action'),
  t('BPI syndicated'),
);
