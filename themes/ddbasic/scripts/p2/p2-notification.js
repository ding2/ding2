(function($) {

  // Notification count
  Drupal.behaviors.ding_p2_notifications = {
    attach: function(context, settings) {
      var count = 0,
          notification_count = $('.pane-notifications-top-menu .notifications-count');

      if(notification_count.length) {
        notification_count.each(function( index ) {
          count = count + parseInt($(this).text(), 10);;
        });

        if($('.topbar-link-user-account .topbar-link-user-account')) {
          $('.topbar-link-user-account .topbar-link-user-account').append('<div class="notification-count">' + count + '</div>');
        }
      }


      console.log(count);
    }
  };

})(jQuery);