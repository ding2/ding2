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
  $view->human_name = 'Ding groups (temapages)';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Themes';
  $handler->display->display_options['use_more'] = TRUE;
  $handler->display->display_options['use_more_always'] = TRUE;
  $handler->display->display_options['use_more_text'] = 'See all themes';
  $handler->display->display_options['link_display'] = 'custom_url';
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['style_plugin'] = 'list';
  $handler->display->display_options['style_options']['grouping'] = array(
    0 => array(
      'field' => 'field_ding_group_category',
      'rendered' => 1,
      'rendered_strip' => 0,
    ),
  );
  $handler->display->display_options['style_options']['row_class'] = 'groups-list-item';
  $handler->display->display_options['style_options']['class'] = 'list groups-list';
  $handler->display->display_options['style_options']['wrapper_class'] = '';
  $handler->display->display_options['row_plugin'] = 'fields';
  $handler->display->display_options['row_options']['default_field_elements'] = FALSE;
  /* Relationship: Nodequeue: Queue */
  $handler->display->display_options['relationships']['nodequeue_rel']['id'] = 'nodequeue_rel';
  $handler->display->display_options['relationships']['nodequeue_rel']['table'] = 'node';
  $handler->display->display_options['relationships']['nodequeue_rel']['field'] = 'nodequeue_rel';
  $handler->display->display_options['relationships']['nodequeue_rel']['limit'] = 1;
  $handler->display->display_options['relationships']['nodequeue_rel']['names'] = array(
    'ding_groups_listning' => 'ding_groups_listning',
    'ding_tabroll' => 0,
    'ding_tabroll_for_libraries' => 0,
  );
  /* Field: Category (groups rows) */
  $handler->display->display_options['fields']['field_ding_group_category']['id'] = 'field_ding_group_category';
  $handler->display->display_options['fields']['field_ding_group_category']['table'] = 'field_data_field_ding_group_category';
  $handler->display->display_options['fields']['field_ding_group_category']['field'] = 'field_ding_group_category';
  $handler->display->display_options['fields']['field_ding_group_category']['ui_name'] = 'Category (groups rows)';
  $handler->display->display_options['fields']['field_ding_group_category']['label'] = '';
  $handler->display->display_options['fields']['field_ding_group_category']['exclude'] = TRUE;
  $handler->display->display_options['fields']['field_ding_group_category']['element_type'] = 'h3';
  $handler->display->display_options['fields']['field_ding_group_category']['element_class'] = 'groups-list-group';
  $handler->display->display_options['fields']['field_ding_group_category']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_ding_group_category']['element_default_classes'] = FALSE;
  $handler->display->display_options['fields']['field_ding_group_category']['type'] = 'taxonomy_term_reference_plain';
  /* Field: Content: List image */
  $handler->display->display_options['fields']['field_ding_group_list_image']['id'] = 'field_ding_group_list_image';
  $handler->display->display_options['fields']['field_ding_group_list_image']['table'] = 'field_data_field_ding_group_list_image';
  $handler->display->display_options['fields']['field_ding_group_list_image']['field'] = 'field_ding_group_list_image';
  $handler->display->display_options['fields']['field_ding_group_list_image']['label'] = '';
  $handler->display->display_options['fields']['field_ding_group_list_image']['element_type'] = 'div';
  $handler->display->display_options['fields']['field_ding_group_list_image']['element_class'] = 'groups-image-wrapper';
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
  $handler->display->display_options['fields']['title']['element_class'] = 'groups-heading';
  $handler->display->display_options['fields']['title']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['title']['element_default_classes'] = FALSE;
  /* Field: Content: Lead */
  $handler->display->display_options['fields']['field_ding_group_lead']['id'] = 'field_ding_group_lead';
  $handler->display->display_options['fields']['field_ding_group_lead']['table'] = 'field_data_field_ding_group_lead';
  $handler->display->display_options['fields']['field_ding_group_lead']['field'] = 'field_ding_group_lead';
  $handler->display->display_options['fields']['field_ding_group_lead']['label'] = '';
  $handler->display->display_options['fields']['field_ding_group_lead']['element_type'] = 'div';
  $handler->display->display_options['fields']['field_ding_group_lead']['element_class'] = 'groups-list-content';
  $handler->display->display_options['fields']['field_ding_group_lead']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_ding_group_lead']['element_default_classes'] = FALSE;
  /* Field: Link (arrow) */
  $handler->display->display_options['fields']['view_node']['id'] = 'view_node';
  $handler->display->display_options['fields']['view_node']['table'] = 'views_entity_node';
  $handler->display->display_options['fields']['view_node']['field'] = 'view_node';
  $handler->display->display_options['fields']['view_node']['ui_name'] = 'Link (arrow)';
  $handler->display->display_options['fields']['view_node']['label'] = '';
  $handler->display->display_options['fields']['view_node']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['view_node']['alter']['text'] = '<i class="icon-chevron-right"></i>';
  $handler->display->display_options['fields']['view_node']['element_type'] = 'div';
  $handler->display->display_options['fields']['view_node']['element_class'] = 'groups-arrow-link';
  $handler->display->display_options['fields']['view_node']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['view_node']['element_default_classes'] = FALSE;
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
  $handler->display->display_options['defaults']['use_more'] = FALSE;
  $handler->display->display_options['defaults']['use_more_always'] = FALSE;
  $handler->display->display_options['defaults']['use_more_always'] = FALSE;
  $handler->display->display_options['use_more_always'] = TRUE;
  $handler->display->display_options['defaults']['use_more_text'] = FALSE;
  $handler->display->display_options['use_more_text'] = 'See all themes';
  $handler->display->display_options['defaults']['link_display'] = FALSE;
  $handler->display->display_options['link_display'] = 'custom_url';
  $handler->display->display_options['defaults']['pager'] = FALSE;
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = '20';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['pager']['options']['id'] = '0';
  $handler->display->display_options['pager']['options']['quantity'] = '9';
  $handler->display->display_options['defaults']['style_plugin'] = FALSE;
  $handler->display->display_options['style_plugin'] = 'default';
  $handler->display->display_options['defaults']['style_options'] = FALSE;
  $handler->display->display_options['defaults']['row_plugin'] = FALSE;
  $handler->display->display_options['row_plugin'] = 'node';
  $handler->display->display_options['row_options']['links'] = FALSE;
  $handler->display->display_options['defaults']['row_options'] = FALSE;
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Field: Category (groups rows) */
  $handler->display->display_options['fields']['field_ding_group_category']['id'] = 'field_ding_group_category';
  $handler->display->display_options['fields']['field_ding_group_category']['table'] = 'field_data_field_ding_group_category';
  $handler->display->display_options['fields']['field_ding_group_category']['field'] = 'field_ding_group_category';
  $handler->display->display_options['fields']['field_ding_group_category']['ui_name'] = 'Category (groups rows)';
  $handler->display->display_options['fields']['field_ding_group_category']['label'] = '';
  $handler->display->display_options['fields']['field_ding_group_category']['exclude'] = TRUE;
  $handler->display->display_options['fields']['field_ding_group_category']['element_type'] = 'h3';
  $handler->display->display_options['fields']['field_ding_group_category']['element_class'] = 'groups-list-group';
  $handler->display->display_options['fields']['field_ding_group_category']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_ding_group_category']['element_default_classes'] = FALSE;
  $handler->display->display_options['fields']['field_ding_group_category']['type'] = 'taxonomy_term_reference_plain';
  /* Field: Content: List image */
  $handler->display->display_options['fields']['field_ding_group_list_image']['id'] = 'field_ding_group_list_image';
  $handler->display->display_options['fields']['field_ding_group_list_image']['table'] = 'field_data_field_ding_group_list_image';
  $handler->display->display_options['fields']['field_ding_group_list_image']['field'] = 'field_ding_group_list_image';
  $handler->display->display_options['fields']['field_ding_group_list_image']['label'] = '';
  $handler->display->display_options['fields']['field_ding_group_list_image']['element_type'] = 'div';
  $handler->display->display_options['fields']['field_ding_group_list_image']['element_class'] = 'groups-image-wrapper';
  $handler->display->display_options['fields']['field_ding_group_list_image']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_ding_group_list_image']['element_default_classes'] = FALSE;
  $handler->display->display_options['fields']['field_ding_group_list_image']['click_sort_column'] = 'fid';
  $handler->display->display_options['fields']['field_ding_group_list_image']['type'] = 'cs_adaptive_image';
  $handler->display->display_options['fields']['field_ding_group_list_image']['settings'] = array(
    'image_link' => 'content',
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
  $handler->display->display_options['fields']['title']['element_class'] = 'groups-heading';
  $handler->display->display_options['fields']['title']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['title']['element_default_classes'] = FALSE;
  /* Field: Content: Lead */
  $handler->display->display_options['fields']['field_ding_group_lead']['id'] = 'field_ding_group_lead';
  $handler->display->display_options['fields']['field_ding_group_lead']['table'] = 'field_data_field_ding_group_lead';
  $handler->display->display_options['fields']['field_ding_group_lead']['field'] = 'field_ding_group_lead';
  $handler->display->display_options['fields']['field_ding_group_lead']['label'] = '';
  $handler->display->display_options['fields']['field_ding_group_lead']['element_type'] = 'div';
  $handler->display->display_options['fields']['field_ding_group_lead']['element_class'] = 'groups-list-content';
  $handler->display->display_options['fields']['field_ding_group_lead']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_ding_group_lead']['element_default_classes'] = FALSE;
  /* Field: Link (arrow) */
  $handler->display->display_options['fields']['view_node']['id'] = 'view_node';
  $handler->display->display_options['fields']['view_node']['table'] = 'views_entity_node';
  $handler->display->display_options['fields']['view_node']['field'] = 'view_node';
  $handler->display->display_options['fields']['view_node']['ui_name'] = 'Link (arrow)';
  $handler->display->display_options['fields']['view_node']['label'] = '';
  $handler->display->display_options['fields']['view_node']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['view_node']['alter']['text'] = '<i class="icon-chevron-right"></i>';
  $handler->display->display_options['fields']['view_node']['element_type'] = 'div';
  $handler->display->display_options['fields']['view_node']['element_class'] = 'groups-arrow-link';
  $handler->display->display_options['fields']['view_node']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['view_node']['element_default_classes'] = FALSE;
  $handler->display->display_options['defaults']['sorts'] = FALSE;
  /* Sort criterion: Nodequeue: Subqueue ID */
  $handler->display->display_options['sorts']['sqid']['id'] = 'sqid';
  $handler->display->display_options['sorts']['sqid']['table'] = 'nodequeue_nodes';
  $handler->display->display_options['sorts']['sqid']['field'] = 'sqid';
  $handler->display->display_options['sorts']['sqid']['relationship'] = 'nodequeue_rel';
  $handler->display->display_options['sorts']['sqid']['order'] = 'DESC';
  /* Sort criterion: Nodequeue: Position */
  $handler->display->display_options['sorts']['position']['id'] = 'position';
  $handler->display->display_options['sorts']['position']['table'] = 'nodequeue_nodes';
  $handler->display->display_options['sorts']['position']['field'] = 'position';
  $handler->display->display_options['sorts']['position']['relationship'] = 'nodequeue_rel';
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

  /* Display: Front page groups listing */
  $handler = $view->new_display('panel_pane', 'Front page groups listing', 'panel_pane_frontpage');
  $handler->display->display_options['defaults']['title'] = FALSE;
  $handler->display->display_options['defaults']['use_more'] = FALSE;
  $handler->display->display_options['use_more'] = TRUE;
  $handler->display->display_options['defaults']['use_more_always'] = FALSE;
  $handler->display->display_options['defaults']['use_more_always'] = FALSE;
  $handler->display->display_options['use_more_always'] = TRUE;
  $handler->display->display_options['defaults']['use_more_text'] = FALSE;
  $handler->display->display_options['use_more_text'] = 'See all themes';
  $handler->display->display_options['defaults']['link_display'] = FALSE;
  $handler->display->display_options['link_display'] = 'custom_url';
  $handler->display->display_options['link_url'] = 'temaer';
  $handler->display->display_options['defaults']['style_plugin'] = FALSE;
  $handler->display->display_options['style_plugin'] = 'default';
  $handler->display->display_options['defaults']['style_options'] = FALSE;
  $handler->display->display_options['defaults']['row_plugin'] = FALSE;
  $handler->display->display_options['row_plugin'] = 'node';
  $handler->display->display_options['row_options']['links'] = FALSE;
  $handler->display->display_options['defaults']['row_options'] = FALSE;
  $handler->display->display_options['defaults']['relationships'] = FALSE;
  /* Relationship: Nodequeue: Queue */
  $handler->display->display_options['relationships']['nodequeue_rel']['id'] = 'nodequeue_rel';
  $handler->display->display_options['relationships']['nodequeue_rel']['table'] = 'node';
  $handler->display->display_options['relationships']['nodequeue_rel']['field'] = 'nodequeue_rel';
  $handler->display->display_options['relationships']['nodequeue_rel']['label'] = 'Queue';
  $handler->display->display_options['relationships']['nodequeue_rel']['required'] = TRUE;
  $handler->display->display_options['relationships']['nodequeue_rel']['limit'] = 1;
  $handler->display->display_options['relationships']['nodequeue_rel']['names'] = array(
    'ding_groups_frontpage_listing' => 'ding_groups_frontpage_listing',
    'ding_library_listing' => 0,
    'ding_groups_listning' => 0,
    'ding_tabroll_frontpage' => 0,
  );
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = '';
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['title']['alter']['ellipsis'] = FALSE;
  $handler->display->display_options['fields']['title']['element_type'] = 'h2';
  $handler->display->display_options['fields']['title']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['title']['element_default_classes'] = FALSE;
  /* Field: Content: Title image */
  $handler->display->display_options['fields']['field_ding_group_title_image']['id'] = 'field_ding_group_title_image';
  $handler->display->display_options['fields']['field_ding_group_title_image']['table'] = 'field_data_field_ding_group_title_image';
  $handler->display->display_options['fields']['field_ding_group_title_image']['field'] = 'field_ding_group_title_image';
  $handler->display->display_options['fields']['field_ding_group_title_image']['label'] = '';
  $handler->display->display_options['fields']['field_ding_group_title_image']['element_type'] = '0';
  $handler->display->display_options['fields']['field_ding_group_title_image']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_ding_group_title_image']['element_default_classes'] = FALSE;
  $handler->display->display_options['fields']['field_ding_group_title_image']['click_sort_column'] = 'fid';
  $handler->display->display_options['fields']['field_ding_group_title_image']['type'] = 'cs_adaptive_image';
  $handler->display->display_options['fields']['field_ding_group_title_image']['settings'] = array(
    'image_link' => 'content',
    'styles' => array(
      'breakpoint_1' => '768',
      'style_1' => 'ding_panorama_primary_small',
      'breakpoint_2' => '500',
      'style_2' => 'ding_panorama_primary_small',
      'max_style' => 'ding_panorama_primary_small',
      'fallback_style' => 'ding_panorama_primary_small',
    ),
  );
  /* Field: Content: Lead */
  $handler->display->display_options['fields']['field_ding_group_lead']['id'] = 'field_ding_group_lead';
  $handler->display->display_options['fields']['field_ding_group_lead']['table'] = 'field_data_field_ding_group_lead';
  $handler->display->display_options['fields']['field_ding_group_lead']['field'] = 'field_ding_group_lead';
  $handler->display->display_options['fields']['field_ding_group_lead']['label'] = '';
  $handler->display->display_options['fields']['field_ding_group_lead']['element_type'] = 'p';
  $handler->display->display_options['fields']['field_ding_group_lead']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_ding_group_lead']['element_default_classes'] = FALSE;
  /* Field: Link to group */
  $handler->display->display_options['fields']['title_1']['id'] = 'title_1';
  $handler->display->display_options['fields']['title_1']['table'] = 'node';
  $handler->display->display_options['fields']['title_1']['field'] = 'title';
  $handler->display->display_options['fields']['title_1']['ui_name'] = 'Link to group';
  $handler->display->display_options['fields']['title_1']['label'] = '';
  $handler->display->display_options['fields']['title_1']['element_type'] = 'span';
  $handler->display->display_options['fields']['title_1']['element_class'] = 'group-link';
  $handler->display->display_options['fields']['title_1']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['title_1']['element_default_classes'] = FALSE;
  $handler->display->display_options['defaults']['sorts'] = FALSE;
  /* Sort criterion: Nodequeue: Position */
  $handler->display->display_options['sorts']['position']['id'] = 'position';
  $handler->display->display_options['sorts']['position']['table'] = 'nodequeue_nodes';
  $handler->display->display_options['sorts']['position']['field'] = 'position';
  $handler->display->display_options['sorts']['position']['relationship'] = 'nodequeue_rel';
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
    'ding_group' => 'ding_group',
  );
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
  $translatables['ding_groups'] = array(
    t('Master'),
    t('Themes'),
    t('See all themes'),
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
    t('queue'),
    t('<i class="icon-chevron-right"></i>'),
    t('Group overview (simple)'),
    t('Simply list all groups'),
    t('Groups panes'),
    t('Front page groups listing'),
    t('Queue'),
  );
  $export['ding_groups'] = $view;

  return $export;
}
