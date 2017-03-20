/*jshint forin:false, jquery:true, browser:true, indent:2, trailing:true, unused:false */
/*globals ddbasic*/

(function($) {
  'use strict';

  Drupal.behaviors.misc = {
    attach: function(context, settings) {
      //Add Event handler to frontpage openinghours on mobile.
      var pane_opening_hours = $('.front .pane-all-opening-hours .pane-title', context);
      pane_opening_hours
        .on('click', function(){
          if($('.is-mobile', context).is(':visible')) {
            $(this).siblings('.pane-content').slideToggle('fast');
          }
        })
        .siblings('.pane-content');

      //Topbar openinghours button.
      var opening_hours_button = $('.topbar-menu a.topbar-link-opening-hours', context);
      opening_hours_button.on('click', function(event){
        if (pane_opening_hours.length > 0) {
          event.preventDefault();
          $('html, body').animate({
            scrollTop: pane_opening_hours.offset().top - 164}, 400);
        }
      });

      //Make sure facet browser is open when item is selected
      var facet_items = $('.js-facet-browser-toggle input[type=checkbox]');
      facet_items.each(function(){
        var $this = $(this);
        if($this.is(':checked')) {
          $this
            .closest('fieldset')
            .removeClass('collapsed');
        }
      });

      //Close messages
      var pane_messages = $('.pane-page-messages'),
          close_messages_button = $('.close-messages-button', context);

      close_messages_button.on('click', function(){
        pane_messages.slideUp('fast');
      });
    }
  };

  // Minimize ask tab on moblie
  $(function () {
    $(window).bind('resize.ding_ask_tab', function (evt) {
      switch (ddbasic.breakpoint.is('mobile', 'ask_tab')) {
        case ddbasic.breakpoint.IN:
          $('.ask-vopros-tab').addClass('minimized');
        break;
      }
    });
    setTimeout(function(){
      $(window).triggerHandler('resize.ding_ask_tab');
    }, 4000);
  });

})(jQuery);
