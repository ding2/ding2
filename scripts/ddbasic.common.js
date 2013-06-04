(function($) {

  /*
   * Toggle opening hours
   */
  function toggle_opening_hours() {
    // Set variables
    var element = $(".js-opening-hours-toggle");

    // Attach click
    element.on('click touchstart', function(event) {
      // Toggle
      element.parent().next(".js-opening-hours-toggle-element").slideToggle();
    });

    // Prevent default (href)
    event.preventDefault();
  }

  // When ready start the magic
  $(document).ready(function () {

    // Toggle opening hours
    toggle_opening_hours();

    // Toggle for footer menu
    $('.footer .pane-title').on('click', function() {
      var element = $(this).parent();
      $('.menu', element).toggle();
      $(this).toggleClass('js-toggled');
    });
  });

  // Add equal heights on $(window).load() instead of $(document).ready()
  // See: http://www.cssnewbie.com/equalheights-jquery-plugin/#comment-13286
  $(window).load(function () {

    // Set equal heights on front page content
    $('.main-wrapper .grid-inner').equalHeights();

    // Set equal heights on front page attachments
    $('.attachments-wrapper .grid-inner > div').equalHeights();
  });

})(jQuery);