<?php

/**
 * @file
 * Cover upload page when form is submitted.
 */

use CoverServiceUpload\ApiException;
use CoverServiceUpload\Api\CoverApi;
use CoverServiceUpload\Model\MaterialWrite;
use CoverServiceUpload\Api\MaterialApi;
use GuzzleHttp\Client;

/**
 * Check cover service to determine if file has been uploaded.
 *
 * Ajax callback function.
 */
function _cover_upload_check_submission() {
  $data = $_SESSION['ddb_cover_upload_data'];

  // Validation to prevent page re-load submit and upload.
  $exists = FALSE;
  if (isset($data['image_uri'])) {
    $exists = file_exists(drupal_realpath($data['image_uri']));
  }

  // Check if the minimum required data exists.
  if (!$exists || !isset($data['image_uri']) || !isset($data['pid'])) {
    drupal_json_output(array(
      'message' => t('Either the image have been uploaded ot something is wrong with the session'),
      'status' => 'error',
    ));
    drupal_exit();
  }

  try {
    _ddb_cover_upload_client_upload($data['image_uri'], $data['pid'], 'pid');
    watchdog('ddb_cover_upload', 'Cover have been upload for %pid to DDB upload service', array('%pid' => $data['pid']), WATCHDOG_INFO);

    // Clear cover and materials cache.
    cache_clear_all('ddb_cover_upload', 'cache', TRUE);
  }
  catch (ApiException $e) {
    drupal_json_output(array(
      'message' => $e->getMessage(),
      'status' => 'error',
    ));
    drupal_exit();
  }

  // If we get here the image should have been upload and we clean up the local
  // installation.
  _ddb_cover_upload_cleanup();

  // Notify frontend "Nothing to see yet".
  drupal_json_output(array(
    'status' => 'success',
  ));
  drupal_exit();
}

/**
 * Remove db entry and files locally.
 */
function _ddb_cover_upload_cleanup() {
  $data = $_SESSION['ddb_cover_upload_data'];

  // Mark image as upload to prevent more uploads of the same data.
  unset($_SESSION['ddb_cover_upload_data']);

  // Remove local copy of the image.
  file_unmanaged_delete($data['image_uri']);
}

/**
 * Wrapper to upload a cover to the service.
 *
 * @param string $image_uri
 *   The local URI for the cover image.
 * @param string $identifier
 *   The identifier for the material for the cover.
 * @param string $identifier_type
 *   The type of identifier (faust, pid, isbn).
 *
 * @throws \CoverServiceUpload\ApiException
 * @throws \GuzzleHttp\Exception\BadResponseException
 */
function _ddb_cover_upload_client_upload($image_uri, $identifier, $identifier_type) {
  $image = drupal_realpath($image_uri);
  $config = ddb_cover_upload_client_config();
  $apiInstance = new CoverApi(
    new Client(),
    $config
  );
  $cover = $apiInstance->postCoverCollection($image);

  $material = new MaterialWrite();
  $material->setCover('/api/covers/' . $cover->getId());
  $material->setIsType($identifier_type);
  $material->setIsIdentifier($identifier);

  $apiInstance = new MaterialApi(
    new Client(),
    $config
  );
  $apiInstance->postMaterialCollection($material);
}
