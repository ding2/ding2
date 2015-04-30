<?php
/**
 * @file
 * ding_campaign.strongarm.inc
 */

/**
 * Implements hook_strongarm().
 */
function ding_campaign_strongarm() {
  $export = array();

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'scheduler_publish_enable_ding_campaign';
  $strongarm->value = 1;
  $export['scheduler_publish_enable_ding_campaign'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'scheduler_publish_required_ding_campaign';
  $strongarm->value = 0;
  $export['scheduler_publish_required_ding_campaign'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'scheduler_publish_revision_ding_campaign';
  $strongarm->value = 0;
  $export['scheduler_publish_revision_ding_campaign'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'scheduler_publish_touch_ding_campaign';
  $strongarm->value = 1;
  $export['scheduler_publish_touch_ding_campaign'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'scheduler_unpublish_enable_ding_campaign';
  $strongarm->value = 1;
  $export['scheduler_unpublish_enable_ding_campaign'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'scheduler_unpublish_required_ding_campaign';
  $strongarm->value = 0;
  $export['scheduler_unpublish_required_ding_campaign'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'scheduler_unpublish_revision_ding_campaign';
  $strongarm->value = 0;
  $export['scheduler_unpublish_revision_ding_campaign'] = $strongarm;

  return $export;
}
