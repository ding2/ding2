/*jshint forin:false, jquery:true, browser:true, indent:2, trailing:true, unused:false */

(function (scope, $) {
  'use strict';

  // The default slick options.
  // These can be overriden by the current theme.
  scope.ting_carousel_slick_options = scope.ting_carousel_slick_options || {
    infinite: false,
    slidesToShow: 4,
    slidesToScroll: 4,
    arrows: true,
    responsive: [
        {
          breakpoint: 1100,
          settings: {
            slidesToShow: 3,
            slidesToScroll: 3

          }
        },
        {
          breakpoint: 600,
          settings: {
            slidesToShow: 1.5,
            slidesToScroll: 1
          }
        }
      ]
  };

  Drupal.behaviors.ting_carousel = {
    attach: function(context, settings) {
      $('.ting-carousel, .ting-carousel-field > .field-items', context).each(function (delta, carousel) {
        var $carousel = $(carousel);

        $carousel.slick(ting_carousel_slick_options);
      });
    }
  };
})(this, jQuery);
