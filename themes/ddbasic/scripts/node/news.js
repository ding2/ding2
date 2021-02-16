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
      $('.view-ding-news .view-elements').imagesLoaded( function() {
        $(window).triggerHandler('resize.ding_news_teaser');
      });
    }
  };

  /**
   * Hover first item in view ding news with class "first-child-large"
   */
  Drupal.behaviors.hover_view_ding_news_first_child_large = {
    attach: function(context, settings) {
      var text_element_height;
      $('.view-ding-news.first-child-large .views-row:first-child', context).mouseenter(function() {
        if(!ddbasic.breakpoint.is('mobile')) {
          text_element_height = $(this).find('.inner').outerHeight() - $(this).find('.news-text').outerHeight();
          $(this).find('.field-name-field-ding-news-lead').height(text_element_height);
        }
      });
      $('.view-ding-news.first-child-large .views-row:first-child', context).mouseleave(function() {
        if(!ddbasic.breakpoint.is('mobile')) {
          $(this).find('.field-name-field-ding-news-lead').height(0);
        }
      });
    }
  };

  // Hover functions for news teasers.
  Drupal.behaviors.ding_news_teaser_hover = {
    attach: function(context, settings) {
      var title_and_lead_height,
          hovered;
      $('.node-ding-news.node-teaser', context).mouseenter(function() {
        // Set height for title and lead text.
        title_and_lead_height = $(this).find('.title').outerHeight(true) + $(this).find('.field-name-field-ding-news-lead').outerHeight(true) + 50;

        $(this).find('.title-and-lead').css('min-height', title_and_lead_height);
      });
      $('.node-ding-news.node-teaser').mouseleave(function() {
        $(this).find('.title-and-lead').css('min-height', '');
      });
    }
  };

})(jQuery);
