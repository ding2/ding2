(function($) {
  "use strict";

  $(document).ready(function() {
    // Click the label link when a radio button is clicked.
    $('#ting-search-backend-engines-form input[type="radio"]').change(function() {
      var link = $(this).parent().find('a');
      window.location = link.attr('href');
    });

    // When a label link is click, also check the radio button.
    $('#ting-search-backend-engines-form a').click(function(event) {
      var radio = $(this).parent().parent().find('input[type="radio"]');
      if (radio.is(':checked')) {
        // If it is already checked do nothing.
        event.preventDefault();
        return false;
      }
      else {
        // Check the radio button and continue handling the click event.
        radio.attr('checked', 'checked');
        return true;
      }
    });
  });
}(jQuery));
