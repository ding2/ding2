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
    'ding_nodelist' => array(
      'value' => 1,
      'weight' => '-10',
      'title' => 'Nodelist',
      'category' => 'easyddb',
      'type' => 'ding_nodelist',
      'subtype' => 'ding_nodelist',
    ),
    'campaign' => array(
      'value' => 1,
      'weight' => '-9',
      'title' => 'Relevant campaigns',
      'category' => 'ding-',
      'type' => 'campaign',
      'subtype' => 'campaign',
    ),
    'carousel' => array(
      'value' => 1,
      'weight' => '-8',
      'title' => 'Ting search carousel',
      'category' => 'ting',
      'type' => 'carousel',
      'subtype' => 'carousel',
    ),
    'ding_item_list' => array(
      'value' => 1,
      'weight' => '-7',
      'title' => 'Ding item list',
      'category' => 'ding-',
      'type' => 'ding_item_list',
      'subtype' => 'ding_item_list',
    ),
    'ding_item_viewer' => array(
      'value' => 1,
      'weight' => '-6',
      'title' => 'Ding item viewer',
      'category' => 'ding-',
      'type' => 'ding_item_viewer',
      'subtype' => 'ding_item_viewer',
    ),
    'ding_item_viewer-item_viewer' => array(
      'value' => 1,
      'weight' => '-5',
      'title' => 'Ding item viewer',
      'category' => 'miscellaneous',
      'type' => 'block',
      'subtype' => 'ding_item_viewer-item_viewer',
    ),
    'ding_tabroll-ding_frontpage_tabroll' => array(
      'value' => 1,
      'weight' => '-4',
      'title' => 'Ding frontpage tabroll',
      'category' => 'ding-',
      'type' => 'views_panes',
      'subtype' => 'ding_tabroll-ding_frontpage_tabroll',
    ),
    'ding_news-ding_news_frontpage_list' => array(
      'value' => 1,
      'weight' => '-3',
      'title' => 'View: Ding news: News list (frontpage)',
      'category' => 'news-panes',
      'type' => 'views_panes',
      'subtype' => 'ding_news-ding_news_frontpage_list',
    ),
    'ding_event-ding_event_list_frontpage' => array(
      'value' => 1,
      'weight' => '-2',
      'title' => 'View: Ding event: Event list (frontpage)',
      'category' => 'event-panes',
      'type' => 'views_panes',
      'subtype' => 'ding_event-ding_event_list_frontpage',
    ),
    'ding_groups-ding_group_overview_simple' => array(
      'value' => 1,
      'weight' => '-1',
      'title' => 'View: Ding groups (temapages): Group overview (simple)',
      'category' => 'groups-panes',
      'type' => 'views_panes',
      'subtype' => 'ding_groups-ding_group_overview_simple',
    ),
    'menu_block-3' => array(
      'value' => 1,
      'weight' => '0',
      'title' => 'Submenu (menu block)',
      'category' => 'menus',
      'type' => 'block',
      'subtype' => 'menu_block-3',
    ),
    'menu_block-4' => array(
      'value' => 1,
      'weight' => '1',
      'title' => 'Submenu (secodary menu block)',
      'category' => 'menus',
      'type' => 'block',
      'subtype' => 'menu_block-4',
    ),
  );
  $export['ding_ipe_filter_table'] = $strongarm;

  return $export;
}
