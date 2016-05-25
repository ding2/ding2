(function ($) {
  "use strict";
  $('html').click(function() {
    $('.ipe-popup').addClass('hide');
    $('.ipe-popup').removeClass('top');
  });
  $(document).on('click', '.ipe-trigger', function() {
    // Hide all elements before open other.
    $('.ipe-popup').addClass('hide');
    $('.ipe-popup').removeClass('top');

    var menu = '#ipe-add-' + $(this).attr('target_region');
    // Move menu from the left if it is too close to the border.
    if (parseInt($(this).parent().offset().left) < 300) {
      $(menu).toggleClass('left');
    }
    // Move menu on top if it is too close to bottom of the page.
    if (parseInt($(this).parent().offset().top) - parseInt(screen.height) > 1400) {
      $(menu).toggleClass('top');
    }
    // Display element on click.
    $(menu).toggleClass('hide');

    return false;
  });
  
  $(document).on('mouseleave', '.ipe-popup', function() {
    $(this).toggleClass('hide');
    $(this).removeClass('left');
    $(this).removeClass('top');
  });
})(jQuery);
