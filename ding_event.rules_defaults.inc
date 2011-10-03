<?php
/**
 * @file
 * ding_event.rules_defaults.inc
 */

/**
 * Implementation of hook_default_rules_configuration().
 */
function ding_event_default_rules_configuration() {
  $items = array();
  $items['rules_event_category_content_update'] = entity_import('rules_config', '{ "rules_event_category_content_update" : {
      "LABEL" : "Event category content update",
      "PLUGIN" : "reaction rule",
      "TAGS" : [ "ding_event" ],
      "REQUIRES" : [ "rules", "cache_actions" ],
      "ON" : [ "node_insert", "node_delete", "node_update" ],
      "IF" : [
        { "node_is_of_type" : {
            "node" : [ "node" ],
            "type" : { "value" : { "ding_event" : "ding_event" } }
          }
        }
      ],
      "DO" : [
        { "cache_actions_action_clear_panels_pane_cache" : { "panes" : { "value" : {
                "subtask:page_ding_events_panel_context:page:ding_events:new-2" : "subtask:page_ding_events_panel_context:page:ding_events:new-2",
                "subtask:page_ding_events_library_panel_context:page:ding_events_library:new-1" : "subtask:page_ding_events_library_panel_context:page:ding_events_library:new-1",
                "task:term_view_panel_context_2:term_view:new-2" : "task:term_view_panel_context_2:term_view:new-2"
              }
            }
          }
        }
      ]
    }
  }');
  return $items;
}
