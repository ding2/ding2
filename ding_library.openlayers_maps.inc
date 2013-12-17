<?php
/**
 * @file
 * ding_library.openlayers_maps.inc
 */

/**
 * Implements hook_openlayers_maps().
 */
function ding_library_openlayers_maps() {
  $export = array();

  $openlayers_maps = new stdClass();
  $openlayers_maps->disabled = FALSE; /* Edit this to true to make a default openlayers_maps disabled initially */
  $openlayers_maps->api_version = 1;
  $openlayers_maps->name = 'ding_library_map';
  $openlayers_maps->title = 'Ding! library map';
  $openlayers_maps->description = 'Map of libraries ';
  $openlayers_maps->data = array(
    'width' => 'auto',
    'height' => '275px',
    'image_path' => '',
    'css_path' => '',
    'proxy_host' => '',
    'hide_empty_map' => 0,
    'center' => array(
      'initial' => array(
        'centerpoint' => '10.201468, 56.156099',
        'zoom' => '12',
      ),
      'restrict' => array(
        'restrictextent' => 0,
        'restrictedExtent' => '',
      ),
    ),
    'behaviors' => array(
      'openlayers_behavior_tooltip' => array(
        'layers' => array(
          'ding_library_openlayers_1' => 'ding_library_openlayers_1',
        ),
      ),
      'openlayers_behavior_fullscreen' => array(
        'activated' => 0,
      ),
      'openlayers_behavior_keyboarddefaults' => array(),
      'openlayers_behavior_navigation' => array(
        'zoomWheelEnabled' => 0,
        'documentDrag' => 0,
      ),
      'openlayers_behavior_panzoom' => array(),
    ),
    'default_layer' => 'osm_mapnik',
    'layers' => array(
      'osm_mapnik' => 'osm_mapnik',
      'ding_library_openlayers_1' => 'ding_library_openlayers_1',
    ),
    'layer_weight' => array(
      'ding_library_openlayers_1' => '0',
      'geofield_formatter' => '0',
    ),
    'layer_styles' => array(
      'geofield_formatter' => '0',
      'ding_library_openlayers_1' => '0',
    ),
    'layer_activated' => array(
      'ding_library_openlayers_1' => 'ding_library_openlayers_1',
      'geofield_formatter' => 0,
    ),
    'layer_switcher' => array(
      'geofield_formatter' => 0,
      'ding_library_openlayers_1' => 0,
    ),
    'projection' => 'EPSG:900913',
    'displayProjection' => 'EPSG:4326',
    'styles' => array(
      'default' => 'default',
      'select' => 'default',
      'temporary' => 'default',
    ),
  );
  $export['ding_library_map'] = $openlayers_maps;

  return $export;
}
