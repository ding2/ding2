<?php
/**
 * @file
 * smart_search_string.views_default.inc
 */

/**
 * Implements hook_views_default_views().
 */
function smart_search_string_views_default_views() {
  $export = array();

  $view = new view();
  $view->name = 'smart_search_strings';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'eck_ting_type';
  $view->human_name = 'Smart search strings';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Smart search strings';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['use_more_text'] = 'mere';
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['access']['perm'] = 'configure smart search';
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
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['pager']['options']['id'] = '0';
  $handler->display->display_options['pager']['options']['quantity'] = '9';
  $handler->display->display_options['pager']['options']['expose']['items_per_page_label'] = 'Antal elementer';
  $handler->display->display_options['pager']['options']['expose']['items_per_page_options_all_label'] = '- Alle -';
  $handler->display->display_options['pager']['options']['expose']['offset_label'] = 'Forskydning';
  $handler->display->display_options['pager']['options']['tags']['first'] = '« første';
  $handler->display->display_options['pager']['options']['tags']['previous'] = '‹ forrige';
  $handler->display->display_options['pager']['options']['tags']['next'] = 'næste ›';
  $handler->display->display_options['pager']['options']['tags']['last'] = 'sidste »';
  $handler->display->display_options['style_plugin'] = 'table';
  $handler->display->display_options['style_options']['columns'] = array(
    'counter' => 'counter',
    'views_bulk_operations' => 'views_bulk_operations',
    'title' => 'title',
    'field_alternate_search_string' => 'field_alternate_search_string',
    'field_sss_boost_materials' => 'field_sss_boost_materials',
    'field_custom_boost_values' => 'field_custom_boost_values',
    'field_content_reference' => 'field_content_reference',
    'field_sss_sort' => 'field_sss_sort',
    'field_sss_hits_per_year' => 'field_sss_hits_per_year',
    'field_sss_hits_per_month' => 'field_sss_hits_per_month',
    'created' => 'created',
    'changed' => 'changed',
    'field_status' => 'field_status',
    'edit_link' => 'edit_link',
    'delete_link' => 'delete_link',
  );
  $handler->display->display_options['style_options']['default'] = 'field_sss_hits_per_year';
  $handler->display->display_options['style_options']['info'] = array(
    'counter' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'views_bulk_operations' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'title' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_alternate_search_string' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 1,
    ),
    'field_sss_boost_materials' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 1,
    ),
    'field_custom_boost_values' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 1,
    ),
    'field_content_reference' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 1,
    ),
    'field_sss_sort' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 1,
    ),
    'field_sss_hits_per_year' => array(
      'sortable' => 1,
      'default_sort_order' => 'desc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_sss_hits_per_month' => array(
      'sortable' => 1,
      'default_sort_order' => 'desc',
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
    'changed' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_status' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
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
  );
  /* Felt: Global: View resultattæller */
  $handler->display->display_options['fields']['counter']['id'] = 'counter';
  $handler->display->display_options['fields']['counter']['table'] = 'views';
  $handler->display->display_options['fields']['counter']['field'] = 'counter';
  $handler->display->display_options['fields']['counter']['label'] = '#';
  $handler->display->display_options['fields']['counter']['counter_start'] = '1';
  $handler->display->display_options['fields']['counter']['reverse'] = 0;
  /* Felt: Masse-handlinger: Ting_type */
  $handler->display->display_options['fields']['views_bulk_operations']['id'] = 'views_bulk_operations';
  $handler->display->display_options['fields']['views_bulk_operations']['table'] = 'eck_ting_type';
  $handler->display->display_options['fields']['views_bulk_operations']['field'] = 'views_bulk_operations';
  $handler->display->display_options['fields']['views_bulk_operations']['vbo_settings']['display_type'] = '0';
  $handler->display->display_options['fields']['views_bulk_operations']['vbo_settings']['enable_select_all_pages'] = 1;
  $handler->display->display_options['fields']['views_bulk_operations']['vbo_settings']['row_clickable'] = 1;
  $handler->display->display_options['fields']['views_bulk_operations']['vbo_settings']['force_single'] = 0;
  $handler->display->display_options['fields']['views_bulk_operations']['vbo_settings']['entity_load_capacity'] = '10';
  $handler->display->display_options['fields']['views_bulk_operations']['vbo_operations'] = array(
    'action::views_bulk_operations_modify_action' => array(
      'selected' => 1,
      'postpone_processing' => 0,
      'skip_confirmation' => 0,
      'override_label' => 0,
      'label' => '',
      'settings' => array(
        'show_all_tokens' => 1,
        'display_values' => array(
          'smart_search_string::field_status' => 'smart_search_string::field_status',
          'smart_search_string::field_alternate_search_string' => 'smart_search_string::field_alternate_search_string',
        ),
      ),
    ),
    'action::views_bulk_operations_delete_item' => array(
      'selected' => 1,
      'postpone_processing' => 0,
      'skip_confirmation' => 0,
      'override_label' => 0,
      'label' => '',
    ),
  );
  /* Felt: Ting_type: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'eck_ting_type';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = 'Søgestreng';
  $handler->display->display_options['fields']['title']['alter']['make_link'] = TRUE;
  $handler->display->display_options['fields']['title']['alter']['path'] = 'search/ting/[title]';
  $handler->display->display_options['fields']['title']['alter']['target'] = '_blank';
  /* Felt: ting_type: Alternative search string */
  $handler->display->display_options['fields']['field_alternate_search_string']['id'] = 'field_alternate_search_string';
  $handler->display->display_options['fields']['field_alternate_search_string']['table'] = 'field_data_field_alternate_search_string';
  $handler->display->display_options['fields']['field_alternate_search_string']['field'] = 'field_alternate_search_string';
  $handler->display->display_options['fields']['field_alternate_search_string']['label'] = 'Alternate search string';
  /* Felt: ting_type: Promoted materials */
  $handler->display->display_options['fields']['field_sss_boost_materials']['id'] = 'field_sss_boost_materials';
  $handler->display->display_options['fields']['field_sss_boost_materials']['table'] = 'field_data_field_sss_boost_materials';
  $handler->display->display_options['fields']['field_sss_boost_materials']['field'] = 'field_sss_boost_materials';
  $handler->display->display_options['fields']['field_sss_boost_materials']['delta_offset'] = '0';
  /* Felt: Handler mangler eller er i stykker */
  $handler->display->display_options['fields']['field_custom_boost_values']['id'] = 'field_custom_boost_values';
  $handler->display->display_options['fields']['field_custom_boost_values']['table'] = 'field_data_field_custom_boost_values';
  $handler->display->display_options['fields']['field_custom_boost_values']['field'] = 'field_custom_boost_values';
  /* Felt: Handler mangler eller er i stykker */
  $handler->display->display_options['fields']['field_content_reference']['id'] = 'field_content_reference';
  $handler->display->display_options['fields']['field_content_reference']['table'] = 'field_data_field_content_reference';
  $handler->display->display_options['fields']['field_content_reference']['field'] = 'field_content_reference';
  /* Felt: ting_type: Sort */
  $handler->display->display_options['fields']['field_sss_sort']['id'] = 'field_sss_sort';
  $handler->display->display_options['fields']['field_sss_sort']['table'] = 'field_data_field_sss_sort';
  $handler->display->display_options['fields']['field_sss_sort']['field'] = 'field_sss_sort';
  $handler->display->display_options['fields']['field_sss_sort']['label'] = 'Sortér';
  /* Felt: ting_type: Searches - year */
  $handler->display->display_options['fields']['field_sss_hits_per_year']['id'] = 'field_sss_hits_per_year';
  $handler->display->display_options['fields']['field_sss_hits_per_year']['table'] = 'field_data_field_sss_hits_per_year';
  $handler->display->display_options['fields']['field_sss_hits_per_year']['field'] = 'field_sss_hits_per_year';
  $handler->display->display_options['fields']['field_sss_hits_per_year']['label'] = 'Hits - år';
  $handler->display->display_options['fields']['field_sss_hits_per_year']['settings'] = array(
    'thousand_separator' => '',
    'prefix_suffix' => 1,
  );
  /* Felt: ting_type: Searches - 30 days */
  $handler->display->display_options['fields']['field_sss_hits_per_month']['id'] = 'field_sss_hits_per_month';
  $handler->display->display_options['fields']['field_sss_hits_per_month']['table'] = 'field_data_field_sss_hits_per_month';
  $handler->display->display_options['fields']['field_sss_hits_per_month']['field'] = 'field_sss_hits_per_month';
  $handler->display->display_options['fields']['field_sss_hits_per_month']['label'] = 'Hits - 30 dage';
  $handler->display->display_options['fields']['field_sss_hits_per_month']['settings'] = array(
    'thousand_separator' => '',
    'prefix_suffix' => 1,
  );
  /* Felt: Ting_type: Created */
  $handler->display->display_options['fields']['created']['id'] = 'created';
  $handler->display->display_options['fields']['created']['table'] = 'eck_ting_type';
  $handler->display->display_options['fields']['created']['field'] = 'created';
  $handler->display->display_options['fields']['created']['label'] = 'Oprettet';
  $handler->display->display_options['fields']['created']['date_format'] = 'ding_date_only';
  $handler->display->display_options['fields']['created']['second_date_format'] = 'ding_date_only';
  /* Felt: Ting_type: Changed */
  $handler->display->display_options['fields']['changed']['id'] = 'changed';
  $handler->display->display_options['fields']['changed']['table'] = 'eck_ting_type';
  $handler->display->display_options['fields']['changed']['field'] = 'changed';
  $handler->display->display_options['fields']['changed']['label'] = 'Ændret';
  $handler->display->display_options['fields']['changed']['date_format'] = 'ding_date_only';
  $handler->display->display_options['fields']['changed']['second_date_format'] = 'ding_date_only';
  /* Felt: ting_type: Status */
  $handler->display->display_options['fields']['field_status']['id'] = 'field_status';
  $handler->display->display_options['fields']['field_status']['table'] = 'field_data_field_status';
  $handler->display->display_options['fields']['field_status']['field'] = 'field_status';
  /* Felt: Ting_type: Redigér-link */
  $handler->display->display_options['fields']['edit_link']['id'] = 'edit_link';
  $handler->display->display_options['fields']['edit_link']['table'] = 'eck_ting_type';
  $handler->display->display_options['fields']['edit_link']['field'] = 'edit_link';
  /* Felt: Ting_type: Slet-link */
  $handler->display->display_options['fields']['delete_link']['id'] = 'delete_link';
  $handler->display->display_options['fields']['delete_link']['table'] = 'eck_ting_type';
  $handler->display->display_options['fields']['delete_link']['field'] = 'delete_link';
  /* Filterkriterie: Ting_type: ting_type type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'eck_ting_type';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'smart_search_string' => 'smart_search_string',
  );
  /* Filterkriterie: Ting_type: Title */
  $handler->display->display_options['filters']['title']['id'] = 'title';
  $handler->display->display_options['filters']['title']['table'] = 'eck_ting_type';
  $handler->display->display_options['filters']['title']['field'] = 'title';
  $handler->display->display_options['filters']['title']['operator'] = 'contains';
  $handler->display->display_options['filters']['title']['exposed'] = TRUE;
  $handler->display->display_options['filters']['title']['expose']['operator_id'] = 'title_op';
  $handler->display->display_options['filters']['title']['expose']['label'] = 'Filtrér på søgestreng';
  $handler->display->display_options['filters']['title']['expose']['operator'] = 'title_op';
  $handler->display->display_options['filters']['title']['expose']['identifier'] = 'title';
  $handler->display->display_options['filters']['title']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
    4 => 0,
    5 => 0,
    6 => 0,
    7 => 0,
    8 => 0,
    9 => 0,
    10 => 0,
  );
  /* Filterkriterie: ting_type: Status (field_status) */
  $handler->display->display_options['filters']['field_status_value']['id'] = 'field_status_value';
  $handler->display->display_options['filters']['field_status_value']['table'] = 'field_data_field_status';
  $handler->display->display_options['filters']['field_status_value']['field'] = 'field_status_value';
  $handler->display->display_options['filters']['field_status_value']['exposed'] = TRUE;
  $handler->display->display_options['filters']['field_status_value']['expose']['operator_id'] = 'field_status_value_op';
  $handler->display->display_options['filters']['field_status_value']['expose']['label'] = 'Status';
  $handler->display->display_options['filters']['field_status_value']['expose']['operator'] = 'field_status_value_op';
  $handler->display->display_options['filters']['field_status_value']['expose']['identifier'] = 'field_status_value';
  $handler->display->display_options['filters']['field_status_value']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
    4 => 0,
    5 => 0,
    6 => 0,
    7 => 0,
    8 => 0,
    9 => 0,
    10 => 0,
  );

  /* Display: Page */
  $handler = $view->new_display('page', 'Page', 'page');
  $handler->display->display_options['path'] = 'admin/structure/entity-type/ting_type/smart_search_string/list';
  $handler->display->display_options['menu']['type'] = 'tab';
  $handler->display->display_options['menu']['title'] = 'Liste';
  $handler->display->display_options['menu']['weight'] = '0';
  $handler->display->display_options['menu']['context'] = 0;
  $handler->display->display_options['menu']['context_only_inline'] = 0;
  $export['smart_search_strings'] = $view;

  return $export;
}
