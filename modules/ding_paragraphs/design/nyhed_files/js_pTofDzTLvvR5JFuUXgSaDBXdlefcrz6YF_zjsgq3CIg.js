/* Flexmenu plugin with B14 changes

  jQuery.flexMenu 1.2
	https://github.com/352Media/flexMenu
	Description: If a list is too long for all items to fit on one line, display a popup menu instead.
	Dependencies: jQuery, Modernizr (optional). Without Modernizr, the menu can only be shown on click (not hover). */

(function (factory) {
	if (typeof define === 'function' && define.amd) {
		// AMD. Register as an anonymous module.
		define(['jquery'], factory);
	} else {
		// Browser globals
		factory(jQuery);
	}
}(function ($) {
	var flexObjects = [], // Array of all flexMenu objects
		resizeTimeout;
	// When the page is resized, adjust the flexMenus.
	function adjustFlexMenu() {
		$(flexObjects).each(function () {
			$(this).flexMenu({
				'undo' : true
			}).flexMenu(this.options);
		});
	}
	function collapseAllExcept($menuToAvoid) {
		var $activeMenus,
			$menusToCollapse;
		$activeMenus = $('li.flexMenu-viewMore.active');
		$menusToCollapse = $activeMenus.not($menuToAvoid);
		$menusToCollapse.removeClass('active').find('> ul').hide();
	}
	$(window).resize(function () {
		clearTimeout(resizeTimeout);
		resizeTimeout = setTimeout(function () {
			adjustFlexMenu();
		}, 200);
	});
	$.fn.flexMenu = function (options) {
		var checkFlexObject,
			s = $.extend({
				'threshold' : 2, // [integer] If there are this many items or fewer in the list, we will not display a "View More" link and will instead let the list break to the next line. This is useful in cases where adding a "view more" link would actually cause more things to break  to the next line.
				'cutoff' : 2, // [integer] If there is space for this many or fewer items outside our "more" popup, just move everything into the more menu. In that case, also use linkTextAll and linkTitleAll instead of linkText and linkTitle. To disable this feature, just set this value to 0.
				'linkText' : 'More', // [string] What text should we display on the "view more" link?
				'linkTitle' : 'View More', // [string] What should the title of the "view more" button be?
				'linkTextAll' : 'Menu', // [string] If we hit the cutoff, what text should we display on the "view more" link?
				'linkTitleAll' : 'Open/Close Menu', // [string] If we hit the cutoff, what should the title of the "view more" button be?
				'showOnHover' : true, // [boolean] Should we we show the menu on hover? If not, we'll require a click. If we're on a touch device - or if Modernizr is not available - we'll ignore this setting and only show the menu on click. The reason for this is that touch devices emulate hover events in unpredictable ways, causing some taps to do nothing.
				'popupAbsolute' : true, // [boolean] Should we absolutely position the popup? Usually this is a good idea. That way, the popup can appear over other content and spill outside a parent that has overflow: hidden set. If you want to do something different from this in CSS, just set this option to false.
				'undo' : false // [boolean] Move the list items back to where they were before, and remove the "View More" link.
			}, options);
		this.options = s; // Set options on object
		checkFlexObject = $.inArray(this, flexObjects); // Checks if this object is already in the flexObjects array
		if (checkFlexObject >= 0) {
			flexObjects.splice(checkFlexObject, 1); // Remove this object if found
		} else {
			flexObjects.push(this); // Add this object to the flexObjects array
		}
		return this.each(function () {
			var $this = $(this),
				$items = $this.find('> li'),
				$self = $this,
				$firstItem = $items.first(),
				$lastItem = $items.last(),
				numItems = $this.find('li').length,
				firstItemTop = Math.floor($firstItem.offset().top),
				firstItemHeight = Math.floor($firstItem.outerHeight(true)),
				$lastChild,
				keepLooking,
				$moreItem,
				$moreLink,
				numToRemove,
				allInPopup = false,
				$menu,
				i,
				// B14 variables
				$moreMenu,
				more_link;

			function needsMenu($itemOfInterest) {
				var result = (Math.ceil($itemOfInterest.offset().top) >= (firstItemTop + firstItemHeight)) ? true : false;
				// Values may be calculated from em and give us something other than round numbers. Browsers may round these inconsistently. So, let's round numbers to make it easier to trigger flexMenu.
				return result;
			}
			if (needsMenu($lastItem) && numItems > s.threshold && !s.undo && $this.is(':visible')) {
				var $popup = $('<ul class="flexMenu-popup"' + ((s.popupAbsolute) ? ' position: absolute;' : '') + '"></ul>'),
				// Move all list items after the first to this new popup ul
					firstItemOffset = $firstItem.offset().top;
				for (i = numItems; i > 1; i--) {
					// Find all of the list items that have been pushed below the first item. Put those items into the popup menu. Put one additional item into the popup menu to cover situations where the last item is shorter than the "more" text.
					$lastChild = $this.find('> li:last-child');
					keepLooking = (needsMenu($lastChild));
					$lastChild.appendTo($popup);
					// If there only a few items left in the navigation bar, move them all to the popup menu.
					if ((i - 1) <= s.cutoff) { // We've removed the ith item, so i - 1 gives us the number of items remaining.
						$($this.children().get().reverse()).appendTo($popup);
						allInPopup = true;
						break;
					}
					if (!keepLooking) {
						break;
					}
				}
				if (allInPopup) {
					$this.append('<li class="flexMenu-viewMore flexMenu-allInPopup"><a href="#" title="' + s.linkTitleAll + '">' + s.linkTextAll + '</a></li>');
				} else {
					$this.append('<li class="flexMenu-viewMore"><a href="#">' + s.linkText + '</a></li>');
				}

				$moreItem = $this.find('> li.flexMenu-viewMore');
				/// Check to see whether the more link has been pushed down. This might happen if the link immediately before it is especially wide.
				if (needsMenu($moreItem)) {
					$this.find('> li:nth-last-child(2)').appendTo($popup);
				}
				// Our popup menu is currently in reverse order. Let's fix that.
				$popup.children().each(function (i, li) {
					$popup.prepend(li);

				});
				$moreItem.append($popup);
				$moreMenu = $('ul.flexMenu-popup');

				// B14 change - added flex-container
				$moreMenu.wrap( "<div class='flex-container'></div>" );


				//
				// Lines below commentet out by B14, so we can use our own hover
				// functionality, uses classes and expands the hitbox.
				// $moreLink.click(function (e) {
				//	// Collapsing any other open flexMenu
				//	collapseAllExcept($moreItem);
				//	//Open and Set active the one being interacted with.
				//	$popup.toggle();
				//	$moreItem.toggleClass('active');
				//	e.preventDefault();
				//});
				//if (s.showOnHover && (typeof Modernizr !== 'undefined') && !Modernizr.touch) { // If requireClick is false AND touch is unsupported, then show the menu on hover. If Modernizr is not available, assume that touch is unsupported. Through the magic of lazy evaluation, we can check for Modernizr and start using it in the same if statement. Reversing the order of these variables would produce an error.
				//	$moreLink.hover(
				//		function () {
				//			$popup.show();
				//			$(this).addClass('active');
				//		},
				//		function () {
				//			$popup.hide();
				//			$(this).removeClass('active');
				//		});
				//}

				// B14 changes below - hover function
				more_link = $('.flexMenu-viewMore'),
        more_link.bind('mouseenter', function(evt) {
          $(this).addClass('active');
          $(this).removeClass('in-active');
        });
        $('.pane-menu-block-main-menu-second-level').bind('mouseleave', function(evt) {
          $(this).find('.flexMenu-viewMore').addClass('in-active');
          $(this).find('.flexMenu-viewMore').removeClass('active');
        });




			} else if (s.undo && $this.find('ul.flexMenu-popup')) {
				$menu = $this.find('ul.flexMenu-popup');
				numToRemove = $menu.find('li').length;
				for (i = 1; i <= numToRemove; i++) {
					$menu.find('> li:first-child').appendTo($this);
				}
				$menu.remove();
				$this.find('> li.flexMenu-viewMore').remove();
			}
		});
	};
}));
;
(function($) {
  "use strict";

  // Add classes for touch and no touch.
  $(function () {
    var ua = navigator.userAgent.toLowerCase();
    if (
      /(ipad)/.exec(ua) ||
      /(iphone)/.exec(ua) ||
      /(android)/.exec(ua) ||
      /(windows phone)/.exec(ua)
    ) {
      $('body').addClass('has-touch');
    } else {
      $('body').addClass('no-touch');
    }
  });

}(jQuery));
;
/*jshint forin:false, jquery:true, browser:true, indent:2, trailing:true, unused:false */
(function($) {
  'use strict';

  /**
   * Toggle opening hours
   */
  function toggle_opening_hours() {
    // Create toggle link
    $('.js-opening-hours-toggle-element').each(function () {
      var
        $this = $(this),
        text = [];

      if ($this.attr('data-extended-title')) {
        $('th', this).slice(1).each(function () {
          text.push($(this).text());
        });
      } else {
        text.push(Drupal.t('Opening hours'));
      }

      $('<a />', {
        'class' : 'opening-hours-toggle js-opening-hours-toggle js-collapsed collapsed',
        'href' : Drupal.t('#toggle-opening-hours'),
        'text' : text.join(', ')
      }).insertBefore(this);
    });

    // Set variables
    var element = $('.js-opening-hours-toggle');
    var siteHeader = $('.site-header');

    // Attach click
    element.on('click touchstart', function(event) {
      // Store clicked element for later use
      var element = this;

      // Toggle
      $(this).next('.js-opening-hours-toggle-element').slideToggle('fast', function() {
        // Toggle class
        $(element)
          .toggleClass('js-collapsed js-expanded collapsed')

          // Remove focus from link
          .blur();
      });

      // Prevent default (href)
      event.preventDefault();
    });

    // Expand opening hours on library pages.
    if (Drupal.settings.ding_ddbasic_opening_hours && Drupal.settings.ding_ddbasic_opening_hours.expand_on_library) {
      element.triggerHandler('click');
    }
  }

  // When ready start the magic.
  $(document).ready(function () {
    // Toggle opening hours.
    toggle_opening_hours();

    // Check an organic group and library content.
    // If a group does not contain both news and events
    // then add an additional class to the content lists.
    [
      '.ding-group-news,.ding-group-events',
      '.ding-library-news,.ding-library-events'
    ].forEach(function(e) {
        var selector = e;
        $(selector).each(function() {
          if ($(this).parent().find(selector).size() < 2) {
            $(this).addClass('js-og-single-content-type');
          }
      });
    });
  });

  // Submenus
  Drupal.behaviors.ding_submenu = {
    attach: function(context, settings) {

      $('.sub-menu-title', context).click(function(evt) {
        if ($('.is-tablet').is(':visible')) {
          evt.preventDefault();
          $(this).parent().find('ul').slideToggle("fast");
        }
      });
    }
  };

})(jQuery);
;
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
;
/*jshint forin:false, jquery:true, browser:true, indent:2, trailing:true, unused:false */
(function (scope, $) {
  'use strict';

  var
    /**
     * Holder for the breakpoint identifiers.
     */
    _bpi = {};

  if (scope.ddbasic === undefined) {
    scope.ddbasic = {};
  }

  /**
   * Helper for only running code once when entering or leaving a breakpoint.
   */
  scope.ddbasic.breakpoint = {
    /**
     * Moving into the breakpoint.
     */
    IN: true,

    /**
     * Moving out of the breakpoint.
     */
    OUT: false,

    /**
     * Breakpoint already tested.
     * Meaning it's not changing "state".
     */
    NOP: null,

    /**
     * Check if the specific breakpoint is activated.
     *
     * @param string breakpoint
     *   The breakpoint to check for.
     * @param string identifier
     *   The identifier/context.
     *
     * @return mixed
     *   Returns if the breakpoint is activated (IN), deactivated (OUT) or
     *   it hasn't changed (NOP), in reference to the identifier.
     */
    is: function (breakpoint, identifier) {
      var
        $checker = $('.is-' + breakpoint),
        result = $checker.is(':visible');

      if (identifier === undefined) {
        return result ? this.IN : this.OUT;
      }

      if (_bpi[identifier] !== result) {
        _bpi[identifier] = result;
        return result ? this.IN : this.OUT;
      }

      return this.NOP;
    },

    /**
     * Reset an identifier.
     *
     * @param string identifier
     *   The identifier/context.
     */
    reset: function (identifier) {
      delete _bpi[identifier];
    }
  };

})(this, jQuery);
;
/*jshint forin:false, jquery:true, browser:true, indent:2, trailing:true, unused:false */
(function (scope, $) {
  'use strict';

  // Hide and show header on mobile
  var last_scroll_top = 0,
      scroll_delta = 100,
      topbar_height = 148;
  $(window).on('scroll.header', function() {
    // If mobile
    if (ddbasic.breakpoint.is('mobile')) {
      var st = $(window).scrollTop();

      // Make sure they scroll more than delta.
      if(Math.abs(last_scroll_top - st) <= scroll_delta) {
        return;
      }

      // If they scrolled down and are past the topbar, add class .topbar-up.
      if(st > last_scroll_top && st > topbar_height) {
          // Scroll Down
          $('header.site-header').addClass('topbar-up');
      } else {
          // Scroll Up
          if(st + $(window).height() < $(document).height()) {
            $('header.site-header').removeClass('topbar-up');
          }
      }

      last_scroll_top = st;
    }
  });

  $(window).on('dingpopup-close', function () {
    $('body').removeClass('pane-login-is-open overlay-is-active');
  });

  /**
   * Menu functionality.
   */
  Drupal.behaviors.menu = {
    attach: function(context, settings) {
      var topbar_link_user = $('a.topbar-link-user', context),
          close_user_login = $('.close-user-login', context),
          mobile_menu_btn = $('a.topbar-link-menu', context),
          search_btn = $('a.topbar-link-search', context),
          search_extended_btn = $('a.search-extended-button', context),
          first_level_expanded = $('.main-menu-wrapper > .main-menu > .expanded > a', context),
          second_level_expanded = $('.main-menu-wrapper > .main-menu > .expanded > .main-menu > .expanded > a', context),
          body = $('body');

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
      // Logout-link is created with after-element.
      // We check if after-element is clicked by checking if clicked point has a
      // larger y position than the menu itself.
      $('.header-wrapper .navigation-inner > ul.main-menu-third-level').click(function(evt) {
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

  /**
   * Add flex menu to second level.
   */
  Drupal.behaviors.second_level_menu = {
    attach: function(context, settings) {
      $('ul.main-menu-second-level').flexMenu({
        linkText: Drupal.t('More') + '...',
        popupAbsolute: false,
        cutoff: 1
      });
    }
  };

})(this, jQuery);
;
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
;
/*jshint forin:false, jquery:true, browser:true, indent:2, trailing:true, unused:false */
(function($) {
  'use strict';

  /**
   * Slide toggle footer menus
   */
  Drupal.behaviors.mobile_footer = {
    attach: function(context, settings) {
      $('.footer .pane-title', context).click(function(){
        $(this).toggleClass('open');
        $(this).parent().find(".pane-content").slideToggle("fast");
        $('html, body').animate({
            scrollTop: $(this).offset().top - 180
        }, 300);
      });
    }
  };
})(jQuery);
;
/*jshint forin:false, jquery:true, browser:true, indent:2, trailing:true, unused:false */
/*globals ddbasic*/

(function($) {
  'use strict';

  Drupal.behaviors.misc = {
    attach: function(context, settings) {
      //Topbar openinghours button.
      var opening_hours_button = $('.topbar-menu a.topbar-link-opening-hours', context);
      opening_hours_button.on('click', function(event){
        if (pane_opening_hours.length > 0) {
          event.preventDefault();
          $('html, body').animate({
            scrollTop: pane_opening_hours.offset().top - 164}, 400);
        }
      });

      //Make sure facet browser is open when item is selected
      var facet_items = $('.js-facet-browser-toggle input[type=checkbox]');
      facet_items.each(function(){
        var $this = $(this);
        if($this.is(':checked')) {
          $this
            .closest('fieldset')
            .removeClass('collapsed');
        }
      });

      //Close messages
      var pane_messages = $('.pane-page-messages'),
          close_messages_button = $('.close-messages-button', context);

      close_messages_button.on('click', function(){
        pane_messages.slideUp('fast');
      });
    }
  };

  // Minimize ask tab on moblie
  $(function () {
    $(window).bind('resize.ding_ask_tab', function (evt) {
      switch (ddbasic.breakpoint.is('mobile', 'ask_tab')) {
        case ddbasic.breakpoint.IN:
          $('.ask-vopros-tab').addClass('minimized');
        break;
      }
    });
    setTimeout(function(){
      $(window).triggerHandler('resize.ding_ask_tab');
    }, 4000);
  });

})(jQuery);
;
/*jshint forin:false, jquery:true, browser:true, indent:2, trailing:true, unused:false */
(function($) {
  'use strict';

  // Set height for event teasers.
  $(window).bind('resize.ding_event_teaser', function (evt) {
    var ding_event_teaser_height = 0;

    $('.node-ding-event.node-teaser').each(function (delta, view) {
      ding_event_teaser_height = $(this).find('.inner').outerHeight();
      $(this).height(ding_event_teaser_height);
    });
  });

  // Call resize function when images are loaded.
  Drupal.behaviors.ding_event_teaser_loaded = {
    attach: function(context, settings) {
      $('.view-ding-event .view-elements').imagesLoaded( function() {
        $(window).triggerHandler('resize.ding_event_teaser');
      });
    }
  };

  // Hover functions for event teasers.
  Drupal.behaviors.ding_event_teaser_hover = {
    attach: function(context, settings) {
      var title_and_lead_height,
          hovered;
      $('.node-ding-event.node-teaser', context).mouseenter(function() {
        // Set height for title and lead text.
        title_and_lead_height = $(this).find('.title').outerHeight(true) + $(this).find('.field-name-field-ding-event-lead .field-items').outerHeight(true) + 20;
        $(this).find('.title-and-lead').css('min-height', title_and_lead_height);

        // Set timeout to make shure element is still above while it animates
        // out.
        hovered = $(this);
        setTimeout(function(){
          $('.node-ding-event.node-teaser').removeClass('is-hovered');
          hovered.addClass('is-hovered');
        }, 300);
      });
      $('.node-ding-event.node-teaser', context).mouseleave(function() {
         $(this).find('.title-and-lead').css('min-height', '');
      });
    }
  };

})(jQuery);
;
/*jshint forin:false, jquery:true, browser:true, indent:2, trailing:true, unused:false */
/*globals ddbasic*/
(function($) {
  'use strict';

  /**
   * Hover first item in view ding news with class "first-child-large"
   */
  Drupal.behaviors.hover_view_ding_news_first_child_large = {
    attach: function(context, settings) {
      var text_element_height;
      $('.view-ding-news.first-child-large .views-row:first-child', context).mouseenter(function() {
        if(!ddbasic.breakpoint.is('mobile')) {
          text_element_height = $(this).outerHeight() - $(this).find('.news-text').outerHeight();
          $(this).find('.field-name-field-ding-news-lead').height(text_element_height);
        }
      });
      $('.view-ding-news.first-child-large .views-row:first-child', context).mouseleave(function() {
        if(!ddbasic.breakpoint.is('mobile')) {
          $(this).find('.field-name-field-ding-news-lead').height(0);
        }
      });
    }
  };

})(jQuery);
;
/*jshint forin:false, jquery:true, browser:true, indent:2, trailing:true, unused:false */
/*globals ddbasic*/
(function($) {
  'use strict';

  // Ting search results, filter styling.
  $(function () {
    $("<div class='expand-search'>" + Drupal.t('Limit search to') + "</div>").insertAfter($( ".pane-search-result-count"));
    $('.page-search-ting').find('.mobile-hide').wrapAll("<div class='hide-wrap'></div>");

    $('.expand-search').click(function(){
        $(this).toggleClass('expanded');
        $(this).parent().find('.hide-wrap').slideToggle("fast");
    });
  });

  // Hover functions for ting object teasers.
  function ting_teaser_hover(element_to_hover){
    element_to_hover.mouseenter( function() {
      if($('body').hasClass('has-touch')) {
        return;
      }
      var hovered = $(this),
          window_width = $(window).width(),
          position_of_hovered = hovered.offset();

      // If hovered element is left of window center.
      if(position_of_hovered.left < (window_width / 2)) {
        hovered.addClass('move-right');
      } else {
        hovered.addClass('move-left');
      }

      // Set timeout to make shure element is still above while it animates out.
      setTimeout(function(){
        element_to_hover.removeClass('is-hovered');
        hovered.addClass('is-hovered');

      }, 300);
    });
    element_to_hover.mouseleave(function() {
      $(this).removeClass('move-left');
      $(this).removeClass('move-right');
    });
  }
  Drupal.behaviors.ding_ting_teaser_hover = {
    attach: function(context, settings) {
      ting_teaser_hover($('.ting-object.view-mode-teaser > .inner', context));
    }
  };

  // Shorten ting object teaser titles
  Drupal.behaviors.ding_ting_teaser_short_title = {
    attach: function(context, settings) {
      $('.ting-object.view-mode-teaser > .inner .field-name-ting-title h2').each(function(){
        this.innerText = ellipse(this.innerText, 45);
      });
    }
  };

  function ellipse(str, max){
    return str.length > (max - 3) ? str.substring(0,max-3) + '...' : str;
  }

  // Ting teaser image proportions.
  function adapt_images(images){
    $(images).each(function() {
      var image = new Image();
      image.src = $(this).attr("src");
      var that = $(this);
      image.onload = function() {
        var img_height = this.height;
        var img_width = this.width;
        var img_format = img_width/img_height;
        // Format of our container.
        var standart_form = 0.7692;

        if(img_format >= standart_form) {
          that.addClass('scale-height');
        } else if (img_width < img_height) {
          that.addClass('scale-width');
        }
      };
    });
  }
  Drupal.behaviors.ding_ting_teaser_image_width = {
    attach: function(context, settings) {
      adapt_images($('.ting-object.view-mode-teaser img'));
    }
  };

  // Ting teaser mobile
  Drupal.behaviors.ding_ting_object_list_mobile = {
    attach: function(context, settings) {
      $('.js-toggle-info-container', context).click(function(){
        if(ddbasic.breakpoint.is('mobile')) {
          $(this)
            .toggleClass('is-open')
            .closest('.ting-object-right').find('.info-container')
              .slideToggle('fast');
        }
      });
    }
  };

  // Ting scroll to other formats
  Drupal.behaviors.ding_ting_object_scrollto_other_formats = {
    attach: function(context, settings) {
      var other_formats_btn = $('a.other-formats', context),
          pane_ting_object_types = $('.pane-ting-ting-object-types', context),
          html = $('html, body');

      other_formats_btn.on('click', function(event){
        event.preventDefault();
        html.animate({
          scrollTop: pane_ting_object_types.offset().top - 148}, 400);
      });

    }
  };

})(jQuery);
;
/*jshint forin:false, jquery:true, browser:true, indent:2, trailing:true, unused:false */
/*globals ddbasic*/
(function($) {
  'use strict';

  // Group teasers and remove extra teasers in event max-two-rows views when
  // other teasers has image.
  $(function () {
    var masonry_is_active = false;

    $(window).bind('resize.ding_event_grouping', function (evt) {
      if (ddbasic.breakpoint.is('mobile', 'mobile_out_reset') === ddbasic.breakpoint.OUT) {
        ddbasic.breakpoint.reset('event_grouping');
      }

      switch (ddbasic.breakpoint.is('tablet', 'event_grouping')) {
        case ddbasic.breakpoint.IN:
          if (ddbasic.breakpoint.is('mobile') === ddbasic.breakpoint.OUT) {
            $('.view-ding-event.max-two-rows .group-row .views-row').unwrap();

            var row_count = $('.view-ding-event.max-two-rows .views-row').length,
                teaser_number = 0;

            $('.view-ding-event.max-two-rows .views-row').each(function(index) {

              // A row with an image counts for 2.
              if ($(this).find('.event-list-image').length) {
                teaser_number = teaser_number + 2;
              }
              else {
                teaser_number = teaser_number + 1;
              }

              // Remove redundant rows.
              if (row_count <= 6) {
                if (teaser_number > 6) {
                  $(this).addClass('hide');
                }
              } else if (row_count <= 12) {
                if (teaser_number > 12) {
                  $(this).addClass('hide');
                }
              } else if(teaser_number > 18) {
                $(this).addClass('hide');
              }
            });

            $('.view-ding-event.max-two-rows .view-elements').masonry({
              layoutInstant: false,
              itemSelector: '.views-row',
              columnWidth: '.grid-sizer',
              gutter: '.grid-gutter',
              percentPosition: true,
            })
            .on('layoutComplete', function () {
              $(this).addClass('is-masonry-complete');
            });

            masonry_is_active = true;
          }
          break;

        case ddbasic.breakpoint.OUT:
          if  (masonry_is_active === true) {
            $('.view-ding-event.max-two-rows .view-elements').masonry('destroy');
          }

          var row_count = Drupal.settings.number_of_events,
              teaser_number = 0,
              view_inner = $('.view-ding-event.max-two-rows .view-elements-inner'),
              first_group_element = '<div class="first-group-row group-row"></div>',
              second_group_row = false,
              second_group_element = '<div class="second-group-row group-row"></div>',
              third_group_row = false,
              third_group_element = '<div class="third-group-row group-row"></div>',
              current_group,
              current;

          // Frontpge view has special setting because row_count is a variable
          // set in theme-settings.
          $('.view-ding-event.max-two-rows.frontpage-view .views-row').each(function(index) {
            // First element.
            if (teaser_number === 0) {
              $(view_inner).append(first_group_element);
              current_group = $('.first-group-row');
            }

            // A row with an image counts for 2.
            if ($(this).find('.event-list-image').length) {
              teaser_number = teaser_number + 2;
            }
            else {
              teaser_number = teaser_number + 1;
            }

            if (row_count > 6) {
              // Start second group row.
              if (teaser_number > 6 && second_group_row === false) {
                $(view_inner).append(second_group_element);
                current_group = $('.second-group-row');

                // Reset count to prevent count error if previous group is not
                // filled up.
                teaser_number = 6;
                if ($(this).find('.event-list-image').length) {
                  teaser_number = teaser_number + 2;
                }
                else {
                  teaser_number = teaser_number + 1;
                }

                second_group_row = true;
              }
            }

            if (row_count > 12) {
              // Start third group row
              if (teaser_number > 12 && third_group_row === false) {
                $(view_inner).append(third_group_element);
                current_group = $('.third-group-row');

                // Reset count to prevent count error if previous group is not
                // filled up.
                teaser_number = 12;
                if ($(this).find('.event-list-image').length) {
                  teaser_number = teaser_number + 2;
                }
                else {
                  teaser_number = teaser_number + 1;
                }

                third_group_row = true;
              }

            }

            // Append rows.
            $(current_group).append($(this));

            // Remove redundant rows.
            if (row_count <= 6) {
              if (teaser_number > 6) {
                $(this).addClass('hide');
              }
            } else if (row_count <= 12) {
              if (teaser_number > 12) {
                $(this).addClass('hide');
              }
            } else if(teaser_number > 18) {
              $(this).addClass('hide');
            }

          });

          // Not frontpage views.
          $('.view-ding-event.max-two-rows.not-frontpage-view .views-row').each(function(index) {
            // First element.
            if (teaser_number === 0) {
              $(view_inner).append(first_group_element);
              current_group = $('.first-group-row');
            }

            // A row with an image counts for 2.
            if ($(this).find('.event-list-image').length) {
              teaser_number = teaser_number + 2;
            }
            else {
              teaser_number = teaser_number + 1;
            }

            // Append rows.
            $(current_group).append($(this));


            if (teaser_number > 6) {
              $(this).addClass('hide');
            }


          });
          $('.view-ding-event.max-two-rows .view-elements .view-elements-inner .group-row').each(function() {
            var rows = $(this).children('.views-row'),
                row_total = 0,
                row_order = 0,
                has_image,
                doc_style = document.documentElement.style;

            // Check if number of rows is less than 4 and if flex wrap is supportet
            if (rows.length < 4 || !('flexWrap' in doc_style)) {
              $(this).addClass('no-flex');
            }
            else {
              $(this).addClass('flex');
              rows.each(function(index) {
                if ($(this).children('.node-teaser').hasClass('has-image')) {
                  row_total = row_total + 2;
                  has_image = true;
                } else {
                  row_total = row_total + 1;
                  has_image = false;
                }

                // If odd and has image.
                if (row_total % 2 === 1 && has_image === true) {
                  row_order = row_order - 1;
                }
                else {
                  row_order = row_order + 1;
                }

                // Set css order on rows.
                $(this).attr('style',  'order:' + row_order);

              });
            }
          });
          break;
      }

      switch (ddbasic.breakpoint.is('mobile', 'event_grouping_mobile')) {
        case ddbasic.breakpoint.IN:
          if (masonry_is_active === true) {
            $('.view-ding-event.max-two-rows .view-elements').masonry('destroy');
          }
          break;
      }
    });
  });

  // Call resize when images are loaded.
  Drupal.behaviors.ding_event_grouping = {
    attach: function(context, settings) {
      $('.view-ding-event.max-two-rows .view-elements .view-elements-inner', context).imagesLoaded( function() {
        $(window).triggerHandler('resize.ding_event_grouping');
      });
    }
  };

  // Update masonry on resize.
  $(window).bind('resize.ding_event_masonry', function (evt) {
    handle_ding_event_masonry();
  });

  // Add masonry to event views.
  function handle_ding_event_masonry(force) {
    if (force === true) {
      ddbasic.breakpoint.reset('event_masonry');
    }

    switch (ddbasic.breakpoint.is('mobile', 'event_masonry')) {
      case ddbasic.breakpoint.IN:
        var element = $('.js-masonry-view');
        if (element.data('masonry')) {
          element.masonry('destroy');
        }
        break;
      case ddbasic.breakpoint.OUT:
        $('.js-masonry-view').masonry({
          layoutInstant: false,
          itemSelector: '.views-row',
          columnWidth: '.grid-sizer',
          gutter: '.grid-gutter',
          percentPosition: true,
        })
        .on('layoutComplete', function () {
          $(this).addClass('is-masonry-complete');
        });
        break;
    }
  }

  // Call masonry resize when images are loaded.
  Drupal.behaviors.ding_event_teaser_masonry = {
    attach: function(context, settings) {
      $('.js-masonry-view', context).imagesLoaded( function() {
        handle_ding_event_masonry(true);
      });
    }
  };

  $(function () {
    // Set and destroy slick slider on views.
    var event_view_rows = $(".view-ding-event.max-two-rows .view-elements-inner .views-row");
    $(window).bind('resize.ding_view_slide', function (evt) {
      switch (ddbasic.breakpoint.is('mobile', 'view_slide')) {
        case ddbasic.breakpoint.IN:
          // Event max-two-rows view
          for (var i = 0; i < event_view_rows.length; i+=2) {
            // wrap slides in containers of 2.
            event_view_rows.slice(i, i+2).wrapAll("<div class='two-slides'></div>");
          }
          $('.view-ding-event.max-two-rows .view-elements-inner').slick({
            arrows: true,
            infinite: false,
            slidesToScroll: 1,
            slidesToShow: 1
          });

          // Slide-on-mobile views
          $('.view.slide-on-mobile .view-content').slick({
            arrows: true,
            infinite: false,
            slidesToScroll: 1,
            slidesToShow: 1
          });

          break;
        case ddbasic.breakpoint.OUT:
          // Event max-two-rows view.
          $('.view-ding-event.max-two-rows .view-elements-inner.slick-initialized').slick('unslick');
          $('.two-slides .views-row').unwrap();

          var doc_style = document.documentElement.style;

          if (event_view_rows.length > 3 || ('flexWrap' in doc_style)) {
            $('.view-ding-event.max-two-rows').removeClass('no-flex');
            $('.view-ding-event.max-two-rows').addClass('flex');
          }

          // Slide-on-mobile views.
          $('.view.slide-on-mobile .view-content.slick-initialized').slick('unslick');

          break;
      }
    }).triggerHandler('resize.ding_view_slide');
  });

  Drupal.behaviors.date_popup_auto_submit = {
    attach: function(context) {
      // Remove keyup auto-submit from date popup
      $('.ctools-auto-submit-full-form .form-type-date-popup input:text', context)
        .not('.ctools-auto-submit-exclude').unbind('keydown keyup');
    }
  };

})(jQuery);
;
/*jshint forin:false, jquery:true, browser:true, indent:2, trailing:true, unused:false */
(function($) {
  'use strict';

  // Notification count
  Drupal.behaviors.ding_p2_notifications = {
    attach: function(context, settings) {
      var count = 0,
        notification_count = $('.pane-notifications-top-menu .notifications-count');

      if (notification_count.length) {
        notification_count.each(function(index) {
          count = count + parseInt($(this).text(), 10);
        });

        if ($('.topbar-link-user-account .topbar-link-user-account')) {
          $('.topbar-link-user-account .topbar-link-user-account', context).append('<div class="notification-count">' + count + '</div>');
        }
      }
    }
  };
})(jQuery);
;
/*jshint forin:false, jquery:true, browser:true, indent:2, trailing:true, unused:false */
(function($) {
  'use strict';

  // P2 Ding list
  Drupal.behaviors.ding_p2_list = {
    attach: function(context, settings) {
      $('.field-name-ding-entity-buttons .ding-list-add-button .trigger').on('click', function(evt) {
        evt.preventDefault();
        $(this).parent().addClass('open-overlay');
      });
      $('.field-name-ding-entity-buttons .ding-list-add-button .close').on('click', function(evt) {
        evt.preventDefault();
        $(this).parents('.ding-list-add-button').removeClass('open-overlay');
      });
    }
  };

  // Close all open add overlays when the popup is closed.
  $(window).on('dingpopup-close', function () {
    $('.ding-list-add-button').removeClass('open-overlay');
  });

})(jQuery);
;
