/**
 * @file
 * Detects if the URL contains a redo string in the fragment and sends an
 * Drupal ajax request to that url.
 *
 * It's use to re-start an ajax command after an redirect to the oAuth login
 * where the ajax request was not completed due to login redirect.
 */

(function ($) {
  "use strict";

  Drupal.behaviors.ding_adgangsplatformen = {
    attach: function (context, settings) {
      // We use the body as the ajax element as this is required to
      // programmatically send an Drupal Ajax request. So we use the once
      // trick to only redo the request... well once.
      $('body').once('js-redo-ajax-processed', function() {
        var hash = window.location.hash;
        if (hash.indexOf('redo') !== -1) {
          // Remove the fragment as it has been used now. This is only to clean-up
          // URL if the user should bookmark it etc.
          window.location.replace("#");
          if (typeof window.history.replaceState === 'function') {
            history.replaceState({}, '', window.location.href.slice(0, -1));
          }

          // Create drupal ajax request and trigger it with "this" which in this
          // context is the body element. We use an custom event "redo" to
          // ensure that we don't trigger unwanted events on the body element.
          var uri = hash.substring(hash.indexOf('=') + 1);
          var base = 'js-redo-ajax';
          var element_settings = {
            url: window.location.protocol + '//' + window.location.hostname +  settings.basePath + settings.pathPrefix + uri,
            event: 'redo',
            progress: {
              type: 'throbber'
            }
          };
          Drupal.ajax[base] = new Drupal.ajax(base, this, element_settings);
          $(this).trigger('redo');
        }
      });
    }
  };
}(jQuery));
