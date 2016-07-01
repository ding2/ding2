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
}
