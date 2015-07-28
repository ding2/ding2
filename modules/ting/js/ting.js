/**
 * @file
 * Simple script to help display search overlay when links are clicked.
 */
(function($) {
  "use strict";

  $(document).ready(function() {
    $('a.js-search-overlay').live('click', function() {
      var link = $(this);
      if (link.attr('href').charAt(0) !== '#') {
        // Only show overlay for non-local links.
        Drupal.TingSearchOverlay();
      }
    });

    // Ensure overlay on collection view links.
    $('.ting-collection-wrapper a[href*="/ting/"]').live('click', function() {
      if ($(this).not('[target="_blank"]').length) {
        Drupal.TingSearchOverlay();
      }
    });

    // Ensure overlay on object view links.
    $('.ting-object-wrapper a[href*="/ting/"]').live('click', function() {
      if ($(this).not('[target="_blank"]').length) {
        Drupal.TingSearchOverlay();
      }
    });
  });
}(jQuery));
