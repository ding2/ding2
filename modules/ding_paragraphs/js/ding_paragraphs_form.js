/**
 * @file
 *
 * Disables dragging in paragraphs when any paragraphs are open.
 */
(function ($) {
  'use strict';
  Drupal.behaviors.ding_paragraphs_form = {
    attach: function () {
      // Hide table drag on page load and ajax load.
      // This is done to prevent data loss when dragging open paragraphs around.
      if ($(".field-type-paragraphs input[name$='collapse_button']").length > 0) {
        $(".field-type-paragraphs .field-multiple-drag").hide();
      }
      else {
        $(".field-type-paragraphs .field-multiple-drag").show();
      }
    }
  }
})(jQuery);
