/**
 * @file
 * Handle campaigns.
 */

(function ($) {
  'use strict';

  /**
   * Load lazy loaded campaigns.
   */
  Drupal.behaviors.ding_campaign_plus_lazy_load = {
    attach: function (context) {
      $('[data-ding-campaign-plus-cid]', context).once(function () {
        var campaign = $(this);
        var cid = campaign.data('ding-campaign-plus-cid');
        var url = Drupal.settings.basePath + Drupal.settings.pathPrefix + 'ding_campaigns_plus/' + cid;
        $.get(url, {}, function (response) {
          campaign.replaceWith(response);
        });

      });
    }
  };

  /**
   * Handle trigger type auto-complete callbacks.
   *
   * @type {{attach: Drupal.behaviors.ding_campaign_plus_basic_triggers.attach}}
   */
  Drupal.behaviors.ding_campaign_plus_node_edit = {
    attach: function (context) {
      $('.form-item-ding-campaign-plus-auto-generate-keywords', context).once(function () {
        if (!$(':input[name="ding_campaign_plus_auto_generate[enable]"]').is(':checked')) {
          $(this).hide();
        }
      });
    }
  };

})(jQuery);
