(function($) {

  Drupal.behaviors.toggleFormat = {
    attach: function(context, settings) {
      $('#ding-toggle-format', context).click(function() {
        var toFormat = (Cookies.get('ding_toggle_format') == 'short') ? 'long': 'short';
        Drupal.setFormat(toFormat);
        return false;
      });
    }
  };

  Drupal.behaviors.readyFormat = {
    attach: function(context, settings) {
      if ($('body').hasClass('page-search-ting')) {
        $('.pane-ding-toggle-format-toggle').insertBefore('.pane-search-result');
      }

      $('#ding-toggle-format', context).ready(function() {
        var format = (Cookies.get('ding_toggle_format')) ? Cookies.get('ding_toggle_format') : 'long';
        Drupal.setFormat(format);
      });
    }
  };

  Drupal.setFormat = function(format) {
    $('#ding-toggle-format').removeClass('ding-toggle-format-long');
    $('#ding-toggle-format').removeClass('ding-toggle-format-short');
    $('#ding-toggle-format').addClass('ding-toggle-format-' + format);

    /* Search results formats */
    $('li.search-result, div.material-item').removeClass('ding-format-long');
    $('li.search-result, div.material-item').removeClass('ding-format-short');
    $('li.search-result, div.material-item').addClass('ding-format-' + format);

    /* Ting objects formats */
    $('.pane-ting-object, div.ting-object').removeClass('ding-format-long');
    $('.pane-ting-object, div.ting-object').removeClass('ding-format-short');
    $('.pane-ting-object, div.ting-object').addClass('ding-format-' + format);

    Cookies('ding_toggle_format', format, {
      expires: 30
    });
  };

} (jQuery));
