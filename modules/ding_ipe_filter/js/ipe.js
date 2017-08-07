(function ($) {
  "use strict";
  $('html').click(function() {
    $('.ipe-popup').addClass('element-hidden');
    $('.ipe-popup').removeClass('ding-ipe-popup-top');
    $('.ipe-popup').removeClass('ding-ipe-popup-left');
  });
  $(document).on('click', '.ipe-trigger', function() {
    // Hide all elements before open other.
    $(this).addClass('active');
    $('.ipe-popup').addClass('element-hidden');
    $('.ipe-popup').removeClass('ding-ipe-popup-top');
    $('.ipe-popup').removeClass('ding-ipe-popup-left');

    var menu = '#ipe-add-' + $(this).attr('target_region');
    // Move menu from the left if it is too close to the border.
    if (parseInt($(this).parent().offset().left) < 700) {
      $(menu).toggleClass('left');
    }
    // Move menu on top if it is too close to bottom of the page.
    var containerHeight = $('.panels-ipe-display-container').height();
    var menuPosition = $(this).parent().offset().top;
    if (parseInt(containerHeight - menuPosition) < 0) {
      $(menu).toggleClass('ding-ipe-popup-top');
    }
    // Display element on click.
    $(menu).toggleClass('element-hidden');

    return false;
  });

  $(document).on('mouseleave', '.ipe-popup', function() {
    $(this).toggleClass('element-hidden');
    $(this).removeClass('ding-ipe-popup-left');
    $(this).removeClass('ding-ipe-popup-top');
    $('.ipe-trigger').removeClass('active');
  });

  Drupal.behaviors.ding_ipe_filter = {
    attach: function(context) {
      // Close modal window on cancel button click.
      $('#edit-cancel', context).on('click', function() {
        Drupal.CTools.Modal.dismiss();
        return false;
      });
    }
  };
})(jQuery);
