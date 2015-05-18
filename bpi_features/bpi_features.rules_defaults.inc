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
  $items['rules_after_updating_entity'] = entity_import('rules_config', '{ "rules_after_updating_entity" : {
      "LABEL" : "Before changing workflow to Sent to BPI",
      "PLUGIN" : "reaction rule",
      "OWNER" : "rules",
      "REQUIRES" : [ "rules", "bpi" ],
      "ON" : { "node_presave--ding_news" : { "bundle" : "ding_news" } },
      "IF" : [
        { "data_is" : { "data" : [ "node:field-bpi-workflow" ], "value" : "8" } }
      ],
      "DO" : [ { "bpi_rules_push" : { "entity" : [ "node" ] } } ]
    }
  }');
  $items['rules_before_changing_workflow_to_delete_from_bpi'] = entity_import('rules_config', '{ "rules_before_changing_workflow_to_delete_from_bpi" : {
      "LABEL" : "Before changing workflow to Delete from BPI",
      "PLUGIN" : "reaction rule",
      "OWNER" : "rules",
      "REQUIRES" : [ "rules", "bpi" ],
      "ON" : { "node_presave--ding_news" : { "bundle" : "ding_news" } },
      "IF" : [
        { "data_is" : { "data" : [ "node:field-bpi-workflow" ], "value" : "12" } }
      ],
      "DO" : [ { "bpi_rules_delete" : { "entity" : [ "node" ] } } ]
    }
  }');
  return $items;
}
