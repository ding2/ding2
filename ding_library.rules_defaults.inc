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
        { "cache_actions_action_clear_views_cache" : { "view" : { "value" : { "ding_library" : "ding_library" } } } },
        { "cache_actions_action_clear_panels_pane_cache" : { "panes" : { "value" : {
                "task:node_view_panel_context_3:node_view:new-1" : "task:node_view_panel_context_3:node_view:new-1",
                "task:node_view_panel_context_3:node_view:new-4" : "task:node_view_panel_context_3:node_view:new-4",
                "task:node_view_panel_context_3:node_view:new-5" : "task:node_view_panel_context_3:node_view:new-5",
                "subtask:page_ding_libraries_panel_context:page:ding_libraries:new-1" : "subtask:page_ding_libraries_panel_context:page:ding_libraries:new-1",
                "subtask:page_ding_libraries_panel_context:page:ding_libraries:new-2" : "subtask:page_ding_libraries_panel_context:page:ding_libraries:new-2",
                "subtask:page_ding_library_about_panel_context:page:ding_library_about:new-1" : "subtask:page_ding_library_about_panel_context:page:ding_library_about:new-1",
                "subtask:page_ding_library_about_panel_context:page:ding_library_about:new-2" : "subtask:page_ding_library_about_panel_context:page:ding_library_about:new-2",
                "subtask:page_ding_library_about_panel_context:page:ding_library_about:new-3" : "subtask:page_ding_library_about_panel_context:page:ding_library_about:new-3",
                "subtask:page_ding_library_about_panel_context:page:ding_library_about:new-4" : "subtask:page_ding_library_about_panel_context:page:ding_library_about:new-4",
                "subtask:page_ding_library_about_panel_context:page:ding_library_about:new-5" : "subtask:page_ding_library_about_panel_context:page:ding_library_about:new-5"
              }
            }
          }
        }
      ]
    }
  }');
  return $items;
}
