(function($) {
  // Profile dropdown
  Drupal.behaviors.profile_dropdown = {
    attach: function(context, settings) {
      var dropdown = $('.js-mobile-user-menu .navigation-inner > .main-menu-third-level', context),
          my_account = $('a.topbar-link-user-account', context),
          body = $('body', context),
          second_menu_block = $('.pane-menu-block-main-menu-second-level', context);
      
      //Open/close mobile menu on click
      my_account.on('click', function(event){
        if($('.is-tablet', context).is(':visible')) {
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
      
      //Open dropdown when mouse enters my account menu-link
      my_account.on('mouseenter', function(){
        if(!$('.is-tablet', context).is(':visible')) {
          console.log(second_menu_block.height());
          dropdown.css({
            'left': my_account.position().left - (dropdown.width() - my_account.width()),
          });
          body.addClass('mobile-usermenu-is-open');
          my_account.addClass('js-active');
        }
      });
      
      //Close dropdown when mouse leaves the dropdown
      dropdown.on('mouseleave', function(){
        if(!$('.is-tablet', context).is(':visible')) { 
          dropdown.css({
            'left': 0,
          });
          body.removeClass('mobile-usermenu-is-open');
          my_account.removeClass('js-active');
        }
      });
      
      //Close dropdown when mouse leaves my-account menu-link from the sides
      my_account.on('mouseleave', function(event){
        if(!$('.is-tablet', context).is(':visible')) {
          if (event.offsetX < 0 || event.offsetX > $(this).width()) {
            dropdown.css({
              'left': 0,
            });
            body.removeClass('mobile-usermenu-is-open');
            my_account.removeClass('js-active');
          }
        }
      });
      
    }
  };

})(jQuery);