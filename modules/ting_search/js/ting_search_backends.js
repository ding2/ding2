(function($) {
  "use strict";

  /**
   * This script handle the changes from the different backends, which
   * currently is the data-well and the homepage. This in sures that action
   * is taken when the labels or radios are clicked.
   */
  $(document).ready(function() {
    // Click the label link when a radio button is clicked.
    $('.pane-search-backends input[type="radio"]').change(function() {
      var link = $(this).parent().find('a');
      Drupal.TingSearchOverlay();
      window.location = link.attr('href');
    });

    // When a label link is click, also check the radio button.
    $('.pane-search-backends a').click(function(event) {
      var radio = $(this).parent().parent().find('input[type="radio"]');
      if (radio.is(':checked')) {
        // If it is already checked do nothing.
        event.preventDefault();
        return false;
      }
      else {
        // Check the radio button and continue handling the click event.
        radio.attr('checked', 'checked');
        Drupal.TingSearchOverlay();
        return true;
      }
    });
  });
}(jQuery));
