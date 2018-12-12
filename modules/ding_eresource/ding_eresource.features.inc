<?php
/**
 * @file
 * ding_eresource.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function ding_eresource_ctools_plugin_api($module = NULL, $api = NULL) {
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
function ding_eresource_views_api($module = NULL, $api = NULL) {
  return array("api" => "3.0");
}

/**
 * Implements hook_image_default_styles().
 */
function ding_eresource_image_default_styles() {
  $styles = array();

  // Exported image style: ding_eresource_list.
  $styles['ding_eresource_list'] = array(
    'label' => 'Ding eresource list',
    'effects' => array(
      7 => array(
        'name' => 'manualcrop_reuse',
        'data' => array(
          'reuse_crop_style' => 'crop_4_3',
          'apply_all_effects' => 0,
        ),
        'weight' => 0,
      ),
      8 => array(
        'name' => 'image_scale_and_crop',
        'data' => array(
          'width' => 150,
          'height' => 112,
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
function ding_eresource_node_info() {
  $items = array(
    'ding_eresource' => array(
      'name' => t('E-resource'),
      'base' => 'node_content',
      'description' => '',
      'has_title' => '1',
      'title_label' => t('titel'),
      'help' => '',
    ),
  );
  drupal_alter('node_info', $items);
  return $items;
}
