<?php
/**
 * @file
 * openruth.features.inc
 */

/**
 * Implements hook_default_profile2_type().
 */
function openruth_default_profile2_type() {
  $items = array();
  $items['provider_openruth'] = entity_import('profile2_type', '{
    "userCategory" : true,
    "userView" : true,
    "type" : "provider_openruth",
    "label" : "Openruth",
    "weight" : "0",
    "data" : { "registration" : 0 }
  }');
  return $items;
}
