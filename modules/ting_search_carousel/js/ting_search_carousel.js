/**
 * @file
 * Handles the carousels loading of content and changes between tabs.
 *
 * There are two selectors to change tabs based on breaks points
 * (which is handle by the theme).
 *
 * For large screens the normal tab list (ul -> li) is used while on small
 * screens (mobile/tables) a select dropdown is used.
 */

(function ($) {
  "use strict";

  /**
   * Start the carousel when the document is ready.
   */
  $(document).ready(function() {
    $('.ting-search-carousel').each(function(i, e) {
      var carousel_wrapper = $(e).children('div[id^="ting-search-carousel-"]');
      var carousel_tabs = $(e).find('ul.ting-search-carousel-list-tabs');
      var carousel_select_tabs = $(e).find('select.ting-search-carousel-select-tabs');
      var tabs_index = $(carousel_tabs).children().length - 1;
      var autoplay = $(carousel_wrapper).attr('ting-search-carousel-autoplay') * 1000;
      var index = 0;

      // Init carousel
      $(carousel_wrapper).slick({
        arrows: true,
        infinite: true,
        slidesToShow: 7,
        slidesToScroll: 3,

        responsive: [{

          breakpoint: 1024,
          settings: {
            slidesToShow: 3
          }

        }, {

          breakpoint: 600,
          settings: {
            slidesToShow: 2,
            nextArrow: false,
            prevArrow: false
          }

        }, {

          breakpoint: 300,
          settings: "unslick" // destroys slick

        }]
      });

      update_carousel(false, false);

      // Stop tab switching if mouse enters carousel.
      var is_active = true;
      $(e).mouseenter(function() {
        is_active = false;
      }).mouseleave(function() {
        is_active = true;
      });

      if (autoplay != 0 && carousel_tabs.length > 1) {
        // Switch tabs by timer.
        setInterval(function() {
          if (is_active) {
            if (index == tabs_index) {
              update_carousel(false, false);
            }
            else {
              update_carousel(true, false);
            }
          }
        }, autoplay);
      }

      // Switch tabs on click by it.
      $(carousel_tabs).find('li').on('click', function(event) {
        event.preventDefault();
        update_carousel(false, $(this).attr('tab-index'));
      });

      $(carousel_select_tabs).on('change', function() {
        event.preventDefault();
        update_carousel(false, $(this).find(':selected').index());
      });

      // Get the list of tabs and the number of tabs in the list.
      $('.ting-search-carousel').each(function() {
        var tabsList = $(this).find('.ting-search-carousel-list-tabs');
        var childCount = tabsList.children('li').length;

        // Only do somehting if there actually is tabs
        if (childCount > 0) {

          // Get the width of the <ul> list element.
          var parentWidth = tabsList.width();

          // Calculate the width of the <li>'s.
          var childWidth = Math.floor(parentWidth / childCount);

          // Calculate the last <li> width to combined childrens width it self not
          // included.
          var childWidthLast = parentWidth - ( childWidth * (childCount -1) );

          // Set the tabs css widths.
          tabsList.children().css({'width' : childWidth + 'px'});
          tabsList.children(':last-child').css({'width' : childWidthLast + 'px'});
        }
      });



      /**
       * Function updates carousel on tab switching.
       *
       * @param bool increment
       *   Determines if we should we switch to next tab or to first.
       * @param bool|string user_selected
       *
       */
      function update_carousel(increment, user_selected) {
        var prev_index = index;

        if (user_selected) {
          index = user_selected;
        }
        else {
          index = (increment) ? index + 1 : 0;
        }

        $(carousel_tabs).find('li.index-' + prev_index).removeClass('active');
        $(carousel_tabs).find('li.index-' + index).addClass('active');

        $(carousel_select_tabs).find(':selected').removeAttr('selected');
        $(carousel_select_tabs.find('option')[index]).attr('selected', true);

        $(carousel_wrapper).slick('slickUnfilter');
        $(carousel_wrapper).slick('slickFilter', '.index-' + index);
      }
    });
  });
})(jQuery);
