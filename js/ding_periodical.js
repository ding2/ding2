(function ($) {
  $(document).ready(function(){
    // Hide all elements.
    $('.ding-periodical-issues li').children('.item-list').hide();

    // Add class to style the list as being expandable.
    $('.ding-periodical-fold').addClass('expand expand-more');
    
    // Attach click event to fold in/out the issues.
    $('.field-name-ding-periodical-issues .ding-periodical-fold').live("click", function() {
      $(this).next().toggle();
      $(this).next().toggleClass('expanded-periodicals');
      $(this).parent().toggleClass('expanded-periodicals-parent');
    });
  });
}(jQuery));
