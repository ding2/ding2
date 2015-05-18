<?php
/**
 * @file
 * bpi_features.features.inc
 */

/**
 * Implements hook_default_Workflow().
 */
function bpi_features_default_Workflow() {
  $workflows = array();

  // Exported workflow: 'bpi'
  $workflows['bpi'] = entity_import('Workflow', '{
    "name" : "bpi",
    "tab_roles" : [],
    "options" : [],
    "states" : {
      "7" : {"sid":"7","wid":"2","weight":"-50","sysid":"1","state":"(creation)","status":"1","name":"(creation)"},
      "10" : {"sid":"10","wid":"2","weight":"-19","sysid":"0","state":"Local content","status":"1","name":"local_content"},
      "8" : {"sid":"8","wid":"2","weight":"-18","sysid":"0","state":"Sent to BPI","status":"1","name":"sent_to_bpi"},
      "11" : {"sid":"11","wid":"2","weight":"-17","sysid":"0","state":"Sent, updated locally","status":"1","name":"sent_updated_locally"},
      "9" : {"sid":"9","wid":"2","weight":"-16","sysid":"0","state":"Created from BPI","status":"1","name":"created_from_bpi"},
      "12" : {"sid":"12","wid":"2","weight":"-15","sysid":"0","state":"Deleted","status":"1","name":"deleted"}
    },
    "transitions" : {
      "25" : {"tid":"25","sid":"7","target_sid":"10","roles":{"-1":-1,"3":3,"4":4,"6":6,"7":7},"wid":"2","name":"7_10","label":"Save"},
      "21" : {"tid":"21","sid":"7","target_sid":"9","roles":{"3":3,"4":4,"6":6,"7":7},"wid":"2","name":"7_9","label":"Save content from BPI"},
      "26" : {"tid":"26","sid":"10","target_sid":"10","roles":{"-1":-1,"3":3,"4":4,"5":5,"6":6,"7":7,"8":8,"9":9},"wid":"2","name":"10_10","label":"Save"},
      "27" : {"tid":"27","sid":"10","target_sid":"8","roles":{"3":3,"4":4,"6":6,"7":7},"wid":"2","name":"10_8","label":"Save and push"},
      "30" : {"tid":"30","sid":"10","target_sid":"12","roles":{"3":3,"4":4,"6":6,"7":7},"wid":"2","name":"10_12","label":"Delete from BPI"},
      "22" : {"tid":"22","sid":"8","target_sid":"8","roles":{"-1":-1,"3":3,"4":4,"5":5,"6":6,"7":7,"8":8,"9":9},"wid":"2","name":"8_8","label":"Save and push"},
      "31" : {"tid":"31","sid":"8","target_sid":"11","roles":{"3":3,"4":4,"6":6,"7":7},"wid":"2","name":"8_11","label":"Save"},
      "32" : {"tid":"32","sid":"8","target_sid":"12","roles":{"3":3,"4":4,"6":6,"7":7},"wid":"2","name":"8_12","label":"Delete from BPI"},
      "33" : {"tid":"33","sid":"11","target_sid":"8","roles":{"3":3,"4":4,"6":6,"7":7},"wid":"2","name":"11_8","label":"Save and push"},
      "34" : {"tid":"34","sid":"11","target_sid":"11","roles":{"-1":-1,"3":3,"4":4,"5":5,"6":6,"7":7,"8":8,"9":9},"wid":"2","name":"11_11","label":"Save"},
      "35" : {"tid":"35","sid":"11","target_sid":"12","roles":{"3":3,"4":4,"6":6,"7":7},"wid":"2","name":"11_12","label":"Delete from BPI"},
      "24" : {"tid":"24","sid":"9","target_sid":"9","roles":{"-1":-1,"3":3,"4":4,"5":5,"6":6,"7":7,"8":8,"9":9},"wid":"2","name":"9_9","label":"Save content from BPI"},
      "36" : {"tid":"36","sid":"9","target_sid":"12","roles":{"3":3,"4":4,"6":6,"7":7},"wid":"2","name":"9_12","label":"Delete from BPI"},
      "37" : {"tid":"37","sid":"12","target_sid":"12","roles":{"-1":-1,"3":3,"4":4,"5":5,"6":6,"7":7,"8":8,"9":9},"wid":"2","name":"12_12","label":"N\\/A"}
    },
    "label" : "BPI",
    "typeMap" : [],
    "wid_original" : "2",
    "system_roles" : {
      "-1" : "(author)",
      "1" : "anonymous user",
      "2" : "authenticated user",
      "3" : "administrators",
      "4" : "editor",
      "5" : "guest blogger",
      "6" : "local administrator",
      "7" : "local editor",
      "8" : "provider",
      "9" : "staff"
    }
  }');

  return $workflows;
}

/**
 * Implements hook_ctools_plugin_api().
 */
function bpi_features_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "field_group" && $api == "field_group") {
    return array("version" => "1");
  }
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_views_api().
 */
function bpi_features_views_api($module = NULL, $api = NULL) {
  return array("api" => "3.0");
}
