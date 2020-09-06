/**
 * @file
 * Subsearch Suggestions JS functionality.
 */

(function ($) {
  'use strict';

  var settings = Drupal.settings.tingSubsearchSuggestions;

  $.ajax({
    type: 'POST',
    url: '/subsearch_suggestions',
    data: {
      'originalSearch': settings.originalSearch,
      'originalSearchNumResults': settings.originalSearchNumResults
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
