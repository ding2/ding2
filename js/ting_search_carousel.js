
/**
 * Behaviour to set up the search carousel.
 */
(function ($) {
  Drupal.behaviors.tingSearchCarousel = {
    attach: function(context) {
      $.ajax({
        type: 'get',
        url : Drupal.settings.basePath + 'ting_search_carousel/results/ajax/dorthe/0/10',
        dataType : 'json',
        success : function(msg) {
          $('.ting-search-carousel .subtitle').html(msg.subtitle);
          $('.ting-search-carousel #ting-rs-carousel .rs-carousel-runner').html(msg.content);
          $('.ting-search-carousel #ting-rs-carousel').carousel();
        }
      });
    }
  }
})(jQuery);

var ting_rs_carousel = {
  init: function(view) {
    this.view = view;
    this.elements();
  },
  elements: function() {
    var view = this.view;
    this.elements = {};
    this.elements.carousel = view.find('#ting-rs-carousel-1');
  }
};
