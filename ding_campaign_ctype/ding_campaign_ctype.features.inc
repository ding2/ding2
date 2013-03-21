<?php
/**
 * @file
 * ding_campaign_ctype.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function ding_campaign_ctype_ctools_plugin_api() {
  list($module, $api) = func_get_args();
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_image_default_styles().
 */
function ding_campaign_ctype_image_default_styles() {
  $styles = array();

  // Exported image style: ding_campaign_small.
  $styles['ding_campaign_small'] = array(
    'name' => 'ding_campaign_small',
    'effects' => array(
      3 => array(
        'label' => 'Scale',
        'help' => 'Scaling will maintain the aspect-ratio of the original image. If only a single dimension is specified, the other dimension will be calculated.',
        'effect callback' => 'image_scale_effect',
        'dimensions callback' => 'image_scale_dimensions',
        'form callback' => 'image_scale_form',
        'summary theme' => 'image_scale_summary',
        'module' => 'image',
        'name' => 'image_scale',
        'data' => array(
          'width' => '360',
          'height' => '',
          'upscale' => 0,
        ),
        'weight' => '1',
      ),
      4 => array(
        'label' => 'Scale and crop',
        'help' => 'Scale and crop will maintain the aspect-ratio of the original image, then crop the larger dimension. This is most useful for creating perfectly square thumbnails without stretching the image.',
        'effect callback' => 'image_scale_and_crop_effect',
        'dimensions callback' => 'image_resize_dimensions',
        'form callback' => 'image_resize_form',
        'summary theme' => 'image_resize_summary',
        'module' => 'image',
        'name' => 'image_scale_and_crop',
        'data' => array(
          'width' => '360',
          'height' => '240',
        ),
        'weight' => '2',
      ),
    ),
  );

  return $styles;
}

/**
 * Implements hook_node_info().
 */
function ding_campaign_ctype_node_info() {
  $items = array(
    'ding_campaign' => array(
      'name' => t('Campaign'),
      'base' => 'node_content',
      'description' => '',
      'has_title' => '1',
      'title_label' => t('Campaign name'),
      'help' => '',
    ),
  );
  return $items;
}
