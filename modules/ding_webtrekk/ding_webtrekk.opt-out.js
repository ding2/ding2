/**
 * @file
 * Implement opt-out option for the Webtrekk cookie.
 */

(function($) {

  "use strict";

  Drupal.behaviors.ding_webtrekk_opt_out = {
    attach: function(context) {
      $('.webtrekk-opt-out', context).click(function(e) {
        e.preventDefault();
        // If Webtrekk is not setup correctly, we might not have this.
        if (typeof webtrekkV3 === 'undefined') {
          return;
        }

        webtrekk = new webtrekkV3();
        // track the opt-out event in Webtrekk.
        webtrekk.sendinfo({linkId: 'event_optout'});
        // Set the opt-out cookie (for 5 years).
        webtrekk.setCookie ('webtrekkOptOut', 1, 60 * 60 * 24 * 30 * 12 * 5);

        // Use ding_popup to show confirmation text.
        var text = '<p>' + Drupal.t('You have successfully excluded yourself from tracking.') + '</p>';
        var popup = ddbasic.popupbar.set('ding_webtrekk', text, false);
        $('.close-popupbar', popup).click(function(e) {
          e.preventDefault();
          ddbasic.popupbar.close();
        });
      });
    }
  };
})(jQuery);
