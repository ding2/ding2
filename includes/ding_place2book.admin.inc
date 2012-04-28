<?php

/**
 * @file ding_place2book.admin.inc
 * Admin forms, page callbacks and related functions.
 */

/**
 * The main settings form.
 */
function ding_place2book_admin_settings_form($form_state) {
  global $user;

  $form = array(
    '#tree' => TRUE,
  );

  // Load default settings
  $defaults = variable_get('ding_place2book', array());

  // Default settings
  $form['ding_place2book'] = array(
    '#type' => 'fieldset',
    '#title' => t('Place2Book service'),
    '#collapsible' => TRUE,
    '#collapsed' => isset($defaults['service_url']) ? TRUE : FALSE,
  );

  $form['ding_place2book']['service_url'] = array(
    '#type' => 'textfield',
    '#title' => t('Place2Book service URL'),
    '#default_value' => isset($defaults['service_url']) ? $defaults['service_url'] : 'https://www.place2book.com/da/event_api',
    '#description' => t('Enter a valid Place2book service endpoint, such as https://www.place2book.com/da/event_api'),
    '#required' => TRUE,
    '#size' => 100,
  );

  $form['ding_place2book']['event_url'] = array(
    '#type' => 'textfield',
    '#title' => t('Place2Book events URL'),
    '#default_value' => isset($defaults['event_url']) ? $defaults['event_url'] : 'https://www.place2book.com/da/events',
    '#description' => t('Link to events on Place2Book, such as https://www.place2book.com/da/events. It will be used to generate links to the event at Place2Book'),
    '#required' => TRUE,
    '#size' => 100,
  );

  $form['ding_place2book']['api_key'] = array(
    '#type' => 'textfield',
    '#title' => t('Place2Book default API key'),
    '#default_value' => isset($defaults['api_key']) ? $defaults['api_key'] : '',
    '#required' => TRUE,
    '#description' => t('This is the default API key used when connecting to Place2book. If you provide API key for a specific library (below), events related to that library will use that key instead of the default key.'),
  );

  $form['ding_place2book']['provider_name'] = array(
    '#type' => 'textfield',
    '#title' => t('Place2Book provider name'),
    '#default_value' => isset($defaults['provider_name']) ? $defaults['provider_name'] : $user->name,
    '#required' => TRUE,
    '#description' => t('Name sent to Place2Book as the provider'),
  );

  $form['ding_place2book']['provider_mail'] = array(
    '#type' => 'textfield',
    '#title' => t('Place2Book provider e-mail'),
    '#default_value' => isset($defaults['provider_mail']) ? $defaults['provider_mail'] : $user->mail,
    '#required' => TRUE,
    '#description' => t('E-mail sent to Place2Book as the provider'),
  );

  $form['ding_place2book_libraries'] = array(
    '#type' => 'fieldset',
    '#title' => t('Library API keys'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );

  // Load default settings
  $defaults = variable_get('ding_place2book_libraries', array());

  // Find all libraries and order them by title.
  $result = db_query("SELECT n.nid, n.title FROM {node} n
                      WHERE type = 'ding_library'
                      ORDER BY title");
  
  foreach ($result as $record) {
    $form['ding_place2book_libraries'][$record->nid] = array(
      '#type' => 'textfield',
      '#title' => 'API key ' . check_plain($record->title),
      '#default_value' => isset($defaults[$record->nid]) ? $defaults[$record->nid] : '',
      '#description' => t('Optional. If you have several accounts at Place2book, each library can have their own API key. In that case, the base API key will be overridden by the provided key when sending data on events related to this library.'),
    );
  }

  $form['ding_place2book_event_nodes'] = array(
    '#type' => 'fieldset',
    '#title' => t('Place2Book event node defaults'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );

  // Load default settings
  $defaults = variable_get('ding_place2book_event_nodes', array());

  $form['ding_place2book_event_nodes']['capacity'] = array(
    '#type' => 'textfield',
    '#title' => t('Capacity'),
    '#default_value' => isset($defaults['capacity']) ? $defaults['capacity'] : 0,
    '#size' => 5,
    '#maxlength' => 5,
    '#description' => t('The default capacity for new events. Set to 0 for unlimited capacity.'),
  );

  $form['ding_place2book_event_nodes']['defaults'] = array(
    '#type' => 'checkboxes',
    '#options' => array(
      'maintain_copy' => t('Maintain copy'),
      'kultunaut_export' => t('Kultunaut export'),
      'passive' => t('Passive event'),
    ),
    '#default_value' => isset($defaults['defaults']) ? $defaults['defaults'] : array(),
  );

  return system_settings_form($form);
}
