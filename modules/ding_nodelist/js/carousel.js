(function ($) {
  "use strict";

  Drupal.behaviors.ding_nodelist_carousel = {
    attach: function (context) {
      $('.ding_nodelist-carousel', context).each(function() {
        var classes = $(this).attr('class').split(' ');
        var delay = 0;
        // Find pane's ID to get its delay settings.
        $(classes).each(function(i, item){
          if (item.match(/pane\-\d+/)) {
            delay = parseInt(Drupal.settings.ding_nodelist[item]);
          }
        });

        $(this).find('.ding_nodelist-items').slick({
          nextArrow: '<i class="icon-next"></i>',
          prevArrow: '<i class="icon-prev"></i>',
          autoplay: true,
          speed: 500,
          autoplaySpeed: delay,
          responsive: true,
          dots: true,
          infinite: true,
          slidesToScroll: 1,
          slidesToShow: 1,
          customPaging: function(slick, index) {
            return '<a>' + (index + 1) + '</a>';
          }
        });
      });
    }
  };
})(jQuery);
