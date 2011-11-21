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
        { "cache_actions_action_clear_cache" : { "tables" : { "value" : {
                "cache" : "cache",
                "cache_block" : "cache_block",
                "cache_page" : "cache_page",
                "cache_similarterms" : "cache_similarterms",
                "cache_token" : "cache_token",
                "cache_views" : "cache_views"
              }
            }
          }
        }
      ]
    }
  }');
  return $items;
}
