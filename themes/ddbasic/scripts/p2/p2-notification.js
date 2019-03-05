/*jshint forin:false, jquery:true, browser:true, indent:2, trailing:true, unused:false */
(function($) {
  'use strict';

  // Notification count
  Drupal.behaviors.ding_p2_notifications = {
    attach: function(context, settings) {
      var count = 0,
        notification_count = $('.pane-notifications-top-menu .notifications-count');

      if (notification_count.length) {
        notification_count.each(function(index) {
          count = count + parseInt($(this).text(), 10);
        });

        if ($('.topbar-link-user-account .topbar-link-user-account')) {
          $('.topbar-link-user-account .topbar-link-user-account', context).append('<div class="notification-count">' + count + '</div>');
        }
      }
    }
  };
})(jQuery);
