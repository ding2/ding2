
(function ($) {
  "use strict";

  /**
   * Handle the click on the login link. If redirect URL are used, redirect the
   * user to it. This file are only added, if an URL are provided.
   */
  $(document).ready(function(){
    // To remove the quick flicker of the login form from the theme, we remove
    // it here. Alternative is to make the theme overrideable.

    // The URL the user should get redirected to.
    var login_url = Drupal.settings.ding_redirect.login_url;
    $('.topbar-link-user').on('click touchstart', function(e) {
      $('.js-topbar-user').remove();
      window.location = login_url;
      e.preventDefault();
    });
  });

})(jQuery);
