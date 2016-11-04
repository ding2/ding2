(function ($) {
  'use strict';

  Drupal.behaviors.dingEventSubscriptions = {
    attach: function (context, settings) {
      function copyToClipboard(element) {
        var $temp = $("<input>");
        $('body').append($temp);
        var url = $(element).data('domain') + '/' + $(element).data('reference');
        $temp.val(url).select();
        document.execCommand('copy');
        $temp.remove();
      }

      $('.ding-event-subscriptions', context).on('click', function (e) {
        e.preventDefault();
        window.location.href = $(this).data('reference');
        copyToClipboard($(this));
        $(this).tooltip({
          items: '.ding-event-subscriptions',
          content: Drupal.t('Link was copied to clipboard')
        });
        $(this).tooltip('open');
      }).on('mouseover', function () {
        $(this).tooltip('disable');
      });
    }
  };

})(jQuery);
