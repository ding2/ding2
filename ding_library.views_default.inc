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

  $view = new view();
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
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['use_more_text'] = 'mere';
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['query']['options']['query_comment'] = FALSE;
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['exposed_form']['options']['submit_button'] = 'Udfør';
  $handler->display->display_options['exposed_form']['options']['reset_button_label'] = 'Gendan';
  $handler->display->display_options['exposed_form']['options']['exposed_sorts_label'] = 'Sortér efter';
  $handler->display->display_options['exposed_form']['options']['sort_asc_label'] = 'Stigende';
  $handler->display->display_options['exposed_form']['options']['sort_desc_label'] = 'Faldende';
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
  $handler->display->display_options['fields']['nid']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['nid']['element_default_classes'] = FALSE;
  $handler->display->display_options['fields']['nid']['hide_alter_empty'] = FALSE;
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = '';
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['title']['alter']['ellipsis'] = FALSE;
  $handler->display->display_options['fields']['title']['element_type'] = 'h2';
  $handler->display->display_options['fields']['title']['element_class'] = 'libraries-title org';
  $handler->display->display_options['fields']['title']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['title']['element_wrapper_type'] = '0';
  $handler->display->display_options['fields']['title']['element_default_classes'] = FALSE;
  $handler->display->display_options['fields']['title']['hide_alter_empty'] = FALSE;
  /* Field: List image */
  $handler->display->display_options['fields']['field_ding_library_list_image']['id'] = 'field_ding_library_list_image';
  $handler->display->display_options['fields']['field_ding_library_list_image']['table'] = 'field_data_field_ding_library_list_image';
  $handler->display->display_options['fields']['field_ding_library_list_image']['field'] = 'field_ding_library_list_image';
  $handler->display->display_options['fields']['field_ding_library_list_image']['ui_name'] = 'List image';
  $handler->display->display_options['fields']['field_ding_library_list_image']['label'] = '';
  $handler->display->display_options['fields']['field_ding_library_list_image']['element_class'] = 'photo';
  $handler->display->display_options['fields']['field_ding_library_list_image']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_ding_library_list_image']['element_wrapper_type'] = '0';
  $handler->display->display_options['fields']['field_ding_library_list_image']['element_default_classes'] = FALSE;
  $handler->display->display_options['fields']['field_ding_library_list_image']['click_sort_column'] = 'fid';
  $handler->display->display_options['fields']['field_ding_library_list_image']['settings'] = array(
    'image_style' => '',
    'image_link' => 'content',
  );
  /* Field: Content: Address */
  $handler->display->display_options['fields']['field_ding_library_addresse']['id'] = 'field_ding_library_addresse';
  $handler->display->display_options['fields']['field_ding_library_addresse']['table'] = 'field_data_field_ding_library_addresse';
  $handler->display->display_options['fields']['field_ding_library_addresse']['field'] = 'field_ding_library_addresse';
  $handler->display->display_options['fields']['field_ding_library_addresse']['label'] = 'Adresse';
  $handler->display->display_options['fields']['field_ding_library_addresse']['element_type'] = 'div';
  $handler->display->display_options['fields']['field_ding_library_addresse']['element_class'] = 'dd adr address';
  $handler->display->display_options['fields']['field_ding_library_addresse']['element_label_type'] = 'div';
  $handler->display->display_options['fields']['field_ding_library_addresse']['element_label_class'] = 'dt adr-label';
  $handler->display->display_options['fields']['field_ding_library_addresse']['element_wrapper_class'] = 'dl address-content';
  $handler->display->display_options['fields']['field_ding_library_addresse']['element_default_classes'] = FALSE;
  $handler->display->display_options['fields']['field_ding_library_addresse']['hide_empty'] = TRUE;
  $handler->display->display_options['fields']['field_ding_library_addresse']['click_sort_column'] = 'country';
  $handler->display->display_options['fields']['field_ding_library_addresse']['settings'] = array(
    'use_widget_handlers' => 1,
    'format_handlers' => array(
      'address' => 'address',
    ),
  );
  /* Field: Content: Phone number */
  $handler->display->display_options['fields']['field_ding_library_phone_number']['id'] = 'field_ding_library_phone_number';
  $handler->display->display_options['fields']['field_ding_library_phone_number']['table'] = 'field_data_field_ding_library_phone_number';
  $handler->display->display_options['fields']['field_ding_library_phone_number']['field'] = 'field_ding_library_phone_number';
  $handler->display->display_options['fields']['field_ding_library_phone_number']['label'] = 'Phone';
  $handler->display->display_options['fields']['field_ding_library_phone_number']['element_type'] = 'div';
  $handler->display->display_options['fields']['field_ding_library_phone_number']['element_class'] = 'dd phone tel';
  $handler->display->display_options['fields']['field_ding_library_phone_number']['element_label_type'] = 'div';
  $handler->display->display_options['fields']['field_ding_library_phone_number']['element_label_class'] = 'dt tel-label';
  $handler->display->display_options['fields']['field_ding_library_phone_number']['element_wrapper_class'] = 'dl phone-content';
  $handler->display->display_options['fields']['field_ding_library_phone_number']['element_default_classes'] = FALSE;
  $handler->display->display_options['fields']['field_ding_library_phone_number']['hide_empty'] = TRUE;
  /* Field: Content: Fax number */
  $handler->display->display_options['fields']['field_ding_library_fax_number']['id'] = 'field_ding_library_fax_number';
  $handler->display->display_options['fields']['field_ding_library_fax_number']['table'] = 'field_data_field_ding_library_fax_number';
  $handler->display->display_options['fields']['field_ding_library_fax_number']['field'] = 'field_ding_library_fax_number';
  $handler->display->display_options['fields']['field_ding_library_fax_number']['label'] = 'Fax';
  $handler->display->display_options['fields']['field_ding_library_fax_number']['element_type'] = 'div';
  $handler->display->display_options['fields']['field_ding_library_fax_number']['element_class'] = 'dd fax';
  $handler->display->display_options['fields']['field_ding_library_fax_number']['element_label_type'] = 'div';
  $handler->display->display_options['fields']['field_ding_library_fax_number']['element_label_class'] = 'dt fax-label';
  $handler->display->display_options['fields']['field_ding_library_fax_number']['element_wrapper_class'] = 'dl fax-content';
  $handler->display->display_options['fields']['field_ding_library_fax_number']['element_default_classes'] = FALSE;
  $handler->display->display_options['fields']['field_ding_library_fax_number']['hide_empty'] = TRUE;
  /* Field: Content: E-mail */
  $handler->display->display_options['fields']['field_ding_library_mail']['id'] = 'field_ding_library_mail';
  $handler->display->display_options['fields']['field_ding_library_mail']['table'] = 'field_data_field_ding_library_mail';
  $handler->display->display_options['fields']['field_ding_library_mail']['field'] = 'field_ding_library_mail';
  $handler->display->display_options['fields']['field_ding_library_mail']['element_type'] = 'div';
  $handler->display->display_options['fields']['field_ding_library_mail']['element_class'] = 'dd email';
  $handler->display->display_options['fields']['field_ding_library_mail']['element_label_type'] = 'div';
  $handler->display->display_options['fields']['field_ding_library_mail']['element_label_class'] = 'dt email-label';
  $handler->display->display_options['fields']['field_ding_library_mail']['element_wrapper_class'] = 'dl email-content';
  $handler->display->display_options['fields']['field_ding_library_mail']['element_default_classes'] = FALSE;
  $handler->display->display_options['fields']['field_ding_library_mail']['hide_empty'] = TRUE;
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title_1']['id'] = 'title_1';
  $handler->display->display_options['fields']['title_1']['table'] = 'node';
  $handler->display->display_options['fields']['title_1']['field'] = 'title';
  $handler->display->display_options['fields']['title_1']['label'] = '';
  $handler->display->display_options['fields']['title_1']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['title_1']['alter']['text'] = '<i class="icon-chevron-right"></i> [title_1]';
  $handler->display->display_options['fields']['title_1']['alter']['make_link'] = TRUE;
  $handler->display->display_options['fields']['title_1']['alter']['path'] = '[title_1]';
  $handler->display->display_options['fields']['title_1']['element_type'] = 'p';
  $handler->display->display_options['fields']['title_1']['element_class'] = 'library-link';
  $handler->display->display_options['fields']['title_1']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['title_1']['element_wrapper_type'] = '0';
  $handler->display->display_options['fields']['title_1']['element_default_classes'] = FALSE;
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

  /* Display: Libraries list */
  $handler = $view->new_display('panel_pane', 'Libraries list', 'ding_library_libraries_list');
  $handler->display->display_options['defaults']['style_plugin'] = FALSE;
  $handler->display->display_options['style_plugin'] = 'list';
  $handler->display->display_options['style_options']['row_class'] = 'js-library-opening-hours-target';
  $handler->display->display_options['style_options']['class'] = 'library-list';
  $handler->display->display_options['style_options']['wrapper_class'] = '';
  $handler->display->display_options['defaults']['style_options'] = FALSE;
  $handler->display->display_options['defaults']['row_plugin'] = FALSE;
  $handler->display->display_options['row_plugin'] = 'node';
  $handler->display->display_options['defaults']['row_options'] = FALSE;
  $handler->display->display_options['defaults']['relationships'] = FALSE;
  /* Relationship: Nodequeue: Queue */
  $handler->display->display_options['relationships']['nodequeue_rel']['id'] = 'nodequeue_rel';
  $handler->display->display_options['relationships']['nodequeue_rel']['table'] = 'node';
  $handler->display->display_options['relationships']['nodequeue_rel']['field'] = 'nodequeue_rel';
  $handler->display->display_options['relationships']['nodequeue_rel']['limit'] = 1;
  $handler->display->display_options['relationships']['nodequeue_rel']['names'] = array(
    'ding_library_listing' => 'ding_library_listing',
    'ding_groups_listning' => 0,
    'ding_tabroll_frontpage' => 0,
  );
  $handler->display->display_options['defaults']['sorts'] = FALSE;
  /* Sort criterion: Nodequeue: Position */
  $handler->display->display_options['sorts']['position']['id'] = 'position';
  $handler->display->display_options['sorts']['position']['table'] = 'nodequeue_nodes';
  $handler->display->display_options['sorts']['position']['field'] = 'position';
  $handler->display->display_options['sorts']['position']['relationship'] = 'nodequeue_rel';
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

  /* Display: Leaflet Pane */
  $handler = $view->new_display('panel_pane', 'Leaflet Pane', 'ding_library_leaflet');
  $handler->display->display_options['defaults']['style_plugin'] = FALSE;
  $handler->display->display_options['style_plugin'] = 'leaflet';
  $handler->display->display_options['style_options']['data_source'] = 'field_ding_library_geocode';
  $handler->display->display_options['style_options']['name_field'] = 'title';
  $handler->display->display_options['style_options']['description_field'] = 'field_ding_library_addresse';
  $handler->display->display_options['style_options']['view_mode'] = 'teaser';
  $handler->display->display_options['style_options']['map'] = 'OSM Mapnik';
  $handler->display->display_options['style_options']['height'] = '275';
  $handler->display->display_options['style_options']['zoom']['initialZoom'] = '-1';
  $handler->display->display_options['style_options']['zoom']['minZoom'] = '0';
  $handler->display->display_options['style_options']['zoom']['maxZoom'] = '18';
  $handler->display->display_options['style_options']['vector_display']['stroke'] = 0;
  $handler->display->display_options['style_options']['vector_display']['fill'] = 0;
  $handler->display->display_options['style_options']['vector_display']['clickable'] = 0;
  $handler->display->display_options['defaults']['style_options'] = FALSE;
  $handler->display->display_options['defaults']['row_plugin'] = FALSE;
  $handler->display->display_options['defaults']['row_options'] = FALSE;
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Field: Content: Body */
  $handler->display->display_options['fields']['field_ding_library_body']['id'] = 'field_ding_library_body';
  $handler->display->display_options['fields']['field_ding_library_body']['table'] = 'field_data_field_ding_library_body';
  $handler->display->display_options['fields']['field_ding_library_body']['field'] = 'field_ding_library_body';
  $handler->display->display_options['fields']['field_ding_library_body']['label'] = '';
  $handler->display->display_options['fields']['field_ding_library_body']['element_label_colon'] = FALSE;
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = '';
  $handler->display->display_options['fields']['title']['element_label_colon'] = FALSE;
  /* Field: Content: Address */
  $handler->display->display_options['fields']['field_ding_library_addresse']['id'] = 'field_ding_library_addresse';
  $handler->display->display_options['fields']['field_ding_library_addresse']['table'] = 'field_data_field_ding_library_addresse';
  $handler->display->display_options['fields']['field_ding_library_addresse']['field'] = 'field_ding_library_addresse';
  $handler->display->display_options['fields']['field_ding_library_addresse']['label'] = '';
  $handler->display->display_options['fields']['field_ding_library_addresse']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['field_ding_library_addresse']['alter']['text'] = '[title]
[field_ding_library_addresse]';
  $handler->display->display_options['fields']['field_ding_library_addresse']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_ding_library_addresse']['click_sort_column'] = 'country';
  $handler->display->display_options['fields']['field_ding_library_addresse']['settings'] = array(
    'use_widget_handlers' => 1,
    'format_handlers' => array(
      'address' => 'address',
    ),
  );
  /* Field: Content: Geocode */
  $handler->display->display_options['fields']['field_ding_library_geocode']['id'] = 'field_ding_library_geocode';
  $handler->display->display_options['fields']['field_ding_library_geocode']['table'] = 'field_data_field_ding_library_geocode';
  $handler->display->display_options['fields']['field_ding_library_geocode']['field'] = 'field_ding_library_geocode';
  $handler->display->display_options['fields']['field_ding_library_geocode']['click_sort_column'] = 'geom';
  $handler->display->display_options['fields']['field_ding_library_geocode']['type'] = 'geofield_leaflet';
  $handler->display->display_options['fields']['field_ding_library_geocode']['settings'] = array(
    'leaflet_map' => 'OSM Mapnik',
    'height' => '400',
    'popup' => array(
      'show' => 0,
      'text' => '',
    ),
    'zoom' => array(
      'initialZoom' => '-1',
      'minZoom' => '1',
      'maxZoom' => '-1',
    ),
    'icon' => array(
      'iconType' => 'marker',
      'iconUrl' => '',
      'shadowUrl' => '',
      'html' => '',
      'iconImageStyle' => 'ding_campaign_w_180',
      'htmlClass' => '',
      'iconSize' => array(
        'x' => '',
        'y' => '',
      ),
      'iconAnchor' => array(
        'x' => '',
        'y' => '',
      ),
      'shadowAnchor' => array(
        'x' => '',
        'y' => '',
      ),
      'popupAnchor' => array(
        'x' => '',
        'y' => '',
      ),
    ),
    'vector_display' => array(
      'stroke_override' => 0,
      'stroke' => 1,
      'color' => '',
      'weight' => '',
      'opacity' => '',
      'dashArray' => '',
      'fill' => 1,
      'fillColor' => '',
      'fillOpacity' => '',
      'clickable' => 1,
    ),
  );
  $handler->display->display_options['pane_category']['name'] = 'Library panes';
  $handler->display->display_options['pane_category']['weight'] = '0';
  $translatables['ding_library'] = array(
    t('Master'),
    t('mere'),
    t('Udfør'),
    t('Gendan'),
    t('Sortér efter'),
    t('Stigende'),
    t('Faldende'),
    t('Adresse'),
    t('Phone'),
    t('Fax'),
    t('E-mail'),
    t('<i class="icon-chevron-right"></i> [title_1]'),
    t('Libraries list'),
    t('more'),
    t('queue'),
    t('Library panes'),
    t('Leaflet Pane'),
    t('[title]
[field_ding_library_addresse]'),
    t('Geocode'),
  );
  $export['ding_library'] = $view;

  return $export;
}
