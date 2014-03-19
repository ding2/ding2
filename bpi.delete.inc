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
 * @param object $node
 *   Node object.
 *
 * @return array
 *   A set of ajax commands or form structure.
 */
function bpi_delete_action($type = 'ajax', $node = NULL) {
  // Only author can delete his node.
  if (!bpi_ability($node->nid, 'delete')) {
    drupal_access_denied();
    drupal_exit();
  }

  $delete_form = drupal_get_form('bpi_delete_form', $node);

  if ($type == 'ajax') {
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
 * @param object $node
 *   Node object.
 *
 * @return array
 *   Form structure.
 *
 * @ingroup forms
 */
function bpi_delete_form($form, $form_state, $node) {
  $form['bpi_delete_bpi_id'] = array(
    '#type' => 'value',
    '#value' => isset($node->bpi_id) ? $node->bpi_id : 0,
  );

  return confirm_form(
    $form,
    t('Are you sure you want to delete %title from bpi well?', array('%title' => $node->title)),
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
  $bpi_id = $form_state['values']['bpi_delete_bpi_id'];

  if (empty($bpi_id)) {
    drupal_set_message(t('Selected content could not be deleted from the BPI well.'), 'error');
    return;
  }

  $status = bpi_well_delete($bpi_id);

  if ($status) {
    drupal_set_message(t('Selected content deleted from BPI well.'));
  }
  else {
    drupal_set_message(t('Failed to delete selected content from BPI well.'), 'error');
  }
}

/**
 * Form ajax callback for delete action.
 *
 * @param array $form
 *   Form structure.
 * @param array $form_state
 *   Form state values.
 *
 * @return array
 *   A set of AJAX commands.
 */
function bpi_delete_action_ajax_callback($form, &$form_state) {
  $response = array(
    '#type' => 'ajax',
    '#commands' => array(),
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
