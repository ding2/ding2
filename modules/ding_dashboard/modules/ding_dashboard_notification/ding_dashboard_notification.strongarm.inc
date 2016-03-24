<?php
/**
 * @file
 * ding_dashboard_notification.strongarm.inc
 */

/**
 * Implements hook_strongarm().
 */
function ding_dashboard_notification_strongarm() {
  $export = array();

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'ding_dashboard_notification_settings';
  $strongarm->value = array(
    'author' => array(
      'push' => array(
        'administrators' => 0,
        'editor' => 1,
        'guest blogger' => 0,
        'local administrator' => 0,
        'local editor' => 0,
        'provider' => 0,
        'staff' => 0,
      ),
    ),
    'editor' => array(
      'approve' => 1,
      'reject' => 1,
      'delete' => 1,
      'commented' => 1,
    ),
  );
  $export['ding_dashboard_notification_settings'] = $strongarm;

  return $export;
}
