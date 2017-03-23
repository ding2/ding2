<?php
/**
 * @file
 * ting_subsearch_secondary.features.features_overrides.inc
 */

/**
 * Implements hook_features_override_default_overrides().
 */
function ting_subsearch_secondary_features_override_default_overrides() {
  // This code is only used for UI in features. Exported alters hooks do the magic.
  $overrides = array();

  // Exported overrides for: field_instance
  $overrides["field_instance.ting_collection-ting_collection-ting_primary_object.display|minimal"] = array(
    'label' => 'hidden',
    'module' => 'ting',
    'settings' => array(
      'view_mode' => 'minimal',
    ),
    'type' => 'ting_primary_object_default',
    'weight' => 0,
  );
  $overrides["field_instance.ting_object-ting_object-ting_author.display|minimal"] = array(
    'label' => 'hidden',
    'module' => 'ting_subsearch_secondary',
    'settings' => array(),
    'type' => 'ting_author_minimal',
    'weight' => 2,
  );
  $overrides["field_instance.ting_object-ting_object-ting_title.display|minimal"] = array(
    'label' => 'hidden',
    'module' => 'ting_subsearch_secondary',
    'settings' => array(
      'link_type' => 'none',
      'prefix_type' => 'no',
    ),
    'type' => 'ting_title_minimal',
    'weight' => 0,
  );
  $overrides["field_instance.ting_object-ting_object-ting_type.display|minimal"] = array(
    'label' => 'hidden',
    'module' => 'ting',
    'settings' => array(),
    'type' => 'ting_type_default',
    'weight' => 1,
  );

 return $overrides;
}
