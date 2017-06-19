/*jshint forin:false, jquery:true, browser:true, indent:2, trailing:true, unused:false */
(function($) {
  'use strict';

  // P2 Ding list
  Drupal.behaviors.ding_p2_list = {
    attach: function(context, settings) {
      $('.field-name-ding-entity-buttons .ding-list-add-button .trigger').on('click', function(evt) {
        evt.preventDefault();
        $(this).parent().addClass('open-overlay');
      });
      $('.field-name-ding-entity-buttons .ding-list-add-button .close').on('click', function(evt) {
        evt.preventDefault();
        $(this).parents('.ding-list-add-button').removeClass('open-overlay');
      });
    }
  };

  // Close all open add overlays when the popup is closed.
  $(window).on('dingpopup-close', function () {
    $('.ding-list-add-button').removeClass('open-overlay');
  });

})(jQuery);
