
(function($) {

  Drupal.behaviors.tingFieldSearchWebtrends = {
    attach: function(context, settings) {

      // Track when a profile is selected if Webtrends is selected.
      $("#edit-ting-field-search", context).change(function() {
        if (typeof dcsMultiTrack !== "undefined") {
          var profile_name = $(this).children(":selected").val();
          var uri = "/ting-field-search/profile-selected/" + profile_name;

          dcsMultiTrack("WT.ti", profile_name, "DCS.uri", uri);
        }
      });
    }
  };

})(jQuery);
