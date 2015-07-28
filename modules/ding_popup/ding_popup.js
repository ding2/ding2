
(function ($) {

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
    $('.ui-dialog-content input[type=text]:not(.ding-popup-processed), .ui-dialog-content input[type=password]:not(.ding-popup-processed)').addClass('ding-popup-processed').each(function () {
      $(this).keypress(function (event) {
        if (event.which == 13) {
          $($(this.form).find('input[type=submit]').get(0)).trigger('mousedown');
          return false;
        }
      });
    });
  }
};

/**
 * Object to handle popups.
 */
Drupal.ding_popup = {
  refresh: false,
  states: {},
  dialogs: {},

  setState: function (response) {
    var self = this;
    if (this.dialogs[response.name] == undefined) {
      this.dialogs[response.name] = $('<div class="ding-popup-content"></div>').dialog({
          autoOpen: false,
          modal: true,
          draggable: false,
          closeText : Drupal.t('close'),
          close: function(event, ui) {
            if (response['refresh'] || self.refresh === true) {
              // Ensure that the page is not reload, when the log in dialog is
              // closed.
              if (self.refresh && response.name === 'ding_user') {
                return;
              }
              window.location.reload(true);
            }
          }
      });
    }
    this.dialogs[response.name].dialog('option', {'title': response.title});
    this.dialogs[response.name].html(response.data);

    Drupal.attachBehaviors(this.dialogs[response.name]);
    this.dialogs[response.name].dialog('open');
  },

  open: function(response) {
    if (this.states[response.name] == undefined) {
      this.states[response.name] = [];
    }
    if (response['resubmit']) {
      this.states[response.name].push(response);
    }
    this.setState(response);
  },

  close: function(response) {
    while (this.states[response.name].length > 0) {
      var state = this.states[response.name].pop();
      Drupal.detachBehaviors(this.dialog);

      // User login have been preformed, so page need to be reloaded.
      if (state.name === 'ding_user') {
        this.refresh = true;
      }

      // Add in extra post vars.
      $.extend(state['orig_ajax'].options.data, state['extra_data']);
      // Call original ajax callback.
      state['orig_ajax'].eventResponse(state['orig_ajax'], null);
    }
    if (this.dialogs[response.name].refresh_on_close) {
      alert('refresh');
    }
    this.dialogs[response.name].dialog('close');
  }
};

/**
 * Command to create a popup.
 */
Drupal.ajax.prototype.commands['ding_popup'] = function (ajax, response, status) {
  response['orig_ajax'] = ajax;
  Drupal.ding_popup.open(response);
};

/**
 * Command to close a popup.
 */
Drupal.ajax.prototype.commands['ding_popup_close'] = function (ajax, response, status) {
  Drupal.ding_popup.close(response);
};


})(jQuery);
