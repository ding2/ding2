<?php
/**
 * @file
 * Administration user interface for the module.
 */

/**
 * Implements hook_form().
 */
function ding_registration_admin_settings_form($form, &$form_state) {
  $form = array(
    '#tree' => TRUE,
  );

  $defaults = _ding_registration_config();

  $form['ding_registration'] = array(
    '#type' => 'fieldset',
    '#title' => t('User self registration'),
    '#collapsible' => FALSE,
    '#collapsed' => FALSE,
  );

  $form['ding_registration']['age_limit'] = array(
    '#type' => 'textfield',
    '#title' => t('Age limit'),
    '#description' => t('The age limit will be used to ensure that no user is created without being above the limit. If left empty no age limit is enforced.'),
    '#default_value' => $defaults['age_limit'],
    '#element_validate' => array('element_validate_integer_positive'),
  );

  // Define before create info page.
  $form['ding_registration']['information'] = array(
    '#type' => 'fieldset',
    '#title' => t('Information page'),
    '#description' => t('Information displayed before the user starts the self registration page. This could be information about the rules for self registration and links to the library regulations.'),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
    '#tree' => TRUE,
  );

  $form['ding_registration']['information']['title'] = array(
    '#type' => 'textfield',
    '#title' => t('Page title'),
    '#default_value' => $defaults['information']['title'],
  );

  $form['ding_registration']['information']['content'] = array(
    '#type' => 'text_format',
    '#title' => t('Content'),
    '#default_value' => $defaults['information']['content']['value'],
    '#format' => $defaults['information']['content']['format'],
    '#rows' => 15,
  );

  $form['ding_registration']['information']['link'] = array(
    '#type' => 'textfield',
    '#title' => t('Link title'),
    '#default_value' => $defaults['information']['link'],
  );

  $form['ding_registration']['information']['reset'] = array(
    '#type' => 'submit',
    '#value' => t('Reset to DDB default text'),
    '#submit' => array('ding_registration_information_reset'),
  );

  // Accepting text.
  $form['ding_registration']['acceptance'] = array(
    '#type' => 'fieldset',
    '#title' => t('Acceptance page'),
    '#description' => t('Before the user can be created we need to get basic contact information and the user needs to accept regulations.'),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
    '#tree' => TRUE,
  );

  $form['ding_registration']['acceptance']['description'] = array(
    '#type' => 'text_format',
    '#title' => t('Acceptance text'),
    '#description' => t('Description displayed next to the user acceptance check box.'),
    '#default_value' => $defaults['acceptance']['description']['value'],
    '#format' => $defaults['acceptance']['description']['format'],
    '#rows' => 15,
  );

  // Define after create info page.
  $form['ding_registration']['success'] = array(
    '#type' => 'fieldset',
    '#title' => t('Successful registration page'),
    '#description' => t('Information displayed after the user have been successful registered at the provider.'),
    '#tree' => TRUE,
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
  );

  $form['ding_registration']['success']['title'] = array(
    '#type' => 'textfield',
    '#title' => t('Title'),
    '#default_value' => $defaults['success']['title'],
  );

  $form['ding_registration']['success']['content'] = array(
    '#type' => 'text_format',
    '#title' => t('Content'),
    '#default_value' => $defaults['success']['content']['value'],
    '#format' => $defaults['success']['content']['format'],
    '#rows' => 15,
  );

  return system_settings_form($form);
}

/**
 * Submit handler that resets the information text.
 */
function ding_registration_information_reset($form, $form_state) {
  $config = variable_get('ding_registration', FALSE);
  if ($config) {
    unset($config['information']);
  }
  variable_set('ding_registration', $config);

  drupal_set_message(t('Information text have been reset to DDB default text'));
}
