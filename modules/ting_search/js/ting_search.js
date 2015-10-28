(function($) {
  "use strict";

  $(document).ready(function() {
    // Add overlay with spinner to search input fields while searching.
    $('input[name="search_block_form"]').keydown(function(event) {
      // When enter is hit in the search form.
      if (event.which == 13) {
        Drupal.TingSearchOverlay();
      }
    });

    // Hook into the search button as well.
    $('#search-block-form input[type="submit"]').click(function() {
      Drupal.TingSearchOverlay();

      return true;
    });

    // Add search link to the different links on the search result page.
    $('.search-results a').live('click', function() {
      if ($(this).not('[target="_blank"]').length) {
        Drupal.TingSearchOverlay();
      }
    });
  });

  /**
   * Add or remove spinner class to search block form wrapper.
   *
   * @param bool $state
   *   If TRUE the class spinner is added, FALSE it's removed.
   */
  function ting_search_toggle_spinner(state) {
    $('.search-field-wrapper').toggleClass('spinner', state);
  }

  // Override default auto-complete to add spinner class.
  Drupal.jsAC.prototype.setStatus = function (status) {
    switch (status) {
      case 'begin':
        ting_search_toggle_spinner(true);
        break;
      case 'cancel':
      case 'error':
      case 'found':
        ting_search_toggle_spinner(false);
        break;
    }
  };

  /**
   * Override default auto-complete behavior that prevents form submit
   */
  Drupal.autocompleteSubmit = function () {
    $('#autocomplete').each(function () {
      this.owner.hidePopup();
    });

    return true;
  };
}(jQuery));
