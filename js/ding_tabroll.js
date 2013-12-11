/**
 * @file
 * Enables the tabs to change automatically and add handler to capture click
 * events on the tabs.
 */
(function ($) {

  $(document).ready(function($) {
    var tabroll = $('.ding-tabroll');
    var tabroll_select = $('.ding-tabroll-select-tabs');

    // Hack to check if tab have been tab_selected, as unbind event will not work.
    var tab_selected = false;

    // Check if the tabs lib is loaded before trying to call it.
    if ($.fn.tabs) {
      tabroll.tabs({
        select: function(event, ui) {
          // Update the mobile navigation drop down.
          tabroll_select.prop('selectedIndex', ui.index);
        }
      }).tabs("rotate", 5000);

      // Stop tabs rotate when mouse is over the tab roll.
      tabroll.mouseenter(function() {
        tabroll.tabs('rotate', 0);
      });

      // Start tabs rotate when mouse is out.
      tabroll.mouseleave(function() {
        if (!tab_selected) {
          tabroll.tabs().tabs("rotate", 5000);
        }
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
    tabroll_select.live('change', function() {
      tabroll.tabs("select", $(this).prop('selectedIndex'));
      tabroll.tabs().tabs('rotate', 0);
      tab_selected = true;
    });
  });

})(jQuery);
