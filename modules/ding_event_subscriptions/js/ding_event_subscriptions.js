(function ($) {
  "use strict";
  function copyToClipboard(element) {
    var $temp = $("<input>");
    $("body").append($temp);
    $temp.val($(element).data('reference')).select();
    document.execCommand("copy");
    $temp.remove();
  }

  $(document).ready(function () {
    $('.ding-event-subscriptions').on('click', function (e) {
      e.preventDefault();
      copyToClipboard($(this));
      $(this).tooltip({
        items: ".ding-event-subscriptions",
        content: Drupal.t("Link was copied to clipboard")
      });
      $(this).tooltip("open");
    }).on('mouseover', function () {
      $(this).tooltip("disable");
    });
  });
})(jQuery);
