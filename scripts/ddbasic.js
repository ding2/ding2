(function($) {
  $(document).ready(function () {

    // Fixed elements and scroll
    var menu = $('.navigation-wrapper');

		pos = menu.offset();

    if ($(window).scrollTop() > pos.top-$(menu).height()) {
      //$('body').css('padding-bottom', $(menu).height());

      $(menu).addClass('fixed');

      $('.js-fixed-element').each(function() {
        $(this).show();
      });

    }


		$(window).scroll(function(){

      // $('body').css('padding-bottom', $(menu).height());

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


    // Toggle element

    $(".js-show-element").click(function() {

      var $element = $("." + $(this).attr("rel"));
      var offset = $(this).offset();

      if ($(this).hasClass("active")) {
        $(this).removeClass("active");        
      } else {
        $(this).addClass("active");        
      }

      $element.toggle();

      $element.css({"top": offset.top + 72, "left": offset.left - 275});

    });


    // Hide element
    $(".js-hide-element").click(function() {
      $(this).parent().hide();
    });


  });

})(jQuery);