(function ($) {
  'use strict';

  Drupal.behaviors.ting_subsearch_secondary = {
    attach: function (context) {
      $('#ting-subsearch-secondary', context).on('click', function (e) {
        var target = e.target;

        if (!$(target).closest('a').length) {
          var redirectUrl = $(this).data('href');
          window.open(redirectUrl, '_blank');
        }
      });
    }
  };
})(jQuery);
