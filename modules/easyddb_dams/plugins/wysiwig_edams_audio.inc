<?php
/**
 * @file
 * Contains definition of audio button plugin.
 */

/**
 * AAA.
 *
 * @return mixed
 *   AA.
 */
function easyddb_dams_wysiwig_edams_audio_plugin() {
  $libraries = module_invoke('media', 'library');
  foreach ($libraries as $name => $library) {
    drupal_add_library('easyddb_dams', $name);
  }

  $plugins['wysiwig_edams_audio'] = [
    'title' => t('DAMS audio'),
    'icon file' => 'wysiwig_edams_audio.png',
    'icon title' => t('DAMS audio'),
    'settings' => [
      'global' => [
        'enabledPlugins' => variable_get('media_wysiwyg_wysiwyg_browser_plugins', []),
        'file_directory' => variable_get('media_wysiwyg_wysiwyg_upload_directory', ''),
        'types' => ['audio'],
      ],
    ],
  ];

  return $plugins;
}
