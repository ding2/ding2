<?php

/**
 * @file ding_wishlist.theme.inc
 * Theming functions for wishlist.
 */

/**
 * Template preprocessor for wishlist items.
 */
function template_preprocess_ding_wishlist_item(&$variables) {
  // Helpful $content variable for templates.
  foreach (element_children($variables['elements']) as $key) {
    $variables['content'][$key] = $variables['elements'][$key];
  }
}
