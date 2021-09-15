<?php
/**
 * @file
 * test.features.metatag.inc
 */

/**
 * Implements hook_metatag_export_default().
 */
function ding_page_metatag_export_default() {
  $config = array();

   // Exported Metatag config instance: node:ding_page.
   $config['node:ding_page'] = array(
    'instance' => 'node:ding_page',
    'config' => array(
      'og:type' => array(
        'value' => 'website',
      ),
      'og:description' => array(
        'value' => '[node:field_ding_page_lead]',
      ),
      'og:image' => array(
        'value' => '[node:field_ding_page_title_image]',
      ),
      'og:image:width' => array(
        'value' => 1480,
      ),
      'og:image:height' => array(
        'value' => 370,
      ),
    ),
  );

  return $config;
}
