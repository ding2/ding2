<?php
/**
 * @file
 * Batch job callbacks used in the installation profile.
 */

/**
 * Enables an module.
 *
 * @param string $module
 *   The modules machine name.
 * @param string $module_name
 *   The modules human name.
 * @param array $context
 *   The context of the batch job.
 */
function _ding2_enable_module($module, $module_name, &$context) {
  module_enable(array($module), FALSE);
  $context['message'] = st('Installed %module module.', array('%module' => $module_name));
}

/**
 * Import translation into the database.
 *
 * @param string $type
 *   Type of translation.
 * @param string $translation_file
 *   File with translation.
 * @param array $context
 *   The context of the batch job.
 */
function _ding2_insert_translation($type, $translation_file, &$context) {
  $file = new stdClass();
  $file->uri = DRUPAL_ROOT . $translation_file;
  $file->filename = basename($file->uri);

  _locale_import_po($file, 'da', LOCALE_IMPORT_OVERWRITE, $type);

  $context['message'] = st('Installed %type translation.', array('%type' => $type));
}

/**
 * Reverts a given feature module.
 *
 * @param string $feature
 *   Name of the module to revert.
 */
function _ding2_features_revert($feature) {
  // Load the feature.
  if (($feature = features_load_feature($feature, TRUE)) && module_exists($feature)) {
    // Get all components of the feature.
    foreach (array_keys($feature->info['features']) as $component) {
      if (features_hook($component, 'features_revert')) {
        // Revert each component (force).
        features_revert(array($feature => array($component)));
      }
    }
  }

  $context['message'] = st('Reverted %feature.', array('%feature' => $feature));
}
