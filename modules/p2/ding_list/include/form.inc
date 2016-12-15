<?php

/**
 * @file
 * Forms used by ding_list.
 */

/**
 * Implements hook_forms().
 */
function ding_list_forms($form_id, $args) {
  $forms = array();

  // Use the ding_list_remove_element_form for all ding_list_remove_element_*
  // forms.
  if (substr($form_id, 0, 24) == 'ding_list_remove_element') {
    $forms[$form_id] = array('callback' => 'ding_list_remove_element_form');
  }

  return $forms;
}

/**
 * Form to remove and element from a list.
 */
function ding_list_remove_element_form($form, &$form_state, $element) {
  $list = ding_list_get_list_by_element($element);

  if (!ding_list_user_has_access($list, 'edit') || !ding_list_allowed($list, DING_LIST_OPERATION_DETACH)) {
    return $form;
  }

  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Remove from list'),
    '#attributes' => array('class' => array('close-btn')),
  );

  return $form;
}

/**
 * Submit handler for the ding_list_remove_element_form form.
 */
function ding_list_remove_element_form_submit($form, &$form_state) {
  // Get the first argument of the ding_list_remove_ekement_form ($element).
  $element = $form_state['build_info']['args'][0];
  $list = ding_list_get_list_by_element($element);
  if ($list) {
    ding_list_detach_ding_list_element($list, array($element->id));
  }
}

/**
 * Add an element to a list.
 *
 * @param string $type
 *   The type of element to add.
 * @param string $value
 *   The value of the element, typically an identifier.
 * @param string $title
 *   If there's more than 1 list, use this as the title for the submit button,
 *   when there's only a single list use that list add text as submit text.
 */
function ding_list_add_element_form($form, &$form_state, $type, $value, $title = 'Dinglist') {
  if (is_array($type)) {
    $type = key($type);
  }

  $options = ding_list_get_add_to_list_data($type, $value);
  if (count($options) > 1) {
    $submit_title = $title;

    $form['list'] = array(
      '#type' => 'select',
      '#options' => array(),
    );

    foreach ($options as $option) {
      $form['list']['#options'][$option['list_id']] = $option['title'];
      if ($option['value'] != $value) {
        $form_state['special_lists'][$option['list_id']] = array(
          'type' => $option['type'],
          'value' => $option['value'],
        );
      }
    }
  }
  else {
    $list = current($options);
    if (!ding_list_has_ding_list_element(ding_list_get_list($list['list_id']), $type, $value)) {
      $form['list'] = array(
        '#type' => 'hidden',
        '#value' => $list['list_id'],
      );

      $submit_title = $list['title'];
    }
  }

  if (isset($form['list'])) {
    $form['submit'] = array(
      '#type' => 'submit',
      '#value' => $submit_title,
      '#ajax' => array(
        'callback' => 'ding_list_add_element_form_callback',
        'wrapper' => 'ding-list-add-element-form',
      ),
    );
  }

  return $form;
}

/**
 * Submit handler for the ding_list_add_element form.
 */
function ding_list_add_element_form_submit($form, &$form_state) {
  // Get the arguments given the ding_list_add_element form ($type and $value).
  $type = $form_state['build_info']['args'][0];
  if (is_array($type)) {
    $type = current($type);
  }
  $value = $form_state['build_info']['args'][1];

  $list = ding_list_get_list($form_state['values']['list']);
  if (isset($form_state['special_lists'][$form_state['values']['list']])) {
    $type = $form_state['special_lists'][$form_state['values']['list']]['type'];
    $value = $form_state['special_lists'][$form_state['values']['list']]['value'];
  }

  if (is_array($value)) {
    $value = current($value);
  }

  // Only add the new element, if it's not already added.
  if (!ding_list_has_ding_list_element($list, $type, $value)) {
    $element = ding_list_create_ding_list_element($list, $type, array('value' => $value));

    // When adding a search_query use the $extra_data (3) argument as value.
    // This allows for custom titles in search query elements.
    if ($type == 'search_query') {
      if (!empty($form_state['build_info']['args'][3])) {
        $element->field_search_title[LANGUAGE_NONE][] = array('value' => $form_state['build_info']['args'][3]);
      }
      else {
        $element->field_search_title[LANGUAGE_NONE][] = array('value' => $value);
      }
      $element->save();
    }

    if ($element !== FALSE) {
      $form_state['storage']['response_html'] = t('Added to !name', array('!name' => l($list->title, 'list/' . $list->id)));
    }
    else {
      $form_state['storage']['response_html'] = t("An error occurred, your element wasn't created. Please contact the administrator if this problem persists.");
    }
  }
  else {
    $form_state['storage']['response_html'] = t('Already added to !name', array('!name' => l($list->title, 'list/' . $list->id)));
  }
}

/**
 * Ajax handler when using the ding_list_add_element form to add an element.
 */
function ding_list_add_element_form_callback($form, &$form_state) {
  $response = array(
    '#type' => 'ajax',
    '#commands' => array(),
  );

  $html = theme('ding_list_message', array('message' => $form_state['storage']['response_html']));
  // Popup.
  $response['#commands'][] = ajax_command_ding_popup('ding_list', t('List'), $html);

  return $response;
}

/**
 * The form used to create a ding_list object.
 *
 * If an existing ding_list object is given, that object is editted instead
 * of creating a new object.
 *
 * @param mixed $existing
 *   This is the existing ding_list object.
 */
function ding_list_create_list_form($form, &$form_state, $existing = FALSE) {
  global $user;

  if ($existing !== FALSE) {
    $form_state['existing'] = $existing->id;

    if (isset($form_state['storage']['confirm'])) {
      $form['#submit'] = array('ding_list_create_list_form_submit_delete');

      $tmp = confirm_form(
        $form,
        t('Do you really want to delete !list?', array('!list' => check_plain($existing->title))),
        current_path(),
        t('Do you really want to delete !list?', array('!list' => check_plain($existing->title)))
      );

      return $tmp;
    }

    $note = field_get_items('ding_type', $existing, 'field_notes');
    if ($note !== FALSE) {
      $note = $note[0]['value'];
    }
  }
  else {
    $form_state['existing'] = FALSE;
  }

  $form['title'] = array(
    '#type' => 'textfield',
    '#title' => t('Title'),
    '#required' => TRUE,
    '#default_value' => isset($existing->title) ? $existing->title : '',
  );

  $form['notes'] = array(
    '#type' => 'textarea',
    '#title' => t('Note'),
    '#default_value' => isset($note) ? $note : '',
  );

  if ($existing) {
    // The user can is always allowed to edit existing lists.
    $form['actions']['edit_list'] = array(
      '#type' => 'submit',
      '#value' => t('Save list'),
    );

    if (ding_list_allowed($existing, DING_LIST_OPERATION_DELETE)) {
      $form['actions']['delete_list'] = array(
        '#type' => 'submit',
        '#value' => t('Delete list'),
      );
      if ($existing->uid == $user->uid) {
        $form['actions']['delete_list']['#submit'] = array('ding_list_create_list_form_submit_delete');
      }
      else {
        $form['actions']['delete_list']['#submit'] = array('ding_list_create_list_form_submit_delete_share');
      }
    }
  }
  else {
    $form['actions']['add_list'] = array(
      '#type' => 'submit',
      '#value' => t('Add new list'),
    );
  }

  $form['actions']['cancel'] = array(
    '#type' => 'submit',
    '#value' => t('Cancel'),
    '#submit' => array('ding_list_create_list_form_submit_cancel'),
    '#limit_validation_errors' => array(),
  );

  // If auto add is set, add the hidden fields that will enable autoadding
  // an element to the list after creation.
  if (isset($_GET['at'])) {
    $form['auto_add_type'] = array(
      '#type' => 'hidden',
      '#value' => $_GET['at'],
    );

    $form['auto_add_value'] = array(
      '#type' => 'hidden',
      '#value' => $_GET['av'],
    );
  }

  return $form;
}

/**
 * Cancel button on create submit.
 */
function ding_list_create_list_form_submit_cancel($form, &$form_state) {
  // You cancelled, nothing is happening.
  if (!empty($form_state['existing'])) {
    $form_state['redirect'] = 'list/' . $form_state['existing'];
  }
  else {
    $form_state['redirect'] = 'user';
  }
}

/**
 * Delete list handler.
 */
function ding_list_create_list_form_submit_delete($form, &$form_state) {
  if (!isset($form_state['storage']['confirm'])) {
    $form_state['storage']['confirm'] = TRUE;
    $form_state['rebuild'] = TRUE;
    return;
  }

  if (!$form_state['existing']) {
    return;
  }

  $list = ding_list_get_list($form_state['existing']);
  ding_list_delete_list($list);

  $form_state['redirect'] = 'user/' . $GLOBALS['user']->uid . '/dinglists';
}

/**
 * Remove share from list.
 */
function ding_list_list_permissions_form_unfollow_shared($form, &$form_state) {
  $permission = ding_list_get_permission($form_state['build_info']['args'][0]);
  ding_list_remove_permission($permission);

  $form_state['redirect'] = 'user/' . $GLOBALS['user']->uid . '/dinglists';
}

/**
 * The create_list_form submit handler.
 */
function ding_list_create_list_form_submit($form, &$form_state) {
  // Create the new list object.
  if (!$form_state['existing']) {
    $list = ding_list_create_ding_list(
      $form_state['values']['title'],
      DING_LIST_TYPE_USER_LIST,
      NULL,
      NULL,
      NULL,
      array(
        array(
          'name' => 'field_notes',
          'value_type' => 'value',
          'value' => $form_state['values']['notes'],
        ),
      )
    );

    if ($list === FALSE) {
      drupal_set_message(t("An error occurred, your list wasn't created. Please contact the administrator if this problem persists."), 'error');
      return;
    }

    drupal_set_message(t(
        "You've create the list !list.<br/>Read more about how you use the lists !help",
        array(
          '!list' => l($list->title, 'list/' . $list->id),
          '!help' => l(t('Here'), 'help/lists'),
        )
      ));
  }
  else {
    $list = ding_list_get_list($form_state['existing']);

    ding_list_edit_ding_list(
      $list,
      $form_state['values']['title'],
      NULL,
      TRUE,
      array(
        array(
          'name' => 'field_notes',
          'value_type' => 'value',
          'value' => $form_state['values']['notes'],
        ),
      )
    );
  }

  if (isset($form_state['values']['auto_add_type'])) {
    ding_list_create_ding_list_element($list, $form_state['values']['auto_add_type'], array('value' => $form_state['values']['auto_add_value']));
  }

  $form_state['redirect'] = 'list/' . $list->id;
}

/**
 * A list permissions handler form.
 *
 * This is a pure ajax interface form.
 */
function ding_list_list_permissions_form($form, $form_state, $list = FALSE) {
  if (!ding_list_user_has_access($list, 'owner')) {
    $form['unfollow_shared'] = array(
      '#type' => 'submit',
      '#value' => t('Unfollowed shared list'),
      '#submit' => array('ding_list_list_permissions_form_unfollow_shared'),
    );

    return $form;
  }

  // Get the status options from the field_ding_list_status allowed values.
  $status = field_info_field('field_ding_list_status');
  $status = $status['settings']['allowed_values'];

  // Translate the allowed values.
  foreach ($status as $key => &$value) {
    $value = i18n_string('field:field_ding_list_status:#allowed_values:' . $key, $value);
  }

  $form['status'] = array(
    '#type' => 'select',
    '#title' => t('Status'),
    '#description' => t('Please note: When you share a list, your name will be displayed with the list.'),
    '#options' => $status,
    '#default_value' => ding_base_get_value('ding_type', $list, 'field_ding_list_status', 'value', 'private'),
    '#ajax' => array(
      'callback' => 'ding_list_list_permissions_form_state_callback',
      'wrapper' => 'status-description',
    ),
  );
  // Used for callback information.
  $form['status_description'] = array(
    '#markup' => '<div id="status-description"></div>',
  );

  $form['sharer'] = array(
    '#type' => 'fieldset',
    '#title' => t('Settings'),
    '#states' => array(
      'visible' => array(
        ':input[name="status"]' => array('value' => 'shared'),
      ),
    ),
  );

  $permission_options = array(
    'view' => t('Allow to view this list'),
    'edit' => t('Allow to view and edit this list'),
  );

  $form['sharer']['permission'] = array(
    '#type' => 'select',
    '#title' => t('Select which type of access to share'),
    '#options' => $permission_options,
  );

  // Setup the share link, with the correct token.
  $uri = entity_uri('ding_type', $list);
  foreach ($permission_options as $key => $title) {
    $token = ding_list_share_token($list, $key);
    $form['sharer']['link'][$key] = array(
      '#type' => 'textfield',
      '#title' => t('Share link'),
      '#value' => url($uri['path'], array('absolute' => TRUE, 'query' => array('token' => $token))),
      '#states' => array(
        'visible' => array(
          ':input[name="permission"]' => array('value' => $key),
        ),
      ),
    );
  }

  $form['mail_sharer'] = array(
    '#type' => 'fieldset',
    '#title' => t('Share'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
    '#states' => array(
      'visible' => array(
        ':input[name="status"]' => array('value' => 'shared'),
      ),
    ),
  );

  $form['mail_sharer']['email'] = array(
    '#type' => 'textfield',
    '#title' => t('Send invitation to this email adress:'),
    '#description' => t('At the moment only users at this library can share your lists.'),
  );

  $form['mail_sharer']['share'] = array(
    '#type' => 'submit',
    '#value' => t('Send mail invitation with share link'),
    '#ajax' => array(
      'callback' => 'ding_list_list_permissions_form_share_callback',
    ),
  );

  // Create the interface for handling specific user permissions.
  $permissions = ding_base_get_items('ding_type', $list, 'field_ding_list_permissions');
  if (!empty($permissions)) {
    $keys = array();
    foreach ($permissions as $permission) {
      $keys[] = $permission['target_id'];
    }

    // Load all permission entities.
    $permissions = entity_load('ding_type', $keys);
    $form['mail_sharer']['shared'] = array(
      '#prefix' => '<div id="shared-list">',
      '#suffix' => '</div>',
      '#type' => 'fieldset',
      '#title' => t('Shared'),
      '#description' => t('The following users has access to this shared list.'),
      '#states' => array(
        'visible' => array(
          ':input[name="status"]' => array('value' => 'shared'),
        ),
      ),
      '#tree' => TRUE,
      '#theme' => 'ding_list_shared_permissions_table',
    );

    // Add an item to the shared list, for each user with access.
    foreach ($permissions as $permission) {
      $user_id = ding_base_get_value('ding_type', $permission, 'field_ding_list_user');
      if (ding_provider_implements('openlist', 'get_user')) {
        $user_account = ding_provider_invoke('openlist', 'get_user', $user_id);
      }
      else {
        // User with access permissions, has accepted sharing of email.
        $user_account = user_load($user_id);
      }

      $form['mail_sharer']['shared'][$permission->id]['user'] = array(
        '#markup' => $user_account->mail,
      );

      $permission_options['remove'] = t('Revoke access to this list');
      $form['mail_sharer']['shared'][$permission->id]['permission'] = array(
        '#type' => 'select',
        '#options' => $permission_options,
        '#default_value' => ding_base_get_value('ding_type', $permission, 'field_ding_list_permission'),
        '#ajax' => array(
          'callback' => 'ding_list_list_permissions_form_set_permission_callback',
          'wrapper' => 'shared-list',
        ),
      );
    }
  }

  return $form;
}

/**
 * Theme function that makes the shared table for the permissions form.
 */
function theme_ding_list_shared_permissions_table($variables) {
  $element = $variables['element'];

  $header = array(
    'user' => t('User'),
    'permission' => t('Permission'),
  );

  $rows = array();
  foreach (element_children($element) as $key) {
    $row = array();

    $row['data'] = array();
    foreach ($header as $fieldname => $title) {
      $row['data'][] = drupal_render($element[$key][$fieldname]);
    }
    $rows[] = $row;
  }

  return theme('table', array(
    'header' => $header,
    'rows' => $rows,
  ));
}

/**
 * Ajax callback for changing a user permission.
 */
function ding_list_list_permissions_form_set_permission_callback($form, &$form_state) {
  // Get the permission entity id, from the triggering elements parents.
  // The array parents will look  like: ["mail_sharer", "shared", ID,
  // "permission"].
  $permission_id = array_slice($form_state['triggering_element']['#array_parents'], -2, 1);
  $permission_id = $permission_id[0];
  $entity = entity_load_single('ding_type', $permission_id);

  $permission = $form_state['values']['shared'][$permission_id]['permission'];

  if ($permission != 'remove') {
    $entity->field_ding_list_permission[LANGUAGE_NONE] = array(array('value' => $permission));
    entity_save('ding_type', $entity);
  }
  else {
    unset($form['mail_sharer']['shared'][$entity->id]);

    ding_list_remove_permission($entity);

    if (count(element_children($form['mail_sharer']['shared'])) == 0) {
      return array();
    }
  }

  return $form['mail_sharer']['shared'];
}

/**
 * When changing the permissions status of the list.
 */
function ding_list_list_permissions_form_state_callback($form, &$form_state) {
  $list = $form_state['build_info']['args'][0];
  ding_list_edit_ding_list(
    $list,
    $list->title,
    NULL,
    TRUE,
    array(
      array(
        'name' => 'field_ding_list_status',
        'value_type' => 'value',
        'value' => $form_state['values']['status'],
      ),
    )
  );

  $output = array(
    'shared' => t('Your list is now shared.'),
    'public' => t('Your list is now public. You can find it under !link', array('!link' => l(t('Public lists'), 'public-lists'))),
    'private' => t('Your list is now private.'),
  );

  return theme('ding_list_permission_description', array('message' => $output[$form_state['values']['status']]));
}

/**
 * Callback for sending the share by mail.
 */
function ding_list_list_permissions_form_share_callback($form, &$form_state) {
  global $language;

  $response = array(
    '#type' => 'ajax',
    '#commands' => array(),
  );

  if (empty($form_state['values']['email'])) {
    $response['#commands'][] = ajax_command_ding_popup('ding_list', t('The emails field is required to send out invitations.'), t('No mails send.'));
    return $response;
  }

  $list = $form_state['build_info']['args'][0];

  $uri = entity_uri('ding_type', $list);
  $token = ding_list_share_token($form_state['build_info']['args'][0], $form_state['values']['permission']);

  $link = l($list->title, $uri['path'], array('absolute' => TRUE, 'query' => array('token' => $token)));

  drupal_mail('ding_list', 'share', $form_state['values']['email'], $language, array(
    'link' => $link,
    'list' => $list,
  ));

  // Get generated message.
  $html = theme('ding_list_message', array('message' => t('Mail sent')));
  // Popup.
  $response['#commands'][] = ajax_command_ding_popup('ding_list', t('Share'), $html);

  return $response;
}
