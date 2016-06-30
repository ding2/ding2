<?php

/**
 * @file
 * ding_interests.views_default.inc
 */

/**
 * Implements hook_views_default_views().
 */
function ding_interests_views_default_views() {
  $export = array();

  $view = new view();
  $view->name = 'ding_interests';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'taxonomy_term_data';
  $view->human_name = 'Ding interests';
  $view->core = 7;
  $view->api_version = '3.0';
  /* Edit this to true to make a default view disabled initially */

  $view->disabled = FALSE;

  /* Display: Master */

  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Biblioteket anbefaler emneord';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['use_more_text'] = 'mere';
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['exposed_form']['options']['submit_button'] = 'Udfør';
  $handler->display->display_options['exposed_form']['options']['reset_button_label'] = 'Gendan';
  $handler->display->display_options['exposed_form']['options']['exposed_sorts_label'] = 'Sortér efter';
  $handler->display->display_options['exposed_form']['options']['sort_asc_label'] = 'Stigende';
  $handler->display->display_options['exposed_form']['options']['sort_desc_label'] = 'Faldende';
  $handler->display->display_options['pager']['type'] = 'some';
  $handler->display->display_options['pager']['options']['items_per_page'] = '3';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['style_plugin'] = 'default';
  $handler->display->display_options['row_plugin'] = 'fields';
  /* Forbindelse: Ding: interests */

  $handler->display->display_options['relationships']['ding_interests']['id'] = 'ding_interests';
  $handler->display->display_options['relationships']['ding_interests']['table'] = 'taxonomy_term_data';
  $handler->display->display_options['relationships']['ding_interests']['field'] = 'ding_interests';
  $handler->display->display_options['relationships']['ding_interests']['required'] = 0;
  $handler->display->display_options['relationships']['ding_interests']['ding_interests'] = 'interests';
  /* Felt: Ord i ordforråd: Rendered Ord i ordforråd */

  $handler->display->display_options['fields']['rendered_entity']['id'] = 'rendered_entity';
  $handler->display->display_options['fields']['rendered_entity']['table'] = 'views_entity_taxonomy_term';
  $handler->display->display_options['fields']['rendered_entity']['field'] = 'rendered_entity';
  $handler->display->display_options['fields']['rendered_entity']['label'] = '';
  $handler->display->display_options['fields']['rendered_entity']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['rendered_entity']['link_to_entity'] = 1;
  $handler->display->display_options['fields']['rendered_entity']['display'] = 'view';
  $handler->display->display_options['fields']['rendered_entity']['view_mode'] = 'teaser';
  /* Sorteringskriterie: Global: Tilfældig */

  $handler->display->display_options['sorts']['random']['id'] = 'random';
  $handler->display->display_options['sorts']['random']['table'] = 'views';
  $handler->display->display_options['sorts']['random']['field'] = 'random';
  /* Filterkriterie: Ordforråd: Maskinnavn */

  $handler->display->display_options['filters']['machine_name']['id'] = 'machine_name';
  $handler->display->display_options['filters']['machine_name']['table'] = 'taxonomy_vocabulary';
  $handler->display->display_options['filters']['machine_name']['field'] = 'machine_name';
  $handler->display->display_options['filters']['machine_name']['value'] = array(
    'ding_content_tags' => 'ding_content_tags',
  );
  /* Filterkriterie: Ord i ordforråd: Status (field_status) */

  $handler->display->display_options['filters']['field_status_tid']['id'] = 'field_status_tid';
  $handler->display->display_options['filters']['field_status_tid']['table'] = 'field_data_field_status';
  $handler->display->display_options['filters']['field_status_tid']['field'] = 'field_status_tid';
  $handler->display->display_options['filters']['field_status_tid']['value'] = array(
    60 => '60',
  );
  $handler->display->display_options['filters']['field_status_tid']['type'] = 'select';
  $handler->display->display_options['filters']['field_status_tid']['vocabulary'] = 'interest_status';
  /* Filterkriterie: Ding: Ding interests */

  $handler->display->display_options['filters']['ding_interests']['id'] = 'ding_interests';
  $handler->display->display_options['filters']['ding_interests']['table'] = 'taxonomy_term_data';
  $handler->display->display_options['filters']['ding_interests']['field'] = 'ding_interests';
  $handler->display->display_options['filters']['ding_interests']['value'] = '0';

  /* Display: Content pane */

  $handler = $view->new_display('panel_pane', 'Content pane', 'panel_pane_1');
  $translatables['ding_interests'] = array(
    t('Master'),
    t('Biblioteket anbefaler emneord'),
    t('mere'),
    t('Udfør'),
    t('Gendan'),
    t('Sortér efter'),
    t('Stigende'),
    t('Faldende'),
    t('Ding interest'),
    t('Content pane'),
    t('View panes'),
  );
  $export[$view->name] = $view;

  return $export;
}
