
(function ($) {

Drupal.behaviors.ding_authenticate_form = {
  attach: function (context, settings) {
    $('#ding-user-authenticate-form input[type=text]:not(.ding-user-processed), #ding-user-authenticate-form input[type=password]:not(.ding-user-processed)').addClass('ding-user-processed').each(function () {
      $(this).keypress(function (event) {
        if (event.which == 13) {
          console.dir($(this).parents('form').find('input[type=submit]').get(0));
          $($(this).parents('form').find('input[type=submit]').get(0)).trigger('mousedown');
          return false;
        }
      });
    });
  }
}

Drupal.ajax.prototype.commands['ding_user_authenticate'] = function (ajax, response, status) {
  var new_content_wrapped = $('<div></div>').html(response.data);

  new_content_wrapped.dialog({
      'close': function (event, ui) {
        $(this).dialog('destroy').remove();
      },
      'modal': true,
      'draggable': false,
      'resizable': false,
      'title': Drupal.t('User login')
  });

  // Store data for cleanup.
  Drupal.ding_user_authenticate = {
    'dialog': new_content_wrapped,
    'form_id': response.form_id,
    'orig_ajax': ajax
  }
}

Drupal.ajax.prototype.commands['ding_user_authenticate_close'] = function (ajax, response, status) {
  if (Drupal.ding_user_authenticate != undefined) {
    var dua = Drupal.ding_user_authenticate;
    Drupal.ding_user_authenticate = undefined;
    // Destroy dialog.
    dua['dialog'].dialog('destroy');
    // Add form id so ding_provider knows what form to submit.
    dua['orig_ajax'].options.data['dp_form_id'] = dua['form_id'];
    // Call original ajax callback.
    dua['orig_ajax'].eventResponse(dua['orig_ajax'], null);
  }
}


})(jQuery);
