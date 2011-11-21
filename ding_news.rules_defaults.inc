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
        { "cache_actions_action_clear_panels_pane_cache" : { "panes" : { "value" : {
                "task:term_view_panel_context:term_view:new-2" : "task:term_view_panel_context:term_view:new-2",
                "subtask:page_ding_news_panel_context:page:ding_news:new-2" : "subtask:page_ding_news_panel_context:page:ding_news:new-2",
                "subtask:page_ding_frontpage_panel_context:page:ding_frontpage:new-1" : "subtask:page_ding_frontpage_panel_context:page:ding_frontpage:new-1",
                "subtask:page_ding_news_library_panel_context:page:ding_news_library:new-1" : "subtask:page_ding_news_library_panel_context:page:ding_news_library:new-1",
                "task:node_view_panel_context:node_view:new-2" : "task:node_view_panel_context:node_view:new-2",
                "task:node_view_panel_context_3:node_view:new-2" : "task:node_view_panel_context_3:node_view:new-2"
              }
            }
          }
        }
      ]
    }
  }');
  return $items;
}
