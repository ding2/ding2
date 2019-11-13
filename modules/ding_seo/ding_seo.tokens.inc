<?php

/**
 * Implements hook_token_info().
 * 
 * Custom tokens for JSON LD. 
 * A new token type 'Ding Seo' is added to give easier access to the tokens from the UI.  
 * Tokens is defined with this hook, content is added later with hook_tokens()
 * 
 */

function ding_seo_token_info()
{
    $type = [
        'name' => t('Ding Seo'),
        'description' => t('Tokens for structured data as JSON LD.'),
    ];

    // Location tokens
    $node['location_name'] = [
        'name' => t("Location Name"),
        'description' => t('The location is the '),
    ];
    $node['location_url'] = [
        'name' => t("Location Url"),
        'description' => t('location_url'),
    ];
    $node['postalCode'] = [
        'name' => t("Postal Code"),
        'description' => t('Postal Code'),
    ];
    $node['streetAddress'] = [
        'name' => t("Street Address"),
        'description' => t('Street Address'),
    ];
    $node['addressLocality'] = [
        'name' => t("Address Locality"),
        'description' => t('Address Locality'),
    ];
    $node['addressRegion'] = [
        'name' => t("Address Region"),
        'description' => t('Address Region'),
    ];
    $node['addressCountry'] = [
        'name' => t("Address Country"),
        'description' => t('Address Country'),
    ];
    $node['longitude'] = [
        'name' => t("longitude"),
        'description' => t('longitude'),
    ];
    $node['latitude'] = [
        'name' => t("latitude"),
        'description' => t('latitude'),
    ];
  
    // Logo dimensions tokens
    $node['logo_width'] = [
        'name' => t("logo_width"),
        'description' => t('logo_width'),
    ];
    $node['logo_height'] = [
        'name' => t("logo_height"),
        'description' => t('logo_height'),
    ];

    // Event data formatting
    $node['event_startdate'] = [
        'name' => t("Event Startdate"),
        'description' => t('Event enddate in YYYY-MM-DD HH:MM::SS format'),
    ];
    $node['event_enddate'] = [
        'name' => t("Event Enddate"),
        'description' => t('Event enddate in YYYY-MM-DD HH:MM::SS format'),
    ];
    $node['event_free'] = [
        'name' => t("Event Free Boolean"),
        'description' => t('Boolean of whether the event is free or not '),
    ];

    // Language
    $node['language'] = [
        'name' => t("language"),
        'description' => t('language'),
    ];

    // Returns the new token type as well as the tokens
    return [
        'types' => ['dingseotoken' => $type],
        'tokens' => ['dingseotoken' => $node],
    ];
}

/**
 * Implements hook_tokens().
 * 
 * Add content to the tokens.
 * 
 */

function ding_seo_tokens($type, $tokens, array $data, array $options)
{
    $replacements = [];

    if ($type == 'dingseotoken' && !empty($data['node'])) {

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
                case 'postalCode':
                    if ($data["node"]->type == "ding_library") {
                        $replacements[$original] = $data["node"]->field_ding_library_addresse["und"][0]["postal_code"];
                    } else if (empty($data["node"]->field_ding_event_location["und"][0]["name_line"])) {
                        $replacements[$original] = $library_data->field_ding_library_addresse["und"][0]["postal_code"];
                    } else {
                        $replacements[$original] = $data['node']->field_ding_event_location['und'][0]['postal_code'];
                    }
                    break;

                case 'streetAddress':
                    if ($data["node"]->type == "ding_library") {
                        $replacements[$original] = $data["node"]->field_ding_library_addresse["und"][0]["thoroughfare"];
                    } else if (empty($data["node"]->field_ding_event_location["und"][0]["name_line"])) {
                        $replacements[$original] = $library_data->field_ding_library_addresse["und"][0]["thoroughfare"];
                    } else {
                        $replacements[$original] = $data['node']->field_ding_event_location['und'][0]['thoroughfare'];
                    }
                    break;

                case 'addressLocality':
                    if ($data["node"]->type == "ding_library") {
                        $replacements[$original] = $data["node"]->field_ding_library_addresse["und"][0]["locality"];
                    } else if (empty($data["node"]->field_ding_event_location["und"][0]["name_line"])) {
                        $replacements[$original] = $library_data->field_ding_library_addresse["und"][0]["locality"];
                    } else {
                        $replacements[$original] = $data["node"]->field_ding_event_location["und"][0]["locality"];
                    }
                    break;

                case 'addressRegion':
                    if ($data["node"]->type == "ding_library") {
                        $replacements[$original] = $data["node"]->field_ding_library_addresse["und"][0]["region"];
                    } else if (empty($data["node"]->field_ding_event_location["und"][0]["name_line"])) {
                        $replacements[$original] = $library_data->field_ding_library_addresse["und"][0]["region"];
                    } else {
                        $replacements[$original] = $data['node']->field_ding_event_location['und'][0]['region'];
                    }
                    break;

                case 'addressCountry':
                    if ($data["node"]->type == "ding_library") {
                        $replacements[$original] = $data["node"]->field_ding_library_addresse["und"][0]["country"];
                    } else if (empty($data["node"]->field_ding_event_location["und"][0]["name_line"])) {
                        $replacements[$original] = $library_data->field_ding_library_addresse["und"][0]["country"];
                    } else {
                        $replacements[$original] = $data["node"]->field_ding_event_location["und"][0]["country"];
                    }
                    break;

                case 'longitude':
                    if ($data["node"]->type == "ding_library") {
                        $replacements[$original] = $data["node"]->field_ding_library_geocode["und"][0]["lon"];
                    } else if (empty($data["node"]->field_ding_event_location["und"][0]["name_line"])) {
                        $replacements[$original] = $library_data->field_ding_library_geocode["und"][0]["lon"];
                    } else {
                        $replacements[$original] = "long";
                    }
                    break;

                case 'latitude':
                    if ($data["node"]->type == "ding_library") {
                        $replacements[$original] = $data["node"]->field_ding_library_geocode["und"][0]["lat"];
                    } else if (empty($data["node"]->field_ding_event_location["und"][0]["name_line"])) {
                        $replacements[$original] = $library_data->field_ding_library_geocode["und"][0]["lat"];
                    } else {
                        $replacements[$original] = "lat";
                    }
                    break;

                case 'location_name':
                    if (empty($data["node"]->field_ding_event_location["und"][0]["name_line"])) {
                        $replacements[$original] = $library_data->title;
                    } else {
                        $replacements[$original] = $data["node"]->field_ding_event_location["und"][0]["name_line"];
                    }
                    break;

                case 'location_url':
                    if (!empty($library_data)) {
                        //echo var_dump($library_data);
                        //exit(1);
                        $replacements[$original] = $_SERVER['REQUEST_SCHEME'] . '://'.$_SERVER['HTTP_HOST'] . "/node/" . $library_data->nid;
                    } else {
                        $replacements[$original] = "";
                    }
                    break;

                // logo image dimensions
                case 'logo_height':
                    $replacements[$original] = $logo_height;
                    break;
                case 'logo_width':
                    $replacements[$original] = $logo_width;
                    break;

                // event date formatting
                case 'event_startdate':
                    $replacements[$original] = $data["node"]->field_ding_event_date["und"][0]["value"];
                    break;
                case 'event_enddate':
                    $replacements[$original] = $data["node"]->field_ding_event_date["und"][0]["value2"];
                    break;

                // event extras
                case 'event_free':
                    if (empty($data["node"]->field_ding_event_price) || $data["node"]->field_ding_event_price["und"][0]["value"] == 0) {
                        $replacements[$original] = true;
                    } else {
                        $replacements[$original] = false;
                    }
                    break;

                // language

                case 'language':
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
