<?php
/**
 * @file
 * ding_staff.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function ding_staff_ctools_plugin_api($module = NULL, $api = NULL) {
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
function ding_staff_views_api($module = NULL, $api = NULL) {
  return array("api" => "3.0");
}

/**
 * Implements hook_image_default_styles().
 */
function ding_staff_image_default_styles() {
  $styles = array();

  // Exported image style: ding_staff_thumbnail.
  $styles['ding_staff_thumbnail'] = array(
    'name' => 'ding_staff_thumbnail',
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
          'width' => 60,
          'height' => 60,
        ),
        'weight' => 1,
      ),
    ),
    'label' => 'ding_staff_thumbnail',
  );

  return $styles;
}

/**
 * Implements hook_default_profile2_type().
 */
function ding_staff_default_profile2_type() {
  $items = array();
  $items['ding_staff_profile'] = entity_import('profile2_type', '{
    "userCategory" : true,
    "userView" : true,
    "type" : "ding_staff_profile",
    "label" : "Staff",
    "weight" : "0",
    "data" : { "registration" : 0, "use_page" : 0 }
  }');
  return $items;
}
