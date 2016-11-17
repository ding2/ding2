<?php

/**
 * @file
 * Container for menu callback functions.
 */

/**
 * Reorder a list.
 *
 * @param string $list_id
 *   The ID of the list.
 *
 * @return array
 *   Ajax commands, with information about the process.
 */
function ding_list_set_order_callback($list_id) {
  if (empty($list_id) || !isset($_POST['item']) || !isset($_POST['previous'])) {
    return drupal_json_encode(array(
      'status' => FALSE,
    ));
  }
  $list = ding_list_get_list($list_id);

  $item = entity_load_single('ding_type', $_POST['item']);
  $previous = entity_load_single('ding_type', $_POST['previous']);
  ding_list_set_element_position($list, $item, $previous);

  $html = t('List changed');
  $commands = array();

  $commands[] = ajax_command_changed('#' . $context['html_id'], $html);

  return array(
    '#type' => 'ajax',
    '#commands' => $commands,
  );
}

/**
 * Attach an element to a list.
 *
 * @param string $type
 *   The element type.
 * @param string $list_id
 *   The ID of the list.
 * @param string $value
 *   Value of the element.
 *
 * @return array
 *   Ajax commands, with information about the process.
 */
function ding_list_attach_element_callback($type, $list_id, $value) {
  $commands = array();

  $list = ding_list_get_list($list_id);

  $op_infos = ding_list_list_operations();
  $op = $op_infos[$type];

  if (!ding_list_has_ding_list_element($list, $type, $value)) {
    $element = ding_list_create_ding_list_element($list, $type, array('value' => $value));

    if ($element !== FALSE) {

      if (isset($_GET['title'])) {
        $element->field_search_title[LANGUAGE_NONE] = array(array('value' => $_GET['title']));
        $element->save();
      }

      if (!empty($op['_data']['response_success'])) {
        // Translate the response.
        $response = t($op['_data']['response_success'], array('!name' => l($list->title, 'list/' . $list->id)));
      }
      else {
        $response = t('Added to !name', array('!name' => l($list->title, 'list/' . $list->id)));
      }
    }
    else {
      $response = t("An error occurred, your element wasn't created. Please contact the administrator if this problem persists.");
    }
  }
  else {
    $response = t('Already added to !name', array('!name' => l($list->title, 'list/' . $list->id)));
  }

  $commands[] = ajax_command_ding_popup('ding_list', t('List'), '<div class="ding-list-message">' . $response . '</div>');
  return array(
    '#type' => 'ajax',
    '#commands' => $commands,
  );
}

/**
 * Remove an element from a list.
 *
 * @param string $list_id
 *   The ID of the list.
 * @param string $element_id
 *   The ID of the element.
 *
 * @return array
 *   Ajax commands, with information about the process.
 */
function ding_list_remove_element_from_list_callback($list_id, $element_id) {
  $list = ding_list_get_list($list_id);
  $context = drupal_get_query_parameters();
  if (ding_list_detach_ding_list_element($list, explode(',', $element_id)) !== FALSE) {
    $html = t('Removed from !name', array('!name' => l($list->title, 'user/list/' . $list->id)));
  }
  else {
    $html = t("An error occurred while removing your element. Please contact the administrator if this problem persists.");
  }

  $status = array(
    'selector' => '#' . $context['html_id'],
    'message' => $html,
    'status' => TRUE,
    'refresh' => TRUE,
  );
  $commands = array();

  $commands[] = ajax_command_html('#' . $context['html_id'] . ' .action-message', $html, $status);

  return array(
    '#type' => 'ajax',
    '#commands' => $commands,
  );
}

/**
 * Delete a list.
 *
 * @param string $list_id
 *   The ID of the list.
 *
 * @return array
 *   Ajax commands, with information about the process.
 */
function ding_list_delete_list_callback($list_id) {
  $list = ding_list_get_list($list_id);

  ding_list_delete_list($list);

  $status = array(
    'status' => TRUE,
    'remove' => '.ding-type-ding-list',
  );

  $html = t('List deleted');
  $commands = array();
  $context = drupal_get_query_parameters();
  $commands[] = ajax_command_append('#' . $context['html_id'], $html, $status);

  return array(
    '#type' => 'ajax',
    '#commands' => $commands,
  );
}

/**
 * Private share message.
 *
 * @param string $list_id
 *   The ID of the list.
 *
 * @return array
 *   Ajax commands, with information about the process.
 */
function ding_list_private_share_message_callback($list_id) {
  $list = ding_list_get_list($list_id);

  $commands = array();

  $commands[] = ajax_command_ding_popup(
    'ding_list',
    t('Info'),
    '<p>' . t("You can only share public lists.") . '<br>' .
      l(t('Click here and set this list status to public'), 'list/' . $list->id . '/share')
    . '</p>'
  );

  return array(
    '#type' => 'ajax',
    '#commands' => $commands,
  );
}
