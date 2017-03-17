/*jshint forin:false, jquery:true, browser:true, indent:2, trailing:true, unused:false */
/*globals ddbasic*/
(function($) {
  'use strict';

  $(function() {
    // Make actions-container sticky when it hits header.
    var current,
        is_mobile,
        form_width,
        header_height,
        title_container_height,
        title_container_offset;

    $(window).bind('resize.account_form', function (evt) {
      if (ddbasic.breakpoint.is('mobile', 'mobile_out_account') === ddbasic.breakpoint.OUT) {
        is_mobile = false;
      }
      if (ddbasic.breakpoint.is('mobile', 'mobile_in_account') === ddbasic.breakpoint.IN) {
        is_mobile = true;
      }

      header_height = $('.site-header .topbar').height() + $('.site-header > .navigation-wrapper').height();

      $('.default-account-panel-layout').each(function(index) {
        current = $(this);
        form_width = current.find('.pane-content > form').width();
        title_container_height = current.find('.title-container').height();
        title_container_offset = current.find('.title-container').offset();

        if (is_mobile === false) {
          current.find('.actions-container').css({
            "position": "absolute",
            "top": title_container_height,
            "width": form_width
          });
        } else {
          current.find('.actions-container').css({
            "position": "relative",
            "top": 0,
            "width": form_width
          });
        }
      });

    }).triggerHandler('resize.account_form');

    // Scroll event.
    $(window).bind('scroll.actions_container', function (evt) {

      if (title_container_offset) {
        $('.default-account-panel-layout').each(function(index) {
          current = $(this);
          form_width = current.find('.pane-content > form').width();
          title_container_height = current.find('.title-container').height();
          title_container_offset = current.find('.title-container').offset();

          var scroll = $(window).scrollTop(),
              action_container_position = title_container_offset.top + title_container_height - scroll;

          if (is_mobile === false) {

            if (action_container_position < header_height) {
              current.find('.actions-container').css({
                "position": "fixed",
                "top": header_height,
              });

            } else {
              current.find('.actions-container').css({
                "position": "absolute",
                "top": title_container_height,
              });
            }

            var
              current_position = 0,
              current_offset = current.find('.actions-container').offset(),
              current_height = current.find('.actions-container').outerHeight() + 20,
              footer_offset = $('footer').offset(),
              footer_position = footer_offset.top - scroll;

            if(current_offset) {
              current_position = current_offset.top + current_height - scroll;
            }

            // If next sibling has action container.
            if (current.next('.default-account-panel-layout').find('.actions-container').length) {
              var next_offset = current.next().find('.actions-container').offset();

              if(current_offset && next_offset) {
                var next_position = next_offset.top - scroll,
                    current_top = next_position - current_height;

                if(current_position >= next_position) {
                  current.find('.actions-container').css({
                    "top": current_top,
                  });
                }
              }
            }

            // If scrolled to footer.
            if (current_position >= footer_position) {
              var current_top = footer_position - current_height;
              current.find('.actions-container').css({
                "top": current_top,
              });
            }

          }
        });
      }
    });
  });

})(jQuery);
