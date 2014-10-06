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
      "OWNER" : "rules",
      "TAGS" : [ "ding_staff" ],
      "REQUIRES" : [ "rules", "ding_staff", "profile2" ],
      "ON" : { "profile2_insert" : [] },
      "IF" : [
        { "data_is" : { "data" : [ "profile2:type:type" ], "value" : "ding_staff_profile" } }
      ],
      "DO" : [
        { "ding_staff_add_role_staff" : { "profile_user" : [ "profile2:user" ] } }
      ]
    }
  }');
  return $items;
}
