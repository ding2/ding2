<?php
/**
 * @file
 * ding_frontpage.rules_defaults.inc
 */

/**
 * Implements hook_default_rules_configuration().
 */
function ding_frontpage_default_rules_configuration() {
  $items = array();
  $items['rules_rule_scheduler_frontpage_clear'] = entity_import('rules_config', '{ "rules_rule_scheduler_frontpage_clear" : {
      "LABEL" : "rule_scheduler_frontpage_clear",
      "PLUGIN" : "reaction rule",
      "OWNER" : "rules",
      "REQUIRES" : [ "rules", "cache_actions", "scheduler" ],
      "ON" : {
        "scheduler_node_has_been_unpublished_event" : [],
        "scheduler_node_has_been_published_event" : []
      },
      "DO" : [
        { "cache_actions_action_clear_cache_cid" : { "bin" : "cache_page", "cid" : "[site:url]", "wildcard" : 0 } }
      ]
    }
  }');
  return $items;
}
