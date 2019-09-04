/**
 * Checks reservability for materials before activating the reserve button.
 */

(function($) {

  "use strict";

  Drupal.behaviors.ding_reservation = {
    attach: function(context) {
      var localIds = [];
      var selector = '.js-check-reservability';
      $(selector, context).once('js-check-reservability', function() {
        localIds.push($(this).data("local-id"));
      });

      if (localIds.length) {
        $.ajax({
          dataType: 'json',
          type: 'POST',
          url: '/ding_reservation/is_reservable',
          data: {
            localIds: localIds
          },
          success: function(result) {
            $.each(result, function(localId, reservable) {
              if (reservable) {
                $(selector + '[data-local-id="' + localId + '"]', context).addClass('reservable');
              }
            });
          }
        });
      }
    }
  };

})(jQuery);
