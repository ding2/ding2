/**
 * @file
 * Defines the ting search overlay and makes it available for other scripts.
 */
(function($) {
  "use strict";

  var ctrlKeyIsPressed = false;
  // Ctrl or CMD key codes.
  var keyCodes = [224, 17, 91, 93];

  // Do not show overlay if ctrl key is pressed.
  $('body').live('keydown keyup', function(e) {

    var keyPressState = e.type === 'keydown' ? true : false;
    if($.inArray(e.which, keyCodes) !== -1) {
      ctrlKeyIsPressed = keyPressState;
    }
  });

  /**
   * Add search overlay function, so all search related JavaScripts can call it.
   */
  Drupal.TingSearchOverlay = function(remove_overlay) {

    if (ctrlKeyIsPressed === false) {
      // Try to get overlay
      var overlay = $('.search-overlay--wrapper');
      if (!overlay.length) {
        // Overlay not found so create is and display.
        overlay = $('<div class="search-overlay--wrapper"><div class="search-overlay--inner"><div class="spinner-container"><i class="icon-spinner icon-spin search-overlay--icon"><svg x="0px" y="0px" width="84px" height="84px" viewBox="0 0 84 84" enable-background="new 0 0 84 84" xml:space="preserve"><path fill="#FFFFFF" d="M74.566,15.48l8.072,1.058l0.26-1.974l-11.909-1.558l-0.698,11.918l1.998,0.117l0.501-8.577 C78.738,23.634,82,32.637,82,42c0,22.063-17.943,40.012-40,40.012C19.944,82.012,2,64.063,2,42C2,19.938,19.944,1.988,42,1.988V0 C18.841,0,0,18.841,0,42c0,23.158,18.841,42,42,42c23.158,0,42-18.842,42-42C84,32.296,80.662,22.958,74.566,15.48z"/></svg></i></div><p class="search-overlay--text">' + Drupal.t('Searching please wait...') + '</p><p class="cancel"><a href="#">' + Drupal.t('Cancel') + '</a></p></div></div>');
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
  };

  // Hook into the overlays "Cancel" link and stop page loading if clicked.
  $(document).ready(function() {
    $('.search-overlay--wrapper .cancel').live('click', function() {
      window.stop();
      Drupal.TingSearchOverlay(true);
    });

    // Remove overlay on page unload, so it's not shown when back button is used
    // in the browser.
    $(window).bind("pageshow", function() {
      if ($('.search-overlay--wrapper')[0]) {
        Drupal.TingSearchOverlay(true);
      }
    });

    // Make sure that the overlay is removed when ESC is pressed.
    $(window).keydown(function(event) {
      // Keycode for the ESC-button.
      if (event.which === 27) {
        var overlay = $('.search-overlay--wrapper');

        if (overlay.length) {
          Drupal.TingSearchOverlay(true);
        }
      }
    });
  });

}(jQuery));
