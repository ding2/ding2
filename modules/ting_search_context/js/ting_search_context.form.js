(function($) {

	Drupal.behaviors.tingSearchContextForm = {

		attach: function(context, settings) {
			// Hide rating select box on the last field item.
			$("#edit-field-ting-search-context tr:last-child td:nth-child(2) div:nth-child(2)", context).hide();
			// Change hanlder on context name select box.
			$(".field_ting_search_context_name", context).change(function(e) {
				var ratingFormItem = $(this).parent().next();
				$(this).val() == 0 ? ratingFormItem.hide() : ratingFormItem.show();
			});
			// CLick handler for the reset button.
			$(".field_ting_search_context_remove", context).click(function(e) {
				e.preventDefault();
				var ratingFormItem = $(this).prev();
				var nameFormItem = ratingFormItem.prev();
				ratingFormItem.hide();
				nameFormItem.find("select").val(0);
			});
		}

	};

})(jQuery);