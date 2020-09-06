/**
 * @file
 * Subsearch Translate module JS functionality.
 */

(function ($) {
  'use strict';

  var settings = Drupal.settings.subsearch_translate;
  var keys = settings.keys;
  var conditions = settings.conditions;
  var results = settings.results;

  $.ajax({
    type: 'POST',
    url: '/subsearch_translate',
    data: {
      'keys': keys,
      'conditions': conditions,
      'results': results
    },
  }).done(function(r) {
    if (r !== '') {
      $('#ting-subsearch-translate-placeholder').replaceWith(r);
      Drupal.attachBehaviors(r);
    }
  }).fail(function(e) {
    console.log(e);
  });
})(jQuery, Drupal);
