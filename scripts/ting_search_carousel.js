(function ($) {
  var carousel = false;
  
  Drupal.behaviors.tingSearchCarousel = {
    attach: function(context) {
      carousel_init(0);

      $('.rs-carousel-tabs li').click(function() {
        $(this).parent().find('li').removeClass('active');
        $(this).addClass('active');        

        carousel_init($(this).index());
        
        return false;
      });
    }
  }

  carousel_init = function(index) {

    // Set the width of the tabs according to the width of the list.
    // Based on https://github.com/andyford/equalwidths/blob/master/jquery.equalwidths.js.
    
    // Set variables
    var $tabsList = $('.rs-carousel-tabs ul');
    var $childCount = $tabsList.children().size();

    // Only do somehting if there actually is tabs
    if ($childCount > 0) {
      
      // Set the width of the <ul> list
      parentWidth = $tabsList.width();
      
      // Set the width of the <li>'s
      childWidth = Math.floor(parentWidth / $childCount);
      
      // Set the last <li> width to combined childrens width it self not included
      childWidthLast = parentWidth - ( childWidth * ($childCount -1) );
      
      // Set the css widths
      $tabsList.children().css({ 'width' : childWidth + 'px' });
      $tabsList.children(':last-child').css({ 'width' : childWidthLast + 'px' });
      
    }

    
    $.ajax({
      type: 'get',
      url : Drupal.settings.basePath + 'ting_search_carousel/results/ajax/' + index,
      dataType : 'json',
      success : function(msg) {
        $('.rs-carousel-title').html(msg.subtitle);
        
        if (!carousel) {
          $('.rs-carousel .rs-carousel-runner').html(msg.content);
          carousel = $('.rs-carousel').carousel();
        }
        else {
          carousel.carousel('destroy');
          $('.rs-carousel .rs-carousel-runner').html(msg.content);
          carousel.carousel();
        }
      }
    });
  }
})(jQuery);
