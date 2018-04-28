/**
 * @file
 * JavaScript behaviours for fetching and displaying availability.
 */

(function ($) {
  "use strict";

  // Cache of fetched availability information.
  Drupal.DADB = {};

  /**
   * Update availability information.
   *
   * Add classes to reservation texts and display reservation button based on
   * availability information.
   *
   * @param provider_id
   *   Id for which to update availability information.
   * @param html_id
   *   HTML id for the element to update availability for.
   */
  function ding_availability_update_availability(provider_id, html_id) {
    var element = $('#' + html_id);
    element.removeClass('pending').addClass('processed');
    // Reserve button.
    var reserve_button = element.parents('.ting-object:first, .material-item:first').find('a[id$=' + provider_id + '].reserve-button');

    if (Drupal.DADB.hasOwnProperty(html_id)) {
      var item = Drupal.DADB[html_id];
      var available = available || item.available;
      var reservable = reservable || item.reservable;

      // Special handling for periodicals.
      if (item.hasOwnProperty('is_periodical') && item.is_periodical) {
        // The main object of a periodical is neither available nor
        // reservable, the individual issues is.
        available = reservable = false;
      }
      var classes = [];

      classes.push(available ? 'available' : 'unavailable');
      classes.push(reservable ? 'reservable' : 'not-reservable');
      classes = classes.join(' ');

      element.addClass(classes);
      reserve_button.addClass(classes);

      if (available && !reservable) {
        reserve_button.removeClass('available').addClass('unavailable');
      }
    }
    else {
      reserve_button.addClass('not-reservable');
    }
  }

  /**
   * Update availability holdings information.
   *
   * Insert HTML with information about where the entities are located.
   *
   * @param html_id
   *   HTML id for the element to update holdings for.
   */
  function ding_availability_update_holdings(html_id) {
    if (Drupal.DADB.hasOwnProperty(html_id) && Drupal.DADB[html_id].hasOwnProperty('holdings')) {
      // Insert/update holding information for material.
      $('#' + html_id).html(Drupal.DADB[html_id].html);
    }
  }

  /**
   * Load information from the backend.
   *
   * @param {string} mode
   *   The type of information to fetch "holdings" or "items".
   * @param {array} ids
   *   The ids to fetch information for.
   */
  function ding_availability_fetch(mode, ids) {
    var path = Drupal.settings.basePath + 'ding_availability/' + mode;
    $.ajax({
      type: "POST",
      dataType: "json",
      url: path,
      data: { 'ids': ids },
      success: function (data) {
        $.each(data, function (provider_id, item) {
          // Update cache.
          Drupal.DADB[item.ids.html_id] = item;
          if (mode === 'holdings') {
            ding_availability_update_holdings(item.ids.html_id);
          }
          else {
            ding_availability_update_availability(provider_id, item.ids.html_id);
          }
        });
      },
      error: function () {
        $('div.loader').remove();
      }
    });
  }

  /**
   * Attach the availability behaviors to the page.
   *
   * The will be re-attached at every page content update.
   */
  Drupal.behaviors.ding_availability = {
    attach: function (context) {
      var settings = Drupal.settings;
      var ids = {};
      var html_ids = [];

      // Loop through the materials given in the settings and collect
      // id.
      if (settings.hasOwnProperty('ding_availability')) {
        $.each(settings.ding_availability, function (id, data) {
          if (!Drupal.DADB.hasOwnProperty(data.html_id)) {
            Drupal.DADB[data.html_id] = null;
            ids[data.html_id] = data;
            html_ids.push(data.html_id);
          }
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
      if (!$.isEmptyObject(ids)) {
        // Detect the material being viewed. Not all show materials
        // needs to load holdings information. The materials in the
        // carousels/listings etc. don't need to load holdings to show
        // a reservation button.
        var holdingsId = $('.field-name-ding-availability-holdings .field-item div');
        if (holdingsId.size() > 0) {
          var id = holdingsId.attr('id');
          if (ids.hasOwnProperty(id)) {
            var data = {};
            data[ids[id].local_id] = ids[id];
            ding_availability_fetch('holdings', data);
            delete ids[id];
          }
        }
        // Only fetch items availability if there are any items on the current page.
        if (!$.isEmptyObject(ids)) {
          ding_availability_fetch('items', ids);
        }
      }
    }
  };
})(jQuery);
