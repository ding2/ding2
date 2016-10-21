<?php
/**
 * @file
 * Represents configuration forms and logic.
 */

/**
 * Form handler for configuration service settings.
 */
function ding_place2book_migrate_admin_form($form, &$form_state) {

  $form['start'] = array(
    '#type' => 'submit',
    '#value' => t('Start'),
    '#suffix' => t('Starting migration event to new api. This operation can not be canceled.'),
  );

  return $form;
}

/**
 * Submit handler for migrating form.
 */
function ding_place2book_migrate_admin_form_submit($form, &$form_state) {
  $query = db_select('ding_place2book', 'd');
  $query->join('node', 'n', 'n.nid=d.nid');
  $query->fields('d');
  $result = $query->execute()->fetchAll();
  $operations = array(array('_ding_place2book_migrate_batch', array($result)));

  $batch = array(
    'operations' => $operations,
    'finished' => '_ding_place2book_migrate_batch_finished',
    'title' => t('Migration events...'),
    'init_message' => t('Events migration initializes...'),
    'progress_message' => t('Migrating events.'),
    'error_message' => t('Migration failed. Check reports.'),
  );

  batch_set($batch);
}
