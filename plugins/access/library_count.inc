<?php
/**
 * @file
 * Plugin to provide access control based upon node type.
 */

/**
 * Plugins are described by creating a $plugin array which will be used
 * by the system that includes this file.
 */
$plugin = array(
  'title' => t("Library: number of libraries"),
  'description' => t('Control access based on the number of libraries.'),
  'callback' => 'ding_library_count_ctools_access_check',
  'default' => array('count' => 1),
  'settings form' => 'ding_library_count_ctools_access_settings',
  'summary' => 'ding_library_count_ctools_access_summary',
);

/**
 * Settings form for the 'library count' access plugin.
 */
function ding_library_count_ctools_access_settings($form, &$form_state, $conf) {
  $form['settings']['count'] = array(
    '#title' => t('Number of libraries'),
    '#type' => 'textfield',
    '#description' => t('The number of published ding library nodes that should grant access.'),
    '#default_value' => 1,
  );

  return $form;
}

/**
 * Check for access.
 */
function ding_library_count_ctools_access_check($conf, $context) {
  // Use static variable as this may be called more than once.
  $count = &drupal_static(__FUNCTION__);
  if (!isset($count)) {
    // Count the number of published libraries.
    $count = db_select('node', 'n')
      ->fields('n', array('nid'))
      ->condition('status', 1)
      ->condition('type', 'ding_library')
      ->countQuery()
      ->execute()
      ->fetchField();
  }

  // If count matches the configured number, access is given.
  if ($count == $conf['count']) {
    return TRUE;
  }

  return FALSE;
}

/**
 * Provide a summary description based upon the configuration.
 */
function ding_library_count_ctools_access_summary($conf, $context) {
  return t('Library access count is @count.', array('@count', $conf['count']));
}

