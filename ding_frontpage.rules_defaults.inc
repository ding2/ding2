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
  $items['rules_ding_frontpage_content_created'] = entity_import('rules_config', '{ "rules_ding_frontpage_content_created" : {
      "LABEL" : "Front page content updates",
      "PLUGIN" : "reaction rule",
      "TAGS" : [ "ding_frontpage" ],
      "REQUIRES" : [ "rules", "cache_actions" ],
      "ON" : [ "node_insert", "node_delete", "node_update" ],
      "IF" : [
        { "OR" : [
            { "node_is_of_type" : {
                "node" : [ "node" ],
                "type" : { "value" : { "campaign" : "campaign" } }
              }
            },
            { "AND" : [
                { "node_is_of_type" : {
                    "node" : [ "node" ],
                    "type" : { "value" : { "ding_news" : "ding_news" } }
                  }
                },
                { "node_is_promoted" : { "node" : [ "node" ] } }
              ]
            },
            { "AND" : [
                { "node_is_of_type" : {
                    "node" : [ "node" ],
                    "type" : { "value" : { "ding_event" : "ding_event" } }
                  }
                },
                { "node_is_promoted" : { "node" : [ "node" ] } }
              ]
            }
          ]
        }
      ],
      "DO" : [
        { "cache_actions_action_clear_panels_pane_cache" : { "panes" : { "value" : { "subtask:page_ding_frontpage_panel_context:page:ding_frontpage:new-1" : "subtask:page_ding_frontpage_panel_context:page:ding_frontpage:new-1" } } } },
        { "cache_actions_action_clear_panels_pane_cache" : { "panes" : { "value" : { "subtask:page_ding_frontpage_panel_context:page:ding_frontpage:new-2" : "subtask:page_ding_frontpage_panel_context:page:ding_frontpage:new-2" } } } },
        { "cache_actions_action_clear_panels_pane_cache" : { "panes" : { "value" : { "subtask:page_ding_frontpage_panel_context:page:ding_frontpage:new-3" : "subtask:page_ding_frontpage_panel_context:page:ding_frontpage:new-3" } } } }
      ]
    }
  }');
  return $items;
}
