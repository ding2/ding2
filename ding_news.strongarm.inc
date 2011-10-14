<?php
/**
 * @file
 * ding_news.strongarm.inc
 */

/**
 * Implements hook_strongarm().
 */
function ding_news_strongarm() {
  $export = array();

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'language_content_type_ding_news';
  $strongarm->value = '0';
  $export['language_content_type_ding_news'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'node_options_ding_news';
  $strongarm->value = array(
    0 => 'status',
  );
  $export['node_options_ding_news'] = $strongarm;

  return $export;
}
