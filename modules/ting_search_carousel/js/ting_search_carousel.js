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

  transitions.none = function() {
  };

  transitions.none.prototype.switchTo = function (to, element) {
    element.find('.carousel-tab:visible').hide();
    to.show();
  };

  transitions.fade = function() {
  };

  transitions.fade.prototype.switchTo = function (to, element) {
    // Freeze height so it wont collapse in the instant that both tabs
    // are invisible. Avoids odd scrolling.
    element.height(element.height());
    element.find('.carousel-tab:visible').fadeOut(200, function() {
      to.fadeIn(200);
      element.height('auto');
    });
  };

  transitions.crossFade = function() {
  };

  transitions.crossFade.prototype.init = function (element) {
    // Add a delay so things have time to find their size.
    window.setTimeout(function () {
      // Add a wrapper and set position/width height, so we can
      // cross-fade between carousels.
      element.find('.carousel-tab').wrapAll($('<div class=fade-container>'));
      var container = element.find('.fade-container');
      container.css('position', 'relative').height(container.height());
      container.find('.carousel-tab').css({
        'position': 'absolute',
        'width': '100%',
        'box-sizing': 'border-box'
      });
    });
  };

  transitions.crossFade.prototype.switchTo = function (to, element) {
    element.find('.carousel-tab').fadeOut(200);
    to.fadeIn(200);
  };

  /*
   * End of transition definitions.
   */

  /**
   * Object handling tabs.
   */
  var Tabset = function(tingCarousel, transition, beforeChange) {
    var self = this;
    this.tingCarousel = tingCarousel;
    this.beforeChange = beforeChange;
    this.transition = transition;
    this.element = $('<div>').addClass('carousel-tabs');
    this.tabs = $('<ul>');
    this.select = $('<select>');

    // Make basic tab structure.
    this.element.append(this.tabs).append(this.select);

    // Initialize transition.
    if (typeof this.transition.init === 'function') {
        this.transition.init(this.tingCarousel);
    }

    // Add event handler for changing tabs when clicked.
    this.tabs.on('click', 'li', function (e) {
      e.preventDefault();
      self.changeTab($(this).data('target'));
      return false;
    });

    // Add event handler for the select for mobile users.
    this.select.on('change', function() {
        self.changeTab($(this).find(':selected').data('target'));
    });

    /**
     * Add a tab.
     */
    this.addTab = function(title, element) {
      // Without the href, the styling suffers.
      var tab = $('<li>').append($('<a>').text(title).attr('href', '#')).data('target', element);
      element.data('tabset-tab', tab);
      this.tabs.append(tab);
      var option = $('<option>').text(title).data('target', element);
      element.data('tabset-option', option);
      this.select.append(option);
    };

    /**
     * Change tab.
     */
    this.changeTab = function(target) {
      // De-activate current tab.
      this.tabs.find('.active').removeClass('active');
      this.select.find(':selected').removeAttr('selected');

      if (typeof this.beforeChange === 'function') {
        this.beforeChange(target, this.tingCarousel);
      }
      this.transition.switchTo(target, this.tingCarousel);

      // Activate the current tab.
      $(target).data('tabset-tab').addClass('active');
      $(target).data('tabset-option').attr('selected', true);
    };

    /**
     * Make tabs equal width.
     *
     * @todo This might be done with CSS these days.
     */
    this.equalizeTabWith = function () {
      // Get the list of tabs and the number of tabs in the list.
      var childCount = this.tabs.children('li').length;

      // Only do somehting if there actually is tabs.
      if (childCount > 0) {

        // Get the width of the <ul> list element.
        var parentWidth = this.tabs.width();

        // Calculate the width of the <li>'s.
        var childWidth = Math.floor(parentWidth / childCount);

        // Calculate the last <li> width to combined childrens width it self not
        // included.
        var childWidthLast = parentWidth - (childWidth * (childCount - 1));

        // Set the tabs css widths.
        this.tabs.children().css({'width' : childWidth + 'px'});
        this.tabs.children(':last-child').css({'width' : childWidthLast + 'px'});
      }
    };

    /**
     * Insert the tabs into the page.
     */
    this.insert = function(element) {
      $(element).after(this.element);

      // Make the tabs equal size.
      this.equalizeTabWith();
      var self = this;
      // Resize the tabs if the window size changes.
      $(window).bind('resize', function () {
        self.equalizeTabWith();
      });

      // Activate the first tab.
      var target = this.tabs.find('li:first-child').data('target');
      $(target).data('tabset-tab').addClass('active');
      $(target).data('tabset-option').attr('selected', true);
    };
  };

  var queue = [];
  var running = false;

  /**
   * Fetches more covers.
   *
   * Runs the queue if not already running.
   */
  var update = function() {
    if (running || queue.length < 1) {
      return;
    }
    running = true;
    var item = queue.shift();

    $.ajax({
      type: 'get',
      url : Drupal.settings.basePath + item.tab.data('path') + '/' + item.tab.data('offset'),
      dataType : 'json',
      success : function(data) {
        // Remove placeholders.
        item.target.find('.carousel-item.placeholder').remove();
        item.target.slick('slickAdd', data.content);
        item.tab.data('updating', false);
        // Carry on processing the queue.
        running = false;
        update();
      }
    });
  };

  /**
   * Event handler for progressively loading more covers.
   */
  var update_handler = function(e, slick) {
    var tab = e.data;
    if (!tab.data('updating')) {
      // If its the first batch or we're near the end.
      if (tab.data('offset') === 0 ||
           (tab.data('offset') > -1 &&
            (slick.slideCount - slick.currentSlide) <
            (slick.options.slidesToShow * 2))) {
        // Disable updates while updating.
        tab.data('updating', true);
        // Add to queue.
        queue.push({'tab': tab, 'slick': slick, 'target': $(e.target)});
      }
    }
    // Run queue.
    update();
  };

  /**
   * Start the carousel when the document is ready.
   */
  Drupal.behaviors.ting_search_carousel = {
    attach: function (context) {

      $('.ting-search-carousel', context).once('ting-search-carousel', function() {

        var transition;
        if (typeof $(this).data('transition') === 'string' &&
            typeof Drupal.tingSearchCarouselTransitions[$(this).data('transition')] === 'function') {
          transition = new Drupal.tingSearchCarouselTransitions[$(this).data('transition')]();
        }
        else {
          transition = new Drupal.tingSearchCarouselTransitions.fade();
        }

        var settings = {};
        if (typeof $(this).data('settings') === 'object') {
          settings = $(this).data('settings');
        }

        $('.carousel-tab', this).each(function () {
          var tab = $(this);
          // Reset ul to 100% width before we start Slick. See the CSS.
          tab.find('ul').css('width', '100%');
          // Init carousels. In order to react to the init event, the
          // event handler needs to be defined before triggering Slick
          // (obviously in hindsight).
          $('.carousel', this).on('init reInit afterChange', tab, update_handler)
            .slick(settings);
        });

        // Add tabs.
        var tabs = new Tabset($(this), transition, function (tab) {
          if (tab.hasClass('additional-tab')) {
            // Silck cannot find the proper width when the parent is hidden, so
            // show the tab, reinit slick and immediately hide it again, before
            // running the real transition.
            tab.show();
            $('.slick-slider', tab).slick('reinit');
            tab.hide();
          }
        });
        $('.carousel-tab', this).each(function () {
          tabs.addTab($(this).data('title'), $(this));
        });
        tabs.insert($(this));
      });
    }

  };

})(jQuery);
