<?php
/**
 * @file
 * ding_example_content.features.menu_links.inc
 */

/**
 * Implements hook_menu_default_menu_links().
 */
function ding_example_content_menu_default_menu_links() {
  $menu_links = array();

  // Exported menu link: main-menu:<front>
  $menu_links['main-menu:<front>'] = array(
    'menu_name' => 'main-menu',
    'link_path' => '<front>',
    'router_path' => '',
    'link_title' => 'Forsiden',
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
    'weight' => -36,
  );
  // Exported menu link: menu-footer-menu-1:<front>
  $menu_links['menu-footer-menu-1:<front>'] = array(
    'menu_name' => 'menu-footer-menu-1',
    'link_path' => '<front>',
    'router_path' => '',
    'link_title' => 'Test I',
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
    'weight' => 0,
  );
  // Exported menu link: menu-footer-menu-2:<front>
  $menu_links['menu-footer-menu-2:<front>'] = array(
    'menu_name' => 'menu-footer-menu-2',
    'link_path' => '<front>',
    'router_path' => '',
    'link_title' => 'Test II',
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
    'weight' => 0,
  );
  // Exported menu link: menu-footer-menu-3:<front>
  $menu_links['menu-footer-menu-3:<front>'] = array(
    'menu_name' => 'menu-footer-menu-3',
    'link_path' => '<front>',
    'router_path' => '',
    'link_title' => 'Test III',
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
    'weight' => 0,
  );
  // Exported menu link: menu-footer-menu-4:<front>
  $menu_links['menu-footer-menu-4:<front>'] = array(
    'menu_name' => 'menu-footer-menu-4',
    'link_path' => '<front>',
    'router_path' => '',
    'link_title' => 'Test IIII',
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
    'weight' => 0,
  );

  // Translatables
  // Included for use with string extractors like potx.
  t('Forsiden');
  t('Test I');
  t('Test II');
  t('Test III');
  t('Test IIII');

  return $menu_links;
}
