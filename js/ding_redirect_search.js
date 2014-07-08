
(function ($) {

/**
 * Handle the submit of a search block. If the chosen type of search has a
 * redirect URL, redirect the user to it.
 */
Drupal.behaviors.ding_redirect_search_form_submit = {
  attach: function (context, settings) {
    $('#search-block-form input[type="submit"]', context).click(function(event) {
      var choosen_search = $('#search-block-form input[name=ding_redirect_redirect_radios]:checked').val();

      if (settings.ding_redirect[choosen_search] !== '') {
        // Redirect the user to the new URL from settings. Add the query to
        // the URL.
        var url = settings.ding_redirect[choosen_search],
            query = $('#search-block-form input[type="text"]').val();
        url = url.replace('%QUERY%', query);

        window.location = url;
        event.preventDefault();
      }
    });
  }
};

/**
 * Handle the submit of a login block. If redirect URL are used, redirect the
 * user to it.
 */
Drupal.behaviors.ding_redirect_login_form_submit = {
  attach: function (context, settings) {

  }
};

})(jQuery);
