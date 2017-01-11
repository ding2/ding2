/**
 * @file
 * Fixes for the lazy pane ajax implementation.
 *
 * Instead of using the Drupal.ajax handler lazy_pane uses it's own custom ajax
 * handler, which resembles the core handler.
 * But the current lazy_pane handler only supports the 'insert' and 'settings'
 * ajax command.
 * This fix listens for lazy_pane ajax, and calls the core commands for the
 * missing commands.
 *
 * The lazy_pane module doesn't expose it's own handler, which is why this
 * listens for all jQuery ajaxSuccess events.
 */

(function ($) {
  "use strict";

  var SUPPORTED_LAZY_PANE_COMMANDS = ['insert', 'settings'];

  // Hook into the general ajaxSuccess to fill in the missing ajax commands.
  $(document).ajaxSuccess(function(evt, jqXHR, ajaxOptions, data) {
    if (ajaxOptions.url === '/lazy-pane/ajax') {
      for (var i in data) {
        // Don't do anything if lazy pane already support the command.
        if ($.inArray(data[i].command, SUPPORTED_LAZY_PANE_COMMANDS) > -1) {
          continue;
        }

        if (Drupal.ajax.prototype.commands[data[i].command]) {
          // We dont have a Drupal.ajax object, so we pass an empty dummy object
          // to the command. This will result in some of the commands not
          // working.
          Drupal.ajax.prototype.commands[data[i].command]({}, data[i], 'success');
        }
      }
    }
  });

}(jQuery));
