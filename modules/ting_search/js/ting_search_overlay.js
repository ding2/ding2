/**
 * @file
 * Defines the ting search overlay and makes it available for other scripts.
 */
(function ($) {
  "use strict";

  var ctrlKeyIsPressed = false;
  // Ctrl or CMD key codes.
  var keyCodes = [224, 17, 91, 93];

  Drupal.behaviors.ting_search_overlay = {
    attach: function () {
      if (!$('body').hasClass("page-admin")) {
        // Do not show overlay if ctrl key is pressed.
        $('body').on('keydown keyup', function (e) {

          var keyPressState = e.type === 'keydown' ? true : false;
          if ($.inArray(e.which, keyCodes) !== -1) {
            ctrlKeyIsPressed = keyPressState;
          }
        });
      }
    }
  };

  /**
   * Add search overlay function, so all search related JavaScripts can call it.
   */
  Drupal.TingSearchOverlay = function (remove_overlay) {
    if (!$('body').hasClass("page-admin")) {
      if (ctrlKeyIsPressed === false) {
        // Try to get overlay
        var overlay = $('.search-overlay--wrapper');
        if (!overlay.length) {
          // Overlay not found so create is and display.
          overlay = $('<div class="search-overlay--wrapper"><div class="search-overlay--inner"><div class="spinner-container"><i class="icon-spinner icon-spin search-overlay--icon"><svg x="0px" y="0px" width="84px" height="84px" viewBox="0 0 84 84" enable-background="new 0 0 84 84" xml:space="preserve"><path fill="#FFFFFF" d="M84,42C84,18.842,65.158,0,42,0C18.841,0,0,18.842,0,42c0,23.159,18.841,42,42,42v-1.988	C19.944,82.012,2,64.062,2,42S19.944,1.988,42,1.988c22.057,0,40,17.949,40,40.012c0,9.363-3.262,18.366-9.21,25.536l-0.501-8.577 l-1.998,0.117l0.697,11.918l11.91-1.559l-0.26-1.974l-8.072,1.058C80.662,61.042,84,51.704,84,42z"/></svg></i></div><p class="search-overlay--text">' + Drupal.t('Searching please wait...') + '</p><p class="cancel"><a href="#">' + Drupal.t('Cancel') + '</a></p></div></div>');
          $('body').prepend(overlay);
        }
        else {
          // Overlay found.
          if (typeof remove_overlay !== 'undefined') {
            // If toggle remove it.
            overlay.remove();
          }
        }
      }
    }
  };

  // Hook into the overlays "Cancel" link and stop page loading if clicked.
  $(document).ready(function () {
    if (!$('body').hasClass("page-admin")) {
      $('.search-overlay--wrapper .cancel').on('click', function () {
        window.stop();
        Drupal.TingSearchOverlay(true);
      });

      // Remove overlay on page unload, so it's not shown when back button is
      // used in the browser.
      $(window).on("pageshow", function () {
        if ($('.search-overlay--wrapper')[0]) {
          Drupal.TingSearchOverlay(true);
        }
      });

      // Make sure that the overlay is removed when ESC is pressed.
      $(window).keydown(function (event) {
        // Keycode for the ESC-button.
        if (event.which === 27) {
          var overlay = $('.search-overlay--wrapper');

          if (overlay.length) {
            Drupal.TingSearchOverlay(true);
          }
        }
      });
    }
  });

}(jQuery));
