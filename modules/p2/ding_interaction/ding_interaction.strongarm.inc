<?php
/**
 * @file
 * ding_interaction.strongarm.inc
 */

/**
 * Implements hook_strongarm().
 */
function ding_interaction_strongarm() {
  $export = array();

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'ding_interaction_callbacks';
  $strongarm->value = array(
    'ding_entity_rating_loan_history' => 'ding_entity_rating_loan_history',
    'ding_interaction_manual' => 'ding_interaction_manual',
    'ding_interests' => 'ding_interests',
    'ding_interests_by_history' => 'ding_interests_by_history',
    'ding_user_complete' => 'ding_user_complete',
    'ding_user_consent' => 'ding_user_consent',
  );
  $export['ding_interaction_callbacks'] = $strongarm;

  return $export;
}
