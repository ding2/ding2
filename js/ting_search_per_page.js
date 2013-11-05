(function($) {
  "use strict";

  $(document).ready(function() {
    $('.pane-search-per-page select').change(function() {
      // Reloads the page when new size is selected in the drop-down.
      $('#ting-search-per-page-form').trigger("submit");
    });
  });
}(jQuery));
