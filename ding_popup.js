
(function ($) {

/**
 * Add a keypress handler on text and password fields that catches
 * return and submits the form by triggering the first submit
 * button. Else the browser standard handler is used, and it doesn't
 * post by AJAX.
 *
 * @todo possibly support more input types.
 */
Drupal.behaviors.ding_popup_form_submit = {
  attach: function (context, settings) {
    $('.ui-dialog-content input[type=text]:not(.ding-popup-processed), .ui-dialog-content input[type=password]:not(.ding-popup-processed)').addClass('ding-popup-processed').each(function () {
      $(this).keypress(function (event) {
        if (event.which == 13) {
          $($(this).parents('form').find('input[type=submit]').get(0)).trigger('mousedown');
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
  states: {},
  dialogs: {},

  setState: function (response) {
    if (this.dialogs[response.name] == undefined) {
      this.dialogs[response.name] = $('<div class="ding-popup-content"></div>').dialog({
          'autoOpen': false,
          'modal': true,
      });
    }
    this.dialogs[response.name].dialog('option', {'title': response.title});
    this.dialogs[response.name].html(response.data);
    Drupal.attachBehaviors(this.dialogs[response.name]);
    this.dialogs[response.name].dialog('open');
  },

  open: function(response) {
    if (this.states[response.name] == undefined) {
      this.states[response.name] = []
    }
    if (response['resubmit']) {
      this.states[response.name].push(response);
    }
    this.setState(response);
  },

  close: function(response) {
    while (this.states[response.name].length > 0) {
      state = this.states[response.name].pop();
      Drupal.detachBehaviors(this.dialog);

      // Add in extra post vars.
      $.extend(state['orig_ajax'].options.data, state['extra_data']);
      // Call original ajax callback.
      state['orig_ajax'].eventResponse(state['orig_ajax'], null);
    }
    this.dialogs[response.name].dialog('close');
  }
};

// Drupal.ding_popup = []

/**
 * Command to create a popup.
 */
Drupal.ajax.prototype.commands['ding_popup'] = function (ajax, response, status) {
  response['orig_ajax'] = ajax;
  Drupal.ding_popup.open(response);
  return;
  var content_wrapped = $('<div></div>').html(response.data);

  content_wrapped.dialog({
      'close': function (event, ui) {
        $(this).dialog('destroy').remove();
      },
      'modal': true,
      'draggable': false,
      'resizable': false,
      'title': response.title
  });

  // Store data for cleanup.
  Drupal.ding_popup.push({
    'dialog': content_wrapped,
    'resubmit': response.resubmit,
    'extra_data': response.extra_data,
    'orig_ajax': ajax
  });
};

/**
 * Command to close a popup.
 */
Drupal.ajax.prototype.commands['ding_popup_close'] = function (ajax, response, status) {
  Drupal.ding_popup.close(response);
  return;
  var popup = Drupal.ding_popup.pop();
  if (popup != undefined) {
    // Destroy dialog.
    popup['dialog'].dialog('destroy');
    if (popup['resubmit']) {
      // Add in extra post vars.
      $.extend(popup['orig_ajax'].options.data, popup['extra_data']);
      // Call original ajax callback.
      popup['orig_ajax'].eventResponse(popup['orig_ajax'], null);
    }
  }
};


})(jQuery);
