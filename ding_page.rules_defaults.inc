<?php
/**
 * @file
 * ding_page.rules_defaults.inc
 */

/**
 * Implements hook_default_rules_configuration().
 */
function ding_page_default_rules_configuration() {
  $items = array();
  $items['rules_ding_page_node_update'] = entity_import('rules_config', '{ "rules_ding_page_node_update" : {
      "LABEL" : "Ding page node update",
      "PLUGIN" : "reaction rule",
      "REQUIRES" : [ "rules", "cache_actions" ],
      "ON" : [ "node_update", "node_delete", "node_insert" ],
      "IF" : [
        { "node_is_of_type" : {
            "node" : [ "node" ],
            "type" : { "value" : { "ding_page" : "ding_page" } }
          }
        }
      ],
      "DO" : [
        { "cache_actions_action_clear_panels_pane_cache" : { "panes" : { "value" : { "task:node_view_panel_context_4:node_view:new-2" : "task:node_view_panel_context_4:node_view:new-2" } } } }
      ]
    }
  }');
  return $items;
}
