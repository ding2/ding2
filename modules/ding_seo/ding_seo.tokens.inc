<?php

/**
 * @file
 * Token callbacks for Ding SEO module.
 */

 /**
 * Implements hook_token_info()
 */
function ding_seo_token_info() {
  $info['types']['ding_seo_ting_cover_path'] = [
    'name' => t('Ding SEO ting cover path'),
    'description' => t('Path to the downloaded cover for a ting object'),
    'needs-data' => 'ding_seo_ting_cover_path',
  ];
  $info['tokens']['ding_seo_ting_cover_path']['url'] = [
    'name' => t('URL'),
    'description' => t('External URL to the cover'),
  ];
  $info['tokens']['ding_seo_ting_cover_path']['width'] = [
    'name' => t('Width'),
    'description' => t('Width of the cover'),
  ];
  $info['tokens']['ding_seo_ting_cover_path']['height'] = [
    'name' => t('Height'),
    'description' => t('Height of the cover'),
  ];
  $info['tokens']['ting_object']['ding_seo_ting_cover_path'] = [
    'name' => t('Ding SEO ting cover path'),
    'description' => t('Path to the downloaded cover for a ting object'),
    'type' => 'ding_seo_ting_cover_path',
  ];

  return $info;
}

/**
 * Implements hook_tokens().
 */
function ding_seo_tokens($type, $tokens, array $data, array $options) {
  $replacements = [];

  if ($type == 'ting_object' && !empty($data['ting_object'])) {
    $ting_object = $data['ting_object'];
    foreach ($tokens as $name => $original) {
      if ($name == 'ding_seo_ting_cover_path') {
        // Maybe the ting object has no cover, so we're taking a guess here.
        // Find out how search engines will handle the 404. Maybe a file_exists
        // is more appropiate.
        $replacements[$original] = ting_covers_object_path($ting_object->getId());
      }
    }
    // Handle chained token.
    if ($cover_tokens = token_find_with_prefix($tokens, 'ding_seo_ting_cover_path')) {
      $path = ting_covers_object_path($ting_object->getId());
      $replacements += token_generate('ding_seo_ting_cover_path', $cover_tokens, array(
        'ding_seo_ting_cover_path' => ting_covers_object_path($ting_object->getId()),
      ), $options);
    }
  }

  if ($type == 'ding_seo_ting_cover_path' && !empty($data['ding_seo_ting_cover_path'])) {
    $path = $data['ding_seo_ting_cover_path'];
    foreach ($tokens as $name => $original) {
      if ($name == 'url') {
        $replacements[$original] = file_create_url($path);
      }
      elseif ($name == 'width' || $name == 'height') {
        $realpath = drupal_realpath($path);
        // We can only output something here if the file exists and is valid
        // image file. Furthermore if the cover cache has just been cleared
        // the file may not be there until next request even though the ting
        // object has cover.
        if (file_exists($path) && $size = getimagesize($realpath)) {
          if ($name == 'width') {
            $replacements[$original] = $size[0];
          }
          elseif ($name == 'height') {
            $replacements[$original] = $size[1];
          }
        }
      }
    }
  }

  return $replacements;
}
