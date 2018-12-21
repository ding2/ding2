/**
 * @file
 * Simple script to help display search overlay when links are clicked.
 */
(function($) {
  "use strict";

  $(document).ready(function() {
    // Ensure overlay on collection view links.
    $('.ting-collection-wrapper a[href*="/ting/"]').on('click', function() {
      if ($(this).not('[target="_blank"]').length) {
        Drupal.TingSearchOverlay();
      }
    });

    // Ensure overlay on object view links.
    $('.ting-object-wrapper a[href*="/ting/"]').on('click', function() {
      if ($(this).not('[target="_blank"]').length) {
        Drupal.TingSearchOverlay();
      }
    });
  });
}(jQuery));
