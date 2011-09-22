(function ($) {
  campaign_content_click = function(type) {
    $('#edit-field-camp-image, #edit-field-camp-text-full').hide();

    switch(type) {
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
      campaign_content_click($('.node-campaign-form #edit-field-camp-settings input[type=radio]:checked').attr('value'));

      $('.node-campaign-form #edit-field-camp-settings input[type=radio]').click(function() {
        var type = $(this).attr('value');
        campaign_content_click(type);
      });

      $('.ding-campaign-rule select').change(function() {
        if ($(this).selected().attr('value') == 'rule_generic') {
          $(this).parent().parent().parent().find('.rule-value').hide();
        }
        else {
          $(this).parent().parent().parent().find('.rule-value').show();
        }
      });

      $('#ding-campaign-rules .ding-campaign-rule').each(function() {
        if ($(this).find('.rule-type select').selected().attr('value') == 'rule_generic') {
          $(this).find('.rule-value').hide();
        }
      });
    }
  }
})(jQuery);
