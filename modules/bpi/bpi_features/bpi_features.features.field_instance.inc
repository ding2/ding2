<?php
/**
 * @file
 * bpi_features.features.field_instance.inc
 */

/**
 * Implements hook_field_default_field_instances().
 */
function bpi_features_field_default_field_instances() {
  $field_instances = array();

  // Exported field_instance: 'node-ding_news-field_bpi_workflow'
  $field_instances['node-ding_news-field_bpi_workflow'] = array(
    'bundle' => 'ding_news',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 9,
      ),
      'search_result' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
      'teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
      'teaser_highlight' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'node',
    'field_name' => 'field_bpi_workflow',
    'label' => 'BPI workflow',
    'required' => 1,
    'settings' => array(
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'workflowfield',
      'settings' => array(
        'comment' => 1,
        'name_as_title' => 1,
      ),
      'type' => 'workflow_default',
      'weight' => 35,
    ),
  );

  // Translatables
  // Included for use with string extractors like potx.
  t('BPI workflow');

  return $field_instances;
}
