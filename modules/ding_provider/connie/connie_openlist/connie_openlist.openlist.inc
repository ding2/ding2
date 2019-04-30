<?php

/**
 * @file
 * Openlist provider functions.
 */

/**
 * Make request.
 *
 * @see ting_openlist_handler_request()
 */
function connie_openlist_openlist_request($function, $arguments, $detailed_log = FALSE) {
  // If the provider can't have separate functions, at least we can fake it.
  // Convert camel case to snake case.
  $function_name = 'connie_openlist_openlist_' . ltrim(strtolower(preg_replace('/[A-Z]/', '_$0', $function)), '_');
  if (function_exists($function_name)) {
    return call_user_func_array($function_name, $arguments);
  }
  if (function_exists('dpm')) {
    // @codingStandardsIgnoreLine
    dpm($arguments, 'Unimplemented Openlist function called: ' . $function);
  }
  else {
    drupal_set_message('Unimplemented Connie Openlist function called: ' . $function, 'error');
  }
  throw new DingProviderDoesntImplement($function . ' not implemented');
}

/**
 * Create list.
 */
function connie_openlist_openlist_create_list($owner, $title, $type, $data) {

  $list = array(
    'created' => REQUEST_TIME,
    'modified' => REQUEST_TIME,
    'status' => 1,
    'owner' => $owner,
    'title' => $title,
    'type' => $type,
    'data' => $data,
  );

  drupal_write_record('connie_openlist_lists', $list);
  return $list['list_id'];
}

/**
 * Edit list.
 */
function connie_openlist_openlist_edit_list($list_id, $title, $data) {
  $list = db_select('connie_openlist_lists', 'l')
        ->fields('l')
        ->condition('list_id', $list_id)
        ->execute()
        ->fetchAssoc();
  if (!$list) {
    throw new Exception('Connie: Unknown list ' . $list_id . ' in editList');
  }
  $list['title'] = $title;
  $list['data'] = $data;
  drupal_write_record('connie_openlist_lists', $list, 'list_id');
}

/**
 * Delete list.
 */
function connie_openlist_openlist_delete_list($list_id) {
  db_delete('connie_openlist_lists')
    ->condition('list_id', $list_id)
    ->execute();
  db_delete('connie_openlist_list_items')
    ->condition('list_id', $list_id)
    ->execute();
}

/**
 * Get lists for user.
 */
function connie_openlist_openlist_get_lists($owner, $from = 0) {
  $lists = db_select('connie_openlist_lists', 'l')
         ->fields('l')
         ->condition('owner', $owner)
         ->condition('modified', $from, '>')
         ->execute();

  return $lists->fetchAll(PDO::FETCH_ASSOC);
}

/**
 * Create list element.
 */
function connie_openlist_openlist_create_element($list_id, $data) {
  $item = array(
    'created' => REQUEST_TIME,
    'modified' => REQUEST_TIME,
    'list_id' => $list_id,
    'data' => $data,
  );
  drupal_write_record('connie_openlist_list_items', $item);
  return $item['element_id'];
}

/**
 * Delete list element.
 */
function connie_openlist_openlist_delete_element($element_id) {
  db_delete('connie_openlist_list_items')
    ->condition('element_id', $element_id)
    ->execute();
}

/**
 * Provide identifier for user.
 *
 * @param object $account
 *   The user account.
 *
 * @return mixed
 *   The identifier or FALSE otherwise.
 */
function connie_openlist_openlist_user_identifier($account = NULL) {
  // Use the current user account, if no account is specified.
  if ($account === NULL) {
    global $user;
    $account = $user;
  }

  // Something simple.
  return 'connie_' . $account->uid;
}

/**
 * Stop warnings from P2 that doesn't check if this is availble before calling.
 */
function connie_openlist_openlist_call_module() {
  return array();
}
