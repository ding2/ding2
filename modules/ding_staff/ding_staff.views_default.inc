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
  $handler->display->display_options['use_more_text'] = 'mere';
  $handler->display->display_options['access']['type'] = 'none';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['exposed_form']['options']['submit_button'] = 'Udfør';
  $handler->display->display_options['exposed_form']['options']['reset_button_label'] = 'Gendan';
  $handler->display->display_options['exposed_form']['options']['exposed_sorts_label'] = 'Sortér efter';
  $handler->display->display_options['exposed_form']['options']['sort_asc_label'] = 'Stigende';
  $handler->display->display_options['exposed_form']['options']['sort_desc_label'] = 'Faldende';
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = '10';
  $handler->display->display_options['pager']['options']['expose']['items_per_page_label'] = 'Antal elementer';
  $handler->display->display_options['pager']['options']['expose']['items_per_page_options_all_label'] = '- Alle -';
  $handler->display->display_options['pager']['options']['expose']['offset_label'] = 'Forskydning';
  $handler->display->display_options['pager']['options']['tags']['first'] = '« første';
  $handler->display->display_options['pager']['options']['tags']['previous'] = '‹ forrige';
  $handler->display->display_options['pager']['options']['tags']['next'] = 'næste ›';
  $handler->display->display_options['pager']['options']['tags']['last'] = 'sidste »';
  $handler->display->display_options['style_plugin'] = 'default';
  $handler->display->display_options['row_plugin'] = 'fields';
  /* Opførsel ved ingen resultater: Global: Tekstområde */
  $handler->display->display_options['empty']['area']['id'] = 'area';
  $handler->display->display_options['empty']['area']['table'] = 'views';
  $handler->display->display_options['empty']['area']['field'] = 'area';
  $handler->display->display_options['empty']['area']['label'] = 'Tomt tekstfelt';
  $handler->display->display_options['empty']['area']['empty'] = TRUE;
  $handler->display->display_options['empty']['area']['content'] = 'Der er ingen medarbejdere tilknyttet biblioteket';
  $handler->display->display_options['empty']['area']['format'] = 'ding_wysiwyg';
  /* Felt: User uid (excluded) */
  $handler->display->display_options['fields']['user']['id'] = 'user';
  $handler->display->display_options['fields']['user']['table'] = 'profile';
  $handler->display->display_options['fields']['user']['field'] = 'user';
  $handler->display->display_options['fields']['user']['ui_name'] = 'User uid (excluded)';
  $handler->display->display_options['fields']['user']['label'] = '';
  $handler->display->display_options['fields']['user']['exclude'] = TRUE;
  $handler->display->display_options['fields']['user']['element_label_colon'] = FALSE;
  /* Felt: Forename (excluded) */
  $handler->display->display_options['fields']['field_ding_staff_forename']['id'] = 'field_ding_staff_forename';
  $handler->display->display_options['fields']['field_ding_staff_forename']['table'] = 'field_data_field_ding_staff_forename';
  $handler->display->display_options['fields']['field_ding_staff_forename']['field'] = 'field_ding_staff_forename';
  $handler->display->display_options['fields']['field_ding_staff_forename']['ui_name'] = 'Forename (excluded)';
  $handler->display->display_options['fields']['field_ding_staff_forename']['label'] = '';
  $handler->display->display_options['fields']['field_ding_staff_forename']['exclude'] = TRUE;
  $handler->display->display_options['fields']['field_ding_staff_forename']['element_label_colon'] = FALSE;
  /* Felt: Profil: Image */
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
  /* Felt: Surname Forename (Link) */
  $handler->display->display_options['fields']['field_ding_staff_surname']['id'] = 'field_ding_staff_surname';
  $handler->display->display_options['fields']['field_ding_staff_surname']['table'] = 'field_data_field_ding_staff_surname';
  $handler->display->display_options['fields']['field_ding_staff_surname']['field'] = 'field_ding_staff_surname';
  $handler->display->display_options['fields']['field_ding_staff_surname']['ui_name'] = 'Surname Forename (Link)';
  $handler->display->display_options['fields']['field_ding_staff_surname']['label'] = 'Navn';
  $handler->display->display_options['fields']['field_ding_staff_surname']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['field_ding_staff_surname']['alter']['text'] = '[field_ding_staff_surname], [field_ding_staff_forename]';
  $handler->display->display_options['fields']['field_ding_staff_surname']['alter']['trim_whitespace'] = TRUE;
  $handler->display->display_options['fields']['field_ding_staff_surname']['alter']['strip_tags'] = TRUE;
  $handler->display->display_options['fields']['field_ding_staff_surname']['element_class'] = 'staff-name';
  $handler->display->display_options['fields']['field_ding_staff_surname']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_ding_staff_surname']['element_default_classes'] = FALSE;
  /* Felt: Profil: Position */
  $handler->display->display_options['fields']['field_ding_staff_position']['id'] = 'field_ding_staff_position';
  $handler->display->display_options['fields']['field_ding_staff_position']['table'] = 'field_data_field_ding_staff_position';
  $handler->display->display_options['fields']['field_ding_staff_position']['field'] = 'field_ding_staff_position';
  $handler->display->display_options['fields']['field_ding_staff_position']['label'] = 'Placering';
  $handler->display->display_options['fields']['field_ding_staff_position']['element_label_colon'] = FALSE;
  /* Felt: Profil: Department */
  $handler->display->display_options['fields']['field_ding_staff_department']['id'] = 'field_ding_staff_department';
  $handler->display->display_options['fields']['field_ding_staff_department']['table'] = 'field_data_field_ding_staff_department';
  $handler->display->display_options['fields']['field_ding_staff_department']['field'] = 'field_ding_staff_department';
  $handler->display->display_options['fields']['field_ding_staff_department']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_ding_staff_department']['type'] = 'taxonomy_term_reference_plain';
  $handler->display->display_options['fields']['field_ding_staff_department']['delta_offset'] = '0';
  $handler->display->display_options['fields']['field_ding_staff_department']['separator'] = '<br/>';
  /* Felt: Profil: Phone */
  $handler->display->display_options['fields']['field_ding_staff_phone']['id'] = 'field_ding_staff_phone';
  $handler->display->display_options['fields']['field_ding_staff_phone']['table'] = 'field_data_field_ding_staff_phone';
  $handler->display->display_options['fields']['field_ding_staff_phone']['field'] = 'field_ding_staff_phone';
  $handler->display->display_options['fields']['field_ding_staff_phone']['label'] = 'Telefon';
  $handler->display->display_options['fields']['field_ding_staff_phone']['element_label_colon'] = FALSE;
  /* Felt: Profil: Email */
  $handler->display->display_options['fields']['field_ding_staff_email']['id'] = 'field_ding_staff_email';
  $handler->display->display_options['fields']['field_ding_staff_email']['table'] = 'field_data_field_ding_staff_email';
  $handler->display->display_options['fields']['field_ding_staff_email']['field'] = 'field_ding_staff_email';
  $handler->display->display_options['fields']['field_ding_staff_email']['label'] = 'E-mail';
  $handler->display->display_options['fields']['field_ding_staff_email']['element_label_colon'] = FALSE;
  /* Sorteringskriterie: Profil: Surname (field_ding_staff_surname) */
  $handler->display->display_options['sorts']['field_ding_staff_surname_value']['id'] = 'field_ding_staff_surname_value';
  $handler->display->display_options['sorts']['field_ding_staff_surname_value']['table'] = 'field_data_field_ding_staff_surname';
  $handler->display->display_options['sorts']['field_ding_staff_surname_value']['field'] = 'field_ding_staff_surname_value';
  /* Filterkriterie: Profil: Type */
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
  /* Forbindelse: OG membership: Group Indholdselement from OG membership */
  $handler->display->display_options['relationships']['og_membership_related_node_group']['id'] = 'og_membership_related_node_group';
  $handler->display->display_options['relationships']['og_membership_related_node_group']['table'] = 'og_membership';
  $handler->display->display_options['relationships']['og_membership_related_node_group']['field'] = 'og_membership_related_node_group';
  /* Forbindelse: Profil: Bruger uid */
  $handler->display->display_options['relationships']['user']['id'] = 'user';
  $handler->display->display_options['relationships']['user']['table'] = 'profile';
  $handler->display->display_options['relationships']['user']['field'] = 'user';
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Felt: Library node title (as token for header)(excluded) */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['relationship'] = 'og_membership_related_node_group';
  $handler->display->display_options['fields']['title']['ui_name'] = 'Library node title (as token for header)(excluded)';
  $handler->display->display_options['fields']['title']['label'] = '';
  $handler->display->display_options['fields']['title']['exclude'] = TRUE;
  $handler->display->display_options['fields']['title']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['title']['link_to_node'] = FALSE;
  /* Felt: GID from OG membership (for group header)(excluded) */
  $handler->display->display_options['fields']['gid']['id'] = 'gid';
  $handler->display->display_options['fields']['gid']['table'] = 'og_membership';
  $handler->display->display_options['fields']['gid']['field'] = 'gid';
  $handler->display->display_options['fields']['gid']['ui_name'] = 'GID from OG membership (for group header)(excluded)';
  $handler->display->display_options['fields']['gid']['label'] = '';
  $handler->display->display_options['fields']['gid']['exclude'] = TRUE;
  $handler->display->display_options['fields']['gid']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['gid']['alter']['text'] = '[title]';
  $handler->display->display_options['fields']['gid']['element_label_colon'] = FALSE;
  /* Felt: User uid (excluded) */
  $handler->display->display_options['fields']['user']['id'] = 'user';
  $handler->display->display_options['fields']['user']['table'] = 'profile';
  $handler->display->display_options['fields']['user']['field'] = 'user';
  $handler->display->display_options['fields']['user']['ui_name'] = 'User uid (excluded)';
  $handler->display->display_options['fields']['user']['label'] = '';
  $handler->display->display_options['fields']['user']['exclude'] = TRUE;
  $handler->display->display_options['fields']['user']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['user']['separator'] = '';
  /* Felt: Forename (excluded) */
  $handler->display->display_options['fields']['field_ding_staff_forename']['id'] = 'field_ding_staff_forename';
  $handler->display->display_options['fields']['field_ding_staff_forename']['table'] = 'field_data_field_ding_staff_forename';
  $handler->display->display_options['fields']['field_ding_staff_forename']['field'] = 'field_ding_staff_forename';
  $handler->display->display_options['fields']['field_ding_staff_forename']['ui_name'] = 'Forename (excluded)';
  $handler->display->display_options['fields']['field_ding_staff_forename']['label'] = '';
  $handler->display->display_options['fields']['field_ding_staff_forename']['exclude'] = TRUE;
  $handler->display->display_options['fields']['field_ding_staff_forename']['element_label_colon'] = FALSE;
  /* Felt: Profil: Image */
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
  /* Felt: Surname Forename (Link) */
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
  /* Felt: Profil: Position */
  $handler->display->display_options['fields']['field_ding_staff_position']['id'] = 'field_ding_staff_position';
  $handler->display->display_options['fields']['field_ding_staff_position']['table'] = 'field_data_field_ding_staff_position';
  $handler->display->display_options['fields']['field_ding_staff_position']['field'] = 'field_ding_staff_position';
  $handler->display->display_options['fields']['field_ding_staff_position']['label'] = '';
  $handler->display->display_options['fields']['field_ding_staff_position']['element_type'] = '0';
  $handler->display->display_options['fields']['field_ding_staff_position']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_ding_staff_position']['element_wrapper_type'] = 'div';
  $handler->display->display_options['fields']['field_ding_staff_position']['element_wrapper_class'] = 'staff-position';
  $handler->display->display_options['fields']['field_ding_staff_position']['element_default_classes'] = FALSE;
  /* Felt: Profil: Phone */
  $handler->display->display_options['fields']['field_ding_staff_phone']['id'] = 'field_ding_staff_phone';
  $handler->display->display_options['fields']['field_ding_staff_phone']['table'] = 'field_data_field_ding_staff_phone';
  $handler->display->display_options['fields']['field_ding_staff_phone']['field'] = 'field_ding_staff_phone';
  $handler->display->display_options['fields']['field_ding_staff_phone']['label'] = 'Telefon';
  $handler->display->display_options['fields']['field_ding_staff_phone']['element_type'] = '0';
  $handler->display->display_options['fields']['field_ding_staff_phone']['element_wrapper_type'] = 'div';
  $handler->display->display_options['fields']['field_ding_staff_phone']['element_wrapper_class'] = 'staff-phone';
  $handler->display->display_options['fields']['field_ding_staff_phone']['element_default_classes'] = FALSE;
  /* Felt: Profil: Email */
  $handler->display->display_options['fields']['field_ding_staff_email']['id'] = 'field_ding_staff_email';
  $handler->display->display_options['fields']['field_ding_staff_email']['table'] = 'field_data_field_ding_staff_email';
  $handler->display->display_options['fields']['field_ding_staff_email']['field'] = 'field_ding_staff_email';
  $handler->display->display_options['fields']['field_ding_staff_email']['label'] = 'E-mail';
  $handler->display->display_options['fields']['field_ding_staff_email']['element_type'] = '0';
  $handler->display->display_options['fields']['field_ding_staff_email']['element_wrapper_type'] = 'div';
  $handler->display->display_options['fields']['field_ding_staff_email']['element_wrapper_class'] = 'staff-email';
  $handler->display->display_options['fields']['field_ding_staff_email']['element_default_classes'] = FALSE;
  /* Felt: Profil: Department */
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
  /* Sorteringskriterie: Indhold: titel */
  $handler->display->display_options['sorts']['title']['id'] = 'title';
  $handler->display->display_options['sorts']['title']['table'] = 'node';
  $handler->display->display_options['sorts']['title']['field'] = 'title';
  $handler->display->display_options['sorts']['title']['relationship'] = 'og_membership_related_node_group';
  /* Sorteringskriterie: Profil: Surname (field_ding_staff_surname) */
  $handler->display->display_options['sorts']['field_ding_staff_surname_value']['id'] = 'field_ding_staff_surname_value';
  $handler->display->display_options['sorts']['field_ding_staff_surname_value']['table'] = 'field_data_field_ding_staff_surname';
  $handler->display->display_options['sorts']['field_ding_staff_surname_value']['field'] = 'field_ding_staff_surname_value';
  $handler->display->display_options['defaults']['filter_groups'] = FALSE;
  $handler->display->display_options['defaults']['filters'] = FALSE;
  /* Filterkriterie: Profil: Type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'profile';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'ding_staff_profile' => 'ding_staff_profile',
  );
  /* Filterkriterie: Bruger: Roller */
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
  /* Forbindelse: Profil: Department (field_ding_staff_department) */
  $handler->display->display_options['relationships']['field_ding_staff_department_tid']['id'] = 'field_ding_staff_department_tid';
  $handler->display->display_options['relationships']['field_ding_staff_department_tid']['table'] = 'field_data_field_ding_staff_department';
  $handler->display->display_options['relationships']['field_ding_staff_department_tid']['field'] = 'field_ding_staff_department_tid';
  /* Forbindelse: OG membership: Group Indholdselement from OG membership */
  $handler->display->display_options['relationships']['og_membership_related_node_group']['id'] = 'og_membership_related_node_group';
  $handler->display->display_options['relationships']['og_membership_related_node_group']['table'] = 'og_membership';
  $handler->display->display_options['relationships']['og_membership_related_node_group']['field'] = 'og_membership_related_node_group';
  /* Forbindelse: Profil: Bruger uid */
  $handler->display->display_options['relationships']['user']['id'] = 'user';
  $handler->display->display_options['relationships']['user']['table'] = 'profile';
  $handler->display->display_options['relationships']['user']['field'] = 'user';
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Felt: Department (for group header)(excluded) */
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
  /* Felt: User uid (excluded) */
  $handler->display->display_options['fields']['user']['id'] = 'user';
  $handler->display->display_options['fields']['user']['table'] = 'profile';
  $handler->display->display_options['fields']['user']['field'] = 'user';
  $handler->display->display_options['fields']['user']['ui_name'] = 'User uid (excluded)';
  $handler->display->display_options['fields']['user']['label'] = '';
  $handler->display->display_options['fields']['user']['exclude'] = TRUE;
  $handler->display->display_options['fields']['user']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['user']['separator'] = '';
  /* Felt: Forename (excluded) */
  $handler->display->display_options['fields']['field_ding_staff_forename']['id'] = 'field_ding_staff_forename';
  $handler->display->display_options['fields']['field_ding_staff_forename']['table'] = 'field_data_field_ding_staff_forename';
  $handler->display->display_options['fields']['field_ding_staff_forename']['field'] = 'field_ding_staff_forename';
  $handler->display->display_options['fields']['field_ding_staff_forename']['ui_name'] = 'Forename (excluded)';
  $handler->display->display_options['fields']['field_ding_staff_forename']['label'] = '';
  $handler->display->display_options['fields']['field_ding_staff_forename']['exclude'] = TRUE;
  $handler->display->display_options['fields']['field_ding_staff_forename']['element_label_colon'] = FALSE;
  /* Felt: Profil: Image */
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
  /* Felt: Forename Surname (Link) */
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
  /* Felt: Profil: Position */
  $handler->display->display_options['fields']['field_ding_staff_position']['id'] = 'field_ding_staff_position';
  $handler->display->display_options['fields']['field_ding_staff_position']['table'] = 'field_data_field_ding_staff_position';
  $handler->display->display_options['fields']['field_ding_staff_position']['field'] = 'field_ding_staff_position';
  $handler->display->display_options['fields']['field_ding_staff_position']['label'] = '';
  $handler->display->display_options['fields']['field_ding_staff_position']['element_type'] = '0';
  $handler->display->display_options['fields']['field_ding_staff_position']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_ding_staff_position']['element_wrapper_type'] = 'div';
  $handler->display->display_options['fields']['field_ding_staff_position']['element_wrapper_class'] = 'staff-position';
  $handler->display->display_options['fields']['field_ding_staff_position']['element_default_classes'] = FALSE;
  /* Felt: Profil: Phone */
  $handler->display->display_options['fields']['field_ding_staff_phone']['id'] = 'field_ding_staff_phone';
  $handler->display->display_options['fields']['field_ding_staff_phone']['table'] = 'field_data_field_ding_staff_phone';
  $handler->display->display_options['fields']['field_ding_staff_phone']['field'] = 'field_ding_staff_phone';
  $handler->display->display_options['fields']['field_ding_staff_phone']['label'] = 'Telefon';
  $handler->display->display_options['fields']['field_ding_staff_phone']['element_type'] = '0';
  $handler->display->display_options['fields']['field_ding_staff_phone']['element_wrapper_type'] = 'div';
  $handler->display->display_options['fields']['field_ding_staff_phone']['element_wrapper_class'] = 'staff-phone';
  $handler->display->display_options['fields']['field_ding_staff_phone']['element_default_classes'] = FALSE;
  /* Felt: Profil: Email */
  $handler->display->display_options['fields']['field_ding_staff_email']['id'] = 'field_ding_staff_email';
  $handler->display->display_options['fields']['field_ding_staff_email']['table'] = 'field_data_field_ding_staff_email';
  $handler->display->display_options['fields']['field_ding_staff_email']['field'] = 'field_ding_staff_email';
  $handler->display->display_options['fields']['field_ding_staff_email']['label'] = 'E-mail';
  $handler->display->display_options['fields']['field_ding_staff_email']['element_type'] = '0';
  $handler->display->display_options['fields']['field_ding_staff_email']['element_wrapper_type'] = 'div';
  $handler->display->display_options['fields']['field_ding_staff_email']['element_wrapper_class'] = 'staff-email';
  $handler->display->display_options['fields']['field_ding_staff_email']['element_default_classes'] = FALSE;
  $handler->display->display_options['defaults']['sorts'] = FALSE;
  /* Sorteringskriterie: Ord i ordforråd: Vægt */
  $handler->display->display_options['sorts']['weight']['id'] = 'weight';
  $handler->display->display_options['sorts']['weight']['table'] = 'taxonomy_term_data';
  $handler->display->display_options['sorts']['weight']['field'] = 'weight';
  $handler->display->display_options['sorts']['weight']['relationship'] = 'field_ding_staff_department_tid';
  /* Sorteringskriterie: Profil: Surname (field_ding_staff_surname) */
  $handler->display->display_options['sorts']['field_ding_staff_surname_value']['id'] = 'field_ding_staff_surname_value';
  $handler->display->display_options['sorts']['field_ding_staff_surname_value']['table'] = 'field_data_field_ding_staff_surname';
  $handler->display->display_options['sorts']['field_ding_staff_surname_value']['field'] = 'field_ding_staff_surname_value';
  $handler->display->display_options['defaults']['arguments'] = FALSE;
  /* Kontekstuelt filter: Indhold: Slug (field_ding_library_slug) */
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
  /* Filterkriterie: Profil: Type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'profile';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'ding_staff_profile' => 'ding_staff_profile',
  );
  /* Filterkriterie: Bruger: Roller */
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
    t('mere'),
    t('Udfør'),
    t('Gendan'),
    t('Sortér efter'),
    t('Stigende'),
    t('Faldende'),
    t('Antal elementer'),
    t('- Alle -'),
    t('Forskydning'),
    t('« første'),
    t('‹ forrige'),
    t('næste ›'),
    t('sidste »'),
    t('Tomt tekstfelt'),
    t('Der er ingen medarbejdere tilknyttet biblioteket'),
    t('.'),
    t(','),
    t('Navn'),
    t('[field_ding_staff_surname], [field_ding_staff_forename]'),
    t('Placering'),
    t('Department'),
    t('Telefon'),
    t('E-mail'),
    t('All staff list'),
    t('All libraries: Staff'),
    t('Group node from OG membership'),
    t('Bruger'),
    t('[title]'),
    t('Department(s)'),
    t('Library departments list'),
    t('Department grouped list, not using tables'),
    t('term fra field_ding_staff_department'),
    t('[field_ding_staff_forename] [field_ding_staff_surname]'),
    t('Alle'),
  );
  $export['ding_staff'] = $view;

  $view = new view();
  $view->name = 'ding_staff_admin_users';
  $view->description = 'List, add, and edit Ding! users.';
  $view->tag = 'default';
  $view->base_table = 'users';
  $view->human_name = 'Administration: Ding users';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'People (D!ng users)';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['use_more_text'] = 'mere';
  $handler->display->display_options['access']['type'] = 'none';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['exposed_form']['options']['submit_button'] = 'Udfør';
  $handler->display->display_options['exposed_form']['options']['reset_button_label'] = 'Gendan';
  $handler->display->display_options['exposed_form']['options']['exposed_sorts_label'] = 'Sortér efter';
  $handler->display->display_options['exposed_form']['options']['sort_asc_label'] = 'Stigende';
  $handler->display->display_options['exposed_form']['options']['sort_desc_label'] = 'Faldende';
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = '50';
  $handler->display->display_options['pager']['options']['expose']['items_per_page_label'] = 'Antal elementer';
  $handler->display->display_options['pager']['options']['expose']['items_per_page_options_all_label'] = '- Alle -';
  $handler->display->display_options['pager']['options']['expose']['offset_label'] = 'Forskydning';
  $handler->display->display_options['pager']['options']['tags']['first'] = '« første';
  $handler->display->display_options['pager']['options']['tags']['previous'] = '‹ forrige';
  $handler->display->display_options['pager']['options']['tags']['next'] = 'næste ›';
  $handler->display->display_options['pager']['options']['tags']['last'] = 'sidste »';
  $handler->display->display_options['style_plugin'] = 'table';
  $handler->display->display_options['style_options']['columns'] = array(
    'views_bulk_operations' => 'views_bulk_operations',
    'name' => 'name',
    'data' => 'name',
    'mail' => 'name',
    'rid' => 'rid',
    'field_ding_staff_forename' => 'field_ding_staff_forename',
    'field_ding_staff_surname' => 'field_ding_staff_forename',
    'status' => 'status',
    'created' => 'created',
    'access' => 'access',
    'edit_node' => 'edit_node',
    'cancel_node' => 'edit_node',
  );
  $handler->display->display_options['style_options']['default'] = 'access';
  $handler->display->display_options['style_options']['info'] = array(
    'views_bulk_operations' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'name' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '<br />',
      'empty_column' => 0,
    ),
    'data' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'mail' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'rid' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_ding_staff_forename' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '&nbsp;',
      'empty_column' => 0,
    ),
    'field_ding_staff_surname' => array(
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
    'created' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'access' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'edit_node' => array(
      'align' => '',
      'separator' => '&emsp;',
      'empty_column' => 0,
    ),
    'cancel_node' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
  );
  $handler->display->display_options['style_options']['sticky'] = TRUE;
  $handler->display->display_options['style_options']['empty_table'] = TRUE;
  /* Opførsel ved ingen resultater: Global: Ufiltreret tekst */
  $handler->display->display_options['empty']['area_text_custom']['id'] = 'area_text_custom';
  $handler->display->display_options['empty']['area_text_custom']['table'] = 'views';
  $handler->display->display_options['empty']['area_text_custom']['field'] = 'area_text_custom';
  $handler->display->display_options['empty']['area_text_custom']['empty'] = TRUE;
  $handler->display->display_options['empty']['area_text_custom']['content'] = 'Ingen brugere tilgængelige.';
  /* Forbindelse: Profile: staff */
  $handler->display->display_options['relationships']['profile']['id'] = 'profile';
  $handler->display->display_options['relationships']['profile']['table'] = 'users';
  $handler->display->display_options['relationships']['profile']['field'] = 'profile';
  $handler->display->display_options['relationships']['profile']['ui_name'] = 'Profile: staff';
  $handler->display->display_options['relationships']['profile']['bundle_types'] = array(
    'ding_staff_profile' => 'ding_staff_profile',
  );
  /* Felt: Masse-handlinger: Bruger */
  $handler->display->display_options['fields']['views_bulk_operations']['id'] = 'views_bulk_operations';
  $handler->display->display_options['fields']['views_bulk_operations']['table'] = 'users';
  $handler->display->display_options['fields']['views_bulk_operations']['field'] = 'views_bulk_operations';
  $handler->display->display_options['fields']['views_bulk_operations']['vbo_settings']['display_type'] = '0';
  $handler->display->display_options['fields']['views_bulk_operations']['vbo_settings']['enable_select_all_pages'] = 1;
  $handler->display->display_options['fields']['views_bulk_operations']['vbo_settings']['force_single'] = 0;
  $handler->display->display_options['fields']['views_bulk_operations']['vbo_settings']['entity_load_capacity'] = '10';
  $handler->display->display_options['fields']['views_bulk_operations']['vbo_operations'] = array(
    'action::user_block_user_action' => array(
      'selected' => 1,
      'postpone_processing' => 0,
      'skip_confirmation' => 0,
      'override_label' => 0,
      'label' => '',
    ),
    'action::role_delegation_delegate_roles_action' => array(
      'selected' => 1,
      'postpone_processing' => 0,
      'skip_confirmation' => 0,
      'override_label' => 1,
      'label' => 'Edit user roles',
    ),
    'action::views_bulk_operations_user_roles_action' => array(
      'selected' => 0,
      'postpone_processing' => 0,
      'skip_confirmation' => 0,
      'override_label' => 1,
      'label' => 'Change user roles',
    ),
    'action::views_bulk_operations_modify_action' => array(
      'selected' => 1,
      'postpone_processing' => 0,
      'skip_confirmation' => 0,
      'override_label' => 1,
      'label' => 'Ret brugerindstillinger',
      'settings' => array(
        'show_all_tokens' => 0,
        'display_values' => array(
          'name' => 'name',
          'mail' => 'mail',
          'status' => 'status',
          'theme' => 'theme',
          'language' => 'language',
          'user::group_audience' => 'user::group_audience',
        ),
      ),
    ),
    'action::views_bulk_operations_argument_selector_action' => array(
      'selected' => 0,
      'skip_confirmation' => 0,
      'override_label' => 0,
      'label' => '',
      'settings' => array(
        'url' => '',
      ),
    ),
    'action::system_send_email_action' => array(
      'selected' => 1,
      'postpone_processing' => 0,
      'skip_confirmation' => 0,
      'override_label' => 1,
      'label' => 'Send e-mail',
    ),
    'action::views_bulk_operations_delete_item' => array(
      'selected' => 1,
      'postpone_processing' => 0,
      'skip_confirmation' => 0,
      'override_label' => 1,
      'label' => 'Slet',
    ),
    'action::flag_user_action' => array(
      'selected' => 0,
      'postpone_processing' => 0,
      'skip_confirmation' => 0,
      'override_label' => 0,
      'label' => '',
    ),
    'action::views_bulk_operations_script_action' => array(
      'selected' => 0,
      'postpone_processing' => 0,
      'skip_confirmation' => 0,
      'override_label' => 0,
      'label' => '',
    ),
    'action::pathauto_user_update_action' => array(
      'selected' => 0,
      'postpone_processing' => 0,
      'skip_confirmation' => 0,
      'override_label' => 0,
      'label' => '',
    ),
  );
  /* Felt: Profil: Image */
  $handler->display->display_options['fields']['field_ding_staff_image']['id'] = 'field_ding_staff_image';
  $handler->display->display_options['fields']['field_ding_staff_image']['table'] = 'field_data_field_ding_staff_image';
  $handler->display->display_options['fields']['field_ding_staff_image']['field'] = 'field_ding_staff_image';
  $handler->display->display_options['fields']['field_ding_staff_image']['relationship'] = 'profile';
  $handler->display->display_options['fields']['field_ding_staff_image']['label'] = '';
  $handler->display->display_options['fields']['field_ding_staff_image']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_ding_staff_image']['click_sort_column'] = 'fid';
  $handler->display->display_options['fields']['field_ding_staff_image']['settings'] = array(
    'image_style' => 'ding_staff_thumbnail',
    'image_link' => '',
  );
  /* Felt: Bruger: Navn */
  $handler->display->display_options['fields']['name']['id'] = 'name';
  $handler->display->display_options['fields']['name']['table'] = 'users';
  $handler->display->display_options['fields']['name']['field'] = 'name';
  $handler->display->display_options['fields']['name']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['name']['alter']['ellipsis'] = FALSE;
  /* Felt: Bruger: E-mail */
  $handler->display->display_options['fields']['mail']['id'] = 'mail';
  $handler->display->display_options['fields']['mail']['table'] = 'users';
  $handler->display->display_options['fields']['mail']['field'] = 'mail';
  $handler->display->display_options['fields']['mail']['label'] = '';
  $handler->display->display_options['fields']['mail']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['mail']['link_to_user'] = '0';
  /* Felt: Bruger: Roller */
  $handler->display->display_options['fields']['rid']['id'] = 'rid';
  $handler->display->display_options['fields']['rid']['table'] = 'users_roles';
  $handler->display->display_options['fields']['rid']['field'] = 'rid';
  $handler->display->display_options['fields']['rid']['type'] = 'ul';
  /* Felt: Profil: Forename */
  $handler->display->display_options['fields']['field_ding_staff_forename']['id'] = 'field_ding_staff_forename';
  $handler->display->display_options['fields']['field_ding_staff_forename']['table'] = 'field_data_field_ding_staff_forename';
  $handler->display->display_options['fields']['field_ding_staff_forename']['field'] = 'field_ding_staff_forename';
  $handler->display->display_options['fields']['field_ding_staff_forename']['relationship'] = 'profile';
  $handler->display->display_options['fields']['field_ding_staff_forename']['label'] = 'Name (in Staff)';
  /* Felt: Profil: Surname */
  $handler->display->display_options['fields']['field_ding_staff_surname']['id'] = 'field_ding_staff_surname';
  $handler->display->display_options['fields']['field_ding_staff_surname']['table'] = 'field_data_field_ding_staff_surname';
  $handler->display->display_options['fields']['field_ding_staff_surname']['field'] = 'field_ding_staff_surname';
  $handler->display->display_options['fields']['field_ding_staff_surname']['relationship'] = 'profile';
  $handler->display->display_options['fields']['field_ding_staff_surname']['label'] = 'Surname (Staff)';
  /* Felt: Bruger: Aktiv */
  $handler->display->display_options['fields']['status']['id'] = 'status';
  $handler->display->display_options['fields']['status']['table'] = 'users';
  $handler->display->display_options['fields']['status']['field'] = 'status';
  $handler->display->display_options['fields']['status']['label'] = 'Status';
  $handler->display->display_options['fields']['status']['type'] = 'active-blocked';
  $handler->display->display_options['fields']['status']['not'] = 0;
  /* Felt: Bruger: Dato */
  $handler->display->display_options['fields']['created']['id'] = 'created';
  $handler->display->display_options['fields']['created']['table'] = 'users';
  $handler->display->display_options['fields']['created']['field'] = 'created';
  $handler->display->display_options['fields']['created']['label'] = 'Medlem i';
  $handler->display->display_options['fields']['created']['date_format'] = 'raw time ago';
  /* Felt: Bruger: Seneste tilgang */
  $handler->display->display_options['fields']['access']['id'] = 'access';
  $handler->display->display_options['fields']['access']['table'] = 'users';
  $handler->display->display_options['fields']['access']['field'] = 'access';
  $handler->display->display_options['fields']['access']['date_format'] = 'raw time ago';
  /* Felt: Bruger: Redigér-link */
  $handler->display->display_options['fields']['edit_node']['id'] = 'edit_node';
  $handler->display->display_options['fields']['edit_node']['table'] = 'users';
  $handler->display->display_options['fields']['edit_node']['field'] = 'edit_node';
  $handler->display->display_options['fields']['edit_node']['label'] = 'Handlinger';
  /* Felt: Bruger: Annullér-link */
  $handler->display->display_options['fields']['cancel_node']['id'] = 'cancel_node';
  $handler->display->display_options['fields']['cancel_node']['table'] = 'users';
  $handler->display->display_options['fields']['cancel_node']['field'] = 'cancel_node';
  $handler->display->display_options['fields']['cancel_node']['label'] = '';
  $handler->display->display_options['fields']['cancel_node']['element_label_colon'] = FALSE;
  /* Sorteringskriterie: Bruger: Dato */
  $handler->display->display_options['sorts']['created']['id'] = 'created';
  $handler->display->display_options['sorts']['created']['table'] = 'users';
  $handler->display->display_options['sorts']['created']['field'] = 'created';
  $handler->display->display_options['sorts']['created']['order'] = 'DESC';
  /* Filterkriterie: Bruger: Navn */
  $handler->display->display_options['filters']['uid']['id'] = 'uid';
  $handler->display->display_options['filters']['uid']['table'] = 'users';
  $handler->display->display_options['filters']['uid']['field'] = 'uid';
  $handler->display->display_options['filters']['uid']['operator'] = 'not in';
  $handler->display->display_options['filters']['uid']['value'] = array(
    0 => 0,
  );
  $handler->display->display_options['filters']['uid']['group'] = 1;
  /* Filterkriterie: Bruger: Navn (rå data) */
  $handler->display->display_options['filters']['name']['id'] = 'name';
  $handler->display->display_options['filters']['name']['table'] = 'users';
  $handler->display->display_options['filters']['name']['field'] = 'name';
  $handler->display->display_options['filters']['name']['operator'] = 'contains';
  $handler->display->display_options['filters']['name']['group'] = 1;
  $handler->display->display_options['filters']['name']['exposed'] = TRUE;
  $handler->display->display_options['filters']['name']['expose']['operator_id'] = 'name_op';
  $handler->display->display_options['filters']['name']['expose']['label'] = 'Brugernavn';
  $handler->display->display_options['filters']['name']['expose']['operator'] = 'name_op';
  $handler->display->display_options['filters']['name']['expose']['identifier'] = 'name';
  $handler->display->display_options['filters']['name']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    4 => 0,
    5 => 0,
    6 => 0,
    7 => 0,
    3 => 0,
    8 => 0,
  );
  /* Filterkriterie: Bruger: E-mail */
  $handler->display->display_options['filters']['mail']['id'] = 'mail';
  $handler->display->display_options['filters']['mail']['table'] = 'users';
  $handler->display->display_options['filters']['mail']['field'] = 'mail';
  $handler->display->display_options['filters']['mail']['operator'] = 'contains';
  $handler->display->display_options['filters']['mail']['group'] = 1;
  $handler->display->display_options['filters']['mail']['exposed'] = TRUE;
  $handler->display->display_options['filters']['mail']['expose']['operator_id'] = 'mail_op';
  $handler->display->display_options['filters']['mail']['expose']['label'] = 'E-mail';
  $handler->display->display_options['filters']['mail']['expose']['operator'] = 'mail_op';
  $handler->display->display_options['filters']['mail']['expose']['identifier'] = 'mail';
  $handler->display->display_options['filters']['mail']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    4 => 0,
    5 => 0,
    6 => 0,
    7 => 0,
    3 => 0,
    8 => 0,
  );
  /* Filterkriterie: Bruger: Aktiv */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'users';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = 'All';
  $handler->display->display_options['filters']['status']['group'] = 1;
  $handler->display->display_options['filters']['status']['exposed'] = TRUE;
  $handler->display->display_options['filters']['status']['expose']['operator_id'] = '';
  $handler->display->display_options['filters']['status']['expose']['label'] = 'Aktiv';
  $handler->display->display_options['filters']['status']['expose']['operator'] = 'status_op';
  $handler->display->display_options['filters']['status']['expose']['identifier'] = 'status';
  $handler->display->display_options['filters']['status']['expose']['remember'] = TRUE;
  $handler->display->display_options['filters']['status']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    4 => 0,
    5 => 0,
    6 => 0,
    7 => 0,
    3 => 0,
    8 => 0,
  );
  /* Filterkriterie: Bruger: Roller */
  $handler->display->display_options['filters']['rid']['id'] = 'rid';
  $handler->display->display_options['filters']['rid']['table'] = 'users_roles';
  $handler->display->display_options['filters']['rid']['field'] = 'rid';
  $handler->display->display_options['filters']['rid']['group'] = 1;
  $handler->display->display_options['filters']['rid']['exposed'] = TRUE;
  $handler->display->display_options['filters']['rid']['expose']['operator_id'] = 'rid_op';
  $handler->display->display_options['filters']['rid']['expose']['label'] = 'Rolle';
  $handler->display->display_options['filters']['rid']['expose']['operator'] = 'rid_op';
  $handler->display->display_options['filters']['rid']['expose']['identifier'] = 'rid';
  $handler->display->display_options['filters']['rid']['expose']['remember'] = TRUE;
  $handler->display->display_options['filters']['rid']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    4 => 0,
    5 => 0,
    6 => 0,
    7 => 0,
    3 => 0,
    8 => 0,
  );
  /* Filterkriterie: Profil: Forename (field_ding_staff_forename) */
  $handler->display->display_options['filters']['field_ding_staff_forename_value']['id'] = 'field_ding_staff_forename_value';
  $handler->display->display_options['filters']['field_ding_staff_forename_value']['table'] = 'field_data_field_ding_staff_forename';
  $handler->display->display_options['filters']['field_ding_staff_forename_value']['field'] = 'field_ding_staff_forename_value';
  $handler->display->display_options['filters']['field_ding_staff_forename_value']['relationship'] = 'profile';
  $handler->display->display_options['filters']['field_ding_staff_forename_value']['operator'] = 'contains';
  $handler->display->display_options['filters']['field_ding_staff_forename_value']['group'] = 1;
  $handler->display->display_options['filters']['field_ding_staff_forename_value']['exposed'] = TRUE;
  $handler->display->display_options['filters']['field_ding_staff_forename_value']['expose']['operator_id'] = 'field_ding_staff_forename_value_op';
  $handler->display->display_options['filters']['field_ding_staff_forename_value']['expose']['label'] = 'Forename (Staff)';
  $handler->display->display_options['filters']['field_ding_staff_forename_value']['expose']['operator'] = 'field_ding_staff_forename_value_op';
  $handler->display->display_options['filters']['field_ding_staff_forename_value']['expose']['identifier'] = 'field_ding_staff_forename_value';
  $handler->display->display_options['filters']['field_ding_staff_forename_value']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    4 => 0,
    5 => 0,
    6 => 0,
    7 => 0,
    3 => 0,
    8 => 0,
  );
  /* Filterkriterie: Profil: Surname (field_ding_staff_surname) */
  $handler->display->display_options['filters']['field_ding_staff_surname_value']['id'] = 'field_ding_staff_surname_value';
  $handler->display->display_options['filters']['field_ding_staff_surname_value']['table'] = 'field_data_field_ding_staff_surname';
  $handler->display->display_options['filters']['field_ding_staff_surname_value']['field'] = 'field_ding_staff_surname_value';
  $handler->display->display_options['filters']['field_ding_staff_surname_value']['relationship'] = 'profile';
  $handler->display->display_options['filters']['field_ding_staff_surname_value']['operator'] = 'contains';
  $handler->display->display_options['filters']['field_ding_staff_surname_value']['group'] = 1;
  $handler->display->display_options['filters']['field_ding_staff_surname_value']['exposed'] = TRUE;
  $handler->display->display_options['filters']['field_ding_staff_surname_value']['expose']['operator_id'] = 'field_ding_staff_surname_value_op';
  $handler->display->display_options['filters']['field_ding_staff_surname_value']['expose']['label'] = 'Surname (Staff)';
  $handler->display->display_options['filters']['field_ding_staff_surname_value']['expose']['operator'] = 'field_ding_staff_surname_value_op';
  $handler->display->display_options['filters']['field_ding_staff_surname_value']['expose']['identifier'] = 'field_ding_staff_surname_value';
  $handler->display->display_options['filters']['field_ding_staff_surname_value']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    4 => 0,
    5 => 0,
    6 => 0,
    7 => 0,
    3 => 0,
    8 => 0,
  );

  /* Display: Page */
  $handler = $view->new_display('page', 'Page', 'ding_staff_people_list');
  $handler->display->display_options['defaults']['access'] = FALSE;
  $handler->display->display_options['access']['type'] = 'role';
  $handler->display->display_options['access']['role'] = array(
    7 => '7',
    8 => '8',
  );
  $handler->display->display_options['path'] = 'admin/ding_users';
  $handler->display->display_options['menu']['type'] = 'normal';
  $handler->display->display_options['menu']['title'] = 'People (+staff)';
  $handler->display->display_options['menu']['description'] = 'Administer users - incl. staff profiles';
  $handler->display->display_options['menu']['weight'] = '10';
  $handler->display->display_options['menu']['name'] = 'management';
  $handler->display->display_options['menu']['context'] = 0;
  $handler->display->display_options['menu']['context_only_inline'] = 0;
  $translatables['ding_staff_admin_users'] = array(
    t('Master'),
    t('People (D!ng users)'),
    t('mere'),
    t('Udfør'),
    t('Gendan'),
    t('Sortér efter'),
    t('Stigende'),
    t('Faldende'),
    t('Antal elementer'),
    t('- Alle -'),
    t('Forskydning'),
    t('« første'),
    t('‹ forrige'),
    t('næste ›'),
    t('sidste »'),
    t('Ingen brugere tilgængelige.'),
    t('Profil'),
    t('Bruger'),
    t('- Vælg en handling -'),
    t('Edit user roles'),
    t('Change user roles'),
    t('Ret brugerindstillinger'),
    t('Send e-mail'),
    t('Slet'),
    t('Navn'),
    t('Roller'),
    t('Name (in Staff)'),
    t('Surname (Staff)'),
    t('Status'),
    t('Medlem i'),
    t('Seneste tilgang'),
    t('Handlinger'),
    t('Brugernavn'),
    t('E-mail'),
    t('Aktiv'),
    t('Rolle'),
    t('Forename (Staff)'),
    t('Page'),
  );
  $export['ding_staff_admin_users'] = $view;

  return $export;
}
