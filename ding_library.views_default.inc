<?php
/**
 * @file
 * ding_library.views_default.inc
 */

/**
 * Implements hook_views_default_views().
 */
function ding_library_views_default_views() {
  $export = array();

  $view = new view;
  $view->name = 'ding_library';
  $view->description = '';
  $view->tag = 'ding_library';
  $view->base_table = 'node';
  $view->human_name = 'Ding library';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['query']['options']['query_comment'] = FALSE;
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['exposed_form']['options']['reset_button_label'] = 'Gendan';
  $handler->display->display_options['pager']['type'] = 'none';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['style_plugin'] = 'list';
  $handler->display->display_options['style_options']['row_class'] = 'vcard clearfix library-[nid]';
  $handler->display->display_options['style_options']['class'] = 'library-list';
  $handler->display->display_options['style_options']['wrapper_class'] = '';
  $handler->display->display_options['row_plugin'] = 'fields';
  /* Field: Content: Nid */
  $handler->display->display_options['fields']['nid']['id'] = 'nid';
  $handler->display->display_options['fields']['nid']['table'] = 'node';
  $handler->display->display_options['fields']['nid']['field'] = 'nid';
  $handler->display->display_options['fields']['nid']['label'] = '';
  $handler->display->display_options['fields']['nid']['exclude'] = TRUE;
  $handler->display->display_options['fields']['nid']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['nid']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['nid']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['nid']['alter']['external'] = 0;
  $handler->display->display_options['fields']['nid']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['nid']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['nid']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['nid']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['nid']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['nid']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['nid']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['nid']['alter']['html'] = 0;
  $handler->display->display_options['fields']['nid']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['nid']['element_default_classes'] = 0;
  $handler->display->display_options['fields']['nid']['hide_empty'] = 0;
  $handler->display->display_options['fields']['nid']['empty_zero'] = 0;
  $handler->display->display_options['fields']['nid']['hide_alter_empty'] = 0;
  $handler->display->display_options['fields']['nid']['link_to_node'] = 0;
  /* Field: div class=libraries-content */
  $handler->display->display_options['fields']['nothing_1']['id'] = 'nothing_1';
  $handler->display->display_options['fields']['nothing_1']['table'] = 'views';
  $handler->display->display_options['fields']['nothing_1']['field'] = 'nothing';
  $handler->display->display_options['fields']['nothing_1']['ui_name'] = 'div class=libraries-content';
  $handler->display->display_options['fields']['nothing_1']['label'] = '';
  $handler->display->display_options['fields']['nothing_1']['alter']['text'] = '<div class="libraries-content">';
  $handler->display->display_options['fields']['nothing_1']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['nothing_1']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['nothing_1']['alter']['external'] = 0;
  $handler->display->display_options['fields']['nothing_1']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['nothing_1']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['nothing_1']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['nothing_1']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['nothing_1']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['nothing_1']['alter']['more_link'] = 0;
  $handler->display->display_options['fields']['nothing_1']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['nothing_1']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['nothing_1']['alter']['html'] = 0;
  $handler->display->display_options['fields']['nothing_1']['element_type'] = '0';
  $handler->display->display_options['fields']['nothing_1']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['nothing_1']['element_wrapper_type'] = '0';
  $handler->display->display_options['fields']['nothing_1']['element_default_classes'] = 0;
  $handler->display->display_options['fields']['nothing_1']['hide_empty'] = 0;
  $handler->display->display_options['fields']['nothing_1']['empty_zero'] = 0;
  $handler->display->display_options['fields']['nothing_1']['hide_alter_empty'] = 0;
  /* Field: Content: Title */
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
  $handler->display->display_options['fields']['title']['element_type'] = 'h2';
  $handler->display->display_options['fields']['title']['element_class'] = 'libraries-title org';
  $handler->display->display_options['fields']['title']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['title']['element_wrapper_type'] = '0';
  $handler->display->display_options['fields']['title']['element_default_classes'] = 0;
  $handler->display->display_options['fields']['title']['hide_empty'] = 0;
  $handler->display->display_options['fields']['title']['empty_zero'] = 0;
  $handler->display->display_options['fields']['title']['hide_alter_empty'] = 0;
  $handler->display->display_options['fields']['title']['link_to_node'] = 1;
  /* Field: Content: List image */
  $handler->display->display_options['fields']['field_ding_library_list_image']['id'] = 'field_ding_library_list_image';
  $handler->display->display_options['fields']['field_ding_library_list_image']['table'] = 'field_data_field_ding_library_list_image';
  $handler->display->display_options['fields']['field_ding_library_list_image']['field'] = 'field_ding_library_list_image';
  $handler->display->display_options['fields']['field_ding_library_list_image']['label'] = '';
  $handler->display->display_options['fields']['field_ding_library_list_image']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['field_ding_library_list_image']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['field_ding_library_list_image']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['field_ding_library_list_image']['alter']['external'] = 0;
  $handler->display->display_options['fields']['field_ding_library_list_image']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['field_ding_library_list_image']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['field_ding_library_list_image']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['field_ding_library_list_image']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['field_ding_library_list_image']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['field_ding_library_list_image']['alter']['more_link'] = 0;
  $handler->display->display_options['fields']['field_ding_library_list_image']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['field_ding_library_list_image']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['field_ding_library_list_image']['alter']['html'] = 0;
  $handler->display->display_options['fields']['field_ding_library_list_image']['element_class'] = 'photo';
  $handler->display->display_options['fields']['field_ding_library_list_image']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_ding_library_list_image']['element_wrapper_type'] = '0';
  $handler->display->display_options['fields']['field_ding_library_list_image']['element_default_classes'] = 0;
  $handler->display->display_options['fields']['field_ding_library_list_image']['hide_empty'] = 0;
  $handler->display->display_options['fields']['field_ding_library_list_image']['empty_zero'] = 0;
  $handler->display->display_options['fields']['field_ding_library_list_image']['hide_alter_empty'] = 1;
  $handler->display->display_options['fields']['field_ding_library_list_image']['click_sort_column'] = 'fid';
  $handler->display->display_options['fields']['field_ding_library_list_image']['settings'] = array(
    'image_style' => 'ding_attachment_small',
    'image_link' => 'content',
  );
  $handler->display->display_options['fields']['field_ding_library_list_image']['field_api_classes'] = 0;
  /* Field: Content: Addresse */
  $handler->display->display_options['fields']['field_ding_library_addresse']['id'] = 'field_ding_library_addresse';
  $handler->display->display_options['fields']['field_ding_library_addresse']['table'] = 'field_data_field_ding_library_addresse';
  $handler->display->display_options['fields']['field_ding_library_addresse']['field'] = 'field_ding_library_addresse';
  $handler->display->display_options['fields']['field_ding_library_addresse']['label'] = 'Address';
  $handler->display->display_options['fields']['field_ding_library_addresse']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['field_ding_library_addresse']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['field_ding_library_addresse']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['field_ding_library_addresse']['alter']['external'] = 0;
  $handler->display->display_options['fields']['field_ding_library_addresse']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['field_ding_library_addresse']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['field_ding_library_addresse']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['field_ding_library_addresse']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['field_ding_library_addresse']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['field_ding_library_addresse']['alter']['more_link'] = 0;
  $handler->display->display_options['fields']['field_ding_library_addresse']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['field_ding_library_addresse']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['field_ding_library_addresse']['alter']['html'] = 0;
  $handler->display->display_options['fields']['field_ding_library_addresse']['element_type'] = 'div';
  $handler->display->display_options['fields']['field_ding_library_addresse']['element_class'] = 'dd adr address';
  $handler->display->display_options['fields']['field_ding_library_addresse']['element_label_type'] = 'div';
  $handler->display->display_options['fields']['field_ding_library_addresse']['element_label_class'] = 'dt label adr-label';
  $handler->display->display_options['fields']['field_ding_library_addresse']['element_label_colon'] = 1;
  $handler->display->display_options['fields']['field_ding_library_addresse']['element_wrapper_class'] = 'dl address-content';
  $handler->display->display_options['fields']['field_ding_library_addresse']['element_default_classes'] = 0;
  $handler->display->display_options['fields']['field_ding_library_addresse']['hide_empty'] = 0;
  $handler->display->display_options['fields']['field_ding_library_addresse']['empty_zero'] = 0;
  $handler->display->display_options['fields']['field_ding_library_addresse']['hide_alter_empty'] = 1;
  $handler->display->display_options['fields']['field_ding_library_addresse']['click_sort_column'] = 'country';
  $handler->display->display_options['fields']['field_ding_library_addresse']['settings'] = array(
    'use_widget_handlers' => 1,
    'format_handlers' => array(
      'address' => 'address',
    ),
  );
  $handler->display->display_options['fields']['field_ding_library_addresse']['field_api_classes'] = 0;
  /* Field: Content: Phone number */
  $handler->display->display_options['fields']['field_ding_library_phone_number']['id'] = 'field_ding_library_phone_number';
  $handler->display->display_options['fields']['field_ding_library_phone_number']['table'] = 'field_data_field_ding_library_phone_number';
  $handler->display->display_options['fields']['field_ding_library_phone_number']['field'] = 'field_ding_library_phone_number';
  $handler->display->display_options['fields']['field_ding_library_phone_number']['label'] = 'Phone';
  $handler->display->display_options['fields']['field_ding_library_phone_number']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['field_ding_library_phone_number']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['field_ding_library_phone_number']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['field_ding_library_phone_number']['alter']['external'] = 0;
  $handler->display->display_options['fields']['field_ding_library_phone_number']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['field_ding_library_phone_number']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['field_ding_library_phone_number']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['field_ding_library_phone_number']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['field_ding_library_phone_number']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['field_ding_library_phone_number']['alter']['more_link'] = 0;
  $handler->display->display_options['fields']['field_ding_library_phone_number']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['field_ding_library_phone_number']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['field_ding_library_phone_number']['alter']['html'] = 0;
  $handler->display->display_options['fields']['field_ding_library_phone_number']['element_type'] = 'div';
  $handler->display->display_options['fields']['field_ding_library_phone_number']['element_class'] = 'dd phone tel';
  $handler->display->display_options['fields']['field_ding_library_phone_number']['element_label_type'] = 'div';
  $handler->display->display_options['fields']['field_ding_library_phone_number']['element_label_class'] = 'dt label tel-label';
  $handler->display->display_options['fields']['field_ding_library_phone_number']['element_label_colon'] = 1;
  $handler->display->display_options['fields']['field_ding_library_phone_number']['element_wrapper_class'] = 'dl phone-content';
  $handler->display->display_options['fields']['field_ding_library_phone_number']['element_default_classes'] = 0;
  $handler->display->display_options['fields']['field_ding_library_phone_number']['hide_empty'] = 0;
  $handler->display->display_options['fields']['field_ding_library_phone_number']['empty_zero'] = 0;
  $handler->display->display_options['fields']['field_ding_library_phone_number']['hide_alter_empty'] = 1;
  $handler->display->display_options['fields']['field_ding_library_phone_number']['field_api_classes'] = 0;
  /* Field: Content: Fax number */
  $handler->display->display_options['fields']['field_ding_library_fax_number']['id'] = 'field_ding_library_fax_number';
  $handler->display->display_options['fields']['field_ding_library_fax_number']['table'] = 'field_data_field_ding_library_fax_number';
  $handler->display->display_options['fields']['field_ding_library_fax_number']['field'] = 'field_ding_library_fax_number';
  $handler->display->display_options['fields']['field_ding_library_fax_number']['label'] = 'Fax';
  $handler->display->display_options['fields']['field_ding_library_fax_number']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['field_ding_library_fax_number']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['field_ding_library_fax_number']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['field_ding_library_fax_number']['alter']['external'] = 0;
  $handler->display->display_options['fields']['field_ding_library_fax_number']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['field_ding_library_fax_number']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['field_ding_library_fax_number']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['field_ding_library_fax_number']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['field_ding_library_fax_number']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['field_ding_library_fax_number']['alter']['more_link'] = 0;
  $handler->display->display_options['fields']['field_ding_library_fax_number']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['field_ding_library_fax_number']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['field_ding_library_fax_number']['alter']['html'] = 0;
  $handler->display->display_options['fields']['field_ding_library_fax_number']['element_type'] = 'div';
  $handler->display->display_options['fields']['field_ding_library_fax_number']['element_class'] = 'dd fax';
  $handler->display->display_options['fields']['field_ding_library_fax_number']['element_label_type'] = 'div';
  $handler->display->display_options['fields']['field_ding_library_fax_number']['element_label_class'] = 'dt label fax-label';
  $handler->display->display_options['fields']['field_ding_library_fax_number']['element_label_colon'] = 1;
  $handler->display->display_options['fields']['field_ding_library_fax_number']['element_wrapper_class'] = 'dl fax-content';
  $handler->display->display_options['fields']['field_ding_library_fax_number']['element_default_classes'] = 0;
  $handler->display->display_options['fields']['field_ding_library_fax_number']['hide_empty'] = 0;
  $handler->display->display_options['fields']['field_ding_library_fax_number']['empty_zero'] = 0;
  $handler->display->display_options['fields']['field_ding_library_fax_number']['hide_alter_empty'] = 1;
  $handler->display->display_options['fields']['field_ding_library_fax_number']['field_api_classes'] = 0;
  /* Field: Content: E-mail */
  $handler->display->display_options['fields']['field_ding_library_mail']['id'] = 'field_ding_library_mail';
  $handler->display->display_options['fields']['field_ding_library_mail']['table'] = 'field_data_field_ding_library_mail';
  $handler->display->display_options['fields']['field_ding_library_mail']['field'] = 'field_ding_library_mail';
  $handler->display->display_options['fields']['field_ding_library_mail']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['field_ding_library_mail']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['field_ding_library_mail']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['field_ding_library_mail']['alter']['external'] = 0;
  $handler->display->display_options['fields']['field_ding_library_mail']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['field_ding_library_mail']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['field_ding_library_mail']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['field_ding_library_mail']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['field_ding_library_mail']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['field_ding_library_mail']['alter']['more_link'] = 0;
  $handler->display->display_options['fields']['field_ding_library_mail']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['field_ding_library_mail']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['field_ding_library_mail']['alter']['html'] = 0;
  $handler->display->display_options['fields']['field_ding_library_mail']['element_type'] = 'div';
  $handler->display->display_options['fields']['field_ding_library_mail']['element_class'] = 'dd email';
  $handler->display->display_options['fields']['field_ding_library_mail']['element_label_type'] = 'div';
  $handler->display->display_options['fields']['field_ding_library_mail']['element_label_class'] = 'dt label email-label';
  $handler->display->display_options['fields']['field_ding_library_mail']['element_label_colon'] = 1;
  $handler->display->display_options['fields']['field_ding_library_mail']['element_wrapper_class'] = 'dl email-content';
  $handler->display->display_options['fields']['field_ding_library_mail']['element_default_classes'] = 0;
  $handler->display->display_options['fields']['field_ding_library_mail']['hide_empty'] = 0;
  $handler->display->display_options['fields']['field_ding_library_mail']['empty_zero'] = 0;
  $handler->display->display_options['fields']['field_ding_library_mail']['hide_alter_empty'] = 1;
  $handler->display->display_options['fields']['field_ding_library_mail']['field_api_classes'] = 0;
  /* Field: /div */
  $handler->display->display_options['fields']['nothing']['id'] = 'nothing';
  $handler->display->display_options['fields']['nothing']['table'] = 'views';
  $handler->display->display_options['fields']['nothing']['field'] = 'nothing';
  $handler->display->display_options['fields']['nothing']['ui_name'] = '/div';
  $handler->display->display_options['fields']['nothing']['label'] = '';
  $handler->display->display_options['fields']['nothing']['alter']['text'] = '</div>';
  $handler->display->display_options['fields']['nothing']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['nothing']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['nothing']['alter']['external'] = 0;
  $handler->display->display_options['fields']['nothing']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['nothing']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['nothing']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['nothing']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['nothing']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['nothing']['alter']['more_link'] = 0;
  $handler->display->display_options['fields']['nothing']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['nothing']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['nothing']['alter']['html'] = 0;
  $handler->display->display_options['fields']['nothing']['element_type'] = '0';
  $handler->display->display_options['fields']['nothing']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['nothing']['element_wrapper_type'] = '0';
  $handler->display->display_options['fields']['nothing']['element_default_classes'] = 0;
  $handler->display->display_options['fields']['nothing']['hide_empty'] = 0;
  $handler->display->display_options['fields']['nothing']['empty_zero'] = 0;
  $handler->display->display_options['fields']['nothing']['hide_alter_empty'] = 0;
  /* Field: Content: Opening hours */
  $handler->display->display_options['fields']['field_ding_library_opening_hours']['id'] = 'field_ding_library_opening_hours';
  $handler->display->display_options['fields']['field_ding_library_opening_hours']['table'] = 'field_data_field_ding_library_opening_hours';
  $handler->display->display_options['fields']['field_ding_library_opening_hours']['field'] = 'field_ding_library_opening_hours';
  $handler->display->display_options['fields']['field_ding_library_opening_hours']['label'] = 'Opening Hours';
  $handler->display->display_options['fields']['field_ding_library_opening_hours']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['field_ding_library_opening_hours']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['field_ding_library_opening_hours']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['field_ding_library_opening_hours']['alter']['external'] = 0;
  $handler->display->display_options['fields']['field_ding_library_opening_hours']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['field_ding_library_opening_hours']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['field_ding_library_opening_hours']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['field_ding_library_opening_hours']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['field_ding_library_opening_hours']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['field_ding_library_opening_hours']['alter']['more_link'] = 0;
  $handler->display->display_options['fields']['field_ding_library_opening_hours']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['field_ding_library_opening_hours']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['field_ding_library_opening_hours']['alter']['html'] = 0;
  $handler->display->display_options['fields']['field_ding_library_opening_hours']['element_type'] = 'div';
  $handler->display->display_options['fields']['field_ding_library_opening_hours']['element_class'] = 'opening-hours-content';
  $handler->display->display_options['fields']['field_ding_library_opening_hours']['element_label_type'] = 'h3';
  $handler->display->display_options['fields']['field_ding_library_opening_hours']['element_label_class'] = 'opening-hours-title';
  $handler->display->display_options['fields']['field_ding_library_opening_hours']['element_label_colon'] = 0;
  $handler->display->display_options['fields']['field_ding_library_opening_hours']['element_wrapper_type'] = 'div';
  $handler->display->display_options['fields']['field_ding_library_opening_hours']['element_wrapper_class'] = 'opening-hours';
  $handler->display->display_options['fields']['field_ding_library_opening_hours']['element_default_classes'] = 0;
  $handler->display->display_options['fields']['field_ding_library_opening_hours']['hide_empty'] = 0;
  $handler->display->display_options['fields']['field_ding_library_opening_hours']['empty_zero'] = 0;
  $handler->display->display_options['fields']['field_ding_library_opening_hours']['hide_alter_empty'] = 1;
  $handler->display->display_options['fields']['field_ding_library_opening_hours']['type'] = 'text_plain';
  $handler->display->display_options['fields']['field_ding_library_opening_hours']['field_api_classes'] = 0;
  /* Sort criterion: Content: Title */
  $handler->display->display_options['sorts']['title']['id'] = 'title';
  $handler->display->display_options['sorts']['title']['table'] = 'node';
  $handler->display->display_options['sorts']['title']['field'] = 'title';
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
  $handler->display->display_options['filters']['type']['value'] = array(
    'ding_library' => 'ding_library',
  );
  /* Filter criterion: Content translation: Language */
  $handler->display->display_options['filters']['language']['id'] = 'language';
  $handler->display->display_options['filters']['language']['table'] = 'node';
  $handler->display->display_options['filters']['language']['field'] = 'language';
  $handler->display->display_options['filters']['language']['value'] = array(
    '***CURRENT_LANGUAGE***' => '***CURRENT_LANGUAGE***',
    'und' => 'und',
  );

  /* Display: Libraries list */
  $handler = $view->new_display('panel_pane', 'Libraries list', 'ding_library_libraries_list');
  $handler->display->display_options['pane_category']['name'] = 'Library panes';
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

  /* Display: OpenLayers Data Overlay */
  $handler = $view->new_display('openlayers', 'OpenLayers Data Overlay', 'openlayers_1');
  $handler->display->display_options['pager']['type'] = 'none';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['defaults']['style_plugin'] = FALSE;
  $handler->display->display_options['style_plugin'] = 'openlayers_data';
  $handler->display->display_options['style_options']['data_source'] = array(
    'value' => 'wkt',
    'other_lat' => 'nid',
    'other_lon' => 'nid',
    'wkt' => 'field_ding_library_geocode',
    'other_top' => 'nid',
    'other_right' => 'nid',
    'other_bottom' => 'nid',
    'other_left' => 'nid',
    'name_field' => 'title',
    'description_field' => '#row',
  );
  $handler->display->display_options['defaults']['style_options'] = FALSE;
  $handler->display->display_options['defaults']['row_plugin'] = FALSE;
  $handler->display->display_options['row_plugin'] = 'fields';
  $handler->display->display_options['row_options']['hide_empty'] = 0;
  $handler->display->display_options['row_options']['default_field_elements'] = 0;
  $handler->display->display_options['defaults']['row_options'] = FALSE;
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Field: Content: Nid */
  $handler->display->display_options['fields']['nid']['id'] = 'nid';
  $handler->display->display_options['fields']['nid']['table'] = 'node';
  $handler->display->display_options['fields']['nid']['field'] = 'nid';
  $handler->display->display_options['fields']['nid']['label'] = '';
  $handler->display->display_options['fields']['nid']['exclude'] = TRUE;
  $handler->display->display_options['fields']['nid']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['nid']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['nid']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['nid']['alter']['external'] = 0;
  $handler->display->display_options['fields']['nid']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['nid']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['nid']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['nid']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['nid']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['nid']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['nid']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['nid']['alter']['html'] = 0;
  $handler->display->display_options['fields']['nid']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['nid']['element_default_classes'] = 0;
  $handler->display->display_options['fields']['nid']['hide_empty'] = 0;
  $handler->display->display_options['fields']['nid']['empty_zero'] = 0;
  $handler->display->display_options['fields']['nid']['hide_alter_empty'] = 0;
  $handler->display->display_options['fields']['nid']['link_to_node'] = 0;
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = '';
  $handler->display->display_options['fields']['title']['exclude'] = TRUE;
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
  $handler->display->display_options['fields']['title']['hide_alter_empty'] = 0;
  $handler->display->display_options['fields']['title']['link_to_node'] = 0;
  /* Field: Content: Geocode */
  $handler->display->display_options['fields']['field_ding_library_geocode']['id'] = 'field_ding_library_geocode';
  $handler->display->display_options['fields']['field_ding_library_geocode']['table'] = 'field_data_field_ding_library_geocode';
  $handler->display->display_options['fields']['field_ding_library_geocode']['field'] = 'field_ding_library_geocode';
  $handler->display->display_options['fields']['field_ding_library_geocode']['label'] = '';
  $handler->display->display_options['fields']['field_ding_library_geocode']['exclude'] = TRUE;
  $handler->display->display_options['fields']['field_ding_library_geocode']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['field_ding_library_geocode']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['field_ding_library_geocode']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['field_ding_library_geocode']['alter']['external'] = 0;
  $handler->display->display_options['fields']['field_ding_library_geocode']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['field_ding_library_geocode']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['field_ding_library_geocode']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['field_ding_library_geocode']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['field_ding_library_geocode']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['field_ding_library_geocode']['alter']['more_link'] = 0;
  $handler->display->display_options['fields']['field_ding_library_geocode']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['field_ding_library_geocode']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['field_ding_library_geocode']['alter']['html'] = 0;
  $handler->display->display_options['fields']['field_ding_library_geocode']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_ding_library_geocode']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['field_ding_library_geocode']['hide_empty'] = 0;
  $handler->display->display_options['fields']['field_ding_library_geocode']['empty_zero'] = 0;
  $handler->display->display_options['fields']['field_ding_library_geocode']['hide_alter_empty'] = 1;
  $handler->display->display_options['fields']['field_ding_library_geocode']['click_sort_column'] = 'wkt';
  $handler->display->display_options['fields']['field_ding_library_geocode']['settings'] = array(
    'data' => 'full',
  );
  $handler->display->display_options['fields']['field_ding_library_geocode']['field_api_classes'] = 0;
  /* Field: Content: Addresse */
  $handler->display->display_options['fields']['field_ding_library_addresse']['id'] = 'field_ding_library_addresse';
  $handler->display->display_options['fields']['field_ding_library_addresse']['table'] = 'field_data_field_ding_library_addresse';
  $handler->display->display_options['fields']['field_ding_library_addresse']['field'] = 'field_ding_library_addresse';
  $handler->display->display_options['fields']['field_ding_library_addresse']['label'] = '';
  $handler->display->display_options['fields']['field_ding_library_addresse']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['field_ding_library_addresse']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['field_ding_library_addresse']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['field_ding_library_addresse']['alter']['external'] = 0;
  $handler->display->display_options['fields']['field_ding_library_addresse']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['field_ding_library_addresse']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['field_ding_library_addresse']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['field_ding_library_addresse']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['field_ding_library_addresse']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['field_ding_library_addresse']['alter']['more_link'] = 0;
  $handler->display->display_options['fields']['field_ding_library_addresse']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['field_ding_library_addresse']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['field_ding_library_addresse']['alter']['html'] = 0;
  $handler->display->display_options['fields']['field_ding_library_addresse']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_ding_library_addresse']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['field_ding_library_addresse']['hide_empty'] = 0;
  $handler->display->display_options['fields']['field_ding_library_addresse']['empty_zero'] = 0;
  $handler->display->display_options['fields']['field_ding_library_addresse']['hide_alter_empty'] = 1;
  $handler->display->display_options['fields']['field_ding_library_addresse']['click_sort_column'] = 'country';
  $handler->display->display_options['fields']['field_ding_library_addresse']['settings'] = array(
    'use_widget_handlers' => 1,
    'format_handlers' => array(
      'address' => 'address',
    ),
  );
  $handler->display->display_options['fields']['field_ding_library_addresse']['field_api_classes'] = 0;
  /* Field: Content: Opening hours */
  $handler->display->display_options['fields']['field_ding_library_opening_hours']['id'] = 'field_ding_library_opening_hours';
  $handler->display->display_options['fields']['field_ding_library_opening_hours']['table'] = 'field_data_field_ding_library_opening_hours';
  $handler->display->display_options['fields']['field_ding_library_opening_hours']['field'] = 'field_ding_library_opening_hours';
  $handler->display->display_options['fields']['field_ding_library_opening_hours']['label'] = '';
  $handler->display->display_options['fields']['field_ding_library_opening_hours']['exclude'] = TRUE;
  $handler->display->display_options['fields']['field_ding_library_opening_hours']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['field_ding_library_opening_hours']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['field_ding_library_opening_hours']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['field_ding_library_opening_hours']['alter']['external'] = 0;
  $handler->display->display_options['fields']['field_ding_library_opening_hours']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['field_ding_library_opening_hours']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['field_ding_library_opening_hours']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['field_ding_library_opening_hours']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['field_ding_library_opening_hours']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['field_ding_library_opening_hours']['alter']['more_link'] = 0;
  $handler->display->display_options['fields']['field_ding_library_opening_hours']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['field_ding_library_opening_hours']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['field_ding_library_opening_hours']['alter']['html'] = 0;
  $handler->display->display_options['fields']['field_ding_library_opening_hours']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_ding_library_opening_hours']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['field_ding_library_opening_hours']['hide_empty'] = 0;
  $handler->display->display_options['fields']['field_ding_library_opening_hours']['empty_zero'] = 0;
  $handler->display->display_options['fields']['field_ding_library_opening_hours']['hide_alter_empty'] = 1;
  $handler->display->display_options['fields']['field_ding_library_opening_hours']['field_api_classes'] = 0;
  $translatables['ding_library'] = array(
    t('Master'),
    t('more'),
    t('Apply'),
    t('Gendan'),
    t('Sort by'),
    t('Asc'),
    t('Desc'),
    t('<div class="libraries-content">'),
    t('Address'),
    t('Phone'),
    t('Fax'),
    t('E-mail'),
    t('</div>'),
    t('Opening Hours'),
    t('Libraries list'),
    t('Library panes'),
    t('OpenLayers Data Overlay'),
  );
  $export['ding_library'] = $view;

  return $export;
}
