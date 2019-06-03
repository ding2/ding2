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
            // Ensure that behaviors are attached to the new content.
            Drupal.attachBehaviors(elm);
          }
        });
      });
    }
  };

})(jQuery);
