<?php

/**
 * @file
 * ding_message_p2_installer.features.field_instance.inc
 */

/**
 * Implements hook_field_default_field_instances().
 */
function ding_message_p2_installer_field_default_field_instances() {
  $field_instances = array();

  // Exported field_instance: 'message-new_content-field_first_element'.
  $field_instances['message-new_content-field_first_element'] = array(
    'bundle' => 'new_content',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => 'The first element of the new items.',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 6,
      ),
    ),
    'entity_type' => 'message',
    'field_name' => 'field_first_element',
    'label' => 'First element',
    'required' => 0,
    'settings' => array(
      'text_processing' => 0,
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'text',
      'settings' => array(
        'size' => 60,
      ),
      'type' => 'text_textfield',
      'weight' => 2,
    ),
  );

  // Exported field_instance: 'message-new_content-field_last_check'.
  $field_instances['message-new_content-field_last_check'] = array(
    'bundle' => 'new_content',
    'deleted' => 0,
    'description' => 'Enter the time of the last check for updates as a unix timestamp.',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 1,
      ),
    ),
    'entity_type' => 'message',
    'field_name' => 'field_last_check',
    'label' => 'Last check',
    'required' => 0,
    'settings' => array(
      'default_value' => 'now',
      'default_value2' => 'same',
      'default_value_code' => '',
      'default_value_code2' => '',
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'date',
      'settings' => array(
        'display_all_day' => 0,
        'increment' => 15,
        'input_format' => 'Y-m-d H:i:s',
        'input_format_custom' => '',
        'label_position' => 'above',
        'text_parts' => array(),
        'year_range' => '-3:+3',
      ),
      'type' => 'date_text',
      'weight' => 1,
    ),
  );

  // Exported field_instance: 'message-new_content-field_last_element'.
  $field_instances['message-new_content-field_last_element'] = array(
    'bundle' => 'new_content',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => 'The last element when we last did an update check.',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 2,
      ),
    ),
    'entity_type' => 'message',
    'field_name' => 'field_last_element',
    'label' => 'Last element',
    'required' => 0,
    'settings' => array(
      'text_processing' => 0,
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'text',
      'settings' => array(
        'size' => 60,
      ),
      'type' => 'text_textfield',
      'weight' => 3,
    ),
  );

  // Exported field_instance: 'message-new_content-field_list_id'.
  $field_instances['message-new_content-field_list_id'] = array(
    'bundle' => 'new_content',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => 'Enter the list this message is related to.',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'message',
    'field_name' => 'field_list_id',
    'label' => 'List id',
    'required' => 0,
    'settings' => array(
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'entityreference',
      'settings' => array(
        'match_operator' => 'CONTAINS',
        'path' => '',
        'size' => 60,
      ),
      'type' => 'entityreference_autocomplete',
      'weight' => 0,
    ),
  );

  // Exported field_instance: 'message-new_content-field_new_count'.
  $field_instances['message-new_content-field_new_count'] = array(
    'bundle' => 'new_content',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => 'Number of new elements.',
    'display' => array(
      'default' => array(
        'label' => 'hidden',
        'module' => 'text',
        'settings' => array(),
        'type' => 'text_default',
        'weight' => 3,
      ),
    ),
    'entity_type' => 'message',
    'field_name' => 'field_new_count',
    'label' => 'New count',
    'required' => 0,
    'settings' => array(
      'text_processing' => 0,
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'text',
      'settings' => array(
        'size' => 60,
      ),
      'type' => 'text_textfield',
      'weight' => 4,
    ),
  );

  // Exported field_instance: 'message-new_content-field_state'.
  $field_instances['message-new_content-field_state'] = array(
    'bundle' => 'new_content',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 5,
      ),
    ),
    'entity_type' => 'message',
    'field_name' => 'field_state',
    'label' => 'State',
    'required' => 0,
    'settings' => array(
      'text_processing' => 0,
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'text',
      'settings' => array(
        'size' => 60,
      ),
      'type' => 'text_textfield',
      'weight' => 5,
    ),
  );

  // Translatables
  // Included for use with string extractors like potx.
  t('Enter the list this message is related to.');
  t('Enter the time of the last check for updates as a unix timestamp.');
  t('First element');
  t('Last check');
  t('Last element');
  t('List id');
  t('New count');
  t('Number of new elements.');
  t('State');
  t('The first element of the new items.');
  t('The last element when we last did an update check.');

  return $field_instances;
}
