<?php

/**
 * @file
 * Token callbacks for Ding SEO module.
 */

 /**
 * Implements hook_token_info()
 */
function ding_seo_token_info() {
  // Define ding_seo_ting_cover token type.
  $info['types']['ding_seo_ting_cover'] = [
    'name' => t('Ding SEO ting cover'),
    'needs-data' => 'ting_object',
  ];
  $info['tokens']['ting_object']['ding_seo_ting_cover'] = [
    'name' => t('Ding SEO ting cover'),
    'description' => t('Pseudo token type for ting object covers'),
    'type' => 'ding_seo_ting_cover',
  ];
  // Define the tokens supported on ding_seo_ting_cover token type.
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

  // Define ding_seo_ting_object_collection_objects
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

  // Define ding_seo_creators_contributers token type.
  $info['types']['ding_seo_creators_contributers'] = [
    'name' => t('Ding SEO creators and contributers'),
    'description' => t('Provides several ways of getting creators and/or contributers for a ting_object. Is also aware of different types of creators and contributers.'),
    'needs-data' => 'ting_object',
  ];
  $info['tokens']['ting_object']['ding_seo_creators_contributers'] = [
    'name' => t('Ding SEO creators and contributers'),
    'type' => 'ding_seo_creators_contributers',
  ];
  // Define tokens supported on ding_seo_creators_contributers.
  $info['tokens']['ding_seo_creators_contributers']['names'] = [
    'name' => t('Names'),
    'description' => t('Comma-separated list of names of all creators and contributers combined'),
  ];
  $info['tokens']['ding_seo_creators_contributers']['author_names'] = [
    'name' => t('Names'),
    'description' => t('Comma-separated list of names of author names'),
  ];
  $info['tokens']['ding_seo_creators_contributers']['translator_names'] = [
    'name' => t('Names'),
    'description' => t('Comma-separated list of names of translator names'),
  ];
  $info['tokens']['ding_seo_creators_contributers']['director_names'] = [
    'name' => t('Director names'),
    'description' => t('Comma-separated list of director names'),
  ];
  $info['tokens']['ding_seo_creators_contributers']['actor_names'] = [
    'name' => t('Actor names'),
    'description' => t('Comma-separated list of actor names'),
  ];
  $info['tokens']['ding_seo_creators_contributers']['producer_names'] = [
    'name' => t('Producer names'),
    'description' => t('Comma-separated list of producer names'),
  ];
  $info['tokens']['ding_seo_creators_contributers']['composer_names'] = [
    'name' => t('Composer names'),
    'description' => t('Comma-separated list of composer names'),
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
  $info['tokens']['ting_object']['ding_seo_extent'] = [
    'name' => t('Ding SEO Extent'),
    'description' => t('The size or duration of the material in ISO 8601'),
  ];

  // Define ding_seo_node_tokens token type.
  $info['types']['ding_seo_node_tokens'] = [
    'name' => t('Ding SEO node tokens'),
    'description' => t('Special node tokens defined by Ding SEO for use in structured data'),
    'needs-data' => 'node',
  ];
  $info['tokens']['node']['ding_seo_node_tokens'] = array(
    'name' => t("Ding SEO node tokens"),
    'description' => t('Special node tokens defined by Ding SEO for use in structured data'),
    'type' => 'ding_seo_node_tokens',
  );
  // Define tokens supported on ding_seo_node_tokens.
  $info['tokens']['ding_seo_node_tokens']['location_name'] = array(
    'name' => t("Location Name"),
    'description' => t('The location is the '),
  );

  $info['tokens']['ding_seo_node_tokens']['location_url'] = [
    'name' => t("Location Url"),
    'description' => t('location_url'),
  ];
  $info['tokens']['ding_seo_node_tokens']['postalCode'] = [
    'name' => t("Postal Code"),
    'description' => t('Postal Code'),
  ];
  $info['tokens']['ding_seo_node_tokens']['streetAddress'] = [
    'name' => t("Street Address"),
    'description' => t('Street Address'),
  ];
  $info['tokens']['ding_seo_node_tokens']['addressLocality'] = [
    'name' => t("Address Locality"),
    'description' => t('Address Locality'),
  ];
  $info['tokens']['ding_seo_node_tokens']['addressRegion'] = [
    'name' => t("Address Region"),
    'description' => t('Address Region'),
  ];
  $info['tokens']['ding_seo_node_tokens']['addressCountry'] = [
    'name' => t("Address Country"),
    'description' => t('Address Country'),
  ];
  $info['tokens']['ding_seo_node_tokens']['longitude'] = [
    'name' => t("Longitude"),
    'description' => t('longitude'),
  ];
  $info['tokens']['ding_seo_node_tokens']['latitude'] = [
    'name' => t("´Latitude"),
    'description' => t('latitude'),
  ];

  // Logo dimensions tokens
  $info['tokens']['ding_seo_node_tokens']['logo_width'] = [
    'name' => t("Logo width"),
    'description' => t('logo_width'),
  ];
  $info['tokens']['ding_seo_node_tokens']['logo_height'] = [
    'name' => t("Logo height"),
    'description' => t('logo_height'),
  ];

  // Event data formatting
  $info['tokens']['ding_seo_node_tokens']['event_startdate'] = [
    'name' => t("Event Startdate"),
    'description' => t('Event enddate in YYYY-MM-DD HH:MM::SS format'),
  ];
  $info['tokens']['ding_seo_node_tokens']['event_enddate'] = [
    'name' => t("Event Enddate"),
    'description' => t('Event enddate in YYYY-MM-DD HH:MM::SS format'),
  ];
  $info['tokens']['ding_seo_node_tokens']['event_free'] = [
    'name' => t("Event Free Boolean"),
    'description' => t('Boolean of whether the event is free or not '),
  ];

  // Language
  $info['tokens']['ding_seo_node_tokens']['language'] = [
    'name' => t("Language"),
    'description' => t('language'),
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

    // Handle ding_seo_ting_cover token type.
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

    // Handle ding_seo_ting_object_collection_objects token type.
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

    // Handle ding_seo_creators_contributers token type.
    foreach (token_find_with_prefix($tokens, 'ding_seo_creators_contributers') as $name => $original) {
      // TODO: Make this search provider non-specific or depend on opensearch?
      $record = $ting_object->getTingObject()->record;
      $creators = $record['dc:creator'] ?? [];
      $contributers = $record['dc:contributor'] ?? [];
      // We don't know if a given function code can be on both so merge them
      // recursively to ensure we don't miss any.
      $combined = array_merge_recursive($creators, $contributers);

      $value = [];
      switch ($name) {
        case 'author_names':
          $value = $combined['dkdcplus:aut'] ?? [];
          break;
        case 'director_names':
          $value = $combined['dkdcplus:drt'] ?? [];
          break;
        case 'actor_names':
          $value = $combined['dkdcplus:act'] ?? [];
          break;
        case 'producer_names':
          $value = $combined['dkdcplus:pro'] ?? [];
          break;
        case 'composer_names':
          $value = $combined['dkdcplus:cmp'] ?? [];
          break;
        case 'translator_names':
          $value = $combined['dkdcplus:trl'] ?? [];
          break;
      }

      if (is_array($value) && !empty($value)) {
        $replacements[$original] = implode(', ', $value);
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
        case 'ding_seo_extent':
          $extent = $ting_object->getTingObject()->getExtent();
          // Is it always array? Is there an error in OpenSearchTingObject we
          // should fix?
          if (is_array($extent)) {
            $extent = reset($extent);
          }

          // The format is "<hh> t. <mm> min.", but can have variations:
          // - 2 t. 26 min.
          // - 88 min.
          // - 82 min.
          // - ca. 3 t., 15 min.
          // - 2 t., 10 min.
          // - Ca. 97 min.
          // We use two capture groups to capture the value and unit separately.
          $pattern = '/(\d+)\s*(t|min)/';
          if (preg_match_all($pattern, $extent, $matches)) {
            $hours = 0;
            $minutes = 0;
            foreach ($matches[1] as $key => $value) {
              $unit = $matches[2][$key];
              if ($unit == 't') {
                $hours += $value;
              }
              else {
                $minutes += $value;
              }
            }
            $hours += floor($minutes / 60);
            $minutes = $minutes % 60;

            // ISO 8601 duration.
            // See: https://en.wikipedia.org/wiki/ISO_8601#Durations
            $replacements[$original] = "PT{$hours}H{$minutes}M";
          }
          break;

      }
    }
  }

  if ($type == 'node' && !empty($data['node'])) {
    // Get library data entity referenced from events.
    $library_data = NULL;
    if ($data["node"]->type == "ding_event") {
      $og = og_get_entity_groups('node', $data['node']);
      foreach ($og['node'] as $nid) {
        $og_node = node_load($nid);
        if ($og_node->type == 'ding_library') {
          $library_data = $og_node;
          break;
        }
      }
    }

    // Get logo dimensions.
    global $base_url;
    drupal_theme_initialize();
    $logo_url = theme_get_setting('logo');
    if (!empty($logo_url)) {
      // Get relative internal for getimagesize. Add 1 to remove leading slash.
      $logo_path = drupal_substr($logo_url, drupal_strlen($base_url) + 1);
      $logo_info = getimagesize($logo_path);
      $logo_width = $logo_info[0];
      $logo_height = $logo_info[1];
    }

    foreach ($tokens as $name => $original) {
      switch ($name) {
        // Location tokens.
        case 'ding_seo_node_tokens:postalCode':
          if ($data["node"]->type == "ding_library") {
            $replacements[$original] = $data["node"]->field_ding_library_addresse["und"][0]["postal_code"];
          }
          elseif (empty($data["node"]->field_ding_event_location["und"][0]["name_line"])) {
            $replacements[$original] = $library_data->field_ding_library_addresse["und"][0]["postal_code"];
          }
          else {
            $replacements[$original] = $data['node']->field_ding_event_location['und'][0]['postal_code'];
          }
          break;

        case 'ding_seo_node_tokens:streetAddress':
          if ($data["node"]->type == "ding_library") {
            $replacements[$original] = $data["node"]->field_ding_library_addresse["und"][0]["thoroughfare"];
          }
          elseif (empty($data["node"]->field_ding_event_location["und"][0]["name_line"])) {
            $replacements[$original] = $library_data->field_ding_library_addresse["und"][0]["thoroughfare"];
          }
          else {
            $replacements[$original] = $data['node']->field_ding_event_location['und'][0]['thoroughfare'];
          }
          break;

        case 'ding_seo_node_tokens:addressLocality':
          if ($data["node"]->type == "ding_library") {
            $replacements[$original] = $data["node"]->field_ding_library_addresse["und"][0]["locality"];
          }
          elseif (empty($data["node"]->field_ding_event_location["und"][0]["name_line"])) {
            $replacements[$original] = $library_data->field_ding_library_addresse["und"][0]["locality"];
          }
          else {
            $replacements[$original] = $data["node"]->field_ding_event_location["und"][0]["locality"];
          }
          break;

        case 'ding_seo_node_tokens:addressRegion':
          if ($data["node"]->type == "ding_library") {
            $replacements[$original] = $data["node"]->field_ding_library_addresse["und"][0]["region"];
          }
          elseif (empty($data["node"]->field_ding_event_location["und"][0]["name_line"])) {
            $replacements[$original] = $library_data->field_ding_library_addresse["und"][0]["region"];
          }
          else {
            $replacements[$original] = $data['node']->field_ding_event_location['und'][0]['region'];
          }
          break;

        case 'ding_seo_node_tokens:addressCountry':
          if ($data["node"]->type == "ding_library") {
            $replacements[$original] = $data["node"]->field_ding_library_addresse["und"][0]["country"];
          }
          elseif (empty($data["node"]->field_ding_event_location["und"][0]["name_line"])) {
            $replacements[$original] = $library_data->field_ding_library_addresse["und"][0]["country"];
          }
          else {
            $replacements[$original] = $data["node"]->field_ding_event_location["und"][0]["country"];
          }
          break;

        case 'ding_seo_node_tokens:longitude':
          if ($data["node"]->type == "ding_library") {
            $replacements[$original] = $data["node"]->field_ding_library_geocode["und"][0]["lon"];
          }
          elseif (empty($data["node"]->field_ding_event_location["und"][0]["name_line"])) {
            $replacements[$original] = $library_data->field_ding_library_geocode["und"][0]["lon"];
          }
          else {
            $replacements[$original] = "long";
          }
          break;

        case 'ding_seo_node_tokens:latitude':
          if ($data["node"]->type == "ding_library") {
            $replacements[$original] = $data["node"]->field_ding_library_geocode["und"][0]["lat"];
          }
          elseif (empty($data["node"]->field_ding_event_location["und"][0]["name_line"])) {
            $replacements[$original] = $library_data->field_ding_library_geocode["und"][0]["lat"];
          }
          else {
            $replacements[$original] = "lat";
          }
          break;

        case 'ding_seo_node_tokens:location_name':
          if (empty($data["node"]->field_ding_event_location["und"][0]["name_line"])) {
            $replacements[$original] = $library_data->title;
          }
          else {
            $replacements[$original] = $data["node"]->field_ding_event_location["und"][0]["name_line"];
          }
          break;

        case 'ding_seo_node_tokens:location_url':
          if (!empty($library_data)) {
            $replacements[$original] = $_SERVER['REQUEST_SCHEME'] . '://'.$_SERVER['HTTP_HOST'] . "/node/" . $library_data->nid;
          }
          else {
            $replacements[$original] = "";
          }
          break;

        // Logo image dimensions.
        case 'ding_seo_node_tokens:logo_height':
          if (isset($logo_height))  {
            $replacements[$original] = $logo_height;
          }
          break;
        case 'ding_seo_node_tokens:logo_width':
          if (isset($logo_width)) {
            $replacements[$original] = $logo_width;
          }
          break;

        // Event date formatting.
        case 'ding_seo_node_tokens:event_startdate':
          $replacements[$original] = $data["node"]->field_ding_event_date["und"][0]["value"];
          break;
        case 'ding_seo_node_tokens:event_enddate':
          $replacements[$original] = $data["node"]->field_ding_event_date["und"][0]["value2"];
          break;

        // Event extras.
        case 'ding_seo_node_tokens:event_free':
          if (empty($data["node"]->field_ding_event_price) || $data["node"]->field_ding_event_price["und"][0]["value"] == 0) {
            $replacements[$original] = true;
          }
          else {
            $replacements[$original] = false;
          }
          break;

        // Language.
        case 'ding_seo_node_tokens:language':
          if ($data["node"]->language == "und") {
            $replacements[$original] = "dk";
          }
          else {
            $replacements[$original] = $data["node"]->language;
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
    // Let the token callback do its thing.
    $value = $callback($object);

    // Handle array values.
    if (is_array($value)) {
      $value = reset($value);
    }

    // Handle empty values and commas. See comment at metatag_views_alter
    // implementation for more info on why we do this.
    if (empty($value)) {
      $value = DING_SEO_EMPTY_PIVOT_VALUE;
    }
    else {
      $value = str_replace(',', DING_SEO_COMMA_PIVOT_VALUE, $value);
    }

    return $value;
  }, $objects));
}
