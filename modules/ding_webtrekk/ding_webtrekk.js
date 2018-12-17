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

  "use strict";

  // Webtrekk tracking parameters.
  var DING_WEBTREKK_PARAMETER_AUTOCOMPLETE = 54;
  var DING_WEBTREKK_PARAMETER_RENEW_SELECTED = 55;
  var DING_WEBTREKK_PARAMETER_RENEW_RATING_ID = 57;
  var DING_WEBTREKK_PARAMETER_RENEW_RATING = 58;
  var DING_WEBTREKK_PARAMETER_CAROUSEL_NEXT = 59;
  var DING_WEBTREKK_PARAMETER_CAROUSEL_PREV = 60;

  var appendQueryParameter = function(url, key, value) {
    var seperator = (url.indexOf('?') !== -1) ? '&' : '?';
    var urlParameter = key + '=' + encodeURIComponent(value);
    return url + seperator + urlParameter;
  };

  Drupal.behaviors.ding_webtrekk = {
    attach: function(context) {
      // Send Webtrekk events attached in the backend.
      $('.js-ding-webtrekk-event', context).once('js-ding-webtrekk').click(function() {
        var eventData = $(this).data('ding-webtrekk-event');
        wts.push(['send', 'click', eventData]);
      });

      // Secial handling for ding entity rating event.
      //
      // It would require a complete rework of the ding_entity_rating_display
      // theme hook to avoid this. It doesn't provide the ability to add custom
      // attributes/classes in preprocess and is not using using render arrays
      // for rating elements, making them problematic to modify.
      $('.js-ding-webtrekk-rating-event', context).once('js-ding-webtrekk', function() {
        var contentId = $(this).data('ding-entity-rating-id');
        $('.js-rating-symbol', this).each(function(index) {
          var rating = (index + 1) + '';
          $(this).click(function() {
            wts.push(['send', 'click', {
              linkId: 'Materiale rating',
              customClickParameter: {
                DING_WEBTREKK_PARAMETER_RENEW_RATING: rating,
                DING_WEBTREKK_PARAMETER_RENEW_RATING_ID: contentId
              }
            }]);
          });
        });
      });

      // Track autocomplete selections.
      $('.js-ding-webtrekk-autocomplete .form-autocomplete', context)
        .once('js-ding-webtrekk')
        .on('autocompleteSelect', function(e, selected) {
          if (($(selected).text())) {
            console.log($(selected).text());
            wts.push(['send', 'click', {
              linkId: 'Autocomplete søgning clicks',
              customClickParameter: {
                DING_WEBTREKK_PARAMETER_AUTOCOMPLETE: $(selected).text()
              }
            }]);
          }
      });

      // Track ding loan renew selected events.
      //
      // The renew all button is attached completely on the server, but for
      // renew selected, we need information about selected loans in the UI,
      // before we send event.
      $('.js-ding-webtrekk-event-renew-selected', context)
        .once('js-ding-webtrekk')
        .click(function(e) {
          // The renew-all button is implemented by checking all renewable loans
          // and then trigger a click on the renew-selected button. We can use
          // originalEvent to check for this.
          if (e.originalEvent === undefined) {
            return;
          }

          var selectedMaterials = [];
          $('.material-item input[type=checkbox]:checked').each(function() {
            // We have collected the material ids (pids) in our event data
            // attribute for each select box.
            selectedMaterials.push($(this).data('ding-webtrekk-event'));
          });
          wts.push(['send', 'click', {
            linkId: 'Forny valgte materialer',
            customClickParameter: {
              DING_WEBTREKK_PARAMETER_RENEW_SELECTED: selectedMaterials.join(';')
            }
          }]);
      });

      // Special handling for ding_carousel.
      //
      // The primary reason for this is that we need the title of the carousel
      // to pass as value in event and URL-parameter. For tabbed carousels the
      // title of the individuals carousels in the tabs are set in the
      // data-title attribute of the carousels. For single carousels the title
      // is not avialable here, but instead it's controlled by the configuration
      // on the panel pane. There are no panel hooks where we can get the title
      // and easily change the content tree to add event and URL-parameters to
      // elements (content is already rendered when hook is run).
      $('.ding-carousel').each(function() {
        var key = 'u_navigatedby';
        // We need a title to send as value in the 'u_navigatedby' parameter, so
        // if we can't find a carousel title we will just have to fallback to
        // this generic one.
        var carouselTitle = 'unknown_carousel';

        if ($(this).data('title')) {
          carouselTitle = $(this).data('title');
        }
        else if ($(this).parent().siblings('.pane-title').length > 0) {
          carouselTitle = $(this).parent().siblings('.pane-title').html();
        }

        // Add tracking URL-pararmeters to items in the carousel.
        $('.ding-carousel-item .ting-object a[href^="/ting/object/"]', this).once('js-ding-webtrekk', function() {
          $(this).attr('href', appendQueryParameter($(this).attr('href'), key, carouselTitle));
        });

        $('.slick-arrow', this).once('js-ding-webtrekk').click(function() {
          var linkId = 'Karousel, click på forrige knappen';
          var customClickParameter = {
            DING_WEBTREKK_PARAMETER_CAROUSEL_PREV: carouselTitle
          };
          if ($(this).hasClass('slick-next')) {
            linkId = 'Karousel, click på næste knappen';
            customClickParameter = {
              DING_WEBTREKK_PARAMETER_CAROUSEL_NEXT: carouselTitle
            };
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
