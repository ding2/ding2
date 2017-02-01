/*jshint forin:false, jquery:true, browser:true, indent:2, trailing:true, unused:false */
(function($) {
  'use strict';

  /**
   * Close button for Cookies pop-up
   */
  Drupal.behaviors.mobile_footer = {
    attach: function(context, settings) {
      $('.footer .footer-inner > .panel-pane .pane-title', context).click(function(){
        $(this).parent().find(".pane-content").slideToggle("fast");
        $('html, body').animate({
            scrollTop: $(this).offset().top - 180
        }, 300);
      });
    }
  };
})(jQuery);
