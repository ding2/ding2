<?php
/**
 * @file
 * connie.features.field_instance.inc
 */

/**
 * Implements hook_field_default_field_instances().
 */
function connie_field_default_field_instances() {
  $field_instances = array();

  // Exported field_instance: 'profile2-provider_connie-connie_preferred_branch'
  $field_instances['profile2-provider_connie-connie_preferred_branch'] = array(
    'bundle' => 'provider_connie',
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
    ),
    'entity_type' => 'profile2',
    'field_name' => 'connie_preferred_branch',
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
      'weight' => 0,
    ),
  );

  // Translatables
  // Included for use with string extractors like potx.
  t('Preferred branch');

  return $field_instances;
}
