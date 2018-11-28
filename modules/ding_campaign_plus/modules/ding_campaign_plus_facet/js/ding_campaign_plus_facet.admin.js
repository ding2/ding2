/**
 * @file
 * Handle rules UI in the administration interface.
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

      case 'facet.subject':
        $('div[class$="facet-value-select-type"]', fieldset).hide();
        $('div[class$="facet-value-select-source"]', fieldset).hide();
        $('div[class$="facet-value"]', fieldset).show();
        break;

      default:
        $('div[class$="facet-value-select-type"]', fieldset).hide();
        $('div[class$="facet-value-select-source"]', fieldset).hide();
        $('div[class$="facet-value"]', fieldset).show();
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
        $(this).on('change', facetTypeChangeHandler);
      });

      // Ensures that the UI selections are initialized correct.
      fact_type_selectors.trigger('change');
    }
  };

})(jQuery);
