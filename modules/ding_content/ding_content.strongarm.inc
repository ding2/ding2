<?php
/**
 * @file
 * ding_content.strongarm.inc
 */

/**
 * Implements hook_strongarm().
 */
function ding_content_strongarm() {
  $export = array();

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_notify_available_alerts';
  $strongarm->value = array(
    1 => '1',
    2 => '2',
  );
  $export['comment_notify_available_alerts'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_notify_comment_notify_default_mailtext';
  $strongarm->value = 'Hej [comment-subscribed:author],

[comment:author] har kommenteret på: "[comment:node:title]"

----
[comment:body]
----

Du kan se kommentaren på følgende url
[comment:url]

Du kan stoppe at modtage emails når nogen kommenterer dit indlæg 
ved at gå til  [comment-subscribed:unsubscribe-url]


Med venlig hilsen [site:name] team
[site:url]';
  $export['comment_notify_comment_notify_default_mailtext'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_notify_default_anon_mailalert';
  $strongarm->value = '0';
  $export['comment_notify_default_anon_mailalert'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_notify_default_registered_mailalert';
  $strongarm->value = '1';
  $export['comment_notify_default_registered_mailalert'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_notify_node_notify_default_mailalert';
  $strongarm->value = 0;
  $export['comment_notify_node_notify_default_mailalert'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_notify_node_notify_default_mailtext';
  $strongarm->value = 'Hej [comment:node:author],

Du har modtaget en kommentar på: "[comment:node:title]"

----
[comment:body]
----

Du kan se kommentaren på følgende url
[comment:url]

Du vil modtage email som denne for hver kommentar på dit indlæg. 
Du kan slå denne funktion fra ved at logge ind og ændre indstillingerne på din brugerprofil på 
[comment:node:author:edit-url].

Med venlig hilsen [site:name] team
[site:url]';
  $export['comment_notify_node_notify_default_mailtext'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_notify_node_types';
  $strongarm->value = array(
    'ding_event' => 'ding_event',
    'ding_news' => 'ding_news',
    'ding_library' => 0,
    'ding_eresource' => 0,
    'ding_faq_question' => 0,
    'ding_group' => 0,
    'ding_campaign' => 0,
    'new_materials' => 0,
    'panel' => 0,
    'promotion' => 0,
    'ding_rolltab' => 0,
    'ding_page' => 0,
    'webform' => 0,
  );
  $export['comment_notify_node_types'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'media_wysiwyg_wysiwyg_browser_plugins';
  $strongarm->value = array(
    0 => 'ding_content',
    1 => 'upload',
    2 => 'media_default--media_browser_1',
    3 => 'media_default--media_browser_my_files',
    4 => 'media_internet',
  );
  $export['media_wysiwyg_wysiwyg_browser_plugins'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'page_manager_node_view_disabled';
  $strongarm->value = FALSE;
  $export['page_manager_node_view_disabled'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'page_manager_term_view_disabled';
  $strongarm->value = FALSE;
  $export['page_manager_term_view_disabled'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'pm_existing_pages_disabled_ding_content_workbench_recent_content';
  $strongarm->value = FALSE;
  $export['pm_existing_pages_disabled_ding_content_workbench_recent_content'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'workbench_myworkbench_disabled';
  $strongarm->value = FALSE;
  $export['workbench_myworkbench_disabled'] = $strongarm;

  return $export;
}
