(function($) {

	Drupal.behaviors.tingSearchContextAdmin = {

		attach: function(context, settings) {
			// Loop through each row in the overview table
			$("#ting-search-context-overview-table tr", context).each(function(index) {
				var row = $(this);
				var checkBox = row.find("input:checkbox");
				// Make sure selected rows is checked and unselected is unchecked.
				// This might get out of sync if the user has changed selection, and
				// clicks refresh instead of the update button.
				if (row.hasClass("selected")) {
					checkBox.attr("checked", true);
				}
				else {
					checkBox.attr("checked", false);
				}
			});
		}

	};

})(jQuery);