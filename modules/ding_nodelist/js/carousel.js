(function ($) {
  $(document).ready(function () {
    $('.ding_nodelist-carousel').each(function() {
      var classes = $(this).attr('class').split(' ');
      delay = 0;
      // Find pane's ID to get its delay settings.
      $(classes).each(function(i, item){
        if (item.match(/pane\-\d+/)) {
          delay = parseInt(Drupal.settings.ding_nodelist[item]);
        }
      });
      $(this).find('.ding_nodelist-items').carouFredSel({
        circular: true,
        infinite: true,
        direction: 'left',
        auto : {
          pauseOnHover: true,
          pauseDuration: delay
        },
        width: '100%',
        align: 'center',
        responsive: true,
        items: 1,
        scroll : {
          items: 1
        },
        pagination : {
          container : $(this).find('.pagination')
        },
        prev: {
          button: $(this).find('.prev'),
          key: "left"
        },
        next: {
          button: $(this).find('.next'),
          key: "right"
        }
      });
    });
  });
})(jQuery);
