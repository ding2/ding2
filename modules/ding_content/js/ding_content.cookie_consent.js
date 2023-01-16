/**
 * @file
 * Behaviour for triggering the cookie popup.
 */
(function ($) {
  Drupal.behaviors.dingContentCookieConsent = {
    attach: function (context, settings) {
      $('.js-cookie-popup-trigger').once('cookie-popup-trigger-processed', function () {
        $(this).click(function() {
          CookieConsent.renew();
        });
      });
    }
  }
}(jQuery));
