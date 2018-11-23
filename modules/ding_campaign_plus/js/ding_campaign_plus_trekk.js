/**
 * @file
 * Added webtrekk view tracking to campaigns.
 */
(function ($) {
  'use strict';

  var queue = [];

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
    else {
      queue.push({
        campaignId: campaignId,
        campaignAction: 'view'
      });
    }
  });

  // Try to busy wait for the "wt" variable to exists in global space to push
  // variables to webtrekk. There will always be a race-condition here and
  // this was the best try to get around it.
  var timer = setInterval(processQueue, 500);
  function processQueue() {
    if (typeof(wt) !== 'undefined') {
      clearInterval(timer);
      for (var i in queue) {
        wt.sendinfo(queue[i]);
      }
    }
  }
})(jQuery);
