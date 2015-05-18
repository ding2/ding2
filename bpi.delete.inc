<?php
/**
 * @file
 * Delete from bpi logic here.
 */

/**
 * Deleted the content from BPI well.
 *
 * @param string $bpi_id
 *   BPI content id to be deleted.
 *
 * @return bool
 *   Status, success or failure.
 */
function bpi_well_delete($bpi_id) {
  try {
    $bpi = bpi_client_instance();

    db_delete('bpi_syndicated')
      ->condition('bid', $bpi_id, '=')
      ->execute();

    $bpi->deleteNode($bpi_id);

    return TRUE;
  }
  catch (Exception $e) {
    watchdog_exception('bpi', $e);

    return FALSE;
  }
}
