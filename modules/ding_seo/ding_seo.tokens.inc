<?php

function ding_seo_token_info()
{
    $type = [
        'name' => t('Ding Seo'),
        'description' => t('Tokens for structured data as JSON LD.'),
    ];
    $node['location_name'] = [
        'name' => t("location_name"),
        'description' => t('location_name'),
    ];
    $node['location_url'] = [
        'name' => t("location_url"),
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
    $node['image_url'] = [
        'name' => t("image_url"),
        'description' => t('image_url'),
    ];
    $node['image_width'] = [
        'name' => t("image_width"),
        'description' => t('image_width'),
    ];
    $node['image_height'] = [
        'name' => t("image_width_height"),
        'description' => t('image_width_height'),
    ];
    $node['logo_width'] = [
        'name' => t("logo_width"),
        'description' => t('logo_width'),
    ];
    $node['logo_height'] = [
        'name' => t("logo_height"),
        'description' => t('logo_height'),
    ];
    $node['event_startdate'] = [
        'name' => t("event_startdate"),
        'description' => t('event_startdate'),
    ];
    $node['event_enddate'] = [
        'name' => t("event_enddate"),
        'description' => t('event_enddate'),
    ];
    $node['event_free'] = [
        'name' => t("event_free"),
        'description' => t('event_free'),
    ];
    $node['language'] = [
        'name' => t("language"),
        'description' => t('language'),
    ];
    return [
        'types' => ['dingseotoken' => $type],
        'tokens' => ['dingseotoken' => $node],
    ];
}

function ding_seo_tokens($type, $tokens, array $data, array $options)
{
    $replacements = [];

    if ($type == 'dingseotoken' && !empty($data['node'])) {

        // get title image
        $image = field_get_items('node', $data['node'], 'field_ding_event_title_image');

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

                // location information
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
                        $replacements[$original] = $data["node"]->field_ding_library_addresse["und"][0]["postal_code"];
                    } else if (empty($data["node"]->field_ding_event_location["und"][0]["name_line"])) {
                        $replacements[$original] = "LIBRARY";
                    } else {
                        $replacements[$original] = "region";
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
                    if (empty($data["node"]->field_ding_event_location["und"][0]["name_line"])) {
                        $replacements[$original] = "LIBRARY";
                    } else {
                        $replacements[$original] = "lat";
                    }
                    break;

                // images dimensions
                case 'image_url':
                    $replacements[$original] = drupal_realpath($data["node"]->field_ding_event_list_image["und"][0]["uri"]);
                    break;
                case 'image_width':
                    if ($data["node"]->type == "ding_news") {
                        $replacements[$original] = $data["node"]->field_ding_news_list_image["und"][0]["width"];
                    } else {
                        $replacements[$original] = $data["node"]->field_ding_event_list_image["und"][0]["width"];
                    }
                    break;
                case 'image_height':
                    if ($data["node"]->type == "ding_news") {
                        $replacements[$original] = $data["node"]->field_ding_news_list_image["und"][0]["height"];
                    } else {
                        $replacements[$original] = $data["node"]->field_ding_event_list_image["und"][0]["height"];
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
