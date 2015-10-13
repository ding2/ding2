/**
 * Handle reservation checkboxes select all and select count on buttons.
 */
(function ($) {
  "use strict";
  $(document).ready(function($) {
    // Variables used to make the buttons follow scroll.
    var actions = $(".action-buttons");
    var actions_offset = 0;
    var win = $(window);

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
      var form = $(this).closest('form');
      var buttons = $('input[type=submit]', form);
      var count = $('.material-item input[type=checkbox]:checked', form).length;
      update_buttons(buttons, count);

      // Handle all checkbox checked state, so if not are all selected the
      // checkbox is not checked.
      if ($('.material-item input[type=checkbox]', form).length != count) {
        $('.select-all input[type=checkbox]:not(:disabled)', form).prop('checked', false);
      }
      else {
        $('.select-all input[type=checkbox]:not(:disabled)', form).prop('checked', true);
      }
    });

    /**
     * Update count string on the buttons.
     */
    function update_buttons(buttons, count) {
      buttons.each(function(index) {
      var btn = $(buttons[index]);
        btn.val(btn.val().replace(/\(\d+\)/, '(' + count + ')'));

        // Toggle buttons based on count.
        if (count > 0) {
          if (!actions_offset) {
            // First time buttons are shown, get their offset value.
            actions_offset = actions.offset().top;
          }
          btn.removeAttr("disabled");
        }
        else {
          btn.prop('disabled', 'disabled');
        }
      });

      toggle_scroll_buttons();
    }

    // Enable scroll and toggle of buttons. It uses class to this effect can be
    // cancelled by removing classes from the theme.
    $(window).scroll(function(){
      toggle_scroll_buttons();
    });

    /**
     * Helper function to toggle the "action-buttons-is-scrolling" class, which
     * moves the out of flow to follow the top of the screen on scroll.
     */
    function toggle_scroll_buttons() {
      if (actions_offset < win.scrollTop()) {
        actions.addClass('action-buttons-is-scrolling');
      }
      else {
        actions.removeClass('action-buttons-is-scrolling');
      }
    }
  });
})(jQuery);
