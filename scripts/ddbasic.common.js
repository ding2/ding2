(function($) {

  // When ready start the magic.
  $(document).ready(function () {

    // Imitate dropdown on carousel tabs
    ting_carousel_dropdown();
  });

  // Add equal heights on $(window).load() instead of $(document).ready()
  // See: http://www.cssnewbie.com/equalheights-jquery-plugin/#comment-13286
  $(window).load(function () {

    // Set equal heights on front page content
    $('.main-wrapper .grid-inner').equalHeights();

    // Set equal heights on front page attachments
    $('.attachments-wrapper .grid-inner > div').equalHeights();
  });

  function ting_carousel_dropdown() {
    var carousel_tabs_wrapper = $('.rs-carousel-tabs ul');

    // Add classes to tabs
    $('li.active', carousel_tabs_wrapper).addClass('js-tab-active');
    $('li:not(.active)', carousel_tabs_wrapper).addClass('js-tab-hidden');

    // Set variables
    var carousel_tab_active = $('.js-tab-active', carousel_tabs_wrapper);
    var carousel_tabs       = $('.js-tab-hidden', carousel_tabs_wrapper);

    // Click active tab
    carousel_tab_active.click(function() {
      // Toggle tabs and classes
      ting_carousel_toggle_tabs(carousel_tabs);
    });

    // Other tab clicked
    carousel_tabs.click(function() {
      // Remove active class from previously active tab
      carousel_tab_active.removeClass('js-tab-active');
      carousel_tab_active.addClass('js-tab-hidden');

      // Toggle tabs and classes
      ting_carousel_toggle_tabs(carousel_tabs);

      // Add active class to clicked tab
      $(this).addClass('js-tab-active');

      // Remove hidden class
      $(this).removeClass('js-tab-hidden');

      // Override variables
      carousel_tab_active = $('.js-tab-active', carousel_tabs_wrapper);
      carousel_tabs       = $('.js-tab-hidden', carousel_tabs_wrapper);

      carousel_tab_active.prependTo(carousel_tabs_wrapper);

    });
  }

  function ting_carousel_toggle_tabs(carousel_tabs) {
    carousel_tabs.each(function() {
      $(this).toggleClass('js-tab-hidden');
      $(this).toggleClass('js-tab-visible');
    });
  }

})(jQuery);