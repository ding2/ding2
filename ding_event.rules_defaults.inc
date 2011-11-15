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
        { "cache_actions_action_clear_panels_pane_cache" : { "panes" : { "value" : {
                "subtask:page_ding_frontpage_panel_context:page:ding_frontpage:new-2" : "subtask:page_ding_frontpage_panel_context:page:ding_frontpage:new-2",
                "subtask:page_ding_events_panel_context:page:ding_events:new-3" : "subtask:page_ding_events_panel_context:page:ding_events:new-3",
                "subtask:page_ding_events_library_panel_context:page:ding_events_library:new-2" : "subtask:page_ding_events_library_panel_context:page:ding_events_library:new-2"
              }
            }
          }
        }
      ]
    }
  }');
  return $items;
}
