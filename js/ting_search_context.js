(function($) {

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
            $("#ting-search-context").html(data);
          }
        }
      });				
      
    }
  }

})(jQuery);


