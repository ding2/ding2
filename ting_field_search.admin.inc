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

  return $form;
}

function ting_field_search_profile_exists($value) {
  return FALSE;
}
