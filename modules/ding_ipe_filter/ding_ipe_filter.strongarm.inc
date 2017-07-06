<?php
/**
 * @file
 * Default settings for user roles and panel panes.
 */

/**
 * Implements hook_strongarm().
 */
function ding_ipe_filter_strongarm() {
  $export = array();

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'ding_ipe_filter_settings';
  $strongarm->value = array(
    'admin_display' => 1,
  );
  $export['ding_ipe_filter_settings'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'ding_ipe_filter_table';
  $strongarm->value = array(
    'popular' => array(
      'value' => 1,
      'weight' => '-10',
      'title' => 'Månedens bedst bedømte titler',
      'category' => 'ding-',
      'type' => 'popular',
      'subtype' => 'popular',
    ),
    'serendipity_ting_object' => array(
      'value' => 1,
      'weight' => '-9',
      'title' => 'Biblioteket foreslår materialer til dig',
      'category' => 'ding-',
      'type' => 'serendipity_ting_object',
      'subtype' => 'serendipity_ting_object',
    ),
    'ding_tabroll-ding_frontpage_tabroll' => array(
      'value' => 1,
      'weight' => '-8',
      'title' => 'Tabroll',
      'category' => 'ding-',
      'type' => 'views_panes',
      'subtype' => 'ding_tabroll-ding_frontpage_tabroll',
    ),
    'carousel' => array(
      'value' => 1,
      'weight' => '-7',
      'title' => 'Forsidekarussel',
      'category' => 'materialer',
      'type' => 'carousel',
      'subtype' => 'carousel',
    ),
    'interaction_pane' => array(
      'value' => 1,
      'weight' => '-6',
      'title' => 'Interaktionsboks',
      'category' => 'ding-',
      'type' => 'interaction_pane',
      'subtype' => 'interaction_pane',
    ),
    'ding_groups-ding_group_overview_simple' => array(
      'value' => 1,
      'weight' => '-5',
      'title' => 'Temaer',
      'category' => 'groups-panes',
      'type' => 'views_panes',
      'subtype' => 'ding_groups-ding_group_overview_simple',
    ),
    'campaign' => array(
      'value' => 1,
      'weight' => '-4',
      'title' => 'Kampagne',
      'category' => 'ding-',
      'type' => 'campaign',
      'subtype' => 'campaign',
    ),
    'ding_news-ding_news_frontpage_list' => array(
      'value' => 1,
      'weight' => '-3',
      'title' => 'Nyheder',
      'category' => 'news-panes',
      'type' => 'views_panes',
      'subtype' => 'ding_news-ding_news_frontpage_list',
    ),
    'ding_event-ding_event_list_frontpage' => array(
      'value' => 1,
      'weight' => '-2',
      'title' => 'Arrangementer',
      'category' => 'event-panes',
      'type' => 'views_panes',
      'subtype' => 'ding_event-ding_event_list_frontpage',
    ),
    'all_opening_hours' => array(
      'value' => 1,
      'weight' => '-1',
      'title' => 'Åbningstider',
      'category' => 'ding-',
      'type' => 'all_opening_hours',
      'subtype' => 'all_opening_hours',
    ),
    'ding_nodelist' => array(
      'value' => 1,
      'weight' => '1',
      'title' => 'Nodeliste',
      'category' => 'easyddb',
      'type' => 'ding_nodelist',
      'subtype' => 'ding_nodelist',
    ),
    'ding_item_list' => array(
      'value' => 1,
      'weight' => '2',
      'title' => 'Materialeliste',
      'category' => 'ding-',
      'type' => 'ding_item_list',
      'subtype' => 'ding_item_list',
    ),
    'ding_item_viewer' => array(
      'value' => 1,
      'weight' => '3',
      'title' => 'Materiale karrusel (ny)',
      'category' => 'ding-',
      'type' => 'ding_item_viewer',
      'subtype' => 'ding_item_viewer',
    ),
  );
  $export['ding_ipe_filter_table'] = $strongarm;

  return $export;
}
