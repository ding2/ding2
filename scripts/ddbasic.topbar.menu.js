/*
 * Creates the topbar toggle menu
 * 
 */

(function($) {

  /*
   * Toggle topbar menu items.
   */
  function toggle_topbar(toggleItem) {

    // Elements to toggle
    var ddbasic_topbar_user = $('.js-topbar-user');
    var ddbasic_topbar_search = $('.js-topbar-search');
    var ddbasic_topbar_menu = $('.js-topbar-menu');

    switch (toggleItem) {
      case 'search':
        ddbasic_topbar_search.toggleClass('js-topbar-toggled');

        ddbasic_topbar_menu.removeClass('js-topbar-toggled');
        ddbasic_topbar_user.removeClass('js-topbar-toggled');
        break;
      case 'user':
        ddbasic_topbar_user.toggleClass('js-topbar-toggled');

        ddbasic_topbar_search.removeClass('js-topbar-toggled');
        ddbasic_topbar_menu.removeClass('js-topbar-toggled');
        break;
      case 'menu':
        ddbasic_topbar_menu.toggleClass('js-topbar-toggled');

        ddbasic_topbar_search.removeClass('js-topbar-toggled');
        ddbasic_topbar_user.removeClass('js-topbar-toggled');
        break;
    }
  }


  // When ready start the magic.
  $(document).ready(function () {

    // Link elements
    var ddbasic_topbar_link = $(".js-topbar-link");

    // Attach some onclick/touch magic
    ddbasic_topbar_link.on('click touchstart', function(event) {

      var clicked = $(this);

      // Toggle elements based on wich link is clicked.
      // User link was clicked.
      if (clicked.hasClass('topbar-link-user')) {
        toggle_topbar('user');
        // Add focus to login field.
        $('.js-topbar-user #edit-name').focus();
      }
      // Search link was clicked
      if (clicked.hasClass('topbar-link-search')) {
        toggle_topbar('search');
        // Add focus to search field.
        $('.js-topbar-search #edit-search-block-form--2').focus();
      }
      // Menu link was clicked
      if (clicked.hasClass('topbar-link-menu')) {
        toggle_topbar('menu');
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

    // Remove active class from topbar menu by default
    ddbasic_topbar_link.removeClass('active');

  });

})(jQuery);