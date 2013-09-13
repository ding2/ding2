(function($) {
  "use strict";
  $('document').ready(function() {
    // Ensure that all checkboxes are not checked (if user reloads the page
    // etc.).
    $('form input[type=checkbox]').prop('checked', false);
    $('.action-buttons input[type=submit]').prop('disabled', 'disabled');

    // Handle select all checkboxes.
    $('.select-all input[type=checkbox]').click(function() {
      var checkboxes = $('input[type=checkbox]', $(this).closest('form'));
      if ($(this).prop('checked')) {
        checkboxes.prop('checked', true);
      }
      else {
        checkboxes.prop('checked', false);
      }
      checkboxes.change();
    });

    // Handle checkbox button count.
    $('.material-item input[type=checkbox]').change(function() {
      // Update button count.
      var form = $(this).closest('form');
      var buttons = $('input[type=submit]', form);
      update_buttons(buttons, $('.material-item input[type=checkbox]:checked', form).length);

      // Handle all checkbox checked state, so if not are all selected the
      // checkbox is not checked.
      var checkboxes = $('.material-item input[type=checkbox]', form);

      // Find all checked checkboxes found above and count theme.
      var checked = 0;
      checkboxes.each(function(index) {
        var checkbox = $(checkboxes[index]);
        if (checkbox.is(':checked')) {
          checked++;
        }
      });

      // Change the select all based on the count found above.
      if (checked !== checkboxes.length) {
        $('.select-all input[type=checkbox]').prop('checked', false);
      }
      else {
        $('.select-all input[type=checkbox]').prop('checked', true);
      }
    });

    // Update count string on the buttons.
    function update_buttons(buttons, count) {
      buttons.each(function(index) {
        var btn = $(buttons[index]);
        btn.val(btn.val().replace(/\(\d+\)/, '(' + count + ')'));

        // Toggle buttons based on count.
        if (count > 0) {
          btn.removeAttr("disabled");
        }
        else {
          btn.prop('disabled', 'disabled');
        }
      });
    }
  });
})(jQuery);
