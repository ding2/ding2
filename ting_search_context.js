(function($) {

	Drupal.behaviors.tingSearchContext = {

		attach: function(context, settings) {
			$("#edit-field-ting-search-context").once(function() {
				// Hide rating select box on the last field item.
				$("#field-ting-search-context-values tr:last-child td:nth-child(2) div:nth-child(2)").hide();

				// CLick handler for the reset button.
				$(".field_ting_search_context_remove").click(function(e) {
					e.preventDefault();
					var ratingFormItem = $(this).prev();
					var nameFormItem = ratingFormItem.prev();
					ratingFormItem.hide().find("select").val(1);
					nameFormItem.find("select").val(0);
				});
			});
		}

	};	

})(jQuery);