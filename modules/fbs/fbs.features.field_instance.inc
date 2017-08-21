<?php
/**
 * @file
 * fbs.features.field_instance.inc
 */

/**
 * Implements hook_field_default_field_instances().
 */
function fbs_field_default_field_instances() {
  $field_instances = array();

  // Exported field_instance: 'profile2-provider_fbs-field_fbs_address'
  $field_instances['profile2-provider_fbs-field_fbs_address'] = array(
    'bundle' => 'provider_fbs',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'fbs',
        'settings' => array(),
        'type' => 'fbs_address_default',
        'weight' => 1,
      ),
    ),
    'entity_type' => 'profile2',
    'field_name' => 'field_fbs_address',
    'label' => 'Address',
    'required' => FALSE,
    'settings' => array(
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 0,
      'module' => 'virtual_field',
      'settings' => array(),
      'type' => 'hidden',
      'weight' => 15,
    ),
  );

  // Exported field_instance: 'profile2-provider_fbs-field_fbs_mail'
  $field_instances['profile2-provider_fbs-field_fbs_mail'] = array(
    'bundle' => 'provider_fbs',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 6,
      ),
    ),
    'entity_type' => 'profile2',
    'field_name' => 'field_fbs_mail',
    'label' => 'E-mail',
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

  // Exported field_instance: 'profile2-provider_fbs-field_fbs_mail_notification'
  $field_instances['profile2-provider_fbs-field_fbs_mail_notification'] = array(
    'bundle' => 'provider_fbs',
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
    'entity_type' => 'profile2',
    'field_name' => 'field_fbs_mail_notification',
    'label' => 'E-mail notifications',
    'required' => 0,
    'settings' => array(
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'fbs',
      'settings' => array(
        'display_label' => 1,
      ),
      'type' => 'fbs_options_onoff',
      'weight' => 5,
    ),
  );

  // Exported field_instance: 'profile2-provider_fbs-field_fbs_name'
  $field_instances['profile2-provider_fbs-field_fbs_name'] = array(
    'bundle' => 'provider_fbs',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'fbs',
        'settings' => array(),
        'type' => 'fbs_default',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'profile2',
    'field_name' => 'field_fbs_name',
    'label' => 'Name',
    'required' => FALSE,
    'settings' => array(
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 0,
      'module' => 'virtual_field',
      'settings' => array(),
      'type' => 'hidden',
      'weight' => 1,
    ),
  );

  // Exported field_instance: 'profile2-provider_fbs-field_fbs_on_hold'
  $field_instances['profile2-provider_fbs-field_fbs_on_hold'] = array(
    'bundle' => 'provider_fbs',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 3,
      ),
    ),
    'entity_type' => 'profile2',
    'field_name' => 'field_fbs_on_hold',
    'label' => 'On hold',
    'required' => 0,
    'settings' => array(
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 0,
      'module' => 'fbs',
      'settings' => array(),
      'type' => 'fbs_period',
      'weight' => 11,
    ),
  );

  // Exported field_instance: 'profile2-provider_fbs-field_fbs_phone'
  $field_instances['profile2-provider_fbs-field_fbs_phone'] = array(
    'bundle' => 'provider_fbs',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 7,
      ),
    ),
    'entity_type' => 'profile2',
    'field_name' => 'field_fbs_phone',
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
        'size' => 60,
      ),
      'type' => 'text_textfield',
      'weight' => 2,
    ),
  );

  // Exported field_instance: 'profile2-provider_fbs-field_fbs_phone_notification'
  $field_instances['profile2-provider_fbs-field_fbs_phone_notification'] = array(
    'bundle' => 'provider_fbs',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 4,
      ),
    ),
    'entity_type' => 'profile2',
    'field_name' => 'field_fbs_phone_notification',
    'label' => 'Phone notifications',
    'required' => 0,
    'settings' => array(
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'fbs',
      'settings' => array(
        'display_label' => 1,
      ),
      'type' => 'fbs_options_onoff',
      'weight' => 3,
    ),
  );

  // Exported field_instance: 'profile2-provider_fbs-field_fbs_preferred_branch'
  $field_instances['profile2-provider_fbs-field_fbs_preferred_branch'] = array(
    'bundle' => 'provider_fbs',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 2,
      ),
    ),
    'entity_type' => 'profile2',
    'field_name' => 'field_fbs_preferred_branch',
    'label' => 'Preferred branch',
    'required' => 0,
    'settings' => array(
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'fbs',
      'settings' => array(),
      'type' => 'fbs_options_select',
      'weight' => 7,
    ),
  );

  // Translatables
  // Included for use with string extractors like potx.
  t('Address');
  t('E-mail');
  t('E-mail notifications');
  t('Name');
  t('On hold');
  t('Phone');
  t('Phone notifications');
  t('Preferred branch');

  return $field_instances;
}
