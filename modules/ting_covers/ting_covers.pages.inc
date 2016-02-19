<?php
/**
 * @file
 * Retrieves covers for ting objects and returns them in the correct format
 * based on configuration.
 */

/**
 * Return the URL for the cover of an object.
 */
function ting_covers_objects($http_request = TRUE, $cover_data = array()) {
  $covers = array();
  $image_styles = array();
  $missing_images_local_ids = array();

  if ($http_request) {
    $cover_data = $_POST['coverData'];
  }
  elseif (!$http_request && empty($cover_data)) {
    return $covers;
  }

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

  // Try to download the missing images.
  try {
    $service = new AdditionalInformationService(variable_get('addi_wsdl_url'), variable_get('addi_username'), variable_get('addi_group'), variable_get('addi_password'));

    // Local ids = Faust numbers. Library object identifiers can be confusing.
    $additional_informations = $service->getByLocalIdentifier($missing_images_local_ids);
    foreach ($missing_images_local_ids as $local_id) {
      // Try to extract the image url from the result.
      $source_url = FALSE;
      if (isset($additional_informations[$local_id->localIdentifier]) && $ai = $additional_informations[$local_id->localIdentifier]) {
        if ($ai->detailUrl) {
          $source_url = $ai->detailUrl;
        }
        elseif ($ai->thumbnailUrl) {
          $source_url = $ai->thumbnailUrl;
        }
      }

      // No cover image found? Cache this for future reference to avoid
      // unnecessary requests.
      if (!$source_url) {
        cache_set('ting_covers:' . $local_id->localIdentifier, 1, 'cache', $_SERVER['REQUEST_TIME'] + TING_COVERS_DEFAULT_CACHE_LIFETIME);
        continue;
      }

      // Try to download the image locally.
      if ($file = _ting_covers_pages_fetch_image(ting_covers_object_path($local_id->localIdentifier), $source_url)) {
        // Generate a path corresponding to the downloaded image, styled.
        $covers[] = array(
          'local_id' => $local_id->localIdentifier,
          'image_style' => $image_styles[$cover_info['local_id']],
          'url' => image_style_url($image_styles[$cover_info['local_id']], $file),
        );
      }
    }
  }
  catch (Exception $e) {
    watchdog('ting_covers', 'Unable to retrieve covers from ADDI: %message', array('%message' => $e->getMessage()), WATCHDOG_ERROR);
  }

  // Return all image information.
  if ($http_request) {
    drupal_json_output($covers);
  }
  else {
    return $covers;
  }
}

/**
 * Helper function to fetch and save a cover image file.
 *
 * @see image_style_create_derivative()
 *
 * @param string $filename
 *   File name, including its path within Drupal's file folder.
 * @param string $image_url
 *   URL for the source image file.
 *
 * @return mixed
 *   A file object or FALSE on error.
 */
function _ting_covers_pages_fetch_image($filename, $image_url) {
  $result = drupal_http_request($image_url);

  // Bail if the HTTP request failed.
  if ($result->code != 200) {
    return FALSE;
  }

  // Get the folder for the final location of this preset.
  $directory = dirname($filename);

  // Build the destination folder tree if it doesn't already exist.
  if (!file_prepare_directory($directory, FILE_CREATE_DIRECTORY | FILE_MODIFY_PERMISSIONS)) {
    watchdog('ting_covers', 'Failed to create directory: %directory', array('%directory' => $directory), WATCHDOG_ERROR);
    return FALSE;
  }

  return file_unmanaged_save_data($result->data, $filename, FILE_EXISTS_REPLACE);
}
