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
    }

    var window_features = [];
    for (var i in options) {
      window_features.push(i + '=' + options[i]);
    }

    window.open(url, window_name, window_features.join(','));
  };

  Drupal.behaviors.ding_sharer = {
    attach: function(context) {

      $('a.sharer-button', context).bind('click', function (evt) {
        var community = '';

        if ($(this).hasClass('sharer-noshare')) {
          return;
        }

        if ($(this).hasClass('sharer-facebook')) {
          community = 'facebook';
        } else if ($(this).hasClass('sharer-twitter')) {
          community = 'twitter';
        }

        if (!$(this).hasClass('sharer-noprevent')) {
          evt.preventDefault();
        }

        sharer(community);
      });
    }
  };

}(jQuery));
