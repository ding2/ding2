<?php
/**
 * @file
 * Ding user settings.
 */

/**
 * Ding user admin.
 */
function ding_user_admin_setting_form($form, &$form_state) {
  $form['ding_user_signup_link'] = array(
    '#type' => 'textfield',
    '#title' => t('Link'),
    '#default_value' => variable_get('ding_user_signup_link', ''),
    '#description' => t('The link is used in the text next to the log-in form'),
  );

  return system_settings_form($form);
}

/**
 * Validate user admin form.
 */
function ding_user_admin_setting_form_validate($form, &$form_state) {
  if (!valid_url($form_state['values']['ding_user_signup_link'])) {
    form_set_error('ding_user_signup_link', t('Not a valid URL.'));
  }
}

/**
 * Admin form structure.
 *
 * @return array
 *   The form itself.
 */
function ding_user_profile_admin_form($form) {
  $ding_provider = ding_provider_get_provider_module_name('user');
  $instances = field_info_instances('profile2', 'provider_' . $ding_provider);

  $form['user_profile_note'] = array(
    '#type' => 'item',
    '#markup' => t('The following fields will contain the description supplied below, however they might be hidden.'),
  );

  // These fields are standard in drupal.
  // The use edit form has fields which cannot be edited.
  $standard_fields = array(
    'pass' => array(
      'label' => 'pincode',
    ),
  );

  // Provider fields.
  foreach ($standard_fields + $instances as $key => $instance) {
    if (isset($instances[$key]) && $instances[$key]['widget']['type'] == 'hidden') {
      continue;
    }

    $field = 'user_profile_' . $key;
    $form[$field] = array(
      '#type' => 'textarea',
      '#rows' => 2,
      '#title' => ucfirst($instance['label']),
      '#default_value' => t('!field', array('!field' => variable_get($field, ''))),
    );
  }

  return system_settings_form($form);
}
