/*
 * Creates the topbar toggle menu
 */

(function($) {

  // When ready start the magic.
  $(document).ready(function () {

    // Elements to toggle
    var ddbasic_search = $('#topbar-search');
    var ddbasic_user_menu = $('#topbar-user-menu');
    var ddbasic_user_name = $('#topbar-user-name');
    var ddbasic_user_loans = $('#topbar-user-menu-loans');
    var ddbasic_user_login = $('#topbar-user-login');
    var ddbasic_navigation = $('.navigation-wrapper');

    // Link elements
    var ddbasic_search_link = $(".topbar-link-search");
    var ddbasic_user_link = $(".topbar-link-user");
    var ddbasic_menu_link = $(".topbar-link-menu");

    // Remove href link from topbar menu
    ddbasic_search_link.removeAttr('href');
    ddbasic_user_link.removeAttr('href');
    ddbasic_menu_link.removeAttr('href');

    // Attach some onclick magic
    ddbasic_search_link.click(function() {
      ddbasic_user_link.removeClass("active");
      ddbasic_menu_link.removeClass("active");
      ddbasic_search_link.addClass("active");
      $.cookie("ddbasic_topbar_state", "ddbasic_search");
      topbar_hide();
      ddbasic_search.toggle();
    });
    ddbasic_user_link.click(function() {
      ddbasic_user_link.addClass("active");
      ddbasic_menu_link.removeClass("active");
      ddbasic_search_link.removeClass("active");
      $.cookie("ddbasic_topbar_state", "ddbasic_user");
      topbar_hide();
      ddbasic_user_menu.toggle();
      ddbasic_user_name.toggle();
      ddbasic_user_loans.toggle();
      ddbasic_user_login.toggle();
    });
    ddbasic_menu_link.click(function() {
      ddbasic_user_link.removeClass("active");
      ddbasic_menu_link.addClass("active");
      ddbasic_search_link.removeClass("active");
      $.cookie("ddbasic_topbar_state", "ddbasic_navigation");
      topbar_hide();
      ddbasic_navigation.toggle();
    });

    /*
     * Check if our cookie value is allowed.
     */
    function check_cookie_val(cookie_val) {
      // Array with allowed cookie values.
      var allowed_cookie_vals = new Array(
        "ddbasic_search",
        "ddbasic_user",
        "ddbasic_navigation"
      );

      if (jQuery.inArray(cookie_val, allowed_cookie_vals) !== -1) {
        return true;
      }
      else {
        return false;
      }
    }

    /*
     * Hides all topbar elements.
     */
    function topbar_hide () {
      ddbasic_search.hide();
      ddbasic_user_menu.hide();
      ddbasic_user_name.hide();
      ddbasic_user_loans.hide();
      ddbasic_user_login.hide();
      ddbasic_navigation.hide();
    }

    // Hide everything
    topbar_hide();

    // Read cookie for current active toggle
    var cookie_val;
    if (check_cookie_val($.cookie("ddbasic_topbar_state"))) {
      // Read the cookie value and display
      cookie_val = $.cookie("ddbasic_topbar_state");
    }
    else {
      // Default state and set cookie
      $.cookie("ddbasic_topbar_state", "ddbasic_navigation");
      cookie_val = $.cookie("ddbasic_topbar_state");
    }

    switch (cookie_val) {
      case "ddbasic_navigation":
        topbar_hide();
        ddbasic_navigation.toggle();
        ddbasic_user_link.removeClass("active");
        ddbasic_menu_link.addClass("active");
        ddbasic_search_link.removeClass("active");
        $.cookie("ddbasic_topbar_state", "ddbasic_navigation");
        break;

      case "ddbasic_search":
        topbar_hide();
        ddbasic_search.toggle();
        ddbasic_user_link.removeClass("active");
        ddbasic_menu_link.removeClass("active");
        ddbasic_search_link.addClass("active");
        $.cookie("ddbasic_topbar_state", "ddbasic_search");
        break;
      case "ddbasic_user":
        topbar_hide();
        ddbasic_user_menu.toggle();
        ddbasic_user_name.toggle();
        ddbasic_user_loans.toggle();
        ddbasic_user_login.toggle();
        ddbasic_user_link.addClass("active");
        ddbasic_menu_link.removeClass("active");
        ddbasic_search_link.removeClass("active");
        $.cookie("ddbasic_topbar_state", "ddbasic_user");
        break;
    }

  });

})(jQuery);