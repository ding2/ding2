(function ($) {
  "use strict";

  // Behaviors might be called with a DOM element (document on page
  // load) or a jQuery object (on AJAX load). DDB React expects a DOM
  // element with querySelectorAll, so this tries to do the right
  // thing.
  var getElement = function(element) {
    if (typeof element.querySelectorAll !== 'function') {
      element = element[0] || element;
    }

    if (typeof element.querySelectorAll !== 'function') {
      return null;
    }

    return element;
  }

  Drupal.behaviors.ding_react = {
    attach: function(context) {
      // Ensure that we have a DOM element.
      var element = getElement(context);
      if (element) {
        window.mountDdbApps(element);
      }
    },
    detach: function(context) {
      var element = getElement(context);
      if (element) {
        window.unMountDdbApps(element);
      }
    }
  };

})(jQuery);
