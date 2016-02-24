(function ($) {
    Drupal.behaviors.pathAutoDisable = {
        attach: function (context) {
            // fake a disabled checkbox
            var check = $('#edit-path-pathauto');
            check.attr('checked', 'checked');
            check.css('opacity','0.5');
            check.change(function(context){
                check.attr('checked', 'checked');
            })
        }
    }
})(jQuery);
