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

      $.each(html_ids, function (index, id) {
        $('#' + id).addClass('pending');
      });

      // Fetch availability.
      if (ids.length > 0) {
        var mode = settings.ding_availability_mode ? settings.ding_availability_mode : 'items';
        var path = settings.basePath + settings.pathPrefix + 'ding_availability/' + mode + '/' + ids.join(',');
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

            $(document).trigger('ding_availability_update_holdings');
            Drupal.attachBehaviors(context);
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
      if (Drupal.DADB[entity_id]) {
        var available = available || Drupal.DADB[entity_id]['available'];
        element.addClass(available ? 'available' : 'unavailable');
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
        var holdings = Drupal.DADB[entity_id];
        $('#' + id).html(holdings.html);
        Drupal.attachBehaviors($('#' + id));

        if (holdings.is_periodical) {
          // Hide all elements.
          $('.ding-periodical-issues li').children('.item-list').hide();

          // Add class to style the list as being expandable.
          $('.ding-periodical-fold').addClass('expand expand-more');

          // Attach click event to fold in/out the issues.
          $('.field-name-ding-availability-holdings .ding-periodical-fold').on("click", function() {
            $(this).next().toggle();
            $(this).next().toggleClass('expanded-periodicals');
            $(this).parent().toggleClass('expanded-periodicals-parent');
          });
        }
        // Don't show queue time if item not reservable.
        if (holdings.reservable === false) {
          $('#' + id + ' span.in-queue').hide();
        }
      }
      else {
        $('div.group-holdings-available').parent().parent().remove();
      }
    });
  }

})(jQuery);
