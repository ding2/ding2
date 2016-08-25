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
      'placeholders' => 1,
      'classes' => '',
    );

    // Render the items, or some placeholders.
    $rendered = array();
    if (count($tab['content'])) {
      foreach ($tab['content'] as $item) {
        $rendered[] = theme('ting_search_carousel_collection', array('collection' => $item));
      }
    }
    else {
      foreach (range(0, $tab['placeholders']) as $dummy) {
        $rendered[] = theme('ting_search_carousel_collection',
                            array('collection' => ting_search_carousel_collection_placeholder()));
      }
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

  // Default Slick settings.
  $vars['settings'] = array(
    'arrows' => TRUE,
    'infinite' => FALSE,
    'slidesToShow' => 5,
    'slidesToScroll' => 4,
    'responsive' => array(
      array(
        'breakpoint' => 1024,
        'settings' => array(
          'slidesToShow' => 4,
          'slidesToScroll' => 4,
        ),
      ),
      array(
        'breakpoint' => 600,
        'settings' => array(
          'slidesToShow' => 2,
          'slidesToScroll' => 2,
          'arrows' => FALSE,
        ),
      ),
      array(
        'breakpoint' => 300,
        // No carousel.
        'settings' => "unslick",
      ),
    ),
  );

  if (!$vars['show_description']) {
    $vars['classes_array'][] = 'no-description';
  }

  $loaded = libraries_load('slick', 'non-minified');
}

/**
 * Preprocess ting_search_carousel template.
 */
function template_preprocess_ting_search_carousel_collection(&$vars) {
  // $vars['collection'] is the legacy variable, leaving it in to not mess
  // with existing templates.
  $collection = $vars['collection'];
  $vars['path'] = '';
  if (!isset($collection->placeholder)) {
    $uri = entity_uri('ting_collection', $collection);
    $vars['path'] = url($uri['path'], $uri['options']);
  }

  if (isset($collection->placeholder)) {
    $vars['classes_array'][] = 'placeholder';
  }

  $vars['title'] = check_plain($collection->title);
  $vars['creator'] = check_plain($collection->creator);

  $image_info = image_get_info($collection->path);
  if ($image_info) {
    $image = array(
      'style_name' => 'ting_search_carousel',
      'path' => $collection->path,
      'width' => $image_info['width'],
      'height' => $image_info['height'],
      'alt' => '',
    );
    $vars['image'] = theme('image_style', $image);
  }
  else {
    // If image_get_info() couldn't get the image size, image style is likely
    // to fail too. So we give up here.
    $vars['image'] = '';
  }
}
