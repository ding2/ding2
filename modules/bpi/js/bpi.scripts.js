/**
 * @file
 * Trigger Drupal's ajax on page load.
 */

(function($){
  Drupal.ajax.prototype.bpi_syndicate_images = function() {
    var ajax = this;

    // Do not perform another ajax command if one is already in progress.
    if (ajax.ajaxing) {
      return false;
    }

    try {
      $.ajax(ajax.options);
    }
    catch (err) {
    }

    return false;
  };

  /**
   * Define a point to trigger our custom actions. e.g. on page load.
   */
  $(document).ready(function() {
    var custom_settings = {};
    custom_settings.url = '/admin/bpi/images/nojs';
    custom_settings.event = 'onload';
    custom_settings.keypress = false;
    custom_settings.prevent = false;

    Drupal.ajax['bpi_syndicate_images'] = new Drupal.ajax(null, $(document.body), custom_settings);

    Drupal.ajax['bpi_syndicate_images'].bpi_syndicate_images();
  });

})(jQuery);
