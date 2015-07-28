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

    db_update('bpi_syndicated')
      ->fields(array('status' => 0))
      ->condition('bid', $bpi_id, '=')
      ->execute();

    $res = $bpi->deleteNode($bpi_id);
    if ($res) {
      drupal_set_message(t('BPI content with id %id was successfully deleted from the BPI well.', array('%id' => $bpi_id)));
    }
    else {
      drupal_set_message(t('BPI content with id %id was NOT deleted from the BPI well. Contact an administrator.', array('%id' => $bpi_id)), 'error');
    }

    return TRUE;
  }
  catch (Exception $e) {
    watchdog_exception('bpi', $e);

    drupal_set_message(t('BPI content with id %id was NOT deleted from the BPI well. Contact an administrator.', array('%id' => $bpi_id)), 'error');
    return FALSE;
  }
}
