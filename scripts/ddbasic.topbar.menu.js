/**
 * Creates the top-bar toggle menu.
 */
(function($) {
  "use strict";

  /**
   * Toggle the search form from the top-bar menu.
   *
   * @param bool open
   *   If true the form and link are active/open.
   */
  function ddbasic_search(open) {
    if (open) {
      //ddbasic_strip_active();
      $('.topbar-menu .leaf .topbar-link-search').toggleClass('active');
      $('.js-topbar-search').toggleClass('open');
    } else {
      $('.topbar-menu .leaf .topbar-link-search').removeClass('active');
      $('.js-topbar-search').removeClass('open');
    }
  }

  /**
   * Toggle the mobile menu from the top-bar menu.
   *
   * @param bool open
   *   If true the form and link are active/open.
   */
  function ddbasic_mobile_menu(open) {
    if (open) {
      //ddbasic_strip_active();
      $('.topbar-menu .leaf .topbar-link-menu').toggleClass('active');
      $('.js-topbar-menu').toggleClass('open');
    } else {
      $('.topbar-menu .leaf .topbar-link-menu').removeClass('active');
      $('.js-topbar-menu').removeClass('open');
    }
  }

  /**
   * Toggle the user login form from the top-bar menu.
   *
   * @param bool open
   *   If true the form and link are active/open.
   */
  function ddbasic_user_login(open) {
    if (open) {
      //ddbasic_strip_active();
      $('.topbar-menu .leaf .topbar-link-user-account').toggleClass('active');
      $('.js-user-top-menu').toggleClass('open');
    } else {
      $('.topbar-menu .leaf .topbar-link-user-account').removeClass('active');
      $('.js-user-top-menu').removeClass('open');
    }
  }

  /**
   * Strip active open classes.
   */
  function ddbasic_strip_active() {
    //$('.topbar-menu .leaf .js-topbar-link').removeClass('active');
    $('.js-topbar-search').removeClass('open');
    $('.js-topbar-menu').removeClass('open');
    $('.js-user-top-menu').removeClass('open');
  }

  /**
   * When ready start the magic and handle the menu.
   */
  $(document).ready(function () {
    // Clone and add mobile link, this way we can add specific action on mobile devices.
    $('.js-topbar-link.topbar-link-user-account').clone().appendTo('.topbar-menu > .topbar-link-user-account');
    $('.topbar-menu .topbar-link-user-account .js-topbar-link:last-child').addClass('js-topbar-link-mobile');

    // Init the top bar.
    ddbasic_strip_active()
    $('.front .js-topbar-search').addClass('open');
    $('.front .leaf .topbar-link-menu').removeClass('active');
    $('.front .leaf .topbar-link-search').addClass('active');

    // If the search link is clicked toggle mobile menu and show/hide search.
    $('.js-topbar-link.topbar-link-search').on('click touchstart', function(e) {
      ddbasic_search(true);
      ddbasic_mobile_menu(false);
      ddbasic_user_login(false);
      e.preventDefault();
    });

    // If the mobile menu is clicked toggle search and show/hide menu.
    $('.js-topbar-link.topbar-link-menu').on('click touchstart', function(e) {
      ddbasic_mobile_menu(true);
      ddbasic_search(false);
      ddbasic_user_login(false);
      e.preventDefault();
    });

    // If the user login is clicked toggle user and show/hide user menu.
    $('.js-topbar-link.js-topbar-link-mobile').on('click touchstart', function(e) {
      ddbasic_user_login(true);
      ddbasic_mobile_menu(false);
      ddbasic_search(false);
      e.preventDefault();
    });


    /**
     * Add news category menu as sub-menu to news in main menu
     */

    if ($(".sub-menu-wrapper").length > 0) {
      $(".sub-menu-wrapper > .sub-menu").clone().appendTo('.main-menu > .active-trail');

      // Switch a few classes for style purposes.
      $(".main-menu .sub-menu a").addClass('menu-item');
      $(".main-menu .sub-menu").addClass('main-menu');
      $(".main-menu .sub-menu").removeClass('sub-menu');

      // The old menu is hidden by css on minor media queries.
    }

    /**
     * Adds library menu above content on local library pages.
     */
    if ($(".library-menu").length > 0) {
      // Move/copy the  library menu.
      $(".library-menu").clone().insertAfter('.primary-content .ding-library-image');

      //Change add selection markup and fix the classes.
      $(".primary-content .library-menu").addClass('js-library-menu-responsive');
      $(".primary-content .library-menu").removeClass('library-menu');
      $(".js-library-menu-responsive .links").wrap("<select></select>");
      $(".js-library-menu-responsive .links").removeClass('links');
      $(".js-library-menu-responsive select li").wrap("<option class='select-item'></option>");
      $(".js-library-menu-responsive select .select-item").unwrap();
      // Move a href to select value.
      $(".primary-content .js-library-menu-responsive select .select-item").each(function() {
        $ (this).attr("value", function() {
          return $(this).find("a").attr("href");
        });
      });
      // Now that path is preserved remove the li and a tags.
      $(".primary-content .js-library-menu-responsive select li a").unwrap();
      $(".primary-content .js-library-menu-responsive select a").replaceWith(function() {
        // Return the stripped text of the link.
        return $(this).contents();
      });
    };

    // Goto action.
    $(".js-library-menu-responsive select").change(function () {
      document.location.href = $(this).val();
    });
  });
})(jQuery);
