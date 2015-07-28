<?php
/**
 * @file
 * bpi_features.rules_defaults.inc
 */

/**
 * Implements hook_default_rules_configuration().
 */
function bpi_features_default_rules_configuration() {
  $items = array();
  $items['rules_after_workflow_sent_to_bpi'] = entity_import('rules_config', '{ "rules_after_workflow_sent_to_bpi" : {
      "LABEL" : "After workflow is set to \\u0027Sent to BPI\\u0027",
      "PLUGIN" : "reaction rule",
      "OWNER" : "rules",
      "REQUIRES" : [ "rules" ],
      "ON" : { "node_update--ding_news" : { "bundle" : "ding_news" } },
      "IF" : [
        { "data_is" : { "data" : [ "node:field-bpi-workflow" ], "value" : "4" } }
      ],
      "DO" : [ { "bpi_rules_push" : { "entity" : [ "node" ] } } ]
    }
  }');
  $items['rules_before_changing_workflow_to_delete_from_bpi'] = entity_import('rules_config', '{ "rules_before_changing_workflow_to_delete_from_bpi" : {
      "LABEL" : "Before changing workflow to Delete from BPI",
      "PLUGIN" : "reaction rule",
      "OWNER" : "rules",
      "REQUIRES" : [ "rules" ],
      "ON" : { "node_update--ding_news" : { "bundle" : "ding_news" } },
      "IF" : [
        { "data_is" : { "data" : [ "node:field-bpi-workflow" ], "value" : "7" } }
      ],
      "DO" : [ { "bpi_rules_delete" : { "entity" : [ "node" ] } } ]
    }
  }');
  $items['rules_new_content_with_save_and_push_'] = entity_import('rules_config', '{ "rules_new_content_with_save_and_push_" : {
      "LABEL" : "New content with \\u0027Save and push\\u0027",
      "PLUGIN" : "reaction rule",
      "OWNER" : "rules",
      "REQUIRES" : [ "rules" ],
      "ON" : { "node_insert--ding_news" : { "bundle" : "ding_news" } },
      "IF" : [
        { "data_is" : { "data" : [ "node:field-bpi-workflow" ], "value" : "3" } }
      ],
      "DO" : [ { "redirect" : { "url" : "node\\/[node:nid]\\/workflow" } } ]
    }
  }');
  return $items;
}
