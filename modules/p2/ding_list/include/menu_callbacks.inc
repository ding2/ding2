<?php

/**
 * @file
 * Container for menu callback functions.
 */

/**
 * Reorder a list.
 *
 * @param string $list_id
 *   The ID of the list.
 *
 * @return array
 *   Ajax commands, with information about the process.
 */
function ding_list_set_order_callback($list_id) {
  if (empty($list_id) || !isset($_POST['item']) || !isset($_POST['previous'])) {
    return drupal_json_encode(array(
      'status' => FALSE,
    ));
  }
  $list = ding_list_get_list($list_id);

  $item = entity_load_single('ding_type', $_POST['item']);
  $previous = entity_load_single('ding_type', $_POST['previous']);
  ding_list_set_element_position($list, $item, $previous);

  $html = t('List changed');
  $commands = array();

  $commands[] = ajax_command_changed('#' . $context['html_id'], $html);

  return array(
    '#type' => 'ajax',
    '#commands' => $commands,
  );
}

/**
 * Attach an element to a list.
 *
 * @param string $type
 *   The element type.
 * @param string $list_id
 *   The ID of the list.
 * @param string $value
 *   Value of the element.
 *
 * @return array
 *   Ajax commands, with information about the process.
 */
function ding_list_attach_element_callback($type, $list_id, $value) {
  $commands = array();

  $list = ding_list_get_list($list_id);

  $op_infos = ding_list_list_operations();
  $op = $op_infos[$type];

  if (!ding_list_has_ding_list_element($list, $type, $value)) {
    $element = ding_list_create_ding_list_element($list, $type, array('value' => $value));

    if ($element !== FALSE) {

      if (isset($_GET['title'])) {
        $element->field_search_title[LANGUAGE_NONE] = array(array('value' => $_GET['title']));
        $element->save();
      }

      if (!empty($op['_data']['response_success'])) {
        // Translate the response.
        $response = t($op['_data']['response_success'], array('!name' => l($list->title, 'list/' . $list->id)));
      }
      else {
        $response = t('Added to !name', array('!name' => l($list->title, 'list/' . $list->id)));
      }
    }
    else {
      $response = t("An error occurred, your element wasn't created. Please contact the administrator if this problem persists.");
    }
  }
  else {
    $response = t('Already added to !name', array('!name' => l($list->title, 'list/' . $list->id)));
  }

  $commands[] = ajax_command_ding_popup('ding_list', t('List'), '<div class="ding-list-message">' . $response . '</div>');
  return array(
    '#type' => 'ajax',
    '#commands' => $commands,
  );
}

/**
 * Remove an element from a list.
 *
 * @param string $list_id
 *   The ID of the list.
 * @param string $element_id
 *   The ID of the element.
 *
 * @return array
 *   Ajax commands, with information about the process.
 */
function ding_list_remove_element_from_list_callback($list_id, $element_id) {
  $list = ding_list_get_list($list_id);
  $context = drupal_get_query_parameters();
  if (ding_list_detach_ding_list_element($list, explode(',', $element_id)) !== FALSE) {
    $html = t('Removed from !name', array('!name' => l($list->title, 'user/list/' . $list->id)));
  }
  else {
    $html = t("An error occurred while removing your element. Please contact the administrator if this problem persists.");
  }

  $status = array(
    'selector' => '#' . $context['html_id'],
    'message' => $html,
    'status' => TRUE,
    'refresh' => TRUE,
  );
  $commands = array();

  $commands[] = ajax_command_html('#' . $context['html_id'] . ' .action-message', $html, $status);

  return array(
    '#type' => 'ajax',
    '#commands' => $commands,
  );
}

/**
 * Delete a list.
 *
 * @param string $list_id
 *   The ID of the list.
 *
 * @return array
 *   Ajax commands, with information about the process.
 */
function ding_list_delete_list_callback($list_id) {
  $list = ding_list_get_list($list_id);

  ding_list_delete_list($list);

  $status = array(
    'status' => TRUE,
    'remove' => '.ding-type-ding-list',
  );

  $html = t('List deleted');
  $commands = array();
  $context = drupal_get_query_parameters();
  $commands[] = ajax_command_append('#' . $context['html_id'], $html, $status);

  return array(
    '#type' => 'ajax',
    '#commands' => $commands,
  );
}

/**
 * Private share message.
 *
 * @param string $list_id
 *   The ID of the list.
 *
 * @return array
 *   Ajax commands, with information about the process.
 */
function ding_list_private_share_message_callback($list_id, $community) {
  $list = ding_list_get_list($list_id);

  $commands = array();

  drupal_add_js(drupal_get_path('module', 'ding_list') . '/js/ding-list-private-sharer.js');

  $query = array();

  $commands[] = ajax_command_ding_popup(
    'ding_list',
    t('Info'),
    '<p>' . t('You need to make your list public, before you can share it on social media.') . '</p>' .
    '<p>' . l(t('Yes - make my list public, and share it.'), 'ding-list/share-list/public/' . $list_id . '/' . $community, array(
      'attributes' => array(
        'class' => array('private-sharer', 'use-ajax'),
      ),
    )) . '<br/>' .
    l(t('No - not right now.'), '#', array('external' => TRUE, 'attributes' => array('class' => array('close-popupbar')))) . '</p>'
  );

  return array(
    '#type' => 'ajax',
    '#commands' => $commands,
  );
}


/**
 * Set a list share permissions.
 */
function ding_list_share_list_callback($permission, $list_id, $community) {
  $commands = array();
  $list = ding_list_get_list($list_id);

  if ($list) {
    ding_list_edit_ding_list(
      $list,
      $list->title,
      NULL,
      TRUE,
      array(
        array(
          'name' => 'field_ding_list_status',
          'value_type' => 'value',
          'value' => $permission,
        ),
      )
    );

    $commands[] = array(
      'command' => 'ding_list_private_sharer',
      'result' => TRUE,
      'community' => $community,
    );
  }
  else {
    $commands[] = ajax_command_ding_popup(
      'ding_list',
      t('Error'),
      '<p>' . t("List doesn't exist.") . '</p>'
    );
  }

  return array(
    '#type' => 'ajax',
    '#commands' => $commands,
  );
}

/**
 * Fetch more list items for carousel's.
 *
 * @param string $list_id
 *   The id of the list to process.
 * @param string $offset
 *   The off-set into the list.
 */
function ding_list_carousel_ajax($list_id, $offset) {
  $build = array(
    'content' => array(),
    'offset' => -1,
  );

  $list = ding_list_get_list($list_id);

  // Check access to the list.
  if (ding_list_user_has_access($list)) {
    $ids = array();
    $items = ding_base_get_items('ding_type', $list, 'field_list_objects');
    foreach (array_slice($items, $offset, DING_LIST_CAROUSEL_CHUNK_SIZE) as $item) {
      $ids[] = $item['target_id'];
    }
    $entities = entity_load('ding_type', $ids);

    $object_ids = array();
    foreach ($entities as $entity) {
      $object_ids[] = ding_list_get_list_element_value($entity);
    }
    $entities = ding_entity_load_multiple($object_ids, 'ting_object');

    $content = array();
    foreach ($entities as $entity) {
      $content[] = array(
        '#type' => 'ding_carousel_item',
        '#content' => ting_object_view($entity, 'teaser'),
      );
    }

    // Calculate if there are more items in the list.
    $next_offset = -1;
    if ($offset + DING_LIST_CAROUSEL_CHUNK_SIZE <= count($items)) {
      $next_offset = $offset + DING_LIST_CAROUSEL_CHUNK_SIZE;
    }

    // If there's more items, add a placeholder at the end to signal the user
    // that it's loading.
    if ($next_offset > -1) {
      $content[] = array(
        '#type' => 'ding_carousel_item',
        '#placeholder' => TRUE,
      );
    }

    $build = array(
      'content' => drupal_render($content),
      'offset' => $next_offset,
    );
  }

  // Return JSON output.
  drupal_json_output($build);
}
