<?php
/**
 * @file
 * ding_interaction.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function ding_interaction_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}
