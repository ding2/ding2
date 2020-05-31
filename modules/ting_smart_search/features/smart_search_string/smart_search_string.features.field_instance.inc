<?php
/**
 * @file
 * smart_search_string.features.field_instance.inc
 */

/**
 * Implements hook_field_default_field_instances().
 */
function smart_search_string_field_default_field_instances() {
  $field_instances = array();

  // Exported field_instance:
  // 'paragraphs_item-custom_boost_values-field_field_boost_value'.
  $field_instances['paragraphs_item-custom_boost_values-field_field_boost_value'] = array(
    'bundle' => 'custom_boost_values',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'text',
        'settings' => array(),
        'type' => 'text_default',
        'weight' => 1,
      ),
      'paragraphs_editor_preview' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'paragraphs_item',
    'field_name' => 'field_field_boost_value',
    'label' => 'Parameter',
    'required' => 0,
    'settings' => array(
      'text_processing' => 0,
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'text',
      'settings' => array(
        'size' => 20,
      ),
      'type' => 'text_textfield',
      'weight' => 4,
    ),
  );

  // Exported field_instance:
  // 'paragraphs_item-custom_boost_values-field_field_boost_weight'.
  $field_instances['paragraphs_item-custom_boost_values-field_field_boost_weight'] = array(
    'bundle' => 'custom_boost_values',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'text',
        'settings' => array(),
        'type' => 'text_default',
        'weight' => 2,
      ),
      'paragraphs_editor_preview' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'paragraphs_item',
    'field_name' => 'field_field_boost_weight',
    'label' => 'Boost værdi',
    'required' => 0,
    'settings' => array(
      'text_processing' => 0,
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'text',
      'settings' => array(
        'size' => 8,
      ),
      'type' => 'text_textfield',
      'weight' => 6,
    ),
  );

  // Exported field_instance:
  // 'paragraphs_item-custom_boost_values-field_field_name'.
  $field_instances['paragraphs_item-custom_boost_values-field_field_name'] = array(
    'bundle' => 'custom_boost_values',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'list',
        'settings' => array(),
        'type' => 'list_default',
        'weight' => 0,
      ),
      'paragraphs_editor_preview' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'paragraphs_item',
    'field_name' => 'field_field_name',
    'label' => 'Feltnavn',
    'required' => 0,
    'settings' => array(
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'options',
      'settings' => array(),
      'type' => 'options_select',
      'weight' => 2,
    ),
  );

  // Exported field_instance:
  // 'ting_type-smart_search_string-field_alternate_search_string'.
  $field_instances['ting_type-smart_search_string-field_alternate_search_string'] = array(
    'bundle' => 'smart_search_string',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => 'Search string sent to the well',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'text',
        'settings' => array(),
        'type' => 'text_default',
        'weight' => 3,
      ),
      'teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'ting_type',
    'field_name' => 'field_alternate_search_string',
    'label' => 'Alternative search string',
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
      'weight' => 7,
    ),
  );

  // Exported field_instance:
  // 'ting_type-smart_search_string-field_custom_boost_values_p'.
  $field_instances['ting_type-smart_search_string-field_custom_boost_values_p'] = array(
    'bundle' => 'smart_search_string',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'paragraphs',
        'settings' => array(
          'view_mode' => 'full',
        ),
        'type' => 'paragraphs_view',
        'weight' => 6,
      ),
      'teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'ting_type',
    'field_name' => 'field_custom_boost_values_p',
    'label' => 'Boost values',
    'required' => 0,
    'settings' => array(
      'add_mode' => 'button',
      'allowed_bundles' => array(
        'custom_boost_values' => 'custom_boost_values',
      ),
      'bundle_weights' => array(
        'custom_boost_values' => -2,
      ),
      'default_edit_mode' => 'open',
      'title' => 'Paragraph',
      'title_multiple' => 'Paragraphs',
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 0,
      'module' => 'paragraphs',
      'settings' => array(),
      'type' => 'paragraphs_embed',
      'weight' => 17,
    ),
  );

  // Exported field_instance:
  // 'ting_type-smart_search_string-field_sss_boost_materials'.
  $field_instances['ting_type-smart_search_string-field_sss_boost_materials'] = array(
    'bundle' => 'smart_search_string',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => 'Only materials part of the result can be promoted',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'text',
        'settings' => array(),
        'type' => 'text_default',
        'weight' => 4,
      ),
      'teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'ting_type',
    'field_name' => 'field_sss_boost_materials',
    'label' => 'Promoted materials',
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
      'weight' => 15,
    ),
  );

  // Exported field_instance: 'ting_type-smart_search_string-field_sss_date'.
  $field_instances['ting_type-smart_search_string-field_sss_date'] = array(
    'bundle' => 'smart_search_string',
    'deleted' => 0,
    'description' => '',
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
        'weight' => 10,
      ),
      'teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'ting_type',
    'field_name' => 'field_sss_date',
    'label' => 'Date',
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
        'input_format' => 'd-m-Y H:i:s',
        'input_format_custom' => '',
        'label_position' => 'none',
        'text_parts' => array(),
        'year_range' => '-0:+2',
      ),
      'type' => 'date_popup',
      'weight' => 6,
    ),
  );

  // Exported field_instance:
  // 'ting_type-smart_search_string-field_sss_hits_per_month'.
  $field_instances['ting_type-smart_search_string-field_sss_hits_per_month'] = array(
    'bundle' => 'smart_search_string',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'number',
        'settings' => array(
          'decimal_separator' => '.',
          'prefix_suffix' => TRUE,
          'scale' => 0,
          'thousand_separator' => '',
        ),
        'type' => 'number_integer',
        'weight' => 9,
      ),
      'teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'ting_type',
    'field_name' => 'field_sss_hits_per_month',
    'label' => 'Searches - 30 days',
    'required' => 0,
    'settings' => array(
      'max' => '',
      'min' => '',
      'prefix' => '',
      'suffix' => '',
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 0,
      'module' => 'number',
      'settings' => array(),
      'type' => 'number',
      'weight' => 2,
    ),
  );

  // Exported field_instance:
  // 'ting_type-smart_search_string-field_sss_hits_per_year'.
  $field_instances['ting_type-smart_search_string-field_sss_hits_per_year'] = array(
    'bundle' => 'smart_search_string',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'number',
        'settings' => array(
          'decimal_separator' => '.',
          'prefix_suffix' => TRUE,
          'scale' => 0,
          'thousand_separator' => '',
        ),
        'type' => 'number_integer',
        'weight' => 8,
      ),
      'teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'ting_type',
    'field_name' => 'field_sss_hits_per_year',
    'label' => 'Searches - year',
    'required' => 0,
    'settings' => array(
      'max' => '',
      'min' => '',
      'prefix' => '',
      'suffix' => '',
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 0,
      'module' => 'number',
      'settings' => array(),
      'type' => 'number',
      'weight' => 1,
    ),
  );

  // Exported field_instance:
  // 'ting_type-smart_search_string-field_sss_import_update'.
  $field_instances['ting_type-smart_search_string-field_sss_import_update'] = array(
    'bundle' => 'smart_search_string',
    'default_value' => array(
      0 => array(
        'value' => 'locked',
      ),
    ),
    'deleted' => 0,
    'description' => 'Allow this smart search to be updated on import',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'list',
        'settings' => array(),
        'type' => 'list_default',
        'weight' => 12,
      ),
      'teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'ting_type',
    'field_name' => 'field_sss_import_update',
    'label' => 'Import update',
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

  // Exported field_instance: 'ting_type-smart_search_string-field_sss_sort'.
  $field_instances['ting_type-smart_search_string-field_sss_sort'] = array(
    'bundle' => 'smart_search_string',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => 'Forced sort - when chosen, all other settings are overridden',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'list',
        'settings' => array(),
        'type' => 'list_default',
        'weight' => 7,
      ),
      'teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'ting_type',
    'field_name' => 'field_sss_sort',
    'label' => 'Sort',
    'required' => 0,
    'settings' => array(
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'options',
      'settings' => array(),
      'type' => 'options_select',
      'weight' => 9,
    ),
  );

  // Exported field_instance: 'ting_type-smart_search_string-field_status'.
  $field_instances['ting_type-smart_search_string-field_status'] = array(
    'bundle' => 'smart_search_string',
    'default_value' => array(
      0 => array(
        'value' => 'inactive',
      ),
    ),
    'deleted' => 0,
    'description' => 'Sæt dato hvis planlagt',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'list',
        'settings' => array(),
        'type' => 'list_default',
        'weight' => 1,
      ),
      'teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'ting_type',
    'field_name' => 'field_status',
    'label' => 'Status',
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

  // Translatables
  // Included for use with string extractors like potx.
  t('Allow this smart search to be updated on import');
  t('Alternative search string');
  t('Boost values');
  t('Boost værdi');
  t('Date');
  t('Feltnavn');
  t('Forced sort - when chosen, all other settings are overridden');
  t('Import update');
  t('Number of clicks');
  t('Only materials part of the result can be promoted');
  t('Parameter');
  t('Promoted materials');
  t('Search score');
  t('Search string sent to the well');
  t('Searches - 30 days');
  t('Searches - year');
  t('Sort');
  t('Status');
  t('Sæt dato hvis planlagt');

  return $field_instances;
}
