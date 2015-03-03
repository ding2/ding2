<?php

/**
 * @file
 * Field functions for FBS profiles.
 */

/**
 * Implements hook_field_info().
 *
 * Define our virtual fields.
 */
function fbs_field_info() {
  return array(
    'fbs_name' => array(
      'label' => t('Name from FBS'),
      'description' => t('The user name from the FBS provider'),
      'default_widget' => 'hidden',
      'default_formatter' => 'fbs_default',
      'virtual_field' => array(
        'entity_types' => array('profile2'),
        'add_widget' => TRUE,
      ),
    ),
    'fbs_phone' => array(
      'label' => t('Phone number from FBS'),
      'description' => t('The user phone number from the FBS provider'),
      // These two keys are for compatibility with the text_textfield widget.
      'settings' => array('max_length' => 255),
      'instance_settings' => array('text_processing' => 0),
      'default_widget' => 'textfield',
      'default_formatter' => 'fbs_default',
      'virtual_field' => array(
        'entity_types' => array('profile2'),
        'add_widget' => TRUE,
      ),
    ),
  );
}

/**
 * Implements hook_widget_info_alter().
 *
 * Alter existing widgets to support our fields.
 */
function fbs_field_widget_info_alter(&$info) {
  if (isset($info['text_textfield'])) {
    $info['text_textfield']['field types'][] = 'fbs_phone';
  }
}

/**
 * Implements hook_field_load().
 */
function fbs_field_load($entity_type, $entities, $field, $instances, $langcode, &$items, $age) {
  global $user;
  if ($field['type'] == 'fbs_name') {
    $patron = ding_user_get_creds($user);
    foreach ($entities as $id => $entity) {
      // Only populate when the profile is for the current user.
      if ($entity->uid == $user->uid) {
        $items[$id][0] = array('value' => $patron['name']);
      }
    }
  }
}

/**
 * Implements hook_field_is_empty().
 */
function fbs_field_is_empty($item, $field) {
  if (empty($item['value']) && (string) $item['value'] !== '0') {
    return TRUE;
  }
  return FALSE;
}

/**
 * Implements hook_field_formatter_info().
 */
function fbs_field_formatter_info() {
  return array(
    'fbs_default' => array(
      'label' => t('Default'),
      'field types' => array(
        'fbs_name',
      ),
    ),
  );
}

/**
 * Implements hook_field_formatter_view().
 */
function fbs_field_formatter_view($entity_type, $entity, $field, $instance, $langcode, $items, $display) {
  $element = array();
  foreach ($items as $delta => $item) {
    switch ($display['type']) {
      case 'fbs_default':
        $element[$delta] = array(
          '#markup' => check_plain($item['value']),
        );
    }
  }

  return $element;
}
