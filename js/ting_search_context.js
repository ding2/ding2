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
          'search_context' : Drupal.settings.ting_search_context
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
     * .
     */
    function _set_element() {
      var position = Drupal.settings.ting_search_context_position;

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
      var position = Drupal.settings.ting_search_context_position;

      var config = carousel_configs.find(position);
      carousel.carousel('option', config);
    }

    /**
     * Private: Updates the carousel after content has been fetched.
     */
    function _update() {
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
     * Public: Init the carousel and fetch content.
     */
    function init() {

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

      pane.show();



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
        init: init
    };
  })();

  /**
   * Start the carousel when the document is ready.
   */
  $(document).ready(function() {
    TingSearchContext.init();
  });
})(jQuery);
