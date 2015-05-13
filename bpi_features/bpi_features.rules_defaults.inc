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
  return $items;
}
