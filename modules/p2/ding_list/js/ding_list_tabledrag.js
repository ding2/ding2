/**
 * @file
 * Doc here.
 */
/*jshint forin:false, jquery:true, browser:true, indent:2, trailing:true, unused:false */
/*global Drupal */

(function ($) {
  "use strict";

  // Call initialize
  Drupal.behaviors.ding_list_sorting = {
    attach: function (context, settings) {
      $('.ding-list-list__elements', context).each(function () {
        var $table = $(this);

        if (Drupal.tableDrag[$table.attr('id')] === undefined) {
          return;
        }

        Drupal.tableDrag[$table.attr('id')].onDrop = function () {
          var list_id = $(this.table).attr('data-list-id'),
            $item = $(this.rowObject.element),
            self = this,
            data = {
              // The order is reversed (descending), so we use the next element
              // as the previous instead, so it's saved properly in the db.
              previous: $item.next().attr('data-element-id'),
              item: $item.attr('data-element-id')
            };

          if (!data.previous) {
            data.previous = 0;
          }

          $.ajax({
            url: Drupal.settings.basePath + 'dinglist/set_order/' + list_id,
            type: 'POST',
            dataType: 'json',
            data: data,
            success: function (data, textStatus, XMLHttpRequest) {
              $(self.table).find('.tabledrag-changed').remove();
            }
          });
        };
      });
    }
  };
}(jQuery));
