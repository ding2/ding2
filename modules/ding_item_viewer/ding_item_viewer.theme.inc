<?php
/**
 *
 */

function template_preprocess_ding_item_viewer(&$vars, $hook) {
  drupal_add_css(DING_ITEM_VIEWER_MODULE_PATH . '/css/ding_item_viewer.css');
  drupal_add_css(DING_ITEM_VIEWER_MODULE_PATH . '/css/ding_item_viewer_screen.css');
  drupal_add_css(DING_ITEM_VIEWER_MODULE_PATH . '/css/slick.css');
  drupal_add_css(DING_ITEM_VIEWER_MODULE_PATH . '/css/slick-theme.css');

  drupal_add_js(DING_ITEM_VIEWER_MODULE_PATH . '/js/slick.min.js');
  drupal_add_js(DING_ITEM_VIEWER_MODULE_PATH . '/js/ding_item_viewer.js');
}
