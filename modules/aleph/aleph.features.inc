<?php
/**
 * @file
 * aleph.features.inc
 */

/**
 * Implements hook_default_profile2_type().
 */
function aleph_default_profile2_type() {
  $items = array();
  $items['provider_aleph'] = entity_import('profile2_type', '{
    "userCategory" : true,
    "userView" : true,
    "type" : "provider_aleph",
    "label" : "Profile for Aleph",
    "weight" : "0",
    "data" : { "registration" : 0 }
  }');
  return $items;
}
