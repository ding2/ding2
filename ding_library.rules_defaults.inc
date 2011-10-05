<?php
/**
 * @file
 * ding_library.rules_defaults.inc
 */

/**
 * Implementation of hook_default_rules_configuration().
 */
function ding_library_default_rules_configuration() {
  $items = array();
  $items['rules_ding_library_front_page_content_updates'] = entity_import('rules_config', '{ "rules_ding_library_front_page_content_updates" : {
      "LABEL" : "Library front page content updates",
      "PLUGIN" : "reaction rule",
      "TAGS" : [ "ding_library" ],
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
        { "cache_actions_action_clear_panels_pane_cache" : { "panes" : { "value" : {
                "task:node_view_panel_context_3:node_view:new-2" : "task:node_view_panel_context_3:node_view:new-2",
                "task:node_view_panel_context_3:node_view:new-3" : "task:node_view_panel_context_3:node_view:new-3",
                "task:node_view_panel_context_3:node_view:new-4" : "task:node_view_panel_context_3:node_view:new-4"
              }
            }
          }
        }
      ]
    }
  }');
  $items['rules_ding_library_list_content_changed'] = entity_import('rules_config', '{ "rules_ding_library_list_content_changed" : {
      "LABEL" : "Library list content changed",
      "PLUGIN" : "reaction rule",
      "TAGS" : [ "ding_library" ],
      "REQUIRES" : [ "rules", "cache_actions" ],
      "ON" : [ "node_insert", "node_delete", "node_update" ],
      "IF" : [
        { "node_is_of_type" : {
            "node" : [ "node" ],
            "type" : { "value" : { "ding_library" : "ding_library" } }
          }
        }
      ],
      "DO" : [
        { "cache_actions_action_clear_panels_pane_cache" : { "panes" : { "value" : { "subtask:page_ding_libraries_panel_context:page:ding_libraries:new-1" : "subtask:page_ding_libraries_panel_context:page:ding_libraries:new-1" } } } }
      ]
    }
  }');
  return $items;
}
