<?php
/**
 * @file
 * ding_staff.rules_defaults.inc
 */

/**
 * Implements hook_default_rules_configuration().
 */
function ding_staff_default_rules_configuration() {
  $items = array();
  $items['rules_role_staff_assign'] = entity_import('rules_config', '{ "rules_role_staff_assign" : {
      "LABEL" : "assign staff role",
      "PLUGIN" : "reaction rule",
      "TAGS" : [ "ding_staff" ],
      "REQUIRES" : [ "rules", "profile2" ],
      "ON" : [ "profile2_insert" ],
      "IF" : [
        { "data_is" : { "data" : [ "profile2:type:type" ], "value" : "ding_staff_profile" } }
      ],
      "DO" : [
        { "user_add_role" : { "account" : [ "profile2:user" ], "roles" : { "value" : { "8" : "8" } } } }
      ]
    }
  }');
  $items['rules_role_staff_remove'] = entity_import('rules_config', '{ "rules_role_staff_remove" : {
      "LABEL" : "remove staff role",
      "PLUGIN" : "reaction rule",
      "TAGS" : [ "ding_staff" ],
      "REQUIRES" : [ "rules", "profile2" ],
      "ON" : [ "profile2_delete" ],
      "IF" : [
        { "data_is" : { "data" : [ "profile2:type:type" ], "value" : "ding_staff_profile" } }
      ],
      "DO" : [
        { "user_remove_role" : { "account" : [ "profile2:user" ], "roles" : { "value" : { "8" : "8" } } } }
      ]
    }
  }');
  return $items;
}
