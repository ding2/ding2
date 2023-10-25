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
  var DING_WEBTREKK_PARAMETER_COVER_PRESENT = 49;
  var DING_WEBTREKK_PARAMETER_DELETE_RESERVATION_SELECTED = 67;

  var appendQueryParameter = function appendQueryParameter(url, key, value) {
    var seperator = (url.indexOf('?') !== -1) ? '&' : '?';
    var urlParameter = key + '=' + encodeURIComponent(value);
    return url + seperator + urlParameter;
  };

  var pushEvent = function pushEvent(event, eventData) {
    if (Drupal.settings.dingWebtrekk.debugMode) {
      console.log('Ding webtrekk - Pushing ' + event + ' event with data: ',
        JSON.stringify(eventData, null, 2)
      );
    }
    // Ensure that the Webtrekk object is defined before pushing event.
    if (typeof wts !== 'undefined') {
      wts.push(['send', event, eventData]);
    }
  };

  // Other modules dealing with client side webtrekk tracking might find these
  // functions useful, so make them available on the global Drupal object.
  Drupal.dingWebtrekkAppendQueryParameter = appendQueryParameter;
  Drupal.dingWebtrekkPushEvent = pushEvent;

  Drupal.dingWebtrekkCoverFound = false;

  Drupal.behaviors.ding_webtrekk = {
    attach: function(context) {
      // Send Webtrekk events attached in the backend.
      $('.js-ding-webtrekk-event', context)
        .once('js-ding-webtrekk')
        .click(function() {
          var eventData = $(this).data('ding-webtrekk-event');
          pushEvent('click', eventData);
        }
      );

      // Track autocomplete selections.
      $('.js-ding-webtrekk-autocomplete .form-autocomplete', context)
        .once('js-ding-webtrekk')
        .on('autocompleteSelect', function(e, selected) {
          if (($(selected).text())) {
            var eventData = {
              linkId: 'Autocomplete søgning clicks',
              customClickParameter: {}
            };
            eventData.customClickParameter[DING_WEBTREKK_PARAMETER_AUTOCOMPLETE] = $(selected).text();
            pushEvent('click', eventData);
          }
        }
      );

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

          var eventData = {
            linkId: 'Forny valgte materialer',
            customClickParameter: {}
          };
          eventData.customClickParameter[DING_WEBTREKK_PARAMETER_RENEW_SELECTED] = selectedMaterials.join(';');
          pushEvent('click', eventData);
      });

      // Track ding reservation selected events.
      //
      // The delete all button is attached completely on the server, but for
      // delete selected, we need information about selected reservations in the UI,
      // before we send event.
      //
      // There is defined a click events which hinders ours from firing so we use mousedown in stead.
      var deleteReservationHandler = function (e) {
        var numberSelected = $('.material-item input[type=checkbox]:checked').length;
        var eventData = {
          linkId: 'Slet valgte reservering',
          customClickParameter: {}
        };
        eventData.customClickParameter[DING_WEBTREKK_PARAMETER_DELETE_RESERVATION_SELECTED] = numberSelected.toString();
        pushEvent('click', eventData);
      }

      $('.js-ding-webtrekk-event-delete-selected', context)
        .once('js-ding-webtrekk')
        .mousedown(deleteReservationHandler);

      // We dont want send parameters twice. The delete all buttons selects all reserverations
      // and fires off the delete select reservation handler. So we unbind it.
      $('.delete-all', context).click(function(e) {
        $('.js-ding-webtrekk-event-delete-selected').unbind('mousedown', deleteReservationHandler);
      });

      // Special handling for ding_carousel.
      //
      // The primary reason for this is that we need the title of the carousel
      // to pass as value in event and URL-parameter. For tabbed carousels the
      // title of the individuals carousels in the tabs are set in the
      // data-title attribute of the carousels. For single carousels the title
      // is not available here, but instead it's controlled by the configuration
      // on the panel pane. There are no panel hooks where we can get the title
      // and easily change the content tree to add event and URL-parameters to
      // elements (content is already rendered when hook is run).
      // Note that 'once' and 'context' is left out intentionally in the outer
      // most selector. This is because items in the carousel are lazy loaded
      // and we want to make sure the selector applies when new items is added.
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
          var wtkId = DING_WEBTREKK_PARAMETER_CAROUSEL_PREV;

          if ($(this).hasClass('slick-next')) {
            linkId = 'Karousel, click på næste knappen';
            wtkId = DING_WEBTREKK_PARAMETER_CAROUSEL_NEXT;
          }

          var eventData = {
            linkId: linkId,
            customClickParameter: {}
          };
          eventData.customClickParameter[wtkId] = carouselTitle;
          pushEvent('click', eventData);
        });
      });

      // Track loaded ding_campaign_plus campaigns.
      //
      // Sometimes campaigns are loaded asynchronously if they are not in cache.
      // In these cases we can't use page parameters, since we don't have the
      // required information at initial page load and we'll have to use an
      // event. To be consistent we track every campaign with event.
      $('.node-ding-campaign-plus', context) .once('js-ding-webtrekk', function() {
        var eventData = $(this).data('ding-webtrekk-event');
        // Sending a 'click'-event to webtrekk in this case may seem weird, but
        // currently our Webtrekk setup only supports this type of event. If our
        // setup is changed in the future it may be more appropriate to send
        // another type of event. The important thing now is that we get the
        // data to Webtrekk.
        pushEvent('click', eventData);
      });

      // Handling of covers on collection and object pages. Covers can come either on
      // page load or on ajax calls so we need to handle both cases. In order not to
      // send the same event multiple times we use global variable Drupal.dingWebtrekkCoverFound
      // to keep track of previously sent events.

      var sendCoverEvent = function (id) {
        if (!Drupal.dingWebtrekkCoverFound) {
          var eventData = {
            linkId: 'Materiale billede event',
            customClickParameter: {}
          };
          eventData.customClickParameter[DING_WEBTREKK_PARAMETER_COVER_PRESENT] = id;
          pushEvent('click', eventData);
          Drupal.dingWebtrekkCoverFound = true;
        }
      };

      $('.view-mode-collection-list .ting-cover, .view-mode-full .ting-cover', context)
        .has('img').once('js-ding-webtrekk', function () {
          var id = $(this).data('ting-cover-object-id');
          sendCoverEvent(id);
        });
      $('.view-mode-collection-list .ting-cover, .view-mode-full .ting-cover', context)
        .once('js-ding-webtrekk').on('DOMSubtreeModified', function () {
          if ($(this).has('img')) {
            var id = $(this).data('ting-cover-object-id');
            sendCoverEvent(id);
          }
          $(this).unbind('DOMSubtreeModified');
        });

      // This code fires multiple times. But we need to make sure that the cookies are removed after they are
      // set and on any change in consent.
      if ((typeof CookieInformation !== 'undefined' && CookieInformation !== null) &&
        (typeof wts !== 'undefined' && wts !== null)) {
        window.addEventListener("CookieInformationConsentGiven", function (event) {
          if (!CookieInformation.getConsentGivenFor("cookie_cat_statistic")) {
            wts.push(['removeIdentifierOptOut']);
          } else {
            wts.push(['setIdentifierOptOut']);
          }
        });
      }
    }
  };

})(jQuery);
