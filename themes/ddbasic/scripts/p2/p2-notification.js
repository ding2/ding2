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
          $('.topbar-link-user-account .topbar-link-user-account', context).append('<div class="notification-count">' + count + '</div>');
        }
      }
    }
  };

  // P2 Ding list @TODO move to own file
  Drupal.behaviors.ding_p2_list = {
    attach: function(context, settings) {
      $('.field-name-ding-entity-buttons .ding-list-add-button .trigger').on('click', function(evt) {
        evt.preventDefault();
        $(this).parent().addClass('open-overlay');
      });
      $('.field-name-ding-entity-buttons .ding-list-add-button .close').on('click', function(evt) {
        evt.preventDefault();
        $(this).parents('.ding-list-add-button').removeClass('open-overlay');
      });
    }
  };

})(jQuery);