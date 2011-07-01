<?php

/**
 * Implementation of hook_ctools_plugin_api().
 */
function ding_tabroll_ctools_plugin_api() {
  list($module, $api) = func_get_args();
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => 1);
  }
}

/**
 * Implementation of hook_imagecache_default_presets().
 */
function ding_tabroll_imagecache_default_presets() {
  $items = array(
    '460_240_crop' => array(
      'presetname' => '460_240_crop',
      'actions' => array(
        '0' => array(
          'weight' => '-10',
          'module' => 'imagecache',
          'action' => 'imagecache_scale',
          'data' => array(
            'width' => '460',
            'height' => '',
            'upscale' => 1,
          ),
        ),
        '1' => array(
          'weight' => '-9',
          'module' => 'imagecache',
          'action' => 'imagecache_crop',
          'data' => array(
            'width' => '460',
            'height' => '240',
            'xoffset' => '',
            'yoffset' => '',
          ),
        ),
        '2' => array(
          'weight' => '0',
          'module' => 'imagecache',
          'action' => 'imagecache_desaturate',
          'data' => array(),
        ),
      ),
    ),
  );
  return $items;
}

/**
 * Implementation of hook_node_info().
 */
function ding_tabroll_node_info() {
  $items = array(
    'rolltab' => array(
      'name' => t('Rullefane'),
      'module' => 'features',
      'description' => t('Rullefaner vises i en Fanerulle (Tabroll), hvor en fane afløser den næste i karrusel'),
      'has_title' => '1',
      'title_label' => t('Titel'),
      'has_body' => '0',
      'body_label' => '',
      'min_word_count' => '0',
      'help' => t('En Fanerulle indeholder 5 rullefaner. Det er de 5 nyeste aktive faner, der vises. NB: Slideshowet med fanerne kan kun køre når der er mindst 5 faner oprettet.'),
    ),
  );
  return $items;
}

/**
 * Implementation of hook_views_api().
 */
function ding_tabroll_views_api() {
  return array(
    'api' => '2',
  );
}
