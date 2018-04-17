<?php

/**
 * @file
 * API Functions.
 */

use DingList\DingList;

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
  $data = array();

  // Get list types that allow for attachment of the specific element type.
  $list_types = ding_list_get_list_types_by_operations(array(
    DING_LIST_OPERATION_ATTACH => array($type),
  ));
  if (empty($list_types)) {
    return array();
  }

  $lists = ding_list_get_lists($list_types);

  // Fill the $data array with actions, getting one action for each list.
  foreach ($lists as $list) {
    $list_title = $list->title;

    if (!ding_list_is_owner($list)) {
      if (!ding_list_user_has_access($list, DING_LIST_PERMISSION_EDIT)) {
        continue;
      }

      $list_title .= ' (' . $list->getOwnerName() . ')';
    }

    $data[] = array(
      'list_id' => $list->id,
      'title' => '<div class="list-title">' . $list_title . '</div><div class="add-to-list-button button">' . t('Add to list') . '</div>',
      'value' => $value,
      'type' => $type,
      'value_title' => $value_title,
    );
  }

  $context = array(
    'type' => $type,
    'value' => $value,
    'value_title' => $value_title,
  );
  drupal_alter('ding_list_add_to_list_data', $data, $context);

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
  $pretty_author = implode(', ', $creators);
  foreach ($creators as & $creator) {
    $creator = 'phrase.creator="' . $creator . '"';
  }
  if (isset($creator)) {
    if (user_is_logged_in()) {
      $lists = ding_list_get_lists(DING_LIST_TYPE_FOLLOW_AUTHOR);
      if (!empty($lists)) {
        foreach ($lists as $list) {
          if (!$list->hasElement($creator)) {
            $list_title = '<div class="list-title">' . $pretty_author . '</div><div class="add-to-list-button button">' . t('Follow the author') . '</div>';

            $data[] = array(
              'list_id' => $list->id,
              'title' => $list_title,
              'value' => $creator,
              'type' => DING_LIST_TYPE_FOLLOW_AUTHOR,
              'value_title' => $pretty_author,
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
    }
    else {
      $data[] = array(
        'custom' => array(
          'title' => t('Follow the author @author', array('@author' => $pretty_author)),
          'href' => 'ding-list/login-attach/' . DING_LIST_TYPE_FOLLOW_AUTHOR . '/' . $creator,
          'attributes' => array(
            'class' => array('use-ajax'),
          ),
          'query' => array('title' => $pretty_author),
          'html' => TRUE,
        ),
      );
    }
  }
  return $data;
}

/**
 * Create a token, used for to give users access to a list.
 *
 * @param \DingList\DingList $list
 *   The list object.
 * @param string $permission
 *   The permission wanted.
 * @param int $date
 *   Unix timestamp date, for when the token is created.
 *
 * @return string
 *   An md5 share token.
 */
function ding_list_share_token(DingList $list, $permission, $date = FALSE) {
  if ($date === FALSE) {
    $date = REQUEST_TIME;
  }

  return md5('prefix_' . $list->id . '_' . $list->owner . '_' . $permission . '_' . date('Ymd', $date));
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
  ), NULL, TRUE);

  // No lists no result.
  if ($lists === FALSE) {
    return FALSE;
  }

  shuffle($lists);

  // Find a non empty list.
  $max_try = 10;
  foreach ($lists as $list) {

    if (empty($list->elements)) {
      continue;
    }

    // Fail safe for big lists.
    if ($max_try-- < 1) {
      return FALSE;
    }

    // Pick randomly but weight newer elements.
    $element = ding_serendipity_pick_weighted_random($list->elements, 1);
    $element = current($element);

    $element_id = ding_list_convert_cql($element->value);

    $ting_entity = ting_object_load($element_id);

    if (empty($ting_entity)) {
      continue;
    }

    // Return as soon as we have found.
    return $ting_entity;

  }
  return FALSE;
}

/**
 * Make sure you're allowed to perform a certain action on a list.
 *
 * @param \DingList\DingList $list
 *   The list you want to operate on.
 * @param string $operation
 *   The operation you wish to perform.
 *
 * @return bool
 *   TRUE if the list has the operation, and FALSE if it doesn't.
 */
function ding_list_allowed(DingList $list, $operation) {
  $list_operations = ding_list_list_operations();
  return isset($list_operations[$list->type][$operation]);
}

/**
 * Move an element in a list down below another element.
 *
 * @param \DingList\DingList $list
 *   The list.
 * @param int $element
 *   ID of the element ot move.
 * @param int $previous
 *   ID of the element to position the $element after.
 *   If this is 0 the $element is positioned as the first element.
 *
 * @return bool
 *   If the move is successful or not.
 */
function ding_list_set_element_position(DingList $list, $element, $previous = 0) {
  try {
    ding_provider_invoke('openlist', 'set_element_after', $list->buildDataArray(), $element, $previous);
  }
  catch (Exception $e) {
    drupal_set_message(t("An error occurred while sorting your elements. Please contact the administrator if this problem persists."), 'error');
    return FALSE;
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
      unset($auto_create[$list->type]);
    }
  }

  // Create all the lists in the $auto_create array.
  foreach ($auto_create as $type => $nothing) {
    $list = new DingList(array(
      'type' => $type,
      'owner' => ding_provider_invoke('openlist', 'user_identifier', $account),
      'title' => $list_operations[$type]['_data']['default_title'],
    ));
    $list->save();
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
  $latest = isset($list->data['latest']) && is_numeric($list->data['latest']) ? $list->data['latest'] : 0;

  $save_list = FALSE;
  if (ding_user_is_provider_user($account)) {
    try {
      $creds = ding_user_get_creds();
      if (!empty($creds['name'])) {
        // Create a timestamp representing today.
        $today = mktime(0, 0, 0);

        $loans = ding_provider_invoke('historical_loans', 'get', $account, $latest);

        foreach ($loans as $loan) {
          if ($loan['loan_date'] < $today) {
            $save_list = TRUE;
            $ding_entity_id = variable_get('ting_agency', '') . ':' . $loan['id'];
            $list->attachElement(array(
              'type' => 'ting_object',
              'value' => $ding_entity_id,
              'note' => serialize($loan),
            ));
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
    $list->data['latest'] = mktime(0, 0, 0, date('n', $latest), date('j', $latest) + 1, date('Y', $latest));
    $list->save();
  }
  return TRUE;
}

/**
 * Add permissions to a list and user.
 *
 * @param \DingList\DingList $list
 *   The list to add the permissions to.
 * @param string $permission
 *   The permission to add.
 * @param object $account
 *   The user to give the permissions.
 */
function ding_list_set_permission(DingList $list, $permission, $account = NULL) {
  if ($account === NULL) {
    global $user;
    $account = $user;
  }

  $openlist_uid = ding_provider_invoke('openlist', 'user_identifier', $account);
  ding_provider_invoke('openlist', 'call_module', 'ListPermission', 'setPermission', array(
    $openlist_uid,
    $list->id,
    $permission,
  ), array('use_cache' => FALSE));

  ding_provider_invoke('openlist', 'clear_cache', 'lp' . $list->id);
  drupal_static_reset('ding_list_get_permission');
}

/**
 * Remove a permission.
 *
 * @param \DingList\DingList $list
 *   The list to add the permissions to.
 * @param object $account
 *   The user to give the permissions.
 */
function ding_list_remove_permission(DingList $list, $account = NULL) {
  if ($account === NULL) {
    global $user;
    $account = $user;
  }

  $openlist_uid = ding_provider_invoke('openlist', 'user_identifier', $account);
  ding_provider_invoke('openlist', 'call_module', 'ListPermission', 'removePermission', array(
    $openlist_uid,
    $list->id,
  ), array('use_cache' => FALSE));

  ding_provider_invoke('openlist', 'clear_cache', 'lp' . $list->id);
  drupal_static_reset('ding_list_get_permission');
}

/**
 * Get the users permissions to a list.
 *
 * @param \DingList\DingList $list
 *   List object.
 * @param object $account
 *   The user.
 *
 * @return bool|object
 *   The permissions entity for the user, or FALSE if there's no permission.
 */
function ding_list_get_permission(DingList $list, $account = NULL) {
  $permissions = &drupal_static(__FUNCTION__, array());

  if ($account === NULL) {
    global $user;
    $account = $user;
  }

  $key = $account->uid . '__' . $list->id;

  if (!isset($permissions[$key])) {
    $openlist_uid = ding_provider_invoke('openlist', 'user_identifier', $account);
    $permissions[$key] = ding_provider_invoke('openlist', 'call_module', 'ListPermission', 'getPermission', array(
      $openlist_uid,
      $list->id,
    ), array('cache_prefix' => 'lp' . $list->id));
  }

  return $permissions[$key];
}

/**
 * Check if the user has list permissions.
 *
 * @param \DingList\DingList $list
 *   List object.
 * @param string $permission
 *   The permission.
 * @param object $account
 *   The user.
 *
 * @return bool
 *   TRUE or FALSE depending on the permission exists.
 */
function ding_list_has_permission(DingList $list, $permission, $account = NULL) {
  $user_permission = ding_list_get_permission($list, $account);

  if (!$user_permission) {
    return FALSE;
  }

  return in_array($permission, ding_list_get_permission_permissions($user_permission['permission']));;
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
 * Check if a user is the owner of the list.
 *
 * @param \DingList\DingList $list
 *   List.
 * @param object $account
 *   User object.
 *
 * @return bool
 *   TRUE if the user is the owner.
 */
function ding_list_is_owner(DingList $list, $account = NULL) {
  if ($account === NULL) {
    global $user;
    $account = $user;
  }

  $account_openlist_id = ding_provider_invoke('openlist', 'user_identifier', $account);

  return $account_openlist_id == $list->owner;
}

/**
 * Check if a user has access to a list, with the given permissions.
 *
 * @param \DingList\DingList|int $list
 *   List or the lists id.
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
  // @TODO Implement permissions system.
  $access = &drupal_static(__FUNCTION__, array());

  // The access key is the key used by the static cache, and it's a unique key
  // defined by all the arguments given the function.
  $access_key = md5(serialize(func_get_args()));
  if (isset($access[$access_key])) {
    return $access[$access_key];
  }
  $access[$access_key] = FALSE;

  if ($account === NULL) {
    global $user;
    $account = $user;
  }

  if (user_access('ding_list administer lists', $account)) {
    $access[$access_key] = TRUE;
    return $access[$access_key];
  }

  if (is_numeric($list)) {
    $list = ding_list_get_list($list);
  }

  if (ding_list_is_owner($list, $account)) {
    $access[$access_key] = TRUE;
    return $access[$access_key];
  }

  if (isset($list->data['visibility']) && $list->data['visibility'] === 'public') {
    $access[$access_key] = TRUE;
    return $access[$access_key];
  }

  if (!empty($token)) {
    foreach (ding_list_get_permission_permissions() as $key => $array) {
      if (ding_list_check_token($list, $key, $token)) {
        $access[$access_key] = TRUE;

        if (user_is_logged_in() && !ding_list_has_permission($list, $key, $account)) {
          ding_list_set_permission($list, $key, $account);
        }

        return $access[$access_key];
      }
    }
  }

  if (ding_list_has_permission($list, $permission, $account)) {
    $access[$access_key] = TRUE;
    return $access[$access_key];
  }

  return $access[$access_key];
}

/**
 * Check a token.
 *
 * @param \DingList\DingList $list
 *   The List.
 * @param string $key
 *   The permission to check.
 * @param string $token
 *   The token to check.
 *
 * @return bool
 *   TRUE or FALSE if token is valid.
 */
function ding_list_check_token(DingList $list, $key, $token) {
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
