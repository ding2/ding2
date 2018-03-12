/*jshint forin:false, jquery:true, browser:true, indent:2, trailing:true, unused:false */
/*globals ddbasic*/
(function($) {
  'use strict';

  /**
   * Hover first item in view ding news with class "first-child-large"
   */
  Drupal.behaviors.hover_view_ding_news_first_child_large = {
    attach: function(context, settings) {
      var text_element_height;
      $('.view-ding-news.first-child-large .views-row:first-child', context).mouseenter(function() {
        if(!ddbasic.breakpoint.is('mobile')) {
          text_element_height = $(this).outerHeight() - $(this).find('.news-text').outerHeight();
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
        title_and_lead_height = $(this).find('.title').outerHeight(true) + $(this).find('.field-name-field-ding-news-lead .field-items').outerHeight(true) + 20;
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
