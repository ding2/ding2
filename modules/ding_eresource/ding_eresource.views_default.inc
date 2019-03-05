<?php
/**
 * @file
 * ding_eresource.views_default.inc
 */

/**
 * Implements hook_views_default_views().
 */
function ding_eresource_views_default_views() {
  $export = array();

  $view = new view();
  $view->name = 'ding_eresource';
  $view->description = 'List of E-resources';
  $view->tag = 'default';
  $view->base_table = 'node';
  $view->human_name = 'Ding E-resource';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'E-resources';
  $handler->display->display_options['use_ajax'] = TRUE;
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['link_display'] = 'custom_url';
  $handler->display->display_options['link_url'] = 'e-materialer';
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['exposed_form']['options']['reset_button_label'] = 'Gendan';
  $handler->display->display_options['exposed_form']['options']['autosubmit'] = TRUE;
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['tags']['first'] = '« første';
  $handler->display->display_options['pager']['options']['tags']['previous'] = '‹ forrige';
  $handler->display->display_options['pager']['options']['tags']['next'] = 'næste ›';
  $handler->display->display_options['pager']['options']['tags']['last'] = 'sidste »';
  $handler->display->display_options['style_plugin'] = 'list';
  $handler->display->display_options['style_options']['row_class'] = 'eresource-list-item';
  $handler->display->display_options['style_options']['class'] = 'list eresource-list';
  $handler->display->display_options['style_options']['wrapper_class'] = '';
  $handler->display->display_options['row_plugin'] = 'fields';
  /* Field: Image (logo) */
  $handler->display->display_options['fields']['field_ding_eresource_list_image']['id'] = 'field_ding_eresource_list_image';
  $handler->display->display_options['fields']['field_ding_eresource_list_image']['table'] = 'field_data_field_ding_eresource_list_image';
  $handler->display->display_options['fields']['field_ding_eresource_list_image']['field'] = 'field_ding_eresource_list_image';
  $handler->display->display_options['fields']['field_ding_eresource_list_image']['ui_name'] = 'Image (logo)';
  $handler->display->display_options['fields']['field_ding_eresource_list_image']['label'] = '';
  $handler->display->display_options['fields']['field_ding_eresource_list_image']['element_type'] = 'div';
  $handler->display->display_options['fields']['field_ding_eresource_list_image']['element_class'] = 'eresource-image-wrapper';
  $handler->display->display_options['fields']['field_ding_eresource_list_image']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_ding_eresource_list_image']['element_default_classes'] = FALSE;
  $handler->display->display_options['fields']['field_ding_eresource_list_image']['click_sort_column'] = 'fid';
  $handler->display->display_options['fields']['field_ding_eresource_list_image']['type'] = 'cs_adaptive_image';
  $handler->display->display_options['fields']['field_ding_eresource_list_image']['settings'] = array(
    'image_link' => '',
    'styles' => array(
      'breakpoint_1' => '768',
      'style_1' => 'ding_list_medium',
      'breakpoint_2' => '500',
      'style_2' => 'ding_list_small',
      'max_style' => 'ding_list_large',
      'fallback_style' => 'ding_list_large',
    ),
  );
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = '';
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['title']['alter']['ellipsis'] = FALSE;
  /* Field: Lead */
  $handler->display->display_options['fields']['field_ding_eresource_lead']['id'] = 'field_ding_eresource_lead';
  $handler->display->display_options['fields']['field_ding_eresource_lead']['table'] = 'field_data_field_ding_eresource_lead';
  $handler->display->display_options['fields']['field_ding_eresource_lead']['field'] = 'field_ding_eresource_lead';
  $handler->display->display_options['fields']['field_ding_eresource_lead']['ui_name'] = 'Lead';
  $handler->display->display_options['fields']['field_ding_eresource_lead']['label'] = '';
  $handler->display->display_options['fields']['field_ding_eresource_lead']['element_type'] = 'p';
  $handler->display->display_options['fields']['field_ding_eresource_lead']['element_class'] = 'eresources-list-lead';
  $handler->display->display_options['fields']['field_ding_eresource_lead']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_ding_eresource_lead']['element_wrapper_type'] = '0';
  $handler->display->display_options['fields']['field_ding_eresource_lead']['element_default_classes'] = FALSE;
  /* Sort criterion: Content: Title */
  $handler->display->display_options['sorts']['title']['id'] = 'title';
  $handler->display->display_options['sorts']['title']['table'] = 'node';
  $handler->display->display_options['sorts']['title']['field'] = 'title';
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
    'ding_eresource' => 'ding_eresource',
  );
  /* Filter criterion: Content: Language */
  $handler->display->display_options['filters']['language']['id'] = 'language';
  $handler->display->display_options['filters']['language']['table'] = 'node';
  $handler->display->display_options['filters']['language']['field'] = 'language';
  $handler->display->display_options['filters']['language']['value'] = array(
    '***CURRENT_LANGUAGE***' => '***CURRENT_LANGUAGE***',
    'und' => 'und',
  );
  /* Filter criterion: Content: Access (field_ding_eresource_access) */
  $handler->display->display_options['filters']['field_ding_eresource_access_tid']['id'] = 'field_ding_eresource_access_tid';
  $handler->display->display_options['filters']['field_ding_eresource_access_tid']['table'] = 'field_data_field_ding_eresource_access';
  $handler->display->display_options['filters']['field_ding_eresource_access_tid']['field'] = 'field_ding_eresource_access_tid';
  $handler->display->display_options['filters']['field_ding_eresource_access_tid']['exposed'] = TRUE;
  $handler->display->display_options['filters']['field_ding_eresource_access_tid']['expose']['operator_id'] = 'field_ding_eresource_access_tid_op';
  $handler->display->display_options['filters']['field_ding_eresource_access_tid']['expose']['label'] = 'Access';
  $handler->display->display_options['filters']['field_ding_eresource_access_tid']['expose']['operator'] = 'field_ding_eresource_access_tid_op';
  $handler->display->display_options['filters']['field_ding_eresource_access_tid']['expose']['identifier'] = 'access';
  $handler->display->display_options['filters']['field_ding_eresource_access_tid']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    5 => 0,
    6 => 0,
    8 => 0,
    3 => 0,
    4 => 0,
    7 => 0,
  );
  $handler->display->display_options['filters']['field_ding_eresource_access_tid']['type'] = 'select';
  $handler->display->display_options['filters']['field_ding_eresource_access_tid']['vocabulary'] = 'e_resource_availability';

  /* Display: E-resources list */
  $handler = $view->new_display('panel_pane', 'E-resources list', 'ding_eresource_list');
  $handler->display->display_options['defaults']['title'] = FALSE;
  $handler->display->display_options['link_url'] = 'e-materialer';
  $handler->display->display_options['defaults']['style_plugin'] = FALSE;
  $handler->display->display_options['style_plugin'] = 'default';
  $handler->display->display_options['defaults']['style_options'] = FALSE;
  $handler->display->display_options['defaults']['row_plugin'] = FALSE;
  $handler->display->display_options['row_plugin'] = 'node';
  $handler->display->display_options['row_options']['links'] = FALSE;
  $handler->display->display_options['defaults']['row_options'] = FALSE;
  $handler->display->display_options['exposed_block'] = TRUE;
  $handler->display->display_options['defaults']['arguments'] = FALSE;
  /* Contextual filter: Content: Category (field_ding_eresource_category) */
  $handler->display->display_options['arguments']['field_ding_eresource_category_tid']['id'] = 'field_ding_eresource_category_tid';
  $handler->display->display_options['arguments']['field_ding_eresource_category_tid']['table'] = 'field_data_field_ding_eresource_category';
  $handler->display->display_options['arguments']['field_ding_eresource_category_tid']['field'] = 'field_ding_eresource_category_tid';
  $handler->display->display_options['arguments']['field_ding_eresource_category_tid']['exception']['title'] = 'Alle';
  $handler->display->display_options['arguments']['field_ding_eresource_category_tid']['default_argument_type'] = 'fixed';
  $handler->display->display_options['arguments']['field_ding_eresource_category_tid']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['field_ding_eresource_category_tid']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['field_ding_eresource_category_tid']['summary_options']['items_per_page'] = '25';
  $handler->display->display_options['arguments']['field_ding_eresource_category_tid']['specify_validation'] = TRUE;
  $handler->display->display_options['arguments']['field_ding_eresource_category_tid']['validate']['type'] = 'taxonomy_term';
  $handler->display->display_options['arguments']['field_ding_eresource_category_tid']['validate_options']['vocabularies'] = array(
    'e_resource_category' => 'e_resource_category',
  );
  /* Contextual filter: E-resurser hvor titel begynder med “%2” */
  $handler->display->display_options['arguments']['title']['id'] = 'title';
  $handler->display->display_options['arguments']['title']['table'] = 'node';
  $handler->display->display_options['arguments']['title']['field'] = 'title';
  $handler->display->display_options['arguments']['title']['ui_name'] = 'E-resurser hvor titel begynder med “%2”';
  $handler->display->display_options['arguments']['title']['exception']['title'] = 'Alle';
  $handler->display->display_options['arguments']['title']['default_argument_type'] = 'fixed';
  $handler->display->display_options['arguments']['title']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['title']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['title']['summary_options']['items_per_page'] = '25';
  $handler->display->display_options['arguments']['title']['specify_validation'] = TRUE;
  $handler->display->display_options['arguments']['title']['glossary'] = TRUE;
  $handler->display->display_options['arguments']['title']['limit'] = '1';
  $handler->display->display_options['arguments']['title']['case'] = 'upper';
  $handler->display->display_options['arguments']['title']['path_case'] = 'lower';
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
    'ding_eresource' => 'ding_eresource',
  );
  /* Filter criterion: Content: Language */
  $handler->display->display_options['filters']['language']['id'] = 'language';
  $handler->display->display_options['filters']['language']['table'] = 'node';
  $handler->display->display_options['filters']['language']['field'] = 'language';
  $handler->display->display_options['filters']['language']['value'] = array(
    '***CURRENT_LANGUAGE***' => '***CURRENT_LANGUAGE***',
    'und' => 'und',
  );
  /* Filter criterion: Content: Access (field_ding_eresource_access) */
  $handler->display->display_options['filters']['field_ding_eresource_access_tid']['id'] = 'field_ding_eresource_access_tid';
  $handler->display->display_options['filters']['field_ding_eresource_access_tid']['table'] = 'field_data_field_ding_eresource_access';
  $handler->display->display_options['filters']['field_ding_eresource_access_tid']['field'] = 'field_ding_eresource_access_tid';
  $handler->display->display_options['filters']['field_ding_eresource_access_tid']['exposed'] = TRUE;
  $handler->display->display_options['filters']['field_ding_eresource_access_tid']['expose']['operator_id'] = 'field_ding_eresource_access_tid_op';
  $handler->display->display_options['filters']['field_ding_eresource_access_tid']['expose']['operator'] = 'field_ding_eresource_access_tid_op';
  $handler->display->display_options['filters']['field_ding_eresource_access_tid']['expose']['identifier'] = 'access';
  $handler->display->display_options['filters']['field_ding_eresource_access_tid']['expose']['remember_roles'] = array(
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
  $handler->display->display_options['filters']['field_ding_eresource_access_tid']['type'] = 'select';
  $handler->display->display_options['filters']['field_ding_eresource_access_tid']['vocabulary'] = 'e_resource_availability';
  $handler->display->display_options['argument_input'] = array(
    'field_ding_eresource_category_tid' => array(
      'type' => 'panel',
      'context' => 'entity:user.cancel-url',
      'context_optional' => 0,
      'panel' => '0',
      'fixed' => '',
      'label' => 'Indhold: Category (field_ding_eresource_category)',
    ),
    'title' => array(
      'type' => 'panel',
      'context' => 'entity:user.cancel-url',
      'context_optional' => 0,
      'panel' => '1',
      'fixed' => '',
      'label' => 'Indhold: Titel',
    ),
  );

  /* Display: Category description */
  $handler = $view->new_display('panel_pane', 'Category description', 'ding_eresource_category');
  $handler->display->display_options['defaults']['title'] = FALSE;
  $handler->display->display_options['defaults']['query'] = FALSE;
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['defaults']['pager'] = FALSE;
  $handler->display->display_options['pager']['type'] = 'some';
  $handler->display->display_options['pager']['options']['items_per_page'] = '1';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['defaults']['style_plugin'] = FALSE;
  $handler->display->display_options['style_plugin'] = 'default';
  $handler->display->display_options['style_options']['default_row_class'] = FALSE;
  $handler->display->display_options['style_options']['row_class_special'] = FALSE;
  $handler->display->display_options['defaults']['style_options'] = FALSE;
  $handler->display->display_options['defaults']['row_plugin'] = FALSE;
  $handler->display->display_options['row_plugin'] = 'fields';
  $handler->display->display_options['defaults']['row_options'] = FALSE;
  $handler->display->display_options['defaults']['empty'] = FALSE;
  /* No results behavior: Global: Unfiltered text */
  $handler->display->display_options['empty']['area_text_custom']['id'] = 'area_text_custom';
  $handler->display->display_options['empty']['area_text_custom']['table'] = 'views';
  $handler->display->display_options['empty']['area_text_custom']['field'] = 'area_text_custom';
  $handler->display->display_options['empty']['area_text_custom']['label'] = 'Standardtekst for E-ressourcer';
  $handler->display->display_options['empty']['area_text_custom']['empty'] = TRUE;
  $handler->display->display_options['empty']['area_text_custom']['content'] = '
<p>E-resurser er elektroniske opslagsværker, aviser og tidsskrifter, e-bøger og andre netmedier, som biblioteket stiller gratis til rådighed for borgerne. Brug e-resurserne til at låne netmedier eller søge i databaser efter alverdens emner. De fleste e-resurser har fjernadgang. Det betyder, at du kan anvende dem hjemmefra fra en hvilken som helst internet-adgang. Det kræver blot, at du er bosat i kommunen og er indmeldt som låner på et af bibliotekerne. Alle kan benytte e-resurserne på biblioteket.</p>';
  $handler->display->display_options['defaults']['relationships'] = FALSE;
  /* Relationship: Content: Category (field_ding_eresource_category) */
  $handler->display->display_options['relationships']['field_ding_eresource_category_tid']['id'] = 'field_ding_eresource_category_tid';
  $handler->display->display_options['relationships']['field_ding_eresource_category_tid']['table'] = 'field_data_field_ding_eresource_category';
  $handler->display->display_options['relationships']['field_ding_eresource_category_tid']['field'] = 'field_ding_eresource_category_tid';
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Field: Content: Category */
  $handler->display->display_options['fields']['field_ding_eresource_category']['id'] = 'field_ding_eresource_category';
  $handler->display->display_options['fields']['field_ding_eresource_category']['table'] = 'field_data_field_ding_eresource_category';
  $handler->display->display_options['fields']['field_ding_eresource_category']['field'] = 'field_ding_eresource_category';
  $handler->display->display_options['fields']['field_ding_eresource_category']['label'] = '';
  $handler->display->display_options['fields']['field_ding_eresource_category']['element_type'] = 'h2';
  $handler->display->display_options['fields']['field_ding_eresource_category']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_ding_eresource_category']['element_wrapper_type'] = '0';
  $handler->display->display_options['fields']['field_ding_eresource_category']['element_default_classes'] = FALSE;
  $handler->display->display_options['fields']['field_ding_eresource_category']['empty'] = '<h2>E-resurser (no results text)<h/2>';
  $handler->display->display_options['fields']['field_ding_eresource_category']['type'] = 'taxonomy_term_reference_plain';
  $handler->display->display_options['fields']['field_ding_eresource_category']['group_rows'] = FALSE;
  $handler->display->display_options['fields']['field_ding_eresource_category']['delta_offset'] = '0';
  /* Field: Taxonomy term: Term description */
  $handler->display->display_options['fields']['description']['id'] = 'description';
  $handler->display->display_options['fields']['description']['table'] = 'taxonomy_term_data';
  $handler->display->display_options['fields']['description']['field'] = 'description';
  $handler->display->display_options['fields']['description']['relationship'] = 'field_ding_eresource_category_tid';
  $handler->display->display_options['fields']['description']['label'] = '';
  $handler->display->display_options['fields']['description']['element_type'] = 'p';
  $handler->display->display_options['fields']['description']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['description']['element_default_classes'] = FALSE;
  $handler->display->display_options['fields']['description']['hide_empty'] = TRUE;
  $handler->display->display_options['defaults']['sorts'] = FALSE;
  $handler->display->display_options['defaults']['arguments'] = FALSE;
  /* Contextual filter: Content: Category (field_ding_eresource_category) */
  $handler->display->display_options['arguments']['field_ding_eresource_category_tid']['id'] = 'field_ding_eresource_category_tid';
  $handler->display->display_options['arguments']['field_ding_eresource_category_tid']['table'] = 'field_data_field_ding_eresource_category';
  $handler->display->display_options['arguments']['field_ding_eresource_category_tid']['field'] = 'field_ding_eresource_category_tid';
  $handler->display->display_options['arguments']['field_ding_eresource_category_tid']['default_action'] = 'empty';
  $handler->display->display_options['arguments']['field_ding_eresource_category_tid']['exception']['value'] = '';
  $handler->display->display_options['arguments']['field_ding_eresource_category_tid']['exception']['title'] = 'Alle';
  $handler->display->display_options['arguments']['field_ding_eresource_category_tid']['default_argument_type'] = 'fixed';
  $handler->display->display_options['arguments']['field_ding_eresource_category_tid']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['field_ding_eresource_category_tid']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['field_ding_eresource_category_tid']['summary_options']['items_per_page'] = '25';
  $handler->display->display_options['arguments']['field_ding_eresource_category_tid']['specify_validation'] = TRUE;
  $handler->display->display_options['defaults']['filter_groups'] = FALSE;
  $handler->display->display_options['defaults']['filters'] = FALSE;
  /* Filter criterion: Content: Type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'node';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'ding_eresource' => 'ding_eresource',
  );
  /* Filter criterion: Content: Language */
  $handler->display->display_options['filters']['language']['id'] = 'language';
  $handler->display->display_options['filters']['language']['table'] = 'node';
  $handler->display->display_options['filters']['language']['field'] = 'language';
  $handler->display->display_options['filters']['language']['value'] = array(
    '***CURRENT_LANGUAGE***' => '***CURRENT_LANGUAGE***',
    'und' => 'und',
  );
  $handler->display->display_options['argument_input'] = array(
    'field_ding_eresource_category_tid' => array(
      'type' => 'panel',
      'context' => 'entity:node.field_ding_faq_category',
      'context_optional' => 0,
      'panel' => '0',
      'fixed' => '',
      'label' => 'Indhold: Category (field_ding_eresource_category)',
    ),
  );
  $translatables['ding_eresource'] = array(
    t('Master'),
    t('E-resources'),
    t('more'),
    t('Apply'),
    t('Gendan'),
    t('Sort by'),
    t('Asc'),
    t('Desc'),
    t('Items per page'),
    t('- All -'),
    t('Offset'),
    t('« første'),
    t('‹ forrige'),
    t('næste ›'),
    t('sidste »'),
    t('Access'),
    t('E-resources list'),
    t('Alle'),
    t('View panes'),
    t('Category description'),
    t('Standardtekst for E-ressourcer'),
    t('
<p>E-resurser er elektroniske opslagsværker, aviser og tidsskrifter, e-bøger og andre netmedier, som biblioteket stiller gratis til rådighed for borgerne. Brug e-resurserne til at låne netmedier eller søge i databaser efter alverdens emner. De fleste e-resurser har fjernadgang. Det betyder, at du kan anvende dem hjemmefra fra en hvilken som helst internet-adgang. Det kræver blot, at du er bosat i kommunen og er indmeldt som låner på et af bibliotekerne. Alle kan benytte e-resurserne på biblioteket.</p>'),
    t('term from field_ding_eresource_category'),
    t('<h2>E-resurser (no results text)<h/2>'),
  );
  $export['ding_eresource'] = $view;

  return $export;
}
