<?php

/**
 * @file
 * ding_interests.features.field_instance.inc
 */

/**
 * Implements hook_field_default_field_instances().
 */
function ding_interests_field_default_field_instances() {
  $field_instances = array();

  // Exported field_instance: 'taxonomy_term-ding_content_tags-field_list_image'
  $field_instances['taxonomy_term-ding_content_tags-field_list_image'] = array(
    'bundle' => 'ding_content_tags',
    'deleted' => 0,
    'description' => 'Upload et billede som vises i lister',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'image',
        'settings' => array(
          'image_link' => '',
          'image_style' => '',
        ),
        'type' => 'image',
        'weight' => 1,
      ),
    ),
    'entity_type' => 'taxonomy_term',
    'field_name' => 'field_list_image',
    'label' => 'Liste billede',
    'required' => 0,
    'settings' => array(
      'alt_field' => 0,
      'default_image' => 0,
      'file_directory' => 'list',
      'file_extensions' => 'png gif jpg jpeg',
      'max_filesize' => '',
      'max_resolution' => '',
      'min_resolution' => '',
      'title_field' => 0,
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'media',
      'settings' => array(
        'allowed_schemes' => array(
          'public' => 'public',
          'vimeo' => 0,
          'youtube' => 0,
        ),
        'allowed_types' => array(
          'audio' => 0,
          'document' => 0,
          'image' => 'image',
          'video' => 0,
        ),
        'browser_plugins' => array(
          'ding_content' => 0,
          'media_default--media_browser_1' => 0,
          'media_default--media_browser_my_files' => 0,
          'media_internet' => 0,
          'upload' => 0,
          'youtube' => 0,
        ),
        'progress_indicator' => 'throbber',
      ),
      'type' => 'media_generic',
      'weight' => 32,
    ),
  );

  // Exported field_instance:
  // 'taxonomy_term-ding_content_tags-field_search_string'
  $field_instances['taxonomy_term-ding_content_tags-field_search_string'] = array(
    'bundle' => 'ding_content_tags',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => 'Skriv den søgestreng som systemet skal bruge til at finde materialer i brønden, som matcher dette tag.',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'text',
        'settings' => array(),
        'type' => 'text_default',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'taxonomy_term',
    'field_name' => 'field_search_string',
    'label' => 'Søgestreng',
    'required' => 0,
    'settings' => array(
      'text_processing' => 0,
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'text',
      'settings' => array(
        'size' => 60,
      ),
      'type' => 'text_textfield',
      'weight' => 31,
    ),
  );

  // Exported field_instance:
  // 'taxonomy_term-ding_content_tags-field_status'
  $field_instances['taxonomy_term-ding_content_tags-field_status'] = array(
    'bundle' => 'ding_content_tags',
    'default_value' => array(
      0 => array(
        'tid' => 61,
      ),
    ),
    'deleted' => 0,
    'description' => 'Angiv interesse status for dette tag.',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'taxonomy',
        'settings' => array(),
        'type' => 'taxonomy_term_reference_link',
        'weight' => 3,
      ),
    ),
    'entity_type' => 'taxonomy_term',
    'field_name' => 'field_status',
    'label' => 'Status',
    'required' => 0,
    'settings' => array(
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'options',
      'settings' => array(),
      'type' => 'options_select',
      'weight' => 34,
    ),
  );

  // Exported field_instance:
  // 'taxonomy_term-ding_content_tags-field_title_image'
  $field_instances['taxonomy_term-ding_content_tags-field_title_image'] = array(
    'bundle' => 'ding_content_tags',
    'deleted' => 0,
    'description' => 'Upload et billede som vises på tag siden.',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'image',
        'settings' => array(
          'image_link' => '',
          'image_style' => '',
        ),
        'type' => 'image',
        'weight' => 2,
      ),
    ),
    'entity_type' => 'taxonomy_term',
    'field_name' => 'field_title_image',
    'label' => 'Titel Billede',
    'required' => 0,
    'settings' => array(
      'alt_field' => 0,
      'default_image' => 0,
      'file_directory' => '',
      'file_extensions' => 'png gif jpg jpeg',
      'max_filesize' => '',
      'max_resolution' => '',
      'min_resolution' => '',
      'title_field' => 0,
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'media',
      'settings' => array(
        'allowed_schemes' => array(
          'public' => 'public',
          'vimeo' => 0,
          'youtube' => 0,
        ),
        'allowed_types' => array(
          'audio' => 0,
          'document' => 0,
          'image' => 'image',
          'video' => 0,
        ),
        'browser_plugins' => array(
          'ding_content' => 0,
          'media_default--media_browser_1' => 0,
          'media_default--media_browser_my_files' => 0,
          'media_internet' => 0,
          'upload' => 0,
          'youtube' => 0,
        ),
        'progress_indicator' => 'throbber',
      ),
      'type' => 'media_generic',
      'weight' => 33,
    ),
  );

  // Translatables
  // Included for use with string extractors like potx.
  t('Angiv interesse status for dette tag.');
  t('Liste billede');
  t('Skriv den søgestreng som systemet skal bruge til at finde materialer i brønden, som matcher dette tag.');
  t('Status');
  t('Søgestreng');
  t('Titel Billede');
  t('Upload et billede som vises i lister');
  t('Upload et billede som vises på tag siden.');

  return $field_instances;
}
