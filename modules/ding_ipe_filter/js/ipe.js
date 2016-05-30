(function ($) {
  "use strict";
  $('html').click(function() {
    $('.ipe-popup').addClass('hide');
    $('.ipe-popup').removeClass('top');
    $('.ipe-popup').removeClass('left');
  });
  $(document).on('click', '.ipe-trigger', function() {
    // Hide all elements before open other.
    $(this).addClass('active');
    $('.ipe-popup').addClass('hide');
    $('.ipe-popup').removeClass('top');
    $('.ipe-popup').removeClass('left');

    var menu = '#ipe-add-' + $(this).attr('target_region');
    // Move menu from the left if it is too close to the border.
    if (parseInt($(this).parent().offset().left) < 700) {
      $(menu).toggleClass('left');
    }
    // Move menu on top if it is too close to bottom of the page.
    if (parseInt($(this).parent().offset().top) > 2200) {
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
    $('.ipe-trigger').removeClass('active');
  });
})(jQuery);
