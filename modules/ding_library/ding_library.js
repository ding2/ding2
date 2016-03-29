(function ($) {
  "use strict";
  Drupal.behaviors.pathAutoDisable = {
    attach: function () {
      // fake a disabled checkbox
      var check = $('#edit-path-pathauto');
      check.attr('checked', 'checked');
      check.css('opacity', '0.5');
      check.change(function () {
        check.attr('checked', 'checked');
      });
    }
  };
})(jQuery);
