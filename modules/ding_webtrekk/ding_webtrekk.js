/**
 * @file
 * Handles webtrekk tracking in the client.
 *
 * Some user interactions that we want to track doesn't result in a page load.
 * These interactions are tracked here with Webtrekk events in the client.
 *
 * URL-parametes are used when we want to track relations. For example, was this
 * ting object view triggered by a link in a carousel? We prefer to attach these
 * parameters on the server, but in some cases this gets very complicated. For
 * example, all the object links in a carousel are not loaded all at once on the
 * page load, but is instead lazy loaded dynamically when the users uses the
 * carousel. In such cases, it's much easier to add the URL-parameters in
 * javascript on the client.
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

      // Unfortunately we need special handling for ding entity rating event. It
      // would require a complete rework of the ding_entity_rating_display theme
      // hook to avoid this.
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

      // Attach URL parameters.
      var key = 'u_navigatedby';
      // Tabbed carousels: each tab is a carousel with a title that we will use
      // for the value of the URL parameter.
      $('.ding-tabbed-carousel .ding-carousel').each(function() {
        var value = 'tabbed-carousel:' + $(this).data('title');

        $('.ding-carousel-item .ting-object a[href^="/ting/object/"]', this).once('ding-webtrekk', function() {
          $(this).attr('href', appendQueryParameter($(this).attr('href'), key, value));
        });
      });

      // Handle single non-tabbed carousels.
      $('.ding-carousel').each(function() {
        var carouselTitle = $(this).parent().siblings('.pane-title');
        // Carousels are lazy loaded, so we might not find something at first.
        if (carouselTitle.length) {
          var value = carouselTitle.html();

          $('.ding-carousel-item .ting-object a[href^="/ting/object/"]', this).once('ding-webtrekk', function() {
            $(this).attr('href', appendQueryParameter($(this).attr('href'), key, value));
          });
        }
      });
    }
  };

})(jQuery);
