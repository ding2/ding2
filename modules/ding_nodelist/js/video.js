(function ($) {
  "use strict";

  var video_play_once = 0;
  Drupal.behaviors.ding_nodelist_video = { //VIMEO, YOUTUBE AND SOUNCLOUD CUSTOM PLAY-BUTTONS
    attach: function (context) {
      var src, stripsrc, newsrc, mediasrc;

      if ($(".media-content .content > div", context)
          .hasClass("media-vimeo-video")) {
        mediasrc = "vimeo";
      }
      else {
        if ($(".media-content .content > div", context)
            .hasClass("media-youtube-video")) {
          mediasrc = "yt";
        }
        else {
          if ($(".media-content .content > div", context)
              .hasClass("media-soundcloud-audio")) {
            mediasrc = "sc";
          }
        }
      }

      if (video_play_once === 0) {
        if (mediasrc === "yt") {
          var ytPlayer = $('.media-youtube-player');
          src = ytPlayer.attr('src');
          stripsrc = src.replace("?wmode=opaque", '');
          newsrc = "https:" + stripsrc + "?enablejsapi=1";
          ytPlayer.attr('src', newsrc);
          ytPlayer.attr('id', 'video');
        }

        else {
          if (mediasrc === "vimeo") {
            var vimeoPlayer = $('.media-vimeo-player');
            src = vimeoPlayer.attr('src');
            stripsrc = src.replace("?color=", '');
            newsrc = stripsrc + "?api=1";
            vimeoPlayer.attr('src', newsrc);
            vimeoPlayer.attr('id', 'video');
          }
          else {
            if (mediasrc === "sc") {
              $('.media-soundcloud-player')
                .attr('id', 'soundcloud_widget');
            }
          }
        }
        video_play_once = 1;
      }

      var player;

      function onPlayerReady01() {
        // bind events
        $('.overlay', context).on("click", function () {
          var $this = $(this);

          $this.fadeOut();
          $this.parent().find('.has-video').fadeOut();
          if ($('.is-tablet').is(':visible') === true) {
            player.playVideo();
          }
        });
      }

      function initPlayer() {
        if (mediasrc === "yt") {
          window.onYouTubePlayerAPIReady = function () {
            // create the global player from the specific iframe (#video)
            player = new window.YT.Player('video', {
              events: {
                // call this function when player is ready to use
                'onReady': onPlayerReady01
              }
            });
          };
          var tag = document.createElement('script');
          tag.src = "https://www.youtube.com/iframe_api";
          var firstScriptTag = document.getElementsByTagName('script')[0];
          firstScriptTag.parentNode.insertBefore(tag, firstScriptTag);

        }

        else {
          if (mediasrc === "vimeo") {
            var iframe = document.getElementById('video');
            player = window.$f(iframe);

            $('.overlay').on("click", function () {
              var $this = $(this);
              $this.fadeOut();
              $this.parent().find('.has-video').fadeOut();
              if ($('.is-tablet').is(':visible') === true) {
                player.api("play");
              }
            });
          }
          else {
            if (mediasrc === "sc") {
              player = window.SC.Widget(document.getElementById('soundcloud_widget'));
              player.bind(window.SC.Widget.Events.READY, function () {
                $('.overlay').on("click", function () {
                  var $this = $(this);
                  $this.fadeOut();
                  $this.parent().find('.has-audio').fadeOut();
                  if ($('.is-tablet')
                      .is(':visible') === true) {
                    player.play();
                  }
                });
              });
            }
          }
        }
      }



      initPlayer();


      //////////////////FRONT PAGE //////////////
      $('.pn-media-play', context).on('click', function (event) {
        event.preventDefault();
        var $this = $(this),
          top = $this.parent().parent(),
          url = top.children('.media-container')
            .children('.media-content')
            .data('url'),
          stripurl,
          mediasrc,
          mediaurl,
          iframe;

        top.children('.media-container')
          .children('.pn-close-media')
          .show(); //show the close btn

        //Vimeo
        if (url.indexOf("vimeo") !== -1) {
          mediasrc = "vimeo";
          stripurl = url.replace("http://vimeo.com/", '');
          mediaurl = "http://player.vimeo.com/video/" + stripurl + "?autoplay=1";
          iframe = '<iframe class="media-vimeo-player" width="100%" height="300px" src="' + mediaurl + '" frameborder="0" webkitallowfullscreen="" mozallowfullscreen="" allowfullscreen="" id="target"></iframe>';

          //fade out info
          top.children('.news-info').fadeOut();
          top.children('.event-info').fadeOut();
          top.children('.page-info').fadeOut();
          top.children('.eresource-info').fadeOut();
          //append the video
          top.children('.media-container')
            .children('.media-content')
            .append(iframe);
        }

        //Youtube

        else {
          if (url.indexOf("youtube") !== -1) {
            let video_id = url.split('v=')[1];
            let ampersandPosition = video_id.indexOf('&');
            if(ampersandPosition !== -1) {
              video_id = video_id.substring(0, ampersandPosition);
            }
            mediaurl = "https://www.youtube.com/embed/" + video_id + "?autoplay=1&autohide=1&enablejsapi=1";
            iframe = '<iframe class="media-youtube-player" width="100%" height="300px" src="' + mediaurl + '" frameborder="0" allowfullscreen="" id="target" autohide="1"></iframe>';

            top.children('.news-info').fadeOut();
            top.children('.event-info').fadeOut();
            top.children('.page-info').fadeOut();
            top.children('.eresource-info').fadeOut();
            top.children('.media-container')
              .children('.media-content')
              .append(iframe);
          }

          //Soundcloud
          else {
            if (url.indexOf("soundcloud") !== -1) {
              mediasrc = "sc";
              stripurl = url.replace("http:", '');
              mediaurl = "//w.soundcloud.com/player/?url=http%3A" + stripurl + "&amp;visual=1&amp;auto_play=true&amp";
              iframe = '<iframe class="media-soundcloud-player" width="100%" height="300px" src="' + mediaurl + '" frameborder="0" allowfullscreen="" id="target"></iframe> ';

              top.children('.news-info').fadeOut();
              top.children('.event-info').fadeOut();
              top.children('.page-info').fadeOut();
              top.children('.eresource-info').fadeOut();
              top.children('.media-container')
                .children('.media-content')
                .append(iframe);

            }
          }
        }
      });
      //End pn-media-play click

      //Close btn
      $('.pn-close-media', context).on('click', function () {
        var $this = $(this);
        $this.fadeOut();
        $this.parent().children('.media-content').empty();
        $this.parent().parent().children('.news-info').fadeIn();
        $this.parent().parent().children('.event-info').fadeIn();
        $this.parent().parent().children('.page-info').fadeIn();
        $this.parent().parent().children('.eresource-info').fadeIn();
      });
    }
  };

}(jQuery));
