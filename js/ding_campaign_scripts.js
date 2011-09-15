(function ($) {
  process_radio_click = function(type) {
    $('#edit-field-camp-text-plain, #edit-field-camp-image, #edit-field-camp-text-full').hide();

    switch(type) {
      case 'plain':
        $('#edit-field-camp-text-plain').show();
        break;
      case 'image':
        $('#edit-field-camp-image').show();
        break;
      case 'full':
        $('#edit-field-camp-text-full').show();
        break;
    }
  }

  Drupal.behaviors.ding_campaing_init = {
    attach: function(context) {
      process_radio_click($('.node-campaign-form #edit-field-camp-settings-und input[type=radio]:checked').attr('value'));

      $('.node-campaign-form #edit-field-camp-settings-und input[type=radio]').click(function() {
        var type = $(this).attr('value');
        process_radio_click(type);
      });
    }
  }
})(jQuery);
