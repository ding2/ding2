<?php

/**
 * @file
 * API Functions.
 */

require_once __DIR__ . '/functions.openlist.inc';
require_once __DIR__ . '/functions.handler.inc';

/**
 * Get the list of actions, depending on type and value.
 *
 * @param string $type
 *   The type of element.
 * @param mixed $value
 *   The value (most of the times this will be an entity object).
 * @param string $value_title
 *   Title of the element, which can override default titles.
 *
 * @return array
 *   An array of list actions available for the specific item, this will most
 *   likely be add to list actions.
 *   Every action is build up of an array that looks like:
 *    - list_id: The ID of the list.
 *    - title: Title of the action.
 *    - value: The given item value.
 *    - type: The given item type.
 *    - value_title: The given value_title.
 *    - custom: The custom is an array that is used in a links theme, as a
 *      single link.
 */
function ding_list_get_add_to_list_data($type, $value, $value_title = FALSE) {
  global $user;

  $data = array();

  // Get list types that allow for attachment of the specific element type.
  $list_types = ding_list_get_list_types_by_operations(array(
    DING_LIST_OPERATION_ATTACH => array($type),
  ));
  if (empty($list_types)) {
    return $data;
  }

  // Get all lists of the list_types given.
  $lists = ding_list_get_lists($list_types);
  if (empty($lists)) {
    return $data;
  }

  // Fill the $data array with actions, getting one action for each list.
  foreach ($lists as $list) {
    $list_title = $list->title;

    if ($list->uid != $user->uid) {
      if (!ding_list_user_has_access($list, DING_LIST_PERMISSION_EDIT)) {
        continue;
      }
      $username = ding_list_list_username($list);
      if ($username) {
        $list_title .= '(' . $username . ')';
      }
    }

    $data[] = array(
      'list_id' => $list->id,
      'title' => t('Add to @list', array('@list' => $list_title)),
      'value' => $value,
      'type' => $type,
      'value_title' => $value_title,
    );
  }

  // Add specific actions when the element is a ting_object.
  if ($type === 'ting_object') {
    $ting_object = ting_object_load($value);

    // Add a follow action for authors.
    $data = array_merge($data, ding_list_get_add_to_list_ting_object_creators($ting_object));
  }

  return $data;
}

/**
 * Get follow creator actions for a ting_object.
 *
 * @see ding_list_get_add_to_list_data()
 */
function ding_list_get_add_to_list_ting_object_creators($ting_object) {
  global $user;

  $data = array();

  $creators = $ting_object->getCreators();
  foreach ($creators as & $creator) {
    $creator = 'phrase.creator="' . $creator . '"';
  }
  if (isset($creator)) {
    $lists = ding_list_get_lists(DING_LIST_TYPE_FOLLOW_AUTHOR);

    foreach ($lists as $list) {
      if (!ding_list_has_ding_list_element($list, DING_LIST_TYPE_FOLLOW_AUTHOR, $creator)) {
        $pretty_author = implode(', ', $ting_object->getCreators());
        $list_title = t('Follow the author @author', array('@author' => $pretty_author));
        if ($list->uid != $user->uid) {
          $username = ding_list_list_username($list);
          if ($username) {
            $list_title .= '(' . $username . ')';
          }
        }

        $data[] = array(
          'list_id' => $list->id,
          'title' => $list_title,
          'value' => $creator,
          'type' => DING_LIST_TYPE_FOLLOW_AUTHOR,
          'value_title' => implode(', ', $ting_object->getCreators()),
        );
      }
      else {
        $list_title = t('Already following @author', array('@author' => implode(', ', $ting_object->getCreators())));
        $data[] = array(
          'custom' => array(
            'title' => $list_title,
          ),
        );
      }
    }
  }

  return $data;
}

/**
 * Create a token, used for to give users access to a list.
 *
 * @param object $list
 *   The list entity.
 * @param string $permission
 *   The permission wanted.
 * @param int $date
 *   Unix timestamp date, for when the token is created.
 *
 * @return string
 *   An md5 share token.
 */
function ding_list_share_token($list, $permission, $date = FALSE) {
  if ($date === FALSE) {
    $date = REQUEST_TIME;
  }

  return md5('prefix_' . $list->id . '_' . $list->created . '_' . $permission . '_' . date('Ymd', $date));
}

/**
 * Clean the operations list, so we only get operations.
 *
 * @param array $list_operations
 *   An array with list operations.
 *
 * @return array
 *   The cleaned list operations array.
 */
function ding_list_clean_list_operations(array $list_operations) {
  foreach ($list_operations as $list => & $operations) {
    if (isset($operations['_data'])) {
      unset($operations['_data']);
    }
  }

  return $list_operations;
}

/**
 * Get the list types which has a set of specific operations available.
 *
 * @param array|string $access
 *   An array of operations or a single operation.
 *
 * @return array
 *   The list types having the given operations.
 */
function ding_list_get_list_types_by_operations($access) {
  $list_operations = ding_list_list_operations();
  $list_operations = ding_list_clean_list_operations($list_operations);

  if (!is_array($access)) {
    $access = array($access => TRUE);
  }

  $list_types = array();
  foreach ($list_operations as $list => $operations) {
    $use_list = FALSE;

    // If the asked operation is in the list operations.
    if (array_intersect_key($access, $operations) === $access) {
      foreach ($access as $operation => $types) {
        // Use the list if the list operation is TRUE, or the specific
        // operation is TRUE and types is not false.
        if ($types === TRUE || ($operations[$operation] === TRUE && $types !== FALSE)) {
          $use_list = TRUE;
        }
        // Assume types is an array when it's not TRUE or FALSE.
        // And if the array is matched with the operations use the list.
        elseif ($types !== FALSE && array_intersect($types, $operations[$operation]) === $types) {
          $use_list = TRUE;
        }
        else {
          $use_list = FALSE;
          break;
        }
      }
    }

    if ($use_list) {
      $list_types[] = $list;
    }
  }

  return $list_types;
}

/**
 * Fetch some random ding_object from user list.
 *
 * @return mixed
 *   The random ting_object. Or FALSE otherwise.
 */
function ding_list_get_random_user_list_item() {

  // Select among these types.
  $lists = ding_list_get_lists(array(
    DING_LIST_TYPE_USER_LIST,
    DING_LIST_TYPE_LOAN_HISTORY,
    DING_LIST_TYPE_BOOKS_READ,
    DING_LIST_TYPE_REMEMBER,
  ));

  // No lists no result.
  if ($lists === FALSE) {
    return FALSE;
  }

  shuffle($lists);

  // Find a non empty list.
  foreach ($lists as $list) {
    $items = field_get_items('ding_type', $list, 'field_list_objects');
    if (isset($items[0]['target_id'])) {
      $index = rand(0, count($items) - 1);
      $element = entity_load_single('ding_type', $items[$index]['target_id']);
      $element_id = ding_list_get_list_element_value($element);

      $element_id = ding_list_convert_cql($element_id);
      $ting_entity = ting_object_load($element_id);
      // Return as soon as we have found.
      return $ting_entity;
    }
  }
  return FALSE;
}

/**
 * Make sure you're allowed to perform a certain action on a list.
 *
 * @param object $list
 *   The list you want to operate on.
 * @param string $operation
 *   The operation you wish to perform.
 *
 * @return bool
 *   TRUE if the list has the operation, and FALSE if it doesn't.
 */
function ding_list_allowed($list, $operation) {
  $list_operations = ding_list_list_operations();

  return isset($list_operations[ding_base_get_value('ding_type', $list, 'field_list_type')][$operation]);
}

/**
 * Load keys from elements in a list of type $key_type.
 *
 * @param object $user
 *   User account.
 * @param mixed $lid
 *   ID of user list OR list identifier.
 * @param mixed $key_type
 *   Optional type of key to extract.
 *
 * @return array
 *   An array of keys.
 */
function ding_list_load_keys($user, $lid, $key_type = FALSE) {
  $keys = array();
  if (is_numeric($lid)) {
    // Load certain list.
    $list = entity_load('ding_type', array($lid));
    if ($list === FALSE) {
      return array();
    }
    $list = array_shift($list);
  }
  else {
    // Load named list.
    $lists = ding_list_get_lists($lid, $user, array(0, 1));
    if ($lists === FALSE) {
      return array();
    }
    $list = array_shift($lists);
  }

  // Load list elements.
  $items = field_get_items('ding_type', $list, 'field_list_objects');
  if ($items !== FALSE) {
    $keys = array();
    foreach ($items as $item) {
      $keys[] = $item['target_id'];
    }

    // Load list entities.
    $elements = entity_load('ding_type', $keys);
    $keys = array();
    foreach ($elements as $element) {
      $type = ding_base_get_value('ding_type', $element, 'field_element_type');
      if ($type !== FALSE && (!$key_type || $type === 'taxonomy_term')) {
        $element_id = ding_base_get_value('ding_type', $element, 'field_' . $type);
        $keys[] = $element_id;
      }
    }
  }
  return $keys;
}

/**
 * Check to see if a list has a specific element.
 *
 * @param object $list
 *   The ding_list to delete.
 * @param string $type
 *   Type of the ding_list_element. This is put into the field_element_type,
 *   and determines which field_[TYPE] to save the $id in.
 * @param int $id
 *   The id of the element. This is a string so the id can be a ting_object
 *   id. It can also be a simple string, which is useful when adding a search
 *   query for example.
 *
 * @return mixed
 *   If the list has the element, return that element entity, if not return
 *   FALSE
 */
function ding_list_has_ding_list_element($list, $type, $id) {
  // Get the elements in the list.
  $elements = ding_list_load_elements($list);

  foreach ($elements as $element) {
    $element_value = ding_list_get_list_element_value($element);
    if ($element_value !== FALSE && $element_value === $id) {
      return $element;
    }
  }

  return FALSE;
}

/**
 * Get the position of an element in the list.
 *
 * @param object $list
 *   If this is a numeric value, it will automatically load the ding_list
 *   object.
 * @param object $element
 *   The element you want to move.
 *
 * @return bool|int
 *   The position of the element in the list. Or explicit FALSE if it doesn't
 *   exist in the list.
 */
function ding_list_get_element_position(&$list, $element) {
  $items = ding_base_get_items('ding_type', $list, 'field_list_objects');
  foreach ($items as $key => $item) {
    if ($item['target_id'] == $element->id) {
      return $key;
    }
  }

  return FALSE;
}

/**
 * Move an element in a list down below another element.
 *
 * @param object $list
 *   If this is a numeric value, it will automatically load the ding_list
 *   object.
 * @param object $element
 *   The element you want to move.
 * @param mixed $previous
 *   The element to position the element being moved after. If this is false
 *   it will move the element to the first position of the list.
 * @param bool $tell_openlist
 *   If this is true (as by default) it will tell the openlist service about
 *   the changes. When synchronizing this would be set to false.
 *
 * @return bool
 *   If the move is successful or not.
 */
function ding_list_set_element_position(&$list, $element, $previous = FALSE, $tell_openlist = TRUE) {
  $transaction = db_transaction();

  if (!$previous) {
    $previous = new stdClass();
    $previous->id = 0;
    $previous->openlist_id = 0;
  }

  $items = ding_base_get_items('ding_type', $list, 'field_list_objects');
  $new_order = array();
  foreach ($items as $key => $item) {
    if ($item['target_id'] !== $element->id) {
      $new_order[] = $item;
    }

    if ($item['target_id'] === $previous->id) {
      $new_order[] = array('target_id' => $element->id);
    }
  }
  if ($previous->id == 0) {
    array_unshift($new_order, array('target_id' => $element->id));
  }

  if ($new_order != $items) {
    if (ding_provider_implements('openlist', 'set_element_after') && $tell_openlist === TRUE) {
      try {
        ding_provider_invoke('openlist', 'set_element_after', $element->openlist_id, $previous->openlist_id);
      }
      catch (Exception $e) {
        $transaction->rollback();
        drupal_set_message(t("An error occurred while sorting your elements. Please contact the administrator if this problem persists."), 'error');
        return FALSE;
      }
    }

    $list->field_list_objects[LANGUAGE_NONE] = $new_order;
    $list->save();
  }

  return TRUE;
}

/**
 * Create all missing lists with the autocreate option, for a specific user.
 *
 * @param mixed $account
 *   The acount to autocreate lists for.
 */
function ding_list_setup_autocreated($account = NULL) {
  $list_operations = ding_list_list_operations();

  // Get all the list types with autocreate.
  $auto_create = ding_list_get_list_types_by_operations(DING_LIST_OPERATION_AUTO_CREATE);
  $lists = ding_list_get_lists($auto_create, $account);
  $auto_create = array_flip($auto_create);

  // Run through the already created lists, and exclude them from the
  // $auto_create variable.
  if ($lists !== FALSE) {
    foreach ($lists as $list) {
      $type = ding_base_get_value('ding_type', $list, 'field_list_type');
      unset($auto_create[$type]);
    }
  }

  // Create all the lists in the $auto_create array.
  foreach ($auto_create as $type => $nothing) {
    ding_list_create_ding_list($list_operations[$type]['_data']['default_title'], $type, $account);
  }
}

/**
 * Update the users historical loans.
 *
 * @param mixed $account
 *   The acount to autocreate lists for.
 *
 * @return bool|string
 *   Will return a message on failure, or an explicit TRUE on update.
 */
function ding_list_update_historical_loans($account = NULL) {
  if ($account === NULL) {
    global $user;
    $account = user_load($user->uid);
  }

  // Get the historical loan list.
  $list = ding_list_get_list(DING_LIST_TYPE_LOAN_HISTORY, $account);
  // Get the last update from the list, or set it to 0 if it doesn't
  // exist.
  $latest = isset($list->more) && is_numeric($list->more) ? $list->more : 0;

  $save_list = FALSE;
  if (ding_user_is_provider_user($account)) {
    try {
      $creds = ding_user_get_creds($account);
      if (!empty($creds['name'])) {
        // Create a timestamp representing today.
        $today = mktime(0, 0, 0);

        $loans = ding_provider_invoke('historical_loans', 'get', $account, $latest);

        foreach ($loans as $loan) {
          if ($loan['loan_date'] < $today) {
            $save_list = TRUE;
            $ding_entity_id = variable_get('ting_agency', '') . ':' . $loan['id'];
            ding_list_create_ding_list_element($list, 'ting_object', array(
              'value' => $ding_entity_id,
              'note' => serialize($loan),
            ), $account, FALSE);
            $latest = max($latest, $loan['loan_date']);
          }
        }
      }
    }
    catch (Exception $e) {
      return t('Sorry but no list is available at this time');
    }
  }

  if ($save_list) {
    // Set the latest time to tomorrow.
    $latest = mktime(0, 0, 0, date('n', $latest), date('j', $latest) + 1, date('Y', $latest));
    ding_list_edit_ding_list($list, $list->title, $latest);
  }
  return TRUE;
}

/**
 * Load recent nodes tagged with $tids.
 *
 * @param array $tids
 *   An array of taxonomy term ids to match with nodes. The function will Load
 *   nids of nodes which are tagged with one or more of these ids.
 *   This parameter is required.
 * @param mixed $type
 *   If provided the result will only contain nodes of this node type.
 * @param mixed $limit
 *   If provided the result will be limited to this number.
 *
 * @return array
 *   An array of nids tagged with one or more of the provided taxonomy terms.
 */
function ding_list_tids_to_nids(array $tids, $type = FALSE, $limit = FALSE) {
  // No tids no nids.
  if (empty($tids)) {
    return array();
  }

  // Setup select query with the provided tids as a condition.
  $query = db_select('taxonomy_index', 't')
    ->condition('tid', $tids, 'IN')
    ->addTag('node_access');

  // Join the node table.
  $query->join('node', 'n', 'n.nid = t.nid');

  // If a limit has been provided add this to the query.
  if ($limit !== FALSE) {
    $query->range(0, $limit);
  }

  // Published nodes only.
  $query->condition('n.status', 1);

  // Optional type(=bundle) filter.
  if ($type !== FALSE) {
    $query->condition('n.type', $type);
  }

  // Select the nid and order by the time of creation.
  $query->addField('t', 'nid');
  $query->orderBy('t.created', "DESC");

  // Return the column of nids.
  return $query->execute()->fetchCol();
}

/**
 * Add permissions to a list and user.
 *
 * @param object $list
 *   The list to add the permissions to.
 * @param string $permission
 *   The permission to add.
 * @param object $account
 *   The user to give the permissions.
 */
function ding_list_add_permission($list, $permission, $account = NULL) {
  if ($account === NULL) {
    global $user;
    $account = $user;
  }

  if (!ding_list_has_permission($list, $permission, $account)) {

    $element = ding_list_get_permission($list, $account);

    $add_to_list = FALSE;
    if ($element === FALSE) {
      $add_to_list = TRUE;
      $element = entity_create('ding_type', array(
        'type' => 'permission',
        'title' => '[' . $list->id . ']' . $list->title . ': ' . $account->name,
      ));

      $id = $account->uid;
      if (ding_provider_implements('openlist', 'user_identifier')) {
        $id = ding_provider_invoke('openlist', 'user_identifier', $account);
      }
      $element->field_ding_list_user[LANGUAGE_NONE] = array(array('value' => $id));
    }

    $element->field_ding_list_permission[LANGUAGE_NONE] = array(array('value' => $permission));

    entity_save('ding_type', $element);

    if ($add_to_list) {
      $list->field_ding_list_permissions[LANGUAGE_NONE][] = array('target_id' => $element->id);
      $list->save();
    }
  }
}

/**
 * Simple helper to set the permission on the entity.
 *
 * @param object $entity
 *   The entity to set the permission on.
 * @param string $permission
 *   The permission.
 *
 * @return object
 *   The given entity.
 */
function ding_list_set_permission($entity, $permission) {
  $entity->field_ding_list_permission[LANGUAGE_NONE] = array(array('value' => $permission));
  entity_save('ding_type', $entity);

  return $entity;
}

/**
 * Get owner name of the list.
 *
 * @param object $list
 *   The list entity.
 *
 * @return string
 *   The username (or an empty string if no username was retrieved).
 */
function ding_list_list_username($list) {
  $owner = user_load($list->uid);

  if (!empty($owner->data) && isset($owner->data['display_name'])) {
    return $owner->data['display_name'];
  }

  return t('Another loaner');
}

/**
 * Get the users permissions to a list.
 *
 * @param object $list
 *   List entity.
 * @param object $account
 *   The user.
 *
 * @return bool|object
 *   The permissions entity for the user, or FALSE if there's no permission.
 */
function ding_list_get_permission($list, $account = NULL) {
  if ($account === NULL) {
    global $user;
    $account = $user;
  }

  $query = db_select('eck_ding_type', 'edt')->fields('edt', array('id'))->condition('edt.type', 'permission');

  $query->join('field_data_field_ding_list_permissions', 'fdlps', 'fdlps.field_ding_list_permissions_target_id = edt.id');
  $query->condition('fdlps.entity_id', $list->id);

  $id = $account->uid;
  if (ding_provider_implements('openlist', 'user_identifier')) {
    $id = ding_provider_invoke('openlist', 'user_identifier', $account);
  }

  $query->join('field_data_field_ding_list_user', 'fdlu', 'fdlu.entity_id = edt.id');
  $query->condition('fdlu.field_ding_list_user_value', $id);

  $result = $query->execute()->fetchField();

  if ($result !== FALSE) {
    return entity_load_single('ding_type', $result);
  }

  return FALSE;
}

/**
 * Check if the user has list permissions.
 *
 * @param object $list
 *   List entity.
 * @param string $permission
 *   The permission.
 * @param object $account
 *   The user.
 *
 * @return bool
 *   TRUE or FALSE depending on the permission exists.
 */
function ding_list_has_permission($list, $permission, $account = NULL) {
  $element = ding_list_get_permission($list, $account);

  if ($element === FALSE) {
    return FALSE;
  }

  $permissions = ding_list_get_permission_permissions(ding_base_get_value('ding_type', $element, 'field_ding_list_permission'));
  return in_array($permission, $permissions);
}

/**
 * Remove a permission (automatically remove it from the list as well).
 *
 * @param object $element
 *   The permission element.
 *
 * @retun bool
 *   If the permissions were successfully removed.
 */
function ding_list_remove_permission($element) {
  $query = db_select('eck_ding_type', 'edt')
    ->fields('edt', array('id'))
    ->condition('edt.type', 'ding_list');

  $query->join('field_data_field_ding_list_permissions', 'fdlps', 'fdlps.entity_id = edt.id');
  $query->condition('fdlps.field_ding_list_permissions_target_id', $element->id);

  $result = $query->execute()->fetchField();
  if ($result !== FALSE) {
    $list = entity_load_single('ding_type', $result);
  }
  else {
    return FALSE;
  }

  $items = ding_base_get_items('ding_type', $list, 'field_ding_list_permissions');
  $keep = array();
  foreach ($items as $item) {
    if ($item['target_id'] != $element->id) {
      $keep[] = $item;
    }
  }

  $list->field_ding_list_permissions[LANGUAGE_NONE] = $keep;
  entity_save('ding_type', $list);
  entity_delete('ding_type', $element->id);

  return TRUE;
}

/**
 * Get the array of permissions connected to the permission.
 */
function ding_list_get_permission_permissions($permission = FALSE) {
  $matrix = array(
    DING_LIST_PERMISSION_VIEW => array(DING_LIST_PERMISSION_VIEW),
    DING_LIST_PERMISSION_EDIT => array(DING_LIST_PERMISSION_EDIT, DING_LIST_PERMISSION_VIEW),
  );

  if ($permission === FALSE || !isset($matrix[$permission])) {
    return $matrix;
  }

  return $matrix[$permission];
}

/**
 * Check if a user has access to a list, with the given permissions.
 *
 * @param object $list
 *   List entity.
 * @param string $permission
 *   The permission to check against.
 * @param object $account
 *   The user account.
 * @param string $token
 *   If a token is given, it will be checked against the last 7 days of
 *   share tokens. If there's a hit permissions will be added.
 *
 * @return bool
 *   TRUE or FALSE depending on the user has access.
 */
function ding_list_user_has_access($list, $permission = DING_LIST_PERMISSION_VIEW, $account = NULL, $token = FALSE) {
  $access = &drupal_static(__FUNCTION__, array());

  // The access key is the key used by the static cache, and it's a unique key
  // defined by all the arguments given the function.
  $access_key = md5(serialize(func_get_args()));
  if (isset($access[$access_key])) {
    return $access[$access_key];
  }

  if (ding_base_get_value('ding_type', $list, 'field_list_type') == DING_LIST_TYPE_LOAN_HISTORY
      && !variable_get('user_consent_activate')) {
    $access[$access_key] = FALSE;
    return $access[$access_key];
  }

  if ($account === NULL) {
    global $user;
    $account = $user;
  }

  // Is owner.
  if ($account->uid == $list->uid) {
    $access[$access_key] = TRUE;
    return $access[$access_key];
  }

  // List share status.
  switch (ding_base_get_value('ding_type', $list, 'field_ding_list_status', 'value', 'private')) {
    case 'private':
      $access[$access_key] = FALSE;
      return $access[$access_key];

    case 'public':
      $access[$access_key] = $permission == DING_LIST_PERMISSION_VIEW;
      return $access[$access_key];
  }

  // User not logged in.
  if (!user_is_logged_in()) {
    $access[$access_key] = FALSE;

    // Check token anonymous.
    if (!empty($token)) {
      foreach (ding_list_get_permission_permissions() as $key => $array) {
        if (ding_list_check_token($list, $key, $token)) {
          $access[$access_key] = TRUE;
        }
      }
    }
    return $access[$access_key];
  }

  // Has permissions in table.
  if (ding_list_has_permission($list, $permission, $account)) {
    $access[$access_key] = TRUE;
    return $access[$access_key];
  }

  // Check token for logged in users.
  if (!empty($token)) {
    if ($account->uid > 0) {
      foreach (ding_list_get_permission_permissions() as $key => $array) {
        if (ding_list_check_token($list, $key, $token)) {
          ding_list_add_permission($list, $key, $account);
          $permissions = ding_list_get_permission_permissions($key);
          $access[$access_key] = in_array($permission, $permissions);
          return $access[$access_key];
        }
      }
    }
  }

  $access[$access_key] = FALSE;

  return $access[$access_key];
}

/**
 * Check a token.
 *
 * @param object $list
 *   The List.
 * @param string $key
 *   The permission to check.
 * @param string $token
 *   The token to check.
 *
 * @return bool
 *   TRUE or FALSE if token is valid.
 */
function ding_list_check_token($list, $key, $token) {
  // A token only works 7 days, so create a token for each of the
  // previous 7 days and test it against the given token.
  for ($i = 0; $i < 7; $i++) {
    $share_token = ding_list_share_token($list, $key, mktime(0, 0, 0, date('n'), date('j') - $i));
    if ($token == $share_token) {
      return TRUE;
    }
  }

  return FALSE;
}

/**
 * Get count of followers for a list.
 *
 * @param object $list
 *   The list entity.
 *
 * @return int
 *   The followers count.
 */
function ding_list_get_list_followers_count($list) {
  $query = db_select('field_data_field_value', 'fv')
    ->fields('fv', array('field_value_value'))
    ->condition('fv.field_value_value', $list->id);

  $query->join('field_data_field_element_type', 'ft', 'ft.entity_id = fv.entity_id');
  $query->condition('ft.field_element_type_value', 'ding_list');

  return $query->countQuery()
    ->execute()
    ->fetchField();
}
