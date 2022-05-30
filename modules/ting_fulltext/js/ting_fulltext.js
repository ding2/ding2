(function ($) {
  "use strict";

  Drupal.behaviors.fullTextReview = {
    attach: function (context) {
      var selector = '#js-ting-lektor-fulltext';
      $(selector, context).once('js-ting-lektor-fulltext', function () {
         var url = $(this).attr("data-fulltext-url");
         $.ajax({
           type: 'POST',
           url: url,
           success: function (result) {
             $("#js-ting-lektor-fulltext").html(result);
           }
         });
      });
    }
  };

})(jQuery);
