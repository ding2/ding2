<?php
/**
 * @file
 * ding_content.features.filter.inc
 */

/**
 * Implements hook_filter_default_formats().
 */
function ding_content_filter_default_formats() {
  $formats = array();

  // Exported format: Wysiwyg.
  $formats['ding_wysiwyg'] = array(
    'format' => 'ding_wysiwyg',
    'name' => 'Wysiwyg',
    'cache' => 1,
    'status' => 1,
    'weight' => 0,
    'filters' => array(
      'media_filter' => array(
        'weight' => 0,
        'status' => 1,
        'settings' => array(),
      ),
      'image_resize_filter' => array(
        'settings' => array(
          'image_locations' => array(
            'local' => 'local'
          )
        ),
        'status' => 1,
        'weight' => 1
      ),
      'filter_html' => array(
        'weight' => 2,
        'status' => 1,
        'settings' => array(
          'allowed_html' => '<a> <p> <em> <strong> <cite> <blockquote> <code> <ul> <ol> <li> <dl> <dt> <dd> <table> <tr> <th> <td> <br>',
          'filter_html_help' => 1,
          'filter_html_nofollow' => 0,
        ),
      ),
      'filter_autop' => array(
        'weight' => 3,
        'status' => 1,
        'settings' => array(),
      ),
      'filter_url' => array(
        'weight' => 4,
        'status' => 1,
        'settings' => array(
          'filter_url_length' => 72,
        ),
      ),

      'filter_htmlcorrector' => array(
        'weight' => 5,
        'status' => 1,
        'settings' => array(),
      ),
    ),
  );

  return $formats;
}
