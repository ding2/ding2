/**
 * @file
 * Enables the tabs to change automatically and add handler to capture click
 * events on the tabs.
 */
(function ($) {
  'use strict';

  Drupal.behaviors.ding_tabroll = {
    attach: function (context) {
      var tabroll = $('.ding-tabroll', context);
      var tabroll_select = $('.ding-tabroll-select-tabs', context);
      var switch_speed = Drupal.settings.ding_tabroll.switch_speed;

      // Hack to check if tab have been tab_selected, as unbind event will not work.
      var tab_selected = false;

      // Check if the tabs lib is loaded before trying to call it.
      if ($.fn.tabs) {
        tabroll.tabs({
          select: function(event, ui) {
            // Update the mobile navigation drop down.
            tabroll_select.prop('selectedIndex', ui.index);
          },
          // The jQuery UI tabs adds a negative tabindex on the tab anchors
          // which we are not interested in having.
          // We'll remove them when the tab is created.
          create: function() {
            var tab_anchors = $('.ui-tabs-anchor', context);

            $(tab_anchors).each(function() {
              $(this).removeAttr('tabindex');
            });
          }
        }).tabs('rotate', switch_speed);

        // Stop tabs rotate when mouse is over the tab roll.
        tabroll.mouseenter(function() {
          tabroll.tabs('rotate', 0);
        });

        // Start tabs rotate when mouse is out.
        tabroll.mouseleave(function () {
          tabroll.tabs().tabs('rotate', switch_speed);
        });

        // Stops tabs rotation when an element within it is in focus.
        tabroll.find(':focusable').focusout(function () {
          tabroll.tabs().tabs('rotate', switch_speed);
        });

        // Starts tabs rotation when an element within it is out of focus.
        tabroll.find(':focusable').focusin(function () {
          tabroll.tabs('rotate', 0);
        });
      }

      // Add click event to select tabs options.
      $('.ui-tabs-nav-item a', tabroll).click(function(e) {
        e.preventDefault();
        tabroll.tabs().tabs('rotate', 0);
        tab_selected = true;
        return false;
      });

      // Hook into click events in the responsive mobile selector.
      tabroll_select.on('change', function() {
        tabroll.tabs('select', $(this).prop('selectedIndex'));
        tabroll.tabs().tabs('rotate', 0);
        tab_selected = true;
      });
    }
  };

})(jQuery);
