<?php

/**
 * @file
 * ding_message_p2_installer.strongarm.inc
 */

/**
 * Implements hook_strongarm().
 */
function ding_message_p2_installer_strongarm() {
  $export = array();

  $strongarm = new stdClass();
  /* Edit this to true to make a default strongarm disabled initially */

  $strongarm->disabled = FALSE;
  $strongarm->api_version = 1;
  $strongarm->name = 'field_bundle_settings_message__new_content';
  $strongarm->value = array(
    'view_modes' => array(
      'full' => array(
        'custom_settings' => FALSE,
      ),
      'token' => array(
        'custom_settings' => FALSE,
      ),
    ),
    'extra_fields' => array(
      'form' => array(),
      'display' => array(
        'message__message_text__0' => array(
          'default' => array(
            'weight' => '0',
            'visible' => FALSE,
          ),
        ),
      ),
    ),
  );
  $export['field_bundle_settings_message__new_content'] = $strongarm;

  return $export;
}
