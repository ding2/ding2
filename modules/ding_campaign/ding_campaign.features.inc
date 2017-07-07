<?php
/**
 * @file
 * ding_campaign.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function ding_campaign_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_node_info().
 */
function ding_campaign_node_info() {
  $items = array(
    'ding_campaign' => array(
      'name' => t('Campaign'),
      'base' => 'node_content',
      'description' => t('Create a new campaign that based on different rules will be shown in a given context on the site.'),
      'has_title' => '1',
      'title_label' => t('Campaign name'),
      'help' => '',
    ),
  );
  return $items;
}
