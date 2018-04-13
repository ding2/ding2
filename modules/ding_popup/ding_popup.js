/*jshint forin:false, jquery:true, browser:true, indent:2, trailing:true, unused:false, -W084 */

(function ($) {
  'use strict';

  var
    states = {},
    refresh = false;

  /**
   * Command to create a popup.
   */
  Drupal.ajax.prototype.commands.ding_popup = function (ajax, response, status) {
    var onclose;

    // Ensure that the page is not reload, when the log in dialog is closed.
    if (response.refresh === true || (refresh === true && response.name !== 'ding_user')) {
      onclose = function () {
        location.reload(true);
        return false;
      };
    }

    if (states[response.name] === undefined) {
      states[response.name] = [];
    }
    if (response.resubmit === true) {
      response.orig_ajax = ajax;
      states[response.name].push(response);
    }

    var $content = ddbasic.popupbar.set(response.name, response.data, false, onclose);
    Drupal.attachBehaviors($content);
  };

  /**
   * Command to close a popup.
   */
  Drupal.ajax.prototype.commands.ding_popup_close = function (ajax, response, status) {
    var state;
    if (states[response.name] !== undefined) {
      while (state = states[response.name].pop()) {
        // User login have been performed, so page needs to be reloaded.
        if (state.name === 'ding_user') {
          refresh = true;
        }

        // Add in extra post vars.
        $.extend(state.orig_ajax.options.data, state.extra_data);
        // Call original ajax callback.
        state.orig_ajax.eventResponse(state.orig_ajax, null);
      }
    }

    // If the global refresh is true the ajax will reload after the popup is
    // closed. This allows for responses before refreshing.
    if (refresh === false && response.refresh === true) {
      location.reload(true);
      return;
    }

    ddbasic.popupbar.close();
  };

  Drupal.behaviors.popupbar = {
    attach: function(context, settings) {
      $('.close-popupbar', context).on('click', function (evt) {
        evt.preventDefault();
        ddbasic.popupbar.close();
      });
    }
  };

})(jQuery);
