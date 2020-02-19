/**
 * @file
 * Ding serendipity
 *
 * Add serendipity GA tracking to links provided by serendipity module
 */

(function ($) {
  "use strict";
  
  Drupal.behaviors.ding_serendipity = {
    attach: function (context) {
      // Bail if there's no analytics.
      if (this._gaq === undefined) {
        return;
      }

      // Add analytics tracking
      $('div[class*="pane-serendipity"] .ting-object, .ding-serendipity-analytics .ting-object', context).each(function() {
        var _source = $('.ding-serendipity-source', this).text();
        $('a', this).click(function() {
          this._gaq.push(['_trackEvent', 'Serendipy', 'click', _source]);
        });
      });
    }
  };
})(jQuery);
