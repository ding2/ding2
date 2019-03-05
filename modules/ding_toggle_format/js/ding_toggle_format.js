(function($) {

  Drupal.behaviors.toggleFormat = {
    attach: function(context, settings) {
      $('#ding-toggle-format', context).click(function() {
        var toFormat = (Cookies.get("ding_toggle_format") == 'short') ? 'long': 'short';
        Drupal.setFormat(toFormat);
        return false;
      });
    }
  };

  Drupal.behaviors.readyFormat = {
    attach: function(context, settings) {
      $('#ding-toggle-format', context).ready(function() {
        var format = (Cookies.get("ding_toggle_format")) ? Cookies.get("ding_toggle_format") : 'long';
        Drupal.setFormat(format);
      });
    }
  };

  Drupal.setFormat = function(format) {
    $("#ding-toggle-format").removeClass('ding-toggle-format-long');
    $("#ding-toggle-format").removeClass('ding-toggle-format-short');
    $("#ding-toggle-format").addClass('ding-toggle-format-' + format);
    $("li.search-result").removeClass('ding-format-long');
    $("li.search-result").removeClass('ding-format-short');
    $("li.search-result").addClass('ding-format-' + format);
    Cookies.set("ding_toggle_format", format, {
      expires: 30
    });
  };

} (jQuery));

