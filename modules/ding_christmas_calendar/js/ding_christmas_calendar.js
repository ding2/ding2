(function ($) {
  "use strict";

  /**
   * Start the carousel when the document is ready.
   */
  $(document).ready(function() {
    var carousel_wrapper = $('.pane-ding-christmas-calendar-mobile .ding-christmas-calendar-widget');

    // Init carousel
    $(carousel_wrapper).slick({

      infinite: false,
      slidesToShow: 7,
      slidesToScroll: 3,

      responsive: [{
        breakpoint: 1024,
        settings: {
        slidesToShow: 3,
          dots: true,
          arrows: false,
        }
      },
      {
        breakpoint: 600,
        settings: {
          slidesToShow: 3,
          dots: true,
          arrows: false,
        }
      },
      {
        breakpoint: 480,
        settings: {
          slidesToShow: 1,
          slidesToScroll: 1,
          dots: false,
          arrows: true,
        }
      }]
    });

    $('.pane-ding-christmas-calendar-widget .future-day a').click(function(e) {
      var popUp = $('.calendar-popup .future-day-popup');
      popUp.fadeIn( 300, function() {
        setTimeout(function () {
          popUp.fadeOut(300);
        }, 1500);
      });
      e.preventDefault();
    });

    $('.pane-ding-christmas-calendar-mobile .future-day a').click(function(e) {
      $.notify(Drupal.t("Hov Hov. Do not cheat! You can not open the door yet"), "info");
      e.preventDefault();
    });
    //.pane-ding-christmas-calendar-mobile
  });
})(jQuery);
