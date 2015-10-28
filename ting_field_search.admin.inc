<?php

/**
 * @file
 *
 * Admin page callback for the Ting field search module.
 */

/**
 * Main profile form builder.
 */
function ting_field_search_profile_form($form, &$form_state) {
  $form['profile'] = array(
    '#type' => 'fieldset',
    '#title' => t('Create profile'),
    '#tree' => TRUE,
  );

  $form['profile']['title'] = array(
    '#type' => 'textfield',
    '#title' => t('Profile title'),
    '#description' => t('Enter the title of the profile'),
    '#required' => TRUE,
    '#maxlength' => 255,
    '#default_value' => '',
  );
  $form['profile']['name'] = array(
    '#type' => 'machine_name',
    '#title' => t('Profile name'),
    '#description' => t('Enter a unique machine-name for this profile.'),
    '#maxlength' => 64,
    '#default_value' => '',
    '#machine_name' => array(
      'exists' => 'ting_field_search_profile_exists',
      'source' => array('profile', 'title'),
      'label' => t('Profile name'),
    ),
  );
  $form['profile']['profile'] = array(
    '#type' => 'textfield',
    '#title' => t('VIP profile name (http://vip.dbc.dk)'),
    '#description' => t('Use a special VIP profile. Leave blank to use the standard search profile.'),
    '#default_value' => '',
  );
  $form['profile']['query'] = array(
    '#type' => 'textfield',
    '#title' => t('Query'),
    '#description' => t('Enter a search code (CQL) to use with this profile.'),
    '#default_value' => '',
  );

  // Form actions
  $form['actions'] = array('#type' => 'actions');
  $form['actions']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save'),
  );

  // Cancel
  $form['actions']['cancel'] = array(
    '#type' => 'submit',
    '#value' => t('Back'),
    '#submit' => array('ting_field_search_profile_form_cancel'),
    // Bypass form-validation since this is a cancel-button
    '#limit_validation_errors' => array(),
    '#weight' => 40,
  );

  return $form;
}

/**
 * Submit callback for the profile form.
 *
 * @see ting_field_search_profile_form()
 */
function ting_field_search_profile_form_submit($form, &$form_state) {
  $profile = $form_state['values']['profile'];

  if (ting_field_search_profile_save($profile)) {
    drupal_set_message(t('Profile saved'));
  }
  else {
    drupal_set_message(t('Something went wrong saving profile. See log for details.'));
  }
  $form_state['redirect'] = 'admin/config/ting/settings';
}

/**
 * Submit calback for the cancel callback on the context form.
 *
 * @see ting_field_search_profile_form()
 */
function ting_field_search_profile_form_cancel($form, &$form_state) {
  // Go back to ting settings
  $form_state['redirect'] = 'admin/config/ting/settings';
}

/**
 * Exists callback for the profile machine-name element.
 */
function ting_field_search_profile_exists($value) {
  // Retrieve existing profile names.
  $profiles = array_keys(ting_field_search_profiles_load());

  return in_array($value, $profiles);
}
