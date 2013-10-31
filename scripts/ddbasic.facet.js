(function($) {

  // This is not the best solution, but it was decided to make a quick solution
  function facet_browser_mobile() {
    // Define vars.
    var facet_browser = $('.pane-ding-facetbrowser');

    // Create toggle link.
    $('<a />', {
      'class' : 'facet-browser-toggle js-facet-browser-hide',
      'href' : '#toggle-facet-browser',
      'text' : Drupal.t('Show search filters')
    }).prependTo('.primary-content');

    // Move and show filters on click.
    $('.facet-browser-toggle').live('click', function() {
      // Clone facet browser if it does not exist.
      var facet_browser_clone = $('.facet-browser-responsive');
      if (!facet_browser_clone.length) {
        // Clone facets.
        facet_browser
          .clone(true)
          .insertAfter(this)
          .removeAttr('class')
          .addClass('facet-browser-responsive js-facet-browser-toggle');
      }
      if (facet_browser_clone.hasClass('js-facet-browser-visible')) {
        facet_browser_clone.hide();

        facet_browser_clone.toggleClass('js-facet-browser-visible');
      } else {
        facet_browser_clone.show();

        facet_browser_clone.addClass('js-facet-browser-visible');
      }

      // Add toggle to legend.
      $('.fieldset-legend', facet_browser_clone).live('click', function() {
        if ($(this).hasClass('js-facet-browser-legend-visible')) {
          // Hide siblings.
          $(this)
            .parent()
            .siblings()
            .hide();

          // Toggle class.
          $(this).toggleClass('js-facet-browser-legend-visible');
        } else {
          // Show siblings.
          $(this)
            .parent()
            .siblings()
            .show();

          // Toggle class.
          $(this).addClass('js-facet-browser-legend-visible');
        }
      });
    });
  }

  // When ready start the magic.
  $(document).ready(function () {
    // Responsive facet browser.
    if ($('.pane-ding-facetbrowser').length) {
      facet_browser_mobile();
    }
  });

})(jQuery);
