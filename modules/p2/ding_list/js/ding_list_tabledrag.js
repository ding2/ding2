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
    // Notice that we don't use context, because we want to process the whole page every time.
    attach: function (context, settings) {
      $('.view-id-ding_list_elements .tabledrag-toggle-weight-wrapper').hide();

      Drupal.tableDrag['ding-list'].onDrop = function() {
        var list_id = $(this.table).attr('data-list-id'),
          $item = $(this.rowObject.element),
          self = this,
          data = {
            previous: $item.prev().find('.views-field-id').attr('data-item-id'),
            item: $item.find('.views-field-id').attr('data-item-id')
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
            $(self).children(':even').removeClass('even').addClass('odd');
            $(self).children(':odd').removeClass('odd').addClass('even');
            $(self.table).find('.tabledrag-changed').remove();
          }
        });
      };
    }
  };
}(jQuery));