<?php
/**
 * @file
 * Controls access based on ting object sanity (existence).
 */

/**
 * Plugin definition array.
 */
$plugin = array(
  'title' => t('Ting object exists'),
  'description' => t('Control access based on ting object existence.'),
  'callback' => 'ting_object_exists_ctools_access_check',
  'required context' => new ctools_context_required(t('Ting object'), 'ting_object'),
);

/**
 * Controls the access to panel variant based on ting object property existence.
 *
 * @return bool
 */
function ting_object_exists_ctools_access_check($__conf, $contexts) {
  // Assume that an existing ting object has this property.
  return !empty($contexts->data->provider_id);
}
