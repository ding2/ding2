(function($) {
  "use strict";

  $(document).ready(function() {
    // We have a hidden element containing all
    // the options as <label>'s - this is necessary
    // to get the px size of a text, something that
    // we cannot calculate as it depends on font-family,
    // font-size and general rendering.
    // By having the texts represented in the dom as
    // labels, we can get the width of these and set the
    // <select> width accordingly.
    function getSelectSize(select) {
      var text = select.options[select.selectedIndex].text;
      var label = $('.js-form-search-sort-labels label:contains("' + text + '")');

      return (label[0].offsetWidth) + 'px';
    }

    var select = $('.js-form-search-sort select');

    // If we cant find a select, we might as well
    // not continue.
    if (!select.length) {
      return;
    }

    // We need to set the initial size of the select.
    select[0].style.width = getSelectSize(select[0]);

    // Whenever the select changes, we'll also
    // want to update the size of the select.
    $(select).change(function () {
      select[0].style.width = getSelectSize(select[0]);
    });
  });
}(jQuery));
