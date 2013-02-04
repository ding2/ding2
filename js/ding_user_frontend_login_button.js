/**
 * Handle click events on the login button to toggle display of the login form.
 */
(function($) {
  $(document).ready(function() {
    $('.ding-user-login-button .login-button').live(function(event) {
      // Stop event propagation.
      event.preventDefault();
      $(this).parent().find('.user').toggle();
    });
  });
}(jQuery));


