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
  $items['rules_ding_news_comment_update'] = entity_import('rules_config', '{ "rules_ding_news_comment_update" : {
      "LABEL" : "Ding news comment update",
      "PLUGIN" : "reaction rule",
      "TAGS" : [ "Ding news" ],
      "REQUIRES" : [ "rules", "comment" ],
      "ON" : [ "comment_delete", "comment_update", "comment_insert" ],
      "IF" : [
        { "node_is_of_type" : {
            "node" : [ "comment:node" ],
            "type" : { "value" : { "ding_news" : "ding_news" } }
          }
        }
      ],
      "DO" : []
    }
  }');
  $items['rules_ding_news_node_update'] = entity_import('rules_config', '{ "rules_ding_news_node_update" : {
      "LABEL" : "Ding news node update",
      "PLUGIN" : "reaction rule",
      "TAGS" : [ "ding_news" ],
      "REQUIRES" : [ "rules" ],
      "ON" : [ "node_insert", "node_update", "node_delete" ],
      "IF" : [
        { "node_is_of_type" : {
            "node" : [ "node" ],
            "type" : { "value" : { "ding_news" : "ding_news" } }
          }
        }
      ],
      "DO" : []
    }
  }');
  return $items;
}
