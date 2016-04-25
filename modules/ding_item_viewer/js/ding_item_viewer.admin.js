(function ($) {
  Drupal.behaviors.ding_item_viewer = {
    attach: function(context) {
      $('.search-item_viewer-query .remove').click(function () {
        $(this).parents('tr').remove();

        return false;
      });
    }
  }
})(jQuery);
