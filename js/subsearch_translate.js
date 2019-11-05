(function ($) {
  'use strict';

  let stSettings = Drupal.settings;

  let keys = stSettings.subsearch_translate.keys;
  let conditions = stSettings.subsearch_translate.conditions;
  let results = stSettings.subsearch_translate.results;

  let progressText = Drupal.t('Loading translations ...');
  let wrapper = $('#subsearch-translate');
  wrapper.text(progressText);

  $.ajax({
    type: 'POST',
    url: '/subsearch_translate',
    data: {
      'keys': keys,
      'conditions': conditions,
      'results': results
    },
  })
    .done(r => {
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
    .fail(e => {
      console.log(e);
    });
})
(jQuery, Drupal);
