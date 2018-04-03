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

  // To avoid form caches, all remove forms have an identifier appended, this
  // this could be a ting_object id.
  if (strpos($form_id, 'ding_list_remove_element_form__') === 0) {
    $forms[$form_id] = array('callback' => 'ding_list_remove_element_form');
  }

  return $forms;
}

/**
 * Form to remove and element from a list.
 */
function ding_list_remove_element_form($form, &$form_state, $element, $title = NULL) {
  $list = ding_list_get_list($element['list_id']);

  // @TODO Add access checks here.
  if (!ding_list_user_has_access($list, 'edit') || !ding_list_allowed($list, DING_LIST_OPERATION_DETACH)) {
    return $form;
  }

  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => $title ? $title : t('Remove from list'),
    '#attributes' => array('class' => array('close-btn')),
  );

  return $form;
}

/**
 * Remove element form submit.
 */
function ding_list_remove_element_form_submit($form, &$form_state) {
  $element = $form_state['build_info']['args'][0];
  ding_list_detach_element($element);
}

/**
 * Add an element to a list.
 *
 * @param string $type
 *   The type of element to add.
 * @param string $value
 *   The value of the element, typically an identifier.
 * @param string $title
 *   Title of the add button.
 */
function ding_list_add_element_form($form, &$form_state, $type, $value, $title) {
  if (is_array($type)) {
    $type = key($type);
  }

  $options = ding_list_get_add_to_list_data($type, $value);
  if (count($options) > 1) {
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
    $list = ding_list_get_list($list['list_id']);
    if (!ding_list_has_element($list, $value)) {
      $form['list'] = array(
        '#type' => 'hidden',
        '#value' => $list['list_id'],
      );
    }
  }

  if (isset($form['list'])) {
    $form['submit'] = array(
      '#type' => 'submit',
      '#value' => $title,
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
  if (!ding_list_has_element($list, $value)) {
    $element = ding_list_attach_element($list, $type, array('value' => $value));

    if ($element !== FALSE) {
      $form_state['storage']['response_html'] = t('Added to !name', array('!name' => l($list['title'], 'list/' . $list['list_id'])));
    }
    else {
      $form_state['storage']['response_html'] = t("An error occurred, your element wasn't created. Please contact the administrator if this problem persists.");
    }
  }
  else {
    $form_state['storage']['response_html'] = t('Already added to !name', array('!name' => l($list['title'], 'list/' . $list['list_id'])));
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
 *
 * @TODO rename this to edit instead of create, and change references.
 */
function ding_list_edit_list_form($form, &$form_state, $existing = FALSE) {
  if (isset($form_state['storage']['confirm'])) {
    $form['#submit'] = array('ding_list_edit_list_form_submit_delete');

    $form = confirm_form(
      $form,
      t('Do you really want to delete !list?', array('!list' => check_plain($existing['title']))),
      current_path(),
      t('Do you really want to delete !list?', array('!list' => check_plain($existing['title'])))
    );

    return $form;
  }

  $form['title'] = array(
    '#type' => 'textfield',
    '#title' => t('Title'),
    '#required' => TRUE,
    '#default_value' => isset($existing['title']) ? $existing['title'] : '',
    '#access' => $existing === FALSE || ding_list_allowed($existing, DING_LIST_OPERATION_EDIT_TITLE),
  );

  $form['note'] = array(
    '#type' => 'textarea',
    '#title' => t('Note'),
    '#default_value' => isset($existing['data']['note']) ? $existing['data']['note'] : '',
  );

  $form['actions'] = array(
    '#type' => 'actions',
  );
  $form['actions']['save'] = array(
    '#type' => 'submit',
    '#value' => t('Save list'),
  );

  if ($existing !== FALSE && ding_list_allowed($existing, DING_LIST_OPERATION_DELETE)) {
    $form['actions']['delete_list'] = array(
      '#type' => 'submit',
      '#value' => t('Delete list'),
      '#submit' => array('ding_list_edit_list_form_submit_delete'),
    );
  }

  $form['actions']['cancel'] = array(
    '#type' => 'submit',
    '#value' => t('Cancel'),
    '#submit' => array('ding_list_edit_list_form_submit_cancel'),
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
 * The create_list_form submit handler.
 */
function ding_list_edit_list_form_submit($form, &$form_state) {
  if (isset($form_state['build_info']['args'][0])) {
    $list = $form_state['build_info']['args'][0];
  }
  else {
    // Load the user object, to make sure it's complete.
    $account = user_load($GLOBALS['user']->uid);

    $list = array(
      'type' => DING_LIST_TYPE_USER_LIST,
      'owner' => ding_provider_invoke('openlist', 'user_identifier', $account),
    );
  }

  $list['title'] = $form_state['values']['title'];
  $list['data']['note'] = $form_state['values']['note'];

  ding_list_save_list($list);

  if (isset($form_state['values']['auto_add_type'])) {
    ding_list_attach_element($list, $form_state['values']['auto_add_type'], array('value' => $form_state['values']['auto_add_value']));
  }

  $form_state['redirect'] = 'list/' . $list['list_id'];
}

/**
 * Edit form delete action.
 */
function ding_list_edit_list_form_submit_delete($form, &$form_state) {
  if (!isset($form_state['storage']['confirm'])) {
    $form_state['storage']['confirm'] = TRUE;
    $form_state['rebuild'] = TRUE;
    return;
  }

  $list = $form_state['build_info']['args'][0];
  ding_list_delete_list($list);
  $form_state['redirect'] = 'user/' . $GLOBALS['user']->uid . '/dinglists';
}

/**
 * Cancel button on create submit.
 */
function ding_list_edit_list_form_submit_cancel($form, &$form_state) {
  $existing = $form_state['build_info']['args'][0];

  // You cancelled, nothing is happening.
  if (!empty($existing)) {
    $form_state['redirect'] = 'list/' . $existing['list_id'];
  }
  else {
    $form_state['redirect'] = 'user';
  }
}

/**
 * Remove share from list.
 */
function ding_list_list_permissions_form_unfollow_shared($form, &$form_state) {
  $list = ding_list_get_list(DING_LIST_TYPE_LISTS);

  if ($list) {
    $element = ding_list_has_element($list, $form_state['build_info']['args'][0]['list_id']);
    if ($element) {
      ding_list_detach_element($element);
    }
  }

  $form_state['redirect'] = 'user';
}

/**
 * A list permissions handler form.
 *
 * This is a pure ajax interface form.
 */
function ding_list_list_permissions_form($form, $form_state, $list = FALSE) {
  if (!ding_list_is_owner($list)) {
    $form['unfollow_shared'] = array(
      '#type' => 'submit',
      '#value' => t('Unfollow shared list'),
      '#submit' => array('ding_list_list_permissions_form_unfollow_shared'),
    );

    return $form;
  }

  $form['status'] = array(
    '#type' => 'select',
    '#title' => t('Status'),
    '#description' => t('Please note: When you share a list, your name will be displayed with the list.'),
    '#options' => array(
      'private' => t('Private - The list is only accessible to you'),
      'public' => t('Public - Anybody can view your list from the public link'),
    ),
    '#default_value' => !empty($list['data']['visibility']) ? $list['data']['visibility'] : 'private',
    '#ajax' => array(
      'callback' => 'ding_list_list_permissions_form_state_callback',
      'wrapper' => 'status-description',
    ),
  );

  return $form;
}

/**
 * When changing the permissions status of the list.
 */
function ding_list_list_permissions_form_state_callback($form, &$form_state) {
  $list = $form_state['build_info']['args'][0];

  $list['data']['visibility'] = $form_state['values']['status'];

  ding_list_save_list($list);

  $output = array(
    'public' => t('Your list is now public.'),
    'private' => t('Your list is now private.'),
  );

  return theme('ding_list_permission_description', array('message' => $output[$list['data']['visibility']]));
}
