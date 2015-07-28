/**
 * @file
 * Defines the ting search overlay and makes it available for other scripts.
 */
(function($) {
  "use strict";

  /**
   * Add search overlay function, so all search related JavaScripts can call it.
   */
  Drupal.TingSearchOverlay = function(remove_overlay) {

    // Try to get overlay
    var overlay = $('.search-overlay--wrapper');
    if (!overlay.length) {
      // Overlay not found so create is and display.
      overlay = $('<div class="search-overlay--wrapper"><div class="search-overlay--inner"><i class="icon-spinner icon-spin search-overlay--icon"></i><p class="search-overlay--text">' + Drupal.t('Searching please wait...') + '</p><p class="cancel"><a href="#">' + Drupal.t('Cancel') + '</a></p></div></div>');
      $('body').prepend(overlay);
    }
    else {
      // Overlay found.
      if (typeof remove_overlay !== 'undefined') {
        // If toggle remove it.
        overlay.remove();
      }
    }
  };

  // Hook into the overlays "Cancel" link and stop page loading if clicked.
  $(document).ready(function() {
    $('.search-overlay--wrapper .cancel').live('click', function() {
      window.stop();
      Drupal.TingSearchOverlay(true);
    });

    // Remove overlay on page unload, so it's not shown when back button is used
    // in the browser.
    $(window).unload(function() {
      var overlay = $('.search-overlay--wrapper');
      if (overlay.length) {
        Drupal.TingSearchOverlay(true);
      }
    });
  });

}(jQuery));
