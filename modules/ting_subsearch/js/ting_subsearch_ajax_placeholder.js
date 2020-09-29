/**
 * @file
 * Process ting subsearch ajax placeholders.
 */

(function($) {
  'use strict';

  /**
   * Process subsearch placeholders.
   */
  Drupal.behaviors.ting_subsearch_ajax_placeholders = {
    attach: function(context, settings) {
      var searchResult = settings.tingSubsearch.searchResult;
      var query = settings.tingSubsearch.query;
      var url = '/ting_subsearch/ajax_placeholder_callback' + query;

      $('.js-ting-subsearch-ajax-placeholder', context).once(function() {
        var placeholder = $(this);
        var module = placeholder.data('ting-subsearch-module');
        var data = {
          'searchResult': searchResult,
          'module': module
        };

        // Note that we intentionally do a separate POST back for each
        // placeholder to avoid one large request that performs several ting
        // searches. As a drawback we potentially send the same serialized
        // request object several times to the server, but we get more
        // responsive subsearches and suggestions which is preferred.
        $.post(url, data, function (response) {
          if (response !== '') {
            // See Drupal's ajax.js.
            var wrapped_message = $('<div></div>').html(response);
            var message = wrapped_message.contents();
            placeholder.replaceWith(message);
            Drupal.attachBehaviors(message);
          }
          else {
            placeholder.remove();
          }
        });
      });
    }
  };

 })(jQuery);
