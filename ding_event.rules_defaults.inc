<?php
/**
 * @file
 * ding_event.rules_defaults.inc
 */

/**
 * Implements hook_default_rules_configuration().
 */
function ding_event_default_rules_configuration() {
  $items = array();
  $items['rules_ding_event_comment_update'] = entity_import('rules_config', '{ "rules_ding_event_comment_update" : {
      "LABEL" : "Ding event comment update",
      "PLUGIN" : "reaction rule",
      "TAGS" : [ "ding_event" ],
      "REQUIRES" : [ "rules", "cache_actions", "comment" ],
      "ON" : [ "comment_delete", "comment_update", "comment_insert" ],
      "IF" : [
        { "node_is_of_type" : {
            "node" : [ "comment:node" ],
            "type" : { "value" : { "ding_event" : "ding_event" } }
          }
        }
      ],
      "DO" : [
        { "cache_actions_action_clear_views_cache" : { "view" : { "value" : { "ding_event" : "ding_event" } } } }
      ]
    }
  }');
  $items['rules_ding_event_node_update'] = entity_import('rules_config', '{ "rules_ding_event_node_update" : {
      "LABEL" : "Ding event node update",
      "PLUGIN" : "reaction rule",
      "TAGS" : [ "ding_event" ],
      "REQUIRES" : [ "rules", "cache_actions" ],
      "ON" : [ "node_insert", "node_update", "node_delete" ],
      "IF" : [
        { "node_is_of_type" : {
            "node" : [ "node" ],
            "type" : { "value" : { "ding_event" : "ding_event" } }
          }
        }
      ],
      "DO" : [
        { "cache_actions_action_clear_views_cache" : { "view" : { "value" : { "ding_event" : "ding_event" } } } }
      ]
    }
  }');
  return $items;
}
