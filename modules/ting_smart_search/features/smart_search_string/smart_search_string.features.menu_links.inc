<?php
/**
 * @file
 * smart_search_string.features.menu_links.inc
 */

/**
 * Implements hook_menu_default_menu_links().
 */
function smart_search_string_menu_default_menu_links() {
  $menu_links = array();

  // Exported menu link: management_smartsearchstring:admin/structure/entity-type/ting_type/smart_search_string.
  $menu_links['management_smartsearchstring:admin/structure/entity-type/ting_type/smart_search_string'] = array(
    'menu_name' => 'management',
    'link_path' => 'admin/structure/entity-type/ting_type/smart_search_string',
    'router_path' => 'admin/structure/entity-type/ting_type/smart_search_string',
    'link_title' => 'smart_search_string',
    'options' => array(
      'attributes' => array(
        'title' => 'View all entites of type ting_type with bundle smart_search_string',
      ),
      'identifier' => 'management_smartsearchstring:admin/structure/entity-type/ting_type/smart_search_string',
    ),
    'module' => 'system',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 1,
    'expanded' => 0,
    'weight' => 0,
    'customized' => 0,
    'parent_identifier' => 'management_tingtype:admin/structure/entity-type/ting_type',
  );
  // Exported menu link: management_ting-smart-search:admin/config/ding/ting_smart_search.
  $menu_links['management_ting-smart-search:admin/config/ding/ting_smart_search'] = array(
    'menu_name' => 'management',
    'link_path' => 'admin/config/ding/ting_smart_search',
    'router_path' => 'admin/config/ding/ting_smart_search',
    'link_title' => 'Ting smart search',
    'options' => array(
      'attributes' => array(
        'title' => 'Manage smart search module',
      ),
      'identifier' => 'management_ting-smart-search:admin/config/ding/ting_smart_search',
    ),
    'module' => 'system',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => 0,
    'customized' => 0,
    'parent_identifier' => 'management_ding:admin/config/ding',
  );
  // Exported menu link: management_tingtype:admin/structure/entity-type/ting_type.
  $menu_links['management_tingtype:admin/structure/entity-type/ting_type'] = array(
    'menu_name' => 'management',
    'link_path' => 'admin/structure/entity-type/ting_type',
    'router_path' => 'admin/structure/entity-type/ting_type',
    'link_title' => 'ting_type',
    'options' => array(
      'attributes' => array(
        'title' => 'View all the bundles for \'ting_type\'',
      ),
      'identifier' => 'management_tingtype:admin/structure/entity-type/ting_type',
    ),
    'module' => 'system',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 1,
    'expanded' => 0,
    'weight' => 0,
    'customized' => 0,
    'parent_identifier' => 'management_entity-types:admin/structure/entity-type',
  );

  // Translatables
  // Included for use with string extractors like potx.
  t('Ting smart search');
  t('smart_search_string');
  t('ting_type');

  return $menu_links;
}
