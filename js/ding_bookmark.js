(function($) {

  Drupal.behaviors.bookmarkSubmit = {
      attach:function(context, settings) {
          $('.ding-bookmark-reservation-button', context).click(function() {
              $('#ding-reservation-reserve-form-' + this.id + ' input[type=submit]').mousedown();
              return false;
          });
      }
  };

} (jQuery));
