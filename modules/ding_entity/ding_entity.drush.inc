<?php
/**
 * @file
 *  Ding_entity's drush integration.
 */

/**
 * Implements hook_drush_command().
 */
function ding_entity_drush_command() {
  $items['ding-entity-update'] = array(
    'description' => 'Update all entity fields.',
  );

  return $items;
}

function drush_ding_entity_update() {
  $modules = array();
  foreach (module_list() as $module) {
    // Hook should be defined in install file.
    module_load_install($module);
    if (module_hook($module, 'ding_entity_fields')) {
      $modules[] = $module;
    }
  }

  if ($modules) {
    ding_entity_modules_disabled($modules);
    ding_entity_modules_enabled($modules);
    drush_log(dt('Updated fields from modules: @modules', array('@modules' => implode(', ', $modules))), 'ok');
  }
  else {
    drush_log(dt('No modules implement hook_ding_entity_fields.'), 'error');
  }
}
