<?php
/**
 * @file
 * ding_news.rules_defaults.inc
 */

/**
 * Implements hook_default_rules_configuration().
 */
function ding_news_default_rules_configuration() {
  $items = array();
  $items['rules_ding_news_node_update'] = entity_import('rules_config', '{ "rules_ding_news_node_update" : {
      "LABEL" : "Ding news node update",
      "PLUGIN" : "reaction rule",
      "TAGS" : [ "ding_news" ],
      "REQUIRES" : [ "rules", "cache_actions" ],
      "ON" : [ "node_insert", "node_update", "node_delete" ],
      "IF" : [
        { "node_is_of_type" : {
            "node" : [ "node" ],
            "type" : { "value" : { "ding_news" : "ding_news" } }
          }
        }
      ],
      "DO" : [
        { "cache_actions_action_clear_views_cache" : { "view" : { "value" : { "ding_news" : "ding_news" } } } }
      ]
    }
  }');
  return $items;
}
