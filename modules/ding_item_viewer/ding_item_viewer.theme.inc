<?php
/**
 * @file
 * Theme functionality for ding item viewer.
 */

/**
 * Implements hook_preprocess_hook().
 */
function template_preprocess_ding_item_viewer(&$vars, $hook) {
  drupal_add_css(DING_ITEM_VIEWER_MODULE_PATH . '/css/ding_item_viewer.css');
  drupal_add_css(DING_ITEM_VIEWER_MODULE_PATH . '/css/ding_item_viewer_screen.css');

  drupal_add_js(DING_ITEM_VIEWER_MODULE_PATH . '/js/ding_item_viewer.js');
}
