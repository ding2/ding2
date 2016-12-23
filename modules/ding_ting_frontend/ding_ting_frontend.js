/**
 * @file
 * Ding Ting Frontend module js actions.
 */
(function ($) {
  "use strict";

  $(document).ready(function () {
    var hashcode = window.location.hash;

    $("#find-holdings").on('click', function(e) {
      e.stopPropagation();
      $('.search-overlay--wrapper').remove();
      $('.group-holdings-available').removeClass('collapsed');
      $("#hasHoldings .field-group-format-wrapper").show();
    });

    if (hashcode === '#hasHoldings') {
      $(".group-holdings-available a").click();
    }
  });

}(jQuery));
