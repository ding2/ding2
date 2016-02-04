/**
 * @file
 * Handles the carousels loading of content. The carousel can be loaded in three
 * different locations on the search page. A Drupal.settings variable indicates
 * the desired location.
 * two selectors to change tabs based on breaks points (which is handle by the
 * theme).
 *
 * For large screens the normal tab list (ul -> li) is used while on small
 * screens (mobile/tables) a select dropdown is used.
 *
 */
(function ($) {
  "use strict";

  var TingSearchContext = (function() {

    var carousel = null;
    var content;
    var pane;
    var position;


    /**
     * Object to store and apply selector-specific carousel-configurations.
     */
    var carousel_configs = {
      configs: [],

      add: function (selector, config) {
        this.configs.push([selector, config]);
      },

      find: function (selector) {
        var val;
        $.each(this.configs, function (index, value) {
          if (value[0] === selector) {
            val = value[1];
          }
        });
        return val;
      },
      clear: function () {
        this.configs = [];
      }
    };

    /**
     * Object to detect and store the current css breakpoint.
     */
    var breakpoint = {
      val: "",

      refresh_value: function () {
        this.val = this.get_current();
      },

      is_small_medium_large: function () {
        return this.val === "<940px";
      },
      has_changed: function () {
        return this.val !== this.get_current();

      },
      get_current: function () {

        var mql = window.matchMedia("screen and (min-width: 940px)");
        if (mql.matches){ // if media query matches
          return ">=940px";
        }
        else {
          return "<940px";
        }
      }
    };




    /**
     * Private: Makes an ajax call to the server to get new content for the
     * carousel. The search context is send along with the ajax request.
     */
    function _fetch() {
      $.ajax({
        type: 'post',
        url : Drupal.settings.basePath + 'ting/ting_search_context/content/ajax',
        dataType : 'json',
        data: {
          'context_id' : Drupal.settings.ting_search_context_id
        },
        success : function(data) {
          content = data;
          // Update the carousel.
          _update();
        }
      });
    }

    /**
     * Private: Sets the carousel element based on position-variable in Drupal.settings.
     * If viewport below 940px, the position-variable is ignored
     * and position is set to js-below-search-result.
     */
    function _set_element() {

      position = Drupal.settings.ting_search_context_position;

      // On small screens display below search results
      if (breakpoint.is_small_medium_large()) {
        position = 'js-below-search-result';
      }

      $('.pane-search-context').each(function(index) {

        if ($(this).hasClass(position)) {
          pane = $(this);
          carousel = $(this).find('.rs-carousel-items');
        }
      });
    }

    /**
     * Private: Sets position-specific options for the carousel.
     *
     */
    function _update_options() {

      var config = carousel_configs.find(position);
      carousel.carousel('option', config);
    }

    /**
     * Private: Updates the carousel after content has been fetched.
     */
    function _update() {
      // Reveal carousel if there is any content to display
      if(content.length > 0) {
        pane.show();
      }

      // Remove spinner.
      $('.rs-carousel-inner .ajax-loader').addClass('element-hidden');

      // Update content.
      $('.rs-carousel .rs-carousel-runner').html(content);

      // Show navigation arrows.
      $('.rs-carousel-action-prev').show();
      $('.rs-carousel-action-next').show();

      // Get the carousel running.
      carousel.carousel('refresh');
      carousel.carousel('goToPage', 0);
    }

    /**
     * Private: Destroys the carousel and clears variables.
     */
    function _destroy() {
      // Remove spinner.
      $('.rs-carousel-inner .ajax-loader').addClass('element-hidden');

      // Update content.
      $('.rs-carousel .rs-carousel-runner').append(content);

      // Show navigation arrows.
      $('.rs-carousel-action-prev').show();
      $('.rs-carousel-action-next').show();

      // Get the carousel running.
      carousel.carousel('refresh');
      carousel.carousel('goToPage', 0);
    }



    /**
     * Public: Reposition the carousel when the window is resized
     * in a way that changes the breakpoint. In viewports below 940px
     * the carousel is moved below search results.
     */
    function reposition() {
      // If breakpoint has changed destroy the carousel
      if (breakpoint.has_changed) {
        pane.hide();
        carousel.carousel('destroy');
        carousel_configs.clear();
      }

      // Reload the carousel
      init();
    }


    /**
     * Public: Init the carousel and fetch content.
     */
    function init() {

      // Detect the viewport
      breakpoint.refresh_value();

      // Initialize carousel configurations pr. position
      carousel_configs.add('js-above-search-result', {
        orientation: 'horizontal'
      });
      carousel_configs.add('js-below-search-result', {
        orientation: 'horizontal'
      });
      carousel_configs.add('js-below-facets', {
        orientation: 'vertical'
      });

      // Pick and set the carousel element.
      _set_element();

      // Exit if no carousel element is selected.
      if(carousel === null) {
        return;
      }





      // Start the carousel.
      carousel.carousel({
        noOfRows: 1,
        orientation: 'horizontal',
        itemsPerTransition: 'auto'
      });

      // Update postion-specifik carousel options
      _update_options();



      // Fetch content for the carousel.
      _fetch();




    }

    /**
     * Expoes public functions.
     */
    return {
        name: 'ting_search_context',
        init: init,
        reposition: reposition
      };
  })();

  /**
   * Start the carousel when the document is ready.
   */
  $(document).ready(function() {
    TingSearchContext.init();
  });

  /**
   * Reposition the carousel when the window is resized or rotated.
   */
  $(window).resize(function() {
    TingSearchContext.reposition();
  });

  // Listen for orientation changes
  window.addEventListener("orientationchange", function() {
    TingSearchContext.reposition();
  }, false);
})(jQuery);
