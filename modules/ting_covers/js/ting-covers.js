(function($) {
  "use strict";

  // Helper function to get information about a given cover place holder.
  var ting_covers_extract_data = function(e) {
    var classname = $(e).attr('class');
    var imageStyle = classname.match(/ting-cover-style-(\S+)/);
    var id = classname.match(/ting-cover-object-id-(\S+)/);
    return {
      local_id : id[1],
      image_style : imageStyle[1]
    };
  };

  var ting_cover_insert = function(coverData) {
    if(coverData === false){
      return;
    }
    $.each(coverData, function(coverInfo, data) {
      // thumbnail
      if (data.urls.thumbnail != undefined) {
        var img = '<img src="' + data.urls.thumbnail + '" alt=""/>';
        $('.ting-cover-processing' + '.ting-cover-object-id-' + data.local_id + ' a').html(img);
        $('.ting-cover-processing' + '.ting-cover-object-id-' + data.local_id + ' a').parents('.work-cover').show();
      }
      // large
      if (data.urls.detail != undefined) {
        var img = '<img src="' + data.urls.detail + '" alt=""/>';
          $('.ting-cover-processing' + '.ting-cover-object-id-' + data.local_id).parents('.work-cover').siblings('.reveal-cover-large').find('.reveal-cover-large-image').html(img);
      }
      // back cover
      if (data.urls.backpage != undefined) {
        var pdf = '<object data="' + data.urls.backpage + '" type="application/pdf" width="590" height="925">' +
          '<p>It appears you dont have a PDF plugin for this browser. ' +
          'No biggie... you can ' +
          '<a href="' + data.urls.backpage + '">click here to download the PDF file.</a>' +
          '</p>' +
          '</object>';
        $('.ting-cover-processing' + '.ting-cover-object-id-' + data.local_id).parents('.work-cover').siblings('.reveal-cover-back').find('.reveal-cover-back-image').html(pdf);
        $('.ting-cover-processing' + '.ting-cover-object-id-' + data.local_id).parents('.work-cover').find('.cover-front').show();
        $('.ting-cover-processing' + '.ting-cover-object-id-' + data.local_id).parents('.work-cover').find('.cover-back').show();

      }
    });
  };

  Drupal.behaviors.tingCovers = {
    attach: function(context) {
      // Assemble information regarding covers.
      var cover_data = [];

      // Extract cover information from the dom.
      $('.ting-cover:not(.ting-cover-processing, .ting-cover-processed)', context).each(function(index, element) {
        cover_data.push(ting_covers_extract_data(element));
      }).addClass('ting-cover-processing');

      if (cover_data.length > 0) {
        //Retrieve covers
        var request = $.ajax({
          url: Drupal.settings.basePath + 'ting/covers',
          type: 'POST',
          data: {
            coverData: cover_data
          },
          dataType: 'json',
          success: ting_cover_insert,
          // Update processing state.
          complete: function(request, status) {
            var processing = $('.ting-cover-processing', context);
            if (status === 'success') {
              processing.addClass('ting-cover-processed');
            }
            processing.removeClass('ting-cover-processing');
          }
        });

        // Associate the request with the context so we can abort the request if
        // the context is detached removed before completion.
        $(context).data('request', request);
      }
    },
    detach: function(context) {
      // If we have a request associated with the context then abort it.
      var request = $(context).data('request');
      if (request) {
        request.abort();
      }
    }
  };
}(jQuery));
