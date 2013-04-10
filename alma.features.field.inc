<?php
/**
 * @file
 * alma.features.field.inc
 */

/**
 * Implements hook_field_default_fields().
 */
function alma_field_default_fields() {
  $fields = array();

  // Exported field: 'profile2-provider_alma-field_alma_absent_id'.
  $fields['profile2-provider_alma-field_alma_absent_id'] = array(
    'field_config' => array(
      'active' => '1',
      'cardinality' => '1',
      'deleted' => '0',
      'entity_types' => array(),
      'field_name' => 'field_alma_absent_id',
      'foreign keys' => array(
        'format' => array(
          'columns' => array(
            'format' => 'format',
          ),
          'table' => 'filter_format',
        ),
      ),
      'indexes' => array(
        'format' => array(
          0 => 'format',
        ),
      ),
      'locked' => '0',
      'module' => 'text',
      'settings' => array(
        'max_length' => '255',
        'profile2_private' => 0,
      ),
      'storage' => array(
        'active' => '1',
        'module' => 'virtual_field',
        'settings' => array(),
        'type' => 'virtual_field',
      ),
      'translatable' => '0',
      'type' => 'text',
      'virtual_field' => array(
        'entity_types' => array(
          0 => 'profile2',
        ),
      ),
    ),
    'field_instance' => array(
      'bundle' => 'provider_alma',
      'default_value' => NULL,
      'deleted' => '0',
      'description' => '',
      'display' => array(
        'default' => array(
          'label' => 'hidden',
          'settings' => array(),
          'type' => 'hidden',
          'weight' => '8',
        ),
      ),
      'entity_type' => 'profile2',
      'field_name' => 'field_alma_absent_id',
      'label' => 'Absent id',
      'required' => 0,
      'settings' => array(
        'text_processing' => '0',
        'user_register_form' => FALSE,
      ),
      'widget' => array(
        'module' => 'virtual_field',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => '38',
      ),
    ),
  );

  // Exported field: 'profile2-provider_alma-field_alma_city'.
  $fields['profile2-provider_alma-field_alma_city'] = array(
    'field_config' => array(
      'active' => '1',
      'cardinality' => '1',
      'deleted' => '0',
      'entity_types' => array(),
      'field_name' => 'field_alma_city',
      'foreign keys' => array(
        'format' => array(
          'columns' => array(
            'format' => 'format',
          ),
          'table' => 'filter_format',
        ),
      ),
      'indexes' => array(
        'format' => array(
          0 => 'format',
        ),
      ),
      'locked' => '0',
      'module' => 'text',
      'settings' => array(
        'max_length' => '255',
        'profile2_private' => 0,
      ),
      'storage' => array(
        'active' => '1',
        'module' => 'virtual_field',
        'settings' => array(),
        'type' => 'virtual_field',
      ),
      'translatable' => '0',
      'type' => 'text',
      'virtual_field' => array(
        'entity_types' => array(
          0 => 'profile2',
        ),
      ),
    ),
    'field_instance' => array(
      'bundle' => 'provider_alma',
      'default_value' => NULL,
      'deleted' => '0',
      'description' => '',
      'display' => array(
        'default' => array(
          'label' => 'above',
          'module' => 'text',
          'settings' => array(),
          'type' => 'text_default',
          'weight' => '3',
        ),
      ),
      'entity_type' => 'profile2',
      'field_name' => 'field_alma_city',
      'label' => 'City',
      'required' => 0,
      'settings' => array(
        'text_processing' => '0',
        'user_register_form' => FALSE,
      ),
      'widget' => array(
        'module' => 'virtual_field',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => '38',
      ),
    ),
  );

  // Exported field: 'profile2-provider_alma-field_alma_full_name'.
  $fields['profile2-provider_alma-field_alma_full_name'] = array(
    'field_config' => array(
      'active' => '1',
      'cardinality' => '1',
      'deleted' => '0',
      'entity_types' => array(),
      'field_name' => 'field_alma_full_name',
      'foreign keys' => array(
        'format' => array(
          'columns' => array(
            'format' => 'format',
          ),
          'table' => 'filter_format',
        ),
      ),
      'indexes' => array(
        'format' => array(
          0 => 'format',
        ),
      ),
      'locked' => '0',
      'module' => 'text',
      'settings' => array(
        'max_length' => '255',
        'profile2_private' => 0,
      ),
      'storage' => array(
        'active' => '1',
        'module' => 'virtual_field',
        'settings' => array(),
        'type' => 'virtual_field',
      ),
      'translatable' => '0',
      'type' => 'text',
      'virtual_field' => array(
        'entity_types' => array(
          0 => 'profile2',
        ),
      ),
    ),
    'field_instance' => array(
      'bundle' => 'provider_alma',
      'default_value' => NULL,
      'deleted' => '0',
      'description' => '',
      'display' => array(
        'default' => array(
          'label' => 'above',
          'module' => 'text',
          'settings' => array(),
          'type' => 'text_default',
          'weight' => '0',
        ),
      ),
      'entity_type' => 'profile2',
      'field_name' => 'field_alma_full_name',
      'label' => 'Full name',
      'required' => 0,
      'settings' => array(
        'text_processing' => '0',
        'user_register_form' => FALSE,
      ),
      'widget' => array(
        'module' => 'virtual_field',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => '38',
      ),
    ),
  );

  // Exported field: 'profile2-provider_alma-field_alma_interest_period'.
  $fields['profile2-provider_alma-field_alma_interest_period'] = array(
    'field_config' => array(
      'active' => '1',
      'cardinality' => '1',
      'deleted' => '0',
      'entity_types' => array(),
      'field_name' => 'field_alma_interest_period',
      'foreign keys' => array(),
      'indexes' => array(
        'value' => array(
          0 => 'value',
        ),
      ),
      'locked' => '0',
      'module' => 'list',
      'settings' => array(
        'allowed_values' => array(
          30 => '1 måned',
          60 => '2 months',
          90 => '3 months',
          180 => '6 months',
        ),
        'allowed_values_function' => '',
        'profile2_private' => 0,
      ),
      'storage' => array(
        'active' => '1',
        'module' => 'virtual_field',
        'settings' => array(),
        'type' => 'virtual_field',
      ),
      'translatable' => '0',
      'type' => 'list_text',
      'virtual_field' => array(
        'entity_types' => array(
          0 => 'profile2',
        ),
      ),
    ),
    'field_instance' => array(
      'bundle' => 'provider_alma',
      'default_value' => array(
        0 => array(
          'value' => '30',
        ),
      ),
      'deleted' => '0',
      'description' => '',
      'display' => array(
        'default' => array(
          'label' => 'above',
          'module' => 'list',
          'settings' => array(),
          'type' => 'list_default',
          'weight' => '7',
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
        'weight' => '5',
      ),
    ),
  );

  // Exported field: 'profile2-provider_alma-field_alma_mobile_phone'.
  $fields['profile2-provider_alma-field_alma_mobile_phone'] = array(
    'field_config' => array(
      'active' => '1',
      'cardinality' => '1',
      'deleted' => '0',
      'entity_types' => array(),
      'field_name' => 'field_alma_mobile_phone',
      'foreign keys' => array(
        'format' => array(
          'columns' => array(
            'format' => 'format',
          ),
          'table' => 'filter_format',
        ),
      ),
      'indexes' => array(
        'format' => array(
          0 => 'format',
        ),
      ),
      'locked' => '0',
      'module' => 'text',
      'settings' => array(
        'max_length' => '16',
        'profile2_private' => 0,
      ),
      'storage' => array(
        'active' => '1',
        'module' => 'virtual_field',
        'settings' => array(),
        'type' => 'virtual_field',
      ),
      'translatable' => '0',
      'type' => 'text',
      'virtual_field' => array(
        'entity_types' => array(
          0 => 'profile2',
        ),
      ),
    ),
    'field_instance' => array(
      'bundle' => 'provider_alma',
      'default_value' => NULL,
      'deleted' => '0',
      'description' => '',
      'display' => array(
        'default' => array(
          'label' => 'above',
          'module' => 'text',
          'settings' => array(),
          'type' => 'text_default',
          'weight' => '4',
        ),
      ),
      'entity_type' => 'profile2',
      'field_name' => 'field_alma_mobile_phone',
      'label' => 'Phone',
      'required' => 0,
      'settings' => array(
        'text_processing' => '0',
        'user_register_form' => FALSE,
      ),
      'widget' => array(
        'active' => 1,
        'module' => 'text',
        'settings' => array(
          'size' => '12',
        ),
        'type' => 'text_textfield',
        'weight' => '8',
      ),
    ),
  );

  // Exported field: 'profile2-provider_alma-field_alma_phone_id'.
  $fields['profile2-provider_alma-field_alma_phone_id'] = array(
    'field_config' => array(
      'active' => '1',
      'cardinality' => '1',
      'deleted' => '0',
      'entity_types' => array(),
      'field_name' => 'field_alma_phone_id',
      'foreign keys' => array(
        'format' => array(
          'columns' => array(
            'format' => 'format',
          ),
          'table' => 'filter_format',
        ),
      ),
      'indexes' => array(
        'format' => array(
          0 => 'format',
        ),
      ),
      'locked' => '0',
      'module' => 'text',
      'settings' => array(
        'max_length' => '255',
      ),
      'storage' => array(
        'active' => '1',
        'module' => 'virtual_field',
        'settings' => array(),
        'type' => 'virtual_field',
      ),
      'translatable' => '0',
      'type' => 'text',
      'virtual_field' => array(
        'entity_types' => array(
          0 => 'profile2',
        ),
      ),
    ),
    'field_instance' => array(
      'bundle' => 'provider_alma',
      'default_value' => NULL,
      'deleted' => '0',
      'description' => '',
      'display' => array(
        'default' => array(
          'label' => 'hidden',
          'settings' => array(),
          'type' => 'hidden',
          'weight' => '9',
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
        'weight' => '38',
      ),
    ),
  );

  // Exported field: 'profile2-provider_alma-field_alma_postal_code'.
  $fields['profile2-provider_alma-field_alma_postal_code'] = array(
    'field_config' => array(
      'active' => '1',
      'cardinality' => '1',
      'deleted' => '0',
      'entity_types' => array(),
      'field_name' => 'field_alma_postal_code',
      'foreign keys' => array(
        'format' => array(
          'columns' => array(
            'format' => 'format',
          ),
          'table' => 'filter_format',
        ),
      ),
      'indexes' => array(
        'format' => array(
          0 => 'format',
        ),
      ),
      'locked' => '0',
      'module' => 'text',
      'settings' => array(
        'max_length' => '255',
        'profile2_private' => 0,
      ),
      'storage' => array(
        'active' => '1',
        'module' => 'virtual_field',
        'settings' => array(),
        'type' => 'virtual_field',
      ),
      'translatable' => '0',
      'type' => 'text',
      'virtual_field' => array(
        'entity_types' => array(
          0 => 'profile2',
        ),
      ),
    ),
    'field_instance' => array(
      'bundle' => 'provider_alma',
      'default_value' => NULL,
      'deleted' => '0',
      'description' => '',
      'display' => array(
        'default' => array(
          'label' => 'above',
          'module' => 'text',
          'settings' => array(),
          'type' => 'text_default',
          'weight' => '2',
        ),
      ),
      'entity_type' => 'profile2',
      'field_name' => 'field_alma_postal_code',
      'label' => 'Postal code',
      'required' => 0,
      'settings' => array(
        'text_processing' => '0',
        'user_register_form' => FALSE,
      ),
      'widget' => array(
        'module' => 'virtual_field',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => '38',
      ),
    ),
  );

  // Exported field: 'profile2-provider_alma-field_alma_preferred_branch'.
  $fields['profile2-provider_alma-field_alma_preferred_branch'] = array(
    'field_config' => array(
      'active' => '1',
      'cardinality' => '1',
      'deleted' => '0',
      'entity_types' => array(),
      'field_name' => 'field_alma_preferred_branch',
      'foreign keys' => array(),
      'indexes' => array(
        'value' => array(
          0 => 'value',
        ),
      ),
      'locked' => '0',
      'module' => 'list',
      'settings' => array(
        'allowed_values' => array(),
        'allowed_values_function' => 'alma_reservation_pickup_branches',
        'profile2_private' => 0,
      ),
      'storage' => array(
        'active' => '1',
        'module' => 'virtual_field',
        'settings' => array(),
        'type' => 'virtual_field',
      ),
      'translatable' => '0',
      'type' => 'list_text',
      'virtual_field' => array(
        'entity_types' => array(
          0 => 'profile2',
        ),
      ),
    ),
    'field_instance' => array(
      'bundle' => 'provider_alma',
      'default_value' => NULL,
      'deleted' => '0',
      'description' => '',
      'display' => array(
        'default' => array(
          'label' => 'above',
          'module' => 'list',
          'settings' => array(),
          'type' => 'list_default',
          'weight' => '5',
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
        'weight' => '4',
      ),
    ),
  );

  // Exported field: 'profile2-provider_alma-field_alma_reservation_pause'.
  $fields['profile2-provider_alma-field_alma_reservation_pause'] = array(
    'field_config' => array(
      'active' => '1',
      'cardinality' => '1',
      'deleted' => '0',
      'entity_types' => array(),
      'field_name' => 'field_alma_reservation_pause',
      'foreign keys' => array(),
      'indexes' => array(),
      'locked' => '0',
      'module' => 'date',
      'settings' => array(
        'granularity' => array(
          'day' => 'day',
          'hour' => 0,
          'minute' => 0,
          'month' => 'month',
          'second' => 0,
          'year' => 'year',
        ),
        'profile2_private' => 0,
        'repeat' => 0,
        'timezone_db' => '',
        'todate' => 'required',
        'tz_handling' => 'none',
      ),
      'storage' => array(
        'active' => '1',
        'module' => 'virtual_field',
        'settings' => array(),
        'type' => 'virtual_field',
      ),
      'translatable' => '0',
      'type' => 'date',
      'virtual_field' => array(
        'entity_types' => array(
          0 => 'profile2',
        ),
      ),
    ),
    'field_instance' => array(
      'bundle' => 'provider_alma',
      'deleted' => '0',
      'description' => 'Set your reservations on pause.',
      'display' => array(
        'default' => array(
          'label' => 'above',
          'module' => 'date',
          'settings' => array(
            'format_type' => 'long',
            'fromto' => 'both',
            'multiple_from' => '',
            'multiple_number' => '',
            'multiple_to' => '',
          ),
          'type' => 'date_default',
          'weight' => '6',
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
          'increment' => '15',
          'input_format' => 'd/m/Y',
          'input_format_custom' => '',
          'label_position' => 'above',
          'repeat_collapsed' => 0,
          'text_parts' => array(),
          'year_range' => '-3:+3',
        ),
        'type' => 'date_popup',
        'weight' => '6',
      ),
    ),
  );

  // Exported field: 'profile2-provider_alma-field_alma_street_name'.
  $fields['profile2-provider_alma-field_alma_street_name'] = array(
    'field_config' => array(
      'active' => '1',
      'cardinality' => '1',
      'deleted' => '0',
      'entity_types' => array(),
      'field_name' => 'field_alma_street_name',
      'foreign keys' => array(
        'format' => array(
          'columns' => array(
            'format' => 'format',
          ),
          'table' => 'filter_format',
        ),
      ),
      'indexes' => array(
        'format' => array(
          0 => 'format',
        ),
      ),
      'locked' => '0',
      'module' => 'text',
      'settings' => array(
        'max_length' => '255',
        'profile2_private' => 0,
      ),
      'storage' => array(
        'active' => '1',
        'module' => 'virtual_field',
        'settings' => array(),
        'type' => 'virtual_field',
      ),
      'translatable' => '0',
      'type' => 'text',
      'virtual_field' => array(
        'entity_types' => array(
          0 => 'profile2',
        ),
      ),
    ),
    'field_instance' => array(
      'bundle' => 'provider_alma',
      'default_value' => NULL,
      'deleted' => '0',
      'description' => '',
      'display' => array(
        'default' => array(
          'label' => 'above',
          'module' => 'text',
          'settings' => array(),
          'type' => 'text_default',
          'weight' => '1',
        ),
      ),
      'entity_type' => 'profile2',
      'field_name' => 'field_alma_street_name',
      'label' => 'Street name',
      'required' => 0,
      'settings' => array(
        'text_processing' => '0',
        'user_register_form' => FALSE,
      ),
      'widget' => array(
        'module' => 'virtual_field',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => '38',
      ),
    ),
  );

  // Translatables
  // Included for use with string extractors like potx.
  t('Absent id');
  t('City');
  t('Full name');
  t('Interest period');
  t('Phone');
  t('Phone id');
  t('Postal code');
  t('Preferred branch');
  t('Reservation pause');
  t('Set your reservations on pause.');
  t('Street name');

  return $fields;
}
