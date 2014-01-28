(function($) {

	Drupal.behaviors.tingSearchContext = {

		attach: function(context, settings) {
			$("#edit-field-ting-search-context").once(function() {
				$(".field_ting_search_context_reset_field").click(function(e) {
					e.preventDefault();
					var weightFormItem = $(this).prev();
					var categoryFormItem = weightFormItem.prev();
					weightFormItem.find("select").val(0);
					categoryFormItem.find("select").val(0);
				});
			});
		}

	};	

})(jQuery);