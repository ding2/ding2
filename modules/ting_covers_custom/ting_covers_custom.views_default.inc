<?php
/**
 * @file
 * ting_covers_custom.views_default.inc
 */

/**
 * Implements hook_views_default_views().
 */
function ting_covers_custom_views_default_views() {
  $export = array();

  $view = new view();
  $view->name = 'ting_covers_custom';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'eck_ting_covers_custom';
  $view->human_name = 'Custom covers';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Custom covers';
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
  $handler->display->display_options['pager']['options']['items_per_page'] = '25';
  $handler->display->display_options['pager']['options']['expose']['items_per_page_label'] = 'Antal elementer';
  $handler->display->display_options['pager']['options']['expose']['items_per_page_options_all_label'] = '- Alle -';
  $handler->display->display_options['pager']['options']['expose']['offset_label'] = 'Forskydning';
  $handler->display->display_options['pager']['options']['tags']['first'] = '« første';
  $handler->display->display_options['pager']['options']['tags']['previous'] = '‹ forrige';
  $handler->display->display_options['pager']['options']['tags']['next'] = 'næste ›';
  $handler->display->display_options['pager']['options']['tags']['last'] = 'sidste »';
  $handler->display->display_options['style_plugin'] = 'table';
  $handler->display->display_options['style_options']['columns'] = array(
    'field_ting_covers_custom_object' => 'field_ting_covers_custom_object',
    'field_ting_covers_custom_image' => 'field_ting_covers_custom_image',
    'name' => 'name',
    'changed' => 'changed',
    'edit_link' => 'edit_link',
    'delete_link' => 'delete_link',
    'nothing' => 'nothing',
  );
  $handler->display->display_options['style_options']['default'] = 'changed';
  $handler->display->display_options['style_options']['info'] = array(
    'field_ting_covers_custom_object' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_ting_covers_custom_image' => array(
      'sortable' => 0,
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
    'edit_link' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'delete_link' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'nothing' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
  );
  $handler->display->display_options['style_options']['sticky'] = TRUE;
  /* Forbindelse: Ting custom cover: Author */
  $handler->display->display_options['relationships']['uid']['id'] = 'uid';
  $handler->display->display_options['relationships']['uid']['table'] = 'eck_ting_covers_custom';
  $handler->display->display_options['relationships']['uid']['field'] = 'uid';
  /* Felt: Ting custom cover: Object */
  $handler->display->display_options['fields']['field_ting_covers_custom_object']['id'] = 'field_ting_covers_custom_object';
  $handler->display->display_options['fields']['field_ting_covers_custom_object']['table'] = 'field_data_field_ting_covers_custom_object';
  $handler->display->display_options['fields']['field_ting_covers_custom_object']['field'] = 'field_ting_covers_custom_object';
  $handler->display->display_options['fields']['field_ting_covers_custom_object']['settings'] = array(
    'view_mode' => 'ting_reference_preview',
  );
  /* Felt: Ting custom cover: Cover image */
  $handler->display->display_options['fields']['field_ting_covers_custom_image']['id'] = 'field_ting_covers_custom_image';
  $handler->display->display_options['fields']['field_ting_covers_custom_image']['table'] = 'field_data_field_ting_covers_custom_image';
  $handler->display->display_options['fields']['field_ting_covers_custom_image']['field'] = 'field_ting_covers_custom_image';
  $handler->display->display_options['fields']['field_ting_covers_custom_image']['label'] = 'Cover';
  $handler->display->display_options['fields']['field_ting_covers_custom_image']['click_sort_column'] = 'fid';
  $handler->display->display_options['fields']['field_ting_covers_custom_image']['settings'] = array(
    'image_style' => 'thumbnail',
    'image_link' => 'file',
  );
  /* Felt: Bruger: Navn */
  $handler->display->display_options['fields']['name']['id'] = 'name';
  $handler->display->display_options['fields']['name']['table'] = 'users';
  $handler->display->display_options['fields']['name']['field'] = 'name';
  $handler->display->display_options['fields']['name']['relationship'] = 'uid';
  $handler->display->display_options['fields']['name']['label'] = 'Bruger';
  /* Felt: Ting custom cover: Changed */
  $handler->display->display_options['fields']['changed']['id'] = 'changed';
  $handler->display->display_options['fields']['changed']['table'] = 'eck_ting_covers_custom';
  $handler->display->display_options['fields']['changed']['field'] = 'changed';
  $handler->display->display_options['fields']['changed']['label'] = 'Ændret';
  $handler->display->display_options['fields']['changed']['date_format'] = 'short';
  $handler->display->display_options['fields']['changed']['second_date_format'] = 'ding_date_only';
  /* Felt: Ting custom cover: Redigér-link */
  $handler->display->display_options['fields']['edit_link']['id'] = 'edit_link';
  $handler->display->display_options['fields']['edit_link']['table'] = 'eck_ting_covers_custom';
  $handler->display->display_options['fields']['edit_link']['field'] = 'edit_link';
  $handler->display->display_options['fields']['edit_link']['label'] = '';
  $handler->display->display_options['fields']['edit_link']['exclude'] = TRUE;
  $handler->display->display_options['fields']['edit_link']['element_label_colon'] = FALSE;
  /* Felt: Ting custom cover: Slet-link */
  $handler->display->display_options['fields']['delete_link']['id'] = 'delete_link';
  $handler->display->display_options['fields']['delete_link']['table'] = 'eck_ting_covers_custom';
  $handler->display->display_options['fields']['delete_link']['field'] = 'delete_link';
  $handler->display->display_options['fields']['delete_link']['label'] = '';
  $handler->display->display_options['fields']['delete_link']['exclude'] = TRUE;
  $handler->display->display_options['fields']['delete_link']['element_label_colon'] = FALSE;
  /* Felt: Global: Tilpasset tekst */
  $handler->display->display_options['fields']['nothing']['id'] = 'nothing';
  $handler->display->display_options['fields']['nothing']['table'] = 'views';
  $handler->display->display_options['fields']['nothing']['field'] = 'nothing';
  $handler->display->display_options['fields']['nothing']['label'] = 'Handlinger';
  $handler->display->display_options['fields']['nothing']['alter']['text'] = '[edit_link] [delete_link]';
  /* Filterkriterie: Ting custom cover: ting_covers_custom type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'eck_ting_covers_custom';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'cover' => 'cover',
  );

  /* Display: Admin list */
  $handler = $view->new_display('page', 'Admin list', 'page');
  $handler->display->display_options['path'] = 'admin/config/ting/covers/custom';
  $translatables['ting_covers_custom'] = array(
    t('Master'),
    t('Custom covers'),
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
    t('Bruger'),
    t('Object'),
    t('Cover'),
    t('Ændret'),
    t('Handlinger'),
    t('[edit_link] [delete_link]'),
    t('Admin list'),
  );
  $export['ting_covers_custom'] = $view;

  return $export;
}
