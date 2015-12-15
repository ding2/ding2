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

  var TingSearchCarousel = (function() {

    var cache = [];
    var carousel;
    var current_tab = 0;
    var navigation;

    /**
     * Private: Ensures that the tabs have the same size. This is purly a design
     * thing.
     */
    function _equale_tab_width() {
      // Get the list of tabs and the number of tabs in the list.
      var tabsList = $('.rs-carousel-list-tabs');
      var childCount = tabsList.children('li').length;

      // Only do somehting if there actually is tabs
      if (childCount > 0) {

        // Get the width of the <ul> list element.
        var parentWidth = tabsList.width();

        // Calculate the width of the <li>'s.
        var childWidth = Math.floor(parentWidth / childCount);

        // Calculate the last <li> width to combined childrens width it self not
        // included.
        var childWidthLast = parentWidth - ( childWidth * (childCount -1) );

        // Set the tabs css widths.
        tabsList.children().css({'width' : childWidth + 'px'});
        tabsList.children(':last-child').css({'width' : childWidthLast + 'px'});
      }
    }

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

      // Remove current content and show spinner.
      $('.rs-carousel-title').html('');
      $('.rs-carousel .rs-carousel-runner').children().remove();
      $('.rs-carousel-inner .ajax-loader').removeClass('element-hidden');

      // Hide navigation arrows.
      $('.rs-carousel-action-prev').hide();
      $('.rs-carousel-action-next').hide();

      current_tab = index;
      _update(current_tab);
    }

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
        // Add support for touch displays (requires jQuery Touch Punch).
        $('.rs-carousel-runner').draggable({
          axis: "x",
          stop: function() {
            var left = $('.rs-carousel-runner').position().left;

            // Left side reached.
            if (left > 0) {
              carousel.carousel('goToPage', 0);
            }

            // Right side reached.
            if ($('.rs-carousel-mask').width() - $('.rs-carousel-runner').width() > left) {
              var lastIndex = carousel.carousel('getNoOfPages') - 1;
              carousel.carousel('goToPage', lastIndex);
            }
          }
        });

        // Hide navigation arrows.
        $('.rs-carousel-action-prev').hide();
        $('.rs-carousel-action-next').hide();
      }
    }

    /**
     * Private: Start the tables and attach event handler for click and change
     * events.
     */
    function _init_tabs() {
      // Select navigation wrapper.
      navigation = $('.rs-carousel-tabs');

      // Sett equal with on the tab navigation menu.
      _equale_tab_width();

      // Attach click events to tabs.
      $('.rs-carousel-list-tabs').on("click", "li", (
        function(e) {
          e.preventDefault();
          _change_tab($(this).index());
          return false;
        }
      ));

      // Add change event to tabs.
      $('.rs-carousel-select-tabs').live('change', function() {
        _change_tab($(this).find(':selected').index());
      });
    }

    /**
     * Private: Updates the content when the user changes tabs. It will fetch
     * the content from the server if it's not fetched allready.
     */
    function _update(index) {
      // Get content from cache, if it have been fetched.
      if (!(index in cache)) {
        _fetch(index);

        // Return as the fetch will call update once more when the Ajax call
        // have completed.
        return;
      }

      var data = cache[index];

      // Remove spinner.
      $('.rs-carousel-inner .ajax-loader').addClass('element-hidden');

      // Update content.
      $('.rs-carousel-title').html(data.subtitle);
      $('.rs-carousel .rs-carousel-runner').append(data.content);

      // Show navigation arrows.
      $('.rs-carousel-action-prev').show();
      $('.rs-carousel-action-next').show();

      // Get the carousel running.
      carousel.carousel('refresh');
      carousel.carousel('goToPage', 0);
    }

    /**
     * Private: Makes an ajax call to the server to get new content for the
     * active navigation tab.
     */
    function _fetch(index) {
      $.ajax({
        type: 'get',
        url : Drupal.settings.basePath + 'ting_search_carousel/results/ajax/' + index,
        dataType : 'json',
        success : function(data) {
          cache[index] = {
            'subtitle' : data.subtitle,
            'content' : data.content
          };

          // If we still are on the same tab update it elese the content have
          // been saved to the cache.
          if (current_tab == data.index) {
            _update(index);
          }
        }
      });
    }

    /**
     * Public: Init the carousel and fetch content for the first tab.
     */
    function init() {
      // Select the carousel element.
      carousel = $('.rs-carousel-items');

      // Fix the tables and fetch the first tabs content.
      _init_tabs();

      // Start the carousel.
      carousel.carousel({
        noOfRows: 1,
        orientation: 'horizontal',
        itemsPerTransition: 'auto'
      });

      // Maybe add support for touch devices (will only be applied on touch
      // enabled devices).
      _add_touch_support();

      // Will get content for the first tab.
      _change_tab(0);
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
  $(document).ready(function() {
    TingSearchCarousel.init();
    $("div.rs-carousel-mask").on('click', 'li', function() {
      Drupal.TingSearchOverlay();
    });
  });
})(jQuery);
