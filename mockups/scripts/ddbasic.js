(function($) {
  $(document).ready(function () {

    var menu = $('.main-menu-wrapper');

		pos = menu.offset();

    if ($(window).scrollTop() > pos.top-$(menu).height()) {
      $('body').css('padding-bottom', $(menu).height());

      $(menu).addClass('fixed');
      
      $('.js-fixed-element').each(function() {
        $(this).show();
      });      
      
    }


		$(window).scroll(function(){

      $('body').css('padding-bottom', $(menu).height());

			if ($(window).scrollTop() > pos.top-$(menu).height()) {
				$(menu).addClass('fixed');

        $('.js-fixed-element').each(function() {
          $(this).show();
        });

			} else if($(menu).scrollTop() <= pos.top && $(menu).hasClass('fixed')) {
  			$(menu).removeClass('fixed');

        $('.js-fixed-element').each(function() {
          $(this).hide();
        });

			}

    });

  });

})(jQuery);