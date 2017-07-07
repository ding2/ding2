<?php

/**
 * @file
 * Functions handling the create, edit and delete api.
 */

/**
 * Get a list by one of its elements.
 *
 * @param object $element
 *   The ding list element to check by.
 *
 * @return bool|object
 *   The list the element is attached to, or FALSE if it's not attached to any.
 */
function ding_list_get_list_by_element($element) {
  $query = new EntityFieldQuery();
  $result = $query->entityCondition('entity_type', 'ding_type')
    ->entityCondition('bundle', 'ding_list')
    ->fieldCondition('field_list_objects', 'target_id', $element->id, '=')
    ->execute();

  if (!empty($result['ding_type'])) {
    return ding_list_get_list(key($result['ding_type']));
  }

  return FALSE;
}

/**
 * Get lists connected to a user.
 *
 * @param string|array $list_type
 *   The list type to filter. If you supply an array it will filter by all the
 *   lists in that array (using OR).
 *   Combining this with the ding_list_get_list_types_by_operations(), will
 *   give an easy way of selecting specific lists which can do specific
 *   operations.
 * @param object $account
 *   The user account on who you want to get the reservations from (if none is
 *   given it will default to the current user).
 * @param array $range
 *   From where to where, in an array(from, length).
 * @param array $order_by
 *   Order by in an array ('what', 'direction'), is ('changed', 'DESC') by
 *   default. Note that you can only order by property.
 *
 * @return mixed
 *   An array of ding_list entities. FALSE otherwise.
 */
function ding_list_get_lists($list_type = NULL, $account = NULL, array $range = array(), array $order_by = array('changed', 'DESC')) {
  if ($account === NULL) {

    // Only authenticated users can have lists.
    if (!user_is_logged_in()) {
      return FALSE;
    }

    global $user;
    $account = $user;
  }

  $lists = array();

  $query = new EntityFieldQuery();
  $query->entityCondition('entity_type', 'ding_type')
    ->entityCondition('bundle', 'ding_list')
    ->propertyCondition('uid', $account->uid)
    ->propertyOrderBy($order_by[0], $order_by[1]);

  if ($list_type !== NULL) {
    $query->fieldCondition('field_list_type', 'value', $list_type);
  }

  if (count($range) == 2) {
    $query->range($range[0], $range[1]);
  }

  $result = $query->execute();
  if (!empty($result)) {
    $lists = $result['ding_type'];
  }

  // Add lists user has access to, but don't own.
  $query = db_select('field_data_field_ding_list_permissions', 'fdlp')
    ->fields('fdlp', array('entity_id'));

  if (user_is_logged_in()) {
    $id = $account->uid;
    if (ding_provider_implements('openlist', 'user_identifier')) {
      $id = ding_provider_invoke('openlist', 'user_identifier', $account);
    }

    $query->join('field_data_field_ding_list_user', 'fdlu', 'fdlu.entity_id = fdlp.field_ding_list_permissions_target_id');
    $query->condition('fdlu.field_ding_list_user_value', $id);
  }

  if ($list_type !== NULL) {
    $query->join('field_data_field_list_type', 'flt', 'flt.entity_id = fdlp.entity_id');
    $query->condition('flt.field_list_type_value', $list_type);
  }

  $result = $query->execute()->fetchAllKeyed(0, 0);
  if (!empty($result)) {
    $lists += $result;
  }

  $lists = entity_load('ding_type', array_keys($lists));

  if (!empty($lists)) {
    return $lists;
  }

  return FALSE;
}

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
 * @param object $account
 *   The user attaching the element.
 * @param bool $save_list
 *   Automatically save the list after the element is attached.
 *   It's useful not to auto save the list if multiple elements are added at
 *   once.
 * @param int $openlist_id
 *   The Openlist id. If not set it will automatically set it.
 *
 * @return mixed
 *   The ding_list_element object.
 */
function ding_list_create_ding_list_element(&$list, $type, array $values, $account = NULL, $save_list = TRUE, $openlist_id = FALSE) {

  $element = entity_create('ding_type', array(
    'type' => 'ding_list_element',
    'title' => $type . ': ' . $values['value'],
  ));

  if ($element === FALSE) {
    return FALSE;
  }

  // The entity_create automatically set the entity uid to the current user so
  // we only need to change this if specified.
  if ($account !== NULL) {
    $element->uid = $account->uid;
  }

  // Set the type, and let the type select which field to add the id to.
  $element->field_element_type[LANGUAGE_NONE][] = array('value' => $type);
  foreach ($values as $key => $value) {
    $element->{'field_' . $key}[LANGUAGE_NONE][] = array('value' => $value);
  }

  // TODO I suggest replacing module_exists with ding_provider_implements.
  if (ding_provider_implements('openlist', 'create_element') && $openlist_id === FALSE) {
    try {
      $openlist_data = $values + array('type' => $type);
      $openlist_id = ding_provider_invoke('openlist', 'create_element', $list->openlist_id, $openlist_data);
    }
    catch (Exception $e) {
      watchdog_exception('ding_list', $e);
      return FALSE;
    }
  }

  if ($openlist_id !== FALSE) {
    $element->openlist_id = $openlist_id;
  }

  $element->save();

  // Finally add the element to the list.
  $list->field_list_objects[LANGUAGE_NONE][] = array(
    'target_id' => $element->id,
  );

  if ($save_list === TRUE) {
    $list->save();
  }

  return $element;
}

/**
 * Create a ding_list.
 *
 * Gives a cleaner, not so specific code, at the cost of some performance. But
 * creating lists shouldn't be an often used function anyway.
 *
 * @param string $title
 *   The title of the list.
 * @param string $type
 *   Type of the list.
 * @param object $account
 *   A user object, to connect the list to. If nothing is supplied it will use
 *   the currently logged in user.
 * @param mixed $more
 *   Data saved into the more property.
 * @param int $openlist_id
 *   The Openlist id. If not set it will automatically set it.
 * @param array $fields
 *   Values for fields in the ding_list entity.
 *
 * @return bool|object
 *   Newly created list element, or FALSE if not created.
 */
function ding_list_create_ding_list($title, $type = DING_LIST_TYPE_USER_LIST, $account = NULL, $more = NULL, $openlist_id = NULL, array $fields = array()) {
  $list = entity_create('ding_type', array(
    'type' => 'ding_list',
    'title' => $title,
  ));

  // The entity_create automatically set the entity uid to the current user so
  // we only need to change this if specified.
  if ($account !== NULL) {
    $list->uid = $account->uid;
  }

  $list->field_list_type[LANGUAGE_NONE][0]['value'] = $type;

  if ($more !== NULL) {
    $list->more = $more;
  }

  ding_list_handle_fields_in_list($list, $fields);

  if ($openlist_id === NULL && ding_provider_implements('openlist', 'user_identifier')
      && ding_provider_implements('openlist', 'create_list')) {
    try {
      $openlist_id = ding_provider_invoke(
        'openlist',
        'create_list',
        ding_provider_invoke('openlist', 'user_identifier', $account),
        $title,
        $type,
        array('more' => $more, 'fields' => $fields)
      );
    }
    catch (Exception $e) {
      return FALSE;
    }
  }

  if ($openlist_id !== NULL) {
    $list->openlist_id = $openlist_id;
  }

  $list->save();

  return $list;
}

/**
 * Insert a list of fields into a list.
 *
 * @param object $list
 *   The list object.
 * @param array $fields
 *   An array with field names and values. The single item array should have
 *   the following values mapped: value, value_type and name.
 */
function ding_list_handle_fields_in_list(&$list, array $fields) {
  if (!empty($fields)) {
    foreach ($fields as $field) {
      if (!is_array($field['value'])) {
        if (!empty($field['value'])) {
          $list->{$field['name']}[LANGUAGE_NONE] = array(array($field['value_type'] => $field['value']));
        }
        else {
          $list->{$field['name']} = array();
        }
      }
      else {
        $list->{$field['name']}[LANGUAGE_NONE] = array();
        foreach ($field['value'] as $value) {
          if (!empty($value)) {
            $list->{$field['name']}[LANGUAGE_NONE][] = array($field['value_type'] => $value);
          }
          else {
            $list->{$field['name']} = array();
          }
        }
      }
    }
  }
}

/**
 * Edit an existing ding_list.
 *
 * @param object $list
 *   The list object.
 * @param string $title
 *   The new title of the list.
 * @param mixed $more
 *   A simple free data form.
 * @param bool $tell_openlist
 *   If this is true (as by default) it will tell the openlist service about
 *   the changes. When synchronizing this would be set to false.
 * @param array $fields
 *   Values for fields in the ding_list entity.
 *
 * @return mixed
 *   The ding_list object or FALSE if edit failed.
 */
function ding_list_edit_ding_list(&$list, $title, $more = NULL, $tell_openlist = TRUE, array $fields = array()) {
  if ($list->title === $title && ($more === NULL || $list->more === $more) && empty($fields)) {
    return $list;
  }

  $list->title = $title;

  if ($more !== NULL) {
    $list->more = $more;
  }

  ding_list_handle_fields_in_list($list, $fields);

  if (ding_provider_implements('openlist', 'edit_list') && $tell_openlist === TRUE && $list->openlist_id > 0) {
    // Remove site specific values before sending to list.
    unset($fields['field_ding_list_permissions']);
    try {
      ding_provider_invoke(
        'openlist',
        'edit_list',
        $list->openlist_id,
        $list->title,
        array(
          'more' => $list->more,
          'fields' => $fields,
        )
      );
    }
    catch (Exception $e) {
      drupal_set_message(t("An error occurred while changing your list. Please contact the administrator if this problem persists."), 'error');
      return FALSE;
    }
  }

  $list->save();

  return $list;
}

/**
 * Detach a ding_list_element from a list, and delete the ding_list_element.
 *
 * @param object $list
 *   ding_list object, the ding_list_element is attached to. This is
 *   parsed by reference so you don't need to reload it after the update.
 * @param array $element_ids
 *   Array of ding_list_element ids to remove and detach.
 * @param bool $save_list
 *   Automatically save the list after element has been detached.
 *   It's usefu to not save the list every time an element is detached, if more
 *   elements are detached right after.
 * @param bool $tell_openlist
 *   Tell Openlist about the changes.
 *   Don't tell openlist about the objects added from openlist while syncing.
 *
 * @return mixed
 *   The count of element items actually deleted. Or FALSE if something went
 *   wrong.
 */
function ding_list_detach_ding_list_element(&$list, array $element_ids = array(), $save_list = TRUE, $tell_openlist = TRUE) {
  if (empty($element_ids)) {
    return 0;
  }

  // Get the ding_list_elements attached to the ding_list.
  $items = ding_base_get_items('ding_type', $list, 'field_list_objects');

  // Run through the ding_list_elements, and determine if they should be
  // removed or kept.
  // This way we can utilize the entity_delete_multiple instead of running a
  // single entity_delete on every id.
  $kept = $delete = array();
  foreach ($items as $item) {
    if (in_array($item['target_id'], $element_ids)) {
      $delete[] = $item['target_id'];
    }
    else {
      $kept[] = $item;
    }
  }

  if (ding_provider_implements('openlist', 'delete_element') && $tell_openlist === TRUE) {
    $query = db_select('eck_ding_type', 'e');
    $result = $query->fields('e', array('openlist_id'))
      ->condition('id', $element_ids)
      ->execute();

    $openlist_ids = $result->fetchCol();

    if (!empty($openlist_ids)) {
      try {
        ding_provider_invoke('openlist', 'delete_element', $openlist_ids);
      }
      catch (Exception $e) {
        drupal_set_message(t("An error occurred while deleting your element. Please contact the administrator if this problem persists."), 'error');
        return FALSE;
      }
    }
  }

  // Delete the ding_list_elements.
  entity_delete_multiple('ding_type', $delete);

  // Overwrite the old field_list_objects with the new $kept list.
  $list->field_list_objects[LANGUAGE_NONE] = $kept;

  if ($save_list) {
    $list->save();
  }

  return count($delete);
}

/**
 * Delete a list and all it's attached elements.
 *
 * @param object|int $list
 *   The ding_list to delete.
 *   If this is a numeric value, it will automatically load the ding_list
 *   object.
 * @param bool $tell_openlist
 *   Tell Openlist about the changes.
 *
 * @return bool
 *   TRUE or FALSE depending on if the list was deleted or not.
 */
function ding_list_delete_list($list, $tell_openlist = TRUE) {
  $transaction = db_transaction();

  // Auto load the ding_list if $list is a number.
  if (is_numeric($list)) {
    $list = entity_load_single('ding_type', $list);
  }

  // Get a list of all the attached elements, and detach them.
  // Detach also deletes the element.
  $keys = array();
  $items = ding_base_get_items('ding_type', $list, 'field_list_objects');
  foreach ($items as $item) {
    $keys[] = $item['target_id'];
  }

  if (!empty($keys)) {
    ding_list_detach_ding_list_element($list, $keys, TRUE, $tell_openlist);
  }

  // TODO I suggest replacing module_exists with ding_provider_implements.
  if (ding_provider_implements('openlist', 'delete_list') && $tell_openlist === TRUE && $list->openlist_id > 0) {
    try {
      ding_provider_invoke('openlist', 'delete_list', $list->openlist_id);
    }
    catch (Exception $e) {
      $transaction->rollback();
      drupal_set_message(t("An error occurred while deleting your list. Please contact the administrator if this problem persists."), 'error');
      return FALSE;
    }
  }

  // Remove the actual ding_list.
  entity_delete('ding_type', $list->id);
  return TRUE;
}

/**
 * Preload ting_objects.
 *
 * @param array $elements
 *   List of elements to preload the connected ting_object.
 *   Any element is allowed, but only ting_object references are preloaded.
 */
function ding_list_pre_call_elements(array $elements) {
  $keys = array();
  foreach ($elements as $element) {
    if (ding_base_get_value('ding_type', $element, 'field_element_type') === 'ting_object') {
      $id = ding_base_get_value('ding_type', $element, 'field_ting_object');
      $keys[] = $id;
    }
  }
  ting_object_load_multiple($keys);
}

/**
 * Load an array with the elements.
 *
 * @param object $list
 *   The ding_list entity.
 *
 * @return array
 *   An array with the elements in, or an empty array, if no elements exist.
 */
function ding_list_load_elements($list) {
  $items = FALSE;
  if ($list) {
    $items = field_get_items('ding_type', $list, 'field_list_objects');
  }
  if ($items !== FALSE) {
    // Run through all the elements to get the target ids.
    // This way we can load all the objects with a single call instead of
    // loading them lazy.
    $keys = array();
    foreach ($items as $item) {
      $keys[] = $item['target_id'];
    }

    // Return all the elements.
    return entity_load('ding_type', $keys);
  }

  return array();
}

/**
 * Get a list object.
 *
 * @param object|int|string $list
 *   The value you which to get a list from.
 * @param mixed $account
 *   The user which the list is connected to.
 *   This only affects the result if the $list is a DING_LIST_TYPE.
 *
 * @return mixed
 *   Either FALSE or the list object.
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

  // If it's a number we assume it's the ID of the list.
  if (is_numeric($list)) {
    $lists[$key] = entity_load_single('ding_type', $list);
  }
  // If it's a string, we assume it's a DING_LIST_TYPE, and we grab the first.
  elseif (is_string($list)) {
    $list_element = ding_list_get_lists($list, $account, array(0, 1));
    if ($list_element !== FALSE) {
      $lists[$key] = array_shift($list_element);
    }
  }

  return $lists[$key];
}

/**
 * Edit an existing ding_list_element.
 *
 * @param object $element
 *   The element to edit.
 * @param string $type
 *   New type of the element.
 * @param array $values
 *   Field values mapped as an array [$key => $value].
 * @param bool $tell_openlist
 *   Tell Openlist about the changes.
 * @param bool $no_save
 *   Don't save the element after changes has been made.
 *
 * @return mixed
 *   The ding_list_element
 */
function ding_list_edit_ding_list_element(&$element, $type = NULL, array $values = NULL, $tell_openlist = TRUE, $no_save = FALSE) {
  if ($type !== NULL) {
    $element->field_element_type[LANGUAGE_NONE][] = array('value' => $type);
  }

  foreach ($values as $key => $value) {
    $element->{'field_' . $key}[LANGUAGE_NONE] = array(array('value' => $value));
  }

  // TODO I suggest replacing module_exists with ding_provider_implements.
  if (ding_provider_implements('openlist', 'edit_element') && $tell_openlist === TRUE && $element->openlist_id > 0) {
    try {
      $openlist_data = $values + array('type' => $type);
      ding_provider_invoke('openlist', 'edit_element', $element->openlist_id, $openlist_data);
    }
    catch (Exception $e) {
      drupal_set_message(t("An error occurred while editing your element. Please contact the administrator if this problem persists."), 'error');
      return FALSE;
    }
  }

  if ($no_save === FALSE) {
    $element->save();
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
 */
function ding_list_get_list_element_value($element) {
  $field_name = 'field_value';
  $element_type = ding_base_get_value('ding_type', $element, 'field_element_type');

  if (!empty($element->{'field_' . $element_type})) {
    $field_name = 'field_' . $element_type;
  }
  $value = ding_base_get_value('ding_type', $element, $field_name);

  return $value;
}

/**
 * Get the state of a list element.
 *
 * @param object $element
 *   The element.
 *
 * @return string
 *   The state of this element
 */
function ding_list_get_list_element_state($element) {
  $value = ding_base_get_value('ding_type', $element, 'field_state');
  return $value;
}

/**
 * Get the weight of a list element.
 *
 * @param object $element
 *   The element.
 *
 * @return int
 *   The weight of this element
 */
function ding_list_get_list_element_weight($element) {
  $value = ding_base_get_value('ding_type', $element, 'field_weight');
  return $value;
}
