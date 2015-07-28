(function ($) {
  Drupal.behaviors.tingProxyAdmin = {
    attach: function (context, settings) {
      // Attache onClick to remove buttons in the admin UI.
      $(context).find('.remove').click(function () {
        var obj = $(this);
        // Mark as deleted and fix required
        obj.parent().find('.removed').val(1);
    
        // Slide it up
        obj.parent().slideToggle('slow', function() {
          obj.parent().find('.url-text-field').val('removed');
        });
    
        // Cancel normal submit
        return false;
     });
    }
  };
}(jQuery));
