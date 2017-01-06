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
  $strongarm->name = 'ding_ipe_filter_table';
  $strongarm->value = array(
    'ding_tabroll-ding_frontpage_tabroll' => array(
      'value' => 1,
      'category' => 'ding-',
      'delta' => 'Ding frontpage tabroll',
      'type' => 'views_panes',
      'subtype' => 'ding_tabroll-ding_frontpage_tabroll',
    ),
    'ding_event-ding_event_list_frontpage' => array(
      'value' => 1,
      'category' => 'event-panes',
      'delta' => 'View: Ding event: Event list (frontpage)',
      'type' => 'views_panes',
      'subtype' => 'ding_event-ding_event_list_frontpage',
    ),
    'ding_groups-panel_pane_1' => array(
      'value' => 1,
      'category' => 'groups-panes',
      'delta' => 'View: Ding groups (temapages): Front page groups listing',
      'type' => 'views_panes',
      'subtype' => 'ding_groups-panel_pane_1',
    ),
    'menu_block-3' => array(
      'value' => 1,
      'category' => 'menus',
      'delta' => 'Submenu (menu block)',
      'type' => 'block',
      'subtype' => 'menu_block-3',
    ),
    'menu_block-4' => array(
      'value' => 1,
      'category' => 'menus',
      'delta' => 'Submenu (secodary menu block)',
      'type' => 'block',
      'subtype' => 'menu_block-4',
    ),
    'ding_news-ding_news_frontpage_list' => array(
      'value' => 1,
      'category' => 'news-panes',
      'delta' => 'View: Ding news: News list (frontpage)',
      'type' => 'views_panes',
      'subtype' => 'ding_news-ding_news_frontpage_list',
    ),
    'carousel' => array(
      'value' => 1,
      'category' => 'ting',
      'delta' => 'Ting search carousel',
      'type' => 'carousel',
      'subtype' => 'carousel',
    ),
  );
  $export['ding_ipe_filter_table'] = $strongarm;

  return $export;
}
