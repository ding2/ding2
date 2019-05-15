/*jshint forin:false, jquery:true, browser:true, indent:2, trailing:true, unused:false */
(function($) {
  'use strict';

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

  // When ready start the magic.
  $(document).ready(function () {
    // Toggle opening hours.
    toggle_opening_hours();

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
  });

  // Submenus
  Drupal.behaviors.ding_submenu = {
    attach: function(context, settings) {

      $('.sub-menu-title', context).click(function(evt) {
        if ($('.is-tablet').is(':visible')) {
          evt.preventDefault();
          $(this).parent().find('ul').slideToggle("fast");
        }
      });
    }
  };

  // Nodelist "Promoted Nodes".
  Drupal.behaviors.ding_nodelist_promoted_nodes = {
    attach: function (context, settings) {
      // "Promoted nodes" items classes list.
      var classes = ['first-left-block', 'first-right-block', 'last-left-block', 'last-right-block'];
      classes.forEach(function (value) {
        // Getting item wrapper.
        var itemWrapper = $('.' + value);
        // Extracting item's url from wrapper.
        var href = itemWrapper.data('href');
        itemWrapper.on('mouseover click', function (event) {
          // Always display pointer cursor.
          itemWrapper.css('cursor', 'pointer');
          // Act as a click on link when "click" event is executed.
          if (event.type === 'click') {
            window.location.href = href;
          }
        });
      });
    }
  };

})(jQuery);
