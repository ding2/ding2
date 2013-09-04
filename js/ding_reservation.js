/**
 * Handle reservation checkboxes select all and select count on buttons.
 */
(function ($) {
  $(document).ready(function($) {
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
      var form = $(this).closest('form');
      var buttons = $('input[type=submit]', form);
      var count = $('.material-item input[type=checkbox]:checked', form).length;
      update_buttons(buttons, count);

      // Handle all checkbox checked state, so if not are all selected the
      // checkbox is not checked.
      if ($('.material-item input[type=checkbox]', form).length != count) {
        $('.select-all input[type=checkbox]', form).prop('checked', false);
      }
      else {
        $('.select-all input[type=checkbox]', form).prop('checked', true);
      }
    })

    // Update count string on the buttons.
    function update_buttons(buttons, count) {
     buttons.each(function(index) {
       var btn = $(buttons[index]);
       btn.val(btn.val().replace(/\(\d+\)/, '(' + count + ')'));
     });
    }
  });
})(jQuery);