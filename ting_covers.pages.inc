<?php

/**
 * Return the URL for the cover of an object
 */
function ting_covers_objects() {
  $covers = array();
  $missing_images_local_ids = array();

  foreach ($_POST['coverData'] as $cover_info) {
    //Reverse cover_info before and after explode to make sure that we explode around
    //the last :. Local ids could contain the delimiter!
    list($local_id, $image_style) = array_reverse(array_map('strrev', explode(':', strrev($cover_info), 2)));

    //Determine if the local id is a known negative
    if (cache_get('ting_covers:' . $local_id, FALSE)) {
      break;
    }
    
    $path = ting_covers_object_path($local_id);
    if (file_exists($path)) {
      //If we we already have a valid cover image w/o style then just use it
      $covers[$local_id.':'.$image_style] = image_style_path($path. $image_style);
    } else {
      //Mark the image for retrieval;
      $missing_images_local_ids[] = $local_id;
    }
  }
  
  //Try to download the missing images
  try {
    $service = new AdditionalInformationService(variable_get('addi_wsdl_url'), variable_get('addi_username'), variable_get('addi_group'), variable_get('addi_password'));
    //Local ids = Faust numbers. Library object identifiers can be confusing...
    $additional_informations = $service->getByFaustNumber($missing_images_local_ids);
    foreach($missing_images_local_ids as $local_id) {
      //Try to extract the image url from the result 
      $source_url = FALSE;
      if (isset($additional_informations[$local_id]) && $ai = $additional_informations[$local_id]) {
        if ($ai->detailUrl) {
          $source_url = $ai->detailUrl;
        } elseif ($ai->thumbnailUrl) {
          $source_url = $ai->thumbnailUrl;
        }
      }
      
      //No cover image found? Cache this for future reference to avoid unnecessary requests
      if (!$source_url) {
        cache_set('ting_covers:'.$local_id, 1, 'cache', $_SERVER['REQUEST_TIME'] + TING_COVERS_CACHE_LIFETIME);
        continue;
      }
      
      //Try to download the image locally
      if ($file = _ting_covers_pages_fetch_image(ting_covers_object_path($local_id), $source_url)) {
        //Generate a path corresponding to the downloaded image, styled
        $covers[$local_id.':'.$image_style] = image_style_url($image_style, $file->uri);
      }
    }
  } catch (Exception $e) {
    print_r($e);
  }
  
  //Return all image information
  drupal_json_output($covers);
}

/**
 * Helper function to fetch and save a cover image file.
 *
 * @see image_style_create_derivative()
 *
 * @param string $filename
 *    File name, including its path within Drupal's file folder.
 * @param string $image_url
 *    URL for the source image file.
 * @return mixed
 *    A file object or FALSE on error.
 */
function _ting_covers_pages_fetch_image($filename, $image_url) {
  $result = drupal_http_request($image_url);

  //Bail if the HTTP request failed
  if ($result->code != 200) {
    return FALSE;
  }
  
  // Get the folder for the final location of this preset...
  $directory = dirname($filename);
  
  // Build the destination folder tree if it doesn't already exist.
  if (!file_prepare_directory($directory, FILE_CREATE_DIRECTORY | FILE_MODIFY_PERMISSIONS)) {
    watchdog('ting_covers', 'Failed to create directory: %directory', array('%directory' => $directory), WATCHDOG_ERROR);
    return FALSE;
  }    

  return file_save_data($result->data, $filename, FILE_EXISTS_REPLACE);
}
