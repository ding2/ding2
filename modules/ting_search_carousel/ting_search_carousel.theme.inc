<?php

/**
 * @file
 * Theme functions used with the ting search carousel.
 */

/**
 * Implements default preprocess function for the search carsousel.
 */
function template_preprocess_ting_search_carousel(&$vars, $hook) {
  // Add JavaScript and CSS.
  $path = drupal_get_path('module', 'ting_search_carousel');
  drupal_add_js($path . '/js/ting_search_carousel.js');
  drupal_add_css($path . '/css/ting_search_carousel.css');

  $vars['content'] = '';
  $vars += array(
    'show_description' => FALSE,
    'transition' => 'fade',
  );

  foreach ($vars['tabs'] as $index => $tab) {
    $tab += array(
      'title' => '',
      'subtitle' => '',
      'path' => '',
      // If an ajax path is given, default to the first page, else disable
      // ajax.
      'offset' => empty($tab['path']) ? -1 : 0,
      'classes' => '',
    );

    // Render the items.
    $rendered = array();
    foreach ($tab['content'] as $item) {
      $rendered[] = theme('ting_search_carousel_collection', array('collection' => $item));
    }
    $tab['description'] = $tab['subtitle'];

    $tab['content'] = implode('', $rendered);

    if ($index != 0) {
      $tab['classes'] = 'additional-tab';
    }
    $vars['tabs'][$index] = $tab;
  }

  $transitions = ting_search_carousel_transitions();
  if (isset($transitions[$vars['transition']])) {
    if (!empty($transitions[$vars['transition']]['file'])) {
      drupal_add_js($transitions[$vars['transition']]['file']);
    }
  }
  else {
    $vars['transition'] = 'fade';
  }

  if (!$vars['show_description']) {
    $vars['classes_array'][] = 'no-description';
  }

  $loaded = libraries_load('slick', 'non-minified');
}
