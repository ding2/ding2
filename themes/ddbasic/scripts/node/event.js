/*jshint forin:false, jquery:true, browser:true, indent:2, trailing:true, unused:false */
(function($) {
  'use strict';

  $(function () {
    // Set height for event teasers.
    var ding_event_teaser_height;
    $(window).bind('resize.ding_event_teaser', function (evt) {
      $('.node-ding-event.node-teaser').each(function (delta, view) {
        ding_event_teaser_height = $(this).find('.inner').outerHeight();
        $(this).height(ding_event_teaser_height);
      });
    });
  });

  // Call resize function when images are loaded.
  Drupal.behaviors.ding_event_teaser_loaded = {
    attach: function(context, settings) {
      $('.view-ding-event .view-elements').imagesLoaded( function() {
        $(window).triggerHandler('resize.ding_event_teaser');
      });
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

})(jQuery);
