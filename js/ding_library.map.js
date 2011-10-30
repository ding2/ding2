/**
 * JavaScript code for the Ding! library map.
 *
 * Adds tooltips and other extra functionality to the map.
 */

(function ($) {
"use strict";
var map, mapContainer, markerIDMap = {}, markerLayer;

/**
 * Resize the map to the requested height.
 */
function resizeMap(height) {
  var center = map.openlayers.getCenter();

  // The height is some times set on both the map container and the
  // parent. This causes issues with resizing, so remove it.
  mapContainer.parent().height('auto');

  mapContainer.animate({'height': height + 'px'}, 1000, 'swing', function () {
    map.openlayers.updateSize();
    map.openlayers.panTo(center);
  });
}

/**
 * Change the map to its expanded state.
 */
function expandMap () {
  resizeMap(450);
}

/**
 * Go to a specific marker's location.
 */
function goToMarker(markerID) {
  var marker = markerLayer.features[markerID],
      latLng = new OpenLayers.LonLat(marker.geometry.x, marker.geometry.y);

  map.openlayers.setCenter(latLng, 15);
  expandMap();
}


$(function () {
  var page = $('#ding-library-page');

  // Get the map instance so we can bind events on it.
  mapContainer = page.find('.openlayers-map-ding_library_map');
  map = mapContainer.data('openlayers');
    
  if (map) {
    markerLayer = map.openlayers.layers[0];

    $.each(markerLayer.features, function (index, value) {
      markerIDMap[value.data.title] = index;
    });

    page.find('.library-list .views-row').each(function (index, Element) {
      var library = $(this),
          title = $.trim(library.find('.title').text());

      if (markerIDMap.hasOwnProperty(title)) {
        $('<a href="#ding-library-page">' + Drupal.t('Show on map') + '</a>')
          .click(function (evt) {
            goToMarker(markerIDMap[title]);
            evt.preventDefault();
          })
          .appendTo(library.find('.address'));
      }
    });
  }
});

}(jQuery));

