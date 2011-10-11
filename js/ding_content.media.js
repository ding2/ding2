(function ($) {
Drupal.behaviors.dingContentMediaLibrary = {
  attach: function (context, settings) {
    var library = new Drupal.media.browser.library(Drupal.settings.media.browser.ding_content);
    $('#media-browser-tabset').bind('tabsselect', function (event, ui) {
      if (ui.tab.hash === '#media-tab-ding_content') {
        // Grab the parameters from the Drupal.settings object
        var params = {};
        for (var parameter in Drupal.settings.media.browser.library) {
          params[parameter] = Drupal.settings.media.browser.library[parameter];
        }
        library.start($(ui.panel), params);
        $('#scrollbox').bind('scroll', library, library.scrollUpdater);
      }
    });
  }
};
}(jQuery));