/**
 * @file
 * Handles the carousels loading of content and changes between tabs. There are
 * two selectors to change tabs based on breaks points (which is handle by the
 * theme).
 *
 * For large screens the normal tab list (ul -> li) is used while on small
 * screens (mobile/tables) a select dropdown is used.
 *
 */
(function ($) {
  "use strict";

  var TingCarousel = (function() {
    var carousel;

    /**
     * Private: Check is the device have support for touch events.
     */
    function _is_touch_device() {
      // First part work in most browser the last in IE 10.
      return !!('ontouchstart' in window) || !!('onmsgesturechange' in window);
    }

    /**
     * Private: Enable draggable touch support to the carousel, but only if the
     * device is touch enabled.
     */
    function _add_touch_support() {
      if (_is_touch_device()) {
        $('.rs-carousel-runner', carousel).data('carousel', carousel);

        // Add support for touch displays (requires jQuery Touch Punch).
        $('.rs-carousel-runner',carousel).draggable({
          axis: "x",
          start: function (evt) {
            var carousel = $(this).data('carousel');
            if (($('.rs-carousel-mask',carousel).width() - $('.rs-carousel-runner',carousel).width()) > 0) {
              evt.preventDefault();
            }
          },
          stop: function() {
            var
              carousel = $(this).data('carousel'),
              left = $('.rs-carousel-runner',carousel).position().left;

            // Left side reached.
            if (left > 0) {
              carousel.carousel('goToPage', 0);
            }

            // Right side reached.
            if ($('.rs-carousel-mask',carousel).width() - $('.rs-carousel-runner',carousel).width() > left) {
              var lastIndex = carousel.carousel('getNoOfPages') - 1;
              carousel.carousel('goToPage', lastIndex);
            }
          }
        });
      }
    }

    /**
     * Public: Init the carousel and fetch content for the first tab.
     */
    function init(prefixer, context) {
      // Select the carousel element.
      carousel = $(prefixer + ' .rs-carousel-items', context);

      if (carousel.length === 0) {
        return;
      }

      // Start the carousel.
      carousel.carousel({
        noOfRows: 1,
        orientation: 'horizontal',
        itemsPerTransition: 'auto'
      });

      if (!carousel.data('carinit')) {
        // Maybe add support for touch devices (will only be applied on touch
        // enabled devices).
        _add_touch_support();
      }

      carousel.data('carinit', true);
    }

    /**
     * Expoes public functions.
     */
    return {
        name: 'ting_carousel',
        init: init
    };
  })();

  Drupal.behaviors.ting_carousel = {
    attach: function (context) {
      for (var i in Drupal.settings.ting_carousel) {
        TingCarousel.init(Drupal.settings.ting_carousel[i], context);
      }
    }
  };

  $(window).bind('resize', function () {
    for (var i in Drupal.settings.ting_carousel) {
      TingCarousel.init(Drupal.settings.ting_carousel[i]);
    }
  });
})(jQuery);
