/**
 * @file
 * Subsearch Translate module JS functionality.
 */

(function ($) {
  'use strict';

  var settings = Drupal.settings.tingSubsearchTranslate;

  $.ajax({
    type: 'POST',
    url: '/subsearch_translate',
    data: {
      'originalSearch': settings.originalSearch,
      'originalSearchNumResults': settings.originalSearchNumResults,
    },
  }).done(function(r) {
    if (r !== '') {
      $('#ting-subsearch-translate-placeholder').replaceWith(r);
      Drupal.attachBehaviors(r);
    }
    else {
      $('#ting-subsearch-translate-placeholder').remove();
    }
  }).fail(function(e) {
    console.log(e);
  });
})(jQuery, Drupal);
