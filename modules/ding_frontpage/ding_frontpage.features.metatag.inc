<?php
/**
 * @file
 * ding_frontpage.features.metatag.inc
 */

/**
 * Implements hook_metatag_export_default().
 */
function ding_frontpage_metatag_export_default() {
  $config = array();

  // Exported Metatag config instance: global:frontpage.
  $config['global:frontpage'] = array(
    'instance' => 'global:frontpage',
    'disabled' => FALSE,
    'config' => array(
      'title' => array(
        'value' => '[site:name]',
      ),
      'canonical' => array(
        'value' => '[site:url]',
      ),
      'shortlink' => array(
        'value' => '[site:url]',
      ),
    ),
  );

  return $config;
}
