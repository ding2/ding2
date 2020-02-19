(function ($) {
  "use strict";

  function removeClasses() {
    var $el =  $('.ipe-popup');
    $el.addClass('element-hidden');
    $el.removeClass('ding-ipe-popup-top');
    $el.removeClass('ding-ipe-popup-left');
  }

  // If click outside the popup menu close the menu.
  $('html').click(function() {
    removeClasses();
  });

  // Handle clicks on the "Add" buttons.
  $(document).on('click', '.ipe-trigger', function() {
    // Hide all elements before open other.
    $(this).addClass('active');
    removeClasses();

    var menu = '#ipe-add-' + $(this).attr('target_region');
    menu = $(menu);

    // Move menu from the left if it is too close to the border.
    if (parseInt($(this).parent().offset().left) < 700) {
      menu.toggleClass('left');
    }

    // Move menu on top if it is too close to bottom of the page.
    var containerHeight = $('.panels-ipe-display-container').height();
    var menuPosition = $(this).parent().offset().top;
    if (parseInt(containerHeight - menuPosition) < 0) {
      menu.toggleClass('ding-ipe-popup-top');
    }

    // Display element on click.
    menu.toggleClass('element-hidden');

    return false;
  });

  // Close popup menu when mouse is move outside the popup.
  $(document).on('mouseleave', '.ipe-popup', function() {
    removeClasses();
    $('.ipe-trigger').removeClass('active');
  });

  // Close modal window on cancel button click.
  Drupal.behaviors.ding_ipe_filter = {
    attach: function(context) {
      $('#edit-cancel', context).on('click', function() {
        Drupal.CTools.Modal.dismiss();

        return false;
      });

      // Display ipe controllers only relative to container.
      $('body').removeClass('panels-ipe-editing');
    }
  };

  /**
   * Override the eventResponse on ajax.js so we can add a little extra
   * behavior.
   */
  Drupal.ajax.prototype.dingIpeReplacedEventResponse = Drupal.ajax.prototype.eventResponse;
  Drupal.ajax.prototype.eventResponse = function (element, event) {
    var retval = this.dingIpeReplacedEventResponse(element, event);
    if (this.ajaxing && this.element_settings.ipe_cache_key) {
      if (this.progress.element) {
        $(this.progress.element).attr('id', 'ding-ipe-throbber').appendTo($('body'));
        $('.html').addClass('overlay-is-active');
      }

      Drupal.PanelsIPE.editors[this.element_settings.ipe_cache_key].hideContainer();
    }
    return retval;
  };

  /**
   * Override the "success" on ajax.js.
   */
  Drupal.ajax.prototype.dingIpeReplacedSuccessResponse = Drupal.ajax.prototype.success;
  Drupal.ajax.prototype.success = function (element, event) {
    var retval = this.dingIpeReplacedSuccessResponse(element, event);
    if (event === 'success') {
      $('.html').removeClass('overlay-is-active');
    }
    return retval;
  };
})(jQuery);
