<?php
/**
 * @file
 * ding_library.openlayers_layers.inc
 */

/**
 * Implements hook_openlayers_layers().
 */
function ding_library_openlayers_layers() {
  $export = array();

  $openlayers_layers = new stdClass;
  $openlayers_layers->disabled = FALSE; /* Edit this to true to make a default openlayers_layers disabled initially */
  $openlayers_layers->api_version = 1;
  $openlayers_layers->name = 'mapquest_open';
  $openlayers_layers->title = 'MapQuest Open';
  $openlayers_layers->description = 'OpenStreetMap-based maps from MapQuest.';
  $openlayers_layers->data = array(
    'base_url' => 'http://otile3.mqcdn.com/tiles/1.0.0/osm/${z}/${x}/${y}.png',
    'layer_type' => 'openlayers_layer_type_xyz',
    'resolutions' => array(
      0 => 156543.0339,
      1 => 78271.51695,
      2 => 39135.758475,
      3 => 19567.8792375,
      4 => 9783.93961875,
      5 => 4891.969809375,
      6 => 2445.9849046875,
      7 => 1222.9924523438,
      8 => 611.49622617188,
      9 => 305.74811308594,
      10 => 152.87405654297,
      11 => 76.437028271484,
      12 => 38.218514135742,
      13 => 19.109257067871,
      14 => 9.5546285339355,
      15 => 4.7773142669678,
      16 => 2.3886571334839,
      17 => 1.1943285667419,
      18 => 0.59716428337097,
    ),
    'projection' => array(
      0 => '900913',
    ),
  );
  $export['mapquest_open'] = $openlayers_layers;

  return $export;
}
