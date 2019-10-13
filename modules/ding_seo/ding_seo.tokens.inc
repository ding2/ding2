<?php

/**
 * @file
 * Token callbacks for Ding SEO module.
 */

 /**
 * Implements hook_token_info()
 */
function ding_seo_token_info() {
  // Define a pseudo token type for covers on ting_object entities. Note that
  // we do not supply a separate description and needs-data, since this token
  // type is only added to ting_cover tokens and is not meant to be used on
  // its own.
  $info['types']['ding_seo_ting_cover'] = [
    'name' => t('Ding SEO ting cover'),
  ];
  $info['tokens']['ting_object']['ding_seo_ting_cover'] = [
    'name' => t('Ding SEO ting cover'),
    'description' => t('Pseudo token type for ting object covers'),
    'type' => 'ding_seo_ting_cover',
  ];

  // Define the tokens supported on our pseudo token type.
  $info['tokens']['ding_seo_ting_cover']['path'] = [
    'name' => t('Path'),
    'description' => t('Path of the cover'),
  ];
  $info['tokens']['ding_seo_ting_cover']['url'] = [
    'name' => t('URL'),
    'description' => t('External URL to the cover'),
  ];
  $info['tokens']['ding_seo_ting_cover']['width'] = [
    'name' => t('Width'),
    'description' => t('Width of the cover'),
  ];
  $info['tokens']['ding_seo_ting_cover']['height'] = [
    'name' => t('Height'),
    'description' => t('Height of the cover'),
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
    $path = ting_covers_object_path($ting_object->getId());

    foreach (token_find_with_prefix($tokens, 'ding_seo_ting_cover') as $name => $original) {
      if ($name == 'path') {
        $replacements[$original] = $path;
      }
      elseif ($name == 'url') {
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
