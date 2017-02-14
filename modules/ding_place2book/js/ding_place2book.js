/**
 * @file
 *
 * Provide event nodes/pages with ticket info from Place2book
 */
(function ($) {

  Drupal.behaviors.ding_place2book = {
    attach: function (context, settings) {
      $('.place2book', context).once('place2book', function () {
        var $this = $(this);
        var event_id = $this.data('event-id');
        var event_maker_id = $this.data('event-maker-id');
        $.ajax({
          url: Drupal.settings.basePath + 'ding/p2b/event_maker/' + event_maker_id + '/event/' + event_id,
          type: 'GET',
          success: function (data) {
            $('.place2book', context).html(JSON.parse(data));
          }
        });
      });
    }
  };

})(jQuery);
