<?php

/**
 * @file
 * Ding SEO metatag hook implementations.
 */

 /**
  * Implements hook_metatag_info_alter().
  */
function ding_seo_metatag_info_alter(&$info) {
  // Ensure that multiple is set on book author so that we can use the pivot
  // option and have mutliple Person entities on books with multiple creators
  // and contributers. This is a requirment by google.
  // See: https://developers.google.com/search/docs/data-types/book#book
  // See: https://www.drupal.org/docs/8/modules/schemaorg-metatag/pivot
  // Note: this is probably an oversight by the developers of schema_metatag
  // and maybe an issue and patch would be appropiate. However this will work
  // for now as it will still work if it's fixed in feature releases.
  $info['tags']['schema_book.author']['multiple'] = TRUE;
}

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
