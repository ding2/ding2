<?php

/**
 * @file
 * Functions handling the create, edit and delete api.
 */

use DingList\DingList;

/**
 * Get a list structure.
 *
 * @param array|int|string $list
 *   The value you which to get a list from.
 * @param mixed $account
 *   The user which the list is connected to.
 *   This only affects the result if the $list is a DING_LIST_TYPE.
 *
 * @return \DingList\DingList|false
 *   Either FALSE or the list.
 */
function ding_list_get_list($list, $account = NULL) {
  // If it's an object return that object.
  if ($list instanceof DingList) {
    return $list;
  }

  $lists = &drupal_static(__FUNCTION__, array());

  // Create the unique key using the list input and account uid.
  $key = $list . "_" . ($account ? $account->uid : "");
  if (isset($lists[$key])) {
    return $lists[$key];
  }

  $lists[$key] = FALSE;

  try {
    // If it's a number we assume it's the ID of the list.
    if (is_numeric($list) && ding_provider_implements('openlist', 'v2_get_list')) {
      $lists[$key] = ding_provider_invoke('openlist', 'v2_get_list', $list);

      if ($lists[$key]) {
        $lists[$key] = new DingList($lists[$key]);
      }
    }
    // If it's a string, we assume it's a DING_LIST_TYPE, and we grab the first.
    elseif (is_string($list)) {
      $tmp = ding_list_get_lists($list, $account, TRUE);
      if ($tmp !== FALSE) {
        $lists[$key] = array_shift($tmp);
      }
    }
  }
  catch (TingOpenlistRequestException $e) {
    return FALSE;
  }

  return $lists[$key];
}

/**
 * Get lists connected to a user.
 *
 * @param string|array $list_types
 *   The list type to filter. If you supply an array it will filter by all the
 *   lists in that array (using OR).
 *   Combining this with the ding_list_get_list_types_by_operations(), will
 *   give an easy way of selecting specific lists which can do specific
 *   operations.
 * @param object $account
 *   The user account on who you want to get the reservations from (if none is
 *   given it will default to the current user).
 * @param bool $expanded
 *   Get the list elements as well.
 *
 * @return \DingList\DingList[]
 *   An array of ding lists.
 */
function ding_list_get_lists($list_types, $account = NULL, $expanded = FALSE) {
  $lists = array();

  // @TODO Implement permissions
  if ($account === NULL) {
    global $user;
    $account = $user;
  }

  if ($account->uid === 0) {
    return $lists;
  }

  if (!is_array($list_types)) {
    $list_types = array($list_types);
  }

  if (empty($list_types)) {
    $list_types = FALSE;
  }

  if (ding_provider_implements('openlist', 'v2_get_lists_by_type')) {
    $lists = ding_provider_invoke('openlist', 'v2_get_lists_by_type', $list_types, $account, $expanded);
  }

  foreach ($lists as &$list) {
    $list = new DingList($list);
  }

  return $lists;
}
