/**
 * @file
 * Handle login slide up.
 */

(function($) {
  "use strict";

  Drupal.behaviors.ding_user_form = {
    attach: function (context, settings) {

      /**
       * Open up the login box.
       */
      function openLogin() {
        var body = $('body');

        body.toggleClass('pane-login-is-open');
        body.removeClass('mobile-menu-is-open mobile-search-is-open mobile-usermenu-is-open');
        if (body.hasClass('pane-login-is-open')) {
          body.addClass('overlay-is-active');
        } else {
          body.removeClass('overlay-is-active');
        }
      }

      function openHandler(event) {
        event.preventDefault();
        openLogin();
      }

      function closeHandler(event) {
        var body = $('body');

        event.preventDefault();
        body.removeClass('pane-login-is-open');
        body.removeClass('overlay-is-active');
      }

      $('a.js-topbar-link-user,a.open-login', context).unbind('click', openHandler);
      $('a.js-topbar-link-user,a.open-login', context).on('click', openHandler);

      $('.close-user-login', context).unbind('click', closeHandler);
      $('.close-user-login', context).on('click', closeHandler);
    }
  };
}(jQuery));
