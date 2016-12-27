(function($) {
    'use strict';

    Drupal.behaviors.ding_item_list = {
        attach: function (context) {

            $('.ding-item-list', context).each(function () {
                var hash = $(this).data('hash');
                var ding_item_list = (Drupal.settings[hash] !== undefined) ? Drupal.settings[hash] : '';
                if (ding_item_list !== '') {
                    $.getJSON(Drupal.settings.basePath + 'ding_item_list/' + hash, {content: ding_item_list}, function (content) {
                        $('.pane-ding-item-list', context).find('[data-hash=' + hash + ']').replaceWith(content);
                    });
                }
            });
        }
    };
} (jQuery));
