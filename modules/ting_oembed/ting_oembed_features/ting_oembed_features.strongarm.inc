<?php
/**
 * @file
 * ting_oembed_features.strongarm.inc
 */

/**
 * Implements hook_strongarm().
 */
function ting_oembed_features_strongarm() {
  $export = array();

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'default_oembed_provider';
  $strongarm->value = array(
    'youtube' => TRUE,
    'vimeo' => TRUE,
    'viddler' => TRUE,
    'twitter' => TRUE,
    'soundcloud' => TRUE,
    'smugmug' => TRUE,
    'slideshare' => TRUE,
    'scribd' => TRUE,
    'revision3' => TRUE,
    'qik' => TRUE,
    'flickr' => TRUE,
  );
  $export['default_oembed_provider'] = $strongarm;

  return $export;
}
