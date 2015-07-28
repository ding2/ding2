<?php

/**
 * @file
 * Theme functions used with the ting search carousel.
 */

/**
 * Implements default preprocess function for the search carsousel.
 */
function template_preprocess_ting_search_carousel(&$vars, $hook) {
  // Add JavaScript and CSS using wrapper functions.
  _ting_search_carousel_add_javascript();
  _ting_search_carousel_add_css();

  // Load toggle configuration.
  $toggle = variable_get('ting_search_carousel_description_toggle', FALSE);
  $vars['toggle_description'] = $toggle ? 'rs-carousel-wide' : 'rs-carousel-compact';
}
