/**
 * @file
 * Handle rules UI in the administration interface.
 */
(function ($) {
  'use strict';

  // The select type that have auto-complete callbacks.
  var auto_complete_types = [
    'page',
    'event',
    'news',
    'library',
    'group',
    'taxonomy'
  ];

  /**
   * Change handler for facet type selection.
   *
   * Fix facet selection boxes as #stats don't work with ajax forms and
   * "add another".
   *
   * @param event
   *   The event that triggered the handler.
   */
  function facetTypeChangeHandler(event) {
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

  /**
   * Rebuild auto-complete callbacks when rule type is changed.
   *
   * @param $context
   *   The context the auto-complete is located in.
   * @param value
   *   The selected value in the rule type select.
   */
  function rebuild_autocomplete($context, value) {
    var $obj = $('input.form-text', $context);
    $obj.unbind().removeClass('form-autocomplete').addClass('autocomplete-processed');

    // Remove span element (will be recreated).
    $('#' + $obj.attr('id') + '-autocomplete-aria-live', $context).remove();

    if (value === undefined) {
      console.log($context);
      value = $('select option:selected', $context).val();
      console.log(auto_complete_types.indexOf(value));
    }

    // Add auto complete if the value is one that has aut-complete support.
    if (auto_complete_types.indexOf(value) !== -1) {
      $context.find('input.autocomplete')
        .val('/ding_campaign_plus/autocomplete/' + value)
        .removeClass('autocomplete-processed')
        .end()
        .find('input.form-text')
        .addClass('form-autocomplete');

      Drupal.attachBehaviors($context);
    }
  }

  /**
   * Handle facet selection boxes.
   *
   * @type {{attach: Drupal.behaviors.ding_campaign_plus_facet_selectors.attach}}
   */
  Drupal.behaviors.ding_campaign_plus_facet_selectors = {
    attach: function (context, settings) {
      var facet_selectors = $('select[multiple="multiple"]', context);
      facet_selectors.parent().hide();

      var fact_type_selectors = $('.js-fact-type', context);

      // Bind change handler to the facet type selection dropdown.
      fact_type_selectors.once('ding-campaign-plus-facet-type').each(function() {
        $(this).bind('change', facetTypeChangeHandler);
      });

      // Ensures that the UI selections are initialized correct.
      fact_type_selectors.trigger('change');
    }
  };

  /**
   * Handle trigger type auto-complete callbacks.
   *
   * @type {{attach: Drupal.behaviors.ding_campaign_plus_other_triggers.attach}}
   */
  Drupal.behaviors.ding_campaign_plus_other_triggers = {
    attach: function (context, settings) {
      var local_context = $('#ding-campaign-triggers', context);

      // OnLoad actions.
      $('fieldset', local_context).once('ding-campaign-plus-triggers').each(function() {
        var $context = $(this);

        // Rebuild auto complete.
        rebuild_autocomplete($context);
      });

      // OnChange event for 'rule type' dropdown.
      $('select', local_context).once('ding-campaign-plus-trigger-type-select').change(function (event) {
        var fieldset = $(event.target).parentsUntil('fieldset');

        // Rebuild the auto-complete for the new type selected.
        rebuild_autocomplete(fieldset, this.value);

        // Clear rule value on rule type change.
        $('input.form-text', fieldset).val('');
      });
    }
  };

})(jQuery);
