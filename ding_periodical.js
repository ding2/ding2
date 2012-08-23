(function ($) {
  $(document).ready(function(){
      $('.field-name-ding-periodical-issues li').children('.item-list').hide();
      $('.field-name-ding-periodical-issues li').children('.item-list form').hide();
  });

  Drupal.behaviors.dingPeriodicalIssueToggle = {
    attach: function (context, settings) {
      $('.field-name-ding-periodical-issues .ding-periodical-fold').toggle(function(){
        $(this).next().show();
        $('.page-ting-object .panel-pane.pane-ting-object-ding-availability-holdings').addClass('holdings-collapsed');
        $('.page-ting-object .grid-3 .panel-pane.pane-ting-object-ding-entity-buttons').addClass('holdings-collapsed');
        $(this).next().toggleClass('expanded-periodicals');
        $(this).parent().toggleClass('expanded-periodicals-parent');
      },
      function () {
        $(this).next().hide();
        $(this).next().toggleClass('expanded-periodicals');
        $(this).parent().toggleClass('expanded-periodicals-parent');
      });
      $('.ding-periodical-foldable .item-list .ding-periodical-foldable li').click(function(){
        $(this).find('form').clone().appendTo($(this));
        $(this).find('form:first').dialog({
          title: Drupal.t('Reserve')
        });
      });
    }
  }    
}(jQuery));
