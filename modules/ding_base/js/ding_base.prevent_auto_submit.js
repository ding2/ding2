/**
 * @file
 *
 * Processing "Terms" filter field behavior.
 */
(function ($) {
  "use strict";

  function triggerSubmit () {
    var $this = $(this);
    if (!$this.hasClass('ctools-ajaxing')) {
      $this.find('.ctools-auto-submit-click').click();
    }
  }

  Drupal.behaviors.prevent_auto_submit = {
    attach: function() {

      // Processing autocomplete functionality for "Terms" filter field.
      $("input[name='ding_base_term_name']").on('change keyup', function (e) {
        if (e.type === 'change' || (e.type === 'keyup' && e.which === 13)) {
          var form = $(this).closest('form');
          var selected;
          if ($(form).find('#autocomplete ul li.selected') !== undefined) {
            selected = $(form).find('#autocomplete ul li.selected')[0].textContent;
          }

          if (selected !== undefined) {
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
