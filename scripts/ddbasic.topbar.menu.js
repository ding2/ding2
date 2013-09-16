/**
 * Creates the top-bar toggle menu.
 */
(function($) {
  "use strict";

  function ddbasic_search(init) {
    var search_link = $('.js-topbar-link.topbar-link-search');
    var search_form = $('.header-wrapper');

    // Handle default init value (false);
    init = typeof init !== 'undefined' ? init : false;

    if (init) {
      // If on front-page display search.
      if ($('body').hasClass('front')) {
        search_link.toggleClass('active');
        search_form.toggle();
      }
      else {
        search_link.removeClass('active');
        search_form.hide();
      }
    }
    else {
      search_link.toggleClass('active');
      search_form.toggle();
    }
  }

  function ddbasic_mobile_menu(init) {
    var menu_link = $('.js-topbar-link.topbar-link-menu');
    var menu = $('.js-topbar-menu');

    // Handle default init value (false);
    init = typeof init !== 'undefined' ? init : false;

    if (init) {
      menu_link.removeClass('active');
    }
    else {
      menu_link.toggleClass('active');
      menu.toggleClass('js-topbar-toggled');
    }
  }


  /**
   * When ready start the magic and handle the menu.
   */
  $(document).ready(function () {
    // Init search form/header.
    ddbasic_search(true);

    // Init mobile menu.
    ddbasic_mobile_menu(true);

    // If the search link is click toggle mobile menu if shown and display search.
    $('.js-topbar-link.topbar-link-search').on('click touchstart', function(e) {
      if ($('.js-topbar-link.topbar-link-menu').hasClass('active')) {
        // Mobile menu is open, so close it.
        ddbasic_mobile_menu();
      }
      ddbasic_search();
      e.preventDefault();
    });

    // If the mobile menu is click toggle search if displayed and display menu.
    $('.js-topbar-link.topbar-link-menu').on('click touchstart', function(e) {
      if ($('.js-topbar-link.topbar-link-search').hasClass('active')) {
        // Search is open, so close it.
        ddbasic_search();
      }
      ddbasic_mobile_menu();
      e.preventDefault();
    });

    /**
     * Add news category menu as sub-menu to news in main menu
     */
    if ($(".pane-news-category-menu").length > 0) {
      $(".pane-news-category-menu .sub-menu").clone().appendTo('.menu-mlid-1793');
      // Do some class magic to get the sub-menu reacting like drupal standard sub-menus.
      $(".main-menu .sub-menu").addClass('main-menu');
      $(".main-menu .sub-menu").removeClass('sub-menu');
      // Add sub-menu-wrapper class to taxonomy menu
      $(".pane-news-category-menu").addClass('sub-menu-wrapper');
    }

    /*
     * Add event category menu as sub-menu to event in main menu
     */
    if ($(".pane-event-category-menu").length > 0) {
      $(".pane-event-category-menu .sub-menu").clone().appendTo('.menu-mlid-1816');
      // Do some class magic to get the sub-menu reacting like drupal standard sub-menus.
      $(".main-menu .sub-menu").addClass('main-menu');
      $(".main-menu .sub-menu").removeClass('sub-menu');
      // Add sub-menu-wrapper class to taxonomy menu
      $(".pane-event-category-menu").addClass('sub-menu-wrapper');
    }
  });
})(jQuery);
