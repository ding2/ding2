/**
 * @file ding.availability.js
 * JavaScript behaviours for fetching and displaying availability.
 */

(function($) {
  "use strict";

  // Cache of fetched availability information.
  Drupal.DADB = {};

  $(document).ready(function() {
    var settings = Drupal.settings;
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
              ding_availability_update_availability(id, entity_ids);
            }
            else {
              // Update holding information.
              ding_availability_update_holdings(id, entity_ids);
            }
          });
        },
        error: function () {
          $('div.loader').remove();
        }
      });
    }
    else {
      // Apply already fetched availability, if any.
      if (settings.hasOwnProperty('ding_availability')) {
        $.each(settings.ding_availability, function(id, entity_ids) {
          ding_availability_update_availability(id, entity_ids);
        });
      }
    }
  });


  /**
   * Update availability information.
   *
   * Add classes to reservation texts and display reservation button based on
   * availability information
   *
   * @param id
   *   HTML id of the availability to update.
   * @param entity_ids
   *   Entity id for which to update availability information.
   */
  function ding_availability_update_availability(id, entity_ids) {
    var available = false;
    var reservable = false;
    var is_internet = false;
    var element = $('#' + id);
    element.removeClass('pending').addClass('processed');

    $.each(entity_ids, function(index, entity_id) {
      // Reserve button
      var reserver_btn = element.parents('.ting-object:first, .material-item:first').find('a[id$=' + entity_id + '].reserve-button');

      if (Drupal.DADB[entity_id]) {
        available = available || Drupal.DADB[entity_id]['available'];
        reservable = reservable || Drupal.DADB[entity_id]['reservable'];
        is_internet = is_internet || Drupal.DADB[entity_id]['is_internet'];

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
        else {
          element.addClass('not-reservable');

          // Add class to reserve button
          if (reserver_btn.length) {
            reserver_btn.addClass('not-reservable');
          }
        }
      }

      else {
        reserver_btn.addClass('not-reservable');
      }
    });
  }

  /**
   * Update availability holdings information.
   *
   * Insert HTML with information about where the entities are located.
   *
   * @param id
   *   HTML id of the availability to update.
   * @param entity_ids
   *   Entity id for which to update availability holdings information.
   */
  function ding_availability_update_holdings(id, entity_ids) {
    var entity_id = entity_ids.pop();
    if (Drupal.DADB[entity_id] && (Drupal.DADB[entity_id]['holdings'])) {
      // Show status for material.
      $('#' + id).html(Drupal.DADB[entity_id].html);
    }
  }

})(jQuery);
