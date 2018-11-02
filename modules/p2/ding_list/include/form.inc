<?php

/**
 * @file
 * Forms used by ding_list.
 */

use DingList\DingList;
use DingList\DingListElement;

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
  $list = ding_list_get_list($element->getListId());

  if (!ding_list_user_has_access($list, 'edit') || !$list->allowed(DING_LIST_OPERATION_DETACH)) {
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
  if (!$element->delete()) {
    drupal_set_message(t("An error occurred while deleting your element. Please contact the administrator if this problem persists."), 'error');
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
    if (!$list->hasElement($value)) {
      $form['list'] = array(
        '#type' => 'hidden',
        '#value' => $list->getId(),
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
  if (!$list->hasElement($value)) {
    $element = $list->attachElement(DingListElement::fromDataArray(array(
      'type' => $type,
      'value' => $value,
    )))->save();

    if ($element !== FALSE) {
      $form_state['storage']['response_html'] = t('Added to !name', array('!name' => l($list->getTitle(), 'list/' . $list->getId())));
    }
    else {
      $form_state['storage']['response_html'] = t("An error occurred, your element wasn't created. Please contact the administrator if this problem persists.");
    }
  }
  else {
    $form_state['storage']['response_html'] = t('Already added to !name', array('!name' => l($list->getTitle(), 'list/' . $list->getId())));
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
 * The form used to create a list object.
 *
 * If an existing list object is given, that object is editted instead
 * of creating a new object.
 *
 * @param \DingList\DingList|false $list
 *   The existing list object, or FALSE if we're creating a new.
 */
function ding_list_edit_list_form($form, &$form_state, $list = FALSE) {
  if (isset($form_state['storage']['confirm'])) {
    $form['#submit'] = array('ding_list_edit_list_form_submit_delete');

    $form = confirm_form(
      $form,
      // Even though the confirm_form tries to drupal_set_title, the panel will
      // take over and set the title. Which is why we leave the $question blank.
      '',
      current_path(),
      t('Do you really want to delete !list?', array('!list' => check_plain($list->getTitle())))
    );

    return $form;
  }

  $form['title'] = array(
    '#type' => 'textfield',
    '#title' => t('Title'),
    '#required' => TRUE,
    '#default_value' => $list !== FALSE ? $list->getTitle() : '',
    '#access' => $list === FALSE || $list->allowed(DING_LIST_OPERATION_EDIT_TITLE),
  );

  $form['note'] = array(
    '#type' => 'textarea',
    '#title' => t('Note'),
    '#default_value' => $list !== FALSE ? $list->getNote() : '',
  );

  if (user_access('ding_list administer lists')) {
    $form['not_public'] = array(
      '#type' => 'checkbox',
      '#title' => t("Hide this list from public lists"),
      '#default_value' => $list !== FALSE ? $list->getData('not_public', 0) : 0,
    );
  }

  $form['actions'] = array(
    '#type' => 'actions',
  );
  $form['actions']['save'] = array(
    '#type' => 'submit',
    '#value' => t('Save list'),
  );

  if ($list !== FALSE && $list->allowed(DING_LIST_OPERATION_DELETE)) {
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
 * Edit form submit action.
 */
function ding_list_edit_list_form_submit($form, &$form_state) {
  if (isset($form_state['build_info']['args'][0])) {
    $list = $form_state['build_info']['args'][0];
  }
  else {
    // Load the user object, to make sure it's complete.
    $account = user_load($GLOBALS['user']->uid);

    $list = DingList::fromDataArray(array(
      'type' => DING_LIST_TYPE_USER_LIST,
      'owner' => ding_provider_invoke('openlist', 'user_identifier', $account),
    ));
  }

  if (isset($form_state['values']['not_public'])) {
    $list->setData('not_public', $form_state['values']['not_public']);
  }

  $list
    ->setTitle($form_state['values']['title'])
    ->setNote($form_state['values']['note'])
    ->save();

  if (isset($form_state['values']['auto_add_type'])) {
    $list->attachElement(DingListElement::fromDataArray(array(
      'type' => $form_state['values']['auto_add_type'],
      'value' => $form_state['values']['auto_add_value'],
    )))->save();
  }

  $form_state['redirect'] = 'list/' . $list->getId();
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
  if ($list->delete()) {
    $form_state['redirect'] = 'user/' . $GLOBALS['user']->uid . '/my-library';
  }
  else {
    drupal_set_message(t("An error occurred while deleting your list. Please contact the administrator if this problem persists."), 'error');
  }
}

/**
 * Edit form cancel action.
 */
function ding_list_edit_list_form_submit_cancel($form, &$form_state) {
  $list = $form_state['build_info']['args'][0];

  // You cancelled, nothing is happening.
  if (!empty($list)) {
    $form_state['redirect'] = 'list/' . $list['list_id'];
  }
  else {
    $form_state['redirect'] = 'user/' . $GLOBALS['user']->uid . '/my-library';
  }
}

/**
 * A list permissions handler form.
 *
 * This is a pure ajax interface form.
 */
function ding_list_list_permissions_form($form, $form_state, $list = FALSE) {
  global $user;

  if (!$list->isOwner($user)) {
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
      'shared' => t('Shared - Users with the secret link can view or edit your list'),
      'public' => t('Public - Anybody can view your list from the public link'),
    ),
    '#default_value' => $list->getData('visibility', 'private'),
    '#ajax' => array(
      'callback' => 'ding_list_list_permissions_form_state_callback',
      'wrapper' => 'status-description',
    ),
  );
  // Used for callback information.
  $form['status_description'] = array(
    '#markup' => '<div id="status-description"></div>',
  );

  // Information when shared.
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
  foreach ($permission_options as $key => $title) {
    $token = ding_list_share_token($list, $key);
    $form['sharer']['link'][$key] = array(
      '#type' => 'textfield',
      '#title' => t('Share link'),
      '#value' => url('list/' . $list->getId(), array('absolute' => TRUE, 'query' => array('token' => $token))),
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

  $username = $user->name;
  if (isset($user->data)) {
    if (is_string($user->data)) {
      $data = unserialize($user->data);
    }
    else {
      $data = $user->data;
    }
    if (!empty($data) && isset($data['display_name'])) {
      $username = $data['display_name'];
    }
  }
  $form['mail_sharer']['email_subject'] = array(
    '#type' => 'textfield',
    '#title' => t('Email subject.'),
    '#default_value' => t('@user has shared a personal list with you at @library', array(
      '@user' => $username,
      '@library' => variable_get('site_name', ''),
    )),
  );
  $form['mail_sharer']['email_text'] = array(
    '#type' => 'textarea',
    '#title' => t('Email text'),
    '#description' => t('The !link text will be replaced by a link to the list'),
    '#default_value' => t('Please use the following link to access this list.
The link is active for 7 days from today, after which it will be disabled for security reasons.
!link'),
    '#resizable' => FALSE,
  );
  $form['mail_sharer']['share'] = array(
    '#type' => 'submit',
    '#value' => t('Send mail invitation with share link'),
    '#ajax' => array(
      'callback' => 'ding_list_list_permissions_form_share_callback',
    ),
  );

  $permissions = ding_provider_invoke(
    'openlist',
    'call_module',
    'ListPermission',
    'listPermissions',
    array($list->getId()),
    array('cache_prefix' => 'lp' . $list->getId())
  );
  if (!empty($permissions)) {
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
      $local_user = ding_provider_invoke('openlist', 'drupal_user', $permission['user']);
      $form['mail_sharer']['shared'][$permission['user']]['user'] = array(
        '#markup' => format_username($local_user),
      );

      $permission_options['remove'] = t('Revoke access to this list');
      $form['mail_sharer']['shared'][$permission['user']]['permission'] = array(
        '#type' => 'select',
        '#options' => $permission_options,
        '#default_value' => $permission['permission'],
        '#ajax' => array(
          'callback' => 'ding_list_list_permissions_form_set_permission_callback',
          'wrapper' => 'shared-list',
        ),
        '#user_id' => $permission['user'],
      );
    }
  }

  // Information when public.
  $form['public'] = array(
    '#type' => 'fieldset',
    '#title' => t('Public'),
    '#description' => t('You can find your public list under !link', array('!link' => l(t('Public lists'), 'public-lists'))),
    '#states' => array(
      'visible' => array(
        ':input[name="status"]' => array('value' => 'public'),
      ),
    ),
    '#tree' => TRUE,
  );
  $url = url('list/' . $list->getId(), array('absolute' => TRUE));
  $form['public']['link'] = array(
    '#type' => 'item',
    '#title' => t('Share link'),
    '#markup' => l($url, $url),
  );

  return $form;
}

/**
 * Permissions form unfollow action.
 *
 * Note this is the action shown, for users that follow a list, not the owner
 * of the list.
 */
function ding_list_list_permissions_form_unfollow_shared($form, &$form_state) {
  // Get the current user follow lists list.
  $list = ding_list_get_list(DING_LIST_TYPE_LISTS);

  if ($list) {
    $element = $list->hasElement($form_state['build_info']['args'][0]->getId());
    if ($element) {
      if (!$element->delete()) {
        drupal_set_message(t("An error occurred while unfollowing the list. Please contact the administrator if this problem persists."), 'error');
        return;
      }
    }
  }

  $form_state['redirect'] = 'user';
}

/**
 * Ajax callback for changing a user permission.
 */
function ding_list_list_permissions_form_set_permission_callback($form, &$form_state) {
  $list = $form_state['build_info']['args'][0];

  $user_id = $form_state['triggering_element']['#user_id'];
  $local_user = ding_provider_invoke('openlist', 'drupal_user', $user_id);
  $permission = $form_state['values']['shared'][$user_id]['permission'];

  if ($permission != 'remove') {
    $list->setPermission($permission, $local_user);
  }
  else {
    unset($form['mail_sharer']['shared'][$user_id]);
    $list->removePermission($local_user);
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

  $list
    ->setData('visibility', $form_state['values']['status'])
    ->save();

  $output = array(
    'public' => t('Your list is now public.'),
    'private' => t('Your list is now private.'),
  );

  return theme('ding_list_permission_description', array('message' => $output[$list->getData('visibility')]));
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
  $token = ding_list_share_token($list, $form_state['values']['permission']);
  $link = l($list->getTitle(), 'list/' . $list->getId(), array('absolute' => TRUE, 'query' => array('token' => $token)));
  drupal_mail('ding_list', 'share', $form_state['values']['email'], $language, array(
    'subject' => $form_state['values']['email_subject'],
    'text' => str_replace('!link', $link, $form_state['values']['email_text']),
  ));
  // Get generated message.
  $html = theme('ding_list_message', array('message' => t('Mail sent')));
  // Popup.
  $response['#commands'][] = ajax_command_ding_popup('ding_list', t('Share'), $html);
  return $response;
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
