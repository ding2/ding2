<?php
/**
 * @file
 * alma.features.inc
 */

/**
 * Implements hook_default_profile2_type().
 */
function alma_default_profile2_type() {
  $items = array();
  $items['provider_alma'] = entity_import('profile2_type', '{
    "userCategory" : false,
    "userView" : false,
    "type" : "provider_alma",
    "label" : "Alma",
    "weight" : "0",
    "data" : { "registration" : 0 }
  }');

  return $items;
}
