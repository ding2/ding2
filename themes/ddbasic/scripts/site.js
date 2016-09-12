(function($) {
  "use strict";
  
  //
  // Add classes for touch and no touch
  $(function () {
    // Touch
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

}(jQuery));