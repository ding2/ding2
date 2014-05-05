<?php
/**
 * @file
 * Creates an import form for bookmarks in CSV file as panels pane.
 */

$plugin = array(
  'title' => t('Import user bookmarks'),
  'description' => t('Form to import user bookmarks'),
  'content_types' => array('list'),
  'required context' => new ctools_context_required(t('User'), 'user'),
  'category' => t('User'),
);

/**
 * Implements hook_content_type_render().
 *
 * Create a form to import bookmarks based on a URL to a CSV file.
 */
function ding_bookmark_import_content_type_render($subtype, $conf, $panel_args, $context) {
  $block = new stdClass();
  $block->module = 'ding_bookmark';
  $block->delta = 'import';

  // Render the form as the block content, if it should be displayed.
  if (variable_get('ding_bookmark_display_import', TRUE)) {
    $form = drupal_get_form('ding_bookmark_import_form');
    $block->content = drupal_render($form);;
  }

  return $block;
}

/**
 * Returns an edit form for the content type.
 *
 * We're not actually doing anything here, but we need to have this hook
 * for this content type to work.
 */
function ding_bookmark_import_content_type_edit_form($form, &$form_state) {
  return $form;
}

/**
 * Implements hook_form().
 *
 * Defines simple form to allow users to submit link to CSV file to import
 * bookmarks from other systems.
 */
function ding_bookmark_import_form($form, &$form_state) {
  $form = array();

  $form['CSV'] = array(
    '#type' => 'textfield',
    '#title' => t('Import bookmarks'),
    '#description' => t('Insert link provided to you by your local library.'),
    '#required' => TRUE,
  );

  $form['import'] = array(
    '#type' => 'submit',
    '#value' => t('Import'),
  );

  return $form;
}

/**
 * Implements submit handler for the import bookmarks form.
 */
function ding_bookmark_import_form_submit($form, &$form_state) {
  global $user;

  // Try to download file from remote server.
  $dir = 'public://bookmark_import';
  if (file_prepare_directory($dir, FILE_CREATE_DIRECTORY)) {
    // Retrieve file from remote server.
    $url = check_url($form_state['values']['CSV']);
    $file = system_retrieve_file($url, 'public://bookmark_import/' . $user->name . '.csv', FALSE, FILE_EXISTS_RENAME);

    if ($file !== FALSE) {
      // Parse the file and create bookmarks.
      _ding_bookmark_import($file);
    }
  }
  else {
    drupal_set_message(t('Unable to import bookmarks into files folder. Please try again later.'), 'error');
    watchdog('ding_bookmark', 'Unable to create local directory to upload CSV file in bookmark import.', array(), WATCHDOG_ERROR);
  }
}

/**
 * Import bookmarks based on CSV file URI.
 *
 * The file should have the following format:
 *
 *  isbn,9788758810560
 *  pid,870970-basis:50673308
 *  faust,29986215
 *  isbn,9788711397510
 *
 * @param string $uri
 *   The URI of the file to import from.
 */
function _ding_bookmark_import($uri) {
  // Get real path.
  $filepath = drupal_realpath($uri);

  // Load ting client.
  module_load_include('inc', 'ting', 'ting.client');

  // Variables to keep track of the import process.
  $found = 0;
  $imported = 0;

  // Parse CVS file.
  $lines = array_map('str_getcsv', file($filepath));
  foreach ($lines as $line) {
    $found++;
    $tid = NULL;
    switch ($line[0]) {
      case 'pid':
        $tid = $line[1];
        break;

      default:
        // Search the date well for the ID.
        $results = ting_do_search($line[1], 1, 1, array('facets' => array(), 'enrich' => FALSE, 'allObjects' => FALSE));
        if ($results->numTotalObjects) {
          // Get tid of first item in the collection.
          $tid = array_shift($results->collections)->ding_entity_id;
        }
        break;
    }

    // Load the entity from cache.
    $entity = ding_entity_load($tid);
    if ($entity && isset($entity->tid)) {
      // Add the entity ting id to the users bookmark list.
      $form_state = array('values' => array());
      drupal_form_submit('flag_confirm', $form_state, 'flag', flag_get_flag('bookmark'), $entity->tid);
      $imported++;

      // Remove the "Added to bookmark" messages.
      drupal_get_messages('status');
    }
  }

  // Set feedback message to the user.
  drupal_set_message(t('@imported out of @found bookmarks was imported.', array('@imported' => $imported, '@found' => $found)));
}
