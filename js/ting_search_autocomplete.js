/**
 * Handler for the "onkeydown" event.
 *
 * Overwritten from Drupal's autocomplete.js to automatically selects
 * the highlighted item if the input has the auto-submit call and the
 * user presses enter.
 *
 * @see https://drupal.org/node/309088
 */
(function ($) {
  Drupal.jsAC.prototype.onkeydown = function (input, e) {
    if (!e) {
      e = window.event;
    }
    switch (e.keyCode) {
      case 13: // Enter.
        if ($(input).hasClass('auto-submit')) {
          this.hidePopup(e.keyCode);
          this.db.cancel();
          this.input.form.submit();
        }
        return true;

      case 40: // down arrow.
        this.selectDown();
        return false;

      case 38: // up arrow.
        this.selectUp();
        return false;

      default: // All other keys.
        return true;
    }
  };
})(jQuery);
