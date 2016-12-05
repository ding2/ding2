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
    'ding_interaction_manual' => 'ding_interaction_manual',
    'ding_list' => 'ding_list',
    'ding_entity_rating' => 0,
    'ding_entity_rating_loan_history' => 0,
    'ding_user_consent' => 0, 
  );
  $export['ding_interaction_callbacks'] = $strongarm;

  return $export;
}
