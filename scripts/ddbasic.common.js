(function($) {
  $(document).ready(function () {

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

    $(window).scroll(function(){
      if ($(window).scrollTop() > menu_pos_relative) {
        menu.addClass('fixed');
      }
      else if (menu.scrollTop() <= pos.top && menu.hasClass('fixed')) {
        menu.removeClass('fixed');
      }

      // Only when Drupal toolbar is present.
      if (menu.hasClass('fixed') && body_paddding) {
        menu.css('top', body_paddding);
      }
      else {
        menu.css('top', '');
      }
    });

  });
})(jQuery);