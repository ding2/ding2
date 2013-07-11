(function ($) {

$(document).ready(function($) {
  // Check if the tabs lib is loaded before trying to call it.
  if ($.fn.tabs) {
    $("#ding-tabroll").tabs({fx: {opacity: "toggle"}}).tabs("rotate", 5000, false);
  }

  //Add click event to select tabs options
  $('.tabroll-tabs-item').click(function(e) {
    //alert('count-' + $(this).index());
    $("#ding-tabroll").tabs("select", $(this).index());
  });

});

})(jQuery);