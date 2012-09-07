<?php

/**
 * @file
 * Theme functions used with the ting search carousel.
 */

/**
 * Implements default preprocess function for the search carsousel.
 */
function template_preprocess_ting_search_carousel(&$vars, $hook) {
  _ting_search_carousel_add_javascript();
  _ting_search_carousel_add_css();

  $vars['toggle_description'] = variable_get('ting_search_carousel_description_toggle', FALSE);
}