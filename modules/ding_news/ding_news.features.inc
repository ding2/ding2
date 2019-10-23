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
    'name' => 'ding_panorama_list_large_wide',
    'label' => 'ding_panorama_list_large_wide',
    'effects' => array(
      22 => array(
        'label' => 'Manual Crop: Reuse cropped style',
        'help' => 'Reuse a crop selection from another Manual Crop enabled image style.',
        'effect callback' => 'manualcrop_reuse_effect',
        'form callback' => 'manualcrop_reuse_form',
        'summary theme' => 'manualcrop_reuse_summary',
        'module' => 'manualcrop',
        'name' => 'manualcrop_reuse',
        'data' => array(
          'reuse_crop_style' => 'crop_22_9',
          'apply_all_effects' => 0,
        ),
        'weight' => 0,
      ),
      23 => array(
        'label' => 'Scale',
        'help' => 'Scaling will maintain the aspect-ratio of the original image. If only a single dimension is specified, the other dimension will be calculated.',
        'effect callback' => 'image_scale_effect',
        'dimensions callback' => 'image_scale_dimensions',
        'form callback' => 'image_scale_form',
        'summary theme' => 'image_scale_summary',
        'module' => 'image',
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
      'description' => t('A content type for news concerning libraries.'),
      'has_title' => '1',
      'title_label' => t('Overskrift'),
      'help' => '',
    ),
  );
  return $items;
}
