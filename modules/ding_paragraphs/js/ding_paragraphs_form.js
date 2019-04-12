/**
 * @file
 *
 * Disables dragging in paragraphs when any paragraphs are open.
 */

(function ($) {
  Drupal.behaviors.ding_paragraphs_form = {
    attach: function () {
      'use strict';

      // Hide table drag on page load and ajax load.
      if ($("input[name$='collapse_button']").length > 0) {
        $(".field-type-paragraphs .field-multiple-drag").hide();
      }
      else {
        $(".field-type-paragraphs .field-multiple-drag").show();
      }

      $('.field-type-paragraphs').once(function () {
        // Limit the number of times to act on DOMSubtreeModified.
        var active = false;
        $(this).on('DOMSubtreeModified', function () {
          if (!active) {
            active = true;
            // Hide dragging if an item is not collapsed.
            if ($("input[name$='collapse_button']").length > 0) {
              $(".field-type-paragraphs .field-multiple-drag").hide();
            }
            else {
              $(".field-type-paragraphs .field-multiple-drag").show();
            }
          }
        });
      });
    }
  }
})(jQuery);
