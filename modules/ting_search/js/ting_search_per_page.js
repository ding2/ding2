(function($) {
  "use strict";

  $(document).ready(function() {
    $('.pane-search-per-page select').change(function() {
      // Display search overlay.
      Drupal.TingSearchOverlay();

      // Reloads the page when new size is selected in the drop-down.
      $('#ting-search-per-page-form').trigger("submit");
    });

    $('.pane-ting-search-sort-form select').change(function() {
      // Display search overlay.
      Drupal.TingSearchOverlay();
    });
 });
}(jQuery));
