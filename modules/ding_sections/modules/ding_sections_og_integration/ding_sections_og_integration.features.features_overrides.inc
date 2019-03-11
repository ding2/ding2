<?php
/**
 * @file
 * ding_sections_og_integration.features.features_overrides.inc
 */

/**
 * Implements hook_features_override_default_overrides().
 */
function ding_sections_og_integration_features_override_default_overrides() {
  // This code is only used for UI in features. Exported alters hooks do the magic.
  $overrides = array();

  // Exported overrides for: variable
  $overrides["variable.og_menu_max_menus_per_group.value"] = 0;

 return $overrides;
}
