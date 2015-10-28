<?php
/**
 * @file
 * alma.features.field_instance.inc
 */

/**
 * Implements hook_field_default_field_instances().
 */
function alma_field_default_field_instances() {
  $field_instances = array();

  // Exported field_instance: 'profile2-provider_alma-field_alma_absent_id'
  $field_instances['profile2-provider_alma-field_alma_absent_id'] = array(
    'bundle' => 'provider_alma',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'hidden',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 10,
      ),
    ),
    'entity_type' => 'profile2',
    'field_name' => 'field_alma_absent_id',
    'label' => 'Absent id',
    'required' => 0,
    'settings' => array(
      'text_processing' => 0,
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'module' => 'virtual_field',
      'settings' => array(),
      'type' => 'hidden',
      'weight' => 10,
    ),
  );

  // Exported field_instance: 'profile2-provider_alma-field_alma_city'
  $field_instances['profile2-provider_alma-field_alma_city'] = array(
    'bundle' => 'provider_alma',
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
    'field_name' => 'field_alma_city',
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

  // Exported field_instance: 'profile2-provider_alma-field_alma_full_name'
  $field_instances['profile2-provider_alma-field_alma_full_name'] = array(
    'bundle' => 'provider_alma',
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
    'field_name' => 'field_alma_full_name',
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

  // Exported field_instance: 'profile2-provider_alma-field_alma_interest_period'
  $field_instances['profile2-provider_alma-field_alma_interest_period'] = array(
    'bundle' => 'provider_alma',
    'default_value' => array(
      0 => array(
        'value' => 180,
      ),
    ),
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'inline',
        'module' => 'list',
        'settings' => array(),
        'type' => 'list_default',
        'weight' => 9,
      ),
    ),
    'entity_type' => 'profile2',
    'field_name' => 'field_alma_interest_period',
    'label' => 'Interest period',
    'required' => 0,
    'settings' => array(
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

  // Exported field_instance: 'profile2-provider_alma-field_alma_mail'
  $field_instances['profile2-provider_alma-field_alma_mail'] = array(
    'bundle' => 'provider_alma',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => 'The e-mail address is not made public and will only be used if you wish to receive certain news or notifications by e-mail.',
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
    'field_name' => 'field_alma_mail',
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

  // Exported field_instance: 'profile2-provider_alma-field_alma_mobile_phone'
  $field_instances['profile2-provider_alma-field_alma_mobile_phone'] = array(
    'bundle' => 'provider_alma',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'inline',
        'module' => 'text',
        'settings' => array(),
        'type' => 'text_default',
        'weight' => 6,
      ),
    ),
    'entity_type' => 'profile2',
    'field_name' => 'field_alma_mobile_phone',
    'label' => 'Phone',
    'required' => 0,
    'settings' => array(
      'text_processing' => 0,
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'text',
      'settings' => array(
        'size' => 12,
      ),
      'type' => 'text_textfield',
      'weight' => 9,
    ),
  );

  // Exported field_instance: 'profile2-provider_alma-field_alma_phone_id'
  $field_instances['profile2-provider_alma-field_alma_phone_id'] = array(
    'bundle' => 'provider_alma',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'hidden',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 11,
      ),
    ),
    'entity_type' => 'profile2',
    'field_name' => 'field_alma_phone_id',
    'label' => 'Phone id',
    'required' => FALSE,
    'settings' => array(
      'text_processing' => 0,
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'module' => 'virtual_field',
      'settings' => array(),
      'type' => 'hidden',
      'weight' => 12,
    ),
  );

  // Exported field_instance: 'profile2-provider_alma-field_alma_postal_code'
  $field_instances['profile2-provider_alma-field_alma_postal_code'] = array(
    'bundle' => 'provider_alma',
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
    'field_name' => 'field_alma_postal_code',
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

  // Exported field_instance: 'profile2-provider_alma-field_alma_preferred_branch'
  $field_instances['profile2-provider_alma-field_alma_preferred_branch'] = array(
    'bundle' => 'provider_alma',
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
    'field_name' => 'field_alma_preferred_branch',
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

  // Exported field_instance: 'profile2-provider_alma-field_alma_reservation_pause'
  $field_instances['profile2-provider_alma-field_alma_reservation_pause'] = array(
    'bundle' => 'provider_alma',
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
        'weight' => 8,
      ),
    ),
    'entity_type' => 'profile2',
    'field_name' => 'field_alma_reservation_pause',
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

  // Exported field_instance: 'profile2-provider_alma-field_alma_sms'
  $field_instances['profile2-provider_alma-field_alma_sms'] = array(
    'bundle' => 'provider_alma',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
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
    'field_name' => 'field_alma_sms',
    'label' => 'SMS',
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

  // Exported field_instance: 'profile2-provider_alma-field_alma_sms_id'
  $field_instances['profile2-provider_alma-field_alma_sms_id'] = array(
    'bundle' => 'provider_alma',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'hidden',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 12,
      ),
    ),
    'entity_type' => 'profile2',
    'field_name' => 'field_alma_sms_id',
    'label' => 'SMS id',
    'required' => 0,
    'settings' => array(
      'text_processing' => 0,
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'module' => 'virtual_field',
      'settings' => array(),
      'type' => 'hidden',
      'weight' => 11,
    ),
  );

  // Exported field_instance: 'profile2-provider_alma-field_alma_street_name'
  $field_instances['profile2-provider_alma-field_alma_street_name'] = array(
    'bundle' => 'provider_alma',
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
    'field_name' => 'field_alma_street_name',
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
  t('Absent id');
  t('City');
  t('E-mail');
  t('Full name');
  t('Interest period');
  t('Phone');
  t('Phone id');
  t('Postal code');
  t('Preferred branch');
  t('Reservation pause');
  t('SMS');
  t('SMS id');
  t('Set your reservations on pause.');
  t('Street name');
  t('The e-mail address is not made public and will only be used if you wish to receive certain news or notifications by e-mail.');

  return $field_instances;
}
