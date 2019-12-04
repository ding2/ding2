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
    'needs-data' => 'ting_object',
  ];
  $info['tokens']['ting_object']['ding_seo_ting_cover'] = [
    'name' => t('Ding SEO ting cover'),
    'description' => t('Pseudo token type for ting object covers'),
    'type' => 'ding_seo_ting_cover',
  ];

  // Define the tokens supported on ding_seo_ting_cover pseudo token type.
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

  $info['types']['ding_seo_ting_object_collection_objects'] = [
    'name' => t('Ding SEO ting_object collection objects'),
    'needs-data' => 'ting_object',
  ];
  $info['tokens']['ting_object']['ding_seo_ting_object_collection_objects'] = [
    'name' => t('Ding SEO ting_object collection objects'),
    'description' => t("Token type that generates lists of values using the properties from the objects on the ting_collection generated when using the passed ting_object as primary object."),
    'type' => 'ding_seo_ting_object_collection_objects',
  ];

  // Define the tokens supported on ding_seo_ting_object_collection_objects token type.
  $info['tokens']['ding_seo_ting_object_collection_objects']['title'] = [
    'name' => t('Title'),
    'description' => t("Comma-separated list of each object's title"),
  ];
  $info['tokens']['ding_seo_ting_object_collection_objects']['ting_object_url'] = [
    'name' => t('Ting object URL'),
    'description' => t("Comma-separated list of each object's external ting object URL"),
  ];
  $info['tokens']['ding_seo_ting_object_collection_objects']['isbn'] = [
    'name' => t('ISBN'),
    'description' => t("Comma-separated list of each object's ISBN"),
  ];
  $info['tokens']['ding_seo_ting_object_collection_objects']['date_published'] = [
    'name' => t('Date published'),
    'description' => t("Comma-separated list of each object's published date"),
  ];
  $info['tokens']['ding_seo_ting_object_collection_objects']['version'] = [
    'name' => t('Version'),
    'description' => t("Comma-separated list of each object's version"),
  ];
  $info['tokens']['ding_seo_ting_object_collection_objects']['book_format'] = [
    'name' => t('Schema.org bookFormat of the ting_object if any (Ebook, Hardcover, Paperback or AudioBook)'),
    'description' => t("Comma-separated list of each object's bookFormat"),
  ];

  // Define general SEO-related tokens on ting_object.
  $info['tokens']['ting_object']['ding_seo_work_url'] = [
    'name' => t('Ding SEO work URL'),
    'description' => t('External URL to the ting_collection for this ting_object'),
  ];
  $info['tokens']['ting_object']['ding_seo_book_format'] = [
    'name' => t('Ding SEO bookFormat'),
    'description' => t('The schema.org the bookFormat of the ting_object (if any)'),
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

    // Handle ding_seo_ting_object_collection_objects tokens.
    $collection_tokens = token_find_with_prefix($tokens, 'ding_seo_ting_object_collection_objects');
    // Only fetch collections if there's any applicable tokens.
    if (!empty($collection_tokens)) {
      $collection = ting_collection_load($ting_object->getId());
      $objects = $collection->getEntities();
      foreach ($collection_tokens as $name => $original) {
        if ($name == 'title') {
          $replacements[$original] = _ding_seo_generate_collection_objects_value(function($object) {
            return $object->getTitle();
          }, $objects);
        }
        elseif ($name == 'ting_object_url') {
          $replacements[$original] = _ding_seo_generate_collection_objects_value(function($object) {
            $ting_object_path = entity_uri('ting_object', $object)['path'];
            return url($ting_object_path, [ 'absolute' => TRUE ]);
          }, $objects);
        }
        elseif ($name == 'isbn') {
          $replacements[$original] = _ding_seo_generate_collection_objects_value(function($object) {
            return $object->getIsbn();
          }, $objects);
        }
        elseif ($name == 'date_published') {
          // The best we can do with TingObjectInterface is to get the year of
          // publication (this is also a limitation in DKABM which mostly only
          // refers to year). If opensearch is search provider we could get more
          // accuracy by fetching marc record, which appearently has year-week
          // publication in 990 *o. But this would be provider specific and also
          // impact performance because of the extra request to the well.
          // See: http://metadata.dk/DKABM_2011#dc:date
          // See: http://www.kat-format.dk/danMARC2/Danmarc2.a3.htm#pgfId=1575596
          $replacements[$original] = _ding_seo_generate_collection_objects_value(function($object) {
            return $object->getTingObject()->getYear();
          }, $objects);
        }
        elseif ($name == 'version') {
          $replacements[$original] = _ding_seo_generate_collection_objects_value(function($object) {
            return $object->getTingObject()->getVersion();
          }, $objects);
        }
        elseif ($name == 'book_format') {
          $replacements[$original] = _ding_seo_generate_collection_objects_value(function($object) {
            return ding_seo_get_schema_book_format($object);
          }, $objects);
        }
      }
    }


    // Handle general "ungrouped" SEO-related tokens on ting_object.
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

/**
 * Private helper function to generate colletion objects value for tokens.
 */
function _ding_seo_generate_collection_objects_value($callback, $objects) {
  return implode(', ', array_map(function($object) use ($callback) {
    // Wrap the callback in our own to be able to do some basic checking and
    // normalizing in a central place.
    $value = $callback($object);

    // Handle array values.
    if (is_array($value)) {
      $value = reset($value);
    }

    // Because we rely on the the pivot setting in Schema metatag module, we
    // can't allow commas in the value since that is used as separator. For now
    // we just remove it.
    $value = str_replace(',', '', $value);
    // We can not allow empty values or else values will be mixed because of the
    // way the pivot setting works. Need to find a way to remove these entries
    // from the final JSON-LD.
    // See: https://www.drupal.org/docs/8/modules/schemaorg-metatag/pivot
    if (empty($value)) {
      $value = 'N/A';
    }

    return $value;
  }, $objects));
}
