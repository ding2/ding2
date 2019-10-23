<?php
/**
 * @file
 * ding_frontend.features.menu_custom.inc
 */

/**
 * Implements hook_menu_default_menu_custom().
 */
function ding_frontend_menu_default_menu_custom() {
  $menus = array();

  // Exported menu: menu-tabs-menu.
  $menus['menu-tabs-menu'] = array(
    'menu_name' => 'menu-tabs-menu',
    'title' => 'Topbar menu',
    'description' => 'This menu is used to display tabs that let the user change between navigational elements.',
  );
  // Translatables
  // Included for use with string extractors like potx.
  t('This menu is used to display tabs that let the user change between navigational elements.');
  t('Topbar menu');


  return $menus;
}
