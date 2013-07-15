(function ($) {

  $(document).ready(function($) {
    var tabroll = $("#ding-tabroll");

    // Check if the tabs lib is loaded before trying to call it.
    if ($.fn.tabs) {
      tabroll.tabs({fx: {opacity: "toggle"}}).tabs("rotate", 5000, false);
    }

    // Add click event to select tabs options.
    $('.tabroll-tabs-item', tabroll).click(function(e) {
      e.preventDefault();
      tabroll.tabs("select", $(this).index());
    });
  });

})(jQuery);