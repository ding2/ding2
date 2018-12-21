/**
 * @file
 * Simple script to help display search overlay when links are clicked.
 */
(function($) {
  "use strict";

  $(document).ready(function() {
    // Ensure search overlay on search links in a ting object view.
    $('.ting-object a[href^="/search/ting/"]').on('click', function() {
      if ($(this).not('[target="_blank"]').length) {
        Drupal.TingSearchOverlay();
      }
    });
  });
}(jQuery));
