<?php
/**
 * @file
 * ding_groups.features.menu_links.inc
 */

/**
 * Implements hook_menu_default_menu_links().
 */
function ding_groups_menu_default_menu_links() {
  $menu_links = array();

  // Exported menu link: main-menu:menu-position/3
  $menu_links['main-menu:menu-position/3'] = array(
    'menu_name' => 'main-menu',
    'link_path' => 'menu-position/3',
    'router_path' => 'menu-position/%',
    'link_title' => 'Groups (menu position rule)',
    'options' => array(
      'alter' => TRUE,
      'attributes' => array(
        'class' => array(
          0 => 'menu-position-link',
        ),
      ),
    ),
    'module' => 'menu_position',
    'hidden' => 1,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => 0,
    'parent_path' => 'grupper',
  );
  // Translatables
  // Included for use with string extractors like potx.
  t('Groups (menu position rule)');


  return $menu_links;
}
