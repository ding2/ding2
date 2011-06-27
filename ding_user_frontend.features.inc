<?php
/**
 * @file
 * ding_user_frontend.features.inc
 */

/**
 * Implementation of hook_ctools_plugin_api().
 */
function ding_user_frontend_ctools_plugin_api() {
  list($module, $api) = func_get_args();
  if ($module == "page_manager" && $api == "pages_default") {
    return array("version" => 1);
  }
}

function ding_user_frontend_preprocess_page(&$variables) {
  // unset tabs in pages with panels that also has tabs.
  if ( in_array('page__user__status',$variables['theme_hook_suggestions']) ) {
    unset($variables['tabs']['#primary']);
    unset($variables['tabs']['#secondary']);
  }
}

