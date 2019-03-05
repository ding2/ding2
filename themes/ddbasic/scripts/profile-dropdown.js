/*jshint forin:false, jquery:true, browser:true, indent:2, trailing:true, unused:false */
(function($) {
  'use strict';

  function dropdown() {
    return $('.js-mobile-user-menu');
  }

  // Profile dropdown
  Drupal.behaviors.profile_dropdown = {
    attach: function(context, settings) {
      var my_account = $('a.topbar-link-user-account', context);
      var body = $('body');

      if (my_account.length === 0) {
        return;
      }

      // Open/close mobile menu on click.
      my_account.on('click', function(event) {
        if(body.hasClass('has-touch') && !ddbasic.breakpoint.is('tablet')) {
          event.preventDefault();
          if($(this).hasClass('js-active')) {
            body.removeClass('mobile-usermenu-is-open overlay-is-active');
            my_account.removeClass('js-active active');
          } else {
            dropdown().css({
              'left': my_account.position().left - (dropdown().width() - my_account.width()),
            });
            body.addClass('mobile-usermenu-is-open overlay-is-active');
            my_account.addClass('js-active active');
          }
        }

        if (ddbasic.breakpoint.is('tablet')) {
          event.preventDefault();
          body.toggleClass('mobile-usermenu-is-open');
          body.removeClass('mobile-menu-is-open pane-login-is-open mobile-search-is-open');
          if(body.hasClass('mobile-usermenu-is-open')) {
            body.addClass('overlay-is-active');
          } else {
            body.removeClass('overlay-is-active');
          }
        }
      });

      // Open dropdown when mouse enters my account menu-link.gla
      my_account.on('mouseenter', function() {
        if (!ddbasic.breakpoint.is('tablet') && !body.hasClass('has-touch')) {
          dropdown().css({
            'left': my_account.offset().left - my_account.width() / 2,
            'position': 'fixed'
          });
          body.addClass('mobile-usermenu-is-open');
          my_account.addClass('js-active active');
        }
      });

      // Close dropdown when mouse leaves the dropdown.
      dropdown().on('mouseleave', function() {
        if(!ddbasic.breakpoint.is('tablet')) {
          dropdown().css('left', '');
          dropdown().css('position', '');
          body.removeClass('mobile-usermenu-is-open');
          my_account.removeClass('js-active active');
        }
      });

      // Close dropdown when mouse leaves my-account menu-link from the sides.
      my_account.on('mouseleave', function(event) {
        if(!ddbasic.breakpoint.is('tablet') && !body.hasClass('has-touch')) {
          if (event.offsetX < 0 || event.offsetX > $(this).width()) {
            dropdown().css('left', '');
            dropdown().css('position', '');
            body.removeClass('mobile-usermenu-is-open');
            my_account.removeClass('js-active active');
          }
        }
      });
    }
  };

})(jQuery);
