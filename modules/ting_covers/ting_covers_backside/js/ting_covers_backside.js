(function($) {
  "use strict";

  // Helper function to get information about a given cover place holder.
  var ting_covers_backside_extract_data = function(e) {
    var classname = $(e).attr('class');
    var imageStyle = classname.match(/ting-cover-style-(\S+)/);
    var id = classname.match(/ting-cover-object-id-(\S+)/);
    return {
      local_id : id[1],
      image_style : imageStyle[1]
    };
  };

  $(document).ready(function () {
    // Assemble information regarding covers.
    var cover_data = [];

    // Extract cover information from the dom.
    $('.ting-cover').each(function(index, element) {
      cover_data.push(ting_covers_backside_extract_data(element));
    });

    $.ajax({
      url: Drupal.settings.basePath + 'ting/covers/backside',
      type: 'POST',
      data: {
        coverData: cover_data
      },
      dataType: 'json',
      success: function (coverData) {
        $.each(coverData, function(coverInfo, data) {
          var $cover_wrapper = $('.ting-cover-object-id-' + coverInfo).parents('.work-cover');
          $(data.link).appendTo($cover_wrapper.find('.work-cover-selector'));
          $(data.popup).appendTo($cover_wrapper.parent());
        });
      }
    });
  });
}(jQuery));
