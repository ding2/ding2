(function ($) {
  "use strict";
  Drupal.behaviors.ding_nodelist_slide = {
    attach: function () {
      $('.next-prev a').click(function (e) {
        e.preventDefault();
      });

      $('.ding_nodelist-slider .ding_nodelist-items').each(function() {
        var nodelistItems = $(this);

        // Find highest nodelist item and make other same height
        var rowHeight = findHighestItem(nodelistItems.find('.item'));

        nodelistItems.find('.item').height(rowHeight);

        nodelistItems.newsTicker({
          row_height: rowHeight,
          max_rows: 3,
          duration: 4000,
          direction: 'up',
          pauseOnHover: 0,
          prevButton: $('.next-prev .prev'),
          nextButton: $('.next-prev .next')
        });
      });
    }
  };

  /**
   * Finds and returns highest item
   */
  function findHighestItem(items) {
    var highestItem = 0;

    items.each(function() {
      if($(this).height() > highestItem) {
        highestItem = $(this).height();
      }
    });

    return highestItem;
  }
})(jQuery);
