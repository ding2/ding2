<?php

/**
 * @file
 * Ding SEO metatag hook implementations.
 */

/**
 * Implements hook_metatag_config_instance_info_alter()
 */
function ding_seo_metatag_config_instance_info_alter(&$info) {
  if (isset($info['ting_object'])) {
    $info['ting_object:book'] = [
      'label' => t('Book'),
    ];
    $info['ting_object:movie'] = [
      'label' => t('Movie'),
    ];
  }
}
