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
function ting_openlist_handler_get_user($openlist_uid) {
  return ting_openlist_get_user($openlist_uid);
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
function ting_openlist_handler_create_list($user_identifier, $title, $type, $data) {
  $method = 'createList';
  return ting_openlist_request($method, func_get_args());
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
function ting_openlist_handler_edit_list($id, $title, $data) {
  $method = 'editList';
  ting_openlist_request($method, func_get_args());
}

/**
 * Delete an element.
 *
 * @param array $id
 *   List of ids to delete.
 */
function ting_openlist_handler_delete_element($ids) {
  $method = 'deleteElement';
  ting_openlist_request($method, func_get_args());
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
function ting_openlist_handler_create_element($id, $data) {
  $method = 'createElement';
  return ting_openlist_request($method, func_get_args());
}

/**
 * Edit an element.
 *
 * @param string $id
 *   Openlist list id.
 * @param array $data
 *   Element data.
 */
function ting_openlist_handler_edit_element($id, $data) {
  $method = 'editElement';
  ting_openlist_request($method, func_get_args());
}

/**
 * Delete a list.
 *
 * @param int $id
 *   Openlist id.
 */
function ting_openlist_handler_delete_list($ids) {
  $method = 'deleteList';
  ting_openlist_request($method, func_get_args());
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
  $method = 'setElementAfter';
  ting_openlist_request($method, func_get_args());
}

/**
 * Get the user's lists.
 *
 * @param string $user_identifier
 *   The user
 * @param int $from
 *   Only get lists with changes from this timestamp.
 *
 * @return array
 *   List of lists.
 */
function ting_openlist_handler_get_lists($user_identifier, $from) {
  $method = 'getLists';
  return ting_openlist_request($method, func_get_args());
}

/**
 * Get all the user's elements.
 *
 * @param string $user_identifier
 *   The user
 * @param int $from
 *   Only get elements with changes from this timestamp.
 *
 * @return array
 *   List of elements
 */
function ting_openlist_handler_get_user_elements($user_identifier, $from) {
  $method = 'getUserElements';
  return ting_openlist_request($method, func_get_args());
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
function ting_openlist_handler_call_module($module, $method, $arguments) {
  $method = 'callModule';
  return ting_openlist_request($method, func_get_args());
}