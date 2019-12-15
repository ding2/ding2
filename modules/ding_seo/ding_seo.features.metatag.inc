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
