<?php

/**
 * @file
 * The provider functions.
 */

/**
 * Make a request to Openlist.
 *
 * This just wraps the ting_openlist_request() function, into the
 * ding_provider way of life.
 *
 * @param string $function
 *   Function name of the function to call on the service.
 * @param array $arguments
 *   Numerical array with the arguments, in their respectable order.
 * @param bool $detailed_log
 *   If set to true, the arguments send is logged by watchdog, if logging is
 *   active.
 *
 * @return mixed
 *   The Openlist request.
 */
function ting_openlist_handler_request($function, array $arguments, $detailed_log = FALSE) {
  return ting_openlist_request($function, $arguments, $detailed_log);
}

/**
 * Get a user identifier.
 *
 * @param object $account
 *   The user account.
 *
 * @return mixed
 *   The identifier or FALSE otherwise.
 */
function ting_openlist_handler_user_identifier($account = NULL) {
  return ting_openlist_user_identifier($account);
}

/**
 * Get a user depending on the openlist_uid.
 *
 * @param string $openlist_uid
 *   The openlist user id.
 *
 * @return object
 *   The user account.
 */
function ting_openlist_handler_local_user($openlist_uid) {
  return ting_openlist_local_user($openlist_uid);
}

/**
 * Update the user account with the openlist_uid.
 *
 * @param object $account
 *   The user account to update.
 */
function ting_openlist_handler_update_user($account) {
  ting_openlist_update_user($account);
}

/**
 * Create a list.
 *
 * @param string $user_identifier
 *   The unique user identifier.
 * @param string $title
 *   List title.
 * @param string $type
 *   List type.
 * @param array $data
 *   Extra data.
 *
 * @return mixed
 *   Openlist id or NULL.
 */
function ting_openlist_handler_create_list($user_identifier, $title, $type, array $data) {
  return ting_openlist_request('createList', array(
    'owner' => $user_identifier,
    'title' => $title,
    'type' => $type,
    'data' => $data,
  ));
}

/**
 * Edit a list.
 *
 * @param string $id
 *   Openlist id.
 * @param string $title
 *   List title.
 * @param array $data
 *   Extra data.
 */
function ting_openlist_handler_edit_list($id, $title, array $data) {
  ting_openlist_request('editList', array(
    'list_id' => $id,
    'title' => $title,
    'data' => $data,
  ), array('use_cache' => FALSE));
}

/**
 * Delete an element.
 *
 * @param array $ids
 *   List of ids to delete.
 */
function ting_openlist_handler_delete_element(array $ids) {
  ting_openlist_request('deleteElement', array(
    'element_id' => $ids,
  ), array('use_cache' => FALSE));
}

/**
 * Delete element.
 *
 * @param array $element
 *   Element.
 */
function ting_openlist_handler_v2_delete_element(array $element) {
  ting_openlist_request('deleteElement', array(
    'element_id' => $element['element_id'],
  ), array('use_cache' => FALSE, 'save_cache' => FALSE));

  $list = ting_openlist_handler_v2_get_list($element['list_id']);
  ting_openlist_cache_clear_list($list);
}

/**
 * Create an element.
 *
 * @param string $id
 *   Openlist list id.
 * @param array $data
 *   Element data.
 *
 * @return mixed
 *   openlist id of the elemnet or false.
 */
function ting_openlist_handler_create_element($id, array $data, $return_element = FALSE) {
  $result = ting_openlist_request('createElement', array(
    'list_id' => $id,
    'data' => $data,
    'return_element' => $return_element,
  ));
  return $result;
}

/**
 * Create an element.
 *
 * @param array $list
 *   List array.
 * @param array $data
 *   The element data.
 * @param bool $return_element
 *   Tells the function if it wants the entire element returned, or just the ID.
 *
 * @return mixed
 *   The element or just the element id, depending on $return_element.
 */
function ting_openlist_handler_v2_create_element(array $list, array $data, $return_element = FALSE) {
  $result = ting_openlist_request('createElement', array(
    'list_id' => $list['list_id'],
    'data' => $data,
    'return_element' => $return_element,
  ), array('use_cache' => FALSE, 'save_cache' => FALSE));

  ting_openlist_cache_clear_list($list);
  return $result;
}

/**
 * Edit element.
 *
 * @param array $element
 *   The element array.
 * @param array $data
 *   The Element data.
 */
function ting_openlist_handler_v2_edit_element(array $element, array $data) {
  ting_openlist_request('editElement', array(
    'element_id' => $element['element_id'],
    'data' => $data,
  ), array('use_cache' => FALSE, 'save_cache' => FALSE));

  $list = ting_openlist_handler_v2_get_list($element['list_id']);
  ting_openlist_cache_clear_list($list);
}

/**
 * Edit an element.
 *
 * @param string $id
 *   Openlist list id.
 * @param array $data
 *   Element data.
 */
function ting_openlist_handler_edit_element($id, array $data) {
  ting_openlist_request('editElement', array(
    'list_id' => $id,
    'data' => $data,
  ));
}

/**
 * Delete a list.
 *
 * @param int $id
 *   Openlist id.
 */
function ting_openlist_handler_delete_list($id) {
  ting_openlist_request('deleteList', array(
    'list_id' => $id,
  ));
}

/**
 * Move an element to after another element.
 *
 * @param int $id
 *   Openlist id, of the element you're moving.
 * @param int $previous_id
 *   Openlist id, of the element you're moving.
 */
function ting_openlist_handler_set_element_after($id, $previous_id) {
  ting_openlist_request('setElementAfter', array(
    'element_id' => $id,
    'previous_id' => $previous_id,
  ));
}

/**
 * Get the user's lists.
 *
 * @param string $user_identifier
 *   The user.
 * @param int $from
 *   Only get lists with changes from this timestamp.
 *
 * @return array
 *   List of lists.
 */
function ting_openlist_handler_get_lists($user_identifier, $from) {
  return ting_openlist_request('getLists', array(
    'owner' => $user_identifier,
    'from' => $from,
  ));
}

/**
 * Get all the user's elements.
 *
 * @param string $user_identifier
 *   The user.
 * @param int $from
 *   Only get elements with changes from this timestamp.
 *
 * @return array
 *   List of elements
 */
function ting_openlist_handler_get_user_elements($user_identifier, $from) {
  return ting_openlist_request('getUserElements', array(
    'owner' => $user_identifier,
    'from' => $from,
  ));
}

/**
 * Call a module function on the openlist service.
 *
 * @param string $module
 *   Name of the module.
 * @param string $method
 *   The method to call.
 * @param array $arguments
 *   List of ordered arguments.
 *
 * @return mixed
 *   The return of the module.
 */
function ting_openlist_handler_call_module($module, $method, array $arguments = array()) {
  return ting_openlist_request('callModule', array(
    'module_name' => $module,
    'method' => $method,
    'args' => $arguments,
  ));
}

/**
 * Get user.
 *
 * @param object $account
 *   User object.
 *
 * @return array
 *   The openlist user object.
 */
function ting_openlist_handler_v2_get_user($account = NULL, $no_cache = FALSE) {
  return ting_openlist_request(
    'v2_getUser',
    array('user' => ting_openlist_user_identifier($account)),
    array('use_cache' => !$no_cache)
  );
}

/**
 * Get list.
 *
 * @param int $list_id
 *   List ID.
 *
 * @return array
 *   The openlist user object.
 */
function ting_openlist_handler_v2_get_list($list_id) {
  return ting_openlist_request('v2_getList', array(
    'list_id' => $list_id,
  ), array('cache_prefix' => 'l' . $list_id));
}

/**
 * Get lists by type.
 *
 * @param array $list_types
 *   The list types.
 * @param object $account
 *   User object.
 * @param bool $expanded
 *   If the list elements should be returned as well.
 *
 * @return array
 *   List of list objects.
 */
function ting_openlist_handler_v2_get_lists_by_type(array $list_types, $account, $expanded = FALSE) {
  return ting_openlist_request('v2_getListsByType', array(
    'types' => $list_types,
    'user' => ting_openlist_user_identifier($account),
    'expanded' => $expanded,
  ), array('cache_prefix' => 'u' . $account->uid));
}

/**
 * Edit list.
 *
 * @param array $list
 *   The list array.
 */
function ting_openlist_handler_v2_edit_list(array $list) {
  ting_openlist_request('editList', array(
    'list_id' => $list['list_id'],
    'title' => $list['title'],
    'data' => $list['data'],
  ), array('method' => 'POST'));

  ting_openlist_cache_clear_list($list);
}

/**
 * Create a list.
 *
 * @param array $list
 *   The list array.
 *
 * @return int
 *   The list id.
 */
function ting_openlist_handler_v2_create_list(array $list) {
  $result = ting_openlist_request('createList', array(
    'owner' => $list['owner'],
    'title' => $list['title'],
    'type' => $list['type'],
    'data' => $list['data'],
  ), array('method' => 'POST'));

  $account = ting_openlist_local_user($list['owner']);
  if ($account !== FALSE && !empty($account->uid)) {
    ting_openlist_cache_clear(['u' . $account->uid]);
  }

  return $result;
}

/**
 * Detele a list.
 *
 * @param array $list
 *   The list array.
 */
function ting_openlist_handler_v2_delete_list(array $list) {
  ting_openlist_request('deleteList', array(
    'list_id' => $list['list_id'],
  ), array('method' => 'POST'));
  ting_openlist_cache_clear_list($list);
}
