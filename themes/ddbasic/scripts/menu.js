/*jshint forin:false, jquery:true, browser:true, indent:2, trailing:true, unused:false */
(function (scope, $) {
  'use strict';

  // Hide and show header on mobile
  var last_scroll_top = 0,
      scroll_delta = 100,
      topbar_height = 148;
  $(window).on('scroll.header', function() {
    // If mobile
    if (ddbasic.breakpoint.is('mobile')) {
      var st = $(window).scrollTop();

      // Make sure they scroll more than delta.
      if(Math.abs(last_scroll_top - st) <= scroll_delta) {
        return;
      }

      // If they scrolled down and are past the topbar, add class .topbar-up.
      if(st > last_scroll_top && st > topbar_height) {
          // Scroll Down
          $('body').addClass('topbar-up');
      } else {
          // Scroll Up
          if(st + $(window).height() < $(document).height()) {
            $('body').removeClass('topbar-up');
          }
      }

      last_scroll_top = st;
    }
  });

  $(window).on('dingpopup-close', function () {
    $('body').removeClass('pane-login-is-open overlay-is-active');
  });

  /**
   * Menu functionality.
   */
  Drupal.behaviors.menu = {
    attach: function(context, settings) {
      var topbar_link_user = $('a.topbar-link-user', context),
          main_menu_wrapper = $('.main-menu-wrapper', context),
          secondary_menu_wrapper = $('.secondary-menu-wrapper', context),
          close_user_login = $('.close-user-login', context),
          mobile_menu_btn = $('a.topbar-link-menu', context),
          search_btn = $('a.topbar-link-search', context),
          search_extended_btn = $('a.search-extended-button', context),
          first_level_expanded = $('.main-menu-wrapper > .main-menu > .expanded > a .main-menu-expanded-icon', context),
          second_level_expanded = $('.main-menu-wrapper > .main-menu > .expanded > .main-menu > .expanded > a .main-menu-expanded-icon', context),
          body = $('body');

      // Scope fixes for inner functions.
      var thisScope = this;

      // We need to check this initially.
      thisScope.checkMainSecondaryMenusOffset(context);

      // We also need to check it everytime we resize the screen.
      $(window).resize(function() {
        thisScope.checkMainSecondaryMenusOffset(context);
      });

      mobile_menu_btn.on('click', function(evt){
        evt.preventDefault();
        body.toggleClass('mobile-menu-is-open');
        body.removeClass('mobile-search-is-open pane-login-is-open mobile-usermenu-is-open');
        body.toggleClass('overlay-is-active');
        if(body.hasClass('mobile-menu-is-open')) {
          body.addClass('overlay-is-active');
        } else {
          body.removeClass('overlay-is-active');
        }
      });

      search_btn.on('click', function(evt){
        evt.preventDefault();
        body.toggleClass('mobile-search-is-open');
        body.removeClass('mobile-menu-is-open pane-login-is-open mobile-usermenu-is-open');
        if(body.hasClass('mobile-search-is-open')) {
          body.addClass('overlay-is-active');
        } else {
          body.removeClass('overlay-is-active');
        }
      });

      topbar_link_user.on('click', function(evt) {
        evt.preventDefault();
        ddbasic.openLogin();
      });

      close_user_login.on('click', function(evt) {
        evt.preventDefault();
        body.removeClass('pane-login-is-open');
        body.removeClass('overlay-is-active');
      });

      first_level_expanded.on('click', function(evt) {
        if($('.is-tablet').is(':visible')) {
          evt.preventDefault();
          first_level_expanded.not($(this)).parent().parent().children('.main-menu').slideUp(200);
          $(this).toggleClass('open');
          $(this).parent().parent().children('.main-menu').slideToggle(200);
        }
      });

      second_level_expanded.on('click', function(evt) {
        if($('.is-tablet').is(':visible')) {
          evt.preventDefault();
          second_level_expanded.not($(this)).removeClass('open');
          second_level_expanded.not($(this)).parent().parent().children('.main-menu').slideUp(200);
          $(this).toggleClass('open');
          $(this).parent().parent().children('.main-menu').slideToggle(200);
        }
      });

      search_extended_btn.on('click', function(evt) {
        evt.preventDefault();
        body.toggleClass('extended-search-is-not-open');
      });

      // Tablet/mobile menu logout
      // Logout-link is created with after-element.
      // We check if after-element is clicked by checking if clicked point has a
      // larger y position than the menu itself.
      $('.header-wrapper .navigation-inner > ul.main-menu-third-level').click(function(evt) {
        if($('.is-tablet').is(':visible')) {
          var menu_offset = $('.header-wrapper .navigation-inner > ul.main-menu-third-level').offset(),
              menu_item = $('.header-wrapper .navigation-inner > ul.main-menu-third-level > li'),
              menu_height = 0;

          menu_item.each(function( index ) {
            menu_height = menu_height + $(this).outerHeight();
          });
          if (evt.offsetY > (menu_offset.top + menu_height)) {
            window.location.href = "/user/logout";
          }
        }
      });
    },

    // If there are too many links in either the main or secondary menu,
    // we need to tell the CSS so it can adjust the fixed header elements.
    checkMainSecondaryMenusOffset: function(context) {
      var main_menu_wrapper = $('.main-menu-wrapper', context),
          secondary_menu_wrapper = $('.secondary-menu-wrapper', context);

      // One is missing, so we'll skip out.
      if (!main_menu_wrapper.length || !secondary_menu_wrapper.length) {
        return;
      }

      if (main_menu_wrapper[0].offsetTop != secondary_menu_wrapper[0].offsetTop) {
        $('body').addClass('secondary-menu-below-main');
      } else {
        $('body').removeClass('secondary-menu-below-main');
      }
    }
  };

  /**
   * Add flex menu to second level.
   */
  Drupal.behaviors.second_level_menu = {
    attach: function(context, settings) {
      $('ul.main-menu-second-level').flexMenu({
        linkText: Drupal.t('More') + '...',
        popupAbsolute: false,
        cutoff: 1
      });
    }
  };

})(this, jQuery);
