/**
 * Handle loan checkboxes select all and select count on buttons.
 */
(function ($) {
  "use strict";
  $(document).ready(function($) {
    // Ensure that all checkboxes are not checked (if user reloads the page
    // etc.).
    $('form input[type=checkbox]').prop('checked', false);
    $('.action-buttons input[type=submit]').prop('disabled', 'disabled');

    // Handle select all checkboxes.
    $('.select-all input[type=checkbox]').click(function() {
      var checkboxes = $('input[type=checkbox]', $(this).closest('.select-all').nextUntil('.select-all'));
      if ($(this).prop('checked')) {
        // Only checkboxes that are enabled.
        checkboxes.each(function(i) {
          var box = $(checkboxes[i]);
          if (!box.is(':disabled')) {
            box.prop('checked', true);
            box.change();
          }
        });
      }
      else {
        checkboxes.prop('checked', false);
      }
    });

    // Handle checkbox button count.
    $('.material-item input[type=checkbox]').change(function() {
      // Update button count.
      var form = $(this).closest('form');
      var buttons = $('input[type=submit]', form);
      update_buttons(buttons, $('.material-item input[type=checkbox]:checked', form).length);

      // Handle all checkbox checked state, so if not are all selected the
      // checkbox is not checked.
      var item = $(this).closest('.material-item');

      // Try to find the checkboxes in the current clicked group (not disabled).
      var checkboxes = $('input[type=checkbox]', item.prevUntil('.select-all')).not(':disabled');
      $.merge(checkboxes, $('input[type=checkbox]', item.nextUntil('.select-all'))).not(':disabled');
      $.merge(checkboxes, $('input[type=checkbox]', item)).not(':disabled');

      // Find all checked checkboxes found above and count theme
      var checked = 0;
      checkboxes.each(function(index) {
        var checkbox = $(checkboxes[index]);
        if (checkbox.is(':checked')) {
          checked++;
        }
      });

      // Change the select all based on the count found above.
      if (checked !== checkboxes.length) {
        item.prevAll('.select-all').find('input[type=checkbox]:not(:disabled)').prop('checked', false);
      }
      else {
        item.prevAll('.select-all').find('input[type=checkbox]:not(:disabled)').prop('checked', true);
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
