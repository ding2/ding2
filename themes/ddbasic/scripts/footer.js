/*jshint forin:false, jquery:true, browser:true, indent:2, trailing:true, unused:false */
(function($) {
  'use strict';

  /**
   * Slide toggle footer menus
   */
  Drupal.behaviors.mobile_footer = {
    attach: function(context, settings) {
      $('.footer .pane-title', context).click(function(){
        $(this).toggleClass('open');
        $(this).parent().find(".pane-content").slideToggle("fast");
        $('html, body').animate({
            scrollTop: $(this).offset().top - 180
        }, 300);
      });
    }
  };
})(jQuery);
