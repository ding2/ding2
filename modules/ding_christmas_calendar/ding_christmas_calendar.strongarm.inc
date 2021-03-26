<?php
/**
 * @file
 * ding_christmas_calendar.strongarm.inc
 */

/**
 * Implements hook_strongarm().
 */
function ding_christmas_calendar_strongarm() {
  $export = array();

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'scheduler_publish_enable_quiz_page';
  $strongarm->value = TRUE;
  $export['scheduler_publish_enable_quiz_page'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'scheduler_unpublish_enable_quiz_page';
  $strongarm->value = TRUE;
  $export['scheduler_unpublish_enable_quiz_page'] = $strongarm;

  return $export;
}
