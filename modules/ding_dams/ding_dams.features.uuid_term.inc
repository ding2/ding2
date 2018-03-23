<?php

/**
 * @file
 * ding_dams.features.uuid_term.inc
 */

/**
 * Implements hook_uuid_features_default_terms().
 */
function ding_dams_uuid_features_default_terms() {
  $terms = array();

  $terms[] = array(
    'name' => 'Staff images',
    'description' => NULL,
    'format' => NULL,
    'weight' => 3,
    'uuid' => '43d13750-aec5-4b2b-bde2-edb244470a7a',
    'vocabulary_machine_name' => 'dams_category',
  );
  $terms[] = array(
    'name' => 'List images',
    'description' => NULL,
    'format' => NULL,
    'weight' => 2,
    'uuid' => 'a8396a8d-ed63-463d-81c9-16f3feb7b43b',
    'vocabulary_machine_name' => 'dams_category',
  );
  $terms[] = array(
    'name' => 'Various',
    'description' => NULL,
    'format' => NULL,
    'weight' => 0,
    'uuid' => 'acf4faaf-a4f0-4733-8370-48e0225a86a8',
    'vocabulary_machine_name' => 'dams_category',
  );
  $terms[] = array(
    'name' => 'Main images',
    'description' => NULL,
    'format' => NULL,
    'weight' => 1,
    'uuid' => 'df06539f-bb2e-424d-a32d-b2d03812172e',
    'vocabulary_machine_name' => 'dams_category',
  );
  return $terms;
}
