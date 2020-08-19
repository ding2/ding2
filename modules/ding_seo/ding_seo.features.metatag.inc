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
        'value' => '[site:url]',
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
        'value' => '[site:url]',
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

  // Exported Metatag config instance: ting_object:book.
  $config['ting_object:book'] = array(
    'instance' => 'ting_object:book',
    'disabled' => FALSE,
    'config' => array(
      'title' => array(
        'value' => '',
      ),
      'schema_book.@type' => array(
        'value' => 'Book',
      ),
      'schema_book.name' => array(
        'value' => '[ting_object:title]',
      ),
      'schema_book.author' => array(
        'value' => 'a:3:{s:5:"pivot";s:1:"1";s:5:"@type";s:6:"Person";s:4:"name";s:58:"[ting_object:ding_seo_creators_contributers:author_names],";}',
      ),
      'schema_book.@id' => array(
        'value' => '[ting_object:ding_seo_work_url]',
      ),
      'schema_book.description' => array(
        'value' => '[ting_object:ting_abstract]',
      ),
      'schema_book.image' => array(
        'value' => 'a:5:{s:5:"@type";s:11:"ImageObject";s:20:"representativeOfPage";s:4:"True";s:3:"url";s:37:"[ting_object:ding_seo_ting_cover:url]";s:5:"width";s:39:"[ting_object:ding_seo_ting_cover:width]";s:6:"height";s:40:"[ting_object:ding_seo_ting_cover:height]";}',
      ),
      'schema_book.url' => array(
        'value' => '[ting_object:ding_seo_work_url]',
      ),
      'schema_book.workExample' => array(
        'value' => 'a:10:{s:5:"pivot";s:1:"1";s:5:"@type";s:4:"Book";s:3:"@id";s:70:"[ting_object:ding_seo_ting_object_collection_objects:ting_object_url],";s:4:"name";s:60:"[ting_object:ding_seo_ting_object_collection_objects:title],";s:3:"url";s:70:"[ting_object:ding_seo_ting_object_collection_objects:ting_object_url],";s:13:"datePublished";s:69:"[ting_object:ding_seo_ting_object_collection_objects:date_published],";s:4:"isbn";s:59:"[ting_object:ding_seo_ting_object_collection_objects:isbn],";s:11:"bookEdition";s:62:"[ting_object:ding_seo_ting_object_collection_objects:version],";s:10:"bookFormat";s:66:"[ting_object:ding_seo_ting_object_collection_objects:book_format],";s:6:"author";a:3:{s:5:"pivot";s:1:"1";s:5:"@type";s:6:"Person";s:4:"name";s:58:"[ting_object:ding_seo_creators_contributers:author_names],";}}',
      ),
    ),
  );

  // Exported Metatag config instance: ting_object:movie.
  $config['ting_object:movie'] = array(
    'instance' => 'ting_object:movie',
    'disabled' => FALSE,
    'config' => array(
      'title' => array(
        'value' => '',
      ),
      'schema_movie.@type' => array(
        'value' => 'Movie',
      ),
      'schema_movie.name' => array(
        'value' => '[ting_object:title]',
      ),
      'schema_movie.@id' => array(
        'value' => '[current-page:url]',
      ),
      'schema_movie.description' => array(
        'value' => '[ting_object:abstract]',
      ),
      'schema_movie.image' => array(
        'value' => 'a:5:{s:5:"@type";s:11:"ImageObject";s:20:"representativeOfPage";s:4:"True";s:3:"url";s:37:"[ting_object:ding_seo_ting_cover:url]";s:5:"width";s:39:"[ting_object:ding_seo_ting_cover:width]";s:6:"height";s:40:"[ting_object:ding_seo_ting_cover:height]";}',
      ),
      'schema_movie.duration' => array(
        'value' => '[ting_object:ding_seo_extent]',
      ),
      'schema_movie.actor' => array(
        'value' => 'a:3:{s:5:"pivot";s:1:"1";s:5:"@type";s:6:"Person";s:4:"name";s:57:"[ting_object:ding_seo_creators_contributers:actor_names],";}',
      ),
      'schema_movie.director' => array(
        'value' => 'a:3:{s:5:"pivot";s:1:"1";s:5:"@type";s:6:"Person";s:4:"name";s:60:"[ting_object:ding_seo_creators_contributers:director_names],";}',
      ),
      'schema_movie.musicBy' => array(
        'value' => 'a:3:{s:5:"pivot";s:1:"1";s:5:"@type";s:6:"Person";s:4:"name";s:60:"[ting_object:ding_seo_creators_contributers:composer_names],";}',
      ),
      'schema_movie.producer' => array(
        'value' => 'a:3:{s:5:"pivot";s:1:"1";s:5:"@type";s:6:"Person";s:4:"name";s:60:"[ting_object:ding_seo_creators_contributers:producer_names],";}',
      ),
    ),
  );

  return $config;
}
