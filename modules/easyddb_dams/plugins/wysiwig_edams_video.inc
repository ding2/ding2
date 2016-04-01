<?php
/**
 * @file
 * Contains definition of image button plugin.
 */

/**
 * AAA.
 *
 * @return mixed
 *   AA.
 */
function easyddb_dams_wysiwig_edams_image_plugin() {
  $libraries = module_invoke('media', 'library');
  foreach ($libraries as $name => $library) {
    drupal_add_library('easyddb_dams', $name);
  }

  $plugins['wysiwig_edams_image'] = [
    'title' => t('DAMS image'),
    'icon file' => 'wysiwig_edams_image.png',
    'icon title' => t('DAMS image'),
    'settings' => [
      'global' => [
        'enabledPlugins' => variable_get('media_wysiwyg_wysiwyg_browser_plugins', []),
        'file_directory' => variable_get('media_wysiwyg_wysiwyg_upload_directory', ''),
        'types' => ['image'],
      ],
    ],
  ];

  return $plugins;
}
