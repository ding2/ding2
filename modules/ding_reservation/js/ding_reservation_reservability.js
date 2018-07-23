/**
 * Checks reservability for materials before activating the reserve button.
 */

(function($) {

  "use strict";

  Drupal.behaviors.ding_reservation = {
    attach: function(context) {
      $(".ting-object .reserve-button", context).once('check-reservability', function() {
        var reserveButton = $(this);
        var entityId = reserveButton.data("entity-id");
        $.ajax({
          dataType: "json",
          url: "/ding_reservation/" + entityId + "/reservable",
          success: function(result) {
            if (result['reservable']) {
              reserveButton.addClass('reservable');
            }
          }
        });
      })
    }
  }

})(jQuery);
