/**
 * @file
 * Secondary search JS functionality.
 */

(function ($) {
  'use strict';

  let ssSettings = Drupal.settings;

  let keys = ssSettings.subsearch_secondary.keys;
  let conditions = ssSettings.subsearch_secondary.conditions;
  let results = ssSettings.subsearch_secondary.results;

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
          $('#subsearch-secondary').html(r);
        }
      })
      .fail(function (e) {
        console.log(e);
      });

})(jQuery, Drupal);
