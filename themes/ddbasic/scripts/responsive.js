(function ($) {
  'use strict';

  $(document).ready(function () {

    /**
    * Responsive class in body tag.
    */
    function responsiveClass() {

      var tag = $('body'),
        currentWidth = $(document).width(),
        scrollWidth = window.innerWidth - $(document).width();

      if (currentWidth <= (768 - scrollWidth)) {
        tag.addClass('responsive-layout-mobile').removeClass('responsive-layout-desktop').removeClass('responsive-layout-tablet');
      }

      else if (currentWidth > (768 - scrollWidth) && currentWidth <= (1024 - scrollWidth)) {
        tag.addClass('responsive-layout-tablet').removeClass('responsive-layout-desktop').removeClass('responsive-layout-mobile');
      }

      else if (currentWidth > (1024 - scrollWidth)) {
        tag.addClass('responsive-layout-desktop').removeClass('responsive-layout-tablet').removeClass('responsive-layout-mobile').removeClass('responsive-layout-tablet');
      }
    }

    // Change class on user resize, after DOM
    responsiveClass();

    $(window).resize(function () {
      responsiveClass();
    });
  });

})(jQuery);

