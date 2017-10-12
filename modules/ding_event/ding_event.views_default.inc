<?php
/**
 * @file
 * ding_event.views_default.inc
 */

/**
 * Implements hook_views_default_views().
 */
function ding_event_views_default_views() {
  $export = array();

  $view = new view();
  $view->name = 'ding_event';
  $view->description = '';
  $view->tag = 'ding_event';
  $view->base_table = 'node';
  $view->human_name = 'Ding event';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['use_more'] = TRUE;
  $handler->display->display_options['use_more_always'] = TRUE;
  $handler->display->display_options['use_more_text'] = 'See all events';
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['exposed_form']['options']['submit_button'] = 'Indsend';
  $handler->display->display_options['exposed_form']['options']['reset_button_label'] = 'Gendan';
  $handler->display->display_options['exposed_form']['options']['exposed_sorts_label'] = 'Sortér efter';
  $handler->display->display_options['exposed_form']['options']['sort_asc_label'] = 'Stigende';
  $handler->display->display_options['exposed_form']['options']['sort_desc_label'] = 'Faldende';
  $handler->display->display_options['pager']['type'] = 'some';
  $handler->display->display_options['pager']['options']['items_per_page'] = '5';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['style_plugin'] = 'default';
  $handler->display->display_options['style_options']['grouping'] = array(
    0 => array(
      'field' => 'field_ding_event_date_1',
      'rendered' => 1,
      'rendered_strip' => 0,
    ),
  );
  $handler->display->display_options['style_options']['uses_fields'] = TRUE;
  $handler->display->display_options['row_plugin'] = 'node';
  $handler->display->display_options['row_options']['links'] = FALSE;
  /* No results behavior: Global: Text area */
  $handler->display->display_options['empty']['area']['id'] = 'area';
  $handler->display->display_options['empty']['area']['table'] = 'views';
  $handler->display->display_options['empty']['area']['field'] = 'area';
  $handler->display->display_options['empty']['area']['label'] = 'Empty text';
  $handler->display->display_options['empty']['area']['empty'] = TRUE;
  $handler->display->display_options['empty']['area']['content'] = 'No events where found.';
  $handler->display->display_options['empty']['area']['format'] = 'ding_wysiwyg';
  /* Relationship: OG membership: OG membership from Node */
  $handler->display->display_options['relationships']['og_membership_rel']['id'] = 'og_membership_rel';
  $handler->display->display_options['relationships']['og_membership_rel']['table'] = 'node';
  $handler->display->display_options['relationships']['og_membership_rel']['field'] = 'og_membership_rel';
  /* Field: Day (excluded) */
  $handler->display->display_options['fields']['field_ding_event_date']['id'] = 'field_ding_event_date';
  $handler->display->display_options['fields']['field_ding_event_date']['table'] = 'field_data_field_ding_event_date';
  $handler->display->display_options['fields']['field_ding_event_date']['field'] = 'field_ding_event_date';
  $handler->display->display_options['fields']['field_ding_event_date']['ui_name'] = 'Day (excluded)';
  $handler->display->display_options['fields']['field_ding_event_date']['label'] = '';
  $handler->display->display_options['fields']['field_ding_event_date']['exclude'] = TRUE;
  $handler->display->display_options['fields']['field_ding_event_date']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_ding_event_date']['element_default_classes'] = FALSE;
  $handler->display->display_options['fields']['field_ding_event_date']['hide_empty'] = TRUE;
  $handler->display->display_options['fields']['field_ding_event_date']['settings'] = array(
    'format_type' => 'day_text_full',
    'fromto' => 'value',
    'multiple_number' => '',
    'multiple_from' => '',
    'multiple_to' => '',
  );
  /* Field: Day of the month (excluded) */
  $handler->display->display_options['fields']['field_ding_event_date_1']['id'] = 'field_ding_event_date_1';
  $handler->display->display_options['fields']['field_ding_event_date_1']['table'] = 'field_data_field_ding_event_date';
  $handler->display->display_options['fields']['field_ding_event_date_1']['field'] = 'field_ding_event_date';
  $handler->display->display_options['fields']['field_ding_event_date_1']['ui_name'] = 'Day of the month (excluded)';
  $handler->display->display_options['fields']['field_ding_event_date_1']['label'] = '';
  $handler->display->display_options['fields']['field_ding_event_date_1']['exclude'] = TRUE;
  $handler->display->display_options['fields']['field_ding_event_date_1']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_ding_event_date_1']['settings'] = array(
    'format_type' => 'day_of_the_month_without_leading_zeros',
    'fromto' => 'value',
    'multiple_number' => '',
    'multiple_from' => '',
    'multiple_to' => '',
  );
  /* Field: Month (excluded) */
  $handler->display->display_options['fields']['field_ding_event_date_2']['id'] = 'field_ding_event_date_2';
  $handler->display->display_options['fields']['field_ding_event_date_2']['table'] = 'field_data_field_ding_event_date';
  $handler->display->display_options['fields']['field_ding_event_date_2']['field'] = 'field_ding_event_date';
  $handler->display->display_options['fields']['field_ding_event_date_2']['ui_name'] = 'Month (excluded)';
  $handler->display->display_options['fields']['field_ding_event_date_2']['label'] = '';
  $handler->display->display_options['fields']['field_ding_event_date_2']['exclude'] = TRUE;
  $handler->display->display_options['fields']['field_ding_event_date_2']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_ding_event_date_2']['settings'] = array(
    'format_type' => 'month_text_full',
    'fromto' => 'both',
    'multiple_number' => '',
    'multiple_from' => '',
    'multiple_to' => '',
  );
  /* Field: Location (excluded) */
  $handler->display->display_options['fields']['field_ding_event_location']['id'] = 'field_ding_event_location';
  $handler->display->display_options['fields']['field_ding_event_location']['table'] = 'field_data_field_ding_event_location';
  $handler->display->display_options['fields']['field_ding_event_location']['field'] = 'field_ding_event_location';
  $handler->display->display_options['fields']['field_ding_event_location']['ui_name'] = 'Location (excluded)';
  $handler->display->display_options['fields']['field_ding_event_location']['label'] = '';
  $handler->display->display_options['fields']['field_ding_event_location']['exclude'] = TRUE;
  $handler->display->display_options['fields']['field_ding_event_location']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_ding_event_location']['click_sort_column'] = 'name_line';
  $handler->display->display_options['fields']['field_ding_event_location']['settings'] = array(
    'use_widget_handlers' => 0,
    'format_handlers' => array(
      'name-oneline' => 'name-oneline',
    ),
  );
  /* Field: Time (excluded) */
  $handler->display->display_options['fields']['field_ding_event_date_3']['id'] = 'field_ding_event_date_3';
  $handler->display->display_options['fields']['field_ding_event_date_3']['table'] = 'field_data_field_ding_event_date';
  $handler->display->display_options['fields']['field_ding_event_date_3']['field'] = 'field_ding_event_date';
  $handler->display->display_options['fields']['field_ding_event_date_3']['ui_name'] = 'Time (excluded)';
  $handler->display->display_options['fields']['field_ding_event_date_3']['label'] = '';
  $handler->display->display_options['fields']['field_ding_event_date_3']['exclude'] = TRUE;
  $handler->display->display_options['fields']['field_ding_event_date_3']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_ding_event_date_3']['settings'] = array(
    'format_type' => 'ding_time_only',
    'fromto' => 'both',
    'multiple_number' => '',
    'multiple_from' => '',
    'multiple_to' => '',
  );
  /* Field: Price (excluded) */
  $handler->display->display_options['fields']['field_ding_event_price']['id'] = 'field_ding_event_price';
  $handler->display->display_options['fields']['field_ding_event_price']['table'] = 'field_data_field_ding_event_price';
  $handler->display->display_options['fields']['field_ding_event_price']['field'] = 'field_ding_event_price';
  $handler->display->display_options['fields']['field_ding_event_price']['ui_name'] = 'Price (excluded)';
  $handler->display->display_options['fields']['field_ding_event_price']['label'] = '';
  $handler->display->display_options['fields']['field_ding_event_price']['exclude'] = TRUE;
  $handler->display->display_options['fields']['field_ding_event_price']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_ding_event_price']['settings'] = array(
    'thousand_separator' => ' ',
    'prefix_suffix' => 1,
  );
  /* Field: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['ui_name'] = 'Title';
  $handler->display->display_options['fields']['title']['label'] = '';
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['title']['alter']['ellipsis'] = FALSE;
  $handler->display->display_options['fields']['title']['element_type'] = 'h3';
  $handler->display->display_options['fields']['title']['element_class'] = 'event-list-title';
  $handler->display->display_options['fields']['title']['element_label_type'] = '0';
  $handler->display->display_options['fields']['title']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['title']['element_wrapper_type'] = '0';
  $handler->display->display_options['fields']['title']['element_default_classes'] = FALSE;
  $handler->display->display_options['fields']['title']['hide_alter_empty'] = FALSE;
  /* Field: Day, date and month */
  $handler->display->display_options['fields']['nothing_1']['id'] = 'nothing_1';
  $handler->display->display_options['fields']['nothing_1']['table'] = 'views';
  $handler->display->display_options['fields']['nothing_1']['field'] = 'nothing';
  $handler->display->display_options['fields']['nothing_1']['ui_name'] = 'Day, date and month';
  $handler->display->display_options['fields']['nothing_1']['label'] = '';
  $handler->display->display_options['fields']['nothing_1']['alter']['text'] = '<div class="event-list-date-wrapper">
  <span class="event-list-day">[field_ding_event_date]</span>
  <div class="event-list-inner-wrapper">
    <span class="event-list-date">[field_ding_event_date_1]</span>
    <span class="event-list-month">[field_ding_event_date_2]</span>
  </div>
</div>';
  $handler->display->display_options['fields']['nothing_1']['element_type'] = '0';
  $handler->display->display_options['fields']['nothing_1']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['nothing_1']['element_wrapper_type'] = '0';
  $handler->display->display_options['fields']['nothing_1']['element_default_classes'] = FALSE;
  /* Field: Location, time and price */
  $handler->display->display_options['fields']['nothing']['id'] = 'nothing';
  $handler->display->display_options['fields']['nothing']['table'] = 'views';
  $handler->display->display_options['fields']['nothing']['field'] = 'nothing';
  $handler->display->display_options['fields']['nothing']['ui_name'] = 'Location, time and price';
  $handler->display->display_options['fields']['nothing']['label'] = '';
  $handler->display->display_options['fields']['nothing']['alter']['text'] = '<div class="event-list-info">
  <span class="event-list-location">[field_ding_event_location]</span>
  <span class="event-list-time">[field_ding_event_date_3]</span>
  <span class="event-list-price">[field_ding_event_price]</span>
</div>';
  $handler->display->display_options['fields']['nothing']['element_type'] = '0';
  $handler->display->display_options['fields']['nothing']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['nothing']['element_wrapper_type'] = '0';
  $handler->display->display_options['fields']['nothing']['element_default_classes'] = FALSE;
  /* Sort criterion: Content: Date -  start date (field_ding_event_date) */
  $handler->display->display_options['sorts']['field_ding_event_date_value']['id'] = 'field_ding_event_date_value';
  $handler->display->display_options['sorts']['field_ding_event_date_value']['table'] = 'field_data_field_ding_event_date';
  $handler->display->display_options['sorts']['field_ding_event_date_value']['field'] = 'field_ding_event_date_value';
  /* Contextual filter: Content: Has taxonomy term ID */
  $handler->display->display_options['arguments']['tid']['id'] = 'tid';
  $handler->display->display_options['arguments']['tid']['table'] = 'taxonomy_index';
  $handler->display->display_options['arguments']['tid']['field'] = 'tid';
  $handler->display->display_options['arguments']['tid']['exception']['title'] = 'Alle';
  $handler->display->display_options['arguments']['tid']['default_argument_type'] = 'raw';
  $handler->display->display_options['arguments']['tid']['default_argument_options']['index'] = '3';
  $handler->display->display_options['arguments']['tid']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['tid']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['tid']['summary_options']['items_per_page'] = '25';
  $handler->display->display_options['arguments']['tid']['validate']['type'] = 'taxonomy_term';
  $handler->display->display_options['arguments']['tid']['validate_options']['vocabularies'] = array(
    'event_category' => 'event_category',
  );
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
    'ding_event' => 'ding_event',
  );
  /* Filter criterion: Date: Date (node) */
  $handler->display->display_options['filters']['date_filter']['id'] = 'date_filter';
  $handler->display->display_options['filters']['date_filter']['table'] = 'node';
  $handler->display->display_options['filters']['date_filter']['field'] = 'date_filter';
  $handler->display->display_options['filters']['date_filter']['operator'] = '>=';
  $handler->display->display_options['filters']['date_filter']['default_date'] = 'now';
  $handler->display->display_options['filters']['date_filter']['date_fields'] = array(
    'field_data_field_ding_event_date.field_ding_event_date_value' => 'field_data_field_ding_event_date.field_ding_event_date_value',
    'field_data_field_ding_event_date.field_ding_event_date_value2' => 'field_data_field_ding_event_date.field_ding_event_date_value2',
  );
  /* Filter criterion: Content: Type */
  $handler->display->display_options['filters']['type_1']['id'] = 'type_1';
  $handler->display->display_options['filters']['type_1']['table'] = 'node';
  $handler->display->display_options['filters']['type_1']['field'] = 'type';
  $handler->display->display_options['filters']['type_1']['relationship'] = 'og_membership_related_node_group';
  $handler->display->display_options['filters']['type_1']['value'] = array(
    'ding_library' => 'ding_library',
  );

  /* Display: Event list */
  $handler = $view->new_display('panel_pane', 'Event list', 'ding_event_list');
  $handler->display->display_options['defaults']['use_more'] = FALSE;
  $handler->display->display_options['defaults']['link_display'] = FALSE;
  $handler->display->display_options['link_display'] = 'custom_url';
  $handler->display->display_options['link_url'] = 'arrangementer';
  $handler->display->display_options['defaults']['exposed_form'] = FALSE;
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['exposed_form']['options']['submit_button'] = 'Search';
  $handler->display->display_options['exposed_form']['options']['reset_button'] = TRUE;
  $handler->display->display_options['exposed_form']['options']['reset_button_label'] = 'Alle arrangementer';
  $handler->display->display_options['exposed_form']['options']['exposed_sorts_label'] = 'Sortér efter';
  $handler->display->display_options['exposed_form']['options']['expose_sort_order'] = FALSE;
  $handler->display->display_options['exposed_form']['options']['sort_asc_label'] = 'Stigende';
  $handler->display->display_options['exposed_form']['options']['sort_desc_label'] = 'Faldende';
  $handler->display->display_options['defaults']['pager'] = FALSE;
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = '10';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['pager']['options']['id'] = '0';
  $handler->display->display_options['pager']['options']['quantity'] = '9';
  $handler->display->display_options['pager']['options']['expose']['items_per_page_label'] = 'Number of elements';
  $handler->display->display_options['pager']['options']['expose']['items_per_page_options_all_label'] = '- Alle -';
  $handler->display->display_options['pager']['options']['expose']['offset_label'] = 'Forskydning';
  $handler->display->display_options['pager']['options']['tags']['first'] = '« First';
  $handler->display->display_options['pager']['options']['tags']['next'] = 'Next ›';
  $handler->display->display_options['pager']['options']['tags']['last'] = 'Last »';
  $handler->display->display_options['defaults']['style_plugin'] = FALSE;
  $handler->display->display_options['style_plugin'] = 'default';
  $handler->display->display_options['style_options']['grouping'] = array(
    0 => array(
      'field' => 'field_ding_event_date_1',
      'rendered' => 1,
      'rendered_strip' => 0,
    ),
  );
  $handler->display->display_options['style_options']['uses_fields'] = TRUE;
  $handler->display->display_options['defaults']['style_options'] = FALSE;
  $handler->display->display_options['defaults']['row_plugin'] = FALSE;
  $handler->display->display_options['row_plugin'] = 'node';
  $handler->display->display_options['row_options']['links'] = FALSE;
  $handler->display->display_options['defaults']['row_options'] = FALSE;
  $handler->display->display_options['exposed_block'] = TRUE;
  $handler->display->display_options['defaults']['relationships'] = FALSE;
  /* Relationship: OG membership: OG membership from Node */
  $handler->display->display_options['relationships']['og_membership_rel']['id'] = 'og_membership_rel';
  $handler->display->display_options['relationships']['og_membership_rel']['table'] = 'node';
  $handler->display->display_options['relationships']['og_membership_rel']['field'] = 'og_membership_rel';
  /* Relationship: OG membership: Group Node from OG membership */
  $handler->display->display_options['relationships']['og_membership_related_node_group']['id'] = 'og_membership_related_node_group';
  $handler->display->display_options['relationships']['og_membership_related_node_group']['table'] = 'og_membership';
  $handler->display->display_options['relationships']['og_membership_related_node_group']['field'] = 'og_membership_related_node_group';
  $handler->display->display_options['relationships']['og_membership_related_node_group']['relationship'] = 'og_membership_rel';
  $handler->display->display_options['relationships']['og_membership_related_node_group']['label'] = 'OG node group';
  /* Relationship: Content: Category (field_ding_event_category) */
  $handler->display->display_options['relationships']['field_ding_event_category_tid']['id'] = 'field_ding_event_category_tid';
  $handler->display->display_options['relationships']['field_ding_event_category_tid']['table'] = 'field_data_field_ding_event_category';
  $handler->display->display_options['relationships']['field_ding_event_category_tid']['field'] = 'field_ding_event_category_tid';
  /* Relationship: Content: Tags (field_ding_event_tags) */
  $handler->display->display_options['relationships']['field_ding_event_tags_tid']['id'] = 'field_ding_event_tags_tid';
  $handler->display->display_options['relationships']['field_ding_event_tags_tid']['table'] = 'field_data_field_ding_event_tags';
  $handler->display->display_options['relationships']['field_ding_event_tags_tid']['field'] = 'field_ding_event_tags_tid';
  /* Relationship: Content: Target (field_ding_event_target) */
  $handler->display->display_options['relationships']['field_ding_event_target_tid']['id'] = 'field_ding_event_target_tid';
  $handler->display->display_options['relationships']['field_ding_event_target_tid']['table'] = 'field_data_field_ding_event_target';
  $handler->display->display_options['relationships']['field_ding_event_target_tid']['field'] = 'field_ding_event_target_tid';
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Field: Date (for group header) */
  $handler->display->display_options['fields']['field_ding_event_date_1']['id'] = 'field_ding_event_date_1';
  $handler->display->display_options['fields']['field_ding_event_date_1']['table'] = 'field_data_field_ding_event_date';
  $handler->display->display_options['fields']['field_ding_event_date_1']['field'] = 'field_ding_event_date';
  $handler->display->display_options['fields']['field_ding_event_date_1']['ui_name'] = 'Date (for group header)';
  $handler->display->display_options['fields']['field_ding_event_date_1']['label'] = '';
  $handler->display->display_options['fields']['field_ding_event_date_1']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_ding_event_date_1']['element_default_classes'] = FALSE;
  $handler->display->display_options['fields']['field_ding_event_date_1']['settings'] = array(
    'format_type' => 'month_and_year_separator',
    'fromto' => 'value',
    'multiple_number' => '',
    'multiple_from' => '',
    'multiple_to' => '',
  );
  /* Field: Content: Body */
  $handler->display->display_options['fields']['field_ding_event_body']['id'] = 'field_ding_event_body';
  $handler->display->display_options['fields']['field_ding_event_body']['table'] = 'field_data_field_ding_event_body';
  $handler->display->display_options['fields']['field_ding_event_body']['field'] = 'field_ding_event_body';
  $handler->display->display_options['fields']['field_ding_event_body']['label'] = '';
  $handler->display->display_options['fields']['field_ding_event_body']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_ding_event_body']['type'] = 'text_plain';
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = '';
  $handler->display->display_options['fields']['title']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['title']['link_to_node'] = FALSE;
  /* Field: Taxonomy term: Name */
  $handler->display->display_options['fields']['name']['id'] = 'name';
  $handler->display->display_options['fields']['name']['table'] = 'taxonomy_term_data';
  $handler->display->display_options['fields']['name']['field'] = 'name';
  $handler->display->display_options['fields']['name']['relationship'] = 'field_ding_event_category_tid';
  $handler->display->display_options['fields']['name']['label'] = '';
  $handler->display->display_options['fields']['name']['element_label_colon'] = FALSE;
  /* Field: Content: Lead */
  $handler->display->display_options['fields']['field_ding_event_lead']['id'] = 'field_ding_event_lead';
  $handler->display->display_options['fields']['field_ding_event_lead']['table'] = 'field_data_field_ding_event_lead';
  $handler->display->display_options['fields']['field_ding_event_lead']['field'] = 'field_ding_event_lead';
  $handler->display->display_options['fields']['field_ding_event_lead']['label'] = '';
  $handler->display->display_options['fields']['field_ding_event_lead']['element_label_colon'] = FALSE;
  /* Field: Taxonomy term: Name */
  $handler->display->display_options['fields']['name_1']['id'] = 'name_1';
  $handler->display->display_options['fields']['name_1']['table'] = 'taxonomy_term_data';
  $handler->display->display_options['fields']['name_1']['field'] = 'name';
  $handler->display->display_options['fields']['name_1']['relationship'] = 'field_ding_event_tags_tid';
  $handler->display->display_options['fields']['name_1']['label'] = '';
  $handler->display->display_options['fields']['name_1']['element_label_colon'] = FALSE;
  /* Field: Taxonomy term: Name */
  $handler->display->display_options['fields']['name_2']['id'] = 'name_2';
  $handler->display->display_options['fields']['name_2']['table'] = 'taxonomy_term_data';
  $handler->display->display_options['fields']['name_2']['field'] = 'name';
  $handler->display->display_options['fields']['name_2']['relationship'] = 'field_ding_event_target_tid';
  $handler->display->display_options['fields']['name_2']['label'] = '';
  $handler->display->display_options['fields']['name_2']['element_label_colon'] = FALSE;
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title_1']['id'] = 'title_1';
  $handler->display->display_options['fields']['title_1']['table'] = 'node';
  $handler->display->display_options['fields']['title_1']['field'] = 'title';
  $handler->display->display_options['fields']['title_1']['relationship'] = 'og_membership_related_node_group';
  $handler->display->display_options['fields']['title_1']['label'] = '';
  $handler->display->display_options['fields']['title_1']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['title_1']['link_to_node'] = FALSE;
  /* Field: Content: Location - Full name */
  $handler->display->display_options['fields']['field_ding_event_location_name_line']['id'] = 'field_ding_event_location_name_line';
  $handler->display->display_options['fields']['field_ding_event_location_name_line']['table'] = 'field_data_field_ding_event_location';
  $handler->display->display_options['fields']['field_ding_event_location_name_line']['field'] = 'field_ding_event_location_name_line';
  $handler->display->display_options['fields']['field_ding_event_location_name_line']['label'] = '';
  $handler->display->display_options['fields']['field_ding_event_location_name_line']['element_label_colon'] = FALSE;
  $handler->display->display_options['defaults']['arguments'] = FALSE;
  /* Contextual filter: Content: Has taxonomy term ID */
  $handler->display->display_options['arguments']['tid']['id'] = 'tid';
  $handler->display->display_options['arguments']['tid']['table'] = 'taxonomy_index';
  $handler->display->display_options['arguments']['tid']['field'] = 'tid';
  $handler->display->display_options['arguments']['tid']['exception']['title'] = 'Alle';
  $handler->display->display_options['arguments']['tid']['default_argument_type'] = 'taxonomy_tid';
  $handler->display->display_options['arguments']['tid']['default_argument_options']['term_page'] = FALSE;
  $handler->display->display_options['arguments']['tid']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['tid']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['tid']['summary_options']['items_per_page'] = '25';
  $handler->display->display_options['arguments']['tid']['specify_validation'] = TRUE;
  $handler->display->display_options['arguments']['tid']['validate']['type'] = 'taxonomy_term';
  $handler->display->display_options['arguments']['tid']['validate_options']['vocabularies'] = array(
    'event_category' => 'event_category',
  );
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
    'ding_event' => 'ding_event',
  );
  $handler->display->display_options['filters']['type']['group'] = 1;
  /* Filter criterion: Date: Date (node) */
  $handler->display->display_options['filters']['date_filter']['id'] = 'date_filter';
  $handler->display->display_options['filters']['date_filter']['table'] = 'node';
  $handler->display->display_options['filters']['date_filter']['field'] = 'date_filter';
  $handler->display->display_options['filters']['date_filter']['operator'] = '>=';
  $handler->display->display_options['filters']['date_filter']['group'] = 1;
  $handler->display->display_options['filters']['date_filter']['default_date'] = 'now';
  $handler->display->display_options['filters']['date_filter']['date_fields'] = array(
    'field_data_field_ding_event_date.field_ding_event_date_value' => 'field_data_field_ding_event_date.field_ding_event_date_value',
  );
  /* Filter criterion: Content: Type */
  $handler->display->display_options['filters']['type_1']['id'] = 'type_1';
  $handler->display->display_options['filters']['type_1']['table'] = 'node';
  $handler->display->display_options['filters']['type_1']['field'] = 'type';
  $handler->display->display_options['filters']['type_1']['relationship'] = 'og_membership_related_node_group';
  $handler->display->display_options['filters']['type_1']['value'] = array(
    'ding_library' => 'ding_library',
  );
  $handler->display->display_options['filters']['type_1']['group'] = 1;
  /* Filter criterion: Global: Combine fields filter */
  $handler->display->display_options['filters']['combine']['id'] = 'combine';
  $handler->display->display_options['filters']['combine']['table'] = 'views';
  $handler->display->display_options['filters']['combine']['field'] = 'combine';
  $handler->display->display_options['filters']['combine']['operator'] = 'allwords';
  $handler->display->display_options['filters']['combine']['group'] = 1;
  $handler->display->display_options['filters']['combine']['exposed'] = TRUE;
  $handler->display->display_options['filters']['combine']['expose']['operator_id'] = 'combine_op';
  $handler->display->display_options['filters']['combine']['expose']['label'] = 'Search';
  $handler->display->display_options['filters']['combine']['expose']['operator'] = 'combine_op';
  $handler->display->display_options['filters']['combine']['expose']['identifier'] = 'title';
  $handler->display->display_options['filters']['combine']['expose']['remember_roles'] = array(
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
  $handler->display->display_options['filters']['combine']['fields'] = array(
    'field_ding_event_body' => 'field_ding_event_body',
    'title' => 'title',
    'name' => 'name',
    'field_ding_event_lead' => 'field_ding_event_lead',
    'name_1' => 'name_1',
    'name_2' => 'name_2',
    'title_1' => 'title_1',
    'field_ding_event_location_name_line' => 'field_ding_event_location_name_line',
  );
  /* Filter criterion: Content: Date -  start date (field_ding_event_date) */
  $handler->display->display_options['filters']['field_ding_event_date_value']['id'] = 'field_ding_event_date_value';
  $handler->display->display_options['filters']['field_ding_event_date_value']['table'] = 'field_data_field_ding_event_date';
  $handler->display->display_options['filters']['field_ding_event_date_value']['field'] = 'field_ding_event_date_value';
  $handler->display->display_options['filters']['field_ding_event_date_value']['operator'] = '>=';
  $handler->display->display_options['filters']['field_ding_event_date_value']['group'] = 1;
  $handler->display->display_options['filters']['field_ding_event_date_value']['exposed'] = TRUE;
  $handler->display->display_options['filters']['field_ding_event_date_value']['expose']['operator_id'] = 'field_ding_event_date_value_op';
  $handler->display->display_options['filters']['field_ding_event_date_value']['expose']['label'] = 'From';
  $handler->display->display_options['filters']['field_ding_event_date_value']['expose']['operator'] = 'field_ding_event_date_value_op';
  $handler->display->display_options['filters']['field_ding_event_date_value']['expose']['identifier'] = 'date';
  $handler->display->display_options['filters']['field_ding_event_date_value']['expose']['remember_roles'] = array(
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
  $handler->display->display_options['filters']['field_ding_event_date_value']['form_type'] = 'date_popup';
  /* Filter criterion: Content: Date -  start date (field_ding_event_date) */
  $handler->display->display_options['filters']['field_ding_event_date_value_1']['id'] = 'field_ding_event_date_value_1';
  $handler->display->display_options['filters']['field_ding_event_date_value_1']['table'] = 'field_data_field_ding_event_date';
  $handler->display->display_options['filters']['field_ding_event_date_value_1']['field'] = 'field_ding_event_date_value';
  $handler->display->display_options['filters']['field_ding_event_date_value_1']['operator'] = '<=';
  $handler->display->display_options['filters']['field_ding_event_date_value_1']['group'] = 1;
  $handler->display->display_options['filters']['field_ding_event_date_value_1']['exposed'] = TRUE;
  $handler->display->display_options['filters']['field_ding_event_date_value_1']['expose']['operator_id'] = 'field_ding_event_date_value_1_op';
  $handler->display->display_options['filters']['field_ding_event_date_value_1']['expose']['label'] = 'To';
  $handler->display->display_options['filters']['field_ding_event_date_value_1']['expose']['operator'] = 'field_ding_event_date_value_1_op';
  $handler->display->display_options['filters']['field_ding_event_date_value_1']['expose']['identifier'] = 'field_ding_event_date_value_1';
  $handler->display->display_options['filters']['field_ding_event_date_value_1']['expose']['remember_roles'] = array(
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
  $handler->display->display_options['filters']['field_ding_event_date_value_1']['form_type'] = 'date_popup';
  $handler->display->display_options['pane_category']['name'] = 'Event panes';
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
    'tid' => array(
      'type' => 'context',
      'context' => 'entity:taxonomy_term.tid',
      'context_optional' => 0,
      'panel' => '0',
      'fixed' => '%tid',
      'label' => 'Content: Has taxonomy term ID',
    ),
  );

  /* Display: Event list (frontpage) */
  $handler = $view->new_display('panel_pane', 'Event list (frontpage)', 'ding_event_list_frontpage');
  $handler->display->display_options['defaults']['title'] = FALSE;
  $handler->display->display_options['title'] = 'Events';
  $handler->display->display_options['defaults']['use_more'] = FALSE;
  $handler->display->display_options['use_more'] = TRUE;
  $handler->display->display_options['defaults']['link_display'] = FALSE;
  $handler->display->display_options['link_display'] = 'custom_url';
  $handler->display->display_options['link_url'] = 'arrangementer';
  $handler->display->display_options['defaults']['pager'] = FALSE;
  $handler->display->display_options['pager']['type'] = 'some';
  $handler->display->display_options['pager']['options']['items_per_page'] = '6';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['defaults']['style_plugin'] = FALSE;
  $handler->display->display_options['style_plugin'] = 'default';
  $handler->display->display_options['defaults']['style_options'] = FALSE;
  $handler->display->display_options['defaults']['row_plugin'] = FALSE;
  $handler->display->display_options['row_plugin'] = 'node';
  $handler->display->display_options['row_options']['links'] = FALSE;
  $handler->display->display_options['defaults']['row_options'] = FALSE;
  $handler->display->display_options['defaults']['relationships'] = FALSE;
  /* Relationship: OG membership: OG membership from Node */
  $handler->display->display_options['relationships']['og_membership_rel']['id'] = 'og_membership_rel';
  $handler->display->display_options['relationships']['og_membership_rel']['table'] = 'node';
  $handler->display->display_options['relationships']['og_membership_rel']['field'] = 'og_membership_rel';
  /* Relationship: OG membership: Group Node from OG membership */
  $handler->display->display_options['relationships']['og_membership_related_node_group']['id'] = 'og_membership_related_node_group';
  $handler->display->display_options['relationships']['og_membership_related_node_group']['table'] = 'og_membership';
  $handler->display->display_options['relationships']['og_membership_related_node_group']['field'] = 'og_membership_related_node_group';
  $handler->display->display_options['relationships']['og_membership_related_node_group']['relationship'] = 'og_membership_rel';
  $handler->display->display_options['relationships']['og_membership_related_node_group']['label'] = 'OG node group';
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Field: Date (for group header) */
  $handler->display->display_options['fields']['field_ding_event_date_1']['id'] = 'field_ding_event_date_1';
  $handler->display->display_options['fields']['field_ding_event_date_1']['table'] = 'field_data_field_ding_event_date';
  $handler->display->display_options['fields']['field_ding_event_date_1']['field'] = 'field_ding_event_date';
  $handler->display->display_options['fields']['field_ding_event_date_1']['ui_name'] = 'Date (for group header)';
  $handler->display->display_options['fields']['field_ding_event_date_1']['label'] = '';
  $handler->display->display_options['fields']['field_ding_event_date_1']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_ding_event_date_1']['element_default_classes'] = FALSE;
  $handler->display->display_options['fields']['field_ding_event_date_1']['settings'] = array(
    'format_type' => 'month_and_year_separator',
    'fromto' => 'value',
    'multiple_number' => '',
    'multiple_from' => '',
    'multiple_to' => '',
  );
  $handler->display->display_options['defaults']['arguments'] = FALSE;
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
    'ding_event' => 'ding_event',
  );
  $handler->display->display_options['filters']['type']['group'] = 1;
  /* Filter criterion: Content: Promoted to front page */
  $handler->display->display_options['filters']['promote']['id'] = 'promote';
  $handler->display->display_options['filters']['promote']['table'] = 'node';
  $handler->display->display_options['filters']['promote']['field'] = 'promote';
  $handler->display->display_options['filters']['promote']['value'] = '1';
  $handler->display->display_options['filters']['promote']['group'] = 1;
  /* Filter criterion: Date: Date (node) */
  $handler->display->display_options['filters']['date_filter']['id'] = 'date_filter';
  $handler->display->display_options['filters']['date_filter']['table'] = 'node';
  $handler->display->display_options['filters']['date_filter']['field'] = 'date_filter';
  $handler->display->display_options['filters']['date_filter']['operator'] = '>=';
  $handler->display->display_options['filters']['date_filter']['group'] = 1;
  $handler->display->display_options['filters']['date_filter']['default_date'] = 'now';
  $handler->display->display_options['filters']['date_filter']['date_fields'] = array(
    'field_data_field_ding_event_date.field_ding_event_date_value' => 'field_data_field_ding_event_date.field_ding_event_date_value',
  );
  /* Filter criterion: Content: Type */
  $handler->display->display_options['filters']['type_1']['id'] = 'type_1';
  $handler->display->display_options['filters']['type_1']['table'] = 'node';
  $handler->display->display_options['filters']['type_1']['field'] = 'type';
  $handler->display->display_options['filters']['type_1']['relationship'] = 'og_membership_related_node_group';
  $handler->display->display_options['filters']['type_1']['value'] = array(
    'ding_library' => 'ding_library',
  );
  $handler->display->display_options['filters']['type_1']['group'] = 1;
  $handler->display->display_options['pane_category']['name'] = 'Event panes';
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
    'tid' => array(
      'type' => 'context',
      'context' => 'entity:taxonomy_term.tid',
      'context_optional' => 0,
      'panel' => '0',
      'fixed' => '%tid',
      'label' => 'Content: Has taxonomy term ID',
    ),
  );

  /* Display: Library event list */
  $handler = $view->new_display('panel_pane', 'Library event list', 'ding_event_library_list');
  $handler->display->display_options['defaults']['use_more'] = FALSE;
  $handler->display->display_options['use_more'] = TRUE;
  $handler->display->display_options['defaults']['link_display'] = FALSE;
  $handler->display->display_options['link_display'] = 'custom_url';
  $handler->display->display_options['link_url'] = 'arrangementer';
  $handler->display->display_options['defaults']['pager'] = FALSE;
  $handler->display->display_options['pager']['type'] = 'some';
  $handler->display->display_options['pager']['options']['items_per_page'] = '6';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['defaults']['style_plugin'] = FALSE;
  $handler->display->display_options['style_plugin'] = 'default';
  $handler->display->display_options['defaults']['style_options'] = FALSE;
  $handler->display->display_options['defaults']['row_plugin'] = FALSE;
  $handler->display->display_options['row_plugin'] = 'node';
  $handler->display->display_options['row_options']['links'] = FALSE;
  $handler->display->display_options['defaults']['row_options'] = FALSE;
  $handler->display->display_options['defaults']['empty'] = FALSE;
  $handler->display->display_options['defaults']['relationships'] = FALSE;
  /* Relationship: OG membership: OG membership from Node */
  $handler->display->display_options['relationships']['og_membership_rel']['id'] = 'og_membership_rel';
  $handler->display->display_options['relationships']['og_membership_rel']['table'] = 'node';
  $handler->display->display_options['relationships']['og_membership_rel']['field'] = 'og_membership_rel';
  /* Relationship: OG membership: Group Node from OG membership */
  $handler->display->display_options['relationships']['og_membership_related_node_group']['id'] = 'og_membership_related_node_group';
  $handler->display->display_options['relationships']['og_membership_related_node_group']['table'] = 'og_membership';
  $handler->display->display_options['relationships']['og_membership_related_node_group']['field'] = 'og_membership_related_node_group';
  $handler->display->display_options['relationships']['og_membership_related_node_group']['relationship'] = 'og_membership_rel';
  $handler->display->display_options['relationships']['og_membership_related_node_group']['label'] = 'OG node group';
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Field: Date (for group header) */
  $handler->display->display_options['fields']['field_ding_event_date_1']['id'] = 'field_ding_event_date_1';
  $handler->display->display_options['fields']['field_ding_event_date_1']['table'] = 'field_data_field_ding_event_date';
  $handler->display->display_options['fields']['field_ding_event_date_1']['field'] = 'field_ding_event_date';
  $handler->display->display_options['fields']['field_ding_event_date_1']['ui_name'] = 'Date (for group header)';
  $handler->display->display_options['fields']['field_ding_event_date_1']['label'] = '';
  $handler->display->display_options['fields']['field_ding_event_date_1']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_ding_event_date_1']['element_default_classes'] = FALSE;
  $handler->display->display_options['fields']['field_ding_event_date_1']['settings'] = array(
    'format_type' => 'month_and_year_separator',
    'fromto' => 'value',
    'multiple_number' => '',
    'multiple_from' => '',
    'multiple_to' => '',
  );
  $handler->display->display_options['defaults']['arguments'] = FALSE;
  /* Contextual filter: OG membership: Group ID */
  $handler->display->display_options['arguments']['gid']['id'] = 'gid';
  $handler->display->display_options['arguments']['gid']['table'] = 'og_membership';
  $handler->display->display_options['arguments']['gid']['field'] = 'gid';
  $handler->display->display_options['arguments']['gid']['relationship'] = 'og_membership_rel';
  $handler->display->display_options['arguments']['gid']['default_action'] = 'empty';
  $handler->display->display_options['arguments']['gid']['default_argument_type'] = 'fixed';
  $handler->display->display_options['arguments']['gid']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['gid']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['gid']['summary_options']['items_per_page'] = '25';
  $handler->display->display_options['pane_category']['name'] = 'Library panes';
  $handler->display->display_options['pane_category']['weight'] = '0';
  $handler->display->display_options['allow']['use_pager'] = 0;
  $handler->display->display_options['allow']['items_per_page'] = 0;
  $handler->display->display_options['allow']['offset'] = 0;
  $handler->display->display_options['allow']['link_to_view'] = 0;
  $handler->display->display_options['allow']['more_link'] = 0;
  $handler->display->display_options['allow']['path_override'] = 0;
  $handler->display->display_options['allow']['title_override'] = 'title_override';
  $handler->display->display_options['allow']['exposed_form'] = 'exposed_form';
  $handler->display->display_options['allow']['fields_override'] = 0;
  $handler->display->display_options['argument_input'] = array(
    'gid' => array(
      'type' => 'context',
      'context' => 'entity:node.nid',
      'context_optional' => 0,
      'panel' => '0',
      'fixed' => '',
      'label' => 'OG membership: Group ID',
    ),
    'tid' => array(
      'type' => 'context',
      'context' => 'entity:taxonomy_term.tid',
      'context_optional' => 1,
      'panel' => '1',
      'fixed' => '%tid',
      'label' => 'Content: Has taxonomy term ID',
    ),
  );

  /* Display: Event list (library) */
  $handler = $view->new_display('panel_pane', 'Event list (library)', 'ding_event_list_library');
  $handler->display->display_options['defaults']['use_more'] = FALSE;
  $handler->display->display_options['defaults']['link_display'] = FALSE;
  $handler->display->display_options['link_display'] = 'custom_url';
  $handler->display->display_options['link_url'] = 'bibliotek/%1/arrangementer';
  $handler->display->display_options['field_language_add_to_query'] = 0;
  $handler->display->display_options['defaults']['pager'] = FALSE;
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = '10';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['pager']['options']['id'] = '0';
  $handler->display->display_options['pager']['options']['expose']['items_per_page_label'] = 'Number of elements';
  $handler->display->display_options['pager']['options']['expose']['items_per_page_options_all_label'] = '- Alle -';
  $handler->display->display_options['pager']['options']['expose']['offset_label'] = 'Forskydning';
  $handler->display->display_options['pager']['options']['tags']['first'] = '« First';
  $handler->display->display_options['pager']['options']['tags']['next'] = 'Next ›';
  $handler->display->display_options['pager']['options']['tags']['last'] = 'Last »';
  $handler->display->display_options['defaults']['style_plugin'] = FALSE;
  $handler->display->display_options['style_plugin'] = 'default';
  $handler->display->display_options['style_options']['grouping'] = array(
    0 => array(
      'field' => 'field_ding_event_date_1',
      'rendered' => 1,
      'rendered_strip' => 0,
    ),
  );
  $handler->display->display_options['style_options']['uses_fields'] = TRUE;
  $handler->display->display_options['defaults']['style_options'] = FALSE;
  $handler->display->display_options['defaults']['row_plugin'] = FALSE;
  $handler->display->display_options['row_plugin'] = 'node';
  $handler->display->display_options['row_options']['links'] = FALSE;
  $handler->display->display_options['defaults']['row_options'] = FALSE;
  $handler->display->display_options['defaults']['relationships'] = FALSE;
  /* Relationship: OG membership: OG membership from Node */
  $handler->display->display_options['relationships']['og_membership_rel']['id'] = 'og_membership_rel';
  $handler->display->display_options['relationships']['og_membership_rel']['table'] = 'node';
  $handler->display->display_options['relationships']['og_membership_rel']['field'] = 'og_membership_rel';
  /* Relationship: OG membership: Group Node from OG membership */
  $handler->display->display_options['relationships']['og_membership_related_node_group']['id'] = 'og_membership_related_node_group';
  $handler->display->display_options['relationships']['og_membership_related_node_group']['table'] = 'og_membership';
  $handler->display->display_options['relationships']['og_membership_related_node_group']['field'] = 'og_membership_related_node_group';
  $handler->display->display_options['relationships']['og_membership_related_node_group']['relationship'] = 'og_membership_rel';
  $handler->display->display_options['relationships']['og_membership_related_node_group']['label'] = 'OG node group';
  $handler->display->display_options['relationships']['og_membership_related_node_group']['required'] = TRUE;
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Field: Date (for group header) */
  $handler->display->display_options['fields']['field_ding_event_date_1']['id'] = 'field_ding_event_date_1';
  $handler->display->display_options['fields']['field_ding_event_date_1']['table'] = 'field_data_field_ding_event_date';
  $handler->display->display_options['fields']['field_ding_event_date_1']['field'] = 'field_ding_event_date';
  $handler->display->display_options['fields']['field_ding_event_date_1']['ui_name'] = 'Date (for group header)';
  $handler->display->display_options['fields']['field_ding_event_date_1']['label'] = '';
  $handler->display->display_options['fields']['field_ding_event_date_1']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_ding_event_date_1']['element_default_classes'] = FALSE;
  $handler->display->display_options['fields']['field_ding_event_date_1']['settings'] = array(
    'format_type' => 'month_and_year_separator',
    'fromto' => 'value',
    'multiple_number' => '',
    'multiple_from' => '',
    'multiple_to' => '',
  );
  $handler->display->display_options['defaults']['arguments'] = FALSE;
  /* Contextual filter: OG membership: Group ID */
  $handler->display->display_options['arguments']['gid']['id'] = 'gid';
  $handler->display->display_options['arguments']['gid']['table'] = 'og_membership';
  $handler->display->display_options['arguments']['gid']['field'] = 'gid';
  $handler->display->display_options['arguments']['gid']['relationship'] = 'og_membership_rel';
  $handler->display->display_options['arguments']['gid']['default_action'] = 'empty';
  $handler->display->display_options['arguments']['gid']['default_argument_type'] = 'fixed';
  $handler->display->display_options['arguments']['gid']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['gid']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['gid']['summary_options']['items_per_page'] = '25';
  /* Contextual filter: Content: Has taxonomy term ID */
  $handler->display->display_options['arguments']['tid']['id'] = 'tid';
  $handler->display->display_options['arguments']['tid']['table'] = 'taxonomy_index';
  $handler->display->display_options['arguments']['tid']['field'] = 'tid';
  $handler->display->display_options['arguments']['tid']['exception']['title'] = 'Alle';
  $handler->display->display_options['arguments']['tid']['default_argument_type'] = 'taxonomy_tid';
  $handler->display->display_options['arguments']['tid']['default_argument_options']['term_page'] = FALSE;
  $handler->display->display_options['arguments']['tid']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['tid']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['tid']['summary_options']['items_per_page'] = '25';
  $handler->display->display_options['arguments']['tid']['specify_validation'] = TRUE;
  $handler->display->display_options['arguments']['tid']['validate']['type'] = 'taxonomy_term';
  $handler->display->display_options['arguments']['tid']['validate_options']['vocabularies'] = array(
    'event_category' => 'event_category',
  );
  $handler->display->display_options['pane_category']['name'] = 'Library panes';
  $handler->display->display_options['pane_category']['weight'] = '0';
  $handler->display->display_options['argument_input'] = array(
    'gid' => array(
      'type' => 'context',
      'context' => 'entity:node.nid',
      'context_optional' => 0,
      'panel' => '0',
      'fixed' => '75',
      'label' => 'OG membership: Group ID',
    ),
    'tid' => array(
      'type' => 'context',
      'context' => 'entity:taxonomy_term.tid',
      'context_optional' => 1,
      'panel' => '1',
      'fixed' => '%tid',
      'label' => 'Content: Has taxonomy term ID',
    ),
  );

  /* Display: Groups event list */
  $handler = $view->new_display('panel_pane', 'Groups event list', 'ding_event_groups_list');
  $handler->display->display_options['defaults']['title'] = FALSE;
  $handler->display->display_options['title'] = 'Group events';
  $handler->display->display_options['defaults']['use_more'] = FALSE;
  $handler->display->display_options['defaults']['link_display'] = FALSE;
  $handler->display->display_options['link_display'] = 'custom_url';
  $handler->display->display_options['link_url'] = 'arrangementer';
  $handler->display->display_options['defaults']['pager'] = FALSE;
  $handler->display->display_options['pager']['type'] = 'some';
  $handler->display->display_options['pager']['options']['items_per_page'] = '5';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['defaults']['style_plugin'] = FALSE;
  $handler->display->display_options['style_plugin'] = 'default';
  $handler->display->display_options['defaults']['style_options'] = FALSE;
  $handler->display->display_options['defaults']['row_plugin'] = FALSE;
  $handler->display->display_options['row_plugin'] = 'node';
  $handler->display->display_options['row_options']['links'] = FALSE;
  $handler->display->display_options['defaults']['row_options'] = FALSE;
  $handler->display->display_options['defaults']['empty'] = FALSE;
  $handler->display->display_options['defaults']['relationships'] = FALSE;
  /* Relationship: OG membership group */
  $handler->display->display_options['relationships']['og_membership_rel']['id'] = 'og_membership_rel';
  $handler->display->display_options['relationships']['og_membership_rel']['table'] = 'node';
  $handler->display->display_options['relationships']['og_membership_rel']['field'] = 'og_membership_rel';
  $handler->display->display_options['relationships']['og_membership_rel']['ui_name'] = 'OG membership group';
  $handler->display->display_options['relationships']['og_membership_rel']['label'] = 'OG membership group';
  /* Relationship: OG group */
  $handler->display->display_options['relationships']['og_membership_related_node_group']['id'] = 'og_membership_related_node_group';
  $handler->display->display_options['relationships']['og_membership_related_node_group']['table'] = 'og_membership';
  $handler->display->display_options['relationships']['og_membership_related_node_group']['field'] = 'og_membership_related_node_group';
  $handler->display->display_options['relationships']['og_membership_related_node_group']['relationship'] = 'og_membership_rel';
  $handler->display->display_options['relationships']['og_membership_related_node_group']['ui_name'] = 'OG group';
  $handler->display->display_options['relationships']['og_membership_related_node_group']['label'] = 'OG group';
  /* Relationship: OG membership from node (Library) */
  $handler->display->display_options['relationships']['og_membership_rel_1']['id'] = 'og_membership_rel_1';
  $handler->display->display_options['relationships']['og_membership_rel_1']['table'] = 'node';
  $handler->display->display_options['relationships']['og_membership_rel_1']['field'] = 'og_membership_rel';
  $handler->display->display_options['relationships']['og_membership_rel_1']['ui_name'] = 'OG membership from node (Library)';
  $handler->display->display_options['relationships']['og_membership_rel_1']['label'] = 'OG membership from node (Library)';
  /* Relationship: OG Library */
  $handler->display->display_options['relationships']['og_membership_related_node_group_1']['id'] = 'og_membership_related_node_group_1';
  $handler->display->display_options['relationships']['og_membership_related_node_group_1']['table'] = 'og_membership';
  $handler->display->display_options['relationships']['og_membership_related_node_group_1']['field'] = 'og_membership_related_node_group';
  $handler->display->display_options['relationships']['og_membership_related_node_group_1']['relationship'] = 'og_membership_rel_1';
  $handler->display->display_options['relationships']['og_membership_related_node_group_1']['ui_name'] = 'OG Library';
  $handler->display->display_options['relationships']['og_membership_related_node_group_1']['label'] = 'OG Library';
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Field: Date (for group header) */
  $handler->display->display_options['fields']['field_ding_event_date_1']['id'] = 'field_ding_event_date_1';
  $handler->display->display_options['fields']['field_ding_event_date_1']['table'] = 'field_data_field_ding_event_date';
  $handler->display->display_options['fields']['field_ding_event_date_1']['field'] = 'field_ding_event_date';
  $handler->display->display_options['fields']['field_ding_event_date_1']['ui_name'] = 'Date (for group header)';
  $handler->display->display_options['fields']['field_ding_event_date_1']['label'] = '';
  $handler->display->display_options['fields']['field_ding_event_date_1']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_ding_event_date_1']['element_default_classes'] = FALSE;
  $handler->display->display_options['fields']['field_ding_event_date_1']['settings'] = array(
    'format_type' => 'month_and_year_separator',
    'fromto' => 'value',
    'multiple_number' => '',
    'multiple_from' => '',
    'multiple_to' => '',
  );
  $handler->display->display_options['defaults']['arguments'] = FALSE;
  /* Contextual filter: OG membership: Group ID */
  $handler->display->display_options['arguments']['gid']['id'] = 'gid';
  $handler->display->display_options['arguments']['gid']['table'] = 'og_membership';
  $handler->display->display_options['arguments']['gid']['field'] = 'gid';
  $handler->display->display_options['arguments']['gid']['relationship'] = 'og_membership_rel';
  $handler->display->display_options['arguments']['gid']['default_action'] = 'empty';
  $handler->display->display_options['arguments']['gid']['default_argument_type'] = 'fixed';
  $handler->display->display_options['arguments']['gid']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['gid']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['gid']['summary_options']['items_per_page'] = '25';
  $handler->display->display_options['defaults']['filter_groups'] = FALSE;
  $handler->display->display_options['defaults']['filters'] = FALSE;
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
    'ding_event' => 'ding_event',
  );
  /* Filter criterion: Date: Date (node) */
  $handler->display->display_options['filters']['date_filter']['id'] = 'date_filter';
  $handler->display->display_options['filters']['date_filter']['table'] = 'node';
  $handler->display->display_options['filters']['date_filter']['field'] = 'date_filter';
  $handler->display->display_options['filters']['date_filter']['operator'] = '>=';
  $handler->display->display_options['filters']['date_filter']['default_date'] = 'now';
  $handler->display->display_options['filters']['date_filter']['date_fields'] = array(
    'field_data_field_ding_event_date.field_ding_event_date_value' => 'field_data_field_ding_event_date.field_ding_event_date_value',
    'field_data_field_ding_event_date.field_ding_event_date_value2' => 'field_data_field_ding_event_date.field_ding_event_date_value2',
  );
  /* Filter criterion: Content: Type */
  $handler->display->display_options['filters']['type_1']['id'] = 'type_1';
  $handler->display->display_options['filters']['type_1']['table'] = 'node';
  $handler->display->display_options['filters']['type_1']['field'] = 'type';
  $handler->display->display_options['filters']['type_1']['relationship'] = 'og_membership_related_node_group_1';
  $handler->display->display_options['filters']['type_1']['value'] = array(
    'ding_library' => 'ding_library',
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
  $handler->display->display_options['allow']['exposed_form'] = 'exposed_form';
  $handler->display->display_options['allow']['fields_override'] = 0;
  $handler->display->display_options['argument_input'] = array(
    'gid' => array(
      'type' => 'context',
      'context' => 'entity:node.nid',
      'context_optional' => 0,
      'panel' => '0',
      'fixed' => '',
      'label' => 'OG membership: Group ID',
    ),
  );

  /* Display: Event list (groups) */
  $handler = $view->new_display('panel_pane', 'Event list (groups)', 'ding_event_groups_list_group');
  $handler->display->display_options['defaults']['title'] = FALSE;
  $handler->display->display_options['title'] = 'Group events';
  $handler->display->display_options['defaults']['use_more'] = FALSE;
  $handler->display->display_options['defaults']['link_display'] = FALSE;
  $handler->display->display_options['link_display'] = 'custom_url';
  $handler->display->display_options['link_url'] = 'arrangementer';
  $handler->display->display_options['defaults']['pager'] = FALSE;
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = '10';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['pager']['options']['id'] = '0';
  $handler->display->display_options['pager']['options']['quantity'] = '9';
  $handler->display->display_options['pager']['options']['expose']['items_per_page_label'] = 'Number of elements';
  $handler->display->display_options['pager']['options']['expose']['items_per_page_options_all_label'] = '- Alle -';
  $handler->display->display_options['pager']['options']['expose']['offset_label'] = 'Forskydning';
  $handler->display->display_options['defaults']['style_plugin'] = FALSE;
  $handler->display->display_options['style_plugin'] = 'default';
  $handler->display->display_options['style_options']['grouping'] = array(
    0 => array(
      'field' => 'field_ding_event_date_1',
      'rendered' => 1,
      'rendered_strip' => 0,
    ),
  );
  $handler->display->display_options['style_options']['uses_fields'] = TRUE;
  $handler->display->display_options['defaults']['style_options'] = FALSE;
  $handler->display->display_options['defaults']['row_plugin'] = FALSE;
  $handler->display->display_options['row_plugin'] = 'node';
  $handler->display->display_options['row_options']['links'] = FALSE;
  $handler->display->display_options['defaults']['row_options'] = FALSE;
  $handler->display->display_options['defaults']['empty'] = FALSE;
  /* No results behavior: Global: Text area */
  $handler->display->display_options['empty']['area']['id'] = 'area';
  $handler->display->display_options['empty']['area']['table'] = 'views';
  $handler->display->display_options['empty']['area']['field'] = 'area';
  $handler->display->display_options['empty']['area']['label'] = 'Empty text';
  $handler->display->display_options['empty']['area']['empty'] = TRUE;
  $handler->display->display_options['empty']['area']['content'] = 'No events where found in the group.';
  $handler->display->display_options['empty']['area']['format'] = 'ding_wysiwyg';
  $handler->display->display_options['defaults']['relationships'] = FALSE;
  /* Relationship: OG membership group */
  $handler->display->display_options['relationships']['og_membership_rel']['id'] = 'og_membership_rel';
  $handler->display->display_options['relationships']['og_membership_rel']['table'] = 'node';
  $handler->display->display_options['relationships']['og_membership_rel']['field'] = 'og_membership_rel';
  $handler->display->display_options['relationships']['og_membership_rel']['ui_name'] = 'OG membership group';
  $handler->display->display_options['relationships']['og_membership_rel']['label'] = 'OG membership group';
  /* Relationship: OG group */
  $handler->display->display_options['relationships']['og_membership_related_node_group']['id'] = 'og_membership_related_node_group';
  $handler->display->display_options['relationships']['og_membership_related_node_group']['table'] = 'og_membership';
  $handler->display->display_options['relationships']['og_membership_related_node_group']['field'] = 'og_membership_related_node_group';
  $handler->display->display_options['relationships']['og_membership_related_node_group']['relationship'] = 'og_membership_rel';
  $handler->display->display_options['relationships']['og_membership_related_node_group']['ui_name'] = 'OG group';
  $handler->display->display_options['relationships']['og_membership_related_node_group']['label'] = 'OG group';
  /* Relationship: OG membership from node (Library) */
  $handler->display->display_options['relationships']['og_membership_rel_1']['id'] = 'og_membership_rel_1';
  $handler->display->display_options['relationships']['og_membership_rel_1']['table'] = 'node';
  $handler->display->display_options['relationships']['og_membership_rel_1']['field'] = 'og_membership_rel';
  $handler->display->display_options['relationships']['og_membership_rel_1']['ui_name'] = 'OG membership from node (Library)';
  $handler->display->display_options['relationships']['og_membership_rel_1']['label'] = 'OG membership from node (Library)';
  /* Relationship: OG Library */
  $handler->display->display_options['relationships']['og_membership_related_node_group_1']['id'] = 'og_membership_related_node_group_1';
  $handler->display->display_options['relationships']['og_membership_related_node_group_1']['table'] = 'og_membership';
  $handler->display->display_options['relationships']['og_membership_related_node_group_1']['field'] = 'og_membership_related_node_group';
  $handler->display->display_options['relationships']['og_membership_related_node_group_1']['relationship'] = 'og_membership_rel_1';
  $handler->display->display_options['relationships']['og_membership_related_node_group_1']['ui_name'] = 'OG Library';
  $handler->display->display_options['relationships']['og_membership_related_node_group_1']['label'] = 'OG Library';
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Field: Date (for group header) */
  $handler->display->display_options['fields']['field_ding_event_date_1']['id'] = 'field_ding_event_date_1';
  $handler->display->display_options['fields']['field_ding_event_date_1']['table'] = 'field_data_field_ding_event_date';
  $handler->display->display_options['fields']['field_ding_event_date_1']['field'] = 'field_ding_event_date';
  $handler->display->display_options['fields']['field_ding_event_date_1']['ui_name'] = 'Date (for group header)';
  $handler->display->display_options['fields']['field_ding_event_date_1']['label'] = '';
  $handler->display->display_options['fields']['field_ding_event_date_1']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_ding_event_date_1']['element_default_classes'] = FALSE;
  $handler->display->display_options['fields']['field_ding_event_date_1']['settings'] = array(
    'format_type' => 'month_and_year_separator',
    'fromto' => 'value',
    'multiple_number' => '',
    'multiple_from' => '',
    'multiple_to' => '',
  );
  $handler->display->display_options['defaults']['arguments'] = FALSE;
  /* Contextual filter: OG membership: Group ID */
  $handler->display->display_options['arguments']['gid']['id'] = 'gid';
  $handler->display->display_options['arguments']['gid']['table'] = 'og_membership';
  $handler->display->display_options['arguments']['gid']['field'] = 'gid';
  $handler->display->display_options['arguments']['gid']['relationship'] = 'og_membership_rel';
  $handler->display->display_options['arguments']['gid']['default_action'] = 'empty';
  $handler->display->display_options['arguments']['gid']['default_argument_type'] = 'fixed';
  $handler->display->display_options['arguments']['gid']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['gid']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['gid']['summary_options']['items_per_page'] = '25';
  /* Contextual filter: Content: Has taxonomy term ID */
  $handler->display->display_options['arguments']['tid']['id'] = 'tid';
  $handler->display->display_options['arguments']['tid']['table'] = 'taxonomy_index';
  $handler->display->display_options['arguments']['tid']['field'] = 'tid';
  $handler->display->display_options['arguments']['tid']['default_argument_type'] = 'fixed';
  $handler->display->display_options['arguments']['tid']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['tid']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['tid']['summary_options']['items_per_page'] = '25';
  $handler->display->display_options['defaults']['filter_groups'] = FALSE;
  $handler->display->display_options['defaults']['filters'] = FALSE;
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
    'ding_event' => 'ding_event',
  );
  /* Filter criterion: Date: Date (node) */
  $handler->display->display_options['filters']['date_filter']['id'] = 'date_filter';
  $handler->display->display_options['filters']['date_filter']['table'] = 'node';
  $handler->display->display_options['filters']['date_filter']['field'] = 'date_filter';
  $handler->display->display_options['filters']['date_filter']['operator'] = '>=';
  $handler->display->display_options['filters']['date_filter']['default_date'] = 'now';
  $handler->display->display_options['filters']['date_filter']['date_fields'] = array(
    'field_data_field_ding_event_date.field_ding_event_date_value' => 'field_data_field_ding_event_date.field_ding_event_date_value',
    'field_data_field_ding_event_date.field_ding_event_date_value2' => 'field_data_field_ding_event_date.field_ding_event_date_value2',
  );
  /* Filter criterion: Content: Type */
  $handler->display->display_options['filters']['type_1']['id'] = 'type_1';
  $handler->display->display_options['filters']['type_1']['table'] = 'node';
  $handler->display->display_options['filters']['type_1']['field'] = 'type';
  $handler->display->display_options['filters']['type_1']['relationship'] = 'og_membership_related_node_group_1';
  $handler->display->display_options['filters']['type_1']['value'] = array(
    'ding_library' => 'ding_library',
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
  $handler->display->display_options['allow']['exposed_form'] = 'exposed_form';
  $handler->display->display_options['allow']['fields_override'] = 0;
  $handler->display->display_options['argument_input'] = array(
    'gid' => array(
      'type' => 'context',
      'context' => 'entity:node.nid',
      'context_optional' => 0,
      'panel' => '0',
      'fixed' => '',
      'label' => 'OG membership: Group ID',
    ),
    'tid' => array(
      'type' => 'context',
      'context' => 'entity:taxonomy_term.tid',
      'context_optional' => 0,
      'panel' => '0',
      'fixed' => '',
      'label' => 'Content: Has taxonomy term ID',
    ),
  );

  /* Display: RSS library event list */
  $handler = $view->new_display('feed', 'RSS library event list', 'ding_event_rss_library_event_list');
  $handler->display->display_options['pager']['type'] = 'some';
  $handler->display->display_options['pager']['options']['items_per_page'] = '20';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['style_plugin'] = 'rss';
  $handler->display->display_options['row_plugin'] = 'node_rss';
  $handler->display->display_options['defaults']['arguments'] = FALSE;
  $handler->display->display_options['path'] = 'node/%/events/feed';
  $handler->display->display_options['displays'] = array(
    'ding_event_library_page_list' => 'ding_event_library_page_list',
    'default' => 0,
    'ding_event_frontpage_list' => 0,
    'ding_event_list' => 0,
    'ding_event_list_library' => 0,
    'ding_event_simple_list' => 0,
  );
  $handler->display->display_options['sitename_title'] = 1;

  /* Display: Simple event list */
  $handler = $view->new_display('panel_pane', 'Simple event list', 'ding_event_simple_list');
  $handler->display->display_options['defaults']['link_display'] = FALSE;
  $handler->display->display_options['link_display'] = 'custom_url';
  $handler->display->display_options['link_url'] = 'arrangementer';
  $handler->display->display_options['defaults']['pager'] = FALSE;
  $handler->display->display_options['pager']['type'] = 'some';
  $handler->display->display_options['pager']['options']['items_per_page'] = '5';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['defaults']['style_plugin'] = FALSE;
  $handler->display->display_options['style_plugin'] = 'list';
  $handler->display->display_options['style_options']['row_class'] = 'list-item';
  $handler->display->display_options['style_options']['class'] = 'list simple';
  $handler->display->display_options['style_options']['wrapper_class'] = '';
  $handler->display->display_options['defaults']['style_options'] = FALSE;
  $handler->display->display_options['defaults']['row_plugin'] = FALSE;
  $handler->display->display_options['row_plugin'] = 'fields';
  $handler->display->display_options['row_options']['hide_empty'] = TRUE;
  $handler->display->display_options['row_options']['default_field_elements'] = FALSE;
  $handler->display->display_options['defaults']['row_options'] = FALSE;
  $handler->display->display_options['defaults']['relationships'] = FALSE;
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Field: Date */
  $handler->display->display_options['fields']['field_ding_event_date']['id'] = 'field_ding_event_date';
  $handler->display->display_options['fields']['field_ding_event_date']['table'] = 'field_data_field_ding_event_date';
  $handler->display->display_options['fields']['field_ding_event_date']['field'] = 'field_ding_event_date';
  $handler->display->display_options['fields']['field_ding_event_date']['ui_name'] = 'Date';
  $handler->display->display_options['fields']['field_ding_event_date']['label'] = '';
  $handler->display->display_options['fields']['field_ding_event_date']['alter']['strip_tags'] = TRUE;
  $handler->display->display_options['fields']['field_ding_event_date']['element_type'] = 'span';
  $handler->display->display_options['fields']['field_ding_event_date']['element_class'] = 'date';
  $handler->display->display_options['fields']['field_ding_event_date']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_ding_event_date']['element_wrapper_type'] = '0';
  $handler->display->display_options['fields']['field_ding_event_date']['element_default_classes'] = FALSE;
  $handler->display->display_options['fields']['field_ding_event_date']['settings'] = array(
    'format_type' => 'ding_short_date_only',
    'fromto' => 'value',
    'multiple_number' => '',
    'multiple_from' => '',
    'multiple_to' => '',
  );
  /* Field: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['ui_name'] = 'Title';
  $handler->display->display_options['fields']['title']['label'] = '';
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['title']['alter']['ellipsis'] = FALSE;
  $handler->display->display_options['fields']['title']['element_type'] = 'h3';
  $handler->display->display_options['fields']['title']['element_class'] = 'heading';
  $handler->display->display_options['fields']['title']['element_label_type'] = '0';
  $handler->display->display_options['fields']['title']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['title']['element_wrapper_type'] = '0';
  $handler->display->display_options['fields']['title']['element_default_classes'] = FALSE;
  $handler->display->display_options['fields']['title']['hide_alter_empty'] = FALSE;
  $handler->display->display_options['defaults']['arguments'] = FALSE;
  /* Contextual filter: Content: Nid */
  $handler->display->display_options['arguments']['nid']['id'] = 'nid';
  $handler->display->display_options['arguments']['nid']['table'] = 'node';
  $handler->display->display_options['arguments']['nid']['field'] = 'nid';
  $handler->display->display_options['arguments']['nid']['default_action'] = 'default';
  $handler->display->display_options['arguments']['nid']['exception']['title'] = 'Alle';
  $handler->display->display_options['arguments']['nid']['default_argument_type'] = 'node';
  $handler->display->display_options['arguments']['nid']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['nid']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['nid']['summary_options']['items_per_page'] = '25';
  $handler->display->display_options['arguments']['nid']['not'] = TRUE;
  /* Contextual filter: Content: Has taxonomy term ID */
  $handler->display->display_options['arguments']['tid']['id'] = 'tid';
  $handler->display->display_options['arguments']['tid']['table'] = 'taxonomy_index';
  $handler->display->display_options['arguments']['tid']['field'] = 'tid';
  $handler->display->display_options['arguments']['tid']['default_action'] = 'default';
  $handler->display->display_options['arguments']['tid']['exception']['title'] = 'Alle';
  $handler->display->display_options['arguments']['tid']['default_argument_type'] = 'taxonomy_tid';
  $handler->display->display_options['arguments']['tid']['default_argument_options']['term_page'] = FALSE;
  $handler->display->display_options['arguments']['tid']['default_argument_options']['node'] = TRUE;
  $handler->display->display_options['arguments']['tid']['default_argument_options']['limit'] = TRUE;
  $handler->display->display_options['arguments']['tid']['default_argument_options']['vocabularies'] = array(
    'event_category' => 'event_category',
  );
  $handler->display->display_options['arguments']['tid']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['tid']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['tid']['summary_options']['items_per_page'] = '25';
  $handler->display->display_options['arguments']['tid']['specify_validation'] = TRUE;
  $handler->display->display_options['arguments']['tid']['validate']['type'] = 'taxonomy_term';
  $handler->display->display_options['arguments']['tid']['validate_options']['vocabularies'] = array(
    'event_category' => 'event_category',
  );
  $handler->display->display_options['arguments']['tid']['validate']['fail'] = 'ignore';
  $handler->display->display_options['pane_category']['name'] = 'Event panes';
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
    'tid' => array(
      'type' => 'context',
      'context' => 'terms.tids',
      'context_optional' => 1,
      'panel' => '0',
      'fixed' => '',
      'label' => 'Content: Has taxonomy term ID',
    ),
    'nid' => array(
      'type' => 'context',
      'context' => 'entity:node.nid',
      'context_optional' => 1,
      'panel' => '0',
      'fixed' => '',
      'label' => 'Content: Nid',
    ),
  );

  /* Display: RSS event list */
  $handler = $view->new_display('feed', 'RSS event list', 'ding_event_rss_event_list');
  $handler->display->display_options['pager']['type'] = 'some';
  $handler->display->display_options['pager']['options']['items_per_page'] = '20';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['style_plugin'] = 'rss';
  $handler->display->display_options['row_plugin'] = 'node_rss';
  $handler->display->display_options['path'] = 'event/feed';
  $handler->display->display_options['displays'] = array(
    'ding_event_frontpage_list' => 'ding_event_frontpage_list',
    'default' => 0,
    'ding_event_library_page_list' => 0,
    'ding_event_list' => 0,
    'ding_event_list_library' => 0,
    'ding_event_simple_list' => 0,
  );
  $handler->display->display_options['sitename_title'] = 1;

  /* Display: Event Image Crop list */
  $handler = $view->new_display('page', 'Event Image Crop list', 'page_1');
  $handler->display->display_options['defaults']['title'] = FALSE;
  $handler->display->display_options['title'] = 'Event Image Crop Overview';
  $handler->display->display_options['defaults']['css_class'] = FALSE;
  $handler->display->display_options['css_class'] = 'imagecrop-list';
  $handler->display->display_options['defaults']['access'] = FALSE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['access']['perm'] = 'edit any ding_event content';
  $handler->display->display_options['defaults']['pager'] = FALSE;
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = '30';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['pager']['options']['id'] = '0';
  $handler->display->display_options['pager']['options']['quantity'] = '9';
  $handler->display->display_options['defaults']['style_plugin'] = FALSE;
  $handler->display->display_options['style_plugin'] = 'table';
  $handler->display->display_options['style_options']['columns'] = array(
    'field_ding_event_date' => 'field_ding_event_date',
    'field_ding_event_date_1' => 'field_ding_event_date_1',
    'field_ding_event_date_2' => 'field_ding_event_date_2',
    'field_ding_event_location' => 'field_ding_event_location',
    'field_ding_event_date_3' => 'field_ding_event_date_3',
    'field_ding_event_price' => 'field_ding_event_price',
    'title' => 'title',
    'nothing_1' => 'nothing_1',
    'nothing' => 'nothing',
  );
  $handler->display->display_options['style_options']['default'] = '-1';
  $handler->display->display_options['style_options']['info'] = array(
    'field_ding_event_date' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_ding_event_date_1' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_ding_event_date_2' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_ding_event_location' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_ding_event_date_3' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_ding_event_price' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'title' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'nothing_1' => array(
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
  $handler->display->display_options['defaults']['style_options'] = FALSE;
  $handler->display->display_options['defaults']['row_plugin'] = FALSE;
  $handler->display->display_options['defaults']['row_options'] = FALSE;
  $handler->display->display_options['defaults']['relationships'] = FALSE;
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Field: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['ui_name'] = 'Title';
  $handler->display->display_options['fields']['title']['label'] = '';
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['title']['alter']['ellipsis'] = FALSE;
  $handler->display->display_options['fields']['title']['element_type'] = 'h3';
  $handler->display->display_options['fields']['title']['element_class'] = 'event-list-title';
  $handler->display->display_options['fields']['title']['element_label_type'] = '0';
  $handler->display->display_options['fields']['title']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['title']['element_wrapper_type'] = '0';
  $handler->display->display_options['fields']['title']['element_default_classes'] = FALSE;
  $handler->display->display_options['fields']['title']['hide_alter_empty'] = FALSE;
  /* Field: Content: Edit link */
  $handler->display->display_options['fields']['edit_node']['id'] = 'edit_node';
  $handler->display->display_options['fields']['edit_node']['table'] = 'views_entity_node';
  $handler->display->display_options['fields']['edit_node']['field'] = 'edit_node';
  $handler->display->display_options['fields']['edit_node']['label'] = 'Rediger';
  $handler->display->display_options['fields']['edit_node']['element_label_colon'] = FALSE;
  /* Field: Content: List image */
  $handler->display->display_options['fields']['field_ding_event_list_image']['id'] = 'field_ding_event_list_image';
  $handler->display->display_options['fields']['field_ding_event_list_image']['table'] = 'field_data_field_ding_event_list_image';
  $handler->display->display_options['fields']['field_ding_event_list_image']['field'] = 'field_ding_event_list_image';
  $handler->display->display_options['fields']['field_ding_event_list_image']['label'] = 'Original Image';
  $handler->display->display_options['fields']['field_ding_event_list_image']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_ding_event_list_image']['click_sort_column'] = 'fid';
  $handler->display->display_options['fields']['field_ding_event_list_image']['settings'] = array(
    'image_style' => '',
    'image_link' => '',
  );
  /* Field: Content: List image */
  $handler->display->display_options['fields']['field_ding_event_list_image_1']['id'] = 'field_ding_event_list_image_1';
  $handler->display->display_options['fields']['field_ding_event_list_image_1']['table'] = 'field_data_field_ding_event_list_image';
  $handler->display->display_options['fields']['field_ding_event_list_image_1']['field'] = 'field_ding_event_list_image';
  $handler->display->display_options['fields']['field_ding_event_list_image_1']['label'] = 'Cropped Image';
  $handler->display->display_options['fields']['field_ding_event_list_image_1']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_ding_event_list_image_1']['click_sort_column'] = 'fid';
  $handler->display->display_options['fields']['field_ding_event_list_image_1']['settings'] = array(
    'image_style' => 'ding_panorama_list_large',
    'image_link' => '',
  );
  $handler->display->display_options['defaults']['arguments'] = FALSE;
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
    'ding_event' => 'ding_event',
  );
  $handler->display->display_options['filters']['type']['group'] = 1;
  $handler->display->display_options['path'] = 'event-imagecrop';
  $translatables['ding_event'] = array(
    t('Master'),
    t('See all events'),
    t('Indsend'),
    t('Gendan'),
    t('Sortér efter'),
    t('Stigende'),
    t('Faldende'),
    t('Empty text'),
    t('No events where found.'),
    t('OG membership from node'),
    t('<div class="event-list-date-wrapper">
  <span class="event-list-day">[field_ding_event_date]</span>
  <div class="event-list-inner-wrapper">
    <span class="event-list-date">[field_ding_event_date_1]</span>
    <span class="event-list-month">[field_ding_event_date_2]</span>
  </div>
</div>'),
    t('<div class="event-list-info">
  <span class="event-list-location">[field_ding_event_location]</span>
  <span class="event-list-time">[field_ding_event_date_3]</span>
  <span class="event-list-price">[field_ding_event_price]</span>
</div>'),
    t('Alle'),
    t('Event list'),
    t('more'),
    t('Search'),
    t('Alle arrangementer'),
    t('Number of elements'),
    t('- Alle -'),
    t('Forskydning'),
    t('« First'),
    t('‹ previous'),
    t('Next ›'),
    t('Last »'),
    t('OG node group'),
    t('term from field_ding_event_category'),
    t('term from field_ding_event_tags'),
    t('term from field_ding_event_target'),
    t('From'),
    t('To'),
    t('Event panes'),
    t('Event list (frontpage)'),
    t('Events'),
    t('Library event list'),
    t('All'),
    t('Library panes'),
    t('Event list (library)'),
    t('Groups event list'),
    t('Group events'),
    t('OG membership group'),
    t('OG group'),
    t('OG membership from node (Library)'),
    t('OG Library'),
    t('Groups panes'),
    t('Event list (groups)'),
    t('« first'),
    t('next ›'),
    t('last »'),
    t('No events where found in the group.'),
    t('RSS library event list'),
    t('Simple event list'),
    t('RSS event list'),
    t('Event Image Crop list'),
    t('Event Image Crop Overview'),
    t('Items per page'),
    t('- All -'),
    t('Offset'),
    t('Rediger'),
    t('Original Image'),
    t('Cropped Image'),
  );
  $export['ding_event'] = $view;

  return $export;
}
