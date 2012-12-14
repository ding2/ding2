(function ($) {

$(document).ready(function($) {
  // Check if the tabs lib is loaded before trying to call it.
  if ($.fn.tabs) {
    //$("#featured").ready({create: removeClassesCreateHandler});
    $("#featured").tabs({fx: {opacity: "toggle"}}).tabs("rotate", 5000);
}
});

})(jQuery);