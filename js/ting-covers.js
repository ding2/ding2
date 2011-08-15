(function($) {

  Drupal.extractCoverData = function(e) {
    classname = $(e).attr('class');
    id = classname.match(/ting-cover-object-id-(\S+)/);
    imageStyle = classname.match(/ting-cover-style-(\S+)/);
    if (!id) {
      return false;
    }
    return id[1] + ':' + imageStyle[1];
  };

  Drupal.insertCovers = function(coverData) {
    $.each(coverData, function(coverInfo, url) {
      coverInfo = coverInfo.split(':');
      $('.ting-cover-processing' + '.ting-cover-object-id-' + coverInfo[0] + '.ting-cover-style-' + coverInfo[1]).html('<img src="' + url + '"/>');
    });
  };

  Drupal.behaviors.tingCovers = {

    attach: function(context) {
      //Assemble information regarding covers
      var coverData = [];
      $('.ting-cover:not(.ting-cover-processing, .ting-cover-processed)', context).each(function(i, e) {
        coverData.push(Drupal.extractCoverData(e));
      }).addClass('ting-cover-processing');

      if (coverData.length > 0) {
        //Retrieve covers
        request = $.ajax({
          url: '/ting/covers',
          type: 'POST',
          data: {
            coverData: coverData
          },
          dataType: 'json',
          success: Drupal.insertCovers,
          //Keep state using classes
          complete: function(request, status) {
            processing = $('.ting-cover-processing', context);
            if (status == 'success') {
              processing.addClass('ting-cover-processed');
            }
            processing.removeClass('ting-cover-processing');
          }
        });

        //Associate the request with the context so we can abort the request
        //if the context is detached removed before completion
        $(context).data('request', request);
      }
    },
    detach: function(context) {
      //If we have a request associated with the context then abort it.
      //It is obsolete.
      var request = $(context).data('request');
      if (request) {
        request.abort();
      }
    }
  };

} (jQuery));

