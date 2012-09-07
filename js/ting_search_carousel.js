(function ($) {
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

    /**
     * @TODO: Use jquery data to create a cache, so the backend do not have to
     * be connected for shift between tabs.
     */

    $.ajax({
      type: 'get',
      url : Drupal.settings.basePath + 'ting_search_carousel/results/ajax/' + index,
      dataType : 'json',
      success : function(msg) {
        $('.rs-carousel-title').html(msg.subtitle);

        if (!carousel) {
          $('.rs-carousel-inner .ajax-loader').addClass('element-hidden');
          $('.rs-carousel .rs-carousel-runner').html(msg.content);
          carousel = $('.rs-carousel').carousel();
        }
        else {
          carousel.carousel('destroy');
          $('.rs-carousel-inner .ajax-loader').addClass('element-hidden');
          $('.rs-carousel .rs-carousel-runner').html(msg.content);
          carousel.carousel();
        }
      }
    });
  };

  $(document).ready(function() {
    // Get the carousel variable initialized.
    carousel_init(0);

    // Set up tab actions.
    $('.rs-carousel-tabs li').click(function(e) {
      e.preventDefault();

      // Move active clase.
      var current = $(this);
      current.parent().find('li').removeClass('active');
      current.addClass('active');

      // Set spinner and remove current content.
      $('.rs-carousel .rs-carousel-runner').html('');
      $('.rs-carousel-inner .ajax-loader').removeClass('element-hidden');

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
