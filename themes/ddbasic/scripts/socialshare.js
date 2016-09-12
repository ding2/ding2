/*jshint forin:false, jquery:true, browser:true, indent:2, trailing:true, unused:false */

(function (scope, $) {
  // Share code for social buttons
  Drupal.behaviors.social_share = {
    attach: function(context, settings) {
      $('a.twitter-share', context).click(function (evt) {
        evt.preventDefault();

        var
          url = location.href,
          share_url = url,
          options = {},
          window_name = 'socials';

          url = 'https://twitter.com/share?'
              + 'url=' + encodeURIComponent(url)
              + '&amp;text=' + encodeURIComponent(document.title);

          options['width'] = 720;
          options['height'] = 460;

        var window_features = [];
        for (var i in options) {
          window_features.push(i + '=' + options[i]);
        }

        window.open(url, window_name, window_features.join(','));
        
      });

      $('a.fb-share', context).click(function (evt) {
        evt.preventDefault();

        var
          url = location.href,
          share_url = url,
          options = {},
          window_name = 'socials';


            url = 'http://www.facebook.com/sharer/sharer.php?u='
                + encodeURIComponent(url)
                + '&amp;t=' + encodeURIComponent(document.title);

            options['width'] = 720;
            options['height'] = 460;

        var window_features = [];
        for (var i in options) {
          window_features.push(i + '=' + options[i]);
        }

        window.open(url, window_name, window_features.join(','));
        
      });
      
      $('a.mail-share', context).click(function (evt) {
        evt.preventDefault();

        var
          options = {},
          url = location.href,
          window_name = 'socials',
          subject = "";
          
          url = encodeURIComponent(url);
          subject = encodeURIComponent(document.title);

        document.location.href = "mailto:?subject=" + subject + "&body=" + subject + "%0D%0A"+ url;
      });

    }
  };

})(this, jQuery);