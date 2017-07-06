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
              itemSelector: '.views-row',
              columnWidth: '.grid-sizer',
              gutter: '.grid-gutter',
              percentPosition: true,
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
          itemSelector: '.views-row',
          columnWidth: '.grid-sizer',
          gutter: '.grid-gutter',
          percentPosition: true,
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
