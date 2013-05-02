/*
 * Creates the topbar toggle menu
 */

(function($) {

  // When ready start the magic.
  $(document).ready(function () {

    // Elements to toggle
    var ddbasic_topbar_user = $('.js-topbar-user');
    var ddbasic_topbar_search = $('.js-topbar-search');

    // Link elements
    var ddbasic_topbar_link = $(".js-topbar-link");

    // Attach some onclick magic
    ddbasic_topbar_link.on('click touchstart', function(event) {

      var clicked = $(this);

      // Toggle elements based on wich link is clicked
      // User link was clicked
      if (clicked.hasClass('topbar-link-user')) {
        ddbasic_topbar_search.hide();
        ddbasic_topbar_user.toggle();
      }
      // Search link was clicked
      if (clicked.hasClass('topbar-link-search')) {
        ddbasic_topbar_user.hide();
        ddbasic_topbar_search.toggle();
      }

      // Set clicked to active link if not already active
      if (clicked.hasClass('active')) {
        clicked.removeClass('active');
        ddbasic_topbar_link.one('touchend', function() {
          clicked.css('background-color', 'inherit');
        });
      }
      else {
        clicked.css('background-color', '');
        ddbasic_topbar_link.removeClass('active');
        clicked.addClass('active');
      }

      // Prevent default (href)
      event.preventDefault();
    });

    // Hide everything by default
    ddbasic_topbar_user.hide();
    ddbasic_topbar_search.hide();

  });

})(jQuery);