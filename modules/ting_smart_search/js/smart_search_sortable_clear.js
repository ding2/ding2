(function($) {

  Drupal.behaviors.smartsearchSortableClearInput = {
      attach: function createInput(context, settings){
        $("#edit-field-sss-boost-materials .form-item.form-type-textfield", context).once().append('<input type="button" value="(x)" />');
      }
  };

  Drupal.behaviors.smartsearchSortableClearReset = {
      attach: function resetForm(context, settings) {
        $(this).prev().val('');
        $( "input[type='button']", context ).bind( "click", resetForm );
      }
  };

} (jQuery));
