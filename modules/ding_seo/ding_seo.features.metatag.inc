<?php
/**
 * @file
 * ding_seo.features.metatag.inc
 */

/**
 * Implements hook_metatag_export_default().
 */
function ding_seo_metatag_export_default() {
  $config = array();

  // Exported Metatag config instance: node.
  $config['node'] = array(
    'instance' => 'node',
    'disabled' => FALSE,
    'config' => array(
      'title' => array(
        'value' => '[node:title] | [current-page:pager][site:name]',
      ),
      'description' => array(
        'value' => '[node:summary]',
      ),
    ),
  );

  // Exported Metatag config instance: node:ding_event.
  $config['node:ding_event'] = array(
    'instance' => 'node:ding_event',
    'disabled' => FALSE,
    'config' => array(
      'schema_event.@type' => array(
        'value' => 'Event',
      ),
      'schema_event.@id' => array(
        'value' => '[node:url]',
      ),
      'schema_event.name' => array(
        'value' => '[node:title]',
      ),
      'schema_event.image' => array(
        'value' => 'a:5:{s:5:"@type";s:11:"ImageObject";s:20:"representativeOfPage";s:4:"True";s:3:"url";s:61:"[node:field_ding_event_title_image:ding_secondary_large:path]";s:5:"width";s:62:"[node:field_ding_event_title_image:ding_secondary_large:width]";s:6:"height";s:63:"[node:field_ding_event_title_image:ding_secondary_large:height]";}',
      ),
      'schema_event.description' => array(
        'value' => '[node:field_ding_event_lead]',
      ),
      'schema_event.isAccessibleForFree' => array(
        'value' => '[node:ding_seo_node_tokens:event_free]',
      ),
      'schema_event.startDate' => array(
        'value' => '[node:ding_seo_node_tokens:event_startdate]',
      ),
      'schema_event.endDate' => array(
        'value' => '[node:ding_seo_node_tokens:event_enddate]',
      ),
      'schema_event.location' => array(
        'value' => 'a:5:{s:5:"@type";s:5:"Place";s:4:"name";s:41:"[node:ding_seo_node_tokens:location_name]";s:3:"url";s:40:"[node:ding_seo_node_tokens:location_url]";s:7:"address";a:6:{s:5:"@type";s:13:"PostalAddress";s:13:"streetAddress";s:41:"[node:ding_seo_node_tokens:streetAddress]";s:15:"addressLocality";s:43:"[node:ding_seo_node_tokens:addressLocality]";s:13:"addressRegion";s:41:"[node:ding_seo_node_tokens:addressRegion]";s:10:"postalCode";s:38:"[node:ding_seo_node_tokens:postalCode]";s:14:"addressCountry";s:42:"[node:ding_seo_node_tokens:addressCountry]";}s:3:"geo";a:3:{s:5:"@type";s:14:"GeoCoordinates";s:8:"latitude";s:36:"[node:ding_seo_node_tokens:latitude]";s:9:"longitude";s:37:"[node:ding_seo_node_tokens:longitude]";}}',
      ),
      'schema_event.url' => array(
        'value' => '[node:url]',
      ),
    ),
  );

  // Exported Metatag config instance: node:ding_library.
  $config['node:ding_library'] = array(
    'instance' => 'node:ding_library',
    'disabled' => FALSE,
    'config' => array(
      'schema_organization.@type' => array(
        'value' => 'Library',
      ),
      'schema_organization.@id' => array(
        'value' => '[node:url]',
      ),
      'schema_organization.name' => array(
        'value' => '[node:title]',
      ),
      'schema_organization.address' => array(
        'value' => 'a:5:{s:5:"@type";s:13:"PostalAddress";s:13:"streetAddress";s:41:"[node:ding_seo_node_tokens:streetAddress]";s:15:"addressLocality";s:30:"[dingseotoken:addressLocality]";s:10:"postalCode";s:38:"[node:ding_seo_node_tokens:postalCode]";s:14:"addressCountry";s:42:"[node:ding_seo_node_tokens:addressCountry]";}',
      ),
      'schema_organization.geo' => array(
        'value' => 'a:3:{s:5:"@type";s:14:"GeoCoordinates";s:8:"latitude";s:36:"[node:ding_seo_node_tokens:latitude]";s:9:"longitude";s:37:"[node:ding_seo_node_tokens:longitude]";}',
      ),
      'schema_organization.telephone' => array(
        'value' => '[node:field_ding_library_phone_number]',
      ),
      'schema_organization.url' => array(
        'value' => '[node:url]',
      ),
      'schema_organization.description' => array(
        'value' => '[node:field_ding_library_lead]',
      ),
      'schema_organization.image' => array(
        'value' => 'a:4:{s:5:"@type";s:11:"ImageObject";s:3:"url";s:61:"[node:field_ding_library_title_image:ding_primary_large:path]";s:5:"width";s:62:"[node:field_ding_library_title_image:ding_primary_large:width]";s:6:"height";s:63:"[node:field_ding_library_title_image:ding_primary_large:height]";}',
      ),
      'schema_organization.logo' => array(
        'value' => 'a:4:{s:5:"@type";s:11:"ImageObject";s:3:"url";s:36:"[node:ding_seo_node_tokens:logo_url]";s:5:"width";s:38:"[node:ding_seo_node_tokens:logo_width]";s:6:"height";s:39:"[node:ding_seo_node_tokens:logo_height]";}',
      ),
    ),
  );

  // Exported Metatag config instance: node:ding_news.
  $config['node:ding_news'] = array(
    'instance' => 'node:ding_news',
    'disabled' => FALSE,
    'config' => array(
      'schema_article.@type' => array(
        'value' => 'NewsArticle',
      ),
      'schema_article.headline' => array(
        'value' => '[node:title]',
      ),
      'schema_article.name' => array(
        'value' => '[node:title]',
      ),
      'schema_article.description' => array(
        'value' => '[node:field_ding_news_lead]',
      ),
      'schema_article.author' => array(
        'value' => 'a:5:{s:5:"@type";s:12:"Organization";s:3:"@id";s:10:"[site:url]";s:4:"name";s:11:"[site:name]";s:3:"url";s:10:"[site:url]";s:4:"logo";a:4:{s:5:"@type";s:11:"ImageObject";s:3:"url";s:36:"[node:ding_seo_node_tokens:logo_url]";s:5:"width";s:38:"[node:ding_seo_node_tokens:logo_width]";s:6:"height";s:39:"[node:ding_seo_node_tokens:logo_height]";}}',
      ),
      'schema_article.publisher' => array(
        'value' => 'a:5:{s:5:"@type";s:12:"Organization";s:3:"@id";s:10:"[site:url]";s:4:"name";s:11:"[site:name]";s:3:"url";s:10:"[site:url]";s:4:"logo";a:4:{s:5:"@type";s:11:"ImageObject";s:3:"url";s:36:"[node:ding_seo_node_tokens:logo_url]";s:5:"width";s:38:"[node:ding_seo_node_tokens:logo_width]";s:6:"height";s:39:"[node:ding_seo_node_tokens:logo_height]";}}',
      ),
      'schema_article.datePublished' => array(
        'value' => '[node:created:short]',
      ),
      'schema_article.dateModified' => array(
        'value' => '[node:changed:short]',
      ),
      'schema_article.image' => array(
        'value' => 'a:4:{s:5:"@type";s:11:"ImageObject";s:3:"url";s:60:"[node:field_ding_news_title_image:ding_secondary_large:path]";s:5:"width";s:61:"[node:field_ding_news_title_image:ding_secondary_large:width]";s:6:"height";s:62:"[node:field_ding_news_title_image:ding_secondary_large:height]";}',
      ),
      'schema_article.mainEntityOfPage' => array(
        'value' => '[current-page:url]',
      ),
      'schema_article.about' => array(
        'value' => '[node:field_ding_news_tags]',
      ),
    ),
  );

  return $config;
}