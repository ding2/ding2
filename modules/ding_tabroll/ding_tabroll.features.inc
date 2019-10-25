<?php
/**
 * @file
 * ding_tabroll.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function ding_tabroll_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_views_api().
 */
function ding_tabroll_views_api($module = NULL, $api = NULL) {
  return array("api" => "3.0");
}

/**
 * Implements hook_image_default_styles().
 */
function ding_tabroll_image_default_styles() {
  $styles = array();

  // Exported image style: crop_3_1.
  $styles['crop_3_1'] = array(
    'label' => 'Crop 3:1',
    'effects' => array(
      29 => array(
        'name' => 'manualcrop_crop',
        'data' => array(
          'width' => 1124,
          'height' => 375,
          'keepproportions' => 1,
          'reuse_crop_style' => '',
          'style_name' => 'crop_3_1',
        ),
        'weight' => 0,
      ),
    ),
  );

  // Exported image style: ding_tabroll_large.
  $styles['ding_tabroll_large'] = array(
    'label' => 'ding_tabroll_large',
    'effects' => array(
      32 => array(
        'name' => 'manualcrop_reuse',
        'data' => array(
          'reuse_crop_style' => 'crop_3_1',
          'apply_all_effects' => 0,
        ),
        'weight' => 0,
      ),
      31 => array(
        'name' => 'image_scale_and_crop',
        'data' => array(
          'width' => 1124,
          'height' => 375,
        ),
        'weight' => 1,
      ),
    ),
  );

  // Exported image style: ding_tabroll_medium.
  $styles['ding_tabroll_medium'] = array(
    'label' => 'ding_tabroll_medium',
    'effects' => array(
      48 => array(
        'name' => 'manualcrop_reuse',
        'data' => array(
          'reuse_crop_style' => 'ding_tabroll_large',
          'apply_all_effects' => 1,
        ),
        'weight' => 0,
      ),
      47 => array(
        'name' => 'image_scale_and_crop',
        'data' => array(
          'width' => 900,
          'height' => 300,
        ),
        'weight' => 1,
      ),
    ),
  );

  // Exported image style: ding_tabroll_small.
  $styles['ding_tabroll_small'] = array(
    'label' => 'ding_tabroll_small',
    'effects' => array(
      50 => array(
        'name' => 'manualcrop_reuse',
        'data' => array(
          'reuse_crop_style' => 'ding_tabroll_large',
          'apply_all_effects' => 1,
        ),
        'weight' => 0,
      ),
      49 => array(
        'name' => 'image_scale_and_crop',
        'data' => array(
          'width' => 450,
          'height' => 150,
        ),
        'weight' => 1,
      ),
    ),
  );

  return $styles;
}

/**
 * Implements hook_node_info().
 */
function ding_tabroll_node_info() {
  $items = array(
    'ding_rolltab' => array(
      'name' => t('Rolltab'),
      'base' => 'node_content',
      'description' => t('Rolltabs are shown in a Tabroll, where each rolltab slide into the next in a carousel.'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
  );
  drupal_alter('node_info', $items);
  return $items;
}
