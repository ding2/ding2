/**
 * Javascript that adds the extra select all checkbox option to the titles on
 * the user reservation page.
 */
(function ($) {
  $(document).ready(function($) {
    $('.select-all-checkbox').click(function() {
      var checkboxes = $('input[type=checkbox]', $(this).closest('form'));
      if ($(this).prop('checked')) {
        checkboxes.prop('checked', true);
      }
      else {
        checkboxes.prop('checked', false);
      }
    });
  });
})(jQuery);