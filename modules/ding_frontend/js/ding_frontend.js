(function ($) {
  'use strict';

  Drupal.behaviors.ding_frontend = {
    attach: function (context) {
      // Submit tags filter only after element is selected.
      let tags_filter_input = $('#custom-tags-filter', context);
      tags_filter_input.on('blur', function () {
        $('form#views-exposed-form-ding-multiple-search-panel-pane-1 input[type=submit]').click();
      });
    }
  };
})(jQuery);
