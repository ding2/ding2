<?php
/**
 * @file
 * ding_campaign_ctype.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function ding_campaign_ctype_ctools_plugin_api() {
  list($module, $api) = func_get_args();
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_node_info().
 */
function ding_campaign_ctype_node_info() {
  $items = array(
    'ding_campaign' => array(
      'name' => t('Campaign'),
      'base' => 'node_content',
      'description' => '',
      'has_title' => '1',
      'title_label' => t('Campaign name'),
      'help' => '',
    ),
  );
  return $items;
}
