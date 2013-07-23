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

  // Exported menu link: main-menu:node/11
  $menu_links['main-menu:node/11'] = array(
    'menu_name' => 'main-menu',
    'link_path' => 'node/11',
    'router_path' => 'node/%',
    'link_title' => 'Vejledninger',
    'options' => array(),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 1,
    'expanded' => 0,
    'weight' => 0,
    'parent_path' => 'node/9',
  );
  // Exported menu link: main-menu:node/12
  $menu_links['main-menu:node/12'] = array(
    'menu_name' => 'main-menu',
    'link_path' => 'node/12',
    'router_path' => 'node/%',
    'link_title' => 'Spørgsmål og svar',
    'options' => array(),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 1,
    'expanded' => 0,
    'weight' => -50,
    'parent_path' => 'node/11',
  );
  // Exported menu link: main-menu:node/14
  $menu_links['main-menu:node/14'] = array(
    'menu_name' => 'main-menu',
    'link_path' => 'node/14',
    'router_path' => 'node/%',
    'link_title' => 'Lån et lokale',
    'options' => array(),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => 0,
    'parent_path' => 'node/9',
  );
  // Exported menu link: main-menu:node/9
  $menu_links['main-menu:node/9'] = array(
    'menu_name' => 'main-menu',
    'link_path' => 'node/9',
    'router_path' => 'node/%',
    'link_title' => 'Det kan du',
    'options' => array(),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 1,
    'expanded' => 0,
    'weight' => 3,
  );
  // Exported menu link: menu-footer-menu-1:http://bibliotek.dk/
  $menu_links['menu-footer-menu-1:http://bibliotek.dk/'] = array(
    'menu_name' => 'menu-footer-menu-1',
    'link_path' => 'http://bibliotek.dk/',
    'router_path' => '',
    'link_title' => 'Bibliotek.dk',
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
  // Exported menu link: menu-footer-menu-1:http://bibliotek.dk/artikel.php
  $menu_links['menu-footer-menu-1:http://bibliotek.dk/artikel.php'] = array(
    'menu_name' => 'menu-footer-menu-1',
    'link_path' => 'http://bibliotek.dk/artikel.php',
    'router_path' => '',
    'link_title' => 'Artikelsøgning',
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
    'weight' => -50,
  );
  // Exported menu link: menu-footer-menu-1:http://www.filmstriben.dk/fjernleje/
  $menu_links['menu-footer-menu-1:http://www.filmstriben.dk/fjernleje/'] = array(
    'menu_name' => 'menu-footer-menu-1',
    'link_path' => 'http://www.filmstriben.dk/fjernleje/',
    'router_path' => '',
    'link_title' => 'Filmstriben',
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
    'weight' => -47,
  );
  // Exported menu link: menu-footer-menu-1:http://www.litteratursiden.dk/
  $menu_links['menu-footer-menu-1:http://www.litteratursiden.dk/'] = array(
    'menu_name' => 'menu-footer-menu-1',
    'link_path' => 'http://www.litteratursiden.dk/',
    'router_path' => '',
    'link_title' => 'Litteratursiden',
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
    'weight' => -46,
  );
  // Exported menu link: menu-footer-menu-1:https://ereolen.dk/
  $menu_links['menu-footer-menu-1:https://ereolen.dk/'] = array(
    'menu_name' => 'menu-footer-menu-1',
    'link_path' => 'https://ereolen.dk/',
    'router_path' => '',
    'link_title' => 'eReolen',
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
    'weight' => -48,
  );
  // Exported menu link: menu-footer-menu-1:https://netlydbog.dk/
  $menu_links['menu-footer-menu-1:https://netlydbog.dk/'] = array(
    'menu_name' => 'menu-footer-menu-1',
    'link_path' => 'https://netlydbog.dk/',
    'router_path' => '',
    'link_title' => 'Netlydbog',
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
  // Exported menu link: menu-footer-menu-2:https://www.borger.dk/Sider/default.aspx
  $menu_links['menu-footer-menu-2:https://www.borger.dk/Sider/default.aspx'] = array(
    'menu_name' => 'menu-footer-menu-2',
    'link_path' => 'https://www.borger.dk/Sider/default.aspx',
    'router_path' => '',
    'link_title' => 'Borger.dk',
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
    'weight' => -50,
  );
  // Exported menu link: menu-footer-menu-3:http://ding2tal.ting.dk/node/85
  $menu_links['menu-footer-menu-3:http://ding2tal.ting.dk/node/85'] = array(
    'menu_name' => 'menu-footer-menu-3',
    'link_path' => 'http://ding2tal.ting.dk/node/85',
    'router_path' => '',
    'link_title' => 'Biblioteket i lommen',
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
  // Exported menu link: menu-footer-menu-4:http://ding2tal.ting.dk/node/88
  $menu_links['menu-footer-menu-4:http://ding2tal.ting.dk/node/88'] = array(
    'menu_name' => 'menu-footer-menu-4',
    'link_path' => 'http://ding2tal.ting.dk/node/88',
    'router_path' => '',
    'link_title' => 'Hjemmesiden',
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
  t('Artikelsøgning');
  t('Bibliotek.dk');
  t('Biblioteket i lommen');
  t('Borger.dk');
  t('Det kan du');
  t('Filmstriben');
  t('Hjemmesiden');
  t('Litteratursiden');
  t('Lån et lokale');
  t('Netlydbog');
  t('Spørgsmål og svar');
  t('Vejledninger');
  t('eReolen');


  return $menu_links;
}
