/**
 * Creates the top-bar toggle menu.
 */
(function($) {
  "use strict";

  /**
   * Toggle the search form from the top-bar menu.
   *
   * @param Boolean open
   *   If true we want to open the form and link else we want to close it.
   */
  function ddbasic_search(open) {
    if (open) {
      // If the user clicked the active link, close it instead.
      if ($('.topbar-menu .leaf .topbar-link-search').hasClass('active')) {
        $('.topbar-menu .leaf .topbar-link-search').toggleClass('active');
        $('.js-topbar-search').css("display", "none");
      }
      else {
        // Display the element.
        $('.topbar-menu .leaf .topbar-link-search').toggleClass('active');
        $('.js-topbar-search').css("display", "block");
      }
    }
    else {
      $('.topbar-menu .leaf .topbar-link-search').removeClass('active');
      $('.js-topbar-search').css("display", "none");
    }
  }

  /**
   * Toggle the mobile menu from the top-bar menu.
   *
   * @param bool open
   *   If true we want to open the form and link else we want to close it.
   */
  function ddbasic_mobile_menu(open) {
    if (open) {
      // If the user clicked the active link, close it instead.
      if ( $('.topbar-menu .leaf .topbar-link-menu').hasClass('active') ) {
        $('.topbar-menu .leaf .topbar-link-menu').toggleClass('active');
        $('.site-header .js-topbar-menu').css("display", "none");
      }
      else {
        // Display the element.
        $('.topbar-menu .leaf .topbar-link-menu').toggleClass('active');
        $('.site-header .js-topbar-menu').css("display", "block");
      }
    }
    else {
      $('.topbar-menu .leaf .topbar-link-menu').removeClass('active');
    }
  }

  /**
   * Toggle the user login form from the top-bar menu.
   *
   * @param bool open
   *   If true we want to open the form and link else we want to close it.
   */
  function ddbasic_user_login(open) {
    if (open) {
      // If the user clicked the active link, close it instead.
      if ( $('.topbar-menu .leaf .topbar-link-user').hasClass('active') ) {
        $('.topbar-menu .leaf .topbar-link-user').toggleClass('active');
        $('.js-topbar-user').css("display", "none");
      }
      else {
        // Display the element.
        $('.topbar-menu .leaf .topbar-link-user').toggleClass('active');
        $('.js-topbar-user').css("display", "block");
      }
    }
    else {
      $('.topbar-menu .leaf .topbar-link-user').removeClass('active');
      $('.js-topbar-user').css("display", "none");
    }
  }

  /**
   * Toggle the user menu when logged in
   *
   * @param bool open
   *   If true we want to open the form and link else we want to close it.
   */
  function ddbasic_user_account(open) {
    if (open) {
      // If the user clicked the active link, close it instead.
      if ( $('.topbar-menu .leaf .topbar-link-user-account').hasClass('active') ) {
        $('.topbar-menu .leaf .topbar-link-user-account').toggleClass('active');
        $('.js-mobile-user-menu').css("display", "none");
      }
      else {
        // Display the element.
        $('.topbar-menu .leaf .topbar-link-user-account').toggleClass('active');
        $('.js-mobile-user-menu').css("display", "block");
      }
    }
    else {
      $('.topbar-menu .leaf .topbar-link-user-account').removeClass('active');
      $('.js-mobile-user-menu').css("display", "none");
    }
  }

  /**
   * When ready start the magic and handle the menu.
   */
  $(document).ready(function () {
    // Open search as default on front page, close on others.
    $('.js-topbar-search').css("display", "none");
    $('.front .js-topbar-search').css("display", "block");

    //Hide user login on load.
    $('.js-topbar-user').css("display", "none");

    // Set active classes on menu.
    $('.front .leaf .topbar-link-menu').removeClass('active');
    $('.front .leaf .topbar-link-search').addClass('active');

    // If the search link is clicked toggle mobile menu and show/hide search.
    $('.js-topbar-link.topbar-link-search').on('click touchstart', function(e) {
      ddbasic_search(true);
      ddbasic_mobile_menu(false);
      ddbasic_user_login(false);
      ddbasic_user_account(false);
      e.preventDefault();
    });

    // If the mobile menu is clicked toggle search and show/hide menu.
    $('.js-topbar-link.topbar-link-menu').on('click touchstart', function(e) {
      ddbasic_mobile_menu(true);
      ddbasic_search(false);
      ddbasic_user_login(false);
      ddbasic_user_account(false);
      e.preventDefault();
    });

    // If the user login is clicked toggle user and show/hide user menu.
    $('.js-topbar-link.topbar-link-user').on('click touchstart', function(e) {
      ddbasic_user_login(true);
      ddbasic_mobile_menu(false);
      ddbasic_search(false);
      e.preventDefault();
    });

    // If the user login is clicked toggle user and show/hide user menu.
    $('.js-topbar-link.topbar-link-user-account.default-override').on('click touchstart', function(e) {
      ddbasic_user_account(true);
      ddbasic_mobile_menu(false);
      ddbasic_search(false);
      e.preventDefault();
    });

    /**
     * Add news category menu as sub-menu to news in main menu
     */

    if ($(".sub-menu-wrapper").length > 0) {
      $('.sub-menu-wrapper > .sub-menu').clone().appendTo('.main-menu > .active-trail');

      // Switch a few classes for style purposes.
      $('.main-menu .sub-menu a').addClass('menu-item');
      $('.main-menu .sub-menu').addClass('main-menu');
      $('.main-menu .sub-menu').removeClass('sub-menu');

      // The old menu is hidden by css on minor media queries.
    }

    /**
     * Adds sub menu above content in Organic groups with OG menu.
     */
    var sub_menu = $(".pane-og-menu-og-single-menu-block");
    if (sub_menu.length) {
      var select = $('<select class="js-og-sub-menu"/>');
      select.addClass('js-og-sub-menu-responsive');

      // Populate drop-down with menu items
      $('a', sub_menu).each(function() {
        var el = $(this);
        $('<option />', {
          "value" : el.attr('href'),
          "text" : el.text(),
          "selected" : el.hasClass('active')
        }).appendTo(select);
      });

      // Detect where to insert the menu. Start with under the library image.
      var target = $('.primary-content .ding-library-image');
      if (!target.length) {
        target = $('.pane-menu-title');
      }

      if (!target.length) {
        // Groups (temaer) pages.
        target = $('.field-name-field-ding-group-title-image');
      }


      if (!target.length) {
        // Static page in OG group and library about page.
        target = $('article.page .page-title');
      }

      // Insert the drop-down if target where found.
      if (target.length) {
        // Attach the menu to the page.
        select.insertAfter(target);

        // Attach "on change" handle to new drop-down menu.
        $(select).change(function () {
         document.location.href = $(this).val();
        });
      }
    }

    // Check if #login fragment is in url.
    var hash = window.location.hash;
    if (hash === "#login") {
      //Show login box.
      ddbasic_user_login(true);
      ddbasic_mobile_menu(false);
      ddbasic_search(false);
    }

    // Figure out if login failed by URL and messaages.
    var url = window.location.toString();
    if (url.indexOf('ding_frontpage') > -1) {
      // Looks like a redirect after a failed login.
      var message = $('.messages');
      if (message.length > 0) {
        // We got messages, positive.
        if (message.hasClass('error')) {
          // And errors. We are guessting the login failed.
          ddbasic_user_login(true);
          ddbasic_mobile_menu(false);
          ddbasic_search(false);
        }
      }
    }
  });
})(jQuery);
