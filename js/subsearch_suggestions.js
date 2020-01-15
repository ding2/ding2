(function ($) {
  'use strict';

  let ssSettings = Drupal.settings;

  let keys = ssSettings.subsearch_suggestions.keys;
  let conditions = ssSettings.subsearch_suggestions.conditions;
  let results = ssSettings.subsearch_suggestions.results;

  const urlParams = new URLSearchParams(window.location.search);
  const originalSearch = urlParams.get('original-search');

  let progressText = Drupal.t('Loading suggestions ...');
  let wrapper = $('#subsearch-suggestions');
  wrapper.text(progressText);

  if (originalSearch !== null) {
    let message = Drupal.t('See results for "!keys", the search for "!originalSearch" returned 0 hits.', {'!keys': keys, '!originalSearch': originalSearch});
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
      .done(function(r) {
        if (r !== '') {
          wrapper.html(r);
        }
        else {
          let messagePane = $('.pane-page-messages');
          let messagesList = messagePane.find('li');
          if (messagesList.length === 1) {
            wrapper.parent('li').remove();
            messagePane.find('.close-container a').click();
          }
          else {
            wrapper.parent('li').remove();
          }
        }
      })
      .fail(function(e) {
        console.log(e);
      });
  }
})(jQuery, Drupal);
