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
      $.getJSON(settings.basePath + 'ding_availability/item/' + ids.join(','), {}, update);
    }
    function update(data, textData) {
      console.dir(data);
      $.each(data, function(id, item) {
        if (settings.ding_availability[id] != undefined) {
          $('.availability-' + id).css('border', '1px solid red');
        }
      });
    }
  }
}

})(jQuery);
