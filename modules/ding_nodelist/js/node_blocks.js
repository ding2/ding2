(function($){
  'use strict';

  // Set height for nodes teasers.
  $(window).bind('resize.node_teaser', function (event, isMobile) {
    $('.ding_nodelist-node_blocks').each(function () {
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
          if (isMobile === true && $(article).hasClass('has-image')) {
            $(article).height(height + 200);
          }
        }

        $row = $(this).find('[data-row="' + id + '"]');
      }
    });
  });

  Drupal.behaviors.ding_nodelist_nodeblocks_hover = {
    attach: function (context) {
      var hovered,
        $nbPane = $('.ding_nodelist-node_blocks .ding_nodelist-items', context),
        isMobile = window.innerWidth <= 600;

      $nbPane.each(function (index, value) {
        var $pane = $(value);
        $pane.trigger('resize.node_teaser', isMobile);
        $pane.find('article').mouseenter(function () {
          // Set timeout to make sure element is still above while it animates
          // out.
          hovered = $(this);
          hovered.find('.field-type-text-long').toggleClass('element-hidden', false);
        });

        $pane.find('article').mouseleave(function () {
          $(this).find('.title-and-lead').css('min-height', '');
          $(this).find('.field-type-text-long').toggleClass('element-hidden', true);
        });

        // Added function to set height for title and lead text for CTs.
        $('.node-ding-event.nb-item, .node-ding-news.nb-item, .node-ding-page.nb-item, .node-ding-eresource.nb-item', context).mouseenter(function () {
          var title_and_lead_height;
          // Set height for title and lead text.
          title_and_lead_height = $(this).find('.title-and-lead').outerHeight(true) + $(this).find('.field-type-text-long').outerHeight(true) + 20;

          if (isMobile !== true) {
            $(this).find('.title-and-lead').css('min-height', title_and_lead_height);
          }
        });

        var displayImagesOnMobile = $pane.data('display-images-on-mobile');
        if (displayImagesOnMobile === 0 && isMobile === true) {
          $pane.find('article').each(function (key, item) {
            var article = $(item);
            article.removeClass('has-image');
            article.find('.nb-image').remove();
            article.height($(item).height() - 200);
            article.find('.text').css('padding-top', '');
            $pane.trigger('resize.node_teaser', isMobile);
          });
        }
      });
    }
  };
})(jQuery);
