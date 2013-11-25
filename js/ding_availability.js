/**
 * @file ding.availability.js
 * JavaScript behaviours for fetching and displaying availability.
 */

(function($) {
  "use strict";

  // Cache of fetched availability information.
  Drupal.DADB = {};

  Drupal.behaviors.dingAvailabilityAttach = {
    attach: function(context, settings) {
      var ids = [];
      var html_ids = [];

      // Extract entity ids and add them to the settings array.
      if (settings.hasOwnProperty('ding_availability')) {
        $.each(settings.ding_availability, function(id, entity_ids) {
          $.each(entity_ids, function(index, entity_id) {
            if (Drupal.DADB[entity_id] === undefined) {
              Drupal.DADB[entity_id] = null;
              ids.push(entity_id);
              html_ids.push(id);
            }
          });
        });
      }

      $.each(html_ids, function(index, id) {
        $('#' + id).addClass('pending');
      });

      // Fetch availability.
      if (ids.length > 0) {
        var mode = settings.ding_availability_mode ? settings.ding_availability_mode : 'items';
        var path = settings.basePath + 'ding_availability/' + mode + '/' + ids.join(',');
        $.ajax({
          dataType: "json",
          url: path,
          success: function(data) {
            $.each(data, function(id, item) {
              // Update cache.
              Drupal.DADB[id] = item;
            });

            $.each(settings.ding_availability, function(id, entity_ids) {
              if (id.match(/^availability-/)) {
                // Update availability indicators.
                update_availability(id, entity_ids);
              }
              else {
                // Update holding information.
                update_holdings(id, entity_ids);
              }
            });
          }
        });
      }
      else {
        // Apply already fetched availability, if any.
        if (settings.hasOwnProperty('ding_availability')) {
          $.each(settings.ding_availability, function(id, entity_ids) {
            update_availability(id, entity_ids);
          });
        }
      }

      function update_availability(id, entity_ids) {
        var available = false;
        var reservable = false;
        var is_internet = false;
        $.each(entity_ids, function(index, entity_id) {
          if (Drupal.DADB[entity_id]) {
            available = available || Drupal.DADB[entity_id]['available'];
            reservable = reservable || Drupal.DADB[entity_id]['reservable'];
            is_internet = is_internet || Drupal.DADB[entity_id]['is_internet'];
          }
        });

        var element = $('#' + id);
        element.removeClass('pending').addClass('processed');

        // Reserve button
        var reserver_btn = element.parents('.ting-object:first').find('[id^=ding-reservation-reserve-form]');

        if (available) {
          element.addClass('available');

          // Add class to reserve button
          if (reserver_btn.length) {
            reserver_btn.addClass('available');
          }
        }
        else {
          element.addClass('unavailable');

          // Add class to reserve button
          if (reserver_btn.length) {
            reserver_btn.addClass('unavailable');
          }
        }
        
        if (reservable) {
          element.addClass('reservable');

          // Add class to reserve button
          if (reserver_btn.length) {
            reserver_btn.addClass('reservable');
          }
        }

        if (!available && !reservable) {
          element.addClass('not-reservable');

          // Add class to reserve button
          if (reserver_btn.length) {
            reserver_btn.addClass('not-reservable');
          }
        }
      }

      function update_holdings(id, entity_ids) {
        var entity_id = entity_ids.pop();
        if (Drupal.DADB[entity_id] && (Drupal.DADB[entity_id]['holdings'])) {
          // Show status for material.
          $('#' + id).append(Drupal.DADB[entity_id].html);
        }
      }
    }
  };
})(jQuery);
