/*jshint forin:false, jquery:true, browser:true, indent:2, trailing:true, unused:false */
(function($) {
  'use strict';

  /**
   * Toggle opening hours
   */
  function toggle_opening_hours() {
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

      $('<a />', {
        'class' : 'opening-hours-toggle js-opening-hours-toggle js-collapsed collapsed',
        'href' : Drupal.t('#toggle-opening-hours'),
        'text' : text.join(', ')
      }).insertBefore(this);
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

    // Expand opening hours on library pages.
    if (Drupal.settings.ding_ddbasic_opening_hours && Drupal.settings.ding_ddbasic_opening_hours.expand_on_library) {
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
          if ($(this).parent().find(selector).size() < 2) {
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

})(jQuery);
