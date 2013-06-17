/**
 * @file ding.availability.js
 * JavaScript behaviours for fetching and displaying availability.
 */

(function($) {

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
        $.getJSON(settings.basePath + 'ding_availability/' + (settings.ding_availability_mode ? settings.ding_availability_mode: 'items') + '/' + ids.join(','), {}, update);
      }
      else {
        // Apply already fetched availability, if any.
        if (settings.hasOwnProperty('ding_availability')) {
          $.each(settings.ding_availability, function(id, entity_ids) {
            updateAvailability(id, entity_ids);
          });
        }
      }

      function update(data, textData) {
        $.each(data, function(id, item) {
          // Update cache.
          Drupal.DADB[id] = item;
        });

        $.each(settings.ding_availability, function(id, entity_ids) {
          if (id.match(/^availability-/)) {
            // Update availability indicators.
            updateAvailability(id, entity_ids);
          }
          else {
            // Update holding information.
            updateHoldings(id, entity_ids);
          }
        });
      }

      function updateAvailability(id, entity_ids) {
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

        if (available) {
          element.addClass('available');
        }
        else {
          element.addClass('unavailable');
        }

        if (reservable) {
          element.addClass('reservable');
        }
        else {
          element.addClass('not-reservable');
        }

        if (available && reservable || is_internet) {
          element.attr('title', Drupal.t('available'));
          // If availability is a link append the status inside the link.
          if (settings.ding_availability_link === 1) {
            $('a', element).append('<span class="availability-status">' + Drupal.t('available') + '<span>');
          }
        }
        else if (!available && reservable) {
          element.attr('title', Drupal.t('on loan'));
          // If availability is a link append the status inside the link.
          if (settings.ding_availability_link === 1) {
            $('a', element).append('<span class="availability-status">' + Drupal.t('on loan') + '<span>');
          }        }
        else if (available && ! reservable) {
          element.attr('title', Drupal.t('not reservable'));
          // If availability is a link append the status inside the link.
          if (settings.ding_availability_link === 1) {
            $('a', element).append('<span class="availability-status">' + Drupal.t('not reservable') + '<span>');
          }
        }
        else if (!available && ! reservable) {
          element.attr('title', Drupal.t('unavailable'));
          // If availability is a link append the status inside the link.
          if (settings.ding_availability_link === 1) {
            $('a', element).append('<span class="availability-status">' + Drupal.t('unavailable') + '<span>');
          }
        }
      }

      function updateHoldings(id, entity_ids) {
        var entity_id = entity_ids.pop();
        if (Drupal.DADB[entity_id] && (Drupal.DADB[entity_id]['holdings'])) {
          // Show status for material.
          $('#' + id).append(Drupal.DADB[entity_id].html) ;
        }
      }
    }
  };
})(jQuery);
