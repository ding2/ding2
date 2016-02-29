(function ($) {
  $(document).ready(function(){
    $('.ding_nodelist-vertical_accordion .ding_nodelist-items').each(function(){
      var c_width = $(this).width();
      var sum_height = 0;
      $(this).find('.va-slice').each(function(){
        sum_height += $(this).outerHeight(true)/1.8;
      });
      var exp_height = $(this).find('.va-slice:first').height();
      var slides = $(this).find('.va-slice').length;
      $(this).vaccordion({
        accordionH: Math.round(sum_height),
        expandedHeight: exp_height,
        accordionW: 'auto',
        visibleSlices: slides,
        animOpacity: 0.25,
        autoplay: 3000
      });
    }).find('.va-content').click(function(e){
      document.location.href = $(this).data('destination');
      e.stopPropagation();
    });
  });
})(jQuery);
