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
    'name' => 'ding_panorama_list_large_desaturate',
    'label' => 'ding_panorama_list_large_desaturate',
    'effects' => array(
      24 => array(
        'label' => 'Manual Crop: Reuse cropped style',
        'help' => 'Reuse a crop selection from another Manual Crop enabled image style.',
        'effect callback' => 'manualcrop_reuse_effect',
        'form callback' => 'manualcrop_reuse_form',
        'summary theme' => 'manualcrop_reuse_summary',
        'module' => 'manualcrop',
        'name' => 'manualcrop_reuse',
        'data' => array(
          'reuse_crop_style' => 'crop_16_9',
          'apply_all_effects' => 0,
        ),
        'weight' => 0,
      ),
      25 => array(
        'label' => 'Afmæt',
        'help' => 'Afmæt konverterer et billede til gråtoner.',
        'effect callback' => 'image_desaturate_effect',
        'dimensions passthrough' => TRUE,
        'module' => 'image',
        'name' => 'image_desaturate',
        'data' => array(),
        'weight' => 2,
      ),
      26 => array(
        'label' => 'Skalér',
        'help' => 'Skalering bevarer billedets højde-bredde-forhold. Hvis kun den ene dimension angives vil den anden blive beregnet.',
        'effect callback' => 'image_scale_effect',
        'dimensions callback' => 'image_scale_dimensions',
        'form callback' => 'image_scale_form',
        'summary theme' => 'image_scale_summary',
        'module' => 'image',
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
      'name' => t('Temaside'),
      'base' => 'node_content',
      'description' => t('Create and new group that can be used to group related content together (temapages)'),
      'has_title' => '1',
      'title_label' => t('titel'),
      'help' => '',
    ),
  );
  return $items;
}
