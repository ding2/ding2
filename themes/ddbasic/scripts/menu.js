(function (scope, $) {
  // Tablet & mobile menu functions
  
  // Hide and show header on mobile
  var didScroll,
      lastScrollTop = 0,
      delta = 100,
      topbarHeight = 148;
  
  $(window).on('scroll.header', function() {
    // If mobile
    if ($('.is-mobile').is(':visible')) {
      didScroll = true;
    }
  });
  
  setInterval(function() {
    if (didScroll) {
      hasScrolled();
      didScroll = false;
    }
  }, 250);
  
  function hasScrolled() {
    var st = $(this).scrollTop();
    
    // Make sure they scroll more than delta
    if(Math.abs(lastScrollTop - st) <= delta)
        return;
    
    // If they scrolled down and are past the topbar, add class .topbar-up.
    if (st > lastScrollTop && st > topbarHeight){
        // Scroll Down
        $('header.site-header').addClass('topbar-up');
    } else {
        // Scroll Up
        if(st + $(window).height() < $(document).height()) {
          $('header.site-header').removeClass('topbar-up');
        }
    }
    
    lastScrollTop = st;
  } 
  
  
  Drupal.behaviors.menu = {
    attach: function(context, settings) {
      var topbar_link_user = $('a.topbar-link-user', context),
          close_user_login = $('.close-user-login', context),
          mobile_menu_btn = $('a.topbar-link-menu', context),
          search_btn = $('a.topbar-link-search', context),
          search_extended_btn = $('a.search-extended-button', context),
          scrolled,
          first_level_expanded = $('.main-menu-wrapper > .main-menu > .expanded > a', context),
          second_level_expanded = $('.main-menu-wrapper > .main-menu > .expanded > .main-menu > .expanded > a', context),
          body = $('body', context);
          
      mobile_menu_btn.on('click', function(evt){
        evt.preventDefault();
        body.toggleClass('mobile-menu-is-open');
        body.removeClass('mobile-search-is-open pane-login-is-open mobile-usermenu-is-open');
        body.toggleClass('overlay-is-active');
        if(body.hasClass('mobile-menu-is-open')) {
          body.addClass('overlay-is-active');
        } else {
          body.removeClass('overlay-is-active');
        }

        // Make a function
        //if(body.hasClass('mobile-menu-is-open')) {
        //  scrolled = body.scrollTop();
        //  body.css({
        //    'top': -scrolled,
        //    'position': 'fixed'
        //  });
        //} else {
        //  body.css('position', '');
        //  body.scrollTop(scrolled);
        //} 

      });
      
      search_btn.on('click', function(evt){
        evt.preventDefault();
        body.toggleClass('mobile-search-is-open');
        body.removeClass('mobile-menu-is-open pane-login-is-open mobile-usermenu-is-open');
        if(body.hasClass('mobile-search-is-open')) {
          body.addClass('overlay-is-active');
        } else {
          body.removeClass('overlay-is-active');
        }
      });
          
      topbar_link_user.on('click', function(evt) {
        evt.preventDefault();
        body.toggleClass('pane-login-is-open');
        body.removeClass('mobile-menu-is-open mobile-search-is-open mobile-usermenu-is-open');
        if(body.hasClass('pane-login-is-open')) {
          body.addClass('overlay-is-active');
        } else {
          body.removeClass('overlay-is-active');
        }
      });
      
      close_user_login.on('click', function(evt) {
        evt.preventDefault();
        body.removeClass('pane-login-is-open');
        body.removeClass('overlay-is-active');
      });
      
      first_level_expanded.on('click', function(evt) {
        if($('.is-tablet').is(':visible')) {
          evt.preventDefault();
          first_level_expanded.not($(this)).parent().children('.main-menu').slideUp(200);
          $(this).parent().children('.main-menu').slideToggle(200);
        }
      });
      
      second_level_expanded.on('click', function(evt) {
        if($('.is-tablet').is(':visible')) {
          evt.preventDefault();
          second_level_expanded.not($(this)).removeClass('open');
          second_level_expanded.not($(this)).parent().children('.main-menu').slideUp(200);
          $(this).toggleClass('open');
          $(this).parent().children('.main-menu').slideToggle(200);
        }
      });
      
      search_extended_btn.on('click', function(evt) {
        evt.preventDefault();
        body.toggleClass('extended-search-is-open');
      });
      
      // Tablet/mobile menu logout
      // Logout-link is created with after-element
      // We check if after-element is clicked by checking if clicked point has a larger y position than the menu itself
      $('.header-wrapper .navigation-inner > ul.main-menu-third-level').click(function(evt) {
        console.log('click');
        if($('.is-tablet').is(':visible')) {
          var menu_offset = $('.header-wrapper .navigation-inner > ul.main-menu-third-level').offset(),
              menu_item = $('.header-wrapper .navigation-inner > ul.main-menu-third-level > li'),
              menu_height = 0;
          
          menu_item.each(function( index ) {
            menu_height = menu_height + $(this).outerHeight();
          });
          if (evt.offsetY > (menu_offset.top + menu_height)) {
            window.location.href = "/user/logout";
          }
        }
      });
    }
  };
  
  Drupal.behaviors.second_level_menu = {
    attach: function(context, settings) {
      $('ul.main-menu-second-level').flexMenu({
          linkText: 'Mere...',
          popupAbsolute: false,
          cutoff: 1
      });
    }
  };
  

})(this, jQuery);