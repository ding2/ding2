// Add specific link buttons to be tracked via Webtrends.
// The following buttons will be tracked:
// - Reserve/bookmark
// - See online
// - See available materials
// - External urls from review section
(function($) {
  var hash = {};
  Drupal.behaviors.track_webtrends = {
    attach: function (context) {
      // Add extra attributes to specific <a> tags (online urls and see online buttons). These attributes adds the
      // correct DCS.dcssip and DCS.dcsuri values for dcsMultiTrack.
      $('.online_url, .button-see-online').each(function() {
        var href = $(this).attr('href');
        var matches = href.match(/^(https?:\/\/.+?)(\/.+)$/);
        $(this).attr('webtrends_dcssip', matches[1]);
        $(this).attr('webtrends_dcsuri', matches[2]);
      });
      // Add attribute to "available materials" collapsible. This will create a unique url instead of using "#" as url.
      $('.group-holdings-available a').each(function() {
        $(this).attr('webtrends_dcsuri', window.location.pathname + '/#group-holdings-available');
      });

      // Array of selectors for links to track via webtrends.
      var webtrendsAdd = [
        '.action-button.reserve-button',
        '.action-button.bookmark-button',
        '.button-see-online',
        '.group-holdings-available a',
        '.online_url'
      ];
      $.each(webtrendsAdd, function(key, val) {
        $(val).each(function () {
          // Check if we have already processed this link. Use either id or href as hash key.
          if ($(this).hasClass('online_url')) {
            id = $(this).attr('href');
          } else {
            var id = $(this).attr('id');
          }
          if (!(id in hash)) {
            // Save current id in hash.
            hash[id] = true;

            // Add "on click" event handler.
            $(this).click(function (event) {
              var dcsuri = $(this).attr('href');
              if ($(this).attr('webtrends_dcsuri')) {
                dcsuri = $(this).attr('webtrends_dcsuri');
              }
              if ($(this).attr('webtrends_dcssip')) {
                dcsMultiTrack('DCS.dcssip', $(this).attr('webtrends_dcssip'), 'DCS.dcsuri', dcsuri, 'WT.ti', $(this).text());
              } else {
                dcsMultiTrack('DCS.dcsuri', dcsuri, 'WT.ti', $(this).text())
              }
            });

            // Ensure our event handler is fired first by popping and unshifting the "on click" event handlers.
            // If we don't do this the handler will not be called, because the event handler - that prevents links
            // from being opened directly in the browser - prevents our event handler to be executed.
            // This way we can be sure that the action of clicking a link is tracked, before the action related to the
            // link is performed.
            var clicks = $(this).data('events').click;
            var event = clicks.pop();
            clicks.unshift(event);
          }
        });
      });
    }
  };
}(jQuery));
