<?php

/**
 * @file
 * ding_message_p2_installer.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function ding_message_p2_installer_ctools_plugin_api() {
  list($module, $api) = func_get_args();
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_default_message_type().
 */
function ding_message_p2_installer_default_message_type() {
  $items = array();
  $items['new_content'] = entity_import('message_type', '{
    "name" : "new_content",
    "description" : "New content",
    "argument_keys" : [],
    "argument" : [],
    "category" : "message_type",
    "data" : {
      "token options" : { "clear" : 0 },
      "purge" : { "override" : 0, "enabled" : 0, "quota" : "", "days" : "" }
    },
    "language" : "da",
    "arguments" : null,
    "message_text" : { "da" : [
        {
          "value" : "\\u003Cp\\u003ESome of the elements you are following has new updates\\u003C\\/p\\u003E",
          "format" : "ding_wysiwyg",
          "safe_value" : "\\u003Cp\\u003ESome of the elements you are following has new updates\\u003C\\/p\\u003E\\n"
        }
      ]
    }
  }');
  return $items;
}
