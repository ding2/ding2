/**
 * @file
 * JavaScript behaviours for fetching and displaying availability information
 * on TingEntities.
 */
(function($) {
  "use strict";

  // Cache of fetched availability information.
  Drupal.DADB = {};

  Drupal.behaviors.dingAvailabilityAttach = {
    attach: function(context, settings) {
      var ids = [];
      var html_ids = [];

      // Extract entity ids from Drupal settings array.
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

      // Fetch availability.
      if (ids.length > 0) {
        var mode = settings.ding_availability_mode ? settings.ding_availability_mode : 'items';
        var path = settings.basePath + settings.pathPrefix + 'ding_availability/' + mode + '/' + ids.join(',');
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
                update_availability(id, entity_ids[0]);
              }
            });
            update_availability_remove_pending();
          },
          error: function (xhr, status, error) {
            $('div.loader').remove();
          }
        });
      }
      else {
        // Apply already fetched availability, if any.
        if (settings.hasOwnProperty('ding_availability')) {
          $.each(settings.ding_availability, function(id, entity_ids) {
            update_availability(id, entity_ids[0]);
          });
          update_availability_remove_pending();
        }
      }

      /**
       * Update availability on the page.
       *
       * The array of entity_ids is an array as we only show one availability
       * label per material type. So if one of these have an available status
       * the label have to reflect this.
       *
       * @param id
       *   The element id that this should target.
       * @param entity_id
       *   Updated entity.
       */
      function update_availability(id, entity_id) {
        // Default the status to not available and not reservable.
        var status = {
          available: false,
          reservable: false
        };

        // Loop over the entity ids and if one has available or reservable
        // true save that value.
        if (Drupal.DADB[entity_id]) {
          status.available = status.available || Drupal.DADB[entity_id].available;
          status.reservable = status.reservable || Drupal.DADB[entity_id].reservable;
        }

        var element = $('#' + id);
        if (element.hasClass('pending')) {
          element.removeClass('pending').addClass('processed');
        }

        update_availability_elements(element, status);
      }

      /**
       * Helper function to crate labels groups and move the materials based on
       * availability.
       *
       * @param element
       *   The target element (material that should be moved).
       * @param status
       *   Structure with available and reservable state.
       */
      function update_availability_type(element, status) {
        var groups_wrapper = element.closest('.search-result--availability');
        var reservable = status.reservable;
        var available = status.available;

        var group = null;
        if (available) {
          group = $('.js-available', groups_wrapper);

          if (group.length === 0) {
            group = $('<p class="js-available">' + Drupal.t('Available') + ': </p>');
          }
          groups_wrapper.append(group);
        }
        else if (reservable) {
          group = $('.js-reservable', groups_wrapper);
          if (group.length === 0) {
            group = $('<p class="js-reservable">' + Drupal.t('Reservable') + ': </p>');
            groups_wrapper.append(group);
          }
        }
        else {
          group = $('.js-unavailable', groups_wrapper);

          if (group.length === 0) {
            var msg = Drupal.t('Not available');
            if (Drupal.settings.hasOwnProperty('ding_ill')) {
              var msg = Drupal.t('Order from another library');
            }
            group = $('<p class="js-unavailable">' + msg + ': </p>');
            groups_wrapper.append(group);
          }
        }

        // Move the element into that type.
        group.append(element);

        // Remove empty groups.
        $('.js-available, .js-reservable, .js-unavailable', groups_wrapper)
          .not(':has(.js-search-result--availability-link)')
          .remove();
      }

      /**
       * Removes js-pending groups (labels) if they are empty or changes the
       * label to "Can be obtained". This should be called as the last function
       * in updating availability information and see as a clean-up function.
       */
      function update_availability_remove_pending() {
        // Loop over all pending availability groups.
        $('.js-pending').each(function() {
          var elm = $(this);
          var children = elm.children();
          if (children.length) {
            // Change the label from pending.
            var label = elm.contents().first()[0];
            label.nodeValue = Drupal.t('Can be obtained') + ': ';
          }
          else {
            // The current pending group is empty, so simply remove it.
            elm.remove();
          }
        });
      }

      /**
       * Add class to both an element and the reservation button.
       *
       * @param element
       *   jQuery availability element to add the class to.
       * @param btn
       *   Reservation button to add the class to.
       * @param status
       *   Structure with available and reservable state.
       */
      function update_availability_elements(element, status) {
        var class_name = null;

        for (var i in status) {
          if (status[i] === true) {
            class_name = i;
          }
          element.addClass(class_name);
        }

        update_availability_type(element, status);
      }
    }
  };
})(jQuery);
