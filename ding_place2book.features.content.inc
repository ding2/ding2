<?php

/**
 * Implementation of hook_content_default_fields().
 */
function ding_place2book_content_default_fields() {
  $fields = array();

  // Exported field: field_place2book_id
  $fields['event-field_place2book_id'] = array(
    'field_name' => 'field_place2book_id',
    'type_name' => 'event',
    'display_settings' => array(
      'weight' => '32',
      'parent' => 'group_place2book',
      'label' => array(
        'format' => 'hidden',
      ),
      'teaser' => array(
        'format' => 'hidden',
        'exclude' => 0,
      ),
      'full' => array(
        'format' => 'hidden',
        'exclude' => 0,
      ),
      '4' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      '2' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      '3' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      'token' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
    ),
    'widget_active' => '1',
    'type' => 'number_integer',
    'required' => '0',
    'multiple' => '0',
    'module' => 'number',
    'active' => '1',
    'prefix' => '',
    'suffix' => '',
    'min' => '',
    'max' => '',
    'allowed_values' => '',
    'allowed_values_php' => '',
    'widget' => array(
      'default_value' => array(
        '0' => array(
          'value' => '',
          '_error_element' => 'default_value_widget][field_place2book_id][0][value',
        ),
      ),
      'default_value_php' => NULL,
      'label' => 'Place2Book ID',
      'weight' => '32',
      'description' => 'An ID-reference to the corresponding event on the ticket booking service Place2Book',
      'type' => 'number',
      'module' => 'number',
    ),
  );

  // Exported field: field_place2book_maintain
  $fields['event-field_place2book_maintain'] = array(
    'field_name' => 'field_place2book_maintain',
    'type_name' => 'event',
    'display_settings' => array(
      'weight' => '31',
      'parent' => 'group_place2book',
      'label' => array(
        'format' => 'hidden',
      ),
      'teaser' => array(
        'format' => 'hidden',
        'exclude' => 0,
      ),
      'full' => array(
        'format' => 'hidden',
        'exclude' => 0,
      ),
      '4' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      '2' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      '3' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      'token' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
    ),
    'widget_active' => '1',
    'type' => 'number_integer',
    'required' => '0',
    'multiple' => '0',
    'module' => 'number',
    'active' => '1',
    'prefix' => '',
    'suffix' => '',
    'min' => '',
    'max' => '',
    'allowed_values' => '0|Maintain copy on Place2Book
1|Maintain copy on Place2Book',
    'allowed_values_php' => '',
    'widget' => array(
      'default_value' => array(
        '0' => array(
          'value' => 1,
        ),
      ),
      'default_value_php' => NULL,
      'label' => 'Maintain copy on Place2Book',
      'weight' => '31',
      'description' => 'When set, a corresponding event is created and updated on the ticket booking service Place2Book.com. ',
      'type' => 'optionwidgets_onoff',
      'module' => 'optionwidgets',
    ),
  );

  // Exported field: field_place2book_use_taxonomy
  $fields['event-field_place2book_use_taxonomy'] = array(
    'field_name' => 'field_place2book_use_taxonomy',
    'type_name' => 'event',
    'display_settings' => array(
      'weight' => '33',
      'parent' => 'group_place2book',
      'label' => array(
        'format' => 'hidden',
      ),
      'teaser' => array(
        'format' => 'hidden',
        'exclude' => 0,
      ),
      'full' => array(
        'format' => 'hidden',
        'exclude' => 0,
      ),
      '4' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      '2' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      '3' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      'token' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
    ),
    'widget_active' => '1',
    'type' => 'number_integer',
    'required' => '0',
    'multiple' => '0',
    'module' => 'number',
    'active' => '1',
    'prefix' => '',
    'suffix' => '',
    'min' => '',
    'max' => '',
    'allowed_values' => '0|Categories to Place2Book
1|Categories to Place2Book',
    'allowed_values_php' => '',
    'widget' => array(
      'default_value' => array(
        '0' => array(
          'value' => NULL,
        ),
      ),
      'default_value_php' => NULL,
      'label' => 'Categories to Place2Book',
      'weight' => '33',
      'description' => 'If checked, categories/taxonomy terms on this ding-event is sent to the corresponding event maintained on place2book.com ',
      'type' => 'optionwidgets_onoff',
      'module' => 'optionwidgets',
    ),
  );

  // Translatables
  // Included for use with string extractors like potx.
  t('Categories to Place2Book');
  t('Maintain copy on Place2Book');
  t('Place2Book ID');

  return $fields;
}
