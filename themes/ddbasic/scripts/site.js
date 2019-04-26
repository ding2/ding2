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
      $(context).on('eu_cookie_compliance_popup_open', function() {
        $('#sliding-popup .close', context).bind('click', function () {
          var popup = $('#sliding-popup');
          if (popup.hasClass('sliding-popup-top')) {
            popup.animate({ top: popup.outerHeight() * -1 }, Drupal.settings.eu_cookie_compliance.popup_delay).trigger('eu_cookie_compliance_popup_close');
          }
          else {
            popup.animate({ bottom: popup.outerHeight() * -1 }, Drupal.settings.eu_cookie_compliance.popup_delay).trigger('eu_cookie_compliance_popup_close');
          }
        });
      });
    }
  };
}(jQuery));
