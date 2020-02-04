(function ($) {
  'use strict';

  let ssSettings = Drupal.settings;

  let keys = ssSettings.subsearch_secondary.keys;
  let conditions = ssSettings.subsearch_secondary.conditions;
  let results = ssSettings.subsearch_secondary.results;

  let wrapper = $('#subsearch-secondary');

  $.ajax({
    type: 'POST',
    url: '/subsearch_secondary',
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
      else {
        wrapper.remove();
      }
    })
    .fail(function (e) {
      console.log(e);
    });

})(jQuery, Drupal);
