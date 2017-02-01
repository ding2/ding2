/**
 * @file
 * Ding interaction widget
 * Handles the close button in the corner.
 */

(function ($) {
  "use strict";

  $.widget("ding.interaction", {
    // the constructor
    _create: function() {
      this.element
        // add a class for theming
        .addClass("ding-interaction")
        // prevent double click to select text
        .disableSelection();

      this.closer = $('.close-btn', this.element).addClass('icon-remove-sign button');

      // bind click events on the changer button to the random method
      $(this.closer).on('click', function(e) {
        e.preventDefault();
        $(this).closest(".pane-interaction-pane").slideUp();
      });
    },
  });

  Drupal.behaviors.ding_interaction = {
    attach: function (context) {
      $('.ding-interaction-pane', context).interaction();
    }
  };
})(jQuery);
