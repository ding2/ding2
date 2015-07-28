<?php
/**
 * @file
 * BPI node preview.
 */

/**
 * Preview a node from BPI.
 *
 * @param string $type
 *   The type of representation. It will be either 'ajax' or 'nojs'.
 * @param string $bpi_id
 *   The BPI node ID.
 *
 * @return mixed
 *   Either an ajax-popup or an HTML representation of the item's preview.
 */
function admin_bpi_preview_ajax_callback($type, $bpi_id) {
  if (empty($bpi_id)) {
    return _admin_bpi_preview_output($type, t('Incorrect BPI ID.'));
  }

  $bpi_ctype = variable_get('bpi_content_type', '');
  // This could lead to unexpected behavior. Just a note.
  if (empty($bpi_ctype)) {
    return _admin_bpi_preview_output($type, t('BPI is not mapped to any content type.'));
  }

  // Load bpi.syndicate.inc for label mappers.
  module_load_include('inc', 'bpi', 'bpi.syndicate');

  try {
    $bpi = bpi_client_instance();
    $bpi_node = $bpi->getNode($bpi_id);
    $bpi_content = $bpi_node->getProperties();
  }
  catch (Exception $e) {
    watchdog_exception('bpi', $e);
    return _admin_bpi_preview_output($type, t('Failed to fetch the article from BPI well.'));
  }

  $output = theme('bpi_preview_item', array('item' => $bpi_content));

  return _admin_bpi_preview_output($type, $output);
}

/**
 * Output preview content.
 *
 * @param string $type
 *   Response type (ajax or standard).
 * @param string $output
 *   Content to output.
 *
 * @return mixed
 *   Response based on type.
 */
function _admin_bpi_preview_output($type, $output) {
  if ($type == 'ajax') {
    drupal_add_js(drupal_get_path('module', 'ding_popup') . '/ding_popup.js');

    $commands = array();
    $commands[] = ajax_command_ding_popup(
      'bpi-preview',
      t('BPI Preview'),
      $output,
      array('refresh' => TRUE, 'width' => '75%')
    );
    $page = array('#type' => 'ajax', '#commands' => $commands);
    ajax_deliver($page);
  }
  else {
    return $output;
  }
}
