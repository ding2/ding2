<?php
/**
 * @file
 * connie.features.inc
 */

/**
 * Implements hook_default_profile2_type().
 */
function connie_default_profile2_type() {
  $items = array();
  $items['provider_connie'] = entity_import('profile2_type', '{
    "userCategory" : true,
    "userView" : true,
    "type" : "provider_connie",
    "label" : "Connie",
    "weight" : "0",
    "data" : null
  }');
  return $items;
}
