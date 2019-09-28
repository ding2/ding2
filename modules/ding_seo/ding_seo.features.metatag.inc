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
        'value' => 'a:4:{s:5:"@type";s:6:"Person";s:3:"@id";s:20:"[ting_object:author]";s:4:"name";s:20:"[ting_object:author]";s:3:"url";s:18:"[current-page:url]";}',
      ),
      'schema_book.@id' => array(
        'value' => '[current-page:url]',
      ),
      'schema_book.description' => array(
        'value' => '[ting_object:ting_abstract]',
      ),
      'schema_book.url' => array(
        'value' => '[current-page:url]',
      ),
    ),
  );

  // Exported Metatag config instance: ting_object:movie.
  $config['ting_object:movie'] = array(
    'instance' => 'ting_object:movie',
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
    ),
  );

  return $config;
}
