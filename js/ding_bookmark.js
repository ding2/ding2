(function($) {

  Drupal.behaviors.ie9bookmarkSubmit = {
      attach:function(context, settings) {
          $('.ding-bookmark-reservation-button', context).click(function() {
              $('#ding-reservation-reserve-form-' + this.id).submit();
              return false;
          });
      }
  };

} (jQuery));
