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

  // Exported menu: menu-footer-menu-1.
  $menus['menu-footer-menu-1'] = array(
    'menu_name' => 'menu-footer-menu-1',
    'title' => 'Footer menu 1',
    'description' => '',
  );
  // Exported menu: menu-footer-menu-2.
  $menus['menu-footer-menu-2'] = array(
    'menu_name' => 'menu-footer-menu-2',
    'title' => 'Footer menu 2',
    'description' => '',
  );
  // Exported menu: menu-footer-menu-3.
  $menus['menu-footer-menu-3'] = array(
    'menu_name' => 'menu-footer-menu-3',
    'title' => 'Footer menu 3',
    'description' => '',
  );
  // Exported menu: menu-footer-menu-4.
  $menus['menu-footer-menu-4'] = array(
    'menu_name' => 'menu-footer-menu-4',
    'title' => 'Footer menu 4',
    'description' => '',
  );
  // Translatables
  // Included for use with string extractors like potx.
  t('Footer menu 1');
  t('Footer menu 2');
  t('Footer menu 3');
  t('Footer menu 4');


  return $menus;
}
