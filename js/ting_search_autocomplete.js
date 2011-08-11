(function ($) {
  Drupal.behaviors.tingSearchAutocomplete = {
    attach: function(context) {
      $('#edit-search-block-form--2').autocomplete({
        minLength: 3,
        source: function(request, response) {
          $.getJSON('/ting/autocomplete',{
            query: request.term
          }, response);
        },
        search: function(event, ui) {
          // Use this when starting a search,
          // for ex showing a spinner gif.
          //$('.spinner').show();
        },
        open: function(event, ui) {
          // When a search is done, use this,
          // to ex. hide the spinner.
          //$('.spinner').hide();
        },
        select: function(event, ui) {
          if (ui.item) {
            $('#edit-search-block-form--2').val(ui.item.value);
            $('#search-block-form').submit();
          }
        }
      });
    }
  };
}(jQuery));
