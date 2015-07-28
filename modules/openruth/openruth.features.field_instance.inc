<?php
/**
 * @file
 * openruth.features.field_instance.inc
 */

/**
 * Implements hook_field_default_field_instances().
 */
function openruth_field_default_field_instances() {
  $field_instances = array();

  // Exported field_instance: 'profile2-provider_openruth-field_openruth_city'
  $field_instances['profile2-provider_openruth-field_openruth_city'] = array(
    'bundle' => 'provider_openruth',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'inline',
        'module' => 'text',
        'settings' => array(),
        'type' => 'text_default',
        'weight' => 3,
      ),
    ),
    'entity_type' => 'profile2',
    'field_name' => 'field_openruth_city',
    'label' => 'City',
    'required' => 0,
    'settings' => array(
      'text_processing' => 0,
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'module' => 'virtual_field',
      'settings' => array(),
      'type' => 'hidden',
      'weight' => 3,
    ),
  );

  // Exported field_instance: 'profile2-provider_openruth-field_openruth_full_name'
  $field_instances['profile2-provider_openruth-field_openruth_full_name'] = array(
    'bundle' => 'provider_openruth',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'inline',
        'module' => 'text',
        'settings' => array(),
        'type' => 'text_default',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'profile2',
    'field_name' => 'field_openruth_full_name',
    'label' => 'Full name',
    'required' => 0,
    'settings' => array(
      'text_processing' => 0,
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'module' => 'virtual_field',
      'settings' => array(),
      'type' => 'hidden',
      'weight' => 0,
    ),
  );

  // Exported field_instance: 'profile2-provider_openruth-field_openruth_interest_period'
  $field_instances['profile2-provider_openruth-field_openruth_interest_period'] = array(
    'bundle' => 'provider_openruth',
    'default_value' => array(
      0 => array(
        'value' => 30,
      ),
    ),
    'deleted' => 0,
    'description' => 'Period of interest - how long is a reservation valid for',
    'display' => array(
      'default' => array(
        'label' => 'inline',
        'module' => 'list',
        'settings' => array(),
        'type' => 'list_default',
        'weight' => 8,
      ),
    ),
    'entity_type' => 'profile2',
    'field_name' => 'field_openruth_interest_period',
    'label' => 'Interest period',
    'required' => 0,
    'settings' => array(
      'text_processing' => 0,
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'options',
      'settings' => array(),
      'type' => 'options_select',
      'weight' => 5,
    ),
  );

  // Exported field_instance: 'profile2-provider_openruth-field_openruth_mail'
  $field_instances['profile2-provider_openruth-field_openruth_mail'] = array(
    'bundle' => 'provider_openruth',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'inline',
        'module' => 'email',
        'settings' => array(),
        'type' => 'email_plain',
        'weight' => 4,
      ),
    ),
    'entity_type' => 'profile2',
    'field_name' => 'field_openruth_mail',
    'label' => 'E-mail',
    'required' => 0,
    'settings' => array(
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'email',
      'settings' => array(
        'size' => 60,
      ),
      'type' => 'email_textfield',
      'weight' => 7,
    ),
  );

  // Exported field_instance: 'profile2-provider_openruth-field_openruth_mobile_phone'
  $field_instances['profile2-provider_openruth-field_openruth_mobile_phone'] = array(
    'bundle' => 'provider_openruth',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => 'Your mobile phone',
    'display' => array(
      'default' => array(
        'label' => 'inline',
        'module' => 'text',
        'settings' => array(),
        'type' => 'text_default',
        'weight' => 5,
      ),
    ),
    'entity_type' => 'profile2',
    'field_name' => 'field_openruth_mobile_phone',
    'label' => 'Mobile phone',
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
      'weight' => 8,
    ),
  );

  // Exported field_instance: 'profile2-provider_openruth-field_openruth_postal_code'
  $field_instances['profile2-provider_openruth-field_openruth_postal_code'] = array(
    'bundle' => 'provider_openruth',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'inline',
        'module' => 'text',
        'settings' => array(),
        'type' => 'text_default',
        'weight' => 2,
      ),
    ),
    'entity_type' => 'profile2',
    'field_name' => 'field_openruth_postal_code',
    'label' => 'Postal code',
    'required' => 0,
    'settings' => array(
      'text_processing' => 0,
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'module' => 'virtual_field',
      'settings' => array(),
      'type' => 'hidden',
      'weight' => 2,
    ),
  );

  // Exported field_instance: 'profile2-provider_openruth-field_openruth_preferred_branch'
  $field_instances['profile2-provider_openruth-field_openruth_preferred_branch'] = array(
    'bundle' => 'provider_openruth',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'inline',
        'module' => 'list',
        'settings' => array(),
        'type' => 'list_default',
        'weight' => 7,
      ),
    ),
    'entity_type' => 'profile2',
    'field_name' => 'field_openruth_preferred_branch',
    'label' => 'Preferred branch',
    'required' => 0,
    'settings' => array(
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'options',
      'settings' => array(),
      'type' => 'options_select',
      'weight' => 4,
    ),
  );

  // Exported field_instance: 'profile2-provider_openruth-field_openruth_reservation_pause'
  $field_instances['profile2-provider_openruth-field_openruth_reservation_pause'] = array(
    'bundle' => 'provider_openruth',
    'deleted' => 0,
    'description' => 'Set your reservations on pause.',
    'display' => array(
      'default' => array(
        'label' => 'inline',
        'module' => 'date',
        'settings' => array(
          'format_type' => 'long',
          'fromto' => 'both',
          'multiple_from' => '',
          'multiple_number' => '',
          'multiple_to' => '',
        ),
        'type' => 'date_default',
        'weight' => 7,
      ),
    ),
    'entity_type' => 'profile2',
    'field_name' => 'field_openruth_reservation_pause',
    'label' => 'Reservation pause',
    'required' => 0,
    'settings' => array(
      'default_value' => 'blank',
      'default_value2' => 'blank',
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
        'input_format' => 'd/m/Y',
        'input_format_custom' => '',
        'label_position' => 'above',
        'repeat_collapsed' => 0,
        'text_parts' => array(),
        'year_range' => '-3:+3',
      ),
      'type' => 'date_popup',
      'weight' => 6,
    ),
  );

  // Exported field_instance: 'profile2-provider_openruth-field_openruth_street_name'
  $field_instances['profile2-provider_openruth-field_openruth_street_name'] = array(
    'bundle' => 'provider_openruth',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'inline',
        'module' => 'text',
        'settings' => array(),
        'type' => 'text_default',
        'weight' => 1,
      ),
    ),
    'entity_type' => 'profile2',
    'field_name' => 'field_openruth_street_name',
    'label' => 'Street name',
    'required' => 0,
    'settings' => array(
      'text_processing' => 0,
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'module' => 'virtual_field',
      'settings' => array(),
      'type' => 'hidden',
      'weight' => 1,
    ),
  );

  // Translatables
  // Included for use with string extractors like potx.
  t('City');
  t('E-mail');
  t('Full name');
  t('Interest period');
  t('Mobile phone');
  t('Period of interest - how long is a reservation valid for');
  t('Postal code');
  t('Preferred branch');
  t('Reservation pause');
  t('Set your reservations on pause.');
  t('Street name');
  t('Your mobile phone');

  return $field_instances;
}
