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

  // SEO-related tokens on ting_object.
  $info['tokens']['ting_object']['ding_seo_work_url'] = [
    'name' => t('Ding SEO work URL'),
    'description' => t('External URL to the ting_collection for this ting_object')
  ];
  $info['tokens']['ting_object']['ding_seo_book_format'] = [
    'name' => t('Ding SEO bookFormat'),
    'description' => t('The schema.org the bookFormat of the ting_object (if any)')
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

    // Handle SEO-related tokens on ting_object.
    foreach ($tokens as $name => $original) {
      switch ($name) {
        case 'ding_seo_work_url':
          $collection_path = entity_uri('ting_collection', $ting_object)['path'];
          $replacements[$original] = url($collection_path, [
            'absolute' => TRUE,
          ]);
          break;
        case 'ding_seo_book_format':
          $book_format = ding_seo_get_schema_book_format($ting_object);
          // Maybe return NULL if not set is more appropiate?
          if (isset($book_format)) {
            $replacements[$original] = $book_format;
          }
          break;
      }
    }
  }

  return $replacements;
}
