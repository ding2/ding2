<?php

/**
 * @file
 * Theme functions used with the ting search carousel.
 */

/**
 * Preprocess variables for ting_search_carousel_cover.tpl.php.
 */
function template_preprocess_ting_search_carousel_cover(&$vars) {
  $cover = $vars['cover'];

  $vars['title'] = check_plain($cover['#cover']->title);
  $vars['creator'] = check_plain($cover['#cover']->creator);

  if (!isset($cover['#cover']->placeholder)) {
    $uri = entity_uri('ting_collection', $cover['#cover']);
    $vars['path'] = url($uri['path'], $uri['options']);
  }
  else {
    $vars['path'] = '';
  }

  $image = array(
    'style_name' => 'ting_search_carousel',
    'path' => $cover['#cover']->path,
    'alt' => $vars['title'] . ' - ' . $vars['creator'],
  );

  // Add width and height to img tag to avoid layout jumping when loading.
  // However, the file might not exist (ting_cover cleans up once in a while),
  // but the cover will still be loaded as ting_cover hooks into the image style
  // callback to fetch the image on demand. So we just add the sizes if they're
  // available or hope the best.
  if (file_exists($cover['#cover']->path)) {
    $image_info = image_get_info($cover['#cover']->path);
    if ($image_info) {
      $image['width'] = $image_info['width'];
      $image['height'] = $image_info['height'];
    }
  }

  $vars['image'] = theme('image_style', $image);
}
