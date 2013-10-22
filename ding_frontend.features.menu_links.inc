<?php
/**
 * @file
 * ding_frontend.features.menu_links.inc
 */

/**
 * Implements hook_menu_default_menu_links().
 */
function ding_frontend_menu_default_menu_links() {
  $menu_links = array();

  // Exported menu link: menu-tabs-menu:<front>
  $menu_links['menu-tabs-menu:<front>'] = array(
    'menu_name' => 'menu-tabs-menu',
    'link_path' => '<front>',
    'router_path' => '',
    'link_title' => 'Menu',
    'options' => array(
      'attributes' => array(
        'title' => '',
      ),
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 1,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -49,
  );
  // Exported menu link: menu-tabs-menu:search
  $menu_links['menu-tabs-menu:search'] = array(
    'menu_name' => 'menu-tabs-menu',
    'link_path' => 'search',
    'router_path' => 'search',
    'link_title' => 'Search',
    'options' => array(
      'attributes' => array(
        'title' => '',
      ),
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -50,
  );
  // Exported menu link: menu-tabs-menu:user
  $menu_links['menu-tabs-menu:user'] = array(
    'menu_name' => 'menu-tabs-menu',
    'link_path' => 'user',
    'router_path' => 'user',
    'link_title' => 'Log in / Create user',
    'options' => array(
      'attributes' => array(
        'title' => '',
      ),
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -48,
  );
  // Exported menu link: menu-tabs-menu:user/logout
  $menu_links['menu-tabs-menu:user/logout'] = array(
    'menu_name' => 'menu-tabs-menu',
    'link_path' => 'user/logout',
    'router_path' => 'user/logout',
    'link_title' => 'Logout',
    'options' => array(
      'attributes' => array(
        'title' => '',
      ),
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -47,
  );
  // Translatables
  // Included for use with string extractors like potx.
  t('Log in / Create user');
  t('Logout');
  t('Menu');
  t('Search');


  return $menu_links;
}
