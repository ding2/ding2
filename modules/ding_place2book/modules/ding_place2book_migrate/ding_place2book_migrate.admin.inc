<?php
/**
 * @file
 * Represents configuration forms and logic.
 */

/**
 * Form handler for configuration service settings.
 */
function ding_place2book_migrate_admin_form($form, &$form_state) {
  // Test that some important settings is configured before allowing migration.
  $failed_tests = [];
  $ding_place2book_settings = variable_get('ding_place2book_settings', []);
  if (empty($ding_place2book_settings['token'])) {
    $failed_tests[] = t('Place2book API-token is missing. Please <a href="@configure-link">configure it here</a>.', [
      '@configure-link' => url('admin/config/ding/place2book'),
    ]);
  }
  if (empty(variable_get('ding_p2b_default_event_maker', NULL))) {
    $failed_tests[] = t('Default event maker is missing. Please <a href="@configure-link">configure it here</a>.', [
      '@configure-link' => url('admin/config/ding/place2book/defaults'),
    ]);
  }
  if (empty(variable_get('ding_p2b_library_event_makers', []))) {
    $failed_tests[] = t('Event maker mapping is missing. Please <a href="@configure-link">configure it here</a>.', [
      '@configure-link' => url('admin/config/ding/place2book/mappings'),
    ]);
  }

  $form['pre_migration_tests'] = array(
    '#type' => 'fieldset',
    '#title' => t('Pre-migration tests'),
  );

  $form['pre_migration_tests']['result'] = [
    '#theme' => 'item_list',
    '#list_type' => 'ul',
    '#items' => !empty($failed_tests) ? $failed_tests : t('Configuration is OK! Migration is ready to be started.'),
  ];

  $form['start'] = array(
    '#type' => 'submit',
    '#value' => t('Start'),
    '#disabled' => !empty($failed_tests),
    '#suffix' => t('Starting migration event to new api. This operation can not be canceled.'),
  );

  if (!empty($failed_tests)) {
    $form['start']['#suffix'] =  t('Some tests failed which need to be sorted out before migration can be started. See above.');
  }

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
