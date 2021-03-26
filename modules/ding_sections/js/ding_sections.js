/**
 * @file
 */
(function ($) {
  "use strict";

  Drupal.behaviors.ding_sections = {
    attach: function () {

      // Adding classes to ding_event_calendar event list.
      let section_event_list_items = Drupal.settings.ding_sections.section_event_list_items;
      if (section_event_list_items !== undefined) {
        if (section_event_list_items.length !== 0) {
          let all_list_items = $('#eventList').find('.event-item');
          $.each(section_event_list_items, function (index, new_class) {
            let item = all_list_items[index];
            $(item).addClass(new_class);
          });
        }
      }

      // Adding classes to ding_nodelist widgets.
      let nodelist_groups = Drupal.settings.ding_sections.nodelist_items;
      if (nodelist_groups !== undefined) {
        $.each(nodelist_groups, function (unique_id, data_array) {
          let nodelist_group;

          // Get separated nodelist widget and pane unique_id.
          let split_array = unique_id.split(':');

          // Process nodelist widgets.
          if (split_array[0] === 'ding_nodelist_widget_rolltab') {
            nodelist_group = $('.' + split_array[1]).find('.ding-tabroll').find('.ding-tabroll');
          }
          else if (split_array[0] === 'ding_nodelist_widget_minimal_display') {
            nodelist_group = $('.' + split_array[1]).find('.minimal-item');
          }
          else if (split_array[0] === 'ding_nodelist_widget_promoted_nodes') {
            nodelist_group = $('.' + split_array[1]).find('.ding_nodelist-pn-item');
          }
          else if (split_array[0] === 'ding_nodelist_widget_carousel') {
            nodelist_group = $('.' + split_array[1]).find('.ding_nodelist-items .slick-list .slick-track').children().once();
          }
          else {
            nodelist_group = $('.' + split_array[1]).find('.ding_nodelist-items').children();
          }

          if (nodelist_group.length !== 0) {
            // Preparing "data_array" array for processing in case when widget
            // is "_ding_nodelist_widget_carousel".
            if (nodelist_group.parents().hasClass('ding_nodelist-carousel')) {
              // When loading page after "clear cache", the count of
              // "nodelist_group" items is equal with count of items in nodelist.
              // In this case we have to duplicate those items in order to make
              // correct matching between "nodelist_group" and "data_array".
              if ((nodelist_group.length - 1)/data_array.length === 2) {
                data_array = data_array.concat(data_array);
              }

              // Get the last item of "data_array" array and append this into
              // the first position so it matches with "nodelist_group" item
              // with "data-slick-index = -1".
              let last = data_array[data_array.length - 1];
              data_array.unshift(last);
            }

            $.each(nodelist_group, function (index, item) {
              if (data_array[index] !== 'empty' && !$(item).hasClass('event-list-leaf')) {
                $(item).addClass(data_array[index]);
              }
            });
          }
        });
      }
    }
  };
})(jQuery);
