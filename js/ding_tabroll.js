/**
 * @file
 * Enables the tabs to change automatically and add handler to capture click
 * events on the tabs.
 */
(function ($) {

  $(document).ready(function($) {
    var tabroll = $("#ding-tabroll");

    // Check if the tabs lib is loaded before trying to call it.
    if ($.fn.tabs) {
      tabroll.tabs().tabs("rotate", 5000, false);

      // Stop tabs rotate when mouse is over the tab roll.
      tabroll.mouseover(function(){
        tabroll.tabs('rotate', 0, false);
      });

      // Start tabs rotate when mouse is out.
      tabroll.mouseout(function(){
        tabroll.tabs().tabs("rotate", 5000, false);
      });
    }

    // Add click event to select tabs options.
    $('.tabroll-tabs-item', tabroll).click(function(e) {
      e.preventDefault();
      tabroll.tabs("select", $(this).index());
    });

    // Hook into click events in the responsive mobile selector.
    $('.ding-tabroll-select-tabs').live('change', function() {
      tabroll.tabs("select", $(this).prop('selectedIndex'));
    });
  });

})(jQuery);
