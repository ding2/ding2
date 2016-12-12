(function ($) {
  "use strict";

  $(document).ready(function () {
    var hashcode = window.location.hash;

    if (hashcode === '#hasHoldings') {
      $(".group-holdings-available a").click();
    }
    else {
      $(".find-items-button").on('click', function() {
        $(".group-holdings-available a").click();
      });
    }
  });
}(jQuery));
