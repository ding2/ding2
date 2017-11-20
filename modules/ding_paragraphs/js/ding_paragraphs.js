/**
 * @file
 * Handles the carousels loading of content and changes between tabs.
 *
 * There are two selectors to change tabs based on breaks points
 * (which is handle by the theme).
 *
 * For large screens the normal tab list (ul -> li) is used while on small
 * screens (mobile/tables) a select dropdown is used.
 */

(function ($) {
  Drupal.behaviors.ding_paragraphs = {
    attach: function (context) {
      "use strict";
      $('.paragraphs-block .view-mode-paragraphs-teaser').once(function () {
        // This ensures that ting objects loaded via ajax in the carousel's gets
        // reservations buttons displayed if available. So basically it finds
        // the material ids and coverts them into ding_availability format and
        // updates the settings, which is this used when behaviors are attached
        // below. This is a hack, but the alternative was to re-write
        // ding_availability.
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