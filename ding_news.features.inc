<?php
/**
 * @file
 * ding_news.features.inc
 */

/**
 * Implementation of hook_ctools_plugin_api().
 */
function ding_news_ctools_plugin_api() {
  list($module, $api) = func_get_args();
  if ($module == "page_manager" && $api == "pages_default") {
    return array("version" => "1");
  }
  list($module, $api) = func_get_args();
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implementation of hook_views_api().
 */
function ding_news_views_api() {
  list($module, $api) = func_get_args();
  if ($module == "views" && $api == "views_default") {
    return array("version" => "3.0");
  }
}

/**
 * Implementation of hook_node_info().
 */
function ding_news_node_info() {
  $items = array(
    'ding_news' => array(
      'name' => t('News'),
      'base' => 'node_content',
      'description' => t('A content type for news concerning libraries.'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
  );
  return $items;
}
