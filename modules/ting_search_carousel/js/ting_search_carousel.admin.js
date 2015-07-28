(function ($) {
  Drupal.behaviors.tingSearchCarousel = {
    attach: function(context) {
      $('.search-carousel-query .remove').click(function () {
        $(this).parents('tr').remove();

        return false;
      });
    }
  }
})(jQuery);