(function($) {
  "use strict";

  /**
   * A11t toggle controls.
   */
  Drupal.behaviors.ddbasic_a11y = {
    attach: function(context) {
      $(".a11y-trigger", context).click(function(event) {
        var $element = $(this);
        var $html = $("html");

        if ($element.hasClass("font-size-trigger")) {
          $html.toggleClass("a11y");
        }

        if ($element.hasClass("contrast-trigger")) {
          $html.toggleClass("a11y-contrast");
        }
        event.preventDefault();
      });
    }
  };
})(jQuery);
