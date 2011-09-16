(function ($) {
  campaign_content_click = function(type) {
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

  campaign_type_click = function(type) {
    $('#edit-field-camp-keywords').hide();

    switch(type) {
      case 'search':
        $('#edit-field-camp-keywords').show();
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

      campaign_type_click($('.node-campaign-form #edit-field-camp-type input[type=radio]:checked').attr('value'));

      $('.node-campaign-form #edit-field-camp-type input[type=radio]').click(function() {
        var type = $(this).attr('value');
        campaign_type_click(type);
      });
    }
  }
})(jQuery);
