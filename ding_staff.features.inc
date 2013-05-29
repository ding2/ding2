<?php
/**
 * @file
 * ding_staff.features.inc
 */

/**
 * Implements hook_default_profile2_type().
 */
function ding_staff_default_profile2_type() {
  $items = array();
  $items['staff'] = entity_import('profile2_type', '{
    "userCategory" : true,
    "userView" : true,
    "type" : "staff",
    "label" : "Staff",
    "weight" : "0",
    "data" : { "registration" : 0 }
  }');
  return $items;
}
