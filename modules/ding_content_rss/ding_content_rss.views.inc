<?php

/**
 * @file
 * Views definitions for 'ding_content_rss'.
 */

/**
 * Implements hook_views_data().
 */
function ding_content_rss_views_data() {
  $data = array();
  // Add Ding Content RSS group.
  $data['ding_content_rss']['table']['group'] = t('Ding Content RSS');
  $data['ding_content_rss']['table']['join'] = array(
    '#global' => array(),
  );

  // Add library id field.
  $data['ding_content_rss']['ding_content_rss_handler_library_id'] = array(
    'title' => t('Library ID'),
    'help' => t("Provides a node's library id."),
    'field' => array(
      'handler' => 'ding_content_rss_handler_library_id',
    ),
  );

  return $data;
}
