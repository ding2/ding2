(function ($) {
$(document).ready(function(){
    $('.field-name-ding-periodical-issues li').children('.item-list').hide();
});

  Drupal.behaviors.dingPeriodicalIssueToggle = {
    attach: function (context, settings) {
      $('.field-name-ding-periodical-issues .ding-periodical-fold').click(function(){
	    $(this).parent('.ding-periodical-foldable').children('.item-list').dialog({
	      title: Drupal.t('Reserve')
	    });
      });
    }
  }    
}(jQuery));
