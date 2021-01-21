(function($){
  'use strict';

  // Set height for nodes teasers.
  $(window).bind('resize.node_teaser', function () {
    var panes = $('.ding_nodelist-node_blocks').each(function () {
      var id = 0, height = 0,
          $row = $(this).find('[data-row="' + id + '"]');

      while ($row.length > 0) {
        id++;
        // Find the highest element in row.
        for (var i = 0; i < $row.length; i++) {
          var row_height = $($row[i]).find('.inner').outerHeight();
          if (height < row_height) {
            height = row_height;
          }
        }
        // Adjust height of all elements in row.
        for (i = 0; i < $row.length; i++) {
          var article = $row[i],
              row = $(article).find('.inner').outerHeight();
          if (height - row !== 0) {
            var padding = $(article).find('.text').css('padding-top');
            $(article).find('.text').css('padding-top', parseInt(padding) + height - row);
          }
          $(article).height(height);
        }

        $row = $(this).find('[data-row="' + id + '"]');
      }
    });
  });

  Drupal.behaviors.ding_nodelist_nodeblocks_hover = {
    attach: function (context) {
      var hovered,
          $pane = $('.ding_nodelist-items', context);
      $pane.trigger('resize.node_teaser');

      $pane.find('article').mouseenter(function() {
        // Set timeout to make sure element is still above while it animates
        // out.
        hovered = $(this);
        hovered.find('.field-type-text-long').toggleClass('element-hidden', false);
      });

      $pane.find('article').mouseleave(function() {
        $(this).find('.title-and-lead').css('min-height', '');
        $(this).find('.field-type-text-long').toggleClass('element-hidden', true);
      });

      $('.node-ding-news.nb-item', context).mouseenter(function() {
        var title_and_lead_height;
        // Set height for title and lead text.
        title_and_lead_height = $(this).find('.title').outerHeight(true) + $(this).find('.field-name-field-ding-news-lead').outerHeight(true) + 50;

        $(this).find('.title-and-lead').css('min-height', title_and_lead_height);
      });
    }
  };
})(jQuery);
