/*jshint forin:false, jquery:true, browser:true, indent:2, trailing:true, unused:false */
/*globals ddbasic*/
(function($) {
  'use strict';

  // Make actions-container sticky when it hits header.
  $(function() {
    var
      offset,
      is_mobile;

    $(window)
      .bind('resize.actions_container', function (evt) {
        offset = $('.js-content-wrapper').offset().top;
        is_mobile = ddbasic.breakpoint.is('mobile');

        // Set the width of the container, so it matches the form.
        $('.js-actions-container-fixed').each(function() {
          var container = $(this),
            form = container.closest('form');

          // The container is not fixed on mobile, so reset it.
          if (is_mobile === true) {
            form.css('padding-top', '');
            container
              .removeClass('is-fixed', 'is-bottom')
              .css({
                width: '',
                top: ''
              });
          }
          else {
            // The container is either absolute or fixed, so we need to add the
            // height as a padding to it's form.
            form.css('padding-top', container.outerHeight(true));
            container.css('width', form.width());
          }
        });

        // Position the container in the scroll event.
        $(window).triggerHandler('scroll.actions_container');
      })
      .bind('scroll.actions_container', function (evt) {
        if (is_mobile) {
          return;
        }

        // The mark where the container starts sticking.
        var mark = $(window).scrollTop() + offset;

        $('.js-actions-container-fixed').each(function() {
          var container = $(this),
            form = container.closest('form'),
            form_top = form.offset().top;

          if (form_top < mark) {
            // If the user has scrolled past the form set the container to the
            // bottom of the form.
            if (form_top + form.height() < mark) {
              if (!container.hasClass('is-bottom')) {
                container
                  .removeClass('is-fixed')
                  .addClass('is-bottom')
                  .css('top', '');
              }
            }
            // Stick it to the top.
            else {
              if (!container.hasClass('is-fixed')) {
                container
                  .addClass('is-fixed')
                  .removeClass('is-bottom')
                  .css('top', offset);
              }
            }
          }
          // Reset the top and any other modifiers if mark has not been reached.
          else if (container.hasClass('is-bottom') || container.hasClass('is-fixed')) {
            container
              .removeClass('is-bottom is-fixed')
              .css('top', '');
          }
        });
      })
      .triggerHandler('resize.actions_container');
  });

})(jQuery);
