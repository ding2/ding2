(function($) {

  /*
   * Toggle opening hours
   */
  function toggle_opening_hours() {
    // Set variables
    var element = $('.js-opening-hours-toggle');
    var scrollOffset;

    // Add collapsed class
    element.addClass('js-collapsed');

    // Attach click
    element.on('click touchstart', function(event) {
      // Store clicked element for later use
      var element = this;

      // Toggle
      $(this).parent().next('.js-opening-hours-toggle-element').slideToggle('fast', function() {
        // Toggle class
        $(element).toggleClass('js-collapsed js-expanded');

        // If the window is scrolled to the top increase offset
        if ($(window).scrollTop() == 0) {
          scrollOffset = -104;
        } else {
          scrollOffset = -60;
        }

        // Scroll to the top
        $.scrollTo($(element).parent(), 500, {offset: scrollOffset, axis: 'y'});
        
        // Remove focus from link
        $(element).blur();
      });

      // Prevent default (href)
      event.preventDefault();
    });
  }

  // When ready start the magic
  $(document).ready(function () {
    // Toggle opening hours
    toggle_opening_hours();

    // Toggle footer menu
    $('.footer .pane-title').on('click', function() {
      var element = $(this).parent();
      $('.menu', element).toggle();
      $(this).toggleClass('js-toggled');
    });
  });

})(jQuery);