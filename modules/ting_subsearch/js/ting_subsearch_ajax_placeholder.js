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

      $('.js-ting-subsearch-ajax-placeholder', context).once(function() {
        var placeholder = $(this);
        var module = placeholder.data('ting-subsearch-module');
        var data = {
          'searchResult': searchResult,
          'module': module
        };

        $.post('/ting_subsearch/ajax_placeholder_callback', data, function (response) {
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
