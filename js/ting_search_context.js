/**
 * @file ding.availability.js
 * JavaScript behaviours for fetching and displaying availability.
 */

(function($) {
  "use strict";

  Drupal.behaviors.tingSearchContextGetNodes = {
    attach: function(context, settings) {
      $.ajax({
        type: "POST",
        url: Drupal.settings.basePath + "ting/searchcontext/ajax",
        dataType: "json",
        data: {
          "search_context" : settings.ting_search_context
        },
        success: function (data) {
          if (data != null) {
            var container;
            container = ting_search_context_get_container(settings.ting_search_context_position);
            container.html(data);
          }
        }
      });

    }
  };

  /**
   * Choose position for related content based on search_context_position_setting
   *
   * Deside which element should hold the related content based on
   * the search_context_position_setting
   *
   * @param position
   *   Class name of element to hold the related content.
   * @returns container
   *   Element choosen to hold the related content.
   */
  function ting_search_context_get_container(position) {
    //the default position is below the search result so if there is no class-match the last occurance is the best choice.
    var container;
    container = $(".pane-search-context").last();

    $(".pane-search-context").each(function( index ) {
      if ($(this).hasClass(position)) {
        container = $(this);
      }
    });

    return container;
  }

})(jQuery);


