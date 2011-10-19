<?php
/**
 * @file
 * ding_page.features.menu_custom.inc
 */

/**
 * Implements hook_menu_default_menu_custom().
 */
function ding_page_menu_default_menu_custom() {
  $menus = array();

  // Exported menu: menu-sider
  $menus['menu-sider'] = array(
    'menu_name' => 'menu-sider',
    'title' => 'Sider',
    'description' => 'Normale indholdssider',
  );
  // Translatables
  // Included for use with string extractors like potx.
  t('Normale indholdssider');
  t('Sider');


  return $menus;
}
