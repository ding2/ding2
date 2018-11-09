/**
 * @file
 *
 * Processing "Terms" filter field behavior.
 */
(function ($) {
  "use strict";

  Drupal.behaviors.prevent_auto_submit = {
    attach: function(context) {
      // Processing autocomplete functionality for "Terms" filter field.
      $("input[name='ding_base_term_name']", context).on('change keyup', function (e) {
        if (e.type === 'change' || (e.type === 'keyup' && e.which === 13)) {
          var form = $(this).closest('form');
          var autocomplete_value = $(form).find('#autocomplete ul li.selected');
          var selected;

          if (autocomplete_value.length !== 0) {
            selected = autocomplete_value[0].textContent;
          }

          if (selected !== '') {
            $("input[name='ding_base_term_name']").val(selected);
          }

          var $this = $(form);
          if (!$this.hasClass('ctools-ajaxing')) {
            $this.find('.ctools-auto-submit-click').click();
          }
        }
      });

      // Resetting "Terms" field value when switching vocabulary.
      $("select#edit-vid").change(function () {
        $("input[name='ding_base_term_name']").val("");
      });
    }
  };

})(jQuery);
