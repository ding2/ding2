<?php
/**
 * @file
 * ding_seo.strongarm.inc
 */

/**
 * Implements hook_strongarm().
 */
function ding_seo_strongarm() {
  $export = array();

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'metatag_entity_type_groups_file_audio';
  $strongarm->value = array(
    'basic' => 'basic',
    'advanced' => 'advanced',
    'verification' => 'verification',
    'open-graph' => 0,
    'schema_article' => 0,
    'schema_event' => 0,
    'schema_organization' => 0,
  );
  $export['metatag_entity_type_groups_file_audio'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'metatag_entity_type_groups_file_document';
  $strongarm->value = array(
    'basic' => 'basic',
    'advanced' => 'advanced',
    'verification' => 'verification',
    'open-graph' => 0,
    'schema_article' => 0,
    'schema_event' => 0,
    'schema_organization' => 0,
  );
  $export['metatag_entity_type_groups_file_document'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'metatag_entity_type_groups_file_image';
  $strongarm->value = array(
    'basic' => 'basic',
    'advanced' => 'advanced',
    'verification' => 'verification',
    'open-graph' => 0,
    'schema_article' => 0,
    'schema_event' => 0,
    'schema_organization' => 0,
  );
  $export['metatag_entity_type_groups_file_image'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'metatag_entity_type_groups_file_video';
  $strongarm->value = array(
    'basic' => 'basic',
    'advanced' => 'advanced',
    'verification' => 'verification',
    'open-graph' => 0,
    'schema_article' => 0,
    'schema_event' => 0,
    'schema_organization' => 0,
  );
  $export['metatag_entity_type_groups_file_video'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'metatag_entity_type_groups_node_ding_campaign_plus';
  $strongarm->value = array(
    'basic' => 'basic',
    'advanced' => 'advanced',
    'verification' => 'verification',
    'open-graph' => 0,
    'schema_article' => 0,
    'schema_event' => 0,
    'schema_organization' => 0,
  );
  $export['metatag_entity_type_groups_node_ding_campaign_plus'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'metatag_entity_type_groups_node_ding_eresource';
  $strongarm->value = array(
    'basic' => 'basic',
    'advanced' => 'advanced',
    'verification' => 'verification',
    'open-graph' => 0,
    'schema_article' => 0,
    'schema_event' => 0,
    'schema_organization' => 0,
  );
  $export['metatag_entity_type_groups_node_ding_eresource'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'metatag_entity_type_groups_node_ding_event';
  $strongarm->value = array(
    'basic' => 'basic',
    'advanced' => 'advanced',
    'open-graph' => 'open-graph',
    'verification' => 'verification',
    'schema_event' => 'schema_event',
    'schema_article' => 0,
    'schema_organization' => 0,
  );
  $export['metatag_entity_type_groups_node_ding_event'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'metatag_entity_type_groups_node_ding_group';
  $strongarm->value = array(
    'basic' => 'basic',
    'advanced' => 'advanced',
    'verification' => 'verification',
    'open-graph' => 0,
    'schema_article' => 0,
    'schema_event' => 0,
    'schema_organization' => 0,
  );
  $export['metatag_entity_type_groups_node_ding_group'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'metatag_entity_type_groups_node_ding_library';
  $strongarm->value = array(
    'basic' => 'basic',
    'advanced' => 'advanced',
    'open-graph' => 'open-graph',
    'verification' => 'verification',
    'schema_organization' => 'schema_organization',
    'schema_article' => 0,
    'schema_event' => 0,
  );
  $export['metatag_entity_type_groups_node_ding_library'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'metatag_entity_type_groups_node_ding_news';
  $strongarm->value = array(
    'basic' => 'basic',
    'advanced' => 'advanced',
    'open-graph' => 'open-graph',
    'verification' => 'verification',
    'schema_article' => 'schema_article',
    'schema_event' => 0,
    'schema_organization' => 0,
  );
  $export['metatag_entity_type_groups_node_ding_news'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'metatag_entity_type_groups_node_ding_page';
  $strongarm->value = array(
    'basic' => 'basic',
    'advanced' => 'advanced',
    'open-graph' => 'open-graph',
    'verification' => 'verification',
    'schema_article' => 0,
    'schema_event' => 0,
    'schema_organization' => 0,
  );
  $export['metatag_entity_type_groups_node_ding_page'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'metatag_entity_type_groups_node_ding_rolltab';
  $strongarm->value = array(
    'basic' => 'basic',
    'advanced' => 'advanced',
    'verification' => 'verification',
    'open-graph' => 0,
    'schema_article' => 0,
    'schema_event' => 0,
    'schema_organization' => 0,
  );
  $export['metatag_entity_type_groups_node_ding_rolltab'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'metatag_entity_type_groups_node_panel';
  $strongarm->value = array(
    'basic' => 'basic',
    'advanced' => 'advanced',
    'verification' => 'verification',
    'open-graph' => 0,
    'schema_article' => 0,
    'schema_event' => 0,
    'schema_organization' => 0,
  );
  $export['metatag_entity_type_groups_node_panel'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'metatag_entity_type_groups_node_webform';
  $strongarm->value = array(
    'basic' => 'basic',
    'advanced' => 'advanced',
    'verification' => 'verification',
    'open-graph' => 0,
    'schema_article' => 0,
    'schema_event' => 0,
    'schema_organization' => 0,
  );
  $export['metatag_entity_type_groups_node_webform'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'metatag_entity_type_groups_profile2_ding_staff_profile';
  $strongarm->value = array(
    'basic' => 'basic',
    'advanced' => 'advanced',
    'verification' => 'verification',
    'open-graph' => 0,
    'schema_article' => 0,
    'schema_event' => 0,
    'schema_organization' => 0,
  );
  $export['metatag_entity_type_groups_profile2_ding_staff_profile'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'metatag_entity_type_groups_profile2_provider_fbs';
  $strongarm->value = array(
    'basic' => 'basic',
    'advanced' => 'advanced',
    'verification' => 'verification',
    'open-graph' => 0,
    'schema_article' => 0,
    'schema_event' => 0,
    'schema_organization' => 0,
  );
  $export['metatag_entity_type_groups_profile2_provider_fbs'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'metatag_entity_type_groups_taxonomy_term_category';
  $strongarm->value = array(
    'basic' => 'basic',
    'advanced' => 'advanced',
    'verification' => 'verification',
    'open-graph' => 0,
    'schema_article' => 0,
    'schema_event' => 0,
    'schema_organization' => 0,
  );
  $export['metatag_entity_type_groups_taxonomy_term_category'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'metatag_entity_type_groups_taxonomy_term_ding_content_tags';
  $strongarm->value = array(
    'basic' => 'basic',
    'advanced' => 'advanced',
    'verification' => 'verification',
    'open-graph' => 0,
    'schema_article' => 0,
    'schema_event' => 0,
    'schema_organization' => 0,
  );
  $export['metatag_entity_type_groups_taxonomy_term_ding_content_tags'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'metatag_entity_type_groups_taxonomy_term_ding_staff_department';
  $strongarm->value = array(
    'basic' => 'basic',
    'advanced' => 'advanced',
    'verification' => 'verification',
    'open-graph' => 0,
    'schema_article' => 0,
    'schema_event' => 0,
    'schema_organization' => 0,
  );
  $export['metatag_entity_type_groups_taxonomy_term_ding_staff_department'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'metatag_entity_type_groups_taxonomy_term_event_category';
  $strongarm->value = array(
    'basic' => 'basic',
    'advanced' => 'advanced',
    'verification' => 'verification',
    'open-graph' => 0,
    'schema_article' => 0,
    'schema_event' => 0,
    'schema_organization' => 0,
  );
  $export['metatag_entity_type_groups_taxonomy_term_event_category'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'metatag_entity_type_groups_taxonomy_term_event_organizer';
  $strongarm->value = array(
    'basic' => 'basic',
    'advanced' => 'advanced',
    'verification' => 'verification',
    'open-graph' => 0,
    'schema_article' => 0,
    'schema_event' => 0,
    'schema_organization' => 0,
  );
  $export['metatag_entity_type_groups_taxonomy_term_event_organizer'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'metatag_entity_type_groups_taxonomy_term_event_target';
  $strongarm->value = array(
    'basic' => 'basic',
    'advanced' => 'advanced',
    'verification' => 'verification',
    'open-graph' => 0,
    'schema_article' => 0,
    'schema_event' => 0,
    'schema_organization' => 0,
  );
  $export['metatag_entity_type_groups_taxonomy_term_event_target'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'metatag_entity_type_groups_taxonomy_term_e_resource_availability';
  $strongarm->value = array(
    'basic' => 'basic',
    'advanced' => 'advanced',
    'verification' => 'verification',
    'open-graph' => 0,
    'schema_article' => 0,
    'schema_event' => 0,
    'schema_organization' => 0,
  );
  $export['metatag_entity_type_groups_taxonomy_term_e_resource_availability'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'metatag_entity_type_groups_taxonomy_term_e_resource_category';
  $strongarm->value = array(
    'basic' => 'basic',
    'advanced' => 'advanced',
    'verification' => 'verification',
    'open-graph' => 0,
    'schema_article' => 0,
    'schema_event' => 0,
    'schema_organization' => 0,
  );
  $export['metatag_entity_type_groups_taxonomy_term_e_resource_category'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'metatag_entity_type_groups_taxonomy_term_group_category';
  $strongarm->value = array(
    'basic' => 'basic',
    'advanced' => 'advanced',
    'verification' => 'verification',
    'open-graph' => 0,
    'schema_article' => 0,
    'schema_event' => 0,
    'schema_organization' => 0,
  );
  $export['metatag_entity_type_groups_taxonomy_term_group_category'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'metatag_entity_type_groups_taxonomy_term_news_category';
  $strongarm->value = array(
    'basic' => 'basic',
    'advanced' => 'advanced',
    'verification' => 'verification',
    'open-graph' => 0,
    'schema_article' => 0,
    'schema_event' => 0,
    'schema_organization' => 0,
  );
  $export['metatag_entity_type_groups_taxonomy_term_news_category'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'metatag_entity_type_groups_taxonomy_term_section';
  $strongarm->value = array(
    'basic' => 'basic',
    'advanced' => 'advanced',
    'verification' => 'verification',
    'open-graph' => 0,
    'schema_article' => 0,
    'schema_event' => 0,
    'schema_organization' => 0,
  );
  $export['metatag_entity_type_groups_taxonomy_term_section'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'metatag_entity_type_groups_ting_collection_ting_collection';
  $strongarm->value = array(
    'basic' => 'basic',
    'advanced' => 'advanced',
    'open-graph' => 0,
    'verification' => 0,
    'schema_article' => 0,
    'schema_event' => 0,
    'schema_organization' => 0,
  );
  $export['metatag_entity_type_groups_ting_collection_ting_collection'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'metatag_entity_type_groups_ting_object_ting_object';
  $strongarm->value = array(
    'basic' => 'basic',
    'advanced' => 'advanced',
    'open-graph' => 0,
    'verification' => 0,
    'schema_article' => 0,
    'schema_event' => 0,
    'schema_organization' => 0,
  );
  $export['metatag_entity_type_groups_ting_object_ting_object'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'metatag_entity_type_groups_ting_type_smart_search_string';
  $strongarm->value = array(
    'basic' => 'basic',
    'advanced' => 'advanced',
    'verification' => 'verification',
    'open-graph' => 0,
    'schema_article' => 0,
    'schema_event' => 0,
    'schema_organization' => 0,
  );
  $export['metatag_entity_type_groups_ting_type_smart_search_string'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'metatag_entity_type_groups_user_user';
  $strongarm->value = array(
    'basic' => 'basic',
    'advanced' => 'advanced',
    'verification' => 'verification',
    'open-graph' => 0,
    'schema_article' => 0,
    'schema_event' => 0,
    'schema_organization' => 0,
  );
  $export['metatag_entity_type_groups_user_user'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'xmlsitemap_batch_limit';
  $strongarm->value = '250';
  $export['xmlsitemap_batch_limit'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'xmlsitemap_chunk_size';
  $strongarm->value = '50000';
  $export['xmlsitemap_chunk_size'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'xmlsitemap_engines_engines';
  $strongarm->value = array(
    0 => 'google',
  );
  $export['xmlsitemap_engines_engines'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'xmlsitemap_engines_minimum_lifetime';
  $strongarm->value = '86400';
  $export['xmlsitemap_engines_minimum_lifetime'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'xmlsitemap_engines_submit_updated';
  $strongarm->value = 1;
  $export['xmlsitemap_engines_submit_updated'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'xmlsitemap_frontpage_changefreq';
  $strongarm->value = '86400';
  $export['xmlsitemap_frontpage_changefreq'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'xmlsitemap_frontpage_priority';
  $strongarm->value = '1.0';
  $export['xmlsitemap_frontpage_priority'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'xmlsitemap_minimum_lifetime';
  $strongarm->value = '86400';
  $export['xmlsitemap_minimum_lifetime'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'xmlsitemap_settings_menu_link_main-menu';
  $strongarm->value = array(
    'status' => '1',
    'priority' => '0.5',
  );
  $export['xmlsitemap_settings_menu_link_main-menu'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'xmlsitemap_settings_menu_link_menu-footer-menu-1';
  $strongarm->value = array(
    'status' => '1',
    'priority' => '0.5',
  );
  $export['xmlsitemap_settings_menu_link_menu-footer-menu-1'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'xmlsitemap_settings_menu_link_menu-footer-menu-2';
  $strongarm->value = array(
    'status' => '1',
    'priority' => '0.5',
  );
  $export['xmlsitemap_settings_menu_link_menu-footer-menu-2'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'xmlsitemap_settings_menu_link_menu-footer-menu-3';
  $strongarm->value = array(
    'status' => '1',
    'priority' => '0.5',
  );
  $export['xmlsitemap_settings_menu_link_menu-footer-menu-3'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'xmlsitemap_settings_menu_link_menu-footer-menu-4';
  $strongarm->value = array(
    'status' => '1',
    'priority' => '0.5',
  );
  $export['xmlsitemap_settings_menu_link_menu-footer-menu-4'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'xmlsitemap_settings_menu_link_menu-secondary-menu';
  $strongarm->value = array(
    'status' => '1',
    'priority' => '0.5',
  );
  $export['xmlsitemap_settings_menu_link_menu-secondary-menu'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'xmlsitemap_settings_node_ding_eresource';
  $strongarm->value = array(
    'status' => '1',
    'priority' => '0.5',
  );
  $export['xmlsitemap_settings_node_ding_eresource'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'xmlsitemap_settings_node_ding_event';
  $strongarm->value = array(
    'status' => '1',
    'priority' => '0.5',
  );
  $export['xmlsitemap_settings_node_ding_event'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'xmlsitemap_settings_node_ding_group';
  $strongarm->value = array(
    'status' => '1',
    'priority' => '0.5',
  );
  $export['xmlsitemap_settings_node_ding_group'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'xmlsitemap_settings_node_ding_library';
  $strongarm->value = array(
    'status' => '1',
    'priority' => '0.5',
  );
  $export['xmlsitemap_settings_node_ding_library'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'xmlsitemap_settings_node_ding_news';
  $strongarm->value = array(
    'status' => '1',
    'priority' => '0.5',
  );
  $export['xmlsitemap_settings_node_ding_news'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'xmlsitemap_settings_node_ding_page';
  $strongarm->value = array(
    'status' => '1',
    'priority' => '0.5',
  );
  $export['xmlsitemap_settings_node_ding_page'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'xmlsitemap_settings_node_webform';
  $strongarm->value = array(
    'status' => '1',
    'priority' => '0.5',
  );
  $export['xmlsitemap_settings_node_webform'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'xmlsitemap_settings_taxonomy_term_ding_content_tags';
  $strongarm->value = array(
    'status' => '1',
    'priority' => '0.5',
  );
  $export['xmlsitemap_settings_taxonomy_term_ding_content_tags'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'xmlsitemap_settings_taxonomy_term_event_category';
  $strongarm->value = array(
    'status' => '1',
    'priority' => '0.5',
  );
  $export['xmlsitemap_settings_taxonomy_term_event_category'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'xmlsitemap_settings_taxonomy_term_e_resource_category';
  $strongarm->value = array(
    'status' => '1',
    'priority' => '0.5',
  );
  $export['xmlsitemap_settings_taxonomy_term_e_resource_category'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'xmlsitemap_settings_taxonomy_term_news_category';
  $strongarm->value = array(
    'status' => '1',
    'priority' => '0.5',
  );
  $export['xmlsitemap_settings_taxonomy_term_news_category'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'xmlsitemap_settings_taxonomy_term_section';
  $strongarm->value = array(
    'status' => '1',
    'priority' => '0.5',
  );
  $export['xmlsitemap_settings_taxonomy_term_section'] = $strongarm;

  return $export;
}
