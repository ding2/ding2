/**
 * @file
 * Handle rules UI in the administration interface.
 */
(function ($) {
  'use strict';

  // The select type that have auto-complete callbacks.
  // @TODO: Get these from the backend via drupal.settings.
  var auto_complete_types = [
    'page',
    'event',
    'news',
    'library',
    'group',
    'taxonomy'
  ];

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
    $obj.off().removeClass('form-autocomplete').addClass('autocomplete-processed');

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
        .val('/ding_campaign_plus/basic/autocomplete/' + value)
        .removeClass('autocomplete-processed')
        .end()
        .find('input.form-text')
        .addClass('form-autocomplete');

      Drupal.attachBehaviors($context);
    }
  }

  /**
   * Handle trigger type auto-complete callbacks.
   *
   * @type {{attach: Drupal.behaviors.ding_campaign_plus_basic_triggers.attach}}
   */
  Drupal.behaviors.ding_campaign_plus_basic_triggers = {
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
