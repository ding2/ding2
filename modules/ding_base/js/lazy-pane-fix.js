/**
 * @file
 * A few fixes for the lazy pane ajax implementation.
 *
 * Might not be needed with future lazy pane versions.
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
