(function($) {

	Drupal.behaviors.tingFieldSearchElement = {

		attach: function(context, settings) {
			$(context).find('.remove').click(function() {
				var element = $(this).parent().parent();
				// Mark deleted
				element.find('.removed').val(1);
				// Hide it
				element.hide();
				// Cancel submit
				return false;
			});

			// Hide any removed elements on reload. This is needed if the user
			// removes an element and afterwards tries to add another.
			$(context).find('.removed').each(function(index, value) {
				if ($(value).val() > 0) {
					$(value).parent().parent().hide();
				}
			});
		}

	};

}(jQuery));
