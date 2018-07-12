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
   * Open up the login box.
   */
  window.ddbasic.openLogin = function () {
    var $body = $('body');

    $body.toggleClass('pane-login-is-open');
    $body.removeClass('mobile-menu-is-open mobile-search-is-open mobile-usermenu-is-open');
    if ($body.hasClass('pane-login-is-open')) {
      $body.addClass('overlay-is-active');
    } else {
      $body.removeClass('overlay-is-active');
    }
  };

  /**
   * Attach open login events.
   */
  Drupal.behaviors.open_login = {
    attach: function(context, settings) {
      $('a.open-login', context).bind('click', function (evt) {
        evt.preventDefault();
        ddbasic.openLogin();
      });
    }
  };

}(jQuery));
