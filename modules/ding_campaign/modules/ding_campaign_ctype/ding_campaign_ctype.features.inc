<?php
/**
 * @file
 * ding_campaign_ctype.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function ding_campaign_ctype_ctools_plugin_api($module = NULL, $api = NULL) {
  list($module, $api) = func_get_args();
  if ($module == "field_group" && $api == "field_group") {
    return array("version" => "1");
  }
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_image_default_styles().
 */
function ding_campaign_ctype_image_default_styles() {
  $styles = array();

  // Exported image style: ding_campaign_w_180.
  $styles['ding_campaign_w_180'] = array(
    'name' => 'ding_campaign_w_180',
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
          'width' => 180,
          'height' => '',
          'upscale' => 1,
        ),
        'weight' => 1,
      ),
    ),
    'label' => 'ding_campaign_w_180',
  );

  // Exported image style: ding_campaign_w_280.
  $styles['ding_campaign_w_280'] = array(
    'name' => 'ding_campaign_w_280',
    'effects' => array(
      4 => array(
        'label' => 'Scale',
        'help' => 'Scaling will maintain the aspect-ratio of the original image. If only a single dimension is specified, the other dimension will be calculated.',
        'effect callback' => 'image_scale_effect',
        'dimensions callback' => 'image_scale_dimensions',
        'form callback' => 'image_scale_form',
        'summary theme' => 'image_scale_summary',
        'module' => 'image',
        'name' => 'image_scale',
        'data' => array(
          'width' => 280,
          'height' => '',
          'upscale' => 1,
        ),
        'weight' => 1,
      ),
    ),
    'label' => 'ding_campaign_w_280',
  );

  // Exported image style: ding_campaign_w_380.
  $styles['ding_campaign_w_380'] = array(
    'name' => 'ding_campaign_w_380',
    'effects' => array(
      5 => array(
        'label' => 'Scale',
        'help' => 'Scaling will maintain the aspect-ratio of the original image. If only a single dimension is specified, the other dimension will be calculated.',
        'effect callback' => 'image_scale_effect',
        'dimensions callback' => 'image_scale_dimensions',
        'form callback' => 'image_scale_form',
        'summary theme' => 'image_scale_summary',
        'module' => 'image',
        'name' => 'image_scale',
        'data' => array(
          'width' => 380,
          'height' => '',
          'upscale' => 1,
        ),
        'weight' => 1,
      ),
    ),
    'label' => 'ding_campaign_w_380',
  );

  // Exported image style: ding_campaign_w_480.
  $styles['ding_campaign_w_480'] = array(
    'name' => 'ding_campaign_w_480',
    'effects' => array(
      6 => array(
        'label' => 'Scale',
        'help' => 'Scaling will maintain the aspect-ratio of the original image. If only a single dimension is specified, the other dimension will be calculated.',
        'effect callback' => 'image_scale_effect',
        'dimensions callback' => 'image_scale_dimensions',
        'form callback' => 'image_scale_form',
        'summary theme' => 'image_scale_summary',
        'module' => 'image',
        'name' => 'image_scale',
        'data' => array(
          'width' => 480,
          'height' => '',
          'upscale' => 1,
        ),
        'weight' => 1,
      ),
    ),
    'label' => 'ding_campaign_w_480',
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
      'description' => t('Create a new campaign that based on different rules will be shown in a given context on the site.'),
      'has_title' => '1',
      'title_label' => t('Campaign name'),
      'help' => '',
    ),
  );
  return $items;
}
