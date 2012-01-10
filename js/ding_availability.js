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
      $.each(settings.ding_availability, function(id, entity_ids) {
        $.each(entity_ids, function(index, entity_id) {
          if (Drupal.DADB[entity_id] === undefined) {
            Drupal.DADB[entity_id] = null;
            ids.push(entity_id);
            html_ids.push(id);
          }
        });
      });

     $.each(html_ids, function(index, id) {
        $('#' + id).addClass('pending');
      });

      // Fetch availability.
      if (ids.length > 0) {
        $.getJSON(settings.basePath + 'ding_availability/' + (settings.ding_availability_mode ? settings.ding_availability_mode: 'items') + '/' + ids.join(','), {}, update);
      }
      else {
        // Apply already fetched availability
        $.each(settings.ding_availability, function(id, entity_ids) {
          updateAvailability(id, entity_ids);
        });
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
        $.each(entity_ids, function(index, entity_id) {
          if (Drupal.DADB[entity_id]) {
            available = available || Drupal.DADB[entity_id]['available'];
            reservable = reservable || Drupal.DADB[entity_id]['reservable'];
          }
        });

        $('#' + id).removeClass('pending');
        $('#' + id).addClass('processed');

        if (available) {
          $('#' + id).addClass('available');
        }
        if (reservable) {
          $('#' + id).addClass('reservable');
        }

        if (available && reservable) {
          $('#' + id).attr('title', Drupal.t('available'));
        }
        else if (!available && reservable) {
          $('#' + id).attr('title', Drupal.t('on loan'));
        }
        else if (available && ! reservable) {
          $('#' + id).attr('title', Drupal.t('not reservable'));
        }
        else if (!available && ! reservable) {
          $('#' + id).attr('title', Drupal.t('unavailable'));
        }
      }

      function updateHoldings(id, entity_ids) {
        var entity_id = entity_ids.pop();
          if (Drupal.DADB[entity_id] && (Drupal.DADB[entity_id]['holdings'] || Drupal.DADB[entity_id]['holdings_available'])) {
          var holdings;
	  var length;

          // Use holdings_available, if set and entity is not a periodical.
          if (Drupal.DADB[entity_id]['holdings_available'] && !Drupal.DADB[entity_id]['is_periodical'] ) {
              holdings = Drupal.DADB[entity_id]['holdings_available'];
              length = holdings.length;
          }
          else {
            holdings = Drupal.DADB[entity_id]['holdings'];
            //holdings is an object - not array
            length = Object.keys(holdings).length;
          }

          
          if (length > 0) {
            $('#' + id).append('<h2>' + Drupal.t('Holdings available on the shelf') + '</h2>');
            $('#' + id).append('<ul>');
            var container = $('#' + id + ' ul');
            $.each(holdings, function(i, holding) {
              container.append('<li>' + holding + '</li>');
            });
          }
        }
      }

    }
  };

})(jQuery);

