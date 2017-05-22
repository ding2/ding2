<?php

/**
 * @file
 * Theming functions for ding_carousel.
 */

/**
 * Preprocess variables for ding_carousel.tpl.php.
 */
function template_preprocess_ding_carousel(&$vars) {
  libraries_load('slick', 'non-minified');
  $carousel = $vars['carousel'];

  $vars['items'] = array();
  // Wrap items in ding_carousel_item.
  foreach ($carousel['#items'] as $item) {
    $vars['items'][] = array(
      '#type' => 'ding_carousel_item',
      '#content' => $item,
    );
  }

  // Fill up with placeholders if there's not enough items.
  if (count($vars['items']) < $carousel['#placeholders']) {
    while (count($vars['items']) < $carousel['#placeholders']) {
      $vars['items'][] = array(
        '#type' => 'ding_carousel_item',
        '#content' => $carousel['#placeholder'],
        '#placeholder' => TRUE,
      );
    }
  }

  // Default Slick settings.
  $vars['slick_settings'] = array(
    'arrows' => TRUE,
    'infinite' => FALSE,
    // Use variableWidth to allow the theme to control cover sizes.
    'variableWidth' => TRUE,
  );

  if ($carousel['#hidden']) {
    $vars['classes_array'][] = 'hidden';
  }

  $vars['title'] = $carousel['#title'];
  $vars['offset'] = $carousel['#offset'];
  $vars['path'] = $carousel['#path'];
}

/**
 * Preprocess variables for ding_tabbed_carousel.tpl.php.
 */
function template_preprocess_ding_tabbed_carousel(&$vars) {
  $tabbed_carousel = $vars['tabbed_carousel'];

  $vars['tabs'] = array();
  $first = TRUE;
  foreach ($tabbed_carousel['#tabs'] as $tab) {
    if (!$first) {
      $tab['#hidden'] = TRUE;
    }
    $vars['tabs'][] = $tab;
    $first = FALSE;
  }

  $vars['transition'] = $tabbed_carousel['#transition'];
}

/**
 * Preprocess variables for ding_carousel_item.tpl.php.
 */
function template_preprocess_ding_carousel_item(&$vars) {
  $item = $vars['item'];

  if ($item['#placeholder']) {
    $vars['classes_array'][] = 'placeholder';
  }

  $vars['content'] = !empty($item['#content']) ? $item['#content'] : '';
}
