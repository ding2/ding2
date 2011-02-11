/**
 * @file ding.availability.js
 * JavaScript behaviours for fetching and displaying availability.
 */

(function ($) {

Drupal.behaviors.dingAvailabilityAttach = {
  attach: function (context, settings) {
    var ids = [];
    $.each(settings.ding_availability, function(id, class_name) {
        ids.push(id);
    });

    if (ids.length > 0) {
      $.getJSON(settings.basePath + 'ding_availability/' + settings.ding_availability_mode + '/' + ids.join(','), {}, update);
    }

    function update(data, textData) {
      $.each(data, function(id, item) {
        if (settings.ding_availability[id] != undefined) {
          var text = "";
          if (item['available']) {
            $('.availability-' + id).addClass('available');
            text += Drupal.t('available');
          }
          if (item['reservable']) {
            $('.availability-' + id).addClass('reservable');
            text += Drupal.t('reservable');
          }
          $('.availability-' + id).text(text);
          if (item['holdings'] !== undefined) {
            if (item['holdings'].length > 0) {
              $('.holdings-' + id).append('<ul>');
              var container = $('.holdings-' + id + ' ul');
              $.each(item['holdings'], function (i, holding) {
                container.append('<li>' + holding + '</li>');
              });
            }
          }
        }
      });
    }
  }
}

})(jQuery);
