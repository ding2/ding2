/*jshint forin:false, jquery:true, browser:true, indent:2, trailing:true, unused:false */
/*globals ddbasic*/
(function($) {
  'use strict';

  // Ting search results, filter styling.
  $(function () {
    $("<div class='expand-search'>" + Drupal.t('Limit search to') + "</div>").insertAfter($( ".pane-search-result-count"));
    $('.page-search-ting').find('.mobile-hide').wrapAll("<div class='hide-wrap'></div>");

    $('.expand-search').click(function(){
        $(this).toggleClass('expanded');
        $(this).parent().find('.hide-wrap').slideToggle("fast");
    });
  });

  // Hover functions for ting object teasers.
  function ting_teaser_hover(element_to_hover){
    element_to_hover.mouseenter( function() {
      if($('body').hasClass('has-touch')) {
        return;
      }
      var hovered = $(this),
          window_width = $(window).width(),
          position_of_hovered = hovered.offset();

      // If hovered element is left of window center.
      if(position_of_hovered.left < (window_width / 2)) {
        hovered.addClass('move-right');
      } else {
        hovered.addClass('move-left');
      }

      // Set timeout to make shure element is still above while it animates out.
      setTimeout(function(){
        element_to_hover.removeClass('is-hovered');
        hovered.addClass('is-hovered');

      }, 300);
    });
    element_to_hover.mouseleave(function() {
      $(this).removeClass('move-left');
      $(this).removeClass('move-right');
    });
  }
  Drupal.behaviors.ding_ting_teaser_hover = {
    attach: function(context, settings) {
      ting_teaser_hover($('.ting-object.view-mode-teaser > .inner', context));
    }
  };

  // Shorten ting object teaser titles
  Drupal.behaviors.ding_ting_teaser_short_title = {
    attach: function(context, settings) {
      $('.ting-object.view-mode-teaser > .inner .field-name-ting-title h2').each(function(){
        this.innerText = ellipse(this.innerText, 45);
      });
    }
  };

  function ellipse(str, max){
    return str.length > (max - 3) ? str.substring(0,max-3) + '...' : str;
  }

  // Ting teaser image proportions.
  function adapt_images(images){
    $(images).each(function() {
      var image = new Image();
      image.src = $(this).attr("src");
      var that = $(this);
      image.onload = function() {
        var img_height = this.height;
        var img_width = this.width;
        var img_format = img_width/img_height;
        // Format of our container.
        var standart_form = 0.7692;

        if(img_format >= standart_form) {
          that.addClass('scale-height');
        } else if (img_width < img_height) {
          that.addClass('scale-width');
        }
      };
    });
  }
  Drupal.behaviors.ding_ting_teaser_image_width = {
    attach: function(context, settings) {
      adapt_images($('.ting-object.view-mode-teaser img'));
    }
  };

  // Ting teaser mobile
  Drupal.behaviors.ding_ting_object_list_mobile = {
    attach: function(context, settings) {
      $('.js-toggle-info-container', context).click(function(){
        if(ddbasic.breakpoint.is('mobile')) {
          $(this)
            .toggleClass('is-open')
            .closest('.ting-object-right').find('.info-container')
              .slideToggle('fast');
        }
      });
    }
  };

  // Ting scroll to other formats
  Drupal.behaviors.ding_ting_object_scrollto_other_formats = {
    attach: function(context, settings) {
      var other_formats_btn = $('a.other-formats', context),
          pane_ting_object_types = $('.pane-ting-ting-object-types', context),
          html = $('html, body');

      other_formats_btn.on('click', function(event){
        event.preventDefault();
        html.animate({
          scrollTop: pane_ting_object_types.offset().top - 148}, 400);
      });

    }
  };

})(jQuery);
