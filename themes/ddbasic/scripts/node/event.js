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
        $('.view-ding-event .view-elements, .view-ding-related-content .view-content').imagesLoaded( function() {
          $(window).triggerHandler('resize.ding_event_teaser');
        });
      }
    }
  };

  // Hover functions for event teasers.
  Drupal.behaviors.ding_event_teaser_hover = {
    attach: function(context, settings) {
      var thisScope = this;
      var teaserSelector = '.node-ding-event.node-teaser';

      // Detecting activating events.

      // Mouseenter / hover event.
      $(teaserSelector, context).mouseenter(function() {
        thisScope.activateTeaser(this);
      });

      // Focus event. We need to do this seperately, as we're actually detecting
      // focus on an <a> tag nested within the actual teaser element.
      $(teaserSelector + ' > a', context).focus(function() {
        thisScope.activateTeaser($(this).parent('.node-ding-event.node-teaser'));
      });

      // Detecting deactivation events.

      // Mouseleave / stopping to hover event.
      $(teaserSelector, context).mouseleave(function() {
        thisScope.deactivateTeaser(this);
      });

      // Focusout event. We need to do this seperately, as we're actually
      // detecting focus on an <a> tag nested within the actual teaser element.
      $(teaserSelector + ' > a', context).focusout(function() {
        thisScope.activateTeaser($(this).parent('.node-ding-event.node-teaser'));
      });
    },

    activateTeaser: function(teaser) {
      // Set height for title and lead text.
      var title_and_lead_height = $(teaser).find('.title').outerHeight(true) + $(teaser).find('.field-name-field-ding-event-lead .field-items').outerHeight(true) + 20;
      $(teaser).find('.title-and-lead').css('min-height', title_and_lead_height);
    },

    deactivateTeaser: function(teaser) {
      $(teaser).find('.title-and-lead').css('min-height', '');
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
