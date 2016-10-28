<?php
/**
 * @file
 * Ting covers page callbacks.
 */

/**
 * Ajax callback.
 *
 * Return the URL and style for the cover of an object.
 */
function ting_covers_objects() {
  $ids = array();
  $styles = array();
  foreach ($_POST['coverData'] as $cover_info) {
    $ids[] = $cover_info['id'];
    $styles[$cover_info['id']] = $cover_info['image_style'];
  }
  $covers = ting_covers_get($ids);
  $return = array();
  foreach ($covers as $id => $path) {
    $return[] = array(
      'id' => $id,
      'image_style' => $styles[$id],
      'url' => image_style_url($styles[$id], $path),
    );
  }

  // Return all image information.
  drupal_json_output($return);
}

/**
 * Page callback.
 *
 * Wraps image_style_deliver to fetch covers beforehand.
 */
function ting_cover_deliver($style) {
  $args = func_get_args();
  array_shift($args);

  // Add in the path prefix that got chopped in the menu definition.
  $target = implode('/', array_merge(array('ting', 'covers'), $args));

  $image_uri = 'public://' . $target;

  if (!is_file($image_uri)) {
    // Source not found, see if we can load a cover.
    // Take the filename, strip off extension and base64_decode the result.
    $ting_id = base64_decode(preg_replace('/\..*$/', '', basename($image_uri)), TRUE);
    if (empty($ting_id) || !ting_covers_get(array($ting_id))) {
      return MENU_NOT_FOUND;
    }
  }

  $params = array_merge(array($style), array('public', 'ting', 'covers'), $args);
  return call_user_func_array('image_style_deliver', $params);
}
