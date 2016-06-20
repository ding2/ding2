(function ($) {
  "use strict";

  /**
   * Start the carousel when the document is ready.
   */
  $(document).ready(function() {
    var carousel_wrapper = $('.pane-ding-christmas-calendar-mobile .ding-christmas-calendar-widget');

    // Init carousel
    $(carousel_wrapper).slick({

      infinite: true,
      slidesToShow: 7,
      slidesToScroll: 3,

      responsive: [{
        breakpoint: 1024,
        settings: {
        slidesToShow: 4,
          dots: true,
          arrows: false,
        }
      }, {
        breakpoint: 600,
        settings: {
          slidesToShow: 3,
          dots: true,
          arrows: false,
        }
      }, {
        breakpoint: 480,
        settings: {
          slidesToShow: 1,
          slidesToScroll: 1,
          dots: false,
          arrows: true,
        }
      }]
    });
  });
})(jQuery);
