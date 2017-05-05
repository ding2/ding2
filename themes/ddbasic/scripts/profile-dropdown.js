/*jshint forin:false, jquery:true, browser:true, indent:2, trailing:true, unused:false */
(function($) {
  'use strict';

  function dropdown() {
    return $('.js-mobile-user-menu .navigation-inner > .main-menu-third-level');
  }

  // Profile dropdown
  Drupal.behaviors.profile_dropdown = {
    attach: function(context, settings) {
      var my_account = $('a.topbar-link-user-account', context),
        body = $('body');

      if (my_account.length === 0) {
        return;
      }

      // Open/close mobile menu on click.
      my_account.on('click', function(event) {
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
        if (!ddbasic.breakpoint.is('tablet')) {
          dropdown().css({
            'left': my_account.position().left - (dropdown().width() - my_account.width()),
          });
          body.addClass('mobile-usermenu-is-open');
          my_account.addClass('js-active active');

          // Close dropdown when mouse leaves the dropdown.
          dropdown().on('mouseleave.profiledropdown', function() {
            if (!ddbasic.breakpoint.is('tablet')) {
              dropdown().css('left', '');
              body.removeClass('mobile-usermenu-is-open');
              my_account.removeClass('js-active active');

              dropdown().off('mouseleave.profiledropdown');
            }
          });
        }
      });

      // Close dropdown when mouse leaves my-account menu-link from the sides.
      my_account.on('mouseleave', function(event) {
        if(!ddbasic.breakpoint.is('tablet')) {
          if (event.offsetX < 0 || event.offsetX > $(this).width()) {
            dropdown().css('left', '');
            body.removeClass('mobile-usermenu-is-open');
            my_account.removeClass('js-active active');
            dropdown().off('mouseleave.profiledropdown');
          }
        }
      });
    }
  };

})(jQuery);
