(function ($) {
  'use strict';

  let isInitialized = false;

  async function displayMap(wayfindingId, openPopup, zoomLevel) {
    const hasLocations = await window.libryWayfinding.wayfindingIdHasLocations(
      wayfindingId
    );

    // Check if a wayfindingId has any locations that can be shown on the map
    if (hasLocations) {
      console.log(zoomLevel);
      const map = await window.libryWayfinding.createMap({
        // Container ID of the html element holding the map
        container: "wayfinding-map",
        zoom: zoomLevel,
        showDevicePosition: true,
        showAllPOIs: true,
      });

      // Add the wayfinding marker.
      map.addPoiMarkerByWayfindingId(wayfindingId, {
        color: "red",
        onClick: function (e, markerOpts) {
          $('.map-info-wrapper').toggle();
        },
      }).then(function (markers) {
        // Update the map to show the floor the marker is on as default.
        let markerOpts = markers[0].markerOpts;
        map.setFloor(markerOpts.location.floor);
        if (openPopup) {
          $('.map-info-wrapper').toggle();
        }
      });

      // Attach close inside information popup.
      var button = document.querySelector('#toggleDetailsBtn');
      var details = document.querySelector('#mapPopoverDetails');
      button.addEventListener('click', function (event) {
            details.classList.toggle('hidden');
            button.classList.toggle('hidden');
        }
      );

      // Attach click handler to route button.
      $('.map-popover__btn').click(function() {
        navigator.geolocation.getCurrentPosition((position) => {
          map.updateDeviceLocation({
            lngLat: {
              lng: position.coords.longitude,
              lat: position.coords.latitude,
            }
          });
          map.findWayToPoiByWayfindingId(wayfindingId);
        });

      });
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
          displayMap(wayfindingId, settings.ding_wayfinding.openPopup, settings.ding_wayfinding.zoomLevel);
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
              displayMap(wayfindingId, settings.ding_wayfinding.openPopup, settings.ding_wayfinding.zoomLevel);
            }
          );
        }
      }
    }
  };

})(jQuery);
