<?php

/**
* @file ding_place2book.admin.inc
* Admin forms, page callbacks and related functions.
*/

/**
* The main settings form.
*/
function ding_place2book_admin_settings_form(&$form_state) {
  $form = array();

  $form['ding_place2book_service_url'] = array(
    '#type' => 'textfield',
    '#title' => t('Place2Book service URL'),
    '#default_value' => variable_get('ding_place2book_service_url', ''),
    '#required' => TRUE,
    '#size' => 100,
    );

  // Grab all the library nodes with their weight.
  $libquery = db_query("
    SELECT nid, title FROM {node}
    WHERE type = 'library'
    ORDER BY title;
  ");

  $form['ding_place2book_api_key'] = array(
    '#type' => 'textfield',
    '#title' => t('Place2Book base API key'),
    '#default_value' => variable_get('ding_place2book_api_key', ''),
    '#required' => TRUE,
    '#description' => t('Required.This is the base API key used when connecting to Place2book. If you provide API key for a specific library (below), events related to that library will use that API key instead of the base API key.'),
    );
  while ($row = db_fetch_object($libquery)) {
    $form['ding_place2book_api_key_' . $row->nid] = array(
      '#type' => 'textfield',
      '#title' => 'API key ' . $row->title,
      '#default_value' => variable_get('ding_place2book_api_key_'.$row->nid, ''),
      '#description' => t('Optional. If you have several accounts at Place2book, each library can have their own API key. In that case, the base API key will be overridden by the provided key when sending data on events related to this library.'),
    );
  }

  $form['ding_place2book_event_nodes'] = array(
      '#type' => 'fieldset',
      '#title' => t('Place2Book event node defaults'),
      '#collapsible' => FALSE,
    );

  $form['ding_place2book_event_nodes']['ding_place2book_default_capacity'] = array(
    '#type' => 'textfield',
    '#title' => t('Capacity'),
    '#default_value' => variable_get('ding_place2book_default_capacity', 0),
    '#size' => 5,
    '#maxlength' => 5,
    '#description' => t('The default capacity for new events. Set to 0 for unlimited capacity.'),
    );

  $form['ding_place2book_event_nodes']['ding_place2book_defaults'] = array(
    '#type' => 'checkboxes',
    '#options' => array
      (
      'maintain_copy' => t('Maintain copy'),
      'kultunaut_export' => t('Kultunaut export'),
      ),
    '#default_value' => variable_get('ding_place2book_defaults', array('maintain_copy')),
    );
  
  return system_settings_form($form);
}
