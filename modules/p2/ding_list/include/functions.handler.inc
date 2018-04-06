<?php

/**
 * @file
 * Functions handling the create, edit and delete api.
 */

/**
 * Create a ding_list_element, and attach it to the list.
 *
 * A ding_list_element should not exist without it being attached to a list,
 * which is why the create function will automatically attach it to a list.
 *
 * @param object $list
 *   The list to attach the element to.
 * @param string $type
 *   Type of the element.
 * @param array $values
 *   An array of elements.
 *
 * @return mixed
 *   The ding_list_element object.
 */
function ding_list_attach_element(&$list, $type, array $values) {
  $element = FALSE;

  if (ding_provider_implements('openlist', 'create_element')) {
    try {
      $element = ding_provider_invoke(
        'openlist',
        'v2_create_element',
        $list,
        $values + array('type' => $type),
        TRUE
      );

      $list['elements'][$element['element_id']] = $element;
    }
    catch (Exception $e) {
      watchdog_exception('ding_list', $e);
      return FALSE;
    }
  }

  return $element;
}

/**
 * Save a list.
 *
 * @param array $list
 *   List to save.
 */
function ding_list_save_list(array &$list) {
  if (!empty($list['list_id'])) {
    if (ding_provider_implements('openlist', 'edit_list')) {
      ding_provider_invoke('openlist', 'v2_edit_list', $list);
    }
  }
  else {
    if (ding_provider_implements('openlist', 'create_list')) {
      $list['list_id'] = ding_provider_invoke('openlist', 'v2_create_list', $list);
    }
  }
}

/**
 * Remove an element.
 *
 * @param array $element
 *   The element to remove.
 *
 * @return bool
 *   If the elements where deleted or not.
 */
function ding_list_detach_element(array $element) {
  if (ding_provider_implements('openlist', 'v2_delete_element')) {
    try {
      ding_provider_invoke('openlist', 'v2_delete_element', $element);
    }
    catch (Exception $e) {
      drupal_set_message(t("An error occurred while deleting your element. Please contact the administrator if this problem persists."), 'error');
      return FALSE;
    }
  }

  return TRUE;
}

/**
 * Delete a list.
 *
 * @param array $list
 *   The list to delete.
 *
 * @return bool
 *   TRUE if the list is deleted.
 */
function ding_list_delete_list(array $list) {
  if (ding_provider_implements('openlist', 'v2_delete_list')) {
    try {
      ding_provider_invoke('openlist', 'v2_delete_list', $list);
    }
    catch (Exception $e) {
      drupal_set_message(t("An error occurred while deleting your list. Please contact the administrator if this problem persists."), 'error');
      return FALSE;
    }
  }

  return TRUE;
}

/**
 * Get a list structure.
 *
 * @param array|int|string $list
 *   The value you which to get a list from.
 * @param mixed $account
 *   The user which the list is connected to.
 *   This only affects the result if the $list is a DING_LIST_TYPE.
 *
 * @return mixed
 *   Either FALSE or the list structure.
 */
function ding_list_get_list($list, $account = NULL) {
  // If it's an object return that object.
  if (is_object($list)) {
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
 * @return mixed
 *   An array of ding_list entities. FALSE otherwise.
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

  if (ding_provider_implements('openlist', 'v2_get_lists_by_type')) {
    $lists = ding_provider_invoke('openlist', 'v2_get_lists_by_type', $list_types, $account, $expanded);
  }

  return $lists;
}

/**
 * Edit an existing ding_list_element.
 *
 * @param object $element
 *   The element to edit.
 * @param array $values
 *   Field values mapped as an array [$key => $value].
 *
 * @return mixed
 *   The ding_list_element
 */
function ding_list_edit_element(&$element, $values = array()) {
  if (ding_provider_implements('openlist', 'v2_edit_element')) {
    try {
      $data = $values + array('type' => $element['type']);
      ding_provider_invoke('openlist', 'v2_edit_element', $element, $data);
    }
    catch (Exception $e) {
      drupal_set_message(t("An error occurred while editing your element. Please contact the administrator if this problem persists."), 'error');
      return FALSE;
    }
  }

  return $element;
}

/**
 * Get the value of a list element.
 *
 * For legacy purposes the function checks if the value is set in a field
 * named: field_{element_type}
 *
 * @param object $element
 *   The element.
 *
 * @return string
 *   The value of this element
 *
 * @deprecated Use $element['value'].
 */
function ding_list_get_list_element_value($element) {
  return $element['value'];
}
