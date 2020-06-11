<?php

/**
 * @file
 * Field hook implementations.
 */

/**
 * Implements hook_field_info().
 */
function ting_field_search_field_info() {
  return array(
    'ting_field_search_profile_page_placement' => array(
      'label' => t('Ting field search: Profile page placement'),
      'description' => t('Used to place search guide on a Ting field search profile page.'),
      'default_widget' => 'ting_field_search_profile_page_placement_default',
      'default_formatter' => 'hidden',
      'property_type' => 'ting_field_search',
      'property_callbacks' => array('ting_field_search_property_info_callback'),
    ),
  );
}

/**
 * Implements hook_field_is_empty().
 */
function ting_field_search_field_is_empty($item, $field) {
  return empty($item['profile_name']);
}

/**
 * Implements hook_field_widget_info().
 */
function ting_field_search_field_widget_info() {
  return array(
    'ting_field_search_profile_page_placement_default' => array(
      'label' => t('Profile page placement: Default'),
      'field types' => array('ting_field_search_profile_page_placement'),
      'behaviors' => array(
        'mutliple values' => FIELD_BEHAVIOR_DEFAULT,
        'default value' => FIELD_BEHAVIOR_DEFAULT,
      ),
    ),
  );
}

/**
 * Implements hook_field_widget_form().
 */
function ting_field_search_field_widget_form(&$form, &$form_state, $field, $instance, $langcode, $items, $delta, $element) {
  $values = isset($items[$delta]) ? $items[$delta] : FALSE;

  $profile_options = array();
  foreach (ting_field_search_profiles_load_all() as $name => $profile) {
    $profile_options[$name] = check_plain($profile->title);
  }

  switch ($instance['widget']['type']) {
    case 'ting_field_search_profile_page_placement_default':
      $element['profile_name'] = array(
        '#type' => 'select',
        '#title' => t('Profile'),
        '#description' => t('Select a profile which should display the search guide.'),
        '#options' => $profile_options,
        '#required' => FALSE,
        '#empty_value' => '',
        '#default_value' => !empty($values['profile_name'] ) ? $values['profile_name'] : '',
      );
      $element['position'] = array(
        '#type' => 'select',
        '#title' => t('Position'),
        '#description' => t('Select the position of the search guide on the proile page.'),
        '#options' => array(
          'sidebar' => t('Sidebar'),
          'bottomleft' => t('Bottom left'),
          'bottomright' => t('Bottom right'),
        ),
        '#default_value' => !empty($values['position'] ) ? $values['position'] : 'sidebar',
      );
      $element['weight'] = array(
        '#type' => 'select',
        '#title' => t('Weight'),
        '#description' => t('Determines the horizontal position of the search guide.'),
        '#options' => drupal_map_assoc(range(-15, 15)),
        '#default_value' => $values['weight'],
      );
      break;
  }

  $path = drupal_get_path('module', 'ting_field_search');
  $element['#attached']['css'][] = $path . '/css/ting_field_search.admin.css';

  return $element;
}

/**
 * Property info callback to provide metadata for the Entity API.
 */
function ting_field_search_property_info_callback(&$info, $entity_type, $field, $instance, $field_type) {
  $property = &$info[$entity_type]['bundles'][$instance['bundle']]['properties'][$field['field_name']];

  // As recommended in Entity API documentation.
  // See: https://www.drupal.org/docs/7/api/entity-api/property-info-for-fields
  $property['getter callback'] = 'entity_metadata_field_verbatim_get';
  $property['setter callback'] = 'entity_metadata_field_verbatim_set';
  unset($property['query callback']);

  // Define the data structure of our field.
  $property['property info']['profile_name'] = array(
    'type' => 'text',
    'label' => t('Profile machine-name'),
    'setter callback' => 'entity_property_verbatim_set',
    'required' => TRUE,
  );
  $property['property info']['position'] = array(
    'type' => 'text',
    'label' => t('Position'),
    'setter callback' => 'entity_property_verbatim_set',
    'required' => TRUE,
  );
  $property['property info']['weight'] = array(
    'type' => 'integer',
    'label' => t('Weight'),
    'setter callback' => 'entity_property_verbatim_set',
    'required' => TRUE,
  );
}
