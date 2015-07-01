<?php

/**
 * @file
 * Theme functions used with the ting search context.
 */

/**
 * Implements default preprocess function for the search context content.
 */
function template_preprocess_ting_search_context(&$vars, $hook) {
  // Add Javascript settings
  drupal_add_js(array('ting_search_context' => $vars[context]), 'setting');
  drupal_add_js(array('ting_search_context_position' => $vars[position]), 'setting');

  // Add JavaScript and CSS using wrapper functions.
  _ting_search_context_add_javascript();
  _ting_search_context_add_css();
}
