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

})(jQuery);
