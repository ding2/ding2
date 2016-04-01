<?php
/**
 * @file
 * Contains definition of video button plugin.
 */

/**
 * AAA.
 *
 * @return mixed
 *   AA.
 */
function easyddb_dams_wysiwig_edams_video_plugin() {
  $libraries = module_invoke('media', 'library');
  foreach ($libraries as $name => $library) {
    drupal_add_library('easyddb_dams', $name);
  }

  $plugins['wysiwig_edams_video'] = [
    'title' => t('DAMS video'),
    'icon file' => 'wysiwig_edams_video.png',
    'icon title' => t('DAMS video'),
    'settings' => [
      'global' => [
        'enabledPlugins' => variable_get('media_wysiwyg_wysiwyg_browser_plugins', []),
        'file_directory' => variable_get('media_wysiwyg_wysiwyg_upload_directory', ''),
        'types' => ['video'],
      ],
    ],
  ];

  return $plugins;
}
