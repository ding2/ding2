/**
 * @file
 * Ajax rating field formatter behavior scripts.
 */

(function ($) {
  "use strict";

  // Drupal behavior.
  Drupal.behaviors.ding_entity_rating_ajax = {
    attach: function (context) {

      var rating_ids = [];
      $('.ding-entity-rating-display-ajax', context).once(function () {
        rating_ids.push($(this).attr('data-ding-entity-display-ajax-rating-id'));
      });

      if (rating_ids.length > 0) {
        var url = Drupal.settings.basePath + Drupal.settings.pathPrefix + 'ding_entity_rating/get';
        $.ajax({
          url: url,
          data: {ids: rating_ids},
          dataType: 'json',
          method: 'post',
          success: function (data) {
            for (var i in data) {
              var element = $('.ding-entity-rating-display-ajax[data-ding-entity-display-ajax-rating-id="' + i + '"] .icon-spinner');
              element.replaceWith(data[i]);

              // Attach rating widget.
              $('.ding-entity-rating, .ding-entity-rating-submitted', context).rating();
            }
          }
        });
      }
    }
  };
})(jQuery);
