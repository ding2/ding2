(function($) {

  // When ready start the magic.
  $(document).ready(function () {

    // Fix Drupal administration menu in relation to the fixed navigation menu.
    var menu = $('.navigation-wrapper');
    var pos = menu.offset();
    var body_paddding = parseInt($('body').css('paddingTop'), 10);
    if (body_paddding) {
      pos.top = pos.top - body_paddding;
    }

    // Only attched the scroll event and actions to the front page.
    if ($('body').hasClass('front')) {

      // Get calculations for elements position on the page and their sizes.
      var menu_height = menu.height();
      var menu_pos_relative = (pos.top - 20) - menu_height;
      /**
      * @todo why do we need to have -20px offset ? If they are not there every
      * thing jumps.
      */

      // User to keep track of navaigation menus fixed state.
      var menu_fixed = false;

      // Hook into window scroll event (it will fire when attched if window is
      // scrolled down).
      $(window).scroll(function(){
        var top = $(window).scrollTop();

        // Figure out if we should fix position the menu or not.
        if (top > menu_pos_relative && !menu_fixed) {
          menu.addClass('fixed');
          menu.css('top', body_paddding);
          menu_fixed = true;
          ddbasic_login_pane_toggle();
        }
        else if (top < menu_pos_relative && menu_fixed) {
          menu.removeClass('fixed');
          menu.css('top', '');
          menu_fixed = false;
          ddbasic_login_pane_toggle();
        }
      });

      // Defined "global" vars used to fix login form vs. slide-down box.
      var ddbasic_login_pane_default = $('.header-inner .pane-user-login');
      var ddbasic_login_pane_toolbar = $('.pane-ding-user-frontend-ding-user-login-button');
      var ddbasic_login_state = false;

      // Remove login button (slide down), if header login is shown.
      if ($(window).scrollTop() < menu_pos_relative) {
        ddbasic_login_pane_toolbar.remove();
      }
    }
    else {  // Not the front page
      // The menu is always fixed.
      $('.navigation-wrapper').addClass('fixed');

      // Fix Drupal admin menu.
      menu.css('top', body_paddding);
    }

    // Helper functio to toggle login panes on the front page.
    function ddbasic_login_pane_toggle() {
      // Toggle the different login panes. We remove them to prevent elements
      // with the same ids etc.
      if (ddbasic_login_state) {
        ddbasic_login_pane_toolbar.remove();
        $('.header-inner').append(ddbasic_login_pane_default);
        ddbasic_login_pane_default.show();
      }
      else {
        ddbasic_login_pane_default.remove();
        $('.topbar > .topbar-inner').append(ddbasic_login_pane_toolbar);
        ddbasic_login_pane_toolbar.show();
      }
      ddbasic_login_state = !ddbasic_login_state;
    }
    
    
    // Equal heights function
    $.fn.setAllToMaxHeight = function(){
      return this.height( Math.max.apply(this, $.map( this , function(e){ return $(e).height() }) ) );
    }
    
    // Set equal heights on front page content
    $('.main-wrapper .grid-inner').setAllToMaxHeight();
    
    // Set equal heights on front page attachments
    $('.attachments-wrapper .grid-inner').setAllToMaxHeight();
    
  });
})(jQuery);