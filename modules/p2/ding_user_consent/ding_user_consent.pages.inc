<?php

/**
 * @file
 * Ding user pages.
 */

/**
 * Ask consent form.
 */
function ding_user_consent_form($form, &$form_state) {
  // If consent longer than 30 days is disabled, ignore the form below:
  if (!variable_get('user_consent_activate')) {
    return;
  }

  if (!empty($form['#user'])) {
    $account = $form['#user'];
  }
  else {
    global $user;
    $account = $user;
  }

  $consents = ding_provider_invoke('user_consent', 'info');
  $consent = ding_provider_invoke('user_consent', 'get_consent', $account);
  foreach ($consents as $id => $values) {
    if (!$account->login) {
      $title = variable_get($id . '_title_first_time', $values['title']);
      $description = variable_get($id . '_description_first_time', $values['description']);
    }
    else {
      $title = variable_get($id . '_title', $values['title']);
      $description = variable_get($id . '_description', $values['description']);
    }

    $form['content'][$id] = array(
      '#type' => 'checkbox',
      '#title' => check_plain($title),
      '#description' => filter_xss($description['value']),
      '#default_value' => !empty($consent[$id]) ? $consent[$id] : 0,
    );
  }

  $form['actions'] = array('#type' => 'actions');
  $form['actions']['submit'] = array('#type' => 'submit', '#value' => t('Save'));

  return $form;
}

/**
 * Form submit function.
 */
function ding_user_consent_form_submit($form, &$form_state) {
  if (!empty($form['#user'])) {
    $account = $form['#user'];
  }
  else {
    global $user;
    $account = $user;
  }

  ding_user_consent_set($form_state['values'], $account);

  $form_state['redirect'] = 'user/' . $account->uid;
}
