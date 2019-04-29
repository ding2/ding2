<?php
/**
 * @file
 * ding_place2book.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function ding_place2book_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_image_default_styles().
 */
function ding_place2book_image_default_styles() {
  $styles = array();

  // Exported image style: ding_place2book_kultunaut_square.
  $styles['ding_place2book_kultunaut_square'] = array(
    'label' => 'ding_place2book_kultunaut_square',
    'effects' => array(
      3 => array(
        'name' => 'image_scale_and_crop',
        'data' => array(
          'width' => 548,
          'height' => 308,
          'upscale' => 1,
        ),
        'weight' => 0,
      ),
    ),
  );

  return $styles;
}
