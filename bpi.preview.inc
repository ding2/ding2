<?php

/**
 * @file
 * Syndication logic here.
 */

/**
 * Returns HTML for a foo.
 *
 * @param string $type
 *   The type of representation. It will be either 'ajax'
 *   or 'nojs'.
 *
 * @param string $bpi_id
 *   The BPI node ID.
 *
 * @return html
 *   Either an ajax-popup or an HTML representation of the item's
 *   preview.
 */
function admin_bpi_preview_ajax_callback($type = 'ajax', $bpi_id) {
  drupal_add_js(drupal_get_path('module', 'ding_popup') . '/ding_popup.js');
  module_load_include('inc', 'bpi', 'bpi.syndicate');

  if (!isset($bpi_id)) {
    return;
  }
  $bpi_ctype = variable_get('bpi_content_type', '');
  // This could lead to unexpected behavior. Just a note.
  if (empty($bpi_ctype)) {
    return;
  }
  $endpoint = variable_get('bpi_service_url', '');
  $agency_id = variable_get('bpi_agency_id', '');
  $api_key = variable_get('bpi_api_key', '');
  $secret_key = variable_get('bpi_secret_key', '');

  try {
    $bpi = new Bpi($endpoint, $agency_id, $api_key, $secret_key);
    $bpi_node = $bpi->getNode($bpi_id);
    $bpi_content = $bpi_node->getProperties();
  }
  catch (Exception $e) {
    watchdog(
      'bpi',
      t('Error when syndicating node %title with message %message'),
      array(
        '%title' => $bpi_content['title'],
        '%message' => $e->getMessage(),
      ),
      WATCHDOG_ERROR
    );
    drupal_set_message(t('Failed to fetch the article from BPI well.'), 'error');
  }

  $body = variable_get('bpi_field_body', '');
  $bpi_teaser = isset($bpi_content['teaser']) ? $bpi_content['teaser'] : '';
  $output = theme('bpi_preview_item', array('item' => $bpi_content));
  if ($type == 'ajax') {
    $commands = array();
    $commands[] = ajax_command_ding_popup(
      'bpi-push',
      t('Push to BPI'),
      $output,
      array('refresh' => TRUE)
    );
    $page = array('#type' => 'ajax', '#commands' => $commands);
    ajax_deliver($page);
  }
  else {
    return $output;
  }
}
