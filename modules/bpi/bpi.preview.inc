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

  $output = theme('bpi_preview_item', array(
    'item' => $bpi_content,
    'syndicate_url' => bpi_get_syndicate_url($bpi_content['type'], $bpi_content['id']),
  ));

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
    ctools_include('modal');
    ctools_modal_add_js();

    $commands = array();
    $commands[] = ctools_modal_command_display(t('BPI Preview'), $output);
    $page = array('#type' => 'ajax', '#commands' => $commands);
    ajax_deliver($page);
  }
  else {
    return $output;
  }
}
