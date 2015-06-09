/**
 * @file
 *
 * Provide event nodes/pages with ticket info from Place2book
 */
(function ($) {

  Drupal.behaviors.ding_place2book = {
    attach: function (context, settings) {
      $('.place2book-ticketinfo').each(function () {
        var request = $.ajax({
          url: Drupal.settings.basePath + 'ding/place2book/ticketinfo/' + this.value,
          type: 'POST',
          dataType: 'json',
          success: ding_place2book_insert,
        });
      });
    }
  };

  var ding_place2book_insert = function(ding_place2book) {
    $('.place2book-ticketinfo').replaceWith(ding_place2book.markup);
  };
 
})(jQuery);
