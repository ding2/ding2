<?php

/**
 * @file
 * Token callbacks for Ding SEO module.
 */

 /**
 * Implements hook_token_info()
 */
function ding_seo_token_info() {
  // Define ding_seo_node_tokens token type.
  $info['types']['ding_seo_node_tokens'] = [
    'name' => t('Ding SEO node tokens'),
    'description' => t('Group of node tokens defined by Ding SEO for use in structured data'),
    'needs-data' => 'node',
  ];
  $info['tokens']['node']['ding_seo_node_tokens'] = array(
    'name' => t("Ding SEO node tokens"),
    'description' => t('Group of node tokens defined by Ding SEO for use in structured data'),
    'type' => 'ding_seo_node_tokens',
  );
  // Define tokens supported on ding_seo_node_tokens.
  $info['tokens']['ding_seo_node_tokens']['location_name'] = array(
    'name' => t("Location Name"),
    'description' => t('The name of the location'),
  );

  $info['tokens']['ding_seo_node_tokens']['location_url'] = [
    'name' => t("Location Url"),
    'description' => t('The URL of the location'),
  ];
  $info['tokens']['ding_seo_node_tokens']['postalCode'] = [
    'name' => t("Postal Code"),
    'description' => t('Postal Code of the location'),
  ];
  $info['tokens']['ding_seo_node_tokens']['streetAddress'] = [
    'name' => t("Street Address"),
    'description' => t('Street Address of the location'),
  ];
  $info['tokens']['ding_seo_node_tokens']['addressLocality'] = [
    'name' => t("Address Locality"),
    'description' => t('City area of the location'),
  ];
  $info['tokens']['ding_seo_node_tokens']['addressCountry'] = [
    'name' => t("Address Country"),
    'description' => t('Country of the location'),
  ];

  // Logo dimensions and URL tokens
  $info['tokens']['ding_seo_node_tokens']['logo_width'] = [
    'name' => t("Logo width"),
    'description' => t('Width of the logo'),
  ];
  $info['tokens']['ding_seo_node_tokens']['logo_height'] = [
    'name' => t("Logo height"),
    'description' => t('Height of the logo'),
  ];
  $info['tokens']['ding_seo_node_tokens']['logo_url'] = [
    'name' => t("Logo URL"),
    'description' => t('URL of the logo'),
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
    'description' => t('Language of the node'),
  ];

  return $info;
}

/**
 * Implements hook_tokens().
 */
function ding_seo_tokens($type, $tokens, array $data, array $options) {
  $replacements = [];

  if ($type == 'node' && !empty($data['node'])) {
    // Get ding_library entity referenced from events.
    $library_data = NULL;
    if ($data['node']->type == 'ding_event') {
      $ding_library_nids = og_get_entity_groups('node', $data['node'], [OG_STATE_ACTIVE], 'og_group_ref');
      $ding_library_nid = reset($ding_library_nids['node']);
      $library_data = node_load($ding_library_nid);
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
          if (empty($data["node"]->field_ding_event_location["und"][0]["name_line"])) {
            $replacements[$original] = $library_data->field_ding_library_addresse["und"][0]["postal_code"];
          }
          else {
            $replacements[$original] = $data['node']->field_ding_event_location['und'][0]['postal_code'];
          }
          break;

        case 'ding_seo_node_tokens:streetAddress':
          if (empty($data["node"]->field_ding_event_location["und"][0]["name_line"])) {
            $replacements[$original] = $library_data->field_ding_library_addresse["und"][0]["thoroughfare"];
          }
          else {
            $replacements[$original] = $data['node']->field_ding_event_location['und'][0]['thoroughfare'];
          }
          break;

        case 'ding_seo_node_tokens:addressLocality':
          if (empty($data["node"]->field_ding_event_location["und"][0]["name_line"])) {
            $replacements[$original] = $library_data->field_ding_library_addresse["und"][0]["locality"];
          }
          else {
            $replacements[$original] = $data["node"]->field_ding_event_location["und"][0]["locality"];
          }
          break;

        case 'ding_seo_node_tokens:addressCountry':
          if (empty($data["node"]->field_ding_event_location["und"][0]["name_line"])) {
            $replacements[$original] = $library_data->field_ding_library_addresse["und"][0]["country"];
          }
          else {
            $replacements[$original] = $data["node"]->field_ding_event_location["und"][0]["country"];
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
        case 'ding_seo_node_tokens:logo_url':
          if (isset($logo_url)) {
            $replacements[$original] = $logo_url;
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
