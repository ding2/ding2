<?php
/**
 * @file
 * ding_campaign_plus.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function ding_campaign_plus_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "field_group" && $api == "field_group") {
    return array("version" => "1");
  }
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_node_info().
 */
function ding_campaign_plus_node_info() {
  $items = array(
    'ding_campaign_plus' => array(
      'name' => t('Campaign Plus'),
      'base' => 'node_content',
      'description' => t('Creation of campaigns based on selection rules and user interaction'),
      'has_title' => '1',
      'title_label' => t('Titel'),
      'help' => '',
    ),
  );
  drupal_alter('node_info', $items);
  return $items;
}
