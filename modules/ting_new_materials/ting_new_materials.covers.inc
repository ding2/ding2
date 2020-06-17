<?php

/**
 * @file
 * Helpers to get covers.
 */

use CoverService\Api\CoverApi;
use GuzzleHttp\Client;

/**
 * Duplicate code from ting_covers and ting_covers_ddb module.
 *
 * Ting covers module doesn't provide a api we can use.
 *
 * @param array $covers_ids
 *   Ids of the materials to fetch covers for.
 * @param int $number_of_objects
 *   The number of objects.
 *
 * @return array
 *   True if there is a cover image else FALSE. Indexed by local id.
 */
function ting_new_materials_check_covers(array $covers_ids, $number_of_objects) {
  $missing_images_local_ids = array();
  $number_found = 0;

  foreach ($covers_ids as $cover_id) {
    // Determine if the local id is a known negative.
    if (cache_get('ting_covers:' . $cover_id->localId, FALSE)) {
      $cover_id->hasImage = FALSE;
      continue;
    }

    $path = ting_covers_object_path($cover_id->localId);
    if (false && file_exists($path)) {
      $cover_id->hasImage = TRUE;
      $number_found++;
    }
    else {
      $cover_id->hasImage = FALSE;
      $missing_images_local_ids[] = $cover_id->localId;
    }
    if ($number_found >= $number_of_objects) {
      break;
    }
  }

  try {
    $config = _ting_cover_ddb_get_client_config();
    $apiInstance = new CoverApi(
      new Client(),
      $config
    );
    _ting_covers_ddb_debug_log('Requested covers for pids: ' . implode(', ', $missing_images_local_ids));
    $retrieved = $apiInstance->getCoverCollection('pid', $missing_images_local_ids, array('original', 'large'));
  }
  catch (Exception $e) {
    watchdog('ting_new_materials', 'Unable to retrieve covers: %message', array('%message' => $e->getMessage()), WATCHDOG_ERROR);
    return $covers_ids;
  }

  foreach ($retrieved as $cover) {
    $covers_ids[$cover->getId()]->hasImage = TRUE;
  }

  return $covers_ids;
}
