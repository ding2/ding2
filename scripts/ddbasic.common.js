(function($) {

  /*
   * Toggle opening hours
   */
  function toggle_opening_hours() {
    // Create toggle link
    $('<a />', {
      'class' : 'opening-hours-toggle js-opening-hours-toggle js-collapsed',
      'href' : Drupal.t('#toggle-opening-hours'),
      'text' : Drupal.t('Opening hours')
    }).insertBefore('.js-opening-hours-toggle-element');

    // Set variables
    var element = $('.js-opening-hours-toggle');
    var siteHeader = $('.site-header');
    var scrollOffset;
    var scrollToTarget;

    // Attach click
    element.on('click touchstart', function(event) {
      // Store clicked element for later use
      var element = this;

      // Toggle
      $(this).next('.js-opening-hours-toggle-element').slideToggle('fast', function() {
        // Toggle class
        $(element).toggleClass('js-collapsed js-expanded');

        // Set scroll offset
        if ($('.site-header.js-fixed').length) {
          // If the site header is fixed use the height
          scrollOffset = $(siteHeader).height();
        } else {
          // Else the window is scrolled to the top and we have to multiply the
          // height by 2 because it get's position fixed
          scrollOffset = $(siteHeader).height()*2;
        }

        // Scroll to the top of the element
        if ($(element).parents('.js-library-opening-hours-target').length) {
          // If there is a wrapper element with the target class
          scrollToTarget = $(element).parents('.js-library-opening-hours-target');
        } else {
          // Else let's scroll to the element clicked
          scrollToTarget = $(element);
        }

        $.scrollTo(scrollToTarget, 500, {
          offset: -scrollOffset,
          axis: 'y'
        });

        // Remove focus from link
        $(element).blur();
      });

      // Prevent default (href)
      event.preventDefault();
    });
  }

  // This is not the best solution, but it was decided to make a quick solution
  function facet_browser_mobile() {
    // Create toogle link
    $('<a />', {
      'class' : 'facet-browser-toggle js-facet-browser-hide',
      'href' : Drupal.t('#toggle-facet-browser'),
      'text' : Drupal.t('Show search filters')
    }).prependTo('.primary-content');

    // Define vars
    var facet_browser = $('.pane-ding-facetbrowser');

    // Move and show filters on click
    $('.facet-browser-toggle').on('click touchstart', function() {
      // Clone facet browser
      if (!$('.facet-browser-responsive').length) {
        // Clone facets
        facet_browser
          .clone()
          .insertAfter(this)
          .removeAttr('class')
          .addClass('facet-browser-responsive');
      }

      var facet_browser_clone = $('.facet-browser-responsive');

      if (facet_browser_clone.hasClass('js-facet-browser-visible')) {
        facet_browser_clone.hide();

        facet_browser_clone.toggleClass('js-facet-browser-visible');
      } else {
        facet_browser_clone.show();

        facet_browser_clone.addClass('js-facet-browser-visible');
      }

      // Add toggle to legend
      $('.fieldset-legend', facet_browser_clone).on('click touchstart', function() {
        if ($(this).hasClass('js-facet-browser-legend-visible')) {
          $(this)
            .parent()
            .siblings('.fieldset-wrapper')
            .hide();

          $(this).toggleClass('js-facet-browser-legend-visible');
        } else {
          $(this)
            .parent()
            .next()
            .show();

          $(this).addClass('js-facet-browser-legend-visible');
        }
      });
    });
  }

  // When ready start the magic
  $(document).ready(function () {
    // Toggle opening hours
    toggle_opening_hours();

    // Toggle footer menu
    $('.footer .pane-title').on('click', function() {
      var element = $(this).parent();
      $('.menu', element).toggle();
      $(this).toggleClass('js-toggled');
    });

    // Responsive facet browser
    facet_browser_mobile();
  });

})(jQuery);