/**
 * @file
 * Subsearch Suggestions JS functionality.
 */

(function ($) {
  'use strict';

  var settings = Drupal.settings.tingSubsearchSuggestions;
  var keys = settings.keys;
  var numTotalObjects = settings.numTotalObjects;

  $.ajax({
    type: 'POST',
    url: '/subsearch_suggestions',
    data: {
      'keys': keys,
      'numTotalObjects': numTotalObjects
    },
  }).done(function (r) {
    if (r !== '') {
      $('#ting-subsearch-suggestions-placeholder').replaceWith(r);
      Drupal.attachBehaviors(r);
    }
    else {
      $('#ting-subsearch-suggestions-placeholder').remove();
    }
  }).fail(function (e) {
    console.log(e);
  });
})(jQuery);
