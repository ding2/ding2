<?php
/**
 * @file
 * ting_new_materials.features.inc
 */


/**
 * Implements hook_node_info().
 */
function ting_new_materials_node_info() {
  $items = array(
    'new_materials' => array(
      'name' => t('New Materials'),
      'base' => 'node_content',
      'description' => '',
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
  );
  return $items;
}
