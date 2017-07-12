/**
 * @file
 * Add specific link buttons to be tracked via Webtrends.
 */

 /*global dcsMultiTrack */

(function($) {
  "use strict";

  Drupal.behaviors.track_webtrends = {
    attach: function () {

      // Array of selectors for links to track via webtrends.
      var webtrendsAdd = [
        '.action-button.reserve-button',
        '.action-button.bookmark-button',
        '.group-holdings-available a'
      ];

      $(webtrendsAdd.join(', ')).once('webtrends-add', function () {
        if ($(this).is('.group-holdings-available a')) {
          // Add attribute to links in "available materials"
          // collapsible. This will create a unique url instead of
          // using "#" as url.
          $(this).attr('webtrends_dcsuri', window.location.pathname + '/#group-holdings-available');
        }
        // Add "on click" event handler.
        $(this).click(function () {
          var dcsuri = $(this).attr('href');
          if ($(this).attr('webtrends_dcsuri')) {
            dcsuri = $(this).attr('webtrends_dcsuri');
          }
          dcsMultiTrack('DCS.dcsuri', dcsuri, 'WT.ti', $(this).text());
        });

        // Ensure our event handler is fired first by popping and
        // unshifting the "on click" event handlers. If we don't do
        // this the handler will not be called, because the event
        // handler - that prevents links from being opened directly in
        // the browser - prevents our event handler to be executed.
        // This way we can be sure that the action of clicking a link
        // is tracked, before the action related to the link is
        // performed.
        var clicks = $(this).data('events').click;
        var event = clicks.pop();
        clicks.unshift(event);
      });
    }
  };
}(jQuery));
