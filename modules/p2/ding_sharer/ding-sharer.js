/**
 * @file
 * Ding sharer
 *
 * Sharing is done JS time, to enable the use of window.open().
 */
(function ($) {
  "use strict";
  
  Drupal.behaviors.ding_sharer = {
    attach: function(context) {
    
      $('a.sharer-button', context).bind('click', function (evt) {
        evt.preventDefault();
        var
          share_url = encodeURIComponent(location.href),
          title = encodeURIComponent(document.title),
          options = {},
          window_name = 'socials',
          
          url = '';
          
        if ($(this).hasClass('sharer-facebook')) {
          url = 'http://www.facebook.com/sharer/sharer.php?' +
              'u=' + share_url +
              '&amp;t=' + title;
          options.width = 720;
          options.height = 460;
        } else if ($(this).hasClass('sharer-twitter')) {
          url = 'https://twitter.com/share?' +
              'url=' + share_url +
              '&amp;text=' + title;

          options.width = 720;
          options.height = 460;
        }
        
        var window_features = [];
        for (var i in options) {
          window_features.push(i + '=' + options[i]);
        }

        window.open(url, window_name, window_features.join(','));
      });
    }
  };
  
}(jQuery));
