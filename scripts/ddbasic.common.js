(function($) {
  $(document).ready(function () {

    // Get calculations for elements position on the page and their sizes.
    var menu = $('.navigation-wrapper');
    var pos = menu.offset();
    var menu_height = menu.height();
    var menu_pos_relative = pos.top - menu_height;

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

      /**
       * @todo: what does this do !
       */
      $('.js-fixed-element').each(function() {
        $(this).show();
      });
    }

//    console.log(pos);
//    console.log(menu_height);

    $(window).scroll(function(){
//      console.log($(window).scrollTop());
//      console.log(menu_pos_relative);
      if ($(window).scrollTop() > menu_pos_relative) {
        menu.addClass('fixed');

        /**
         * @todo: what does this do !
         */
        $('.js-fixed-element').each(function() {
          $(this).show();
        });
      }
      else if (menu.scrollTop() <= pos.top && menu.hasClass('fixed')) {
        menu.removeClass('fixed');
        $('.js-fixed-element').each(function() {
          $(this).hide();
        });
      }

      // Only when Drupal toolbar is present.
      if (menu.hasClass('fixed') && body_paddding) {
        menu.css('top', body_paddding);
      }
      else {
        menu.css('top', '');
      }
    });


    // Toggle element.
    $(".js-show-element").click(function() {

      var self = $(this);

      var $element = $("." + self.attr("rel"));
      var offset = self.offset();

      /**
       * @todo is this needed
       */
      if (self.hasClass("active")) {
        self.removeClass("active");
      }
      else {
        self.addClass("active");
      }

      $element.toggle();
      $element.css({
        "top": offset.top + 72,
        "left": offset.left - 275
      });
    });

    // Hide element
    $(".js-hide-element").click(function() {
      $(this).parent().hide();
    });
  });

})(jQuery);