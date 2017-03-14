/**
 * @file
 *
 * Provide event nodes/pages with ticket info from Place2book
 */
(function ($) {

  Drupal.behaviors.ding_place2book = {
    attach: function (context, settings) {
      $('.place2book-ticketinfo').once('place2book-button', function() {
        var request = $.ajax({
          url: Drupal.settings.basePath + 'ding/place2book/ticketinfo/' + this.value,
          type: 'POST',
          dataType: 'json',
          success: ding_place2book_insert,
        });
      });
    }
  };

  /**
   * Replace placeholder with place2book data.
   */
  var ding_place2book_insert = function(ding_place2book) {
    $(".place2book-ticketinfo[data-ticket='" + ding_place2book.nid + "']").replaceWith(ding_place2book.markup);
  };
 
})(jQuery);
