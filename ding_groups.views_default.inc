<?php
/**
 * @file
 * ding_groups.views_default.inc
 */

/**
 * Implements hook_views_default_views().
 */
function ding_groups_views_default_views() {
  $export = array();

  $view = new view();
  $view->name = 'ding_groups';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'node';
  $view->human_name = 'Groups (temapages)';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['style_plugin'] = 'list';
  $handler->display->display_options['style_options']['row_class'] = 'groups-list-item';
  $handler->display->display_options['style_options']['class'] = 'list groups-list';
  $handler->display->display_options['style_options']['wrapper_class'] = '';
  $handler->display->display_options['row_plugin'] = 'fields';
  /* Field: Content: List image */
  $handler->display->display_options['fields']['field_ding_group_list_image']['id'] = 'field_ding_group_list_image';
  $handler->display->display_options['fields']['field_ding_group_list_image']['table'] = 'field_data_field_ding_group_list_image';
  $handler->display->display_options['fields']['field_ding_group_list_image']['field'] = 'field_ding_group_list_image';
  $handler->display->display_options['fields']['field_ding_group_list_image']['label'] = '';
  $handler->display->display_options['fields']['field_ding_group_list_image']['element_type'] = 'div';
  $handler->display->display_options['fields']['field_ding_group_list_image']['element_class'] = 'group-image-wrapper';
  $handler->display->display_options['fields']['field_ding_group_list_image']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_ding_group_list_image']['element_default_classes'] = FALSE;
  $handler->display->display_options['fields']['field_ding_group_list_image']['click_sort_column'] = 'fid';
  $handler->display->display_options['fields']['field_ding_group_list_image']['type'] = 'cs_adaptive_image';
  $handler->display->display_options['fields']['field_ding_group_list_image']['settings'] = array(
    'image_link' => '',
    'styles' => array(
      'breakpoint_1' => '768',
      'style_1' => 'ding_list_medium',
      'breakpoint_2' => '500',
      'style_2' => 'ding_list_small',
      'max_style' => 'ding_list_medium',
      'fallback_style' => 'ding_list_medium',
    ),
  );
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = '';
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['title']['alter']['ellipsis'] = FALSE;
  $handler->display->display_options['fields']['title']['element_type'] = 'h3';
  $handler->display->display_options['fields']['title']['element_class'] = 'group-heading';
  $handler->display->display_options['fields']['title']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['title']['element_default_classes'] = FALSE;
  /* Field: Content: Lead */
  $handler->display->display_options['fields']['field_ding_group_lead']['id'] = 'field_ding_group_lead';
  $handler->display->display_options['fields']['field_ding_group_lead']['table'] = 'field_data_field_ding_group_lead';
  $handler->display->display_options['fields']['field_ding_group_lead']['field'] = 'field_ding_group_lead';
  $handler->display->display_options['fields']['field_ding_group_lead']['label'] = '';
  $handler->display->display_options['fields']['field_ding_group_lead']['element_label_colon'] = FALSE;
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
    'ding_group' => 'ding_group',
  );

  /* Display: Group overview (simple) */
  $handler = $view->new_display('panel_pane', 'Group overview (simple)', 'ding_group_overview_simple');
  $handler->display->display_options['display_description'] = 'Simply list all groups';
  $translatables['ding_groups'] = array(
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
    t('Group overview (simple)'),
    t('Simply list all groups'),
    t('View panes'),
  );
  $export['ding_groups'] = $view;

  return $export;
}
