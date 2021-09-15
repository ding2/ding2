<?php
/**
 * @file
 * test.features.metatag.inc
 */

/**
 * Implements hook_metatag_export_default().
 */
function ding_event_metatag_export_default() {
  $config = array();

  // Exported Metatag config instance: node:ding_event.
  $config['node:ding_event'] = array(
    'instance' => 'node:ding_event',
    'config' => array(
      'og:type' => array(
        'value' => 'website',
      ),
      'og:description' => array(
        'value' => '[node:field_ding_event_lead]',
      ),
      'og:image' => array(
        'value' => '[node:field_ding_event_title_image]',
      ),
      'og:image:width' => array(
        'value' => 904,
      ),
    ),
  );

  return $config;
}
