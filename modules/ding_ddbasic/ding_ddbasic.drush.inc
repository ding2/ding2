<?php
/**
 * @file
 * Drush functions for the theme.
 */

function ding_ddbasic_drush_command() {
  return array(
    'ding-ddbasic-colorize-css' => array(
      'description' => 'Colorize the css files in the ddbasic theme',
      'aliases' => array('ddcc'),
    ),
  );
}

/**
 * Colorize css files.
 */
function drush_ding_ddbasic_colorize_css() {
  $colors = array();
  foreach (variable_get('theme_ddbasic_settings') as $key => $value) {
    if (strpos($key, 'color_') === 0) {
      $colors[substr($key, 6)] = $value;
    }
  }

  $theme_path = drupal_get_path('theme', 'ddbasic');
  $cssfiles = array_merge(
    file_scan_directory($theme_path . '/css', '/\.css$/'),
    file_scan_directory($theme_path . '/sass_css', '/\.css$/')
  );
  foreach ($cssfiles as &$cssfile) {
    $cssfile = drupal_realpath($cssfile->uri);
  }

  ding_ddbasic_colorize_css($cssfiles, $colors);
}
