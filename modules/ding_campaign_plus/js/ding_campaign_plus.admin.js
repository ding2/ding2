/**
 * @file
 * Handle changes to auto complete callbacks when rule type is changed.
 */
(function ($) {
  'use strict';

  /**
   * Change handler for facet type selection.
   *
   * Fix facet selection boxes as #stats don't work with ajax forms and
   * "add another".
   *
   * @param event
   *   The event that triggered the handler.
   */
  function changeHandler(event) {
    var fieldset = $(event.target).parentsUntil('fieldset');
    switch (this.value) {
      case 'facet.type':
        $('div[class$="facet-value-select-type"]', fieldset).show();
        $('div[class$="facet-value-select-source"]', fieldset).hide();
        $('div[class$="facet-value"]', fieldset).hide();
        break;

      case 'facet.acSource':
        $('div[class$="facet-value-select-source"]', fieldset).show();
        $('div[class$="facet-value-select-type"]', fieldset).hide();
        $('div[class$="facet-value"]', fieldset).hide();
        break;

      default:
        $('div[class$="facet-value-select-type"]', fieldset).hide();
        $('div[class$="facet-value-select-source"]', fieldset).hide();
        $('div[class$="facet-value"]', fieldset).show();
    }
  }

  Drupal.behaviors.ding_campaign_plus_auto_complete = {
    attach: function (context, settings) {
      var facet_selectors = $('select[multiple="multiple"]', context);
      facet_selectors.parent().hide();

      var fact_type_selectors = $('.js-fact-type', context);

      // When "add another" is clicked the attach behaviors is called more
      // than once, so the simple solution was to unbind the event before
      // bind to ensure only one handler.
      fact_type_selectors.unbind('change', changeHandler);
      fact_type_selectors.bind('change', changeHandler);
    }
  }

  // Drupal.behaviors.ding_campaign_init = {
  //     bindAutocomplete: function(obj, type) {
  //       // Add autocomplete behavior to 'rule value' input.
  //       $(obj).find('input.autocomplete')
  //       .val(Drupal.settings.ding_campaign_init.autocompleteUrl + type)
  //       .removeClass('autocomplete-processed')
  //       .end()
  //       .find('input.form-text')
  //       .addClass('form-autocomplete');
  //       Drupal.attachBehaviors($(obj));
  //     },
  //
  //     rebuildAutocomplete: function ($context, value) {
  //       var $obj = $('input.form-text', $context);
  //       $obj.unbind().removeClass('form-autocomplete').addClass('autocomplete-processed');
  //
  //       // Remove span element (will be recreated).
  //       $('#' + $obj.attr('id') + '-autocomplete-aria-live', $context).remove();
  //
  //       if (value == undefined) {
  //         value = $('select option:selected', $context).val();
  //       }
  //
  //       if (value == 'rule_page' || value == 'rule_event' || value == 'rule_news' || value == 'rule_taxonomy' || value == 'rule_library') {
  //         // Add autocomplete.
  //         Drupal.behaviors.ding_campaign_init.bindAutocomplete($context, value);
  //       }
  //     },
  //
  //     attach: function (context, settings) {
  //       // OnLoad actions.
  //       $('.ding-campaign-rule', context).once('ding_campaign_init_start').each(function(){
  //         var $context = $(this);
  //         // Rebuild autocomplete.
  //         Drupal.behaviors.ding_campaign_init.rebuildAutocomplete($context);
  //
  //         // Hide rule value for generic type.
  //         if ($('select option:selected', $context).val() == 'rule_generic') {
  //           $('.rule-value', $context).hide();
  //         }
  //       });
  //
  //       // OnChange event for 'rule type' dropdown.
  //       $('.ding-campaign-rule select', context).once('ding_campaign_init').change(function () {
  //         var $context = $(this).parent().parent().parent();
  //         var value = $(this).selected().val();
  //         if (value == 'rule_generic') {
  //           // Generic does not need a 'rule value'.
  //           $('.rule-value', $context).hide();
  //         }
  //         else {
  //           // Add/remove autocomplete for 'rule value'.
  //           $('.rule-value', $context).show();
  //
  //           // Remove autocomplete.
  //           // Needed to prevent duplicating autocomplete behavior.
  //           Drupal.behaviors.ding_campaign_init.rebuildAutocomplete($context, value);
  //         }
  //
  //         // Clear rule value on rule type change.
  //         $('input.form-text', $context).val('');
  //       });
  //     }
  // };

})(jQuery);
