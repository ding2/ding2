!function(e,$){Drupal.behaviors.menu={attach:function(e,n){var i=$("a.topbar-link-user",e),s=$(".close-user-login",e),a=$("a.topbar-link-menu",e),o=$("a.topbar-link-search",e),l=$(".main-menu-wrapper > .main-menu > .expanded > a",e),t=$(".main-menu-wrapper > .main-menu > .expanded > .main-menu > .expanded > a",e),r=$("body",e);a.on("click",function(e){e.preventDefault(),r.toggleClass("mobile-menu-is-open"),r.removeClass("mobile-search-is-open pane-login-is-open mobile-usermenu-is-open"),r.toggleClass("overlay-is-active"),r.hasClass("mobile-menu-is-open")?r.addClass("overlay-is-active"):r.removeClass("overlay-is-active")}),o.on("click",function(e){e.preventDefault(),r.toggleClass("mobile-search-is-open"),r.removeClass("mobile-menu-is-open pane-login-is-open mobile-usermenu-is-open"),r.hasClass("mobile-search-is-open")?r.addClass("overlay-is-active"):r.removeClass("overlay-is-active")}),i.on("click",function(e){e.preventDefault(),r.toggleClass("pane-login-is-open"),r.removeClass("mobile-menu-is-open mobile-search-is-open mobile-usermenu-is-open"),r.hasClass("pane-login-is-open")?r.addClass("overlay-is-active"):r.removeClass("overlay-is-active")}),s.on("click",function(e){e.preventDefault(),r.removeClass("pane-login-is-open"),r.removeClass("overlay-is-active")}),l.on("click",function(e){$(".is-tablet").is(":visible")&&(e.preventDefault(),l.not($(this)).parent().children(".main-menu").slideUp(200),$(this).parent().children(".main-menu").slideToggle(200))}),t.on("click",function(e){$(".is-tablet").is(":visible")&&(e.preventDefault(),t.not($(this)).removeClass("open"),t.not($(this)).parent().children(".main-menu").slideUp(200),$(this).toggleClass("open"),$(this).parent().children(".main-menu").slideToggle(200))})}}}(this,jQuery);