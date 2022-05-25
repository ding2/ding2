(function($){
  'use strict';

  // Set height for nodes teasers.
  $(window).bind('resize.node_teaser', function () {
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
        }

        $row = $(this).find('[data-row="' + id + '"]');
      }
    });
  });

  Drupal.behaviors.ding_nodelist_nodeblocks_hover = {
    attach: function (context, settings) {
      var nodeBlocksSettings = settings.ding_nodelist.node_blocks;
      var hovered,
          $pane = $('.ding_nodelist-items', context),
          isMobile = window.innerWidth <= 600;
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

      // Added function to set height for title and lead text for CTs.
      $('.node-ding-event.nb-item, .node-ding-news.nb-item, .node-ding-page.nb-item, .node-ding-eresource.nb-item', context).mouseenter(function() {
        var title_and_lead_height;
        // Set height for title and lead text.
        title_and_lead_height = $(this).find('.title-and-lead').outerHeight(true) + $(this).find('.field-type-text-long').outerHeight(true) + 20;

        $(this).find('.title-and-lead').css('min-height', title_and_lead_height);
      });

      /**
       * Node Blocks DOM manipulation.
       */
      var nbPanes = $('.ding_nodelist-node_blocks .ding_nodelist-items', context);
      nbPanes.each(function (key, pane) {
        var $pane = $(pane);

        // Build default config parameters.
        var config = [];
        $pane.find('article').each(function (i, val) {
          var data = {};
          data.id = $(val).data('id');
          data.hasImage = $(val).hasClass('has-image');
          data.marginTop = 0;

          if ($(val).hasClass('has-image') && i !== 0 || !$(val).hasClass('has-image') && i !== 0) {
            data.marginTop = 200;
          }
          config.push(data);
        });

        // Add corrections to the configs conditionally.
        config.map(function (val) {
          var current = config[val.id];
          var next = config[val.id + 1];

          if (next === undefined) {
            return;
          }

          if (current.hasImage === true && next.hasImage === false) {
            next.marginTop = 200;
          }
          else if (current.hasImage === false && next.hasImage === true) {
            next.marginTop = 0;
          }
          else if (current.hasImage === false && next.hasImage === false) {
            next.marginTop = 0;
          }
        });

        // Process items rendering.
        config.forEach(function (e) {
          if (isMobile) {
            if (nodeBlocksSettings.displayMobileImage === 1) {
              if (e.hasImage === true) {
                $pane.find("article[data-id=" + e.id + "]").find('.nb-image').css('display', 'block');

                $pane.find("article[data-id=" + e.id + "]").css('margin-top', e.marginTop);
                $pane.find("article[data-id=" + e.id + "] .inner").css('margin-top', e.marginTop);
                if (e.marginTop === 0) {
                  $pane.find("article[data-id=" + e.id + "] .inner").css('margin-top', 200);
                }
                if (e.id === config.length - 1) {
                  $pane.find("article[data-id=" + e.id + "]").css('margin-bottom', $pane.find("article[data-id=" + e.id + "]").height());
                }
              }
              else {
                $pane.find("article[data-id=" + e.id + "]").css('margin-top', e.marginTop);
              }
            }
          }
        });
      });
    }
  };
})(jQuery);
