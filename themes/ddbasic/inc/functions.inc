<?php
/**
 * @file
 * Provides frequently used functions that get theme info, settings and
 * other data.
 */

/**
 * Return lists of CSS files to unset.
 *
 * This returns a very small amount of data (< 10kb), but is very expensive
 * to get which is why its cached in the database. Without caching the theme
 * settings page takes at least 8 seconds to load if the Unset CSS extension
 * is enabled, and that's no fun.
 *
 * @param string $theme_name
 *   Usually the active theme.
 */
function ddbasic_get_css_files($theme_name) {
  $styles = &drupal_static(__FUNCTION__, array());
  if (empty($styles)) {
    if ($cache = cache_get('ddbasic_get_css_files')) {
      $styles = $cache->data;
    }
    else {

      // Contrib module.
      $module_data = system_rebuild_module_data();
      foreach ($module_data as $module => $data) {
        if ($data->status && !empty($data->info['stylesheets'])) {
          foreach ($data->info['stylesheets'] as $media => $content) {
            foreach ($content as $file) {
              $styles[$file] = array(
                'type' => 'contrib',
                'source' => $module,
              );
            }
          }
        }
      }

      // Libraries.
      if (module_exists('libraries')) {
        $libraries = libraries_get_libraries();
        $extension = 'css';
        foreach ($libraries as $lib) {
          $files = file_scan_directory($lib, '/\.' . $extension . '$/', array('recurse' => TRUE));
          $libraries[$lib] = $files;
        }
        foreach ($libraries as $lib_key => $library) {
          if (is_array($library) && !empty($library)) {
            foreach ($library as $lib_file) {
              $styles[$lib_file->uri] = array(
                'type' => 'library',
                'source' => $lib_file->uri,
              );
            }
          }
        }
      }

      // Theme info defined files.
      $info_data = ddbasic_get_info_trail($theme_name);
      foreach ($info_data as $provider => $theme_info) {
        foreach ($theme_info as $this_info => $info) {
          if ($this_info == 'info') {
            // Core defined.
            if (isset($info['unset_core'])) {
              foreach ($info['unset_core'] as $module_path => $description) {
                $styles[$module_path] = array(
                  'type' => 'unset_core',
                  'source' => $description,
                );
              }
            }
            // Theme defined explicit excludes.
            if (isset($info['unset_css'])) {
              foreach ($info['unset_css'] as $module_path => $description) {
                $styles[$module_path] = array(
                  'type' => 'user_defined',
                  'source' => $description,
                );
              }
            }
            // Theme and ancestors, never show in admin.
            foreach ($info['stylesheets'] as $media => $stylesheets) {
              foreach ($stylesheets as $file => $path) {
                $styles[$path] = array(
                  'type' => 'theme',
                  'source' => $provider,
                );
              }
            }
          }
        }
      }

      cache_set('ddbasic_get_css_files', $styles, 'cache');
    }
  }

  return $styles;
}

/**
 * Returns an array keyed by theme name.
 *
 * Return the all the info file data for a particular theme including base
 * themes. Parts of this function are shamelessly ripped from Drupal core's
 * _drupal_theme_initialize().
 *
 * @param string $theme_name
 *   Usually the active theme.
 */
function ddbasic_get_info_trail($theme_name) {
  $info_trail = &drupal_static(__FUNCTION__, array());
  if (empty($info_trail)) {
    $lt = list_themes();

    // First check for base themes and get info.
    $base_theme = array();
    $ancestor = $theme_name;
    while ($ancestor && isset($lt[$ancestor]->base_theme)) {
      $ancestor = $lt[$ancestor]->base_theme;
      $base_theme[] = $lt[$ancestor];
    }
    foreach ($base_theme as $base) {
      $info_trail[$base->name]['info'] = $base->info;
    }

    // Now the active theme.
    $info_trail[$theme_name]['info'] = $lt[$theme_name]->info;
  }

  return $info_trail;
}
