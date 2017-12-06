/**
 * @file
 * Handle campaigns.
 */
(function ($) {
  'use strict';

  /**
   * Handle trigger type auto-complete callbacks.
   *
   * @type {{attach: Drupal.behaviors.ding_campaign_plus_basic_triggers.attach}}
   */
  Drupal.behaviors.ding_campaign_plus_node_edit = {
    attach: function (context, settings) {
      $('.form-item-ding-campaign-plus-auto-generate-link').once(function () {
        if (!$(':input[name="ding_campaign_plus_auto_generate[enable]"]').is(':checked')) {
          $(this).hide();
        }
      });
      $('.form-item-ding-campaign-plus-auto-generate-keywords').once(function () {
        if (!$(':input[name="ding_campaign_plus_auto_generate[enable]"]').is(':checked')) {
          $(this).hide();
        }
      });

    }
  };

})(jQuery);
