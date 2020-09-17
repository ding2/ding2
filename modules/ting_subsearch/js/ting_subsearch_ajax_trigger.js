/**
 * @file
 * Handle ting subsearch trigger.
 */

 (function($) {
  'use strict';

  /**
   * Trigger asynchronous subsearches.
   */
  Drupal.behaviors.ting_subsearch = {
    attach: function(context) {
      $('.js-ting-subsearch-ajax-trigger', context).once(function() {
        var trigger = $(this);
        var query = trigger.data('ting-subsearch-query');

        $.get('/ting_subsearch/ajax' + query, {}, function (response) {
          if (response !== '') {
            var message = $(response);
            trigger.replaceWith(message);
            Drupal.attachBehaviors(message);
          }
          else {
            trigger.remove();
          }
        });
      });
    }
  };

 })(jQuery);
