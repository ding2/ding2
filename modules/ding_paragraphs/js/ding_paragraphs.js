/**
 * @file
 * Make ding availibility work and fetch material availability.
 * For more information check out ding_carousel.js.
 */

(function ($) {
  Drupal.behaviors.ding_paragraphs = {
    attach: function (context) {
      "use strict";
      $('.paragraphs-block .view-mode-paragraphs-teaser').once(function () {
        // This ensures that ting objects loaded via ajax in the carousel's gets
        // reservations buttons displayed if available.
        var content = $('.paragraphs-block .view-mode-paragraphs-teaser').html();
        var matches = content.match(/reservation-\d+-\w+:\d+/gm);
        if (matches instanceof Array) {
          if (!Drupal.settings.hasOwnProperty('ding_availability')) {
            Drupal.settings.ding_availability = {};
          }
          for (var i in matches) {
            var match = matches[i];
            var id = match.substring(match.indexOf(':') + 1);
            match = match.replace('reservation', 'availability').replace(':', '');
            Drupal.settings.ding_availability[match] = [id];
          }
        }

        // Ensure that behaviors are attached to the new content.
        Drupal.attachBehaviors($('.paragraphs-block .view-mode-paragraphs-teaser'));
      });
    }}
})(jQuery);