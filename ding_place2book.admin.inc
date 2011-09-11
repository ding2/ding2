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

  $form['ding_place2book_api_key'] = array(
    '#type' => 'textfield',
    '#title' => t('Place2Book API key'),
    '#default_value' => variable_get('ding_place2book_api_key', ''),
    '#required' => TRUE,
    '#size' => 60,
  );
	
	$form['ding_place2book_service_url'] = array(
    '#type' => 'textfield',
    '#title' => t('Place2Book service URL'),
    '#default_value' => variable_get('ding_place2book_service_url', ''),
    '#required' => TRUE,
    '#size' => 100,
  );

  return system_settings_form($form);
}