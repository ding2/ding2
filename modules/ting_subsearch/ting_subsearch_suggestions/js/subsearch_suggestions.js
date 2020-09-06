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
      var message = $(r);
      $('#ting-subsearch-suggestions-placeholder').replaceWith(message);
      Drupal.attachBehaviors(message);
    }
    else {
      $('#ting-subsearch-suggestions-placeholder').remove();
    }
  }).fail(function (e) {
    console.log(e);
  });
})(jQuery);
