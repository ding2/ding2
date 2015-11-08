<?php

/**
 * @file
 *
 * Admin page callbacks for the Ting field search module.
 */

/**
 * Profile form builder.
 */
function ting_field_search_profile_form($form, &$form_state, $profile = FALSE) {
  if ($profile || isset($form_state['original_profile'])) {
    // Save the profile object in form_state for later use.
    if (!isset($form_state['original_profile'])) {
      $form_state['original_profile'] = array_shift($profile);
    }
    // During a rebuild; use the stored $profile object.
    $profile = $form_state['original_profile'];
  }

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
    '#default_value' => $profile ? $profile->title : '',
  );
  $form['profile']['name'] = array(
    '#type' => 'machine_name',
    '#title' => t('Name (identificator used in URI)'),
    '#description' => t('Enter a unique machine-name for this profile.'),
    '#maxlength' => 64,
    '#default_value' => $profile ? $profile->name : '',
    '#machine_name' => array(
      'exists' => 'ting_field_search_profile_exists',
      'source' => array('profile', 'title'),
      'label' => t('Name'),
    ),
    // It should'nt be necesarry to change machine-name of existing profiles.
    '#disabled' => $profile,
  );
  $form['profile']['profile'] = array(
    '#type' => 'textfield',
    '#title' => t('VIP profile name (http://vip.dbc.dk)'),
    '#description' => t('Use a special VIP profile. Leave blank to use the standard search profile.'),
    '#default_value' => $profile ? $profile->profile : '',
  );
  $form['profile']['query'] = array(
    '#type' => 'textfield',
    '#title' => t('Query'),
    '#description' => t('Enter a search code (CQL) to use with this profile.'),
    '#default_value' => $profile ? $profile->query : '',
  );
  $form['profile']['alter_links'] = array(
    '#type' => 'checkbox',
    '#title' => t('Alter links'),
    '#description' => t('Use this profile on ting search links generated on search result, collection and object pages, when using this profile.'),
    '#default_value' => $profile ? $profile->alter_links : 1,
  );
  $form['profile']['active'] = array(
    '#type' => 'checkbox',
    '#title' => t('Active'),
    '#description' => t('Activated profiles can be used in the URI with the profile query parameter.'),
    '#default_value' => $profile ? $profile->active : 0,
  );
  $form['profile']['exposed'] = array(
    '#type' => 'checkbox',
    '#title' => t('Exposed'),
    '#description' => t('Exposed profiles is shown to the user and can be selected before searching.'),
    '#default_value' => $profile ? $profile->exposed : 0,
    '#states' => array(
      'disabled' => array(
        ':input[name="profile[active]"]' => array('checked' => FALSE),
      ),
    ),
  );
  $form['profile']['weight'] = array(
    '#type' => 'select',
    '#title' => t('Weight'),
    '#description' => t('Profiles with lower weight will be positioned closer to the top in the select box.'),
    '#options' => drupal_map_assoc(range(-15, 15)),
    '#default_value' => $profile ? $profile->weight : 0,
    '#states' => array(
      'disabled' => array(
        ':input[name="profile[exposed]"]' => array('checked' => FALSE),
      ),
    ),
  );

  // Form actions
  $form['actions'] = array('#type' => 'actions');

  // Save
  $form['actions']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save'),
  );

  // Delete
  if ($profile) {
    $form['actions']['delete'] = array(
      '#type' => 'submit',
      '#value' => t('Delete'),
      '#submit' => array('ting_field_search_profile_form_delete'),
    );
  }

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

  // If updating an existing profile add in missing values from original.
  if (isset($form_state['original_profile'])) {
    $profile += (array) $form_state['original_profile'];
  }

  // Save and go back.
  if (ting_field_search_profile_save($profile)) {
    drupal_set_message(t('Profile saved'));
  }
  else {
    drupal_set_message(t('Something went wrong saving profile. See log for details.'));
  }
  $form_state['redirect'] = 'admin/config/ting/settings';
}

/**
 * Submit callback for the delete button on the context form.
 *
 * @see ting_field_search_profile_form()
 */
function ting_field_search_profile_form_delete($form, &$form_state) {
  // Pass along any destination parameter set from previous pages
  $destination = array();
  if (isset($_GET['destination'])) {
    $destination = drupal_get_destination();
    unset($_GET['destination']);
  }

  $profile = $form_state['original_profile'];
  $path = 'admin/config/ting/settings/ting-field-search-profiles/' . $profile->name .'/delete';
  $form_state['redirect'] = array($path, array('query' => $destination));
}

/**
 * Form builder for the profile delete confirm form.
 */
function ting_field_search_profile_form_delete_confirm_form($form, &$form_state, $profile) {
  // Store the profile for later use in the submit handler.
  $profile = array_shift($profile);
  $form['ting_field_search_profile'] = array(
    '#type' => 'value',
    '#value' => $profile,
  );

  return confirm_form($form,
    t('Are you sure you want to delete the @profile profile?', array(
      '@profile' => check_plain($profile->title),
    )),
    'admin/config/ting/settings/ting-field-search-profiles/' . $profile->name .'/edit',
    NULL, // This action cannot be undone.
    t('Delete'),
    t('Cancel')
  );
}

/**
 * Submit handler for the profile delete confirm form.
 */
function ting_field_search_profile_form_delete_confirm_form_submit($form, &$form_state) {
  $profile = $form_state['values']['ting_field_search_profile'];

  if (ting_field_search_profile_delete($profile->name)) {
    drupal_set_message(t('Profile @profile deleted', array(
      '@profile' => check_plain($profile->title),
    )));
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
