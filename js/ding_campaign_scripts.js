(function ($) {

  Drupal.behaviors.ding_campaing_init = {
      bindAutocomplete: function(obj, type) {
        // Add autocomplete bevavior to 'rule value' input.
        $(obj).find('input.autocomplete')
        .val(Drupal.settings.ding_campaing_init.autocompleteUrl + type)
        .removeClass('autocomplete-processed')
        .end()
        .find('input.form-text')
        .addClass('form-autocomplete');
        Drupal.attachBehaviors($(obj));
      },

      attach: function (context, settings) {
        // OnChange event for 'rule type' dropdown.
        $('.ding-campaign-rule select', context).once('ding_campaign_init').change(function () {
          var $context = $(this).parent().parent().parent();
          var value = $(this).selected().val();
          if (value == 'rule_generic') {
            // Generic does not need a 'rule value'.
            $('.rule-value', $context).hide();
          }
          else {
            // Add/remove autocomplete for 'rule value'.
            $('.rule-value', $context).show();

            // Remove autocomplete.
            // Needed to prevent duplicating autocomplete behavior.
            var $obj = $('input.form-text', $context);
            $obj.unbind().removeClass('form-autocomplete');
            $('#' + $obj.attr('id') + '-autocomplete-aria-live', $context).remove();

            if (value == 'rule_page' || value == 'rule_event' || value == 'rule_news' || value == 'rule_taxonomy' || value == 'rule_library') {
              // Add autocomplete.
              Drupal.behaviors.ding_campaing_init.bindAutocomplete($context, value);
            }
          }
          // Crear rule value on rule type change.
          $('input.form-text', $context).val('');
        });
      }
  };

})(jQuery);
