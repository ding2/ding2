/*jshint forin:false, jquery:true, browser:true, indent:2, trailing:true, unused:false */

(function (scope, $) {
  'use strict';

  var
    states = {},
    refresh = false;
    
    window.sss = states;

  Drupal.ajax.prototype.commands.ding_popup = function (ajax, response, status) {
    var onclose;
    
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

  Drupal.ajax.prototype.commands.ding_popup_close = function (ajax, response, status) {
    var state;
    while (state = states[response.name].pop()) {
      // User login have been preformed, so page need to be reloaded.
      if (state.name === 'ding_user') {
        refresh = true;
      }

      // Add in extra post vars.
      $.extend(state['orig_ajax'].options.data, state['extra_data']);
      // Call original ajax callback.
      state['orig_ajax'].eventResponse(state['orig_ajax'], null);      
    }

    ddbasic.popupbar.close();
  };
}(this, jQuery));
