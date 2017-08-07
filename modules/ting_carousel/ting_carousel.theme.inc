<?php

/**
 * Returns HTML for a ting_carousel.
 *
 * @param $variables
 *   An associative array containing:
 *   - items: A list of items.
 *   - item_type: Tells the template_preprocessor how to handle the items.
 *   - processed_items: The items after the preprocessors has processed them.
 */
function theme_ting_carousel($variables) {
  $output = '';

  foreach ($variables['processed_items'] as $item) {
    $output .= '<div class="ting-carousel-item">' . drupal_render($item) . '</div>';
  }

  return '<div class="ting-carousel type-' . $variables['item_type'] . '">' . $output . '</div>';
}

/**
 * Preprocess ting_carousel().
 */
function template_preprocess_ting_carousel(&$variables) {
  // Add all js and css files needed.
  ting_carousel_add_externals();

  $variables['processed_items'] = array();

  if (!empty($variables['items'])) {
    switch ($variables['item_type']) {
      case 'ting_object':
        $view_mode = isset($variables['args']['view_mode']) ? $variables['args']['view_mode'] : 'teaser';
        foreach (ding_entity_load_multiple($variables['items'], 'ting_object') as $object) {
          $variables['processed_items'][] = ting_object_view($object, $view_mode);
        }

        break;

      case 'items':
      default:
        $variables['processed_items'] = $variables['items'];
        break;
    }
  }
}
