<?php
/**
 * @file
 * ding_example_content_news.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function ding_example_content_news_ctools_plugin_api() {
  list($module, $api) = func_get_args();
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}
