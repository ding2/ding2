(function ($) {
  'use strict';

  /**
   * Facebook block position.
   */
  Drupal.behaviors.facebookSharePosition = {
    attach: function (context) {
      var fb = $('.block-facebookshare', context);

      if (fb.length !== 0) {
        fb.prependTo($('.layout-wrapper', context));
      }
    }
  };

  /**
   * Toggle opening hours.
   */
  function toggleOpeningHours() {
    // Create toggle link
    $('<a />', {
      'class' : 'opening-hours-toggle js-opening-hours-toggle js-collapsed',
      'href' : Drupal.t('#toggle-opening-hours'),
      'text' : Drupal.t('Opening hours')
    }).insertBefore('.js-opening-hours-toggle-element');

    // Set variables
    var element = $('.js-opening-hours-toggle');
    var siteHeader = $('.site-header');
    var scrollOffset = 0;
    var scrollToTarget;

    // Attach click
    element.on('click touchstart', function (event) {
      // Store clicked element for later use
      var element = this;

      // Toggle
      $(this).next('.js-opening-hours-toggle-element').slideToggle('fast', function () {
        // Toggle class
        $(element).toggleClass('js-collapsed js-expanded');

        // Set scroll offset
        if ($('.site-header.js-fixed').length) {
          // If the site header is fixed use the height
          scrollOffset = $(siteHeader).height();
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

  /**
   * Autofocus inputs.
   */
  function autofocusInputs() {
    // Search button click
    $('.topbar-link-search').click(function() {
      var input = $('input[name="search_block_form"]');
      if ($(this).is('.active')) {
        input.focus();
      }
    });

    // Login button click
    $('.topbar-link-user').click(function() {
      var input = $('input[name="name"]');
      if ($(this).is('.active')) {
        input.focus();
      }
    });
  }

  /**
   * Hide listed empty elements.
   */
  function hideElement() {
    var selectors = [
      '.layout-wrapper'
    ];

    for (var i = selectors.length - 1; i >= 0; i--) {
      var $el = $(selectors[i]);

      if($.trim($el.html()) === '') {
        $el.hide();
      }
    }
  }

  /**
   * Sets sarousel image as background.
   */
  function setCarouselBg() {
    $('.ding_nodelist-carousel img, .ding_nodelist-single img').each( function() {
      var imageSrc = $(this).attr("src");
      var bgItem = $(this).parent();
      bgItem.css('background-image', 'url(' + imageSrc + ')');
    });
  }

  // When ready start the magic.
  $(document).ready(function() {
    // Autofocus inputs
    autofocusInputs();

    // Carousel bg
    setCarouselBg();

    // Hide empty elements
    hideElement();

    // Toggle opening hours.
    toggleOpeningHours();

    // Expand block when accesed from "Opening hours" widget.
    var hash = window.location.hash;
    if (hash == '#toggle-opening-hours') {
      var element = $('a.js-opening-hours-toggle');
      if (!$(element).hasClass('js-expanded')) {
        $(element).toggleClass('js-collapsed js-expanded');
        $('.js-opening-hours-toggle-element').css('display','block');
      };
    };

    // Toggle footer menu.
    $('.footer .pane-title').on('click', function() {
      var element = $(this).parent();
      $('.menu', element).toggle();
      $(this).toggleClass('js-toggled');
    });

    // Check an organic group and library content.
    // If a group does not contain both news and events
    // then add an additional class to the content lists.
    [
      '.ding-group-news,.ding-group-events',
      '.ding-library-news,.ding-library-events'
    ].forEach(function(e) {
        var selector = e;
        $(selector).each(function() {
          if ($(this).parent().find(selector).size() < 2) {
            $(this).addClass('js-og-single-content-type');
          }
      });
    });

    $('.layout-wrapper').each(function() {
      if ($(this).children().length == 0) {
        $(this).css('display', 'none');
      }
    });
  });
})(jQuery);
