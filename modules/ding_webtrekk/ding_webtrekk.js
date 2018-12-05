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
    var seperator = (link.indexOf('?') !== -1) ? '&' : '?';
    var urlParameter = key + '=' + encodeURIComponent(value);
    return link + seperator + urlParameter;
  };

  Drupal.behaviors.ding_webtrekk = {
    attach: function(context) {
      // Attach Webtrekk events. This is the preffered to track events in ding
      // webtrekk. Modules can alter elements in the backend and add the class
      // 'ding-webtrekk-event' to enable event traking for that element. Event
      // data is expected to be passed in the data attribute on the element.
      $('.ding-webtrekk-event', context).once('ding-webtrekk').click(function() {
        var eventData = $(this).data('ding-webtrekk-event');
        wts.push(['send', 'click', eventData]);
      });

      // Secial handling for ding entity rating event. It would require a
      // complete rework of the ding_entity_rating_display theme hook to avoid
      // this. It doesn't provide the ability to add custom attributes/classes
      // in preprocess and is not using using render arrays for the rating
      // elements, making it really hard to do anything with them.
      $('.ding-webtrekk-rating-event', context).once('ding-webtrekk', function() {
        var contentId = $(this).data('ding-entity-rating-id');
        $('.js-rating-symbol', this).each(function(index) {
          var rating = (index + 1) + '';
          $(this).click(function() {
            wts.push(['send', 'click', {
              linkId:'Materiale rating',
              customClickParameter: {
                58: rating,
                57: contentId
              }
            }]);
          });
        })
      });

      // Track autocomplete selections.
      $('.form-item-search-block-form .form-autocomplete', context)
        .once('ding-webtrekk')
        .on('autocompleteSelect', function(e, selected) {
          if (($(selected).text())) {
            wts.push(['send', 'click', {
              linkId: 'Autocomplete søgning clicks',
              customClickParameter: { 54: $(selected).text() }
            }]);
          }
      });

      // Special handling for ding_carousel. The primary reason for this is that
      // we need the title of the carousel to pass as value in event and URL-
      // parameter. For tabbed carousels the title of the individuals carousels
      // in the tabs are set in the data-title attribute of the carousels. For
      // single carousels the title is not avialable here, but instead it's
      // controlled by the configuration on the panel pane. There are no panel
      // hooks where we can get the title and easily change the content tree to
      // add event and URL-parameters to elements (content is already rendered
      // when hook is run).
      $('.ding-carousel').each(function() {
        var carouselTitle = false;
        var key = 'u_navigatedby';

        // We need a title to send as value in the 'u_navigatedby' parameter, so
        // if we can't find a carousel title we will just have to fallback to
        // this generic one.
        carouselTitle = 'unknown_carousel';

        if ($(this).data('title')) {
          carouselTitle = $(this).data('title');
        }
        else if ($(this).parent().siblings('.pane-title').length > 0) {
          carouselTitle = $(this).parent().siblings('.pane-title').html();
        }

        // Add tracking URL-pararmeters to items in the carousel.
        $('.ding-carousel-item .ting-object a[href^="/ting/object/"]', this).once('ding-webtrekk', function() {
          $(this).attr('href', appendQueryParameter($(this).attr('href'), key, carouselTitle));
        });

        $('.slick-arrow', this).once('ding-webtrekk').click(function() {
          var linkId = 'Karousel, click på forrige knappen';
          var customClickParameter = { 60: carouselTitle };
          if ($(this).hasClass('slick-next')) {
            linkId = 'Karousel, click på næste knappen';
            customClickParameter = { 59: carouselTitle };
          }
          wts.push(['send', 'click', {
            linkId: linkId,
            customClickParameter: customClickParameter
          }]);
        });
      });
    }
  };

})(jQuery);
