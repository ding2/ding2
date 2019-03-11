/**
 * @file
 * Enables the tabs to change automatically and add handler to capture click
 * events on the tabs.
 */
(function ($) {
  "use strict";

  Drupal.behaviors.ding_nodelist_rolltab = {
    attach: function (context) {
      var rolltab = $('.ding_nodelist-rolltab', context);
      var rolltab_select = $('.ding_nodelist-rolltab-select-tabs', context);

      // Hack to check if tab have been tab_selected, as unbind event will not work.
      var tab_selected = false;

      // Check if the tabs lib is loaded before trying to call it.
      if ($.fn.tabs) {
        rolltab.tabs({
          select: function(event, ui) {
            // Update the mobile navigation drop down.
            rolltab_select.prop('selectedIndex', ui.index);
          }
        }).tabs("rotate", 5000);

        // Stop tabs rotate when mouse is over the tab roll.
        rolltab.mouseenter(function() {
          rolltab.tabs('rotate', 0);
        });

        // Start tabs rotate when mouse is out.
        rolltab.mouseleave(function() {
          if (!tab_selected) {
            rolltab.tabs().tabs("rotate", 5000);
          }
        });
      }

      // Add mouseover event to select tabs options.
      $('.ui-tabs-nav-item', rolltab).mouseover(function(e) {
        e.preventDefault();
        rolltab.tabs({event: "mouseover"}).tabs('rotate', 0);
        tab_selected = true;
        return false;
      });

      // Add click event on selected tab to redirect user to selected tab node.
      $(".ui-tabs-nav-item span").click(function () {
        window.location.href = $(this).attr('datasrc');
        return false;
      });

      // Hook into click events in the responsive mobile selector.
      rolltab_select.on('change', function() {
        rolltab.tabs("option", "active", $(this).prop('selectedIndex'));
        rolltab.tabs().tabs('rotate', 0);
        tab_selected = true;
      });
    }
  };

})(jQuery);
