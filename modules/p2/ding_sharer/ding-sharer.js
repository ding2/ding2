/**
 * @file
 * Ding sharer
 *
 * Sharing is done JS time, to enable the use of window.open().
 */
(function ($) {
  "use strict";

  window.sharer = function (community) {
    var
      share_url = encodeURIComponent(location.href),
      title = encodeURIComponent(document.title),
      options = {},
      window_name = 'socials',
      url = '';

    switch (community) {
      case 'facebook':
        url = 'http://www.facebook.com/sharer/sharer.php?' +
            'u=' + share_url +
            '&amp;t=' + title;
        options.width = 720;
        options.height = 460;
        break;

      case 'twitter':
        url = 'https://twitter.com/share?' +
            'url=' + share_url +
            '&amp;text=' + title;

        options.width = 720;
        options.height = 460;
        break;

      case 'mail':
        window_name = false;
        document.location.href = "mailto:?subject=" + title + "&body=" + title + "%0D%0A"+ share_url;
        break;
    }

    if (window_name !== false) {
      var window_features = [];
      for (var i in options) {
        window_features.push(i + '=' + options[i]);
      }

      window.open(url, window_name, window_features.join(','));
    }
};

  Drupal.behaviors.ding_sharer = {
    attach: function(context) {

      $('.share-buttons a', context).bind('click', function (evt) {
        var community = '';

        evt.preventDefault();

        if ($(this).hasClass('facebook-share')) {
          community = 'facebook';
        }
        else if ($(this).hasClass('twitter-share')) {
          community = 'twitter';
        }
        else if ($(this).hasClass('mail-share')) {
          community = 'mail';
        }

        sharer(community);
      });
    }
  };

}(jQuery));
