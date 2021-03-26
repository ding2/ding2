/**
 * @file
 * Simple script to help display search overlay when links are clicked.
 */

"use strict";

(function ($) {
  Drupal.behaviors.ting = {
    attach: function (context) {
      // TODO: These selectors might be outdated.
      $('a.js-search-overlay', context).on('click', function () {
        var link = $(this);
        if (link.attr('href').charAt(0) !== '#') {
          // Only show overlay for non-local links.
          Drupal.TingSearchOverlay();
        }
      });

      // Ensure search overlay on search links in a ting object view.
      $('.ting-object a[href^="/search/ting/"]', context).on('click', function() {
        if ($(this).not('[target="_blank"]').length) {
          Drupal.TingSearchOverlay();
        }
      });
    }
  };
}(jQuery));
