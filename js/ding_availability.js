/**
 * @file ding.availability.js
 * JavaScript behaviours for fetching and displaying availability.
 */

(function ($) {

Drupal.behaviors.dingAvailabilityAttach = {
  attach: function (context, settings) {
    var ids = [];
    $.each(settings.ding_availability, function(class_name, id) {
        ids.push(id);
    });

    if (ids.length > 0) {
      $.getJSON(settings.basePath + 'ding_availability/' + settings.ding_availability_mode + '/' + ids.join(','), {}, update);
    }

    function update(data, textData) {
      $.each(data, function(id, item) {
        if (settings.ding_availability['availability-' + id] != undefined) {
          var text = "";
          if (item['available']) {
            $('.availability-' + id).addClass('available');
          }
          if (item['reservable']) {
            $('.availability-' + id).addClass('reservable');
          }
          $('.availability-' + id).text(item['status']);
          if (item['holdings'] !== undefined) {
            // TODO: Check if holdings-<id> exists.
            if (item['holdings'].length > 0) {
              $('.holdings-' + id).append('<h2>' + 'Holdings' + '</h2>');
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
