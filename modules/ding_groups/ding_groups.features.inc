<?php
/**
 * @file
 * ding_groups.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function ding_groups_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "field_group" && $api == "field_group") {
    return array("version" => "1");
  }
  if ($module == "page_manager" && $api == "pages_default") {
    return array("version" => "1");
  }
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_views_api().
 */
function ding_groups_views_api($module = NULL, $api = NULL) {
  return array("api" => "3.0");
}

/**
 * Implements hook_image_default_styles().
 */
function ding_groups_image_default_styles() {
  $styles = array();

  // Exported image style: ding_panorama_list_large_desaturate.
  $styles['ding_panorama_list_large_desaturate'] = array(
    'label' => 'ding_panorama_list_large_desaturate',
    'effects' => array(
      24 => array(
        'name' => 'manualcrop_reuse',
        'data' => array(
          'reuse_crop_style' => 'crop_16_9',
          'apply_all_effects' => 0,
        ),
        'weight' => 0,
      ),
      25 => array(
        'name' => 'image_desaturate',
        'data' => array(),
        'weight' => 2,
      ),
      26 => array(
        'name' => 'image_scale',
        'data' => array(
          'width' => 548,
          'height' => 308,
          'upscale' => 1,
        ),
        'weight' => 3,
      ),
    ),
  );

  return $styles;
}

/**
 * Implements hook_node_info().
 */
function ding_groups_node_info() {
  $items = array(
    'ding_group' => array(
      'name' => t('Groups'),
      'base' => 'node_content',
      'description' => t('Create and new group that can be used to group related content together (temapages)'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
  );
  drupal_alter('node_info', $items);
  return $items;
}
