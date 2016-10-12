(function($) {
  "use strict";

  var backside_popup_data = {};

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
        $.each(coverData, function(local_id, data) {
          var $cover_wrapper = $('.ting-cover-object-id-' + local_id).parents('.work-cover');
          $(data.link).appendTo($cover_wrapper.find('.work-cover-selector'));
          backside_popup_data[local_id] = data.popup.data;
          $(data.popup.wrapper).appendTo($cover_wrapper.parent());
        });
      }
    });

    // Load PDF file on modal open.
    $(document).on('reveal:open', 'div[id^="reveal-cover-back-"]', function () {
      var modal = $(this);
      var reg_exp = /\d+/;
      var local_id = reg_exp.exec($(modal).attr('id'))[0];
      $(backside_popup_data[local_id]).appendTo($(modal).find('.reveal-cover-back-image'));
    });
  });
}(jQuery));
