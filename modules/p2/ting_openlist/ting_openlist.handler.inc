<?php

/**
 * @file
 * The provider functions.
 */

use DingList\DingList;
use DingList\DingListElement;

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
 * Get a Drupal user depending on the openlist_uid.
 *
 * @param string $openlist_uid
 *   The openlist user id.
 *
 * @return object
 *   The user account.
 */
function ting_openlist_handler_drupal_user($openlist_uid) {
  return ting_openlist_drupal_user($openlist_uid);
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
 * Delete element.
 *
 * @param DingList\DingListElement $element
 *   The element.
 */
function ting_openlist_handler_delete_element(DingListElement $element) {
  ting_openlist_request('deleteElement', array(
    'element_id' => $element->getId(),
  ), array('use_cache' => FALSE));

  $list = ting_openlist_handler_get_list($element->getListId());
  ting_openlist_cache_clear_list($list);
}

/**
 * Create an element.
 *
 * @param DingList\DingListElement $element
 *   The element.
 */
function ting_openlist_handler_create_element(DingListElement $element) {
  $data = $element->getData() + array(
    'type' => $element->getType(),
    'value' => $element->getValue(),
  );

  $result = ting_openlist_request('createElement', array(
    'list_id' => $element->getListId(),
    'data' => $data,
  ), array('use_cache' => FALSE));

  $element->setId($result);

  $list = ting_openlist_handler_get_list($element->getListId());
  ting_openlist_cache_clear_list($list);
}

/**
 * Edit element.
 *
 * @param DingList\DingListElement $element
 *   The element.
 */
function ting_openlist_handler_edit_element(DingListElement $element) {
  $data = $element->getData() + array(
    'type' => $element->getType(),
    'value' => $element->getValue(),
  );

  ting_openlist_request('editElement', array(
    'element_id' => $element->getId(),
    'data' => $data,
  ), array('use_cache' => FALSE));

  $list = ting_openlist_handler_get_list($element->getListId());
  ting_openlist_cache_clear_list($list);
}

/**
 * Move an element to after another element.
 *
 * @param \DingList\DingList $list
 *   The list.
 * @param int $id
 *   Openlist id, of the element you're moving.
 * @param int $previous_id
 *   Openlist id, of the element you're moving.
 */
function ting_openlist_handler_set_element_after(DingList $list, $id, $previous_id) {
  ting_openlist_request('setElementAfter', array(
    'element_id' => $id,
    'previous_id' => $previous_id,
  ), array('use_cache' => FALSE));

  ting_openlist_cache_clear_list($list);
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
 * @param array $settings
 *   The settings passed along to ting_openlist_request.
 *
 * @return mixed
 *   The return of the module.
 */
function ting_openlist_handler_call_module($module, $method, array $arguments = array(), $settings = array()) {
  return ting_openlist_request('callModule', array(
    'module_name' => $module,
    'method' => $method,
    'args' => $arguments,
  ), $settings);
}

/**
 * Get list.
 *
 * @param int $list_id
 *   List ID.
 *
 * @return \DingList\DingList|false
 *   The list or FALSE if no list exists.
 */
function ting_openlist_handler_get_list($list_id) {
  $list = ting_openlist_request('getList', array(
    'list_id' => $list_id,
  ), array('cache_prefix' => 'l' . $list_id));

  if ($list === FALSE) {
    return FALSE;
  }

  return DingList::fromDataArray($list);
}

/**
 * Get lists by type.
 *
 * @param string[] $list_types
 *   The list types.
 * @param object $account
 *   User object.
 * @param bool $expanded
 *   If the list elements should be returned as well.
 *
 * @return \DingList\DingList[]
 *   List of list objects.
 */
function ting_openlist_handler_get_lists_by_type(array $list_types, $account, $expanded = FALSE) {
  if (empty($list_types)) {
    $list_types = FALSE;
  }

  $lists = ting_openlist_request('getListsByType', array(
    'types' => $list_types,
    'user' => ting_openlist_user_identifier($account),
    'expanded' => $expanded,
  ), array('cache_prefix' => 'u' . $account->uid));

  foreach ($lists as &$list) {
    $list = DingList::fromDataArray($list);
  }

  return $lists;
}

/**
 * Edit list.
 *
 * @param \DingList\DingList $list
 *   The list.
 */
function ting_openlist_handler_edit_list(DingList $list) {
  ting_openlist_request('editList', array(
    'list_id' => $list->getId(),
    'title' => $list->getTitle(),
    'data' => $list->getData(),
  ), array('use_cache' => FALSE));

  ting_openlist_cache_clear_list($list);
}

/**
 * Clear the local cache.
 *
 * @param string|array $prefixes
 *   The prefixes or single prefix to clear.
 */
function ting_openlist_handler_clear_cache($prefixes) {
  ting_openlist_cache_clear($prefixes);
}

/**
 * Create a list.
 *
 * @param \DingList\DingList $list
 *   The list.
 */
function ting_openlist_handler_create_list(DingList $list) {
  $result = ting_openlist_request('createList', array(
    'owner' => $list->getOwner(),
    'title' => $list->getTitle(),
    'type' => $list->getType(),
    'data' => $list->getData(),
  ), array('use_cache' => FALSE));

  $list->setId($result);

  $account = ting_openlist_drupal_user($list->getOwner());
  if ($account !== FALSE && !empty($account->uid)) {
    ting_openlist_cache_clear(['u' . $account->uid]);
  }
}

/**
 * Detele a list.
 *
 * @param \DingList\DingList $list
 *   The list.
 */
function ting_openlist_handler_delete_list(DingList $list) {
  ting_openlist_request('deleteList', array(
    'list_id' => $list->getId(),
  ), array('use_cache' => FALSE));
  ting_openlist_cache_clear_list($list);
}

/**
 * Get list elements.
 *
 * @param \DingList\DingList $list
 *   The list.
 * @param int $offset
 *   Start position.
 * @param int $count
 *   Number of elements to retrieve.
 *
 * @return DingList\DingListElement[]
 *   The elements.
 */
function ting_openlist_handler_get_list_elements(DingList $list, $offset, $count) {
  $elements = ting_openlist_request('getListElements', array(
    'list_id' => $list->getId(),
    'offset' => $offset,
    'count' => $count,
  ), array('cache_prefix' => 'l' . $list->getId()));

  $result = array();

  foreach ($elements as $element_data) {
    $result[] = DingListElement::fromDataArray($element_data);
  }

  return $result;
}

/**
 * Reset an openlist user.
 *
 * @param object $account
 *   The user account to reset.
 */
function ting_openlist_handler_reset_user($account) {
  $user_identifier = ting_openlist_user_identifier($account);
  return ting_openlist_request('callModule', array(
    'module_name' => 'ResetUser',
    'method' => 'reset',
    'args' => array($user_identifier),
  ));
}
