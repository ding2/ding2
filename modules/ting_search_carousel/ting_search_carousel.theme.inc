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

  $css_id = drupal_html_id('ting_search_carousel');
  $vars['id'] = $css_id;
  $vars['content'] = '';

  foreach ($vars['tabs'] as $index => $tab) {
    $tab += array(
      'title' => '',
      'subtitle' => '',
      'path' => '',
      'offset' => empty($tab['path']) ? -1 : 0,
    );

    // Render the items.
    $rendered = array();
    foreach ($tab['content'] as $item) {
      $rendered[] = theme('ting_search_carousel_collection', array('collection' => $item));
    }

    if ($rendered) {
      // Add in the content of the first tab, as it's rendered by the server.
      if ($index == 0) {
        $preload = !empty($vars['preload']) ? $vars['preload'] : 5;
        // Render the first part in the template and add the rest to the JS.
        $vars['content'] = implode('', array_slice($rendered, 0, $preload));
        $tab['content'] = implode('', array_slice($rendered, $preload));
      }
      else {
        $tab['content'] = implode('', $rendered);
      }
    }
    if ($index == 0) {
      $vars['subtitle'] = $tab['subtitle'];
    }
    $vars['tabs'][$index] = $tab;
  }

  $transition = 'fade';
  $transitions = ting_search_carousel_transitions();
  if (!empty($vars['transition']) &&
    isset($transitions[$vars['transition']])) {
    $transition = $vars['transition'];
    if (!empty($transitions[$vars['transition']]['file'])) {
      drupal_add_js($transitions[$vars['transition']]['file']);
    }
  }

  // Load toggle configuration.
  $toggle = variable_get('ting_search_carousel_description_toggle', FALSE);
  $settings = array(
    'ting_search_carousel' => array(
      'show_description' => $toggle,
      'carousels' => array(
        $css_id => array(
          'tabs' => $vars['tabs'],
          'transition' => $transition,
        ),
      ),
    ),
  );
  drupal_add_js($settings, 'setting');

  $vars['toggle_description'] = $toggle;

}
