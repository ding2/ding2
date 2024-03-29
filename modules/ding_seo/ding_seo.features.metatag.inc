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
      'og:type' => array(
        'value' => 'website',
      ),
      'og:url' => array(
        'value' => '[node:url:absolute]',
      ),
      'og:title' => array(
        'value' => '[node:title]',
      ),
      'og:description' => array(
        'value' => '[node:field_ding_event_lead]',
      ),
      'og:updated_time' => array(
        'value' => '[node:changed:custom:c]',
      ),
      'og:image' => array(
        'value' => '[node:field_ding_event_title_image:ding_secondary_large:path]',
      ),
      'og:image:type' => array(
        'value' => '[node:field_ding_event_title_image:ding_secondary_large:mimetype]',
      ),
      'og:image:width' => array(
        'value' => '[node:field_ding_event_title_image:ding_secondary_large:width]',
      ),
      'og:image:height' => array(
        'value' => '[node:field_ding_event_title_image:ding_secondary_large:height]',
      ),
      'schema_event.@type' => array(
        'value' => 'Event',
      ),
      'schema_event.@id' => array(
        'value' => '[node:nid]',
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
      'schema_event.startDate' => array(
        'value' => '[node:field-ding-event-date:value:custom:c]',
      ),
      'schema_event.endDate' => array(
        'value' => '[node:field-ding-event-date:value2:custom:c]',
      ),
      'schema_event.location' => array(
        'value' => 'a:5:{s:5:"@type";s:5:"Place";s:4:"name";s:41:"[node:ding_seo_node_tokens:location_name]";s:3:"url";s:40:"[node:ding_seo_node_tokens:location_url]";s:7:"address";a:5:{s:5:"@type";s:13:"PostalAddress";s:13:"streetAddress";s:42:"[node:ding_seo_node_tokens:street_address]";s:15:"addressLocality";s:44:"[node:ding_seo_node_tokens:address_locality]";s:10:"postalCode";s:39:"[node:ding_seo_node_tokens:postal_code]";s:14:"addressCountry";s:43:"[node:ding_seo_node_tokens:address_country]";}s:3:"geo";a:3:{s:5:"@type";s:14:"GeoCoordinates";s:8:"latitude";s:52:"[node:og-group-ref:0:field-ding-library-geocode:lat]";s:9:"longitude";s:52:"[node:og-group-ref:0:field-ding-library-geocode:lon]";}}',
      ),
      'schema_event.url' => array(
        'value' => '[node:url:absolute]',
      ),
    ),
  );

  // Exported Metatag config instance: node:ding_library.
  $config['node:ding_library'] = array(
    'instance' => 'node:ding_library',
    'disabled' => FALSE,
    'config' => array(
      'og:type' => array(
        'value' => 'website',
      ),
      'og:url' => array(
        'value' => '[node:url:absolute]',
      ),
      'og:title' => array(
        'value' => '[node:title]',
      ),
      'og:description' => array(
        'value' => '[node:field_ding_library_lead]',
      ),
      'og:updated_time' => array(
        'value' => '[node:changed:custom:c]',
      ),
      'og:image' => array(
        'value' => '[node:field_ding_library_title_image:ding_primary_large:path]',
      ),
      'og:image:type' => array(
        'value' => '[node:field_ding_event_title_image:ding_secondary_large:mimetype]',
      ),
      'og:image:width' => array(
        'value' => '[node:field_ding_library_title_image:ding_primary_large:width]',
      ),
      'og:image:height' => array(
        'value' => '[node:field_ding_page_title_image:ding_panorama_primary_large:height]',
      ),
      'schema_organization.@type' => array(
        'value' => 'Library',
      ),
      'schema_organization.@id' => array(
        'value' => '[node:nid]',
      ),
      'schema_organization.name' => array(
        'value' => '[node:title]',
      ),
      'schema_organization.address' => array(
        'value' => 'a:5:{s:5:"@type";s:13:"PostalAddress";s:13:"streetAddress";s:47:"[node:field-ding-library-addresse:thoroughfare]";s:15:"addressLocality";s:43:"[node:field-ding-library-addresse:locality]";s:10:"postalCode";s:46:"[node:field-ding-library-addresse:postal_code]";s:14:"addressCountry";s:42:"[node:field-ding-library-addresse:country]";}',
      ),
      'schema_organization.geo' => array(
        'value' => 'a:3:{s:5:"@type";s:14:"GeoCoordinates";s:8:"latitude";s:37:"[node:field-ding-library-geocode:lat]";s:9:"longitude";s:37:"[node:field-ding-library-geocode:lon]";}',
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
        'value' => 'a:4:{s:5:"@type";s:11:"ImageObject";s:3:"url";s:26:"[ding_seo_logo_tokens:url]";s:5:"width";s:28:"[ding_seo_logo_tokens:width]";s:6:"height";s:29:"[ding_seo_logo_tokens:height]";}',
      ),
    ),
  );

  // Exported Metatag config instance: node:ding_news.
  $config['node:ding_news'] = array(
    'instance' => 'node:ding_news',
    'disabled' => FALSE,
    'config' => array(
      'og:url' => array(
        'value' => '[node:url:absolute]',
      ),
      'og:title' => array(
        'value' => '[node:title]',
      ),
      'og:description' => array(
        'value' => '[node:field_ding_news_lead]',
      ),
      'og:updated_time' => array(
        'value' => '[node:changed:custom:c]',
      ),
      'og:image' => array(
        'value' => '[node:field_ding_news_title_image:ding_secondary_large:path]',
      ),
      'og:image:type' => array(
        'value' => '[node:field_ding_news_title_image:ding_secondary_large:mimetype]',
      ),
      'og:image:width' => array(
        'value' => '[node:field_ding_news_title_image:ding_secondary_large:width]',
      ),
      'og:image:height' => array(
        'value' => '[node:field_ding_news_title_image:ding_secondary_large:height]',
      ),
      'article:published_time' => array(
        'value' => '[node:created:custom:c]',
      ),
      'article:modified_time' => array(
        'value' => '[node:changed:custom:c]',
      ),
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
        'value' => 'a:5:{s:5:"@type";s:6:"Person";s:3:"@id";s:17:"[node:author:uid]";s:4:"name";s:18:"[node:author:name]";s:3:"url";s:17:"[node:author:url]";s:4:"logo";a:4:{s:5:"@type";s:11:"ImageObject";s:3:"url";s:26:"[ding_seo_logo_tokens:url]";s:5:"width";s:28:"[ding_seo_logo_tokens:width]";s:6:"height";s:29:"[ding_seo_logo_tokens:height]";}}',
      ),
      'schema_article.publisher' => array(
        'value' => 'a:5:{s:5:"@type";s:12:"Organization";s:3:"@id";s:10:"[site:url]";s:4:"name";s:11:"[site:name]";s:3:"url";s:10:"[site:url]";s:4:"logo";a:4:{s:5:"@type";s:11:"ImageObject";s:3:"url";s:26:"[ding_seo_logo_tokens:url]";s:5:"width";s:28:"[ding_seo_logo_tokens:width]";s:6:"height";s:29:"[ding_seo_logo_tokens:height]";}}',
      ),
      'schema_article.datePublished' => array(
        'value' => '[node:created:custom:c]',
      ),
      'schema_article.dateModified' => array(
        'value' => '[node:changed:custom:c]',
      ),
      'schema_article.image' => array(
        'value' => 'a:4:{s:5:"@type";s:11:"ImageObject";s:3:"url";s:60:"[node:field_ding_news_title_image:ding_secondary_large:path]";s:5:"width";s:61:"[node:field_ding_news_title_image:ding_secondary_large:width]";s:6:"height";s:62:"[node:field_ding_news_title_image:ding_secondary_large:height]";}',
      ),
      'schema_article.mainEntityOfPage' => array(
        'value' => '[node:url:absolute]',
      ),
      'schema_article.about' => array(
        'value' => '[node:field_ding_news_tags]',
      ),
    ),
  );

  // Exported Metatag config instance: node:ding_page.
  $config['node:ding_page'] = array(
    'instance' => 'node:ding_page',
    'disabled' => FALSE,
    'config' => array(
      'og:type' => array(
        'value' => 'website',
      ),
      'og:url' => array(
        'value' => '[node:url:absolute]',
      ),
      'og:title' => array(
        'value' => '[node:title]',
      ),
      'og:description' => array(
        'value' => '[node:field_ding_page_lead]',
      ),
      'og:updated_time' => array(
        'value' => '[node:changed:custom:c]',
      ),
      'og:image' => array(
        'value' => '[node:field_ding_page_title_image:ding_panorama_primary_large:path]',
      ),
      'og:image:type' => array(
        'value' => '[node:field_ding_page_title_image:ding_panorama_primary_large:mimetype]',
      ),
      'og:image:width' => array(
        'value' => '[node:field_ding_page_title_image:ding_panorama_primary_large:width]',
      ),
      'og:image:height' => array(
        'value' => '[node:field_ding_page_title_image:ding_panorama_primary_large:height]',
      ),
      'schema_web_page.@id' => array(
        'value' => '[node:nid]',
      ),
      'schema_web_page.name' => array(
        'value' => '[node:title]',
      ),
      'schema_web_page.description' => array(
        'value' => '[node:field_ding_page_lead]',
      ),
      'schema_web_page.publisher' => array(
        'value' => 'a:5:{s:5:"@type";s:12:"Organization";s:3:"@id";s:10:"[site:url]";s:4:"name";s:11:"[site:name]";s:3:"url";s:10:"[site:url]";s:4:"logo";a:4:{s:5:"@type";s:11:"ImageObject";s:3:"url";s:26:"[ding_seo_logo_tokens:url]";s:5:"width";s:28:"[ding_seo_logo_tokens:width]";s:6:"height";s:29:"[ding_seo_logo_tokens:height]";}}',
      ),
      'schema_web_page.url' => array(
        'value' => '[node:url:absolute]',
      ),
      'schema_web_page.inLanguage' => array(
        'value' => '[node:ding_seo_node_tokens:language]',
      ),
    ),
  );

  return $config;
}
