<?php
/**
 * @file
 * ding_library.rules_defaults.inc
 */

/**
 * Implements hook_default_rules_configuration().
 */
function ding_library_default_rules_configuration() {
  $items = array();
  $items['rules_ding_library_node_update'] = entity_import('rules_config', '{ "rules_ding_library_node_update" : {
      "LABEL" : "Ding library node update",
      "PLUGIN" : "reaction rule",
      "TAGS" : [ "ding_library" ],
      "REQUIRES" : [ "rules", "cache_actions" ],
      "ON" : [ "node_insert", "node_update", "node_delete" ],
      "IF" : [
        { "node_is_of_type" : {
            "node" : [ "node" ],
            "type" : { "value" : { "ding_library" : "ding_library" } }
          }
        }
      ],
      "DO" : [
        { "cache_actions_action_clear_views_cache" : { "view" : { "value" : { "ding_library" : "ding_library" } } } }
      ]
    }
  }');
  return $items;
}
