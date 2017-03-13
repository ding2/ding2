/*jshint forin:false, jquery:true, browser:true, indent:2, trailing:true, unused:false, -W084 */

(function ($) {
  'use strict';

  /**
   * Add a keypress handler on text and password fields that catches
   * return and submits the form by triggering the first submit
   * button. Otherwise the browser standard handler is used, and it
   * doesn't post by AJAX.
   *
   * @todo possibly support more input types.
   */
  Drupal.behaviors.ding_popup_form_submit = {
    attach: function (context, settings) {
      $('.popupbar-content input[type=text]:not(.ding-popup-processed), .popupbar-content input[type=password]:not(.ding-popup-processed)').addClass('ding-popup-processed').each(function () {
        $(this).keypress(function (event) {
          if (event.which == 13) {
            $($(this.form).find('input[type=submit]').get(0)).trigger('mousedown');
            return false;
          }
        });
      });
    }
  };

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

    ddbasic.popupbar.close();
  };

})(jQuery);
