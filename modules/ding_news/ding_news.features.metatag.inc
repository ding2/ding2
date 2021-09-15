<?php
/**
 * @file
 * test.features.metatag.inc
 */

/**
 * Implements hook_metatag_export_default().
 */
function ding_news_metatag_export_default() {
  $config = array();

  // Exported Metatag config instance: node:ding_news.
  $config['node:ding_news'] = array(
    'instance' => 'node:ding_news',
    'config' => array(
      'og:type' => array(
        'value' => 'website',
      ),
      'og:description' => array(
        'value' => '[node:field_ding_news_lead]',
      ),
      'og:image' => array(
        'value' => '[node:field_ding_news_title_image]',
      ),
      'og:image:width' => array(
        'value' => 904,
      ),
    ),
  );

  return $config;
}
