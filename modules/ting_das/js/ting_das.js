(function ($) {
  "use strict";

  // The click event on the button is blocked by Drupals ajax mechanism so we use ajaxSend to detect
  // that a ajax call is happening and check if comes from pressing the order button
  $(document).ajaxSend(function (e, xhr, settings) {
    if ((typeof settings !== 'undefined') && (typeof settings.extraData !== 'undefined')) {
      if (typeof settings.extraData._triggering_element_name !== 'undefined') {
        var trigger = settings.extraData._triggering_element_name;
        if (trigger == "op") {
          var overlay = $('<div id="ting-das-overlay" class="das-overlay search-overlay--wrapper"><div class="search-overlay--inner"><div class="spinner-container"><i class="icon-spinner icon-spin search-overlay--icon"><svg x="0px" y="0px" width="84px" height="84px" viewBox="0 0 84 84" enable-background="new 0 0 84 84" xml:space="preserve"><path fill="#FFFFFF" d="M84,42C84,18.842,65.158,0,42,0C18.841,0,0,18.842,0,42c0,23.159,18.841,42,42,42v-1.988	C19.944,82.012,2,64.062,2,42S19.944,1.988,42,1.988c22.057,0,40,17.949,40,40.012c0,9.363-3.262,18.366-9.21,25.536l-0.501-8.577 l-1.998,0.117l0.697,11.918l11.91-1.559l-0.26-1.974l-8.072,1.058C80.662,61.042,84,51.704,84,42z"/></svg></i></div><p class="search-overlay--text">' + Drupal.t('Ordering article, please wait. May take up to 10 seconds...') + '</p></div></div>');
          $('#popupbar-ting_das').prepend(overlay);
        }
      }
    }

  }).ajaxComplete(function (e, xhr, settings) {
    $('#ting-das-overlay').hide();
  });


}(jQuery));
