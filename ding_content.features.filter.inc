<?php
/**
 * @file
 * ding_content.features.filter.inc
 */

/**
 * Implements hook_filter_default_formats().
 */
function ding_content_filter_default_formats() {
  $formats = array();

  // Exported format: Wysiwyg.
  $formats['ding_wysiwyg'] = array(
    'format' => 'ding_wysiwyg',
    'name' => 'Wysiwyg',
    'cache' => 1,
    'status' => 1,
    'weight' => 0,
    'filters' => array(
      'media_filter' => array(
        'weight' => 2,
        'status' => 1,
        'settings' => array(),
      ),
      'filter_htmlcorrector' => array(
        'weight' => 10,
        'status' => 1,
        'settings' => array(),
      ),
    ),
  );

  return $formats;
}
