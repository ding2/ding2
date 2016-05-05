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
  // Return all image information.
  drupal_json_output(ting_covers_get_objects());
}

/**
 * Return the URL for the cover of an object.
 *
 * @param array $cover_data
 *   Cover information.
 *
 * @return array
 *   of cover objects.
 */
function ting_covers_get_objects(array $cover_data = array()) {
  $covers = array();
  $image_styles = array();
  $missing_images_local_ids = array();

  $cover_data = (empty($cover_data) ? $_POST['coverData'] : $cover_data);

  foreach ($cover_data as $cover_info) {
    // Determine if the local id is a known negative.
    if (cache_get('ting_covers:' . $cover_info['local_id'], FALSE)) {
      break;
    }

    $path = ting_covers_object_path($cover_info['local_id']);
    if (file_exists($path)) {
      // If we we already have a valid cover image w/o style then just use it.
      $covers[] = array(
        'local_id' => $cover_info['local_id'],
        'image_style' => $cover_info['image_style'],
        'url' => image_style_url($cover_info['image_style'], $path),
      );
    }
    else {
      // Mark the image for retrieval.
      $missing_images_local_ids[] = (object) array(
        'localIdentifier' => $cover_info['local_id'],
        'libraryCode' => $cover_info['owner_id'],
      );

      // Image style to match later one.
      $image_styles[$cover_info['local_id']] = $cover_info['image_style'];
    }
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
