(function ($) {
  'use strict';

  let isInitialized = false;

  async function displayMap(wayfindingId) {
    const hasLocations = await window.libryWayfinding.wayfindingIdHasLocations(
      wayfindingId
    );

    // Check if a wayfindingId has any locations that can be shown on the map
    if (hasLocations) {
      const map = await window.libryWayfinding.createMap({
        // Container ID of the html element holding the map
        container: "wayfinding-map",
        center: { lng: 10.2151585, lat: 56.1531825 },
        zoom: 19.0,
        deviceLocation: {
          floor: 3,
          lngLat: { lng: 10.2151585, lat: 56.1531825 },
          heading: 70,
        },
        // Shows a dot indicating the current device/user location
        showDevicePosition: true,
        showAllPOIs: true,
      });

      map.updateDeviceLocation({
        lngLat: { lng: 10.2151585, lat: 56.1531825 },
      });

      // Add the wayfinding marker.
      map.addPoiMarkerByWayfindingId(wayfindingId, {
        color: "red",
        onClick: function (e, markerOpts) {
          alert(`You clicked ${wayfindingId.faust}`);
        },
      });
    } else {
      alert("There are no locations to show. Dont show map.");
    }
  }

  /**
   * Attach behaviour.
   */
  Drupal.behaviors.ding_wayfinding = {
    attach: function(context, settings) {
      if ($('#wayfinding-map').length) {
        const wayfindingId = settings.ding_wayfinding.id;

        if (isInitialized) {
          displayMap(wayfindingId);
        }
        else {
          let access = settings.ding_wayfinding.access;
          window.libryWayfinding
            .init(
              access.customerId,
              access.agency,
              access.apiKey,
            ).then(function () {
              isInitialized = true;
              displayMap(wayfindingId);
            }
          );
        }
      }
    }
  };

})(jQuery);
