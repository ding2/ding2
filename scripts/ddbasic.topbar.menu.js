/*
 * Creates the topbar toggle menu
 * 
 */

(function($) {

  // When ready start the magic.
  $(document).ready(function () {

    // Elements to toggle
    var ddbasic_topbar_user = $('.js-topbar-user');
    var ddbasic_topbar_search = $('.js-topbar-search');

    // Link elements
    var ddbasic_topbar_link = $(".js-topbar-link");

    // Attach some onclick/touch magic
    ddbasic_topbar_link.on('click touchstart', function(event) {

      var clicked = $(this);

      // Toggle elements based on wich link is clicked.
      // User link was clicked.
      if (clicked.hasClass('topbar-link-user')) {
        ddbasic_topbar_search.hide();
        ddbasic_topbar_user.toggle();
        $('.js-topbar-user #edit-name').focus();
      }
      // Search link was clicked
      if (clicked.hasClass('topbar-link-search')) {
        ddbasic_topbar_user.hide();
        ddbasic_topbar_search.toggle();
        $('.js-topbar-search #edit-search-block-form--2').focus();
      }

      // Set clicked to active link if not already active.
      // This makes it possible to toggle the same element on/off.
      if (clicked.hasClass('active')) {
        clicked.removeClass('active');
        // Reset background color to avoid link being in focus when user toggle same element.
        // This only apply to touchscreen devices.
        ddbasic_topbar_link.one('touchend', function() {
          clicked.css('background-color', 'inherit');
        });
      }
      else {
        // Make sure hardcoded style is removed
        clicked.css('background-color', '');
        // Remove active class from all links and add .active to clicked link.
        ddbasic_topbar_link.removeClass('active');
        clicked.addClass('active');
      }

      // Prevent default (href).
      event.preventDefault();
    });

    // Hide everything by default.
    ddbasic_topbar_user.hide();
    ddbasic_topbar_search.hide();

  });

})(jQuery);