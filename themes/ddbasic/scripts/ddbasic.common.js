/*jshint forin:false, jquery:true, browser:true, indent:2, trailing:true, unused:false */
(function($) {
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
   * Toggle opening hours
   */
  function toggle_opening_hours() {
    var hasOpeningHours = Drupal.settings.hasOwnProperty('ding_ddbasic_opening_hours');

    // Create toggle link
    $('.js-opening-hours-toggle-element').each(function () {
      var
        $this = $(this),
        text = [];

      if ($this.attr('data-extended-title')) {
        $('th', this).slice(1).each(function () {
          text.push($(this).text());
        });
      } else {
        text.push(Drupal.t('Opening hours'));
      }

      if (hasOpeningHours && Drupal.settings.ding_ddbasic_opening_hours.hasOwnProperty('expand_all_libraries')) {
        // Expand all opening hours on library pages
        $('<a />', {
          'class' : 'opening-hours-toggle js-opening-hours-toggle js-collapsed js-expanded collapsed',
          'href' : Drupal.t('#toggle-opening-hours'),
          'text' : text.join(', ')
        }).insertBefore(this);
      } else {
        // Collapse all opening hours on library pages
        $('<a />', {
          'class' : 'opening-hours-toggle js-opening-hours-toggle js-collapsed collapsed',
          'href' : Drupal.t('#toggle-opening-hours'),
          'text' : text.join(', ')
        }).insertBefore(this);
      }
    });

    // Set variables
    var element = $('.js-opening-hours-toggle');
    var siteHeader = $('.site-header');

    // Attach click
    element.on('click touchstart', function(event) {
      // Store clicked element for later use
      var element = this;

      // Toggle
      $(this).next('.js-opening-hours-toggle-element').slideToggle('fast', function() {
        // Toggle class
        $(element)
          .toggleClass('js-collapsed js-expanded collapsed')

          // Remove focus from link
          .blur();
      });

      // Prevent default (href)
      event.preventDefault();
    });

    // Expand opening hours on first library on library pages.
    if (hasOpeningHours && Drupal.settings.ding_ddbasic_opening_hours.hasOwnProperty('expand_on_first_library')) {
      element.triggerHandler('click');
    }
  }

  /**
   * Autofocus inputs.
   */
  function autofocusInputs() {
    // Set autofocus on page load (instead of autofocus attr)
    if (!/iPad|iPhone|iPod/g.test(navigator.userAgent)) {
      $('.search-form-extended input[name="search_block_form"]').focus();
    }

    // Search button click
    $('.search-form-extended .search-extended-button').click(function() {
      var input = $('input[name="search_block_form"]');
      input.focus();
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
  $(document).ready(function () {
    // Autofocus inputs
    autofocusInputs();

    // Carousel bg
    setCarouselBg();

    // Hide empty elements
    hideElement();

    // Toggle opening hours.
    toggle_opening_hours();

    // Expand block when accesed from "Opening hours" widget.
    var hash = window.location.hash;
    if (hash == '#toggle-opening-hours') {
      var element = $('a.js-opening-hours-toggle');
      if (!$(element).hasClass('js-expanded')) {
        $(element).toggleClass('js-collapsed js-expanded');
        $('.js-opening-hours-toggle-element').css('display','block');
      };
    };

    // Check an organic group and library content.
    // If a group does not contain both news and events
    // then add an additional class to the content lists.
    [
      '.ding-group-news,.ding-group-events',
      '.ding-library-news,.ding-library-events'
    ].forEach(function(e) {
        var selector = e;
        $(selector).each(function() {
          if ($(this).parent().find(selector).length < 2) {
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

  // Submenus
  Drupal.behaviors.ding_submenu = {
    attach: function(context, settings) {

      $('.sub-menu-title', context).unbind().click(function(evt) {
        if ($('.is-tablet').is(':visible')) {
          evt.preventDefault();
          $(this).parent().find('ul').slideToggle("fast");
        }
      });
    }
  };

  /**
   * Make clicks on anchor links to stop on correct position.
   */
  Drupal.behaviors.findTopForAnchor = {
    attach: function (context, settings) {
      var offset = $('#page')[0].offsetTop;
      var queryString = window.location.hash;

      function scrollToAnchor(anchorId) {
        var target, anchorObject = $(anchorId);
        if (anchorObject.length !== 0) {
          target = anchorObject.offset().top - offset - 61;
        }
        else {
          return false;
        }

        $('html, body').animate({scrollTop: target}, 'fast', function () {
          window.location.hash = anchorId;
        });
      }

      if (queryString !== "") {
        scrollToAnchor(queryString);
      }

      $('article a[href^="#"]').click(function (event) {
        event.preventDefault();
        var anchorId = $(this).attr('href');
        scrollToAnchor(anchorId);
        return false;
      });
    }
  };

})(jQuery);
