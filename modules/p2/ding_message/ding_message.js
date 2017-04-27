/**
 * @file
 * Ding message javascript
 */

(function ($) {
  "use strict";
  
  function get_url_parameter(sParam) {
    var sPageURL = window.location.search.substring(1);
    var sURLVariables = sPageURL.split('&');
    for (var i = 0; i < sURLVariables.length; i++) {
      var sParameterName = sURLVariables[i].split('=');
      if (sParameterName[0] === sParam) {
        return decodeURIComponent(sParameterName[1]);
      }
    }
    return false;
  }

  // Handle display of new content in the search by marking new since last check.
  // We add a star to show that the content is new.
  Drupal.behaviors.ding_message = {
    attach: function (context) {
      var
        isSet = false,
        latestId = get_url_parameter('message');
      if(latestId && $('.ting-object-collection', context).size() > 0) {
        $('.ting-object-collection', context).each(function() {
          if(!isSet) {
            if($(this).attr('data-ting-object-id') === latestId) {
              isSet = true;
            }
            $(this).addClass('new-content-pending');
          }
        });
      }
      $('.ting-object-collection.new-content-pending', context).each(function() {
        if(isSet) {
          $(this).addClass('new-content');
          $(this).removeClass('new-content-pending');
          if($(this).attr('data-ting-object-id') === latestId) {
            return false;
          }            
        }
      });
      if(latestId && $('.ding-message-item', context).size() > 0) {
        $('.ding-message-item', context).each(function() {
          if($(this).attr('data-ting-object-id') === latestId) {
            isSet = true;
          }
          if(isSet) {
            $(this).addClass('new-content');
          }
        });
      }
    }
  };
})(jQuery);
