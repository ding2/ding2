(function($) {
  $(document).ready(function () {

    // Fixed elements and scroll
    var menu = $('.navigation-wrapper');

		var pos = menu.offset();

    // Take the Drupal toolbar into account
    var bodyPad = parseInt($('body').css('paddingTop'), 10);
    if (bodyPad) {
      pos.top = pos.top - bodyPad;
    }

    if ($(window).scrollTop() > pos.top-$(menu).height()) {
      $(menu).addClass('fixed');

      // Only when Drupal toolbar is present
      if ($(menu).hasClass('fixed') && bodyPad) {
        $(menu).css('top', bodyPad);
      }

      $('.js-fixed-element').each(function() {
        $(this).show();
      });

    }


		$(window).scroll(function(){

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

      // Only when Drupal toolbar is present
      if ($(menu).hasClass('fixed') && bodyPad) {
        $(menu).css('top', bodyPad);
      } else {
        $(menu).css('top', '');
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

    // Equal heights
    // Not working at the moment, must get back to this at a later stage.
    //if ($('body').hasClass('page-ding-frontpage')) {
      //$('.top-wrapper').equalize();
      //$('.main-wrapper').equalize();
      //$('.attachments-wrapper').equalize();
    //}
  });

})(jQuery);