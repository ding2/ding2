(function ($) {

  Drupal.behaviors.ding_campaign_init = {
      bindAutocomplete: function(obj, type) {
        // Add autocomplete behavior to 'rule value' input.
        $(obj).find('input.autocomplete')
        .val(Drupal.settings.ding_campaign_init.autocompleteUrl + type)
        .removeClass('autocomplete-processed')
        .end()
        .find('input.form-text')
        .addClass('form-autocomplete');
        Drupal.attachBehaviors($(obj));
      },

      rebuildAutocomplete: function ($context, value) {
        var $obj = $('input.form-text', $context);
        $obj.unbind().removeClass('form-autocomplete').addClass('autocomplete-processed');

        // Remove span element (will be recreated).
        $('#' + $obj.attr('id') + '-autocomplete-aria-live', $context).remove();

        if (value == undefined) {
          value = $('select option:selected', $context).val();
        }

        if (value == 'rule_page' || value == 'rule_event' || value == 'rule_news' || value == 'rule_taxonomy' || value == 'rule_library') {
          // Add autocomplete.
          Drupal.behaviors.ding_campaign_init.bindAutocomplete($context, value);
        }
      },

      attach: function (context, settings) {
        // OnLoad actions.
        $('.ding-campaign-rule', context).once('ding_campaign_init_start').each(function(){
          var $context = $(this);
          // Rebuild autocomplete.
          Drupal.behaviors.ding_campaign_init.rebuildAutocomplete($context);

          // Hide rule value for generic type.
          if ($('select option:selected', $context).val() == 'rule_generic') {
            $('.rule-value', $context).hide();
          }
        });

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
            Drupal.behaviors.ding_campaign_init.rebuildAutocomplete($context, value);
          }

          // Clear rule value on rule type change.
          $('input.form-text', $context).val('');
        });
      }
  };

})(jQuery);
