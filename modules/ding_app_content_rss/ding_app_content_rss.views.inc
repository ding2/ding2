<?php

/**
 * @file
 * Views definitions for 'ding_app_content_rss'.
 */

/**
 * Implements hook_views_data().
 */
function ding_app_content_rss_views_data() {
  $data = array();
  // Add Ding App Content RSS group.
  $data['ding_app_content_rss']['table']['group'] = t('Ding App Content RSS');
  $data['ding_app_content_rss']['table']['join'] = array(
    '#global' => array(),
  );

  // Add library id field.
  $data['ding_app_content_rss']['ding_app_content_rss_handler_library_id'] = array(
    'title' => t('Library ID'),
    'help' => t("Provides a node's library id."),
    'field' => array(
      'handler' => 'ding_app_content_rss_handler_library_id',
    ),
  );

  return $data;
}
