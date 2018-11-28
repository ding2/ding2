/**
 * @file
 * Handles webtrekk tracking in the client.
 *
 * Some user interactions that we want to track doesn't result in a page load.
 * These interactions are tracked here with Webtrekk events in the client.
 *
 * Also handles has special handling for some elements, which are problematic
 * to handle in the backend.
 */

(function($) {

  "use strict"

  var appendQueryParameter = function(link, key, value) {
    var seperator = (link.indexOf('?') != -1) ? '&' : '?';
    var urlParameter = key + '=' + encodeURIComponent(value);
    return link + seperator + urlParameter;
  };


  Drupal.behaviors.ding_webtrekk = {
    attach: function(context) {
      // Attach Webtrekk events.
      $('.ding-webtrekk-event', context).once('ding-webtrekk').click(function() {
        wt.sendinfo($(this).data('ding-webtrekk-event'));
      });

      // Secial handling for ding entity rating event. It would require a
      // complete rework of the ding_entity_rating_display theme hook to avoid
      // this.
      $('.ding-webtrekk-rating-event', context).once('ding-webtrekk', function() {
        var contentId = $(this).data('ding-entity-rating-id');
        $('.js-rating-symbol', this).each(function(index) {
          $(this).click(function() {
            wt.sendinfo({
              type: 'e_materialrate',
              contentId: contentId,
              rating: ++index
            });
          });
        })
      });

      // Special handling for ding_carousel.
      $('.ding-carousel').each(function() {
        var carouselTitle = false;
        var key = 'u_navigatedby';

        if ($(this).parent().hasClass('ding-tabbed-carousel')) {
          carouselTitle = 'tabbed-carousel:' + $(this).data('title');
        }
        else if ($(this).parent().siblings('.pane-title')) {
          carouselTitle = $(this).parent().siblings('.pane-title').html();
        }

        if (carouselTitle) {
          // Add tracking URL-pararmeters to items in the carousel. Since they
          // are lazy loaded this is problematic to handle in backend.
          $('.ding-carousel-item .ting-object a[href^="/ting/object/"]', this).once('ding-webtrekk', function() {
            $(this).attr('href', appendQueryParameter($(this).attr('href'), key, carouselTitle));
          });

          $('.slick-arrow', this).once('ding-webtrekk').click(function() {
            var type = 'e_carousel_previous_click';
            if ($(this).hasClass('slick-next')) {
              type = 'e_carousel_next_click';
            }
            wt.sendinfo({
              type: type,
              carouselTitle: carouselTitle
            });
          });
        }
      });
    }
  };

})(jQuery);
