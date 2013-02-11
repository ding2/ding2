(function ($) {
$(document).ready(function(){
    $('.field-name-ding-periodical-issues li').children('.item-list').hide();
    $('.ding-periodical-fold').addClass('expand expand-more')
});

  Drupal.behaviors.dingPeriodicalIssueToggle = {
    attach: function (context, settings) {
        $('.field-name-ding-periodical-issues .ding-periodical-fold').click(function(){
          $(this).parent('.ding-periodical-foldable').children('.item-list').toggle();
          $(this).toggleClass('expand-more').toggleClass('expand-less');
        });
    }
  }
}(jQuery));
