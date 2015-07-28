<?php
/**
 * @file
 * ding_tabroll.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function ding_tabroll_ctools_plugin_api() {
  list($module, $api) = func_get_args();
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_views_api().
 */
function ding_tabroll_views_api() {
  return array("api" => "3.0");
}

/**
 * Implements hook_image_default_styles().
 */
function ding_tabroll_image_default_styles() {
  $styles = array();

  // Exported image style: ding_tabroll_large.
  $styles['ding_tabroll_large'] = array(
    'name' => 'ding_tabroll_large',
    'effects' => array(
      1 => array(
        'label' => 'Scale and crop',
        'help' => 'Scale and crop will maintain the aspect-ratio of the original image, then crop the larger dimension. This is most useful for creating perfectly square thumbnails without stretching the image.',
        'effect callback' => 'image_scale_and_crop_effect',
        'dimensions callback' => 'image_resize_dimensions',
        'form callback' => 'image_resize_form',
        'summary theme' => 'image_resize_summary',
        'module' => 'image',
        'name' => 'image_scale_and_crop',
        'data' => array(
          'width' => 1200,
          'height' => 400,
        ),
        'weight' => 1,
      ),
    ),
    'label' => 'ding_tabroll_large',
  );

  // Exported image style: ding_tabroll_medium.
  $styles['ding_tabroll_medium'] = array(
    'name' => 'ding_tabroll_medium',
    'effects' => array(
      2 => array(
        'label' => 'Scale and crop',
        'help' => 'Scale and crop will maintain the aspect-ratio of the original image, then crop the larger dimension. This is most useful for creating perfectly square thumbnails without stretching the image.',
        'effect callback' => 'image_scale_and_crop_effect',
        'dimensions callback' => 'image_resize_dimensions',
        'form callback' => 'image_resize_form',
        'summary theme' => 'image_resize_summary',
        'module' => 'image',
        'name' => 'image_scale_and_crop',
        'data' => array(
          'width' => 900,
          'height' => 300,
        ),
        'weight' => 1,
      ),
    ),
    'label' => 'ding_tabroll_medium',
  );

  // Exported image style: ding_tabroll_small.
  $styles['ding_tabroll_small'] = array(
    'name' => 'ding_tabroll_small',
    'effects' => array(
      3 => array(
        'label' => 'Scale and crop',
        'help' => 'Scale and crop will maintain the aspect-ratio of the original image, then crop the larger dimension. This is most useful for creating perfectly square thumbnails without stretching the image.',
        'effect callback' => 'image_scale_and_crop_effect',
        'dimensions callback' => 'image_resize_dimensions',
        'form callback' => 'image_resize_form',
        'summary theme' => 'image_resize_summary',
        'module' => 'image',
        'name' => 'image_scale_and_crop',
        'data' => array(
          'width' => 450,
          'height' => 150,
        ),
        'weight' => 1,
      ),
    ),
    'label' => 'ding_tabroll_small',
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
  return $items;
}
