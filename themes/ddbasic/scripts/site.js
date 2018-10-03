(function($) {
  "use strict";

  // Add classes for touch and no touch.
  $(function () {
    var ua = navigator.userAgent.toLowerCase();
    if (
      /(ipad)/.exec(ua) ||
      /(iphone)/.exec(ua) ||
      /(android)/.exec(ua) ||
      /(windows phone)/.exec(ua)
    ) {
      $('body').addClass('has-touch');
    } else {
      $('body').addClass('no-touch');
    }
  });

  // Don't override existing ddbasic scope.
  window.ddbasic = window.ddbasic || {};

  /**
   * Attach close cookie notification events.
   */
  Drupal.behaviors.close_cookie_notification = {
    attach: function(context, settings) {
      $('#sliding-popup .close', context).bind('click', function () {
        $(this).closest('#sliding-popup').slideUp();
      });
    }
  };

}(jQuery));
