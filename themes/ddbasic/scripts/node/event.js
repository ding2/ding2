/*jshint forin:false, jquery:true, browser:true, indent:2, trailing:true, unused:false */
(function($) {
  'use strict';

  // Set height for event teasers.
  $(window).bind('resize.ding_event_teaser', function (evt) {
    var ding_event_teaser_height = 0;

    $('.node-ding-event.node-teaser').each(function (delta, view) {
      ding_event_teaser_height = $(this).find('.inner').outerHeight();
      $(this).height(ding_event_teaser_height);
    });
  });

  // Call resize function when images are loaded.
  Drupal.behaviors.ding_event_teaser_loaded = {
    attach: function(context, settings) {
      if ($.isFunction($.fn.imagesLoaded)) {
        $('.view-ding-event .view-elements').imagesLoaded( function() {
          $(window).triggerHandler('resize.ding_event_teaser');
        });
      }
    }
  };

  // Hover functions for event teasers.
  Drupal.behaviors.ding_event_teaser_hover = {
    attach: function(context, settings) {
      var title_and_lead_height,
          hovered;
      $('.node-ding-event.node-teaser', context).mouseenter(function() {
        // Set height for title and lead text.
        title_and_lead_height = $(this).find('.title').outerHeight(true) + $(this).find('.field-name-field-ding-event-lead .field-items').outerHeight(true) + 20;
        $(this).find('.title-and-lead').css('min-height', title_and_lead_height);

        // Set timeout to make shure element is still above while it animates
        // out.
        hovered = $(this);
        setTimeout(function(){
          $('.node-ding-event.node-teaser').removeClass('is-hovered');
          hovered.addClass('is-hovered');
        }, 300);
      });
      $('.node-ding-event.node-teaser', context).mouseleave(function() {
         $(this).find('.title-and-lead').css('min-height', '');
      });
    }
  };

  // Handle checkboxes click on event list exposed form.
  Drupal.behaviors.ding_event_list_exposed_form_checkboxes = {
    attach: function (context, settings) {
      var $this = $(document);
      // Query param attached on page load.
      var search_string = $this[0].location.search;

      // If query param is not empty - proceed with processing.
      if (search_string) {
        var decoded_url = decodeURI(search_string);
        var split = decoded_url.split('=');
        var clean_string = split[0].replace('?', '');
        var exposed_form = $this.find('form#views-exposed-form-ding-event-ding-event-list');

        var selected_category = exposed_form.find(':input[name="' + clean_string + '"]:input[value="' + split[1] + '"]');
        selected_category.prop('checked', true);

        // Remove "checked" property from checkbox if this is already checked.
        if (selected_category.prop('checked') === true) {
          selected_category.on('click', function (e) {
            e.preventDefault();
            // Remove query param before redirect to /arrangementer.
            $this[0].location.search = '';
          });
        }
      }
    }
  };

})(jQuery);
