(function($) {

  // When ready start the magic.
  $(document).ready(function () {

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