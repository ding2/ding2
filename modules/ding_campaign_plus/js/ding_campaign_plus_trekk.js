/**
 * @file
 * Added webtrekk view tracking to campaigns.
 */
(function ($) {
  'use strict';

  // Use custom event fired when campaign is loaded to track the campaign.
  $(document).on('campaignPlusLoaded', function (event, campaignId) {
    // The global wt (webtrekk) object is only loaded on approved domains. So to
    // not block execution test for the variable.
    if (typeof(wt) !== 'undefined') {
      wt.sendinfo({
        campaignId: campaignId,
        campaignAction: 'view'
      });
    }
  });
})(jQuery);