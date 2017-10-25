<?php
/**
 * @file
 * ting_covers_custom.relation_type_default.inc
 */

/**
 * Implements hook_relation_default_relation_types().
 */
function ting_covers_custom_relation_default_relation_types() {
  $export = array();

  $relation_type = new stdClass();
  $relation_type->disabled = FALSE; /* Edit this to true to make a default relation_type disabled initially */
  $relation_type->api_version = 1;
  $relation_type->relation_type = 'ting_covers_custom_cover';
  $relation_type->label = 'Ting custom cover';
  $relation_type->reverse_label = 'Ting custom cover';
  $relation_type->directional = 1;
  $relation_type->transitive = 0;
  $relation_type->r_unique = 1;
  $relation_type->min_arity = 2;
  $relation_type->max_arity = 2;
  $relation_type->source_bundles = array(
    0 => 'ting_covers_custom:cover',
  );
  $relation_type->target_bundles = array(
    0 => 'ting_object:ting_object',
  );
  $export['ting_covers_custom_cover'] = $relation_type;

  return $export;
}
