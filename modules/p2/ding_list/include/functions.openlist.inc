<?php

/**
 * @file
 * Functions related to openlist.
 */

/**
 * Reset the internal last updated field of the user.
 *
 * @param mixed $account
 *   The user account.
 */
function ding_list_reset_openlist_modified($account = NULL) {
  if ($account === NULL) {
    global $user;
    $account = $user;
  }

  $account->openlist_modified = 0;
  user_save($account);
}

/**
 * Create an array that maps a list of ids, to an entity.
 *
 * @param string $type
 *   The ding_type bundle.
 * @param string $property
 *   The name of the ids property.
 * @param array $ids
 *   The ids.
 *
 * @return array
 *   An array which maps all the ids to their entity.
 */
function ding_list_create_map($type, $property, array $ids) {
  if (empty($ids)) {
    return array();
  }

  $ids = array_unique($ids);

  $query = new EntityFieldQuery();
  $result = $query->entityCondition('entity_type', 'ding_type')
    ->entityCondition('bundle', $type)
    ->propertyCondition($property, $ids)
    ->execute();

  $map = array();
  if (!empty($result)) {
    $locals = entity_load('ding_type', array_keys($result['ding_type']));
    foreach ($locals as $local) {
      $map[$local->{$property}] = $local;
    }
  }
  return $map;
}

/**
 * Update the local database, with the changes from Openlist.
 *
 * @param mixed $account
 *   Which account to synchronize (defaults to the logged in user).
 *
 * @return bool
 *   TRUE if the function ran to the end, and FALSE if it ended before
 *   completing.
 *   Note that TRUE might not have actually synced anything, if there's
 *   no new lists or elements ot sync.
 */
function ding_list_sync_openlist($account = NULL) {
  if (!ding_provider_implements('openlist', 'user_identifier')) {
    return FALSE;
  }

  if ($account === NULL) {
    global $user;
    $account = $user;
  }

  // Get the last modified timestamp.
  $from = $account->openlist_modified;

  // Fetch the modified lists and elements.
  try {
    $id = ding_provider_invoke('openlist', 'user_identifier', $account);
    $openlist_lists = ding_provider_invoke('openlist', 'get_lists', $id, $from);
    $openlist_elements = ding_provider_invoke('openlist', 'get_user_elements', $id, $from);
  }
  catch (Exception $e) {
    return FALSE;
  }

  // Create 2 arrays that map the openlist ids to local ids.
  // One array for lists and one for elements.
  // While running through the lists update the $from so it got the latest
  // modified list or element.
  $list_map = $element_map = array();
  foreach ($openlist_lists as $list) {
    $list_map[] = $list['list_id'];
    $from = max($list['modified'], $from);
  }
  
  foreach ($openlist_elements as $element) {
    $list_map[] = $element['list_id'];
    $element_map[] = $element['element_id'];
    if ($element['previous'] > 0) {
      $element_map[] = $element['previous'];
    }
    $from = max($element['modified'], $from);
  }
  $list_map = ding_list_create_map('ding_list', 'openlist_id', $list_map);
  $element_map = ding_list_create_map('ding_list_element', 'openlist_id', $element_map);

  // If needed update the openlist_modified variable on the account.
  if ($from > $account->openlist_modified) {
    $account->openlist_modified = $from;
    user_save($account);
  }

  // Run through all the modified lists.
  foreach ($openlist_lists as $openlist_list) {
    // The list already exists, so we need to either edit or delete it.
    if (isset($list_map[$openlist_list['list_id']])) {
      $local_list = &$list_map[$openlist_list['list_id']];

      // We only edit the list is active (status = 1).
      if ($openlist_list['status'] == 1) {
        if (!isset($openlist_list['data']['fields']) || !is_array($openlist_list['data']['fields'])) {
          $openlist_list['data']['fields'] = array();
        }
        ding_list_edit_ding_list($local_list, $openlist_list['title'], $openlist_list['data']['more'], FALSE, $openlist_list['data']['fields']);
      }
      // Remove it locally.
      else {
        ding_list_delete_list($local_list, FALSE);
      }
    }
    // The list is not present in the local database, so we need to create it.
    else {
      // We only create the list, if it is active (status = 1).
      if ($openlist_list['status'] == 1) {
        if (!isset($openlist_list['data']['fields']) || !is_array($openlist_list['data']['fields'])) {
          $openlist_list['data']['fields'] = array();
        }
        $list_map[$openlist_list['list_id']] = ding_list_create_ding_list(
          $openlist_list['title'],
          $openlist_list['type'],
          $account,
          $openlist_list['data']['more'],
          $openlist_list['list_id'],
          $openlist_list['data']['fields']
        );
      }
    }
  }

  // Run through all the modified elements.
  $save_list = array();
  foreach ($openlist_elements as $openlist_element) {

    // Make sure the local list exists.
    if (!isset($list_map[$openlist_element['list_id']])) {
      continue;
    }

    // The element already exists, so we need to either edit or delete it.
    if (isset($element_map[$openlist_element['element_id']])) {
      // We only edit the list  if it is active (status = 1).
      if ($openlist_element['status'] == 1) {
        $local_element = $element_map[$openlist_element['element_id']];
        $local_list = &$list_map[$openlist_element['list_id']];

        $values = array();
        
        // Old version openlist saved object used id instead of value.
        if (isset($openlist_element['data']['id'])) {
          $values = array(
            'value' => $openlist_element['data']['id'],
          );
        }
        else {
          $values = $openlist_element['data'];
        }

        ding_list_edit_ding_list_element(
          $local_element,
          $openlist_element['data']['type'],
          $values,
          FALSE
        );

        // If the elemen has a previous id, get the element from the element
        // map.
        if ($openlist_element['previous'] > 0) {
          $previous_element = $element_map[$openlist_element['previous']];
        }
        else {
          $previous_element = new stdClass();
          $previous_element->id = 0;
        }

        $items = ding_base_get_items('ding_type', $local_list, 'field_list_objects');
        $new_order = array();
        foreach ($items as $key => $item) {
          if ($item['target_id'] !== $local_element->id) {
            $new_order[] = $item;
          }

          if ($item['target_id'] === $previous_element->id) {
            $new_order[] = array('target_id' => $local_element->id);
          }
        }
        if ($openlist_element['previous'] == 0) {
          array_unshift($new_order, array('target_id' => $local_element->id));
        }

        if ($new_order != $items) {
          $local_list->field_list_objects[LANGUAGE_NONE] = $new_order;
          $save_list[$openlist_element['list_id']] = $openlist_element['modified'];
        }
      }
      // Remove it locally.
      else {
        // Update the save_list, so we can save all the lists changed.
        $save_list[$openlist_element['list_id']] = $openlist_element['modified'];

        ding_list_detach_ding_list_element(
          $list_map[$openlist_element['list_id']],
          array($element_map[$openlist_element['element_id']]->id),
          // save_list.
          FALSE,
          // no_openlist.
          FALSE
        );
      }
    }
    // The element is not present in the local database, so we need to create
    // it.
    else {
      // We only create the element, if it has the status of 1
      if ($openlist_element['status'] == 1) {
        // Update the save_list, so we can save all the lists changed.
        $save_list[$openlist_element['list_id']] = $openlist_element['modified'];

        $values = array();
        // Old version openlist saved object used id instead of value.
        if (isset($openlist_element['data']['id'])) {
          $values = array(
            'value' => $openlist_element['data']['id'],
          );
        }
        // New openlist save method.
        else {
          $values = $openlist_element['data'];
        }

        $element = ding_list_create_ding_list_element(
          $list_map[$openlist_element['list_id']],
          $openlist_element['data']['type'],
          $values,
          $account,
          // save_list
          FALSE,
          $openlist_element['element_id']
        );
        $element_map[$element->openlist_id] = $element;
      }
    }
  }

  // Run through the save_list, update their modified and save them.
  foreach ($save_list as $openlist_id => $modified) {
    $list = $list_map[$openlist_id];
    $list->save();
  }
  
  return TRUE;
}
