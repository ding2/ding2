/*jshint forin:false, jquery:true, browser:true, indent:2, trailing:true, unused:false */
(function($) {
  'use strict';

  /**
   * Close button for Cookies pop-up
   */
  Drupal.behaviors.cookies_close = {
    attach: function(context, settings) {

      $('.popup-content', context).append("<div class='cookies close'></div>");
      $('.cookies.close').click(function(){
        $("#sliding-popup").remove();
      });
    }
  };
})(jQuery);
