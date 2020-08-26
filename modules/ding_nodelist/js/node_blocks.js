(function($){
  'use strict';

  // Set height for nodes teasers.
  $(window).bind('resize.node_teaser', function () {
    var panes = Drupal.settings.ding_nodelist;
    for (var pane in panes) {
      if (panes.hasOwnProperty(pane)) {
        var $pane = $('.ding_nodelist-node_blocks.' + pane),
            id = 0, height = 0,
            $row = $pane.find('[data-row="' + id + '"]');

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

          $row = $pane.find('[data-row="' + id + '"]');
        }
      }
    }
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
    }
  };
})(jQuery);
