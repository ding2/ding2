<?php
/**
 * @file
 * Delete from bpi logic here.
 */

/**
 * Entry point for delete action.
 *
 * @param string $type
 *   Request type, ajax or not.
 * @param int $nid
 *   Node id.
 * @return array
 *   A set of ajax commands or form structure.
 */
function bpi_delete_action($type = 'ajax', $nid) {
  $ajax = ($type == 'ajax');

  if (empty($nid)) {
    return;
  }

  $delete_form = drupal_get_form('bpi_delete_form', $nid);

  if ($ajax) {
    $commands = array();

    $commands[] = ajax_command_ding_popup(
      'bpi-delete',
      t('Delete from BPI'),
      drupal_render($delete_form),
      array('refresh' => TRUE)
    );

    return array('#type' => 'ajax', '#commands' => $commands);
  }
  else {
    return $delete_form;
  }
}

/**
 * Delete from structure.
 *
 * @param array $form
 *   Form structure.
 * @param array $form_state
 *   Form state values.
 * @param int $nid
 *   Node id, which content is to be deleted from the well.
 * @return array
 *   Form structure.
 *
 * @ingroup forms
 */
function bpi_delete_form($form, $form_state, $nid) {
  $node_title = '';
  if (!empty($nid)) {
    $node = node_load($nid);
    $node_title = $node->title;
  }

  $form['bpi_delete_bpi_id'] = array(
    '#type' => 'hidden',
    '#value' => isset($node->bpi_id) ? $node->bpi_id : 0,
  );

  return confirm_form(
    $form,
    t('Are you sure u want to delete <strong>%title</strong> from bpi well?', array('%title' => $node_title)),
    'admin/content'
  );
}

/**
 * Submit handler for delete form.
 *
 * @see bpi_delete_form()
 *
 * @param array $form
 *   Form structure.
 * @param array $form_state
 *   Form state values.
 *
 * @ingroup forms
 */
function bpi_delete_form_submit($form, &$form_state) {
  $bpi_id = $form_state['input']['bpi_delete_bpi_id'];

  if (!empty($bpi_id)) {
    $status = bpi_well_delete($bpi_id);

    if ($status) {
      drupal_set_message(t('Selected content deleted from BPI well.'));
    }
    else {
      drupal_set_message(t('Failed to delete selected content from BPI well.'), 'error');
    }
  }
  else {
    drupal_set_message(t('Selected content could not be deleted from the BPI well.'), 'error');
  }
}

/**
 * Form ajax callback for delete action.
 *
 * @param array $form
 *   Form structure.
 * @param array $form_state
 *   Form state values.
 * @return array
 *   A set of AJAX commands.
 */
function bpi_delete_action_ajax_callback($form, &$form_state) {
  $response = array(
    '#type' => 'ajax',
    '#commands' => array()
  );

  $html = theme('status_messages');

  $response['#commands'][] = ajax_command_ding_popup(
    'bpi-delete',
    t('Delete from BPI'),
    $html
  );

  return $response;
}

/**
 * Deleted the content from BPI well.
 *
 * @param string $bpi_id
 *   BPI content id to be deleted.
 * @return boolean
 *   Status, success or failure.
 */
function bpi_well_delete($bpi_id) {
  $endpoint = variable_get('bpi_service_url', '');
  $agency_id = variable_get('bpi_agency_id', '');
  $api_key = variable_get('bpi_api_key', '');
  $secret_key = variable_get('bpi_secret_key', '');

  try {
    $bpi = new Bpi($endpoint, $agency_id, $api_key, $secret_key);

    db_delete('bpi_syndicated')
      ->condition('bid', $bpi_id, '=')
      ->execute();

    $bpi->deleteNode($bpi_id);

    return TRUE;
  }
  catch (Exception $e) {
    watchdog(
      'bpi',
      t('Failed to delete node %title, with message %message.'),
      array(
        '%title' => $node->title,
        '%message' => $e->getMessage()
      ),
      WATCHDOG_ERROR
    );

    return FALSE;
  }
}
