/**
 * @file
 *
 * Processing "Terms" filter field behavior.
 */
(function ($) {
  Drupal.behaviors.prevent_auto_submit = {
    attach: function(context) {
      function triggerSubmit (e) {
        var $this = $(this);
        if (!$this.hasClass('ctools-ajaxing')) {
          $this.find('.ctools-auto-submit-click').click();
        }
      }

      // Processing autocomplete functionality for "Terms" filter field.
      $("input[name='ding_base_term_name']", context).on('change keyup', function (e) {
        if (e.type === 'change' || (e.type === 'keyup' && e.which === 13)) {
          var form = $(this).closest('form');
          var selected;

          if ($(form).find('#autocomplete ul li.selected').length !== 0) {
            selected = $(form).find('#autocomplete ul li.selected')[0].textContent;
          }

          if (selected !== '') {
            $("input[name='ding_base_term_name']").val(selected);
          }
          triggerSubmit.call(form);
        }
      });

      // Resetting "Terms" field value when switching vocabulary.
      $("select#edit-vid").change(function () {
        $("input[name='ding_base_term_name']").val("");
      });
    }
  };

})(jQuery);
