/**
 * @file
 * Default field formatter behavior scripts.
 */

(function ($) {
  "use strict";

  // Drupal behavior.
  Drupal.behaviors.ding_entity_rating = {
    attach: function (context) {
      // Attach rating widget.
      $('.ding-entity-rating, .ding-entity-rating-submitted', context).rating();

      var rating_ids = [];
      $('.ding-entity-rating.rateable', context).each(function () {
        rating_ids.push($(this).attr('data-ding-entity-rating-id'));
      });

      // Override average ratings with users own ratings.
      if ($('body').hasClass('logged-in') && rating_ids.length > 0) {
        var url = Drupal.settings.basePath + Drupal.settings.pathPrefix + 'ding_entity_rating/user/get';
        $.ajax({
          url: url,
          data: {ids: rating_ids},
          dataType: 'json',
          method: 'get',
          success: function (data) {
            for (var i in data) {
              if (data[i] !== false) {
                $('.ding-entity-rating[data-ding-entity-rating-id="' + i + '"] .js-rating-symbol')
                  .eq(data[i])
                  .removeClass('submitted')
                  .prevAll().addClass('submitted')
                  .end().nextAll().removeClass('submitted')
                  .end().parent().addClass('has-submission')
                  .find('.ding-entity-rating-avg').remove();
              }
            }
          }
        });
      }
    }
  };
})(jQuery);
