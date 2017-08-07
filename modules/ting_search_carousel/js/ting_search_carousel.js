/**
 * @file
 * Handles the carousels loading of content and changes between tabs.
 *
 * There are two selectors to change tabs based on breaks points
 * (which is handle by the theme).
 *
 * For large screens the normal tab list (ul -> li) is used while on small
 * screens (mobile/tables) a select dropdown is used.
 */

(function ($) {
  "use strict";

  Drupal.tingSearchCarouselTransitions = Drupal.tingSearchCarouselTransitions || {};

  /*
   * Transition definitions.
   */

  // Shorthand for the following code.
  var transitions = Drupal.tingSearchCarouselTransitions;

  transitions.none = function() {};

  transitions.none.prototype.switchTo = function (to, element) {
    element.find('.rs-carousel-inner:visible').hide();
    to.show();
  };

  transitions.fade = function() {};

  transitions.fade.prototype.switchTo = function (to, element) {
    // Freeze height so it wont collapse in the instant that both tabs
    // are invisible. Avoids odd scrolling.
    element.height(element.height());
    element.find('.rs-carousel-inner:visible').fadeOut(200, function() {
      to.fadeIn(200);
      element.height('auto');
    });
  };

  transitions.crossFade = function() {};

  transitions.crossFade.prototype.init = function (element) {
    // Add a delay so things have time to find their size.
    window.setTimeout(function () {
      // Add a wrapper and set position/width height, so we can
      // cross-fade between carousels.
      element.find('.rs-carousel-inner').wrapAll($('<div class=fade-container>'));
      var container = element.find('.fade-container');
      container.css('position', 'relative').height(container.height());
      container.find('.rs-carousel-inner').css({
        'position': 'absolute',
        'width': '100%',
        'box-sizing': 'border-box'
      });
    });
  };

  transitions.crossFade.prototype.switchTo = function (to, element) {
    element.find('.rs-carousel-inner').fadeOut(200);
    to.fadeIn(200);
  };

  /*
   * End of transition definitions.
   */

  Drupal.theme.tingSearchCarousel = function(subtitle, content) {
    var carousel = $("<div>").addClass('rs-carousel-inner');
    if (Drupal.settings.ting_search_carousel.show_description) {
      carousel.append($('<div>').addClass('rs-carousel-title').text(subtitle));
    }
    carousel.append($('<div>').addClass('rs-carousel-items').append($('<ul>').append(content)));
    return carousel;
  };

  Drupal.theme.tingSearchCarouselTabs = function(tab_defs) {
    if (tab_defs.length < 1) {
      return "";
    }
    var tabs = $('<ul>').addClass('rs-carousel-list-tabs');
    var select = $('<select>').addClass('rs-carousel-select-tabs');
    $.each(tab_defs, function (index, tab) {
      // Without the href, the styling suffers.
      tabs.append($("<li>").addClass('rs-carousel-item').append($('<a>').text(tab.title).attr('href', '#')));
      select.append($('<option>').addClass('rs-carousel-item').text(tab.title));
    });

    return $('<div>').addClass('rs-carousel-tabs').append(tabs).append(select);
  };

  Drupal.TingSearchCarousel = (function() {

    // Root element that contains both carousels and navigation.
    var element;
    // Tab definition.
    var tabs;
    // Transition for this carousel.
    var transition;
    // Tabs and mobile select for switching carousels.
    var navigation;

    /**
     * Private: Handler activated when the user changes tab.
     */
    function _change_tab(index) {
      // Remove navigation selection.
      navigation.find('.active').removeClass('active');
      navigation.find(':selected').removeAttr('selected');

      // Add new navigation seletions.
      $(navigation.find('li')[index]).addClass('active');
      $(navigation.find('option')[index]).attr('selected', true);

      transition.switchTo(tabs[index].wrapper, element);

      // Refresh carousel so it knows how many items are visible and
      // can scroll accordingly.
      tabs[index].carousel.carousel('refresh');

      _update(index);
    }

    /**
     * Private: Check is the device have support for touch events.
     */
    function _is_touch_device() {
      // First part work in most browser the last in IE 10.
      return !!('ontouchstart' in window) || !!('onmsgesturechange' in window);
    }

    /**
     * Private: Enable draggable touch support to the carousel.
     *
     * But only if the device is touch enabled.
     */
    function _add_touch_support() {
      if (_is_touch_device()) {
        $.each(tabs, function (index, tab) {
          // Add support for touch displays (requires jQuery Touch Punch).
          $('.rs-carousel-runner', tab.wrapper).draggable({
            axis: "x",
            stop: function() {
              var left = $('.rs-carousel-runner', tab.wrapper).position().left;

              // Left side reached.
              if (left > 0) {
                tab.carousel.carousel('goToPage', 0);
              }

              // Right side reached.
              if ($('.rs-carousel-mask', tab.wrapper).width() - $('.rs-carousel-runner', tab.wrapper).width() > left) {
                var lastIndex = tab.carousel.carousel('getNoOfPages') - 1;
                tab.carousel.carousel('goToPage', lastIndex);
              }
            }
          });
        });
      }
    }

    /**
     * Private: Create tabs and attach events.
     */
    function _init_tabs() {
      if (tabs.length < 2 && !tabs[0].title) {
        return;
      }
      // Create tabs.
      navigation = Drupal.theme.tingSearchCarouselTabs(tabs);

      // Attach click events to tabs.
      navigation.find('.rs-carousel-list-tabs').on("click", "li", function(e) {
        e.preventDefault();
        _change_tab($(this).index());
        return false;
      });

      // Add change event to selector.
      navigation.find('.rs-carousel-select-tabs').on('change', function() {
        _change_tab($(this).find(':selected').index());
      });

      element.find('.rs-carousel').append(navigation);

      // Highlight the default tab.
      $(navigation.find('li')[0]).addClass('active');
      $(navigation.find('option')[0]).attr('selected', true);

    }

    /**
     * Private: Create the carousels.
     */
    function _init_carousels() {
      var first_carousel = element.find('.rs-carousel-inner');
      $.each(tabs, function (index, tab) {
        var carousel;
        // Skip first, it was supplied by the server.
        if (index !== 0) {
          carousel = Drupal.theme.tingSearchCarousel(tab.subtitle, tab.content).hide();
          delete tab.content;
          first_carousel.after(carousel);
        }
        else {
          carousel = first_carousel;
          // Add in extra content.
          if (tab.content) {
            carousel.find('ul').append(tab.content);
          }
        }

        tabs[index].wrapper = carousel;
        tabs[index].carousel = carousel.find('.rs-carousel-items');

        var updateData = function () {
          // Update if there's still data to be fetched and we're near
          // the end of the carousel.
          if (tabs[index].offset >= 0) {
            if ($(this).carousel('getIndex') >
                ($(this).carousel('getNoOfPages') - 3)) {
              _update(index);
            }
          }
        };

        tabs[index].carousel.carousel({
          noOfRows: 1,
          orientation: 'horizontal',
          itemsPerTransition: 'auto',
          create: updateData,
          after: updateData,
        });
      });
    }

    /**
     * Private: Fetch content for carousels.
     */
    function _fetch(index, offset, callback) {
      $.ajax({
        type: 'get',
        url : Drupal.settings.basePath + tabs[index].path + '/' + offset,
        dataType : 'json',
        success : function(data) {
          callback(data);
        }
      });
    }

    /**
     * Private: Updates the content when the user changes tabs.
     *
     * It will fetch the content from the server if it's not fetched
     * allready.
     */
    function _update(index) {
      var offset = tabs[index].offset;
      // Either there's no more data to be fetched, or we're already
      // fetching. Skip.
      if (offset < 0) {
        return;
      }
      // Disable updates while updating.
      tabs[index].offset = -1;
      _fetch(index, offset, function (data) {
        var content = $(data.content);
        Drupal.attachBehaviors(content);

        tabs[index].offset = data.offset;
        tabs[index].wrapper.find('.rs-title').append(data.subtitle);
        tabs[index].carousel.find('.rs-carousel-runner').append(content);
        tabs[index].carousel.carousel('refresh');
      });
    }

    /**
     * Public: Init the carousel and fetch content for the first tab.
     */
    function init(id, settings) {
      element = $('#' + id);
      if (element.hasClass('ting_search_carousel_inited')) {
        return;
      }
      element.addClass('ting_search_carousel_inited');

      tabs = settings.tabs;

      // Initialize tabs.
      _init_tabs();

      // Start the carousels.
      _init_carousels();

      if (typeof settings.transition === 'string' &&
          typeof Drupal.tingSearchCarouselTransitions[settings.transition] === 'function') {
        transition = new Drupal.tingSearchCarouselTransitions[settings.transition]();
      }
      else {
        transition = new Drupal.tingSearchCarouselTransitions.fade();
      }

      if (typeof transition.init === 'function') {
        transition.init(element);
      }

      // Maybe add support for touch devices (will only be applied on touch
      // enabled devices).
      _add_touch_support();
    }

    /**
     * Expoes public functions.
     */
    return {
        name: 'ting_search_carousel',
        init: init
    };
  })();

  /**
   * Start the carousel when the document is ready.
   */
  Drupal.behaviors.ting_search_carousel = {
    attach: function (context, settings) {
      $.each(settings.ting_search_carousel.carousels, function (id, carousel_settings) {
        Drupal.TingSearchCarousel.init(id, carousel_settings);
      });
    }
  };

})(jQuery);
