<?php
/**
 * @file
 * This file implements support for drush into the module.
 *
 * Adds support for testing campaign validation rules during development.
 */

/**
 * Implements hook_drush_command().
 */
function ding_campaign_plus_drush_command() {
  return array(
    'campaign_notify' => array(
      'description' => dt('Test campaign notify rules on an campaign (with-out sending mail).'),
      'arguments' => array(
        'cnid' => dt('Campaign node id')
      ),
      'options' => array(),
      'aliases' => array('cmpn'),
      'bootstrap' => DRUSH_BOOTSTRAP_DRUPAL_FULL,
    ),
  );
}

/**
 * Test notification rules for a given campaign.
 */
function drush_ding_campaign_plus_campaign_notify($campaign_nid) {
  _ding_campaign_plus_notification($campaign_nid, FALSE);
}
