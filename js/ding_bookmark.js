(function($) {

  Drupal.behaviors.bookmarkSubmit = {
      attach:function(context, settings) {
          $('.ding-bookmark-reservation-button', context).click(function() {
              $('#ding-reservation-reserve-form-' + this.id + ' input[type=submit]').mousedown();
              return false;
          });
      }
  };

  // reload page after closing reservation pop-up
  Drupal.behaviors.reloadBookmarkOnPopupClose = {
    attach: function(context) {
      // Capture link clicks.
      $('body.page-user-bookmarks a.ui-dialog-titlebar-close').each( function(context) {
        // Unbind existing click behaviors.
        $(this).unbind('click');
        // Handle clicks.
        $(this).click( function(e) {
          // Remove the default click handler.
          e.preventDefault();
          location.reload();
          return false;
        });
      });
    }
  };


})(jQuery);

