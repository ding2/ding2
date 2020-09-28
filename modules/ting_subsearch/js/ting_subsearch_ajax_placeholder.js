/**
 * @file
 * Process ting subsearch ajax placeholders.
 */

(function($) {
  'use strict';

  var settings = Drupal.settings.tingSubsearch;
  var searchResult = settings.searchResult;
  var url = '/ting_subsearch/ajax_placeholder_callback' + settings.query;

  /**
   * Process subsearch placeholders.
   */
  Drupal.behaviors.ting_subsearch_ajax_placeholders = {
    attach: function(context) {
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
            var message = $(response);
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
