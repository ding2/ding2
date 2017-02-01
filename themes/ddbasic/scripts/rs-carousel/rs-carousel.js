(function($) {
  'use strict';

  Drupal.behaviors.ding_carousel = {
    attach: function(context, settings) {
      // Wrap select list
      $( "select.rs-carousel-select-tabs" ).wrap( "<div class='form-type-select rs-carousel-select'><div class='select-wrapper'></div></div>" );
    }
  };

})(jQuery);
