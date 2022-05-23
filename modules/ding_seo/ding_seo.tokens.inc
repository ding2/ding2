<?php

/**
 * @file
 * Token callbacks for Ding SEO module.
 */

/**
 * Implements hook_token_info().
 */
function ding_seo_token_info() {
  // Define ding_seo_node_tokens token type.
  $info['types']['ding_seo_node_tokens'] = [
    'name' => t('Ding SEO node tokens'),
    'description' => t('Group of node tokens defined by Ding SEO for use in structured data'),
    'needs-data' => 'node',
  ];
  $info['types']['ding_seo_logo_tokens'] = [
    'name' => t('Ding SEO logo tokens'),
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
  $info['tokens']['ding_seo_node_tokens']['postal_code'] = [
    'name' => t("Postal Code"),
    'description' => t('Postal Code of the location'),
  ];
  $info['tokens']['ding_seo_node_tokens']['street_address'] = [
    'name' => t("Street Address"),
    'description' => t('Street Address of the location'),
  ];
  $info['tokens']['ding_seo_node_tokens']['address_locality'] = [
    'name' => t("Address Locality"),
    'description' => t('City area of the location'),
  ];
  $info['tokens']['ding_seo_node_tokens']['address_country'] = [
    'name' => t("Address Country"),
    'description' => t('Country of the location'),
  ];

  // Ding SEO logo tokens.
  $info['tokens']['ding_seo_logo_tokens']['width'] = [
    'name' => t("Logo width"),
    'description' => t('Width of the logo'),
  ];
  $info['tokens']['ding_seo_logo_tokens']['height'] = [
    'name' => t("Logo height"),
    'description' => t('Height of the logo'),
  ];
  $info['tokens']['ding_seo_logo_tokens']['url'] = [
    'name' => t("Logo URL"),
    'description' => t('URL of the logo'),
  ];

  return $info;
}

/**
 * Implements hook_tokens().
 */
function ding_seo_tokens($type, $tokens, array $data, array $options) {
  $replacements = [];
  $ding_seo_node_tokens = [];

  if ($type == 'node') {
    $ding_seo_node_tokens = token_find_with_prefix($tokens, 'ding_seo_node_tokens');
  }

  if (!empty($ding_seo_node_tokens) && !empty($data['node'])) {
    $node = $data['node'];
    /** @var \EntityDrupalWrapper */
    $node_wrapper = entity_metadata_wrapper('node', $node);

    // Determine if we should get location data from referenced ding_library
    // node for ding_events.
    $library_node_wrapper = NULL;
    if ($node->type == 'ding_event' && empty($node_wrapper->field_ding_event_location->name_line->value())) {
      // Get the referenced ding_library node.
      $ding_library_nids = og_get_entity_groups('node', $node, [OG_STATE_ACTIVE], 'og_group_ref');
      $ding_library_nid = reset($ding_library_nids['node']);
      $library_node = node_load($ding_library_nid);
      /** @var \EntityDrupalWrapper */
      $library_node_wrapper = entity_metadata_wrapper('node', $library_node);
    }

    foreach ($ding_seo_node_tokens as $name => $original) {
      switch ($name) {
        // Location tokens.
        case 'postal_code':
          if (isset($library_node_wrapper)) {
            $replacements[$original] = $library_node_wrapper->field_ding_library_addresse->postal_code->value();
          }
          else {
            $replacements[$original] = $node_wrapper->field_ding_event_location->postal_code->value();
          }
          break;

        case 'street_address':
          if (isset($library_node_wrapper)) {
            $replacements[$original] = $library_node_wrapper->field_ding_library_addresse->thoroughfare->value();
          }
          else {
            $replacements[$original] = $node_wrapper->field_ding_event_location->thoroughfare->value();
          }
          break;

        case 'address_locality':
          if (isset($library_node_wrapper)) {
            $replacements[$original] = $library_node_wrapper->field_ding_library_addresse->locality->value();
          }
          else {
            $replacements[$original] = $node_wrapper->field_ding_event_location->locality->value();
          }
          break;

        case 'address_country':
          if (isset($library_node_wrapper)) {
            $replacements[$original] = $library_node_wrapper->field_ding_library_addresse->country->value();
          }
          else {
            $replacements[$original] = $node_wrapper->field_ding_event_location->country->value();
          }
          break;

        case 'location_name':
          if (isset($library_node_wrapper)) {
            $replacements[$original] = $library_node_wrapper->field_ding_library_addresse->name_line->value();
          }
          else {
            $replacements[$original] = $node_wrapper->field_ding_event_location->name_line->value();
          }
          break;

        case 'location_url':
          if (isset($library_node_wrapper)) {
            $replacements[$original] = url('node/' . $library_node_wrapper->getIdentifier(), [
              'absolute' => TRUE,
            ]);
          }
          break;
      }
    }
  }

  if ($type == 'ding_seo_logo_tokens') {
    // Get logo URL and dimensions.
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
        case 'height':
          if (isset($logo_height)) {
            $replacements[$original] = $logo_height;
          }
          break;

        case 'width':
          if (isset($logo_width)) {
            $replacements[$original] = $logo_width;
          }
          break;

        case 'url':
          if (isset($logo_url)) {
            $replacements[$original] = $logo_url;
          }
          break;
      }
    }
  }

  return $replacements;
}
