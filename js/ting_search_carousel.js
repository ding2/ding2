(function ($) {
  "use strict";

  var carousel_request_sent = [];
  var carousel_current_index = 0;
  var carousel_cache = [];
  var carousel = false;
  var carousel_init = function(index) {

    // Set the width of the tabs according to the width of the list.
    // Based on https://github.com/andyford/equalwidths/blob/master/jquery.equalwidths.js.

    // Set variables
    var $tabsList = $('.rs-carousel-tabs ul');
    var $childCount = $tabsList.children().size();

    // Only do somehting if there actually is tabs
    if ($childCount > 0) {

      // Set the width of the <ul> list
      var parentWidth = $tabsList.width();

      // Set the width of the <li>'s
      var childWidth = Math.floor(parentWidth / $childCount);

      // Set the last <li> width to combined childrens width it self not included
      var childWidthLast = parentWidth - ( childWidth * ($childCount -1) );

      // Set the css widths
      $tabsList.children().css({'width' : childWidth + 'px'});
      $tabsList.children(':last-child').css({'width' : childWidthLast + 'px'});
    }

    // Save current index, used later on to ensure that AJAX callback insert
    // content into the right tab/page.
    carousel_current_index = index;

    // If the cache is not set, make ajax call to server else just update the
    // carousel.
    if (carousel_cache[index] === undefined) {
      // Prevent users from sending the same request more than once.
      if (carousel_request_sent[index] === undefined) {
        carousel_request_sent[index] = true;
        $.ajax({
          type: 'get',
          url : Drupal.settings.basePath + 'ting_search_carousel/results/ajax/' + index,
          dataType : 'json',
          success : function(data) {
            carousel_cache[index] = {
              'subtitle' : data.subtitle,
              'content' : data.content
            };

            // Check that the AJAX call is still validate (on the same tab).
            if (carousel_current_index == data.index) {
              if (!carousel) {
                carousel_update(index);
                carousel = $('.rs-carousel').carousel();
              }
              else {
                carousel.carousel('destroy');
                carousel_update(index);
                carousel.carousel();
              }
            }
          }
        });
      }
    }
    else {
      carousel.carousel('destroy');
      carousel_update(index);
      carousel.carousel();
    }
  };

  // Updated the carousel content.
  function carousel_update(index) {
    var data = carousel_cache[index];
    $('.rs-carousel-title').html(data.subtitle);
    $('.rs-carousel-inner .ajax-loader').addClass('element-hidden');
    $('.rs-carousel .rs-carousel-runner').html(data.content);
  }

  $(document).ready(function() {
    // Get the carousel variable initialized.
    carousel_init(0);

    // Add click event to tabs.
    $('.rs-carousel-tabs li').click(function(e) {
      e.preventDefault();

      // Move active clase.
      var current = $(this);
      current.parent().find('li').removeClass('active');
      current.addClass('active');

      // Remove current content and show spinner.
      $('.rs-carousel .rs-carousel-runner').html('');
      $('.rs-carousel-inner .ajax-loader').removeClass('element-hidden');

      // Hide navigation arrows.
      $('.rs-carousel-action-prev').hide();
      $('.rs-carousel-action-next').hide();

      carousel_init(current.index());
      return false;
    });

    // This is place inside document ready to ensure that the carousel have
    // been initialized.
    $(window).resize(function () {
      carousel.carousel('refresh');
    });
  });
})(jQuery);
