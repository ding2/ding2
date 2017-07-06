<?php

/**
 * @file
 * ding_interaction_manual.features.inc
 */

/**
 * Implements hook_eck_bundle_info().
 */
function ding_interaction_manual_eck_bundle_info() {
  $items = array(
    'ding_type_ding_interaction' => array(
      'machine_name' => 'ding_type_ding_interaction',
      'entity_type' => 'ding_type',
      'name' => 'ding_interaction',
      'label' => 'Ding Interaction',
      'config' => array(),
    ),
  );
  return $items;
}
