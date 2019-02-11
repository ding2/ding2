<?php

/**
 * @file
 * Theming functions for ding_carousel.
 */

/**
 * Preprocess variables for ding_carousel.tpl.php.
 */
function template_preprocess_ding_carousel(&$vars) {
  // We need to load the non-minified version as with patch the library.
  libraries_load('slick', 'non-minified');

  $carousel = $vars['carousel'];

  $vars['items'] = array();

  foreach ($carousel['#items'] as $item) {
    // Making sure the prefix is a h3 instead of h2 for WCAG reasons.
    // We need to use str_replace as its possible for the element to contain
    // more than just a <h2> tag.
    // @see: https://github.com/ding2/ding2/blob/16ee7ee2063ade17ed3c2efae255304f6828a61d/modules/ting/ting.field.inc#L410
    if (!empty($item['ting_title'][0]['#prefix']) &&
        !empty($item['ting_title'][0]['#suffix'])) {
      $item['ting_title'][0]['#prefix'] = str_replace('<h2', '<h3', $item['ting_title'][0]['#prefix']);
      $item['ting_title'][0]['#suffix'] = str_replace('</h2', '</h3', $item['ting_title'][0]['#suffix']);
    }

    // Wrap items in ding_carousel_item.
    $vars['items'][] = array(
      '#type' => 'ding_carousel_item',
      '#content' => $item,
    );
  }

  // This is an empty carousel, which slick don't handle well (as in it will
  // make a infinite loop and kill the browser). So e.g. 0 hits search
  // carousel's are fixed here be simply placing a single placeholder slide.
  if (empty($vars['items'])) {
    $vars['items'][] = array(
      '#type' => 'ding_carousel_item',
      '#content' => $carousel['#placeholder'],
      '#placeholder' => TRUE,
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
    'outerEdgeLimit' => TRUE,
  );

  if (isset($carousel['#hidden']) && $carousel['#hidden']) {
    $vars['classes_array'][] = 'hidden';
  }

  // Set class if ting_objects are displayed without overlay.
  if (theme_get_setting('ting_object_disable_overlay')) {
    $vars['classes_array'][] = 'ting-object-no-overlay';
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
  foreach ($tabbed_carousel['#tabs'] as $index => $tab) {
    if ($index !== 0) {
      $tab['#hidden'] = TRUE;
    }
    $vars['tabs'][] = $tab;
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

  $content = array(
    '#type' => 'markup',
    '#markup' => '<span class="icon-spinner"></span>',
  );

  $vars['content'] = !empty($item['#content']) ? $item['#content'] : $content;
}
