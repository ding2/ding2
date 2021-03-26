/**
 * @file
 * Implement video in Ding Nodelist widgets.
 */
(function ($) {
  "use strict";

  let NodelistVideo = {
    contentSelectors: ['.article-info', '.event-time', '.news-info', '.event-info', '.page-info', '.eresource-info', '.article_image', '.event-image'],
    addCloseBtn: function (top) {
      return top.children('.media-container').children('.pn-close-media').show();
    },
    afterVideoRendered: function (wrapper) {
      wrapper.fadeOut();
      wrapper.parent().children('.media-content').empty();

      this.contentSelectors.forEach(function (selector) {
        wrapper.parent().parent().children(selector).fadeIn();
      });

      this.showPlayBtn(wrapper.parent().parent());
    },
    buildIframe: function (data) {
      return `<iframe class="media-${data.service}-player" width="100%" height="${data.height}" src="${data.mediaurl}" frameborder="0" allowfullscreen="" id="target" autohide="1" allow="autoplay"></iframe>`;
    },
    getService: function (top) {
      return top.children('.media-container').children('.media-content').data('service');
    },
    getVideoUrl: function (top) {
      return top.children('.media-container').children('.media-content').data('url');
    },
    getVideoId: function (url, service) {
      let videoId;
      if (service === 'youtube') {
        videoId = url.split('v=')[1];
        var ampersandPosition = videoId.indexOf('&');
        if (ampersandPosition !== -1) {
          videoId = videoId.substring(0, ampersandPosition);
        }
      }
      else if (service === 'vimeo') {
        videoId = url.replace("http://vimeo.com/", '');
      }

      return videoId;
    },
    hidePlayBtn: function (wrapper) {
      $('.pn-media-play', wrapper).hide();
    },
    preVideoRender: function (top, iframe) {
      this.contentSelectors.forEach(function (selector) {
        top.children(selector).fadeOut();
      });

      top.children('.media-container')
        .css('z-index', '2')
        .children('.media-content')
        .css('background-color', 'black')
        .append(iframe);
    },
    showPlayBtn: function (wrapper) {
      $('.pn-media-play', wrapper).show();
    },
    render: function (data, url, top) {
      if (data.service === 'vimeo') {
        data.mediaurl = "http://player.vimeo.com/video/" + this.getVideoId(url, data.service) + "?autoplay=1&muted=1";
      }
      else if (data.service === 'youtube') {
        data.mediaurl = "https://www.youtube.com/embed/" + this.getVideoId(url, data.service) + "?autoplay=1&autohide=1&enablejsapi=1";
      }
      let iframe = this.buildIframe(data);
      this.preVideoRender(top, iframe);
      this.hidePlayBtn(top);
    }
  };

  Drupal.behaviors.ding_nodelist_video = {
    attach: function (context) {
      $('body').once('ding_nodelist', function () {
        let root = $('.ding_nodelist', document);

        Array.prototype.forEach.call(root, function (wrapper) {
          let widget = $(wrapper).data('widget-type');

          // Video play.
          $('.pn-media-play', wrapper).on('click', function (event) {
            event.stopPropagation();
            let $this = $(this);

            let top, data = {};
            switch (widget) {
              case 'promoted_nodes':
                top = $this.parent().parent();
                data.height = Math.round(top.height()) + 'px';
                break;

              case 'carousel':
                top = $this.parent();
                data.height = Math.round(top.height()) + 'px';
                $(wrapper).find('.ding_nodelist-items').slick('slickPause');
                break;
            }

            let url = NodelistVideo.getVideoUrl(top);
            data.service = NodelistVideo.getService(top);

            NodelistVideo.addCloseBtn(top);
            NodelistVideo.render(data, url, top);
          });

          // Close btn.
          $('.pn-close-media', context).on('click', function (e) {
            e.stopPropagation();
            let $this = $(this);
            NodelistVideo.afterVideoRendered($this);

            if ('carousel' === widget) {
              $(wrapper).find('.ding_nodelist-items').slick('slickPlay');
            }
          });
        });
      });
    }
  };
}(jQuery));
