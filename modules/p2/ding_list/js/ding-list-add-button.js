/**
 * @file
 * Ding list add button.
 */

(function ($) {
  "use strict";

  Drupal.behaviors.ding_list_add_button = {
    attach: function (context) {
      // Pull out the content of each ding-list-add-button, and place it in an
      // element, that will be positioned absolute under the add-button when
      // hovered.
      $('.ding-list-add-button', context).each(function (delta, dlab) {
        var $buttons = $('.buttons', dlab)
          .css({
            position: 'absolute',
            display: 'none'
          })
          .addClass('dlab-breakout-button')
          .appendTo('body');

        // The .trigger is the "hit area" of the hover effect.
        $('.trigger', dlab).bind('mouseenter', function () {
          $buttons.css($(this).offset())
            .css('display', 'block');
          $(dlab).addClass('showing');
        });

        $buttons.bind('mouseleave', function () {
          $buttons.css('display', 'none');
          $(dlab).removeClass('showing');
        });
      });
    }
  };
}(jQuery));
