<?php
/**
 * @file
 * ding_frontend.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function ding_frontend_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "field_group" && $api == "field_group") {
    return array("version" => "1");
  }
  if ($module == "menu_block" && $api == "menu_block") {
    return array("version" => "1");
  }
  if ($module == "page_manager" && $api == "pages_default") {
    return array("version" => "1");
  }
  if ($module == "pm_existing_pages" && $api == "pm_existing_pages") {
    return array("version" => "1");
  }
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_views_api().
 */
function ding_frontend_views_api($module = NULL, $api = NULL) {
  return array("api" => "3.0");
}

/**
 * Implements hook_image_default_styles().
 */
function ding_frontend_image_default_styles() {
  $styles = array();

  // Exported image style: crop_16_9.
  $styles['crop_16_9'] = array(
    'label' => 'Crop 16:9',
    'effects' => array(
      2 => array(
        'name' => 'manualcrop_crop',
        'data' => array(
          'width' => 356,
          'height' => 200,
          'keepproportions' => 1,
          'reuse_crop_style' => 'crop_unconstrained',
          'style_name' => 'crop_16_9',
        ),
        'weight' => 0,
      ),
    ),
  );

  // Exported image style: crop_22_9.
  $styles['crop_22_9'] = array(
    'label' => 'Crop 22:9',
    'effects' => array(
      15 => array(
        'name' => 'manualcrop_crop',
        'data' => array(
          'width' => 855,
          'height' => 350,
          'keepproportions' => 1,
          'reuse_crop_style' => 'crop_16_9',
          'style_name' => 'crop_22_9',
        ),
        'weight' => 0,
      ),
    ),
  );

  // Exported image style: crop_4_3.
  $styles['crop_4_3'] = array(
    'label' => 'Crop 4:3',
    'effects' => array(
      6 => array(
        'name' => 'manualcrop_crop',
        'data' => array(
          'width' => 200,
          'height' => 150,
          'keepproportions' => 1,
          'reuse_crop_style' => '',
          'style_name' => 'crop_4_3',
        ),
        'weight' => 0,
      ),
    ),
  );

  // Exported image style: crop_unconstrained.
  $styles['crop_unconstrained'] = array(
    'label' => 'Crop unconstrained',
    'effects' => array(
      3 => array(
        'name' => 'manualcrop_crop',
        'data' => array(
          'width' => '',
          'height' => '',
          'keepproportions' => 0,
          'reuse_crop_style' => '',
          'style_name' => 'crop_unconstrained',
        ),
        'weight' => 0,
      ),
    ),
  );

  // Exported image style: ding_attachment_large.
  $styles['ding_attachment_large'] = array(
    'effects' => array(
      6 => array(
        'name' => 'image_scale',
        'data' => array(
          'width' => 500,
          'height' => '',
          'upscale' => 1,
        ),
        'weight' => 1,
      ),
    ),
    'label' => 'ding_attachment_large',
  );

  // Exported image style: ding_attachment_medium.
  $styles['ding_attachment_medium'] = array(
    'effects' => array(
      7 => array(
        'name' => 'image_scale',
        'data' => array(
          'width' => 500,
          'height' => '',
          'upscale' => 1,
        ),
        'weight' => 1,
      ),
    ),
    'label' => 'ding_attachment_medium',
  );

  // Exported image style: ding_attachment_small.
  $styles['ding_attachment_small'] = array(
    'effects' => array(
      8 => array(
        'name' => 'image_scale',
        'data' => array(
          'width' => 500,
          'height' => '',
          'upscale' => 1,
        ),
        'weight' => 1,
      ),
    ),
    'label' => 'ding_attachment_small',
  );

  // Exported image style: ding_full_width.
  $styles['ding_full_width'] = array(
    'label' => 'Ding full width',
    'effects' => array(
      1 => array(
        'name' => 'manualcrop_reuse',
        'data' => array(
          'reuse_crop_style' => 'crop_16_9',
          'apply_all_effects' => 0,
        ),
        'weight' => 0,
      ),
      3 => array(
        'name' => 'image_scale_and_crop',
        'data' => array(
          'width' => 1124,
          'height' => 631,
        ),
        'weight' => 2,
      ),
    ),
  );

  // Exported image style: ding_list_large.
  $styles['ding_list_large'] = array(
    'label' => 'ding_list_large',
    'effects' => array(
      1 => array(
        'name' => 'image_scale',
        'data' => array(
          'width' => 740,
          'height' => '',
          'upscale' => 1,
        ),
        'weight' => 1,
      ),
    ),
  );

  // Exported image style: ding_list_medium.
  $styles['ding_list_medium'] = array(
    'label' => 'ding_list_medium',
    'effects' => array(
      27 => array(
        'name' => 'image_scale',
        'data' => array(
          'width' => 334,
          'height' => '',
          'upscale' => 1,
        ),
        'weight' => 1,
      ),
    ),
  );

  // Exported image style: ding_list_small.
  $styles['ding_list_small'] = array(
    'label' => 'ding_list_small',
    'effects' => array(
      3 => array(
        'name' => 'image_scale',
        'data' => array(
          'width' => 260,
          'height' => '',
          'upscale' => 1,
        ),
        'weight' => 1,
      ),
    ),
  );

  // Exported image style: ding_panorama_list_large.
  $styles['ding_panorama_list_large'] = array(
    'label' => 'ding_panorama_list_large',
    'effects' => array(
      10 => array(
        'name' => 'manualcrop_reuse',
        'data' => array(
          'reuse_crop_style' => 'crop_16_9',
          'apply_all_effects' => 0,
        ),
        'weight' => 0,
      ),
      5 => array(
        'name' => 'image_scale',
        'data' => array(
          'width' => 548,
          'height' => 308,
          'upscale' => 1,
        ),
        'weight' => 1,
      ),
    ),
  );

  // Exported image style: ding_panorama_list_medium.
  $styles['ding_panorama_list_medium'] = array(
    'label' => 'ding_panorama_list_medium',
    'effects' => array(
      18 => array(
        'name' => 'manualcrop_reuse',
        'data' => array(
          'reuse_crop_style' => 'crop_16_9',
          'apply_all_effects' => 0,
        ),
        'weight' => 0,
      ),
      19 => array(
        'name' => 'image_scale',
        'data' => array(
          'width' => 356,
          'height' => 200,
          'upscale' => 0,
        ),
        'weight' => 2,
      ),
    ),
  );

  // Exported image style: ding_panorama_list_small.
  $styles['ding_panorama_list_small'] = array(
    'label' => 'ding_panorama_list_small',
    'effects' => array(
      11 => array(
        'name' => 'manualcrop_reuse',
        'data' => array(
          'reuse_crop_style' => 'crop_16_9',
          'apply_all_effects' => 0,
        ),
        'weight' => 0,
      ),
      7 => array(
        'name' => 'image_scale',
        'data' => array(
          'width' => 260,
          'height' => 146,
          'upscale' => 1,
        ),
        'weight' => 1,
      ),
    ),
  );

  // Exported image style: ding_panorama_primary_large.
  $styles['ding_panorama_primary_large'] = array(
    'label' => 'ding_panorama_primary_large',
    'effects' => array(
      40 => array(
        'name' => 'manualcrop_crop',
        'data' => array(
          'width' => 1200,
          'height' => 300,
          'keepproportions' => 1,
          'reuse_crop_style' => '',
          'style_name' => 'ding_panorama_primary_large',
        ),
        'weight' => 0,
      ),
      39 => array(
        'name' => 'image_scale_and_crop',
        'data' => array(
          'width' => 1200,
          'height' => 300,
        ),
        'weight' => 1,
      ),
    ),
  );

  // Exported image style: ding_panorama_primary_medium.
  $styles['ding_panorama_primary_medium'] = array(
    'label' => 'ding_panorama_primary_medium',
    'effects' => array(
      42 => array(
        'name' => 'manualcrop_reuse',
        'data' => array(
          'reuse_crop_style' => 'ding_panorama_primary_large',
          'apply_all_effects' => 1,
        ),
        'weight' => 0,
      ),
      41 => array(
        'name' => 'image_scale_and_crop',
        'data' => array(
          'width' => 1000,
          'height' => 250,
        ),
        'weight' => 1,
      ),
    ),
  );

  // Exported image style: ding_panorama_primary_small.
  $styles['ding_panorama_primary_small'] = array(
    'label' => 'ding_panorama_primary_small',
    'effects' => array(
      44 => array(
        'name' => 'manualcrop_reuse',
        'data' => array(
          'reuse_crop_style' => 'ding_panorama_primary_large',
          'apply_all_effects' => 1,
        ),
        'weight' => 0,
      ),
      43 => array(
        'name' => 'image_scale_and_crop',
        'data' => array(
          'width' => 500,
          'height' => 125,
        ),
        'weight' => 1,
      ),
    ),
  );

  // Exported image style: ding_primary_large.
  $styles['ding_primary_large'] = array(
    'label' => 'ding_primary_large',
    'effects' => array(
      28 => array(
        'name' => 'manualcrop_reuse',
        'data' => array(
          'reuse_crop_style' => 'crop_22_9',
          'apply_all_effects' => 0,
        ),
        'weight' => 0,
      ),
      8 => array(
        'name' => 'image_scale',
        'data' => array(
          'width' => 855,
          'height' => '',
          'upscale' => 1,
        ),
        'weight' => 1,
      ),
    ),
  );

  // Exported image style: ding_primary_medium.
  $styles['ding_primary_medium'] = array(
    'label' => 'ding_primary_medium',
    'effects' => array(
      36 => array(
        'name' => 'manualcrop_reuse',
        'data' => array(
          'reuse_crop_style' => 'ding_primary_large',
          'apply_all_effects' => 1,
        ),
        'weight' => 0,
      ),
      35 => array(
        'name' => 'image_scale',
        'data' => array(
          'width' => 1000,
          'height' => '',
          'upscale' => 1,
        ),
        'weight' => 1,
      ),
    ),
  );

  // Exported image style: ding_primary_small.
  $styles['ding_primary_small'] = array(
    'label' => 'ding_primary_small',
    'effects' => array(
      38 => array(
        'name' => 'manualcrop_reuse',
        'data' => array(
          'reuse_crop_style' => 'ding_primary_large',
          'apply_all_effects' => 1,
        ),
        'weight' => 0,
      ),
      37 => array(
        'name' => 'image_scale',
        'data' => array(
          'width' => 500,
          'height' => '',
          'upscale' => 1,
        ),
        'weight' => 1,
      ),
    ),
  );

  // Exported image style: ding_secondary_large.
  $styles['ding_secondary_large'] = array(
    'label' => 'ding_secondary_large',
    'effects' => array(
      2 => array(
        'name' => 'manualcrop_reuse',
        'data' => array(
          'reuse_crop_style' => 'crop_unconstrained',
          'apply_all_effects' => 0,
        ),
        'weight' => 0,
      ),
      1 => array(
        'name' => 'image_scale',
        'data' => array(
          'width' => 900,
          'height' => '',
          'upscale' => 1,
        ),
        'weight' => 1,
      ),
    ),
  );

  // Exported image style: ding_secondary_medium.
  $styles['ding_secondary_medium'] = array(
    'effects' => array(
      13 => array(
        'name' => 'image_scale',
        'data' => array(
          'width' => 900,
          'height' => '',
          'upscale' => 1,
        ),
        'weight' => 1,
      ),
    ),
    'label' => 'ding_secondary_medium',
  );

  // Exported image style: ding_secondary_small.
  $styles['ding_secondary_small'] = array(
    'effects' => array(
      14 => array(
        'name' => 'image_scale',
        'data' => array(
          'width' => 500,
          'height' => '',
          'upscale' => 1,
        ),
        'weight' => 1,
      ),
    ),
    'label' => 'ding_secondary_small',
  );

  return $styles;
}

/**
 * Implements hook_default_search_api_index().
 */
function ding_frontend_default_search_api_index() {
  $items = array();
  $items['default_multiple_index'] = entity_import('search_api_index', '{
    "name" : "Default multiple index",
    "machine_name" : "default_multiple_index",
    "description" : null,
    "server" : "localhost_db",
    "item_type" : "multiple",
    "options" : {
      "datasource" : { "types" : [ "node", "user" ] },
      "index_directly" : 0,
      "cron_limit" : "50",
      "fields" : {
        "item_bundle" : { "type" : "string" },
        "item_id" : { "type" : "string" },
        "item_type" : { "type" : "string" },
        "node" : { "type" : "integer", "entity_type" : "node" },
        "node:author" : { "type" : "integer", "entity_type" : "user" },
        "node:changed" : { "type" : "date" },
        "node:created" : { "type" : "date" },
        "node:field_ding_event_category" : { "type" : "integer", "entity_type" : "taxonomy_term" },
        "node:field_ding_event_lead" : { "type" : "text" },
        "node:field_ding_event_tags" : { "type" : "list\\u003Cinteger\\u003E", "entity_type" : "taxonomy_term" },
        "node:field_ding_event_target" : { "type" : "integer", "entity_type" : "taxonomy_term" },
        "node:field_ding_group_lead" : { "type" : "text" },
        "node:field_ding_library_fax_number" : { "type" : "text" },
        "node:field_ding_library_lead" : { "type" : "text" },
        "node:field_ding_library_mail" : { "type" : "text" },
        "node:field_ding_library_phone_number" : { "type" : "text" },
        "node:field_ding_news_category" : { "type" : "integer", "entity_type" : "taxonomy_term" },
        "node:field_ding_news_lead" : { "type" : "text" },
        "node:field_ding_news_tags" : { "type" : "list\\u003Cinteger\\u003E", "entity_type" : "taxonomy_term" },
        "node:field_ding_page_lead" : { "type" : "text" },
        "node:field_ding_page_tags" : { "type" : "list\\u003Cinteger\\u003E", "entity_type" : "taxonomy_term" },
        "node:nid" : { "type" : "integer" },
        "node:title" : { "type" : "text", "boost" : "2.0" },
        "node:type" : { "type" : "string" },
        "node:url" : { "type" : "uri" },
        "search_api_language" : { "type" : "string" },
        "user" : { "type" : "integer", "entity_type" : "user" },
        "user:profile_ding_staff_profile" : { "type" : "integer", "entity_type" : "profile2" },
        "user:profile_ding_staff_profile:field_ding_staff_department" : { "type" : "list\\u003Cinteger\\u003E", "entity_type" : "taxonomy_term" },
        "user:profile_ding_staff_profile:field_ding_staff_email" : { "type" : "text" },
        "user:profile_ding_staff_profile:field_ding_staff_forename" : { "type" : "text", "boost" : "2.0" },
        "user:profile_ding_staff_profile:field_ding_staff_phone" : { "type" : "text" },
        "user:profile_ding_staff_profile:field_ding_staff_position" : { "type" : "text" },
        "user:profile_ding_staff_profile:field_ding_staff_surname" : { "type" : "text", "boost" : "2.0" },
        "user:profile_ding_staff_profile:field_ding_staff_work_areas" : { "type" : "text" },
        "user:relation_ting_reference_ting_object" : { "type" : "list\\u003Cinteger\\u003E", "entity_type" : "ting_object" },
        "user:roles" : { "type" : "list\\u003Cinteger\\u003E" },
        "user:status" : { "type" : "integer" },
        "user:uid" : { "type" : "integer" }
      },
      "data_alter_callbacks" : {
        "ding_frontend_published_filter" : { "status" : 1, "weight" : "-10", "settings" : [] },
        "ding_frontend_role_filter" : {
          "status" : 1,
          "weight" : "-10",
          "settings" : { "default" : "0", "match_type" : "partial", "roles" : { "9" : "9" } }
        },
        "ding_frontend_bundle_filter" : {
          "status" : 1,
          "weight" : "-10",
          "settings" : {
            "default" : "0",
            "bundles" : {
              "node:ding_eresource" : "node:ding_eresource",
              "node:ding_event" : "node:ding_event",
              "node:ding_group" : "node:ding_group",
              "node:ding_library" : "node:ding_library",
              "node:ding_news" : "node:ding_news",
              "node:ding_page" : "node:ding_page"
            }
          }
        },
        "search_api_alter_bundle_filter" : {
          "status" : 0,
          "weight" : "-10",
          "settings" : {
            "default" : "0",
            "bundles" : {
              "node:ding_event" : "node:ding_event",
              "node:ding_group" : "node:ding_group",
              "node:ding_library" : "node:ding_library",
              "node:ding_news" : "node:ding_news",
              "node:ding_page" : "node:ding_page"
            }
          }
        },
        "search_api_alter_add_url" : { "status" : 0, "weight" : "0", "settings" : [] },
        "search_api_alter_add_aggregation" : { "status" : 0, "weight" : "0", "settings" : [] },
        "search_api_alter_add_hierarchy" : { "status" : 0, "weight" : "0", "settings" : { "fields" : [] } },
        "search_api_alter_language_control" : {
          "status" : 0,
          "weight" : "0",
          "settings" : { "lang_field" : "", "languages" : [] }
        }
      },
      "processors" : {
        "search_api_case_ignore" : {
          "status" : 0,
          "weight" : "0",
          "settings" : { "fields" : {
              "node:title" : true,
              "node:field_ding_news_lead" : true,
              "node:field_ding_page_lead" : true,
              "node:field_ding_event_lead" : true,
              "node:field_ding_library_fax_number" : true,
              "node:field_ding_library_lead" : true,
              "node:field_ding_library_mail" : true,
              "node:field_ding_library_phone_number" : true,
              "node:field_ding_group_lead" : true
            }
          }
        },
        "search_api_html_filter" : {
          "status" : 0,
          "weight" : "10",
          "settings" : {
            "fields" : {
              "node:title" : true,
              "node:field_ding_news_lead" : true,
              "node:field_ding_page_lead" : true,
              "node:field_ding_event_lead" : true,
              "node:field_ding_library_fax_number" : true,
              "node:field_ding_library_lead" : true,
              "node:field_ding_library_mail" : true,
              "node:field_ding_library_phone_number" : true,
              "node:field_ding_group_lead" : true
            },
            "title" : 0,
            "alt" : 1,
            "tags" : "h1 = 5\\r\\nh2 = 3\\r\\nh3 = 2\\r\\nstrong = 2\\r\\nb = 2\\r\\nem = 1.5\\r\\nu = 1.5"
          }
        },
        "search_api_transliteration" : {
          "status" : 0,
          "weight" : "15",
          "settings" : { "fields" : {
              "node:title" : true,
              "node:field_ding_news_lead" : true,
              "node:field_ding_page_lead" : true,
              "node:field_ding_event_lead" : true,
              "node:field_ding_library_fax_number" : true,
              "node:field_ding_library_lead" : true,
              "node:field_ding_library_mail" : true,
              "node:field_ding_library_phone_number" : true,
              "node:field_ding_group_lead" : true
            }
          }
        },
        "search_api_tokenizer" : {
          "status" : 0,
          "weight" : "20",
          "settings" : {
            "fields" : {
              "node:title" : true,
              "node:field_ding_news_lead" : true,
              "node:field_ding_page_lead" : true,
              "node:field_ding_event_lead" : true,
              "node:field_ding_library_fax_number" : true,
              "node:field_ding_library_lead" : true,
              "node:field_ding_library_mail" : true,
              "node:field_ding_library_phone_number" : true,
              "node:field_ding_group_lead" : true
            },
            "spaces" : "[^[:alnum:]]",
            "ignorable" : "[\\u0027]"
          }
        },
        "search_api_stopwords" : {
          "status" : 0,
          "weight" : "30",
          "settings" : {
            "fields" : {
              "node:title" : true,
              "node:field_ding_news_lead" : true,
              "node:field_ding_page_lead" : true,
              "node:field_ding_event_lead" : true,
              "node:field_ding_library_fax_number" : true,
              "node:field_ding_library_lead" : true,
              "node:field_ding_library_mail" : true,
              "node:field_ding_library_phone_number" : true,
              "node:field_ding_group_lead" : true
            },
            "file" : "",
            "stopwords" : "but\\r\\ndid\\r\\nthe this that those\\r\\netc"
          }
        },
        "search_api_highlighting" : {
          "status" : 0,
          "weight" : "35",
          "settings" : {
            "prefix" : "\\u003Cstrong\\u003E",
            "suffix" : "\\u003C\\/strong\\u003E",
            "excerpt" : 1,
            "excerpt_length" : "256",
            "exclude_fields" : [],
            "highlight" : "always"
          }
        }
      }
    },
    "enabled" : "1",
    "read_only" : "0"
  }');
  return $items;
}

/**
 * Implements hook_default_search_api_server().
 */
function ding_frontend_default_search_api_server() {
  $items = array();
  $items['localhost_db'] = entity_import('search_api_server', '{
    "name" : "Localhost DB",
    "machine_name" : "localhost_db",
    "description" : "",
    "class" : "search_api_db_service",
    "options" : {
      "database" : "default:default",
      "min_chars" : "1",
      "partial_matches" : 1,
      "indexes" : {
        "default_node_index" : {
          "nid" : {
            "table" : "search_api_db_default_node_index",
            "column" : "nid",
            "type" : "integer",
            "boost" : "1.0"
          },
          "vid" : {
            "table" : "search_api_db_default_node_index",
            "column" : "vid",
            "type" : "integer",
            "boost" : "1.0"
          },
          "type" : {
            "table" : "search_api_db_default_node_index",
            "column" : "type",
            "type" : "string",
            "boost" : "1.0"
          },
          "title" : {
            "table" : "search_api_db_default_node_index_text",
            "type" : "text",
            "boost" : "5.0"
          },
          "language" : {
            "table" : "search_api_db_default_node_index",
            "column" : "language",
            "type" : "string",
            "boost" : "1.0"
          },
          "url" : {
            "table" : "search_api_db_default_node_index",
            "column" : "url",
            "type" : "uri",
            "boost" : "1.0"
          },
          "status" : {
            "table" : "search_api_db_default_node_index",
            "column" : "status",
            "type" : "integer",
            "boost" : "1.0"
          },
          "promote" : {
            "table" : "search_api_db_default_node_index",
            "column" : "promote",
            "type" : "boolean",
            "boost" : "1.0"
          },
          "sticky" : {
            "table" : "search_api_db_default_node_index",
            "column" : "sticky",
            "type" : "boolean",
            "boost" : "1.0"
          },
          "created" : {
            "table" : "search_api_db_default_node_index",
            "column" : "created",
            "type" : "date",
            "boost" : "1.0"
          },
          "changed" : {
            "table" : "search_api_db_default_node_index",
            "column" : "changed",
            "type" : "date",
            "boost" : "1.0"
          },
          "author" : {
            "table" : "search_api_db_default_node_index",
            "column" : "author",
            "type" : "integer",
            "boost" : "1.0"
          },
          "comment_count" : {
            "table" : "search_api_db_default_node_index",
            "column" : "comment_count",
            "type" : "integer",
            "boost" : "1.0"
          },
          "field_bpi_workflow" : {
            "table" : "search_api_db_default_node_index",
            "column" : "field_bpi_workflow",
            "type" : "string",
            "boost" : "1.0"
          },
          "og_group_ref" : {
            "table" : "search_api_db_default_node_index_og_group_ref",
            "column" : "value",
            "type" : "list\\u003Cinteger\\u003E",
            "boost" : "1.0"
          },
          "ding_news_groups_ref" : {
            "table" : "search_api_db_default_node_index_ding_news_groups_ref",
            "column" : "value",
            "type" : "list\\u003Cinteger\\u003E",
            "boost" : "1.0"
          },
          "field_ding_news_category" : {
            "table" : "search_api_db_default_node_index",
            "column" : "field_ding_news_category",
            "type" : "integer",
            "boost" : "1.0"
          },
          "field_ding_news_lead" : {
            "table" : "search_api_db_default_node_index_text",
            "type" : "text",
            "boost" : "1.0"
          },
          "field_ding_news_tags" : {
            "table" : "search_api_db_default_node_index_field_ding_news_tags",
            "column" : "value",
            "type" : "list\\u003Cinteger\\u003E",
            "boost" : "1.0"
          },
          "og_membership" : {
            "table" : "search_api_db_default_node_index_og_membership",
            "column" : "value",
            "type" : "list\\u003Cinteger\\u003E",
            "boost" : "1.0"
          },
          "og_membership__1" : {
            "table" : "search_api_db_default_node_index_og_membership__1",
            "column" : "value",
            "type" : "list\\u003Cinteger\\u003E",
            "boost" : "1.0"
          },
          "og_membership__2" : {
            "table" : "search_api_db_default_node_index_og_membership__2",
            "column" : "value",
            "type" : "list\\u003Cinteger\\u003E",
            "boost" : "1.0"
          },
          "og_membership__3" : {
            "table" : "search_api_db_default_node_index_og_membership__3",
            "column" : "value",
            "type" : "list\\u003Cinteger\\u003E",
            "boost" : "1.0"
          },
          "ding_news_groups_ref__og_membership" : {
            "table" : "search_api_db_default_node_index_ding_news_groups_ref__og_memb",
            "column" : "value",
            "type" : "list\\u003Cinteger\\u003E",
            "boost" : "1.0"
          },
          "ding_news_groups_ref__og_membership__1" : {
            "table" : "search_api_db_default_node_index_ding_news_groups_ref__og_me_1",
            "column" : "value",
            "type" : "list\\u003Cinteger\\u003E",
            "boost" : "1.0"
          },
          "ding_news_groups_ref__og_membership__2" : {
            "table" : "search_api_db_default_node_index_ding_news_groups_ref__og_me_2",
            "column" : "value",
            "type" : "list\\u003Cinteger\\u003E",
            "boost" : "1.0"
          },
          "ding_news_groups_ref__og_membership__3" : {
            "table" : "search_api_db_default_node_index_ding_news_groups_ref__og_me_3",
            "column" : "value",
            "type" : "list\\u003Cinteger\\u003E",
            "boost" : "1.0"
          },
          "og_group_ref__og_membership" : {
            "table" : "search_api_db_default_node_index_og_group_ref__og_membership",
            "column" : "value",
            "type" : "list\\u003Cinteger\\u003E",
            "boost" : "1.0"
          },
          "og_group_ref__og_membership__1" : {
            "table" : "search_api_db_default_node_index_og_group_ref__og_membership__",
            "column" : "value",
            "type" : "list\\u003Cinteger\\u003E",
            "boost" : "1.0"
          },
          "og_group_ref__og_membership__2" : {
            "table" : "search_api_db_default_node_index_og_group_ref__og_membership_1",
            "column" : "value",
            "type" : "list\\u003Cinteger\\u003E",
            "boost" : "1.0"
          },
          "og_group_ref__og_membership__3" : {
            "table" : "search_api_db_default_node_index_og_group_ref__og_membership_2",
            "column" : "value",
            "type" : "list\\u003Cinteger\\u003E",
            "boost" : "1.0"
          },
          "ding_page_group_ref" : {
            "table" : "search_api_db_default_node_index",
            "column" : "ding_page_group_ref",
            "type" : "integer",
            "boost" : "1.0"
          },
          "field_ding_page_lead" : {
            "table" : "search_api_db_default_node_index_text",
            "type" : "text",
            "boost" : "1.0"
          },
          "field_ding_page_tags" : {
            "table" : "search_api_db_default_node_index_field_ding_page_tags",
            "column" : "value",
            "type" : "list\\u003Cinteger\\u003E",
            "boost" : "1.0"
          },
          "ding_page_group_ref__og_membership" : {
            "table" : "search_api_db_default_node_index_ding_page_group_ref__og_membe",
            "column" : "value",
            "type" : "list\\u003Cinteger\\u003E",
            "boost" : "1.0"
          },
          "ding_page_group_ref__og_membership__1" : {
            "table" : "search_api_db_default_node_index_ding_page_group_ref__og_mem_1",
            "column" : "value",
            "type" : "list\\u003Cinteger\\u003E",
            "boost" : "1.0"
          },
          "ding_page_group_ref__og_membership__2" : {
            "table" : "search_api_db_default_node_index_ding_page_group_ref__og_mem_2",
            "column" : "value",
            "type" : "list\\u003Cinteger\\u003E",
            "boost" : "1.0"
          },
          "ding_page_group_ref__og_membership__3" : {
            "table" : "search_api_db_default_node_index_ding_page_group_ref__og_mem_3",
            "column" : "value",
            "type" : "list\\u003Cinteger\\u003E",
            "boost" : "1.0"
          },
          "ding_event_groups_ref" : {
            "table" : "search_api_db_default_node_index_ding_event_groups_ref",
            "column" : "value",
            "type" : "list\\u003Cinteger\\u003E",
            "boost" : "1.0"
          },
          "field_ding_event_category" : {
            "table" : "search_api_db_default_node_index",
            "column" : "field_ding_event_category",
            "type" : "integer",
            "boost" : "1.0"
          },
          "field_ding_event_lead" : {
            "table" : "search_api_db_default_node_index_text",
            "type" : "text",
            "boost" : "1.0"
          },
          "field_ding_event_price" : {
            "table" : "search_api_db_default_node_index",
            "column" : "field_ding_event_price",
            "type" : "integer",
            "boost" : "1.0"
          },
          "field_ding_event_tags" : {
            "table" : "search_api_db_default_node_index_field_ding_event_tags",
            "column" : "value",
            "type" : "list\\u003Cinteger\\u003E",
            "boost" : "1.0"
          },
          "field_ding_event_target" : {
            "table" : "search_api_db_default_node_index",
            "column" : "field_ding_event_target",
            "type" : "integer",
            "boost" : "1.0"
          },
          "ding_event_groups_ref__og_membership" : {
            "table" : "search_api_db_default_node_index_ding_event_groups_ref__og_mem",
            "column" : "value",
            "type" : "list\\u003Cinteger\\u003E",
            "boost" : "1.0"
          },
          "ding_event_groups_ref__og_membership__1" : {
            "table" : "search_api_db_default_node_index_ding_event_groups_ref__og_m_1",
            "column" : "value",
            "type" : "list\\u003Cinteger\\u003E",
            "boost" : "1.0"
          },
          "ding_event_groups_ref__og_membership__2" : {
            "table" : "search_api_db_default_node_index_ding_event_groups_ref__og_m_2",
            "column" : "value",
            "type" : "list\\u003Cinteger\\u003E",
            "boost" : "1.0"
          },
          "ding_event_groups_ref__og_membership__3" : {
            "table" : "search_api_db_default_node_index_ding_event_groups_ref__og_m_3",
            "column" : "value",
            "type" : "list\\u003Cinteger\\u003E",
            "boost" : "1.0"
          },
          "field_ding_library_fax_number" : {
            "table" : "search_api_db_default_node_index_text",
            "type" : "text",
            "boost" : "1.0"
          },
          "field_ding_library_lead" : {
            "table" : "search_api_db_default_node_index_text",
            "type" : "text",
            "boost" : "1.0"
          },
          "field_ding_library_mail" : {
            "table" : "search_api_db_default_node_index_text",
            "type" : "text",
            "boost" : "1.0"
          },
          "field_ding_library_phone_number" : {
            "table" : "search_api_db_default_node_index_text",
            "type" : "text",
            "boost" : "1.0"
          },
          "field_ding_library_slug" : {
            "table" : "search_api_db_default_node_index_text",
            "type" : "text",
            "boost" : "1.0"
          },
          "group_group" : {
            "table" : "search_api_db_default_node_index",
            "column" : "group_group",
            "type" : "boolean",
            "boost" : "1.0"
          },
          "members" : {
            "table" : "search_api_db_default_node_index_members",
            "column" : "value",
            "type" : "list\\u003Cinteger\\u003E",
            "boost" : "1.0"
          },
          "members__1" : {
            "table" : "search_api_db_default_node_index_members__1",
            "column" : "value",
            "type" : "list\\u003Cinteger\\u003E",
            "boost" : "1.0"
          },
          "members__2" : {
            "table" : "search_api_db_default_node_index_members__2",
            "column" : "value",
            "type" : "list\\u003Cinteger\\u003E",
            "boost" : "1.0"
          },
          "members__3" : {
            "table" : "search_api_db_default_node_index_members__3",
            "column" : "value",
            "type" : "list\\u003Cinteger\\u003E",
            "boost" : "1.0"
          },
          "field_ding_group_category" : {
            "table" : "search_api_db_default_node_index",
            "column" : "field_ding_group_category",
            "type" : "integer",
            "boost" : "1.0"
          },
          "field_ding_group_lead" : {
            "table" : "search_api_db_default_node_index_text",
            "type" : "text",
            "boost" : "1.0"
          },
          "field_ding_tabroll_lead" : {
            "table" : "search_api_db_default_node_index_text",
            "type" : "text",
            "boost" : "1.0"
          },
          "field_ding_tabroll_link" : {
            "table" : "search_api_db_default_node_index",
            "column" : "field_ding_tabroll_link",
            "type" : "integer",
            "boost" : "1.0"
          },
          "search_api_language" : {
            "table" : "search_api_db_default_node_index",
            "column" : "search_api_language",
            "type" : "string",
            "boost" : "1.0"
          },
          "body:value" : {
            "table" : "search_api_db_default_node_index_text",
            "type" : "text",
            "boost" : "1.0"
          }
        },
        "default_multiple_index" : {
          "item_id" : {
            "table" : "search_api_db_default_multiple_index",
            "column" : "item_id_1",
            "type" : "string",
            "boost" : "1.0"
          },
          "item_type" : {
            "table" : "search_api_db_default_multiple_index",
            "column" : "item_type",
            "type" : "string",
            "boost" : "1.0"
          },
          "item_bundle" : {
            "table" : "search_api_db_default_multiple_index",
            "column" : "item_bundle",
            "type" : "string",
            "boost" : "1.0"
          },
          "node" : {
            "table" : "search_api_db_default_multiple_index",
            "column" : "node",
            "type" : "integer",
            "boost" : "1.0"
          },
          "user" : {
            "table" : "search_api_db_default_multiple_index",
            "column" : "user",
            "type" : "integer",
            "boost" : "1.0"
          },
          "search_api_language" : {
            "table" : "search_api_db_default_multiple_index",
            "column" : "search_api_language",
            "type" : "string",
            "boost" : "1.0"
          },
          "node:nid" : {
            "table" : "search_api_db_default_multiple_index",
            "column" : "node_nid",
            "type" : "integer",
            "boost" : "1.0"
          },
          "node:title" : {
            "table" : "search_api_db_default_multiple_index_text",
            "type" : "text",
            "boost" : "2.0"
          },
          "node:created" : {
            "table" : "search_api_db_default_multiple_index",
            "column" : "node_created",
            "type" : "date",
            "boost" : "1.0"
          },
          "node:changed" : {
            "table" : "search_api_db_default_multiple_index",
            "column" : "node_changed",
            "type" : "date",
            "boost" : "1.0"
          },
          "node:author" : {
            "table" : "search_api_db_default_multiple_index",
            "column" : "node_author",
            "type" : "integer",
            "boost" : "1.0"
          },
          "node:field_ding_news_category" : {
            "table" : "search_api_db_default_multiple_index",
            "column" : "node_field_ding_news_category",
            "type" : "integer",
            "boost" : "1.0"
          },
          "node:field_ding_news_lead" : {
            "table" : "search_api_db_default_multiple_index_text",
            "type" : "text",
            "boost" : "1.0"
          },
          "node:field_ding_news_tags" : {
            "table" : "search_api_db_default_multiple_index_node_field_ding_news_tags",
            "column" : "value",
            "type" : "list\\u003Cinteger\\u003E",
            "boost" : "1.0"
          },
          "node:field_ding_page_lead" : {
            "table" : "search_api_db_default_multiple_index_text",
            "type" : "text",
            "boost" : "1.0"
          },
          "node:field_ding_page_tags" : {
            "table" : "search_api_db_default_multiple_index_node_field_ding_page_tags",
            "column" : "value",
            "type" : "list\\u003Cinteger\\u003E",
            "boost" : "1.0"
          },
          "node:field_ding_event_category" : {
            "table" : "search_api_db_default_multiple_index",
            "column" : "node_field_ding_event_category",
            "type" : "integer",
            "boost" : "1.0"
          },
          "node:field_ding_event_lead" : {
            "table" : "search_api_db_default_multiple_index_text",
            "type" : "text",
            "boost" : "1.0"
          },
          "node:field_ding_event_tags" : {
            "table" : "search_api_db_default_multiple_index_node_field_ding_event_tag",
            "column" : "value",
            "type" : "list\\u003Cinteger\\u003E",
            "boost" : "1.0"
          },
          "node:field_ding_event_target" : {
            "table" : "search_api_db_default_multiple_index",
            "column" : "node_field_ding_event_target",
            "type" : "integer",
            "boost" : "1.0"
          },
          "node:field_ding_library_fax_number" : {
            "table" : "search_api_db_default_multiple_index_text",
            "type" : "text",
            "boost" : "1.0"
          },
          "node:field_ding_library_lead" : {
            "table" : "search_api_db_default_multiple_index_text",
            "type" : "text",
            "boost" : "1.0"
          },
          "node:field_ding_library_mail" : {
            "table" : "search_api_db_default_multiple_index_text",
            "type" : "text",
            "boost" : "1.0"
          },
          "node:field_ding_library_phone_number" : {
            "table" : "search_api_db_default_multiple_index_text",
            "type" : "text",
            "boost" : "1.0"
          },
          "node:field_ding_group_lead" : {
            "table" : "search_api_db_default_multiple_index_text",
            "type" : "text",
            "boost" : "1.0"
          },
          "user:uid" : {
            "table" : "search_api_db_default_multiple_index",
            "column" : "user_uid",
            "type" : "integer",
            "boost" : "1.0"
          },
          "user:roles" : {
            "table" : "search_api_db_default_multiple_index_user_roles",
            "column" : "value",
            "type" : "list\\u003Cinteger\\u003E",
            "boost" : "1.0"
          },
          "user:status" : {
            "table" : "search_api_db_default_multiple_index",
            "column" : "user_status",
            "type" : "integer",
            "boost" : "1.0"
          },
          "user:profile_ding_staff_profile" : {
            "table" : "search_api_db_default_multiple_index",
            "column" : "user_profile_ding_staff_profile",
            "type" : "integer",
            "boost" : "1.0"
          },
          "user:relation_ting_reference_ting_object" : {
            "table" : "search_api_db_default_multiple_index_user_relation_ting_refere",
            "column" : "value",
            "type" : "list\\u003Cinteger\\u003E",
            "boost" : "1.0"
          },
          "node:type" : {
            "table" : "search_api_db_default_multiple_index",
            "column" : "node_type",
            "type" : "string",
            "boost" : "1.0"
          },
          "node:url" : {
            "table" : "search_api_db_default_multiple_index",
            "column" : "node_url",
            "type" : "uri",
            "boost" : "1.0"
          },
          "user:profile_ding_staff_profile:field_ding_staff_department" : {
            "table" : "search_api_db_default_multiple_index_user_profile_ding_staff_p",
            "column" : "value",
            "type" : "list\\u003Cinteger\\u003E",
            "boost" : "1.0"
          },
          "user:profile_ding_staff_profile:field_ding_staff_email" : {
            "table" : "search_api_db_default_multiple_index_text",
            "type" : "text",
            "boost" : "1.0"
          },
          "user:profile_ding_staff_profile:field_ding_staff_forename" : {
            "table" : "search_api_db_default_multiple_index_text",
            "type" : "text",
            "boost" : "2.0"
          },
          "user:profile_ding_staff_profile:field_ding_staff_phone" : {
            "table" : "search_api_db_default_multiple_index_text",
            "type" : "text",
            "boost" : "1.0"
          },
          "user:profile_ding_staff_profile:field_ding_staff_position" : {
            "table" : "search_api_db_default_multiple_index_text",
            "type" : "text",
            "boost" : "1.0"
          },
          "user:profile_ding_staff_profile:field_ding_staff_surname" : {
            "table" : "search_api_db_default_multiple_index_text",
            "type" : "text",
            "boost" : "2.0"
          },
          "user:profile_ding_staff_profile:field_ding_staff_work_areas" : {
            "table" : "search_api_db_default_multiple_index_text",
            "type" : "text",
            "boost" : "1.0"
          }
        }
      }
    },
    "enabled" : "1"
  }');
  return $items;
}
