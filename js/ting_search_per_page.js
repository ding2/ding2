(function($) {
  "use strict";

  $(document).ready(function() {
    $('.pane-search-per-page select').change(function() {
      // Reloads the page when new size is selected in the drop-down.
      window.location = updateQueryStringParameter(window.location.pathname, 'size', $(this).val());
    });
  });

  /**
   * Updates the query string parameter.
   */
  function updateQueryStringParameter(uri, key, value) {
    var re = new RegExp("([?|&])" + key + "=.*?(&|$)", "i");
    var separator = uri.indexOf('?') !== -1 ? "&" : "?";
    if (uri.match(re)) {
      return uri.replace(re, '$1' + key + "=" + value + '$2');
    }
    else {
      return uri + separator + key + "=" + value;
    }
  }
}(jQuery));
