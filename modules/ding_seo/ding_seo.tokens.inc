<?php

/**
 * @file
 * Token callbacks for Ding SEO module.
 */

 /**
 * Implements hook_token_info()
 */
function ding_seo_token_info() {
  // Token type
  $info['types']['ding_seo_node_tokens'] = [
    'name' => t('Ding SEO node tokens'),
    'description' => t('Special node tokens defined by Ding SEO for use in structured data'),
    'needs-data' => 'node',
  ];

  // Token type label
  $info['tokens']['node']['ding_seo_node_tokens'] = array(
    'name' => t("Ding SEO node tokens"),
    'description' => t('Special node tokens defined by Ding SEO for use in structured data'),
    'type' => 'ding_seo_node_tokens',
  );

  // Tokens
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

  if ($type == 'node' && !empty($data['node'])) {
    // get library data entity referenced from events
    if ($data["node"]->type == "ding_event") {
        $og = og_get_entity_groups('node', $data['node']);
        $library_data = node_load($og["node"][5]);
    }

    // get logo dimensions
    $logo_path = theme_get_setting('logo', 'ddbasic');
    $logo_info = getimagesize($logo_path);
    $logo_width = $logo_info[0];
    $logo_height = $logo_info[1];

    foreach ($tokens as $name => $original) {
        switch ($name) {
            // location tokens
            case 'ding_seo_node_tokens:postalCode':
                if ($data["node"]->type == "ding_library") {
                    $replacements[$original] = $data["node"]->field_ding_library_addresse["und"][0]["postal_code"];
                } else if (empty($data["node"]->field_ding_event_location["und"][0]["name_line"])) {
                    $replacements[$original] = $library_data->field_ding_library_addresse["und"][0]["postal_code"];
                } else {
                    $replacements[$original] = $data['node']->field_ding_event_location['und'][0]['postal_code'];
                }
                break;

            case 'ding_seo_node_tokens:streetAddress':
                if ($data["node"]->type == "ding_library") {
                    $replacements[$original] = $data["node"]->field_ding_library_addresse["und"][0]["thoroughfare"];
                } else if (empty($data["node"]->field_ding_event_location["und"][0]["name_line"])) {
                    $replacements[$original] = $library_data->field_ding_library_addresse["und"][0]["thoroughfare"];
                } else {
                    $replacements[$original] = $data['node']->field_ding_event_location['und'][0]['thoroughfare'];
                }
                break;

            case 'ding_seo_node_tokens:addressLocality':
                if ($data["node"]->type == "ding_library") {
                    $replacements[$original] = $data["node"]->field_ding_library_addresse["und"][0]["locality"];
                } else if (empty($data["node"]->field_ding_event_location["und"][0]["name_line"])) {
                    $replacements[$original] = $library_data->field_ding_library_addresse["und"][0]["locality"];
                } else {
                    $replacements[$original] = $data["node"]->field_ding_event_location["und"][0]["locality"];
                }
                break;

            case 'ding_seo_node_tokens:addressRegion':
                if ($data["node"]->type == "ding_library") {
                    $replacements[$original] = $data["node"]->field_ding_library_addresse["und"][0]["region"];
                } else if (empty($data["node"]->field_ding_event_location["und"][0]["name_line"])) {
                    $replacements[$original] = $library_data->field_ding_library_addresse["und"][0]["region"];
                } else {
                    $replacements[$original] = $data['node']->field_ding_event_location['und'][0]['region'];
                }
                break;

            case 'ding_seo_node_tokens:addressCountry':
                if ($data["node"]->type == "ding_library") {
                    $replacements[$original] = $data["node"]->field_ding_library_addresse["und"][0]["country"];
                } else if (empty($data["node"]->field_ding_event_location["und"][0]["name_line"])) {
                    $replacements[$original] = $library_data->field_ding_library_addresse["und"][0]["country"];
                } else {
                    $replacements[$original] = $data["node"]->field_ding_event_location["und"][0]["country"];
                }
                break;

            case 'ding_seo_node_tokens:longitude':
                if ($data["node"]->type == "ding_library") {
                    $replacements[$original] = $data["node"]->field_ding_library_geocode["und"][0]["lon"];
                } else if (empty($data["node"]->field_ding_event_location["und"][0]["name_line"])) {
                    $replacements[$original] = $library_data->field_ding_library_geocode["und"][0]["lon"];
                } else {
                    $replacements[$original] = "long";
                }
                break;

            case 'ding_seo_node_tokens:latitude':
                if ($data["node"]->type == "ding_library") {
                    $replacements[$original] = $data["node"]->field_ding_library_geocode["und"][0]["lat"];
                } else if (empty($data["node"]->field_ding_event_location["und"][0]["name_line"])) {
                    $replacements[$original] = $library_data->field_ding_library_geocode["und"][0]["lat"];
                } else {
                    $replacements[$original] = "lat";
                }
                break;

            case 'ding_seo_node_tokens:location_name':
                if (empty($data["node"]->field_ding_event_location["und"][0]["name_line"])) {
                    $replacements[$original] = $library_data->title;
                } else {
                    $replacements[$original] = $data["node"]->field_ding_event_location["und"][0]["name_line"];
                }
                break;

            case 'ding_seo_node_tokens:location_url':
                if (!empty($library_data)) {
                    $replacements[$original] = $_SERVER['REQUEST_SCHEME'] . '://'.$_SERVER['HTTP_HOST'] . "/node/" . $library_data->nid;
                } else {
                    $replacements[$original] = "";
                }
                break;

            // logo image dimensions
            case 'ding_seo_node_tokens:logo_height':
                $replacements[$original] = $logo_height;
                break;
            case 'ding_seo_node_tokens:logo_width':
                $replacements[$original] = $logo_width;
                break;

            // event date formatting
            case 'ding_seo_node_tokens:event_startdate':
                $replacements[$original] = $data["node"]->field_ding_event_date["und"][0]["value"];
                break;
            case 'ding_seo_node_tokens:event_enddate':
                $replacements[$original] = $data["node"]->field_ding_event_date["und"][0]["value2"];
                break;

            // event extras
            case 'ding_seo_node_tokens:event_free':
                if (empty($data["node"]->field_ding_event_price) || $data["node"]->field_ding_event_price["und"][0]["value"] == 0) {
                    $replacements[$original] = true;
                } else {
                    $replacements[$original] = false;
                }
                break;

            // language

            case 'ding_seo_node_tokens:language':
                if ($data["node"]->language == "und") {
                    $replacements[$original] = "dk";
                } else {
                    $replacements[$original] = $data["node"]->language;
                }
                break;

        }
    }
  }
  return $replacements;
}
