
(function ($) {
  "use strict";

  /**
   * Handle the click on the login link. If redirect URL are used, redirect the
   * user to it. This file are only added, if an URL are provided.
   */
  $(document).ready(function(){

    // Get all settings from Drupal.
    var login_url = Drupal.settings.ding_redirect.login_url,
        delay = Drupal.settings.ding_redirect.delay,
        dialog_title = Drupal.settings.ding_redirect.dialog_title,
        dialog_text = Drupal.settings.ding_redirect.dialog_text;

    $('.topbar-link-user').on('click touchstart', function(e) {
      // To remove the quick flicker of the login form from the theme, we remove
      // it here. Alternative is to make the theme overridable.
      $('.js-topbar-user').remove();

      if (delay > 0) {
        // Pop a dialog when there is a delay on redirect.
        var canceled = false;
        var $dialog = $('<div class="ding-redirect-modal">' + dialog_text + '</div>').dialog({
          'modal': true,
          'title': dialog_title,
          'closeText': Drupal.t('close'),
          'close': function(event, ui) {
            canceled = true;
            $dialog.dialog('destroy').remove();
          }
        });

        setTimeout(function(){
          if (!canceled) {
            $dialog.dialog('destroy').remove();
            window.location = login_url;
          }
        }, delay);
      }
      else {
        // No dialog and delay used, redirect user.
        window.location = login_url;
      }
      e.preventDefault();
      return false;
    });
  });

})(jQuery);
