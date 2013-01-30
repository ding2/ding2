(function($) {
  $(document).ready(function () {

    if ($('body').hasClass('front')) {
      // Get calculations for elements position on the page and their sizes.
      var menu = $('.navigation-wrapper');
      var pos = menu.offset();
      var menu_height = menu.height();
      var menu_pos_relative = (pos.top - 20) - menu_height;
      /**
      * @todo why do we need to have -20px offset ? If they are not there every
      * ting jumps.
      */

      // Take the Drupal toolbar into account and calculate padding.
      var body_paddding = parseInt($('body').css('paddingTop'), 10);
      if (body_paddding) {
        pos.top = pos.top - body_paddding;
      }

      if ($(window).scrollTop() > (menu_pos_relative)) {
        menu.addClass('fixed');

        // Only when Drupal toolbar is present.
        if (menu.hasClass('fixed') && body_paddding) {
          menu.css('top', body_paddding);
        }
      }

      // Hook into window scroll event.
      $(window).scroll(function(){
        // Figure out if we should fix position the menu or not.
        if ($(window).scrollTop() > menu_pos_relative) {
          menu.addClass('fixed');
          menu.css('top', body_paddding);
        }
        else if (menu.scrollTop() <= pos.top && menu.hasClass('fixed')) {
          menu.removeClass('fixed');
          menu.css('top', '');
        }
      });
    }
    else {
      // Not the front-page, so fix the menu.
      $('.navigation-wrapper').addClass('fixed');
    }
  });
})(jQuery);