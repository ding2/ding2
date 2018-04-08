/**
 * @file
 * JavaScript behaviours for fetching and displaying availability information
 * on TingEntities.
 */
(function($) {
  "use strict";

  // Cache of fetched availability information.
  Drupal.DADB = {};

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
  function ding_availability_labels_update_availability_elements(element, btn, status) {
    var class_name = null;

    for (var i in status) {
      if (status[i] === true) {
        class_name = i;
      }
      else {
        if (i === 'available') {
          class_name = 'un' + i;
        }
        else if (i === 'reservable') {
          class_name = 'not-' + i;
        }
      }

      element.addClass(class_name);
      if (btn.length) {
        btn.addClass(class_name);
      }
    }

    ding_availability_labels_update_availability_type(element, status);
  }

  /**
   * Update availability on the page.
   *
   * The array of entity_ids is an array as we only show one availability
   * label per material type. So if one of these have an available status
   * the label have to reflect this.
   *
   * @param provider_id
   *   Id for which to update availability information.
   * @param html_id
   *   HTML id for the element to update availability for.
   */
  function ding_availability_labels_update_availability(provider_id, html_id) {
    // Default the status to not available and not reservable.
    var status = {
      available: false,
      reservable: false
    };


    if (Drupal.DADB.hasOwnProperty(html_id)) {
      var item = Drupal.DADB[html_id];
      status.available = status.available || item.available;
      status.reservable = status.reservable || item.reservable;
    }

    var element = $('#' + html_id);
    element.removeClass('pending').addClass('processed');

    // Get hold of the reserve button (it hidden as default, so we may need
    // to show it).
    var reserve_btn = element.parents('.ting-object:first').find('[id^=ding-reservation-reserve-form]');

    ding_availability_labels_update_availability_elements(element, reserve_btn, status);
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
  function ding_availability_labels_update_availability_type(element, status) {
    var groups_wrapper = element.closest('.search-result--availability');
    var reservable = status['reservable'];
    var available = status['available'];

    var group = null;
    if ($('.js-online', groups_wrapper).length !== 0) {
      group = $('.js-online', groups_wrapper);
    }
    else if (available) {
      group = $('.js-available', groups_wrapper);

      if (group.length === 0) {
        group = $('<p class="js-available">' + Drupal.t('Available') + ': </p>');
        groups_wrapper.append(group);
      }
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
        group = $('<p class="js-unavailable">' + Drupal.t('Not available') + ': </p>');
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
  function ding_availability_labels_remove_pending() {
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
   * Attach the availability behaviors to the page.
   *
   * The will be re-attached at every page content update.
   */
  Drupal.behaviors.ding_availability_labels = {
    attach: function(context, settings) {
      var ids = [];
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

      // Fetch availability.
      if (!$.isEmptyObject(ids)) {
        var path = settings.basePath + 'ding_availability/items';
        $.ajax({
          type: "POST",
          dataType: "json",
          url: path,
          data: { 'ids': ids },
          success: function(data) {
            $.each(data, function (provider_id, item) {
              // Update cache.
              Drupal.DADB[item.ids.html_id] = item;
              ding_availability_labels_update_availability(provider_id, item.ids.html_id);
            });
            ding_availability_labels_remove_pending();
          },
          error: function () {
            $('div.loader').remove();
          }
        });
      }
    }
  };
})(jQuery);
