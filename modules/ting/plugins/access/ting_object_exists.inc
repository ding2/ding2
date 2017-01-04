<?php
/**
 * @file
 * Controls access based on ting object sanity (existence).
 */

$plugin = array(
  'title' => t('Ting object exists'),
  'description' => t('Control access based on ting object existence.'),
  'callback' => 'ting_object_exists_ctools_access_check',
  'required context' => new ctools_context_required(t('Ting object'), 'ting_object'),
);

function ting_object_exists_ctools_access_check($__conf, $contexts) {
  return !empty($contexts->data->provider_id);
}
