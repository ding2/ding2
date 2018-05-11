/*jshint forin:false, jquery:true, browser:true, indent:2, trailing:true, unused:false */
/*globals ddbasic*/
(function($) {
  'use strict';

  // Set height for news teasers.
  $(window).bind('resize.ding_news_teaser', function (evt) {
    var ding_news_teaser_height = 0;

    $('.node-ding-news.node-teaser').each(function (delta, view) {
      ding_news_teaser_height = $(this).find('.inner').outerHeight();
      $(this).height(ding_news_teaser_height);
    });
  });

  // Call resize function when images are loaded.
  Drupal.behaviors.ding_news_teaser_loaded = {
    attach: function(context, settings) {
      if ($.isFunction($.fn.imagesLoaded)) {
        $('.view-ding-news .view-elements').imagesLoaded( function() {
          $(window).triggerHandler('resize.ding_news_teaser');
        });
      }
    }
  };

  // Hover functions for news teasers.
  Drupal.behaviors.ding_news_teaser_hover = {
    attach: function(context, settings) {
      var title_and_lead_height,
          hovered;
      $('.node-ding-news.node-teaser', context).mouseenter(function() {
        // Set height for title and lead text.
        title_and_lead_height = $(this).find('.title').outerHeight(true) + $(this).find('.field-name-field-ding-news-lead .field-items').outerHeight(true) + 70;
        $(this).find('.title-and-lead').css('min-height', title_and_lead_height);

        // Set timeout to make shure element is still above while it animates
        // out.
        hovered = $(this);
        setTimeout(function(){
          $('.node-ding-news.node-teaser').removeClass('is-hovered');
          hovered.addClass('is-hovered');
        }, 300);
      });
      $('.node-ding-news.node-teaser', context).mouseleave(function() {
         $(this).find('.title-and-lead').css('min-height', '');
      });
    }
  };
})(jQuery);
