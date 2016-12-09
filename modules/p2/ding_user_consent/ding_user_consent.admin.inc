<?php

/**
 * @file
 * Ding user pages.
 */

/**
 * Admin form for consent messages.
 */
function ding_user_consent_admin_form($form, &$form_state) {
  $form['user_consent_activate'] = array(
    '#type' => 'checkbox',
    '#title' => t('Enable Ding User Consent'),
    '#description' => t('Give users access to consent to store their loan history for more than 30 days.'),
    '#default_value' => variable_get('user_consent_activate', FALSE),
  );

  $consents = ding_provider_invoke('user_consent', 'info');
  foreach ($consents as $id => $values) {
    $form_key = 'ding_user_consent_' . $id;
    $form[$form_key] = array(
      '#type' => 'fieldset',
      '#title' => t('Consent for %title', array('%title' => $values['title'])),
      '#collapsible' => TRUE,
      '#collapsed' => FALSE,
    );

    $form[$form_key][$form_key . '_description_markup'] = array(
      '#markup' => t('Notice the settings below will only take effect if user consent is enabled in the checkbox above.'),
    );    
    
    // Consent description link.
    $form[$form_key][$form_key . '_description_link'] = array(
      '#type' => 'textfield',
      '#title' => t('Link to consent description'),
      '#description' => t('Write a link to the page containing a description of user consent. Use whether the format node/!nid or a path alias.') . "<br/>" . ding_user_consent_get_description_link(),
      '#default_value' => variable_get($form_key . '_description_link', ''),
    );
    
    // First time message.
    $form[$form_key]['first_time'] = array(
      '#type' => 'fieldset',
      '#title' => t('First time'),
      '#collapsible' => TRUE,
      '#collapsed' => FALSE,
    );
    
    $form[$form_key]['first_time'][$form_key . '_title_first_time'] = array(
      '#type' => 'textfield',
      '#title' => t('First login message title'),
      '#description' => t('Write a title for the message a first time user will receive'),
      '#default_value' => variable_get($form_key . '_title_first_time', ''),
    );
    
    $description = variable_get($form_key . '_description_first_time', '');
    $description = (is_array($description)) ? $description['value'] : $description;
    $form[$form_key]['first_time'][$form_key . '_description_first_time'] = array(
      '#type' => 'text_format',
      '#title' => t('First login message description'),
      '#description' => t('Write a message for a first time user'),
      '#default_value' => $description,
      '#format' => 'ding_wysiwyg',
    );

    // User consent request message.
    $form[$form_key]['request'] = array(
      '#type' => 'fieldset',
      '#title' => t('Request'),
      '#collapsible' => TRUE,
      '#collapsed' => FALSE,
    );
    
    $form[$form_key]['request'][$form_key . '_title'] = array(
      '#type' => 'textfield',
      '#title' => t('Consent title'),
      '#description' => t('Write a title for the message which the user will see when requested to give consent'),
      '#default_value' => variable_get($form_key . '_title', $values['title']),
    );
    
    $description = variable_get($form_key . '_description', $values['description']);
    $description = (is_array($description)) ? $description['value'] : $description;
    $form[$form_key]['request'][$form_key . '_description'] = array(
      '#type' => 'text_format',
      '#title' => t('Consent description'),
      '#description' => t('Write a message for the user when requested to give consent'),
      '#default_value' => $description,
      '#format' => 'ding_wysiwyg',
    );
  }

  return system_settings_form($form);
}
