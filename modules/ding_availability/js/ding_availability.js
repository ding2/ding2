/**
 * @file
 * JavaScript behaviours for fetching and displaying availability.
 */

(function ($) {
  "use strict";

  // Cache of fetched availability information.
  Drupal.DADB = {};

  Drupal.behaviors.ding_availability = {
    attach: function (context) {
      var settings = Drupal.settings;
      var ids = [];
      var html_ids = [];

      // Loop through the materials given in the settings and collect
      // HTML ids and entity_ids.
      if (settings.hasOwnProperty('ding_availability')) {
        $.each(settings.ding_availability, function (id, entity_ids) {
          $.each(entity_ids, function (index, entity_id) {
            if (Drupal.DADB[entity_id] === undefined) {
              Drupal.DADB[entity_id] = null;
              ids.push(entity_id);
              html_ids.push(id);
            }
          });
        });
      }

      // If there's any reservation buttons, switch to holdings. We have
      // periodicals that's a bit off an odd one in that they can both
      // have issues, which means that the reservation button for the
      // main object should be disabled, or not have any issues, which
      // means that it should be left alone. So we need to fetch full
      // holdings in order to determine whether the material is a
      // periodical. This is a bit of a hack, but it's the quickest way
      // of fixing the problem right now.
      if ($('.reserve-button').size() > 0) {
        settings.ding_availability_mode = 'holdings';
      }

      $.each(html_ids, function (index, id) {
        $('#' + id).addClass('pending');
      });

      // Fetch availability.
      if (ids.length > 0) {
        var mode = settings.ding_availability_mode ? settings.ding_availability_mode : 'items';
        var path = settings.basePath + 'ding_availability/' + mode + '/' + ids.join(',');
        $.ajax({
          dataType: "json",
          url: path,
          success: function (data) {
            $.each(data, function (id, item) {
              // Update cache.
              Drupal.DADB[id] = item;
            });

            $.each(settings.ding_availability, function (id, entity_ids) {
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
          $.each(settings.ding_availability, function (id, entity_ids) {
            ding_availability_update_availability(id, entity_ids);
          });
        }
      }
    }
  };

  /**
   * Update availability information.
   *
   * Add classes to reservation texts and display reservation button based on
   * availability information.
   *
   * @param id
   *   HTML id of the availability to update.
   * @param entity_ids
   *   Entity id for which to update availability information.
   */
  function ding_availability_update_availability(id, entity_ids) {
    var available = false;
    var reservable = false;
    var element = $('#' + id);
    element.removeClass('pending').addClass('processed');

    $.each(entity_ids, function (index, entity_id) {
      // Reserve button.
      var reserve_button = element.parents('.ting-object:first, .material-item:first').find('a[id$=' + entity_id + '].reserve-button');

      if (Drupal.DADB[entity_id]) {
        var available = available || Drupal.DADB[entity_id]['available'];
        var reservable = reservable || Drupal.DADB[entity_id]['reservable'];

        // Special handling for periodicals.
        if (typeof Drupal.DADB[entity_id]['is_periodical'] !== 'undefined' &&
            Drupal.DADB[entity_id]['is_periodical']) {
          // The main object of a periodical is neither available nor
          // reservable, the individual issues is.
          available = reservable = false;
        }
        var classes = [];

        classes.push(available ? 'available' : 'unavailable');
        classes.push(reservable ? 'reservable' : 'not-reservable');

        $.each(classes, function (i, class_name) {
          element.addClass(class_name);

          // Add class to reserve button.
          if (reserve_button.length) {
            reserve_button.addClass(class_name);
          }
        });

        if (available && !reservable) {
          reserve_button.removeClass('available').addClass('unavailable');
        }
      }
      else {
        reserve_button.addClass('not-reservable');
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
    $.each(entity_ids, function (i, entity_id) {
      if (Drupal.DADB[entity_id] && (Drupal.DADB[entity_id]['holdings'])) {
        // Insert/update holding information for material.
        $('#' + id).html(Drupal.DADB[entity_id].html);
      }
    });
  }

})(jQuery);
