/**
 * @file
 * Ajax/lazy load ting reference objects into the current page.
 */
(function ($) {
  "use strict";

  Drupal.behaviors.ting_reference_ajax = {
    attach: function (context) {
      $('.ting-reference-item', context).once('ting-reference-item', function () {
        var elm = $(this);
        var entity_id = elm.data('entity-id');
        var view_mode = elm.data('view-mode');
        $.ajax({
          type: 'get',
          url : Drupal.settings.basePath + 'ting_reference/ajax/' + entity_id + '/' + view_mode,
          dataType : 'json',
          success : function (data) {
            elm.html(data.content);

            // This ensures that ting objects loaded via ajax in the carousel's gets
            // reservations buttons displayed if available. So basically it finds
            // the material ids and coverts them into ding_availability format and
            // updates the settings, which is this used when behaviors are attached
            // below. This is a hack, but the alternative was to re-write
            // ding_availability.
            var matches = data.content.match(/reservation-\d+-\w+:\d+/gm);
            if (matches instanceof Array) {
              if (!Drupal.settings.hasOwnProperty('ding_availability')) {
                Drupal.settings.ding_availability = {};
              }
              for (var i in matches) {
                var match = matches[i];
                var id = match.substring(match.indexOf(':') + 1);
                match = match.replace('reservation', 'availability').replace(':', '');
                Drupal.settings.ding_availability[match] = [ id ];
              }
            }

            // Ensure that behaviors are attached to the new content.
            Drupal.attachBehaviors($('.ting-reference-item'));
          }
        });
      });
    }
  };

})(jQuery);
