<?php
/**
 * @file
 * ding_news.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function ding_news_ctools_plugin_api($module = NULL, $api = NULL) {
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
function ding_news_views_api($module = NULL, $api = NULL) {
  return array("api" => "3.0");
}

/**
 * Implements hook_image_default_styles().
 */
function ding_news_image_default_styles() {
  $styles = array();

  // Exported image style: ding_panorama_list_large_wide.
  $styles['ding_panorama_list_large_wide'] = array(
    'label' => 'ding_panorama_list_large_wide',
    'effects' => array(
      22 => array(
        'name' => 'manualcrop_reuse',
        'data' => array(
          'reuse_crop_style' => 'crop_22_9',
          'apply_all_effects' => 0,
        ),
        'weight' => 0,
      ),
      23 => array(
        'name' => 'image_scale',
        'data' => array(
          'width' => 740,
          'height' => 471,
          'upscale' => 1,
        ),
        'weight' => 2,
      ),
    ),
  );

  return $styles;
}

/**
 * Implements hook_node_info().
 */
function ding_news_node_info() {
  $items = array(
    'ding_news' => array(
      'name' => t('Nyhed'),
      'base' => 'node_content',
      'description' => t('Nyheder er en indholdstyper der kan tilføjes til forsiden, den generelle nyhedsliste eller de enkelte bibliotekers nyhedslister.'),
      'has_title' => '1',
      'title_label' => t('Overskrift'),
      'help' => '',
    ),
  );
  drupal_alter('node_info', $items);
  return $items;
}
