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

  // Exported menu link: menu-tabs-menu_login:user
  $menu_links['menu-tabs-menu_login:user'] = array(
    'menu_name' => 'menu-tabs-menu',
    'link_path' => 'user',
    'router_path' => 'user',
    'link_title' => 'Login',
    'options' => array(
      'attributes' => array(
        'title' => '',
      ),
      'identifier' => 'menu-tabs-menu_login:user',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -47,
    'customized' => 1,
  );
  // Exported menu link: menu-tabs-menu_logout:user/logout
  $menu_links['menu-tabs-menu_logout:user/logout'] = array(
    'menu_name' => 'menu-tabs-menu',
    'link_path' => 'user/logout',
    'router_path' => 'user/logout',
    'link_title' => 'Logout',
    'options' => array(
      'attributes' => array(
        'title' => '',
      ),
      'identifier' => 'menu-tabs-menu_logout:user/logout',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -45,
    'customized' => 1,
  );
  // Exported menu link: menu-tabs-menu_menu:<front>
  $menu_links['menu-tabs-menu_menu:<front>'] = array(
    'menu_name' => 'menu-tabs-menu',
    'link_path' => '<front>',
    'router_path' => '',
    'link_title' => 'Menu',
    'options' => array(
      'attributes' => array(
        'title' => '',
      ),
      'identifier' => 'menu-tabs-menu_menu:<front>',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 1,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -49,
    'customized' => 0,
  );
  // Exported menu link: menu-tabs-menu_opening-hours:libraries
  $menu_links['menu-tabs-menu_opening-hours:libraries'] = array(
    'menu_name' => 'menu-tabs-menu',
    'link_path' => 'libraries',
    'router_path' => 'libraries',
    'link_title' => 'Opening hours',
    'options' => array(
      'attributes' => array(
        'title' => '',
      ),
      'identifier' => 'menu-tabs-menu_opening-hours:libraries',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -48,
    'customized' => 1,
  );
  // Exported menu link: menu-tabs-menu_search:search
  $menu_links['menu-tabs-menu_search:search'] = array(
    'menu_name' => 'menu-tabs-menu',
    'link_path' => 'search',
    'router_path' => 'search',
    'link_title' => 'Search',
    'options' => array(
      'attributes' => array(
        'title' => '',
      ),
      'identifier' => 'menu-tabs-menu_search:search',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -50,
    'customized' => 0,
  );
  // Exported menu link: menu-tabs-menu_user-menu-mobile:node
  $menu_links['menu-tabs-menu_user-menu-mobile:node'] = array(
    'menu_name' => 'menu-tabs-menu',
    'link_path' => 'node',
    'router_path' => 'node',
    'link_title' => 'User menu (mobile)',
    'options' => array(
      'attributes' => array(
        'title' => '',
      ),
      'identifier' => 'menu-tabs-menu_user-menu-mobile:node',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -46,
    'customized' => 1,
  );
  // Translatables
  // Included for use with string extractors like potx.
  t('Login');
  t('Logout');
  t('Menu');
  t('Opening hours');
  t('Search');
  t('User menu (mobile)');


  return $menu_links;
}
