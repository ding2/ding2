/**
 * Handle click events on the login button to toggle display of the login form.
 */
(function($) {
  $(document).ready(function() {
    $('body').delegate('.ding-user-login-button .login-button', 'click', function(event) {
      // Stop event propagation.
      event.preventDefault();
      $(this).parent().find('.user').toggle();
    });
  });
}(jQuery));


