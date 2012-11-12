(function($) {
  $(document).ready(function () { 
    
    var menu = $('.main-menu-wrapper');
    
		pos = menu.offset();
		
		$(window).scroll(function(){
      
      $('body').css('padding-bottom', $(menu).height());
      
			if ($(window).scrollTop() > pos.top-$(menu).height()) {
				$(menu).addClass('fixed');
				$('.header-wrapper').addClass('fixed');
				$('.user-compact').addClass('fixed');
			} else if($(menu).scrollTop() <= pos.top && $(menu).hasClass('fixed')) {
  			$(menu).removeClass('fixed');
				$('.header-wrapper').removeClass('fixed');
				$('.user-compact').removeClass('fixed');
			}      
      
    });
    
  });
        
})(jQuery);