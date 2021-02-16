<?php
/**
 * @file
 * ding_staff.views_default.inc
 */

/**
 * Implements hook_views_default_views().
 */
function ding_staff_views_default_views() {
  $export = array();

  $view = new view();
  $view->name = 'ding_staff';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'profile';
  $view->human_name = 'Ding staff';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Staff';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'none';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['exposed_form']['options']['reset_button_label'] = 'Gendan';
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = '10';
  $handler->display->display_options['style_plugin'] = 'default';
  $handler->display->display_options['row_plugin'] = 'fields';
  /* No results behavior: Global: Text area */
  $handler->display->display_options['empty']['area']['id'] = 'area';
  $handler->display->display_options['empty']['area']['table'] = 'views';
  $handler->display->display_options['empty']['area']['field'] = 'area';
  $handler->display->display_options['empty']['area']['label'] = 'Empty text';
  $handler->display->display_options['empty']['area']['empty'] = TRUE;
  $handler->display->display_options['empty']['area']['content'] = 'No staff was found related to the library selected.';
  $handler->display->display_options['empty']['area']['format'] = 'ding_wysiwyg';
  /* Field: User uid (excluded) */
  $handler->display->display_options['fields']['user']['id'] = 'user';
  $handler->display->display_options['fields']['user']['table'] = 'profile';
  $handler->display->display_options['fields']['user']['field'] = 'user';
  $handler->display->display_options['fields']['user']['ui_name'] = 'User uid (excluded)';
  $handler->display->display_options['fields']['user']['label'] = '';
  $handler->display->display_options['fields']['user']['exclude'] = TRUE;
  $handler->display->display_options['fields']['user']['element_label_colon'] = FALSE;
  /* Field: Forename (excluded) */
  $handler->display->display_options['fields']['field_ding_staff_forename']['id'] = 'field_ding_staff_forename';
  $handler->display->display_options['fields']['field_ding_staff_forename']['table'] = 'field_data_field_ding_staff_forename';
  $handler->display->display_options['fields']['field_ding_staff_forename']['field'] = 'field_ding_staff_forename';
  $handler->display->display_options['fields']['field_ding_staff_forename']['ui_name'] = 'Forename (excluded)';
  $handler->display->display_options['fields']['field_ding_staff_forename']['label'] = '';
  $handler->display->display_options['fields']['field_ding_staff_forename']['exclude'] = TRUE;
  $handler->display->display_options['fields']['field_ding_staff_forename']['element_label_colon'] = FALSE;
  /* Field: Profile: Image */
  $handler->display->display_options['fields']['field_ding_staff_image']['id'] = 'field_ding_staff_image';
  $handler->display->display_options['fields']['field_ding_staff_image']['table'] = 'field_data_field_ding_staff_image';
  $handler->display->display_options['fields']['field_ding_staff_image']['field'] = 'field_ding_staff_image';
  $handler->display->display_options['fields']['field_ding_staff_image']['label'] = '';
  $handler->display->display_options['fields']['field_ding_staff_image']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_ding_staff_image']['click_sort_column'] = 'fid';
  $handler->display->display_options['fields']['field_ding_staff_image']['type'] = 'cs_adaptive_image';
  $handler->display->display_options['fields']['field_ding_staff_image']['settings'] = array(
    'image_link' => '',
    'styles' => array(
      'breakpoint_1' => '',
      'style_1' => '',
      'breakpoint_2' => '',
      'style_2' => '',
      'max_style' => 'ding_staff_thumbnail',
      'fallback_style' => 'ding_staff_thumbnail',
    ),
  );
  /* Field: Surname Forename (Link) */
  $handler->display->display_options['fields']['field_ding_staff_surname']['id'] = 'field_ding_staff_surname';
  $handler->display->display_options['fields']['field_ding_staff_surname']['table'] = 'field_data_field_ding_staff_surname';
  $handler->display->display_options['fields']['field_ding_staff_surname']['field'] = 'field_ding_staff_surname';
  $handler->display->display_options['fields']['field_ding_staff_surname']['ui_name'] = 'Surname Forename (Link)';
  $handler->display->display_options['fields']['field_ding_staff_surname']['label'] = 'Name';
  $handler->display->display_options['fields']['field_ding_staff_surname']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['field_ding_staff_surname']['alter']['text'] = '[field_ding_staff_surname], [field_ding_staff_forename]';
  $handler->display->display_options['fields']['field_ding_staff_surname']['alter']['trim_whitespace'] = TRUE;
  $handler->display->display_options['fields']['field_ding_staff_surname']['alter']['strip_tags'] = TRUE;
  $handler->display->display_options['fields']['field_ding_staff_surname']['element_class'] = 'staff-name';
  $handler->display->display_options['fields']['field_ding_staff_surname']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_ding_staff_surname']['element_default_classes'] = FALSE;
  /* Field: Profile: Position */
  $handler->display->display_options['fields']['field_ding_staff_position']['id'] = 'field_ding_staff_position';
  $handler->display->display_options['fields']['field_ding_staff_position']['table'] = 'field_data_field_ding_staff_position';
  $handler->display->display_options['fields']['field_ding_staff_position']['field'] = 'field_ding_staff_position';
  $handler->display->display_options['fields']['field_ding_staff_position']['element_label_colon'] = FALSE;
  /* Field: Profile: Department */
  $handler->display->display_options['fields']['field_ding_staff_department']['id'] = 'field_ding_staff_department';
  $handler->display->display_options['fields']['field_ding_staff_department']['table'] = 'field_data_field_ding_staff_department';
  $handler->display->display_options['fields']['field_ding_staff_department']['field'] = 'field_ding_staff_department';
  $handler->display->display_options['fields']['field_ding_staff_department']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_ding_staff_department']['type'] = 'taxonomy_term_reference_plain';
  $handler->display->display_options['fields']['field_ding_staff_department']['delta_offset'] = '0';
  $handler->display->display_options['fields']['field_ding_staff_department']['separator'] = '<br/>';
  /* Field: Profile: Phone */
  $handler->display->display_options['fields']['field_ding_staff_phone']['id'] = 'field_ding_staff_phone';
  $handler->display->display_options['fields']['field_ding_staff_phone']['table'] = 'field_data_field_ding_staff_phone';
  $handler->display->display_options['fields']['field_ding_staff_phone']['field'] = 'field_ding_staff_phone';
  $handler->display->display_options['fields']['field_ding_staff_phone']['element_label_colon'] = FALSE;
  /* Field: Profile: Email */
  $handler->display->display_options['fields']['field_ding_staff_email']['id'] = 'field_ding_staff_email';
  $handler->display->display_options['fields']['field_ding_staff_email']['table'] = 'field_data_field_ding_staff_email';
  $handler->display->display_options['fields']['field_ding_staff_email']['field'] = 'field_ding_staff_email';
  $handler->display->display_options['fields']['field_ding_staff_email']['label'] = 'E-mail';
  $handler->display->display_options['fields']['field_ding_staff_email']['element_label_colon'] = FALSE;
  /* Sort criterion: Profile: Surname (field_ding_staff_surname) */
  $handler->display->display_options['sorts']['field_ding_staff_surname_value']['id'] = 'field_ding_staff_surname_value';
  $handler->display->display_options['sorts']['field_ding_staff_surname_value']['table'] = 'field_data_field_ding_staff_surname';
  $handler->display->display_options['sorts']['field_ding_staff_surname_value']['field'] = 'field_ding_staff_surname_value';
  /* Filter criterion: Profile: Type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'profile';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'ding_staff_profile' => 'ding_staff_profile',
  );

  /* Display: All staff list */
  $handler = $view->new_display('panel_pane', 'All staff list', 'ding_staff_list_all');
  $handler->display->display_options['defaults']['title'] = FALSE;
  $handler->display->display_options['title'] = 'All libraries: Staff';
  $handler->display->display_options['defaults']['style_plugin'] = FALSE;
  $handler->display->display_options['style_plugin'] = 'list';
  $handler->display->display_options['style_options']['grouping'] = array(
    0 => array(
      'field' => 'gid',
      'rendered' => 0,
      'rendered_strip' => 0,
    ),
  );
  $handler->display->display_options['style_options']['row_class'] = 'list staff-list-item';
  $handler->display->display_options['style_options']['class'] = 'list staff-list-all';
  $handler->display->display_options['style_options']['wrapper_class'] = '';
  $handler->display->display_options['defaults']['style_options'] = FALSE;
  $handler->display->display_options['defaults']['row_plugin'] = FALSE;
  $handler->display->display_options['row_plugin'] = 'fields';
  $handler->display->display_options['defaults']['row_options'] = FALSE;
  $handler->display->display_options['defaults']['relationships'] = FALSE;
  /* Relationship: OG membership: Group Node from OG membership */
  $handler->display->display_options['relationships']['og_membership_related_node_group']['id'] = 'og_membership_related_node_group';
  $handler->display->display_options['relationships']['og_membership_related_node_group']['table'] = 'og_membership';
  $handler->display->display_options['relationships']['og_membership_related_node_group']['field'] = 'og_membership_related_node_group';
  /* Relationship: Profile: User uid */
  $handler->display->display_options['relationships']['user']['id'] = 'user';
  $handler->display->display_options['relationships']['user']['table'] = 'profile';
  $handler->display->display_options['relationships']['user']['field'] = 'user';
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Field: Library node title (as token for header)(excluded) */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['relationship'] = 'og_membership_related_node_group';
  $handler->display->display_options['fields']['title']['ui_name'] = 'Library node title (as token for header)(excluded)';
  $handler->display->display_options['fields']['title']['label'] = '';
  $handler->display->display_options['fields']['title']['exclude'] = TRUE;
  $handler->display->display_options['fields']['title']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['title']['link_to_node'] = FALSE;
  /* Field: GID from OG membership (for group header)(excluded) */
  $handler->display->display_options['fields']['gid']['id'] = 'gid';
  $handler->display->display_options['fields']['gid']['table'] = 'og_membership';
  $handler->display->display_options['fields']['gid']['field'] = 'gid';
  $handler->display->display_options['fields']['gid']['ui_name'] = 'GID from OG membership (for group header)(excluded)';
  $handler->display->display_options['fields']['gid']['label'] = '';
  $handler->display->display_options['fields']['gid']['exclude'] = TRUE;
  $handler->display->display_options['fields']['gid']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['gid']['alter']['text'] = '[title]';
  $handler->display->display_options['fields']['gid']['element_label_colon'] = FALSE;
  /* Field: User uid (excluded) */
  $handler->display->display_options['fields']['user']['id'] = 'user';
  $handler->display->display_options['fields']['user']['table'] = 'profile';
  $handler->display->display_options['fields']['user']['field'] = 'user';
  $handler->display->display_options['fields']['user']['ui_name'] = 'User uid (excluded)';
  $handler->display->display_options['fields']['user']['label'] = '';
  $handler->display->display_options['fields']['user']['exclude'] = TRUE;
  $handler->display->display_options['fields']['user']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['user']['separator'] = '';
  /* Field: Forename (excluded) */
  $handler->display->display_options['fields']['field_ding_staff_forename']['id'] = 'field_ding_staff_forename';
  $handler->display->display_options['fields']['field_ding_staff_forename']['table'] = 'field_data_field_ding_staff_forename';
  $handler->display->display_options['fields']['field_ding_staff_forename']['field'] = 'field_ding_staff_forename';
  $handler->display->display_options['fields']['field_ding_staff_forename']['ui_name'] = 'Forename (excluded)';
  $handler->display->display_options['fields']['field_ding_staff_forename']['label'] = '';
  $handler->display->display_options['fields']['field_ding_staff_forename']['exclude'] = TRUE;
  $handler->display->display_options['fields']['field_ding_staff_forename']['element_label_colon'] = FALSE;
  /* Field: Profile: Image */
  $handler->display->display_options['fields']['field_ding_staff_image']['id'] = 'field_ding_staff_image';
  $handler->display->display_options['fields']['field_ding_staff_image']['table'] = 'field_data_field_ding_staff_image';
  $handler->display->display_options['fields']['field_ding_staff_image']['field'] = 'field_ding_staff_image';
  $handler->display->display_options['fields']['field_ding_staff_image']['label'] = '';
  $handler->display->display_options['fields']['field_ding_staff_image']['element_type'] = '0';
  $handler->display->display_options['fields']['field_ding_staff_image']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_ding_staff_image']['element_wrapper_type'] = 'div';
  $handler->display->display_options['fields']['field_ding_staff_image']['element_wrapper_class'] = 'staff-image-wrapper';
  $handler->display->display_options['fields']['field_ding_staff_image']['element_default_classes'] = FALSE;
  $handler->display->display_options['fields']['field_ding_staff_image']['click_sort_column'] = 'fid';
  $handler->display->display_options['fields']['field_ding_staff_image']['settings'] = array(
    'image_style' => 'ding_panorama_list_large',
    'image_link' => 'content',
  );
  /* Field: Surname Forename (Link) */
  $handler->display->display_options['fields']['field_ding_staff_surname']['id'] = 'field_ding_staff_surname';
  $handler->display->display_options['fields']['field_ding_staff_surname']['table'] = 'field_data_field_ding_staff_surname';
  $handler->display->display_options['fields']['field_ding_staff_surname']['field'] = 'field_ding_staff_surname';
  $handler->display->display_options['fields']['field_ding_staff_surname']['ui_name'] = 'Surname Forename (Link)';
  $handler->display->display_options['fields']['field_ding_staff_surname']['label'] = '';
  $handler->display->display_options['fields']['field_ding_staff_surname']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['field_ding_staff_surname']['alter']['text'] = '[field_ding_staff_surname], [field_ding_staff_forename]';
  $handler->display->display_options['fields']['field_ding_staff_surname']['alter']['trim_whitespace'] = TRUE;
  $handler->display->display_options['fields']['field_ding_staff_surname']['alter']['strip_tags'] = TRUE;
  $handler->display->display_options['fields']['field_ding_staff_surname']['element_type'] = '0';
  $handler->display->display_options['fields']['field_ding_staff_surname']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_ding_staff_surname']['element_wrapper_type'] = 'div';
  $handler->display->display_options['fields']['field_ding_staff_surname']['element_wrapper_class'] = 'staff-name';
  $handler->display->display_options['fields']['field_ding_staff_surname']['element_default_classes'] = FALSE;
  /* Field: Profile: Position */
  $handler->display->display_options['fields']['field_ding_staff_position']['id'] = 'field_ding_staff_position';
  $handler->display->display_options['fields']['field_ding_staff_position']['table'] = 'field_data_field_ding_staff_position';
  $handler->display->display_options['fields']['field_ding_staff_position']['field'] = 'field_ding_staff_position';
  $handler->display->display_options['fields']['field_ding_staff_position']['label'] = '';
  $handler->display->display_options['fields']['field_ding_staff_position']['element_type'] = '0';
  $handler->display->display_options['fields']['field_ding_staff_position']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_ding_staff_position']['element_wrapper_type'] = 'div';
  $handler->display->display_options['fields']['field_ding_staff_position']['element_wrapper_class'] = 'staff-position';
  $handler->display->display_options['fields']['field_ding_staff_position']['element_default_classes'] = FALSE;
  /* Field: Profile: Phone */
  $handler->display->display_options['fields']['field_ding_staff_phone']['id'] = 'field_ding_staff_phone';
  $handler->display->display_options['fields']['field_ding_staff_phone']['table'] = 'field_data_field_ding_staff_phone';
  $handler->display->display_options['fields']['field_ding_staff_phone']['field'] = 'field_ding_staff_phone';
  $handler->display->display_options['fields']['field_ding_staff_phone']['label'] = 'Ph';
  $handler->display->display_options['fields']['field_ding_staff_phone']['element_type'] = '0';
  $handler->display->display_options['fields']['field_ding_staff_phone']['element_wrapper_type'] = 'div';
  $handler->display->display_options['fields']['field_ding_staff_phone']['element_wrapper_class'] = 'staff-phone';
  $handler->display->display_options['fields']['field_ding_staff_phone']['element_default_classes'] = FALSE;
  /* Field: Profile: Email */
  $handler->display->display_options['fields']['field_ding_staff_email']['id'] = 'field_ding_staff_email';
  $handler->display->display_options['fields']['field_ding_staff_email']['table'] = 'field_data_field_ding_staff_email';
  $handler->display->display_options['fields']['field_ding_staff_email']['field'] = 'field_ding_staff_email';
  $handler->display->display_options['fields']['field_ding_staff_email']['label'] = 'E-mail';
  $handler->display->display_options['fields']['field_ding_staff_email']['element_type'] = '0';
  $handler->display->display_options['fields']['field_ding_staff_email']['element_wrapper_type'] = 'div';
  $handler->display->display_options['fields']['field_ding_staff_email']['element_wrapper_class'] = 'staff-email';
  $handler->display->display_options['fields']['field_ding_staff_email']['element_default_classes'] = FALSE;
  /* Field: Profile: Department */
  $handler->display->display_options['fields']['field_ding_staff_department']['id'] = 'field_ding_staff_department';
  $handler->display->display_options['fields']['field_ding_staff_department']['table'] = 'field_data_field_ding_staff_department';
  $handler->display->display_options['fields']['field_ding_staff_department']['field'] = 'field_ding_staff_department';
  $handler->display->display_options['fields']['field_ding_staff_department']['label'] = 'Department(s)';
  $handler->display->display_options['fields']['field_ding_staff_department']['element_type'] = '0';
  $handler->display->display_options['fields']['field_ding_staff_department']['element_label_type'] = 'strong';
  $handler->display->display_options['fields']['field_ding_staff_department']['element_wrapper_type'] = 'div';
  $handler->display->display_options['fields']['field_ding_staff_department']['element_wrapper_class'] = 'staff-departments';
  $handler->display->display_options['fields']['field_ding_staff_department']['element_default_classes'] = FALSE;
  $handler->display->display_options['fields']['field_ding_staff_department']['type'] = 'taxonomy_term_reference_plain';
  $handler->display->display_options['fields']['field_ding_staff_department']['delta_offset'] = '0';
  $handler->display->display_options['fields']['field_ding_staff_department']['separator'] = '<br/>';
  $handler->display->display_options['defaults']['sorts'] = FALSE;
  /* Sort criterion: Content: Title */
  $handler->display->display_options['sorts']['title']['id'] = 'title';
  $handler->display->display_options['sorts']['title']['table'] = 'node';
  $handler->display->display_options['sorts']['title']['field'] = 'title';
  $handler->display->display_options['sorts']['title']['relationship'] = 'og_membership_related_node_group';
  /* Sort criterion: Profile: Surname (field_ding_staff_surname) */
  $handler->display->display_options['sorts']['field_ding_staff_surname_value']['id'] = 'field_ding_staff_surname_value';
  $handler->display->display_options['sorts']['field_ding_staff_surname_value']['table'] = 'field_data_field_ding_staff_surname';
  $handler->display->display_options['sorts']['field_ding_staff_surname_value']['field'] = 'field_ding_staff_surname_value';
  $handler->display->display_options['defaults']['filter_groups'] = FALSE;
  $handler->display->display_options['defaults']['filters'] = FALSE;
  /* Filter criterion: Profile: Type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'profile';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'ding_staff_profile' => 'ding_staff_profile',
  );
  /* Filter criterion: User: Roles */
  $handler->display->display_options['filters']['rid']['id'] = 'rid';
  $handler->display->display_options['filters']['rid']['table'] = 'users_roles';
  $handler->display->display_options['filters']['rid']['field'] = 'rid';
  $handler->display->display_options['filters']['rid']['relationship'] = 'user';
  $handler->display->display_options['filters']['rid']['value'] = array(
    9 => 9,
  );
  $handler->display->display_options['pane_category']['name'] = 'Bruger';
  $handler->display->display_options['pane_category']['weight'] = '0';

  /* Display: Library departments list */
  $handler = $view->new_display('panel_pane', 'Library departments list', 'ding_staff_library_departments');
  $handler->display->display_options['display_description'] = 'Department grouped list, not using tables';
  $handler->display->display_options['defaults']['style_plugin'] = FALSE;
  $handler->display->display_options['style_plugin'] = 'list';
  $handler->display->display_options['style_options']['grouping'] = array(
    0 => array(
      'field' => 'field_ding_staff_department',
      'rendered' => 1,
      'rendered_strip' => 0,
    ),
  );
  $handler->display->display_options['style_options']['row_class'] = 'list staff-list-item';
  $handler->display->display_options['style_options']['default_row_class'] = FALSE;
  $handler->display->display_options['style_options']['class'] = 'list staff-list';
  $handler->display->display_options['style_options']['wrapper_class'] = '';
  $handler->display->display_options['defaults']['style_options'] = FALSE;
  $handler->display->display_options['defaults']['row_plugin'] = FALSE;
  $handler->display->display_options['row_plugin'] = 'fields';
  $handler->display->display_options['row_options']['hide_empty'] = TRUE;
  $handler->display->display_options['defaults']['row_options'] = FALSE;
  $handler->display->display_options['defaults']['relationships'] = FALSE;
  /* Relationship: Profile: Department (field_ding_staff_department) */
  $handler->display->display_options['relationships']['field_ding_staff_department_tid']['id'] = 'field_ding_staff_department_tid';
  $handler->display->display_options['relationships']['field_ding_staff_department_tid']['table'] = 'field_data_field_ding_staff_department';
  $handler->display->display_options['relationships']['field_ding_staff_department_tid']['field'] = 'field_ding_staff_department_tid';
  /* Relationship: OG membership: Group Node from OG membership */
  $handler->display->display_options['relationships']['og_membership_related_node_group']['id'] = 'og_membership_related_node_group';
  $handler->display->display_options['relationships']['og_membership_related_node_group']['table'] = 'og_membership';
  $handler->display->display_options['relationships']['og_membership_related_node_group']['field'] = 'og_membership_related_node_group';
  /* Relationship: Profile: User uid */
  $handler->display->display_options['relationships']['user']['id'] = 'user';
  $handler->display->display_options['relationships']['user']['table'] = 'profile';
  $handler->display->display_options['relationships']['user']['field'] = 'user';
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Field: Department (for group header)(excluded) */
  $handler->display->display_options['fields']['field_ding_staff_department']['id'] = 'field_ding_staff_department';
  $handler->display->display_options['fields']['field_ding_staff_department']['table'] = 'field_data_field_ding_staff_department';
  $handler->display->display_options['fields']['field_ding_staff_department']['field'] = 'field_ding_staff_department';
  $handler->display->display_options['fields']['field_ding_staff_department']['ui_name'] = 'Department (for group header)(excluded)';
  $handler->display->display_options['fields']['field_ding_staff_department']['label'] = '';
  $handler->display->display_options['fields']['field_ding_staff_department']['exclude'] = TRUE;
  $handler->display->display_options['fields']['field_ding_staff_department']['element_type'] = 'div';
  $handler->display->display_options['fields']['field_ding_staff_department']['element_class'] = 'staff-list-department';
  $handler->display->display_options['fields']['field_ding_staff_department']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_ding_staff_department']['element_wrapper_type'] = 'div';
  $handler->display->display_options['fields']['field_ding_staff_department']['element_wrapper_class'] = 'staff-list-department';
  $handler->display->display_options['fields']['field_ding_staff_department']['element_default_classes'] = FALSE;
  $handler->display->display_options['fields']['field_ding_staff_department']['type'] = 'taxonomy_term_reference_plain';
  $handler->display->display_options['fields']['field_ding_staff_department']['group_rows'] = FALSE;
  $handler->display->display_options['fields']['field_ding_staff_department']['delta_offset'] = '0';
  /* Field: User uid (excluded) */
  $handler->display->display_options['fields']['user']['id'] = 'user';
  $handler->display->display_options['fields']['user']['table'] = 'profile';
  $handler->display->display_options['fields']['user']['field'] = 'user';
  $handler->display->display_options['fields']['user']['ui_name'] = 'User uid (excluded)';
  $handler->display->display_options['fields']['user']['label'] = '';
  $handler->display->display_options['fields']['user']['exclude'] = TRUE;
  $handler->display->display_options['fields']['user']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['user']['separator'] = '';
  /* Field: Forename (excluded) */
  $handler->display->display_options['fields']['field_ding_staff_forename']['id'] = 'field_ding_staff_forename';
  $handler->display->display_options['fields']['field_ding_staff_forename']['table'] = 'field_data_field_ding_staff_forename';
  $handler->display->display_options['fields']['field_ding_staff_forename']['field'] = 'field_ding_staff_forename';
  $handler->display->display_options['fields']['field_ding_staff_forename']['ui_name'] = 'Forename (excluded)';
  $handler->display->display_options['fields']['field_ding_staff_forename']['label'] = '';
  $handler->display->display_options['fields']['field_ding_staff_forename']['exclude'] = TRUE;
  $handler->display->display_options['fields']['field_ding_staff_forename']['element_label_colon'] = FALSE;
  /* Field: Profile: Image */
  $handler->display->display_options['fields']['field_ding_staff_image']['id'] = 'field_ding_staff_image';
  $handler->display->display_options['fields']['field_ding_staff_image']['table'] = 'field_data_field_ding_staff_image';
  $handler->display->display_options['fields']['field_ding_staff_image']['field'] = 'field_ding_staff_image';
  $handler->display->display_options['fields']['field_ding_staff_image']['label'] = '';
  $handler->display->display_options['fields']['field_ding_staff_image']['element_type'] = '0';
  $handler->display->display_options['fields']['field_ding_staff_image']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_ding_staff_image']['element_wrapper_class'] = 'staff-image-wrapper image-styling-16-9';
  $handler->display->display_options['fields']['field_ding_staff_image']['element_default_classes'] = FALSE;
  $handler->display->display_options['fields']['field_ding_staff_image']['click_sort_column'] = 'fid';
  $handler->display->display_options['fields']['field_ding_staff_image']['settings'] = array(
    'image_style' => 'ding_panorama_list_large',
    'image_link' => 'content',
  );
  /* Field: Forename Surname (Link) */
  $handler->display->display_options['fields']['field_ding_staff_surname']['id'] = 'field_ding_staff_surname';
  $handler->display->display_options['fields']['field_ding_staff_surname']['table'] = 'field_data_field_ding_staff_surname';
  $handler->display->display_options['fields']['field_ding_staff_surname']['field'] = 'field_ding_staff_surname';
  $handler->display->display_options['fields']['field_ding_staff_surname']['ui_name'] = 'Forename Surname (Link)';
  $handler->display->display_options['fields']['field_ding_staff_surname']['label'] = '';
  $handler->display->display_options['fields']['field_ding_staff_surname']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['field_ding_staff_surname']['alter']['text'] = '[field_ding_staff_forename] [field_ding_staff_surname]';
  $handler->display->display_options['fields']['field_ding_staff_surname']['alter']['make_link'] = TRUE;
  $handler->display->display_options['fields']['field_ding_staff_surname']['alter']['path'] = 'user/[user]';
  $handler->display->display_options['fields']['field_ding_staff_surname']['alter']['absolute'] = TRUE;
  $handler->display->display_options['fields']['field_ding_staff_surname']['alter']['alt'] = '[field_ding_staff_forename] [field_ding_staff_surname]';
  $handler->display->display_options['fields']['field_ding_staff_surname']['element_type'] = '0';
  $handler->display->display_options['fields']['field_ding_staff_surname']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_ding_staff_surname']['element_wrapper_type'] = 'div';
  $handler->display->display_options['fields']['field_ding_staff_surname']['element_wrapper_class'] = 'staff-name';
  $handler->display->display_options['fields']['field_ding_staff_surname']['element_default_classes'] = FALSE;
  /* Field: Profile: Position */
  $handler->display->display_options['fields']['field_ding_staff_position']['id'] = 'field_ding_staff_position';
  $handler->display->display_options['fields']['field_ding_staff_position']['table'] = 'field_data_field_ding_staff_position';
  $handler->display->display_options['fields']['field_ding_staff_position']['field'] = 'field_ding_staff_position';
  $handler->display->display_options['fields']['field_ding_staff_position']['label'] = '';
  $handler->display->display_options['fields']['field_ding_staff_position']['element_type'] = '0';
  $handler->display->display_options['fields']['field_ding_staff_position']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_ding_staff_position']['element_wrapper_type'] = 'div';
  $handler->display->display_options['fields']['field_ding_staff_position']['element_wrapper_class'] = 'staff-position';
  $handler->display->display_options['fields']['field_ding_staff_position']['element_default_classes'] = FALSE;
  /* Field: Profile: Phone */
  $handler->display->display_options['fields']['field_ding_staff_phone']['id'] = 'field_ding_staff_phone';
  $handler->display->display_options['fields']['field_ding_staff_phone']['table'] = 'field_data_field_ding_staff_phone';
  $handler->display->display_options['fields']['field_ding_staff_phone']['field'] = 'field_ding_staff_phone';
  $handler->display->display_options['fields']['field_ding_staff_phone']['label'] = 'Ph';
  $handler->display->display_options['fields']['field_ding_staff_phone']['element_type'] = '0';
  $handler->display->display_options['fields']['field_ding_staff_phone']['element_wrapper_type'] = 'div';
  $handler->display->display_options['fields']['field_ding_staff_phone']['element_wrapper_class'] = 'staff-phone';
  $handler->display->display_options['fields']['field_ding_staff_phone']['element_default_classes'] = FALSE;
  /* Field: Profile: Email */
  $handler->display->display_options['fields']['field_ding_staff_email']['id'] = 'field_ding_staff_email';
  $handler->display->display_options['fields']['field_ding_staff_email']['table'] = 'field_data_field_ding_staff_email';
  $handler->display->display_options['fields']['field_ding_staff_email']['field'] = 'field_ding_staff_email';
  $handler->display->display_options['fields']['field_ding_staff_email']['label'] = 'E-mail';
  $handler->display->display_options['fields']['field_ding_staff_email']['element_type'] = '0';
  $handler->display->display_options['fields']['field_ding_staff_email']['element_wrapper_type'] = 'div';
  $handler->display->display_options['fields']['field_ding_staff_email']['element_wrapper_class'] = 'staff-email';
  $handler->display->display_options['fields']['field_ding_staff_email']['element_default_classes'] = FALSE;
  $handler->display->display_options['defaults']['sorts'] = FALSE;
  /* Sort criterion: Taxonomy term: Weight */
  $handler->display->display_options['sorts']['weight']['id'] = 'weight';
  $handler->display->display_options['sorts']['weight']['table'] = 'taxonomy_term_data';
  $handler->display->display_options['sorts']['weight']['field'] = 'weight';
  $handler->display->display_options['sorts']['weight']['relationship'] = 'field_ding_staff_department_tid';
  /* Sort criterion: Profile: Surname (field_ding_staff_surname) */
  $handler->display->display_options['sorts']['field_ding_staff_surname_value']['id'] = 'field_ding_staff_surname_value';
  $handler->display->display_options['sorts']['field_ding_staff_surname_value']['table'] = 'field_data_field_ding_staff_surname';
  $handler->display->display_options['sorts']['field_ding_staff_surname_value']['field'] = 'field_ding_staff_surname_value';
  $handler->display->display_options['defaults']['arguments'] = FALSE;
  /* Contextual filter: Content: Slug (field_ding_library_slug) */
  $handler->display->display_options['arguments']['field_ding_library_slug_value']['id'] = 'field_ding_library_slug_value';
  $handler->display->display_options['arguments']['field_ding_library_slug_value']['table'] = 'field_data_field_ding_library_slug';
  $handler->display->display_options['arguments']['field_ding_library_slug_value']['field'] = 'field_ding_library_slug_value';
  $handler->display->display_options['arguments']['field_ding_library_slug_value']['relationship'] = 'og_membership_related_node_group';
  $handler->display->display_options['arguments']['field_ding_library_slug_value']['default_action'] = 'default';
  $handler->display->display_options['arguments']['field_ding_library_slug_value']['exception']['title'] = 'Alle';
  $handler->display->display_options['arguments']['field_ding_library_slug_value']['default_argument_type'] = 'raw';
  $handler->display->display_options['arguments']['field_ding_library_slug_value']['default_argument_options']['index'] = '1';
  $handler->display->display_options['arguments']['field_ding_library_slug_value']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['field_ding_library_slug_value']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['field_ding_library_slug_value']['summary_options']['items_per_page'] = '25';
  $handler->display->display_options['arguments']['field_ding_library_slug_value']['limit'] = '0';
  $handler->display->display_options['defaults']['filter_groups'] = FALSE;
  $handler->display->display_options['defaults']['filters'] = FALSE;
  /* Filter criterion: Profile: Type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'profile';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'ding_staff_profile' => 'ding_staff_profile',
  );
  /* Filter criterion: User: Roles */
  $handler->display->display_options['filters']['rid']['id'] = 'rid';
  $handler->display->display_options['filters']['rid']['table'] = 'users_roles';
  $handler->display->display_options['filters']['rid']['field'] = 'rid';
  $handler->display->display_options['filters']['rid']['relationship'] = 'user';
  $handler->display->display_options['filters']['rid']['value'] = array(
    9 => 9,
  );
  $handler->display->display_options['pane_category']['name'] = 'Bruger';
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
    'field_ding_library_slug_value' => array(
      'type' => 'panel',
      'context' => 'entity:comment.author',
      'context_optional' => 0,
      'panel' => '0',
      'fixed' => '',
      'label' => 'Content: Slug (field_ding_library_slug)',
    ),
  );
  $translatables['ding_staff'] = array(
    t('Master'),
    t('Staff'),
    t('more'),
    t('Apply'),
    t('Gendan'),
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
    t('Empty text'),
    t('No staff was found related to the library selected.'),
    t('.'),
    t(','),
    t('Name'),
    t('[field_ding_staff_surname], [field_ding_staff_forename]'),
    t('Position'),
    t('Department'),
    t('Phone'),
    t('E-mail'),
    t('All staff list'),
    t('All libraries: Staff'),
    t('Group node from OG membership'),
    t('User'),
    t('[title]'),
    t('Ph'),
    t('Department(s)'),
    t('Bruger'),
    t('Library departments list'),
    t('Department grouped list, not using tables'),
    t('term from field_ding_staff_department'),
    t('[field_ding_staff_forename] [field_ding_staff_surname]'),
    t('Alle'),
  );
  $export['ding_staff'] = $view;

  return $export;
}
