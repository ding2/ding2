(function ($) {
  'use strict';

  let ssSettings = Drupal.settings;

  let keys = ssSettings.subsearch_suggestions.keys;
  let conditions = ssSettings.subsearch_suggestions.conditions;
  let results = ssSettings.subsearch_suggestions.results;

  const urlParams = new URLSearchParams(window.location.search);
  const originalSearch = urlParams.get('original-search');

  let main = $('.pane-page-content');
  main.prepend('<div id="subsearch-suggestions" style="background-color: #F1F2F2; padding-top: 30px;"><div style="max-width: 1124px;margin-left: auto;margin-right: auto;width: 90%;" class="suggestions inner-content"></div></div>');
  let wrapper = $('#subsearch-suggestions .inner-content');

  if (originalSearch !== null) {
    let message = Drupal.t('See results for "!keys", the search for "!originalSearch" returned 0 hits.', {
      '!keys': keys,
      '!originalSearch': originalSearch
    });
    message = '<div id="subsearch-suggestions-first">' + message + '</div>';
    wrapper.html(message);
  }
  else {
    $.ajax({
      type: 'POST',
      url: '/subsearch_suggestions',
      data: {
        'keys': keys,
        'conditions': conditions,
        'results': results
      },
    })
      .done(function (r) {
        if (r !== '') {
          wrapper.html(r);
        }
      })
      .fail(function (e) {
        console.log(e);
      });
  }
})(jQuery, Drupal);
