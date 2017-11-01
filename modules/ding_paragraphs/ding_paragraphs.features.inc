<?php
/**
 * @file
 * ding_paragraphs.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function ding_paragraphs_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "field_group" && $api == "field_group") {
    return array("version" => "1");
  }
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_paragraphs_info().
 */
function ding_paragraphs_paragraphs_info() {
  $items = array(
    'ding_paragraphs_image' => array(
      'name' => 'Image paragraph',
      'bundle' => 'ding_paragraphs_image',
      'locked' => '1',
    ),
    'ding_paragraphs_image_and_text' => array(
      'name' => 'Image and text paragraph',
      'bundle' => 'ding_paragraphs_image_and_text',
      'locked' => '1',
    ),
    'ding_paragraphs_text' => array(
      'name' => 'Text paragraph',
      'bundle' => 'ding_paragraphs_text',
      'locked' => '1',
    ),
    'ding_paragraphs_text_box' => array(
      'name' => 'Text box paragraph',
      'bundle' => 'ding_paragraphs_text_box',
      'locked' => '1',
    ),
  );
  return $items;
}
