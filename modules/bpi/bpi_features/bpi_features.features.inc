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
      "(creation)" : {"weight":"-50","sysid":"1","state":"(creation)","status":"1","name":"(creation)"},
      "local_content" : {"weight":"-19","sysid":"0","state":"Local content","status":"1","name":"local_content"},
      "pre_bpi" : {"weight":"-18","sysid":"0","state":"Pre-sending to BPI","status":"1","name":"pre_bpi"},
      "sent_to_bpi" : {"weight":"-17","sysid":"0","state":"Sent to BPI","status":"1","name":"sent_to_bpi"},
      "sent_local" : {"weight":"-16","sysid":"0","state":"Sent, updated locally","status":"1","name":"sent_local"},
      "created_bpi" : {"weight":"-15","sysid":"0","state":"Created from BPI","status":"1","name":"created_bpi"},
      "deleted_bpi" : {"weight":"-14","sysid":"0","state":"Deleted from BPI","status":"1","name":"deleted_bpi"}
    },
    "transitions" : {
      "_creation_to_local_content" : {"roles":{"-1":-1,"3":3,"4":4,"6":6,"7":7},"name":"_creation_to_local_content","label":"Save","start_state":"(creation)","end_state":"local_content"},
      "_creation_to_pre_bpi" : {"roles":{"3":3,"4":4,"6":6,"7":7},"name":"_creation_to_pre_bpi","label":"Save and push","start_state":"(creation)","end_state":"pre_bpi"},
      "_creation_to_created_bpi" : {"roles":{"3":3,"4":4,"6":6,"7":7},"name":"_creation_to_created_bpi","label":"Save content from BPI","start_state":"(creation)","end_state":"created_bpi"},
      "local_content_to_local_content" : {"roles":{"-1":-1,"3":3,"4":4,"6":6,"7":7},"name":"local_content_to_local_content","label":"Save","start_state":"local_content","end_state":"local_content"},
      "local_content_to_sent_to_bpi" : {"roles":{"3":3,"4":4,"6":6,"7":7},"name":"local_content_to_sent_to_bpi","label":"Save and push","start_state":"local_content","end_state":"sent_to_bpi"},
      "pre_bpi_to_local_content" : {"roles":{"3":3,"4":4,"6":6,"7":7},"name":"pre_bpi_to_local_content","label":"Save local content","start_state":"pre_bpi","end_state":"local_content"},
      "pre_bpi_to_pre_bpi" : {"roles":{"-1":-1,"3":3,"4":4,"6":6,"7":7},"name":"pre_bpi_to_pre_bpi","label":"Save","start_state":"pre_bpi","end_state":"pre_bpi"},
      "pre_bpi_to_sent_to_bpi" : {"roles":{"-1":-1,"3":3,"4":4,"6":6,"7":7},"name":"pre_bpi_to_sent_to_bpi","label":"Send to BPI","start_state":"pre_bpi","end_state":"sent_to_bpi"},
      "sent_to_bpi_to_sent_to_bpi" : {"roles":{"-1":-1,"3":3,"4":4,"6":6,"7":7},"name":"sent_to_bpi_to_sent_to_bpi","label":"Save and push","start_state":"sent_to_bpi","end_state":"sent_to_bpi"},
      "sent_to_bpi_to_sent_local" : {"roles":{"3":3,"4":4,"6":6,"7":7},"name":"sent_to_bpi_to_sent_local","label":"Save","start_state":"sent_to_bpi","end_state":"sent_local"},
      "sent_to_bpi_to_deleted_bpi" : {"roles":{"-1":-1,"3":3,"6":6},"name":"sent_to_bpi_to_deleted_bpi","label":"Delete from BPI","start_state":"sent_to_bpi","end_state":"deleted_bpi"},
      "sent_local_to_sent_to_bpi" : {"roles":{"3":3,"4":4,"6":6,"7":7},"name":"sent_local_to_sent_to_bpi","label":"Save and push","start_state":"sent_local","end_state":"sent_to_bpi"},
      "sent_local_to_sent_local" : {"roles":{"-1":-1,"3":3,"4":4,"6":6,"7":7},"name":"sent_local_to_sent_local","label":"Save","start_state":"sent_local","end_state":"sent_local"},
      "sent_local_to_deleted_bpi" : {"roles":{"-1":-1,"3":3,"6":6},"name":"sent_local_to_deleted_bpi","label":"Delete from BPI","start_state":"sent_local","end_state":"deleted_bpi"},
      "created_bpi_to_created_bpi" : {"roles":{"-1":-1,"3":3,"4":4,"6":6,"7":7},"name":"created_bpi_to_created_bpi","label":"Save content from BPI","start_state":"created_bpi","end_state":"created_bpi"},
      "deleted_bpi_to_sent_to_bpi" : {"roles":{"3":3,"4":4,"6":6,"7":7},"name":"deleted_bpi_to_sent_to_bpi","label":"Save and push","start_state":"deleted_bpi","end_state":"sent_to_bpi"},
      "deleted_bpi_to_sent_local" : {"roles":{"3":3,"4":4,"6":6,"7":7},"name":"deleted_bpi_to_sent_local","label":"Save","start_state":"deleted_bpi","end_state":"sent_local"},
      "deleted_bpi_to_deleted_bpi" : {"roles":{"-1":-1,"3":3,"4":4,"6":6,"7":7},"name":"deleted_bpi_to_deleted_bpi","label":"N\\/A","start_state":"deleted_bpi","end_state":"deleted_bpi"}
    },
    "label" : "BPI",
    "typeMap" : [],
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
