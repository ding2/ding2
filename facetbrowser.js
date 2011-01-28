(function($) {
	Drupal.behaviors.facetbrowser = {
    attach: function(context, settings) {
      $('#block-ding-facetbrowser-facetbrowser .item-list li').click(function() {
        document.location.href =  '?' + 'facets=' + $(this).parent().parent().find('h3').text() + ':' + $(this).text();
      });
    }
	};	
})(jQuery);
