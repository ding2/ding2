(function ($) {
  var carousel = false;
  
  Drupal.behaviors.tingSearchCarousel = {
    attach: function(context) {
      carousel_init(0);

      $('.ting-search-controller li').click(function() {
        $(this).parent().find('li').removeClass('active');
        $(this).addClass('active');

        carousel_init($(this).index());
        
        return false;
      });
    }
  }

  carousel_init = function(index) {
    $.ajax({
      type: 'get',
      url : Drupal.settings.basePath + 'ting_search_carousel/results/ajax/' + index,
      dataType : 'json',
      success : function(msg) {
        $('.ting-search-carousel .carousel-subtitle').html(msg.subtitle);
        
        if (!carousel) {
          $('.ting-search-carousel .rs-carousel .rs-carousel-runner').html(msg.content);
          carousel = $('.ting-search-carousel .rs-carousel').carousel();
        }
        else {
          carousel.carousel('destroy');
          $('.ting-search-carousel .rs-carousel .rs-carousel-runner').html(msg.content);
          carousel.carousel();
        }
      }
    });
  }
})(jQuery);
