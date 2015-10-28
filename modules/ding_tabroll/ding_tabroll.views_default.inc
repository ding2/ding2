<?php
/**
 * @file
 * ding_tabroll.views_default.inc
 */

/**
 * Implements hook_views_default_views().
 */
function ding_tabroll_views_default_views() {
  $export = array();

  $view = new view();
  $view->name = 'ding_tabroll';
  $view->description = 'Display a list of all nodes in queue \'frontpage tabroll\'';
  $view->tag = 'nodequeue';
  $view->base_table = 'node';
  $view->human_name = 'Ding frontpage tabroll';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['use_more_text'] = 'See more';
  $handler->display->display_options['access']['type'] = 'none';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['query']['options']['query_comment'] = FALSE;
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['exposed_form']['options']['reset_button_label'] = 'Revert';
  $handler->display->display_options['pager']['type'] = 'some';
  $handler->display->display_options['pager']['options']['items_per_page'] = '5';
  $handler->display->display_options['style_plugin'] = 'default';
  $handler->display->display_options['style_options']['default_row_class'] = FALSE;
  $handler->display->display_options['style_options']['row_class_special'] = FALSE;
  $handler->display->display_options['row_plugin'] = 'fields';
  $handler->display->display_options['row_options']['default_field_elements'] = FALSE;
  /* Relationship: Nodequeue: Queue */
  $handler->display->display_options['relationships']['nodequeue_rel']['id'] = 'nodequeue_rel';
  $handler->display->display_options['relationships']['nodequeue_rel']['table'] = 'node';
  $handler->display->display_options['relationships']['nodequeue_rel']['field'] = 'nodequeue_rel';
  $handler->display->display_options['relationships']['nodequeue_rel']['label'] = 'frontpage tabroll';
  $handler->display->display_options['relationships']['nodequeue_rel']['required'] = TRUE;
  $handler->display->display_options['relationships']['nodequeue_rel']['limit'] = 1;
  $handler->display->display_options['relationships']['nodequeue_rel']['names'] = array(
    'ding_tabroll_frontpage' => 'ding_tabroll_frontpage',
    'ding_groups_listning' => 0,
    'ding_library_listing' => 0,
    'ding_tabroll_libraries' => 0,
  );
  /* Relationship: Entity Reference: Referenced Entity */
  $handler->display->display_options['relationships']['field_ding_tabroll_link_target_id']['id'] = 'field_ding_tabroll_link_target_id';
  $handler->display->display_options['relationships']['field_ding_tabroll_link_target_id']['table'] = 'field_data_field_ding_tabroll_link';
  $handler->display->display_options['relationships']['field_ding_tabroll_link_target_id']['field'] = 'field_ding_tabroll_link_target_id';
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = '';
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['title']['alter']['ellipsis'] = FALSE;
  $handler->display->display_options['fields']['title']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['title']['element_default_classes'] = FALSE;
  $handler->display->display_options['fields']['title']['link_to_node'] = FALSE;
  /* Field: Content: Image */
  $handler->display->display_options['fields']['field_ding_tabroll_image']['id'] = 'field_ding_tabroll_image';
  $handler->display->display_options['fields']['field_ding_tabroll_image']['table'] = 'field_data_field_ding_tabroll_image';
  $handler->display->display_options['fields']['field_ding_tabroll_image']['field'] = 'field_ding_tabroll_image';
  $handler->display->display_options['fields']['field_ding_tabroll_image']['label'] = '';
  $handler->display->display_options['fields']['field_ding_tabroll_image']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_ding_tabroll_image']['element_default_classes'] = FALSE;
  $handler->display->display_options['fields']['field_ding_tabroll_image']['click_sort_column'] = 'fid';
  $handler->display->display_options['fields']['field_ding_tabroll_image']['type'] = 'cs_adaptive_image';
  $handler->display->display_options['fields']['field_ding_tabroll_image']['settings'] = array(
    'relationship' => 'none',
    'ui_name' => '',
    'custom_label' => 0,
    'label' => '',
    'element_label_colon' => 0,
    'exclude' => 0,
    'element_type_enable' => 0,
    'element_type' => '',
    'element_class_enable' => 0,
    'element_class' => '',
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
      'html' => 0,
      'strip_tags' => 0,
      'trim_whitespace' => 0,
      'preserve_tags' => '',
      'nl2br' => 0,
    ),
    'empty' => '',
    'empty_zero' => 0,
    'hide_empty' => 0,
    'hide_alter_empty' => 1,
    'click_sort_column' => 'fid',
    'type' => 'cs_adaptive_image',
    'field_api_classes' => 0,
    'image_link' => '',
    'styles' => array(
      'breakpoint_1' => '768',
      'style_1' => 'ding_tabroll_medium',
      'breakpoint_2' => '500',
      'style_2' => 'ding_tabroll_small',
      'max_style' => 'ding_tabroll_large',
      'fallback_style' => 'ding_tabroll_large',
    ),
  );
  /* Field: Content: Lead */
  $handler->display->display_options['fields']['field_ding_tabroll_lead']['id'] = 'field_ding_tabroll_lead';
  $handler->display->display_options['fields']['field_ding_tabroll_lead']['table'] = 'field_data_field_ding_tabroll_lead';
  $handler->display->display_options['fields']['field_ding_tabroll_lead']['field'] = 'field_ding_tabroll_lead';
  $handler->display->display_options['fields']['field_ding_tabroll_lead']['label'] = '';
  $handler->display->display_options['fields']['field_ding_tabroll_lead']['element_type'] = 'p';
  $handler->display->display_options['fields']['field_ding_tabroll_lead']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_ding_tabroll_lead']['element_default_classes'] = FALSE;
  /* Field: Content: Link */
  $handler->display->display_options['fields']['field_ding_tabroll_link']['id'] = 'field_ding_tabroll_link';
  $handler->display->display_options['fields']['field_ding_tabroll_link']['table'] = 'field_data_field_ding_tabroll_link';
  $handler->display->display_options['fields']['field_ding_tabroll_link']['field'] = 'field_ding_tabroll_link';
  $handler->display->display_options['fields']['field_ding_tabroll_link']['relationship'] = 'field_ding_tabroll_link_target_id';
  $handler->display->display_options['fields']['field_ding_tabroll_link']['label'] = '';
  $handler->display->display_options['fields']['field_ding_tabroll_link']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_ding_tabroll_link']['element_default_classes'] = FALSE;
  $handler->display->display_options['fields']['field_ding_tabroll_link']['type'] = 'entityreference_entity_id';
  $handler->display->display_options['fields']['field_ding_tabroll_link']['settings'] = array(
    'link' => 0,
  );
  /* Sort criterion: Nodequeue: Position */
  $handler->display->display_options['sorts']['position']['id'] = 'position';
  $handler->display->display_options['sorts']['position']['table'] = 'nodequeue_nodes';
  $handler->display->display_options['sorts']['position']['field'] = 'position';
  $handler->display->display_options['sorts']['position']['relationship'] = 'nodequeue_rel';
  /* Filter criterion: Content: Published */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'node';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = 1;
  $handler->display->display_options['filters']['status']['group'] = 1;
  $handler->display->display_options['filters']['status']['expose']['operator'] = FALSE;

  /* Display: Ding frontpage tabroll */
  $handler = $view->new_display('panel_pane', 'Ding frontpage tabroll', 'ding_frontpage_tabroll');
  $handler->display->display_options['display_description'] = 'Ding frontpage tabroll';
  $handler->display->display_options['pane_title'] = 'Ding frontpage tabroll';
  $handler->display->display_options['pane_description'] = 'Ding frontpage tablroll';
  $handler->display->display_options['pane_category']['name'] = 'Ding!';
  $handler->display->display_options['pane_category']['weight'] = '0';
  $translatables['ding_tabroll'] = array(
    t('Master'),
    t('See more'),
    t('Apply'),
    t('Revert'),
    t('Sort by'),
    t('Asc'),
    t('Desc'),
    t('frontpage tabroll'),
    t('Content entity referenced from field_ding_tabroll_link'),
    t('Ding frontpage tabroll'),
    t('more'),
    t('Ding frontpage tablroll'),
    t('Ding!'),
  );
  $export['ding_tabroll'] = $view;

  return $export;
}
