/**
 * Checks reservability for materials before activating the reserve button.
 */

(function($) {

  "use strict";

  Drupal.behaviors.ding_reservation = {
    attach: function(context) {
      var entityIds = [];
      var selector = '.ting-object .reserve-button.check-reservability';
      $(selector, context).once('check-reservability', function() {
        entityIds.push($(this).data("entity-id"));
      });

      if (entityIds.length) {
        $.ajax({
          dataType: "json",
          url: "/ding_reservation/" + entityIds.join(',') + "/is_reservable",
          success: function(result) {
            $.each(result, function(entityId, reservability) {
              $(selector + '[data-entity-id="' + entityId + '"]', context).addClass('reservable');
            });
          }
        });
      }
    }
  };

})(jQuery);
