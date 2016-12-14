<?php
/**
 * @file
 * ding_user_consent.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function ding_user_consent_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}
